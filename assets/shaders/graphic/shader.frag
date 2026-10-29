#version 330 core

out vec4 FragColor;

uniform int steps;
uniform float A;
const float ZOOM = 100.0;
const vec2 OFFSET = vec2(-960.0, -540.0);

const float THICKNESS_PX = 5.0;
const float ZERO = 0.01;
const float MAX = 1000;

float func(float x){
    return A*sin(x)/(cos(x) + A);
}

float dfunc(float x){
    // return (func(x + ZERO) - func(x))/ZERO;
    return A*(cos(x)*(cos(x) + A) + sin(x)*sin(x))/((cos(x) + A)*(cos(x) + A));
}

vec4 grid(vec2 pixel){
    vec4 FragColor;
    float thickness = 0.04f;
    
    if((pixel.y <= thickness && pixel.y >= -thickness) || (pixel.x <= thickness && pixel.x >= -thickness)){
        FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }

    else if((abs(mod(pixel.y, 1.0)) <= thickness/2 && abs(mod(pixel.y, 1.0)) >= -thickness/2) || (abs(mod(pixel.x, 1.0)) <= thickness/2 && abs(mod(pixel.x, 1.0)) >= -thickness/2)){
        FragColor = vec4(0.6f, 0.6f, 0.6f, 1.0f);
    }

    else{
        FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }
    return FragColor;
}

vec4 curve(vec2 pixel){
    float x = pixel.x;
    float y = pixel.y;
    float slope = 1.0;

    for(int i = 0; i < steps; i++){
        slope *= dfunc(x);
        x = func(x);
    }
    
    float d = abs(x - y) / sqrt(1.0 + slope * slope);

    float thickness = THICKNESS_PX / ZOOM;
    float aa = 0.75 / ZOOM;
    float alpha = 1.0 - smoothstep(thickness - aa, thickness + aa, d);

    FragColor = vec4(1.0, 0.0, 0.0, alpha);
    if (gl_FragCoord.x < 20.0 || gl_FragCoord.y < 20.0 ||
    gl_FragCoord.x > 1900.0 || gl_FragCoord.y > 1060.0)
    FragColor = vec4(1.0, 0.0, 1.0, 1.0);
    return FragColor;
}

void main(){
    vec2 pixel = (gl_FragCoord.xy + OFFSET) / ZOOM;
    vec4 bottom = grid(pixel);
    vec4 top = curve(pixel);
    FragColor = vec4(mix(bottom.rgb, top.rgb, top.a), 1.0);
}