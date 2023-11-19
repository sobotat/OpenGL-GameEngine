#include "Mesh.h"

#include <GL/glew.h>
#include <assimp/Importer.hpp>// C++ importerinterface
#include <assimp/scene.h>// aiSceneoutputdata structure
#include <assimp/postprocess.h>// Post processingflags

Mesh::~Mesh() {
    points.clear();
}

void Mesh::setPoints(vector<float> meshPoints) {
    points = meshPoints;
    
    //vertex buffer object (VBO)
    glGenBuffers(1, &VBO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), &points.front(), GL_STATIC_DRAW);
	
    //Vertex Array Object (VAO)
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    const int sizeOf0 = 6 * sizeof(float);    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeOf0, (GLvoid*) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeOf0, (GLvoid*) (sizeOf0 / 2));
}

void Mesh::setPoints(vector<vector<vector<float>>> meshPoints) {

    //Number of Points
    pointCount = meshPoints.size();

    // Convert 3d to 1d vector
    points = vector<float>();
    for (vector<vector<float>> row : meshPoints) {
        for (vector<float> item : row) {            
            for (float value : item) {
                points.push_back(value);
            }
        }
    }
        
    //vertex buffer object (VBO)
    glGenBuffers(1, &VBO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), &points.front(), GL_STATIC_DRAW);
	
    //Vertex Array Object (VAO)
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    const int sizeOf0 = meshPoints[0].size() * meshPoints[0][0].size() * sizeof(float);    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeOf0, (GLvoid*) 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeOf0, (GLvoid*) 4);
}

vector<float> Mesh::loadPointsFromFile(string filename) {
    Assimp::Importer importer;
    unsigned int importOptions = aiProcess_Triangulate
        | aiProcess_OptimizeMeshes              // sloučení malých plošek
        | aiProcess_JoinIdenticalVertices       // NUTNÉ jinak hodně duplikuje
        | aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
        | aiProcess_CalcTangentSpace;           // vypocet tangenty, nutny pro spravne pouziti normalove mapy
    const aiScene* scene = importer.ReadFile(filename.c_str(), importOptions);
    int count = 0;
    std::vector<float> data;
    if (scene) {
        aiMesh* mesh = scene->mMeshes[0];
        count = mesh->mNumFaces * 3;
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < 3; j++)
            {
                int id = face.mIndices[j];

                //Vertex position
                aiVector3D pos = mesh->mVertices[id];
                data.push_back(pos.x);
                data.push_back(pos.y);
                data.push_back(pos.z);

                //Vertex normal
                aiVector3D nor = mesh->mNormals[id];
                data.push_back(nor.x);
                data.push_back(nor.y);
                data.push_back(nor.z);

                //Vertex uv
                aiVector3D uv = mesh->mTextureCoords[0][id];
                data.push_back(uv.x);
                data.push_back(uv.y);
            }
        }
    }else {
        printf("Failed to load Model [%s]\n", filename.c_str());
    }

    return data;
}

void Mesh::draw() {
    glBindVertexArray(VAO);        
    glDrawArrays(GL_TRIANGLES, 0, points.size());
}
