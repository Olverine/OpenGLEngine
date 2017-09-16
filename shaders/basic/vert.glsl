#version 330 core

attribute vec3 vertexPosition;
attribute vec2 uv;

varying vec2 texCoord;

uniform mat4 mvp;

void main(){
    gl_Position = mvp * vec4(vertexPosition, 1.0);
    texCoord = uv;
}