#version 330 core

layout(location = 0) in vec3 vertexPosition;

uniform mat4 mvp;

out vec4 v_color;

void main(){
    v_color = vec4((vertexPosition.y - 70) / 100);
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}