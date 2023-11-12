#version 400

out vec4 frag_colour;
uniform samplerCube textureUnitID;
in vec3 fragmentPosition;

void main () {    
    frag_colour = texture(textureUnitID, fragmentPosition);
}