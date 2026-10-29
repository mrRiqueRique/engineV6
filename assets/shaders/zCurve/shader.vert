#version 330 core

layout (location = 0) in vec3 vp;

uniform mat4 ortho;
uniform mat4 model;

void main() {
   gl_Position = ortho * model * vec4(vp, 1.0);
}