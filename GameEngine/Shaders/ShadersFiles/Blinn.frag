#version 400

in vec3 worldPosition;
in vec3 worldNormal;

uniform vec3 cameraPosition;
uniform vec3 lightPosition;
uniform vec4 lightColor;
uniform vec4 meshColor;

out vec4 fragColor;

void main () {
  vec3 lightVector = normalize(lightPosition - worldPosition);  
  vec3 cameraVector = normalize(cameraPosition - worldPosition);

  vec3 halfwayVector = normalize(lightVector + cameraVector);
  
  float spec = pow( max( dot(cameraVector, halfwayVector), 0.0), 32);
  float specularStrength = .5;
  vec4 specular = specularStrength * spec * lightColor;
  
  float diff = max( dot(lightVector, worldNormal), 0);
  
  vec4 diffuse = diff * lightColor;
  vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);
  
  fragColor = (ambient + diffuse + specular) * meshColor;
}