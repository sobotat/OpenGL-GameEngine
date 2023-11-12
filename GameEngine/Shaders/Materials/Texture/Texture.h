#pragma once
#include "string"
#include <GL/glew.h>

using namespace std;
class Texture {
protected:
    unsigned int textureId = 0;
    float textureScale = 1;
public:
    Texture();
    Texture(string filename, int textureRepeatMode = GL_REPEAT);
    virtual void apply();
    
    float getTextureScale() const;
    void setTextureScale(float textureScale);
};
