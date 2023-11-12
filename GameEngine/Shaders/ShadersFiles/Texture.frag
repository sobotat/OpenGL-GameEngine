#version 400

out vec4 frag_colour;
uniform sampler2D textureUnitID;
uniform float textureScale;
in vec2 uv;

void main () {    
    vec2 uvScaled = uv * textureScale;
    
    //frag_colour = vec4(uvScaled,1.0,1.0); //test na funkcnost uv souřadnic
    frag_colour = texture(textureUnitID, uvScaled);
}