﻿#version 400

in vec3 worldPosition;
in vec3 worldNormal;
in vec3 viewVector;

uniform vec3 cameraPosition;
uniform vec3 lightPosition;
uniform vec4 lightColor;

out vec4 fragColor;

void main () {
  vec3 lightVector = normalize(lightPosition - worldPosition);
  
  vec3 cameraVector = normalize(cameraPosition - worldPosition);

  vec3 reflectVector = reflect( -lightVector, worldNormal);
  float spec = pow( max( dot(cameraVector, reflectVector), 0.0), 32);
  float specularStrength = .5;
  vec4 specular = specularStrength * spec * lightColor;
  
  float diff = max( dot(lightVector, worldNormal), 0);
  
  vec4 diffuse = diff * lightColor;
  vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);
  vec4 objectColor = vec4( 0.385, 0.647, 0.812, 1.0);
  
  fragColor = (ambient + diffuse + specular) * objectColor;
}