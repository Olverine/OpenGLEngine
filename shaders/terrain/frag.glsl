#version 330 core

uniform sampler2D diffuse;
varying vec2 texCoord;

uniform vec3 color;

in vec4 v_color;

void main(){
    vec4 color = (texture2D(diffuse, texCoord / 10) + texture2D(diffuse, texCoord / 100)) / 2;
    gl_FragColor = color * v_color;//vec4(color, 1.0);
}