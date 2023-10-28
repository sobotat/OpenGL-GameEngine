#version 400

in vec3 worldPosition;
in vec3 worldNormal;

uniform vec3 lightPosition;
uniform vec4 lightColor;
uniform float lightDimmingFactor;
uniform vec4 meshColor;

out vec4 fragColor;

void main () {
  vec3 lightVector = normalize(lightPosition - worldPosition);
  
  float diff = max( dot(lightVector, worldNormal), 0);  
  vec4 diffuse = diff * lightColor;
  vec4 ambient = vec4( 0.05, 0.05, 0.05, 1.0);

  float distance = length(lightPosition - worldPosition);
  float attenuation = 1.0 / (1.0 + lightDimmingFactor * distance * distance);

  fragColor = (ambient + attenuation * (diffuse)) * meshColor;
}