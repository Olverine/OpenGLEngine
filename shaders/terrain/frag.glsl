#version 330 core

uniform sampler2D grass;
uniform sampler2D cliff;
varying vec2 texCoord;

uniform vec3 color;

in vec4 v_color;

void main(){
    vec4 grassColor = (texture2D(grass, texCoord / 10) + texture2D(grass, texCoord / 100)) / 2;
    vec4 cliffColor = (texture2D(cliff, texCoord / 10) + texture2D(cliff, texCoord / 100)) / 2;
    gl_FragColor = mix(grassColor, cliffColor, clamp(v_color.x, 0, 1));// * v_color;//vec4(color, 1.0);
}