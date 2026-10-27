#version 330 core

layout (location = 0) in vec3 vp;
layout(location = 1) in vec2 vt;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform mat3 uvModel;

out vec2 TexCoord;

void main(){
    TexCoord = (uvModel* vec3(vt, 1.0)).xy;
    gl_Position = projection * view * model * vec4(vp, 1.0);
}