#version 400

layout(location=0) in vec3 vp;
layout(location=1) in vec3 vn;

uniform vec3 cameraPosition;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
out vec3 fragmentPosition;

void main () {
     
     mat4 t = mat4(1);
     t[3].x = cameraPosition.x;
     t[3].y = cameraPosition.y;
     t[3].z = cameraPosition.z;
     
     gl_Position = projectionMatrix * viewMatrix * t * vec4(vp, 1.0f);
     fragmentPosition = vp;
}