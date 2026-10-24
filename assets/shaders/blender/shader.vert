#version 330 core

layout (location = 0) in vec3 vp;
layout(location = 1) in vec2 vt;

uniform mat4 ortho;
uniform mat4 model;

out vec2 TexCoord;

void main() {
    TexCoord = vt;
    gl_Position = ortho * model * vec4(vp, 1.0);
}