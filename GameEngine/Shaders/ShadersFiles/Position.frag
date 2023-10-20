#version 330

in vec3 worldNormal;
out vec4 fragColor;

void main () {
  fragColor = vec4(worldNormal, 1.0f);
}