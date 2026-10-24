#version 330 core

out vec4 FragColor;

uniform vec2 resolution;
uniform mat4 inverseProjection;
uniform mat4 inverseView;
uniform vec3 cameraPosition;
uniform float maxDistance;

#define MAX_STEPS 400
#define PRECISION 0.00001
#define SPHERE_CENTER vec3(0.0, 0.0, 0.0)
#define SPHERE_RADIUS 0.1

float modSphereSDF(vec3 p, vec3 c, float radius){
    return length(mod(p - c + 0.5, 1.0) - 0.5) - radius;
}

vec3 calcNormal(vec3 p)
{
    const float h = 0.0001;
    const vec2 k = vec2(1,-1);
    return normalize( k.xyy*modSphereSDF(p + k.xyy*h, SPHERE_CENTER, SPHERE_RADIUS) + 
                      k.yyx*modSphereSDF(p + k.yyx*h, SPHERE_CENTER, SPHERE_RADIUS) + 
                      k.yxy*modSphereSDF(p + k.yxy*h, SPHERE_CENTER, SPHERE_RADIUS) + 
                      k.xxx*modSphereSDF(p + k.xxx*h, SPHERE_CENTER, SPHERE_RADIUS) );
}

struct Ray{
    vec3 direction;
    vec3 position;
};

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
    int steps = 0;
    float dist;

    for(int i = 0; i < MAX_STEPS; i++){
    dist = modSphereSDF(ray.position, SPHERE_CENTER, SPHERE_RADIUS);
        if(dist < PRECISION){
            steps = i;
            intersected = true;
            intersection = ray.position;
            normal = calcNormal(ray.position);
            break;
        }
        ray.position += ray.direction*dist;
    
        if(length(ray.position - cameraPosition) > maxDistance)
            break;
    }

    if(intersected){
        FragColor = vec4(normal, 1.0);
    }
    else{
        FragColor = vec4(0.0, 0.0, 0.0, 0.0);
    }

}