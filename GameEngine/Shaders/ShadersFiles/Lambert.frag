﻿#version 400

in vec3 worldPosition;
in vec3 worldNormal;

#define MAX_LIGHTS 16
struct light {
  int type;
  vec3 position;
  vec4 color;
  float dimmingFactorLinear;
  float dimmingFactorQuadratic;
  float diffuseFactor;
  vec3 direction;
  float angle;
  float fadeStartAngle;
};

#define LIGHT_NOTSET       -1
#define LIGHT_POINT         0
#define LIGHT_SPOT          1
#define LIGHT_DIRECTIONAL   2

uniform light lights[MAX_LIGHTS];
uniform int numberOfLights;

uniform vec4 meshColor;
uniform vec4 meshAmbientColor;

uniform int hasTexture;
uniform sampler2D textureUnitID;
uniform float textureScale;
in vec2 uv;

out vec4 fragColor;

void main () {
  for (int index = 0; index < numberOfLights; index++) {
    vec3 lightVector;
    if (lights[index].type == LIGHT_DIRECTIONAL)
      lightVector = normalize(lights[index].direction);
    else
      lightVector = normalize(lights[index].position - worldPosition);

    float diff = max(dot(lightVector, worldNormal), 0);
    vec4 diffuseColor;
    if (hasTexture == 1) {
      diffuseColor = lights[index].diffuseFactor * diff * ((lights[index].color + texture(textureUnitID, uv * textureScale)) / 2);
    } else {
      diffuseColor = lights[index].diffuseFactor * diff * ((lights[index].color + meshColor) / 2);
    }

    float attenuation = 1;
    if (lights[index].type != LIGHT_DIRECTIONAL) {
      float distance = length(lights[index].position - worldPosition);
      attenuation = 1.0 / (1.0 + lights[index].dimmingFactorLinear * distance + lights[index].dimmingFactorQuadratic * distance * distance);
    }

    if (lights[index].type == LIGHT_SPOT) {
      float spotCosine = dot(normalize(-lights[index].direction), lightVector);
      float cosLightAngle = cos(radians(lights[index].angle));
      if (spotCosine > cosLightAngle) {
        float intensity = (spotCosine - cosLightAngle) / (cos(radians(lights[index].fadeStartAngle)) - cosLightAngle);
        intensity = clamp(intensity, 0.0, 1.0);
        fragColor += attenuation * intensity * diffuseColor;
      }
    } else
      fragColor += attenuation * diffuseColor;
  }

  vec4 ambientColor;
  if (hasTexture == 1) {
    ambientColor = meshAmbientColor * texture(textureUnitID, uv * textureScale);
  } else {
    ambientColor = meshAmbientColor * meshColor;
  }
  fragColor += ambientColor;
}