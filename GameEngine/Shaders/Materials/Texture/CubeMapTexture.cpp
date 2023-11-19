#include "CubeMapTexture.h"

#include "../../../Utils/stb_image.h"

CubeMapTexture::CubeMapTexture(string path, string extension) {

    vector<string> names = {
        "posx", "negx", "posy", "negy", "posz", "negz"
    };
    
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(false);
    for (unsigned int i = 0; i < names.size(); i++)
    {
        unsigned char *data = stbi_load( (path + names[i] + extension).c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else {
            printf("\033[1;31mFailed to load texture -> %s\033[0m\n", (path + names[i] + extension).c_str());
            stbi_image_free(data);
            return;
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}

void CubeMapTexture::apply() {
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
}
