#version 330 core

out vec4 FragColor;

in vec3 Position;
uniform vec3 cameraPosition;
uniform float zFar;

void main() {
    FragColor = vec4(abs(1.0 - length(Position - cameraPosition)/zFar), abs(1.0 - length(Position - cameraPosition)/zFar), abs(1.0 - length(Position - cameraPosition)/zFar), 1.0);
}