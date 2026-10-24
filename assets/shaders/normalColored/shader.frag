#version 330 core

out vec4 FragColor;

in vec3 Normal;

void main() {
    FragColor = vec4(abs(sin(Normal.x)/cos(Normal.x)), abs(sin(Normal.y)/cos(Normal.y)), abs(sin(Normal.z)/cos(Normal.z)), 1.0);
}