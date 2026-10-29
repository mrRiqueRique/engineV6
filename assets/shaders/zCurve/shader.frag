#version 330 core

out vec4 FragColor;

uniform vec2 resolution;
uniform mat4 inverseProjection;
uniform mat4 inverseView;
uniform vec3 cameraPosition;
uniform float dist;
uniform int steps;
uniform float maxDistance;
uniform float A;
#define MAX_STEPS 500
#define PRECISION 0.02
#define HMAX 1.5         
#define XMAX 20.0

float func(float x){
    return (A + sin(x)) * (A - cos(x));
}

float h(vec2 xz) {
    if (steps < 2 || xz.y < dist || xz.y > float(steps) * dist || abs(xz.x) > XMAX)
        return 0.0;

    float t = xz.y / dist - 1.0;               // 0 at slice 1
    int   i = min(int(floor(t)), steps - 2);   // segment index
    float w = t - float(i);

    float f = func(xz.x);                      // func^1(x)
    for (int k = 0; k < i; k++) f = func(f);   // func^(i+1)(x)
    float g = func(f);                         // func^(i+2)(x)

    return mix(f, g, w);
}

float sdHeightfield(vec3 p) {
    const float safety = 0.8;

    float h0  = h(p.xz);
    float gap = p.y - h0;

    vec3  v   = p - cameraPosition;
    float t   = length(v);
    float cap = 0.01 * t + 0.02;                // max step, same footprint rule as before

    float s = length(v.xz);
    vec2  u = (s > 1e-6) ? v.xz / s : vec2(1.0, 0.0);

    float L = max(abs(h(p.xz + u * (0.5 * cap)) - h0) / (0.5 * cap),
                  abs(h(p.xz + u * cap)         - h0) /  cap);

    float d = gap * inversesqrt(1.0 + L * L) * safety;
    return min(d, cap);
}

struct Ray{
    vec3 direction;
    vec3 position;
};

vec3 calcNormal(vec3 p)
{
    const float h = 0.0001;
    const vec2 k = vec2(1,-1);
    return normalize( k.xyy*sdHeightfield(p + k.xyy*h) + 
                      k.yyx*sdHeightfield(p + k.yyx*h) + 
                      k.yxy*sdHeightfield(p + k.yxy*h) + 
                      k.xxx*sdHeightfield(p + k.xxx*h) );
}

void main() {
    vec2 pixel = gl_FragCoord.xy;
    vec2 ndc = (pixel / resolution) * 2.0 - 1.0;
    vec4 homogenous = inverseProjection * vec4(ndc, -1.0, 1.0);
    vec3 viewPos = homogenous.xyz/homogenous.w;
    vec4 world = inverseView * vec4(viewPos, 1.0);
    vec3 worldPos = world.xyz/world.w;
    Ray ray = Ray(vec3(normalize(worldPos.xyz - cameraPosition)), cameraPosition);

    bool intersected = false;
    vec3 intersection;
    vec3 normal;
    int rmSteps = 0;

    float dist;

    for(int i = 0; i < MAX_STEPS; i++){
        if (ray.position.y > HMAX && ray.direction.y >= 0.0) break;
        dist = sdHeightfield(ray.position);
        
        if(dist < PRECISION){
            rmSteps = i;
            intersected = true;
            intersection = ray.position;
            normal = calcNormal(intersection);
            break;
        }


        ray.position += ray.direction*dist;

        if(length(ray.position - cameraPosition) > maxDistance)
            break;
    }

    if(intersected)
        FragColor = vec4(vec3(abs(1.0 - length(ray.position - cameraPosition)/maxDistance)), 1.0);
    else
        FragColor = vec4(0.0, 0.0, 0.0, 0.0);
}