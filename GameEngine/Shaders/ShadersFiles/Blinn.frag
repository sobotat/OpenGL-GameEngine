#version 400

in vec3 worldPosition;
in vec3 worldNormal;

#define MAX_LIGHTS 16
struct light {
  vec3 position;
  vec4 color;
  float dimmingFactor;
  float diffuseFactor;
};

uniform light lights[MAX_LIGHTS];
uniform int numberOfLights;

uniform vec3 cameraPosition;
uniform vec4 meshColor;
uniform float shininess;
uniform float specular;

out vec4 fragColor;

void main () {
  vec3 cameraVector = normalize(cameraPosition - worldPosition);

  for (int index = 0; index < numberOfLights; index++) {
    vec3 lightVector = normalize(lights[index].position - worldPosition);

    vec3 halfwayVector = normalize(lightVector + cameraVector);

    float spec = pow(max(dot(worldNormal, halfwayVector), 0), shininess);

    vec4 specularVector = specular * spec * lights[index].color;
    if (dot (worldNormal, lightVector) < 0) {
      specularVector = vec4(0);
    }

    float diff = max(dot(lightVector, worldNormal), 0);

    vec4 ambient = vec4(0.05, 0.05, 0.05, 1) * meshColor;
    vec4 diffuse = lights[index].diffuseFactor * diff * (lights[index].color + meshColor);

    float distance = length(lights[index].position - worldPosition);
    float attenuation = 1.0 / (1.0 + lights[index].dimmingFactor * distance * distance);

    fragColor += (ambient + attenuation * (diffuse + specularVector));
  }
}