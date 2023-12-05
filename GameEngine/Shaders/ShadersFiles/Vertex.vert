#version 400

layout(location=0) in vec3 vp;
layout(location=1) in vec3 vn;
layout(location = 2) in vec2 vt;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
out vec3 worldPosition;
out vec3 worldNormal;
out vec2 uv;

void main () {
     worldNormal = normalize(transpose(inverse(mat3(modelMatrix) / modelMatrix[3][3])) * vn);
     uv = vt;
     
     worldPosition = vec3(modelMatrix * vec4 (vp, 1.0));
     gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
}