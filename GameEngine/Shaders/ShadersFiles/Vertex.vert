#version 330

layout(location=0) in vec3 vp;
layout(location=1) in vec3 vp_color;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
out vec4 worldPosition;
out vec3 color;

void main () {
     worldPosition = projectionMatrix * viewMatrix * modelMatrix * vec4 (vp, 1.0);
     gl_Position = worldPosition;
     color = vp_color;
}