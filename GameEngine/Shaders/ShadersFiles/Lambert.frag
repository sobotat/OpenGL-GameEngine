#version 400

in vec3 worldPosition;
in vec3 worldNormal;

#define MAX_LIGHTS 16
struct light {
  int type;
  vec3 position;
  vec4 color;
  float dimmingFactor;
  float diffuseFactor;
  vec3 direction;
  float angle;
};

uniform light lights[MAX_LIGHTS];
uniform int numberOfLights;

uniform vec4 meshColor;

out vec4 fragColor;

void main () {
  for (int index = 0; index < numberOfLights; index++) {
    vec3 lightVector = normalize(lights[index].position - worldPosition);

    float diff = max(dot(lightVector, worldNormal), 0);
    vec4 diffuse = lights[index].diffuseFactor * diff * (lights[index].color + meshColor);
    vec4 ambient = vec4(0.05, 0.05, 0.05, 1.0) * meshColor;

    float distance = length(lights[index].position - worldPosition);
    float attenuation = 1.0 / (1.0 + lights[index].dimmingFactor * distance * distance);

    fragColor += (ambient + attenuation * (diffuse));
  }
}