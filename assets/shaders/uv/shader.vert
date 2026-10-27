#version 330 core

layout (location = 0) in vec3 vp;
layout(location = 1) in vec2 vt;

uniform mat4 ortho;
uniform mat3 uvModel;

void main(){
    gl_Position = ortho * vec4(uvModel*vec3(vt, 1.0), 1.0);
}