#include "Mesh.h"

#include <cstddef>
#include <utility>
#include <GL/glew.h>

Mesh::Mesh(ShaderProgram* shaderProgram) {
    this->shaderProgram = shaderProgram;
}

Mesh::~Mesh() {
    points.clear();
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
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, meshPoints[0].size() * meshPoints[0][0].size() * sizeof(float), (GLvoid*) 0);
}

void Mesh::tick() {}

void Mesh::draw() {
    shaderProgram->useProgram();
    glBindVertexArray(VAO);        
    glDrawArrays(GL_TRIANGLES, 0, points.size());
}

bool operator==(const Mesh& mesh1, const Mesh& mesh2) {
    return mesh1.VAO == mesh2.VAO;
}
