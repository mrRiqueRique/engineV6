#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1; // first colored
uniform sampler2D texture2; // first z
uniform sampler2D texture3; // second colored
uniform sampler2D texture4; // second z

void main() {
    vec4 Texture1 = texture(texture1, TexCoord);
    vec4 Texture2 = texture(texture2, TexCoord);
    vec4 Texture3 = texture(texture3, TexCoord);
    vec4 Texture4 = texture(texture4, TexCoord);

    vec2 pixel = gl_FragCoord.xy;
    if(Texture2.g > Texture4.g){
        FragColor = vec4(Texture1.xyz, 1.0);
    }
    else{
        FragColor = vec4(Texture3.xyz, 1.0);
    }
}