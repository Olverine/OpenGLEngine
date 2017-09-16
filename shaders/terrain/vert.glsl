#version 330 core

attribute vec3 vertexPosition;
attribute vec2 uv;

varying vec2 texCoord;

uniform mat4 mvp;

out vec4 v_color;

void main(){
    v_color = vec4((vertexPosition.y - 50) / 100);
    gl_Position = mvp * vec4(vertexPosition, 1.0);
    
    texCoord = uv;
}