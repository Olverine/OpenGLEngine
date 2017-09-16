#version 330 core

uniform sampler2D diffuse;
varying vec2 texCoord;

uniform vec3 color;

void main(){
    gl_FragColor = texture2D(diffuse, texCoord);// * vec4(color, 1);
}