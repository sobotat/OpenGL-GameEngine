﻿#version 330

layout(location=0) in vec3 vp;
layout(location=1) in vec3 vn;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
out vec3 worldPosition;
out vec3 worldNormal;

void main () {
     worldNormal = normalize(vec3(modelMatrix * vec4(vn, 0.0)));
     
     worldPosition = vec3(modelMatrix * vec4 (vp, 1.0));
     gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
}