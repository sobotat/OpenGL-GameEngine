#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../../Utils/stb_image.h"

Texture::Texture() {}

Texture::Texture(string filename, int textureRepeatMode) {
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureRepeatMode);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureRepeatMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 4);
    if (data) {        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
        return;
    }
    printf("\033[1;31mFailed to load texture -> %s\033[0m\n", filename.c_str());
    stbi_image_free(data);
}

void Texture::apply() {
    glBindTexture(GL_TEXTURE_2D, textureId);
}

float Texture::getTextureScale() const {
    return textureScale;
}

void Texture::setTextureScale(float textureScale) {
    this->textureScale = textureScale;
}
