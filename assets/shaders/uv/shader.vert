#version 330 core

layout (location = 0) in vec3 vp;
layout(location = 1) in vec2 vt;

uniform mat4 ortho;
uniform vec2 offset;

void main(){
    gl_Position = ortho * vec4(vt + offset, 1.0, 1.0);
}