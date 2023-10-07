#include "Mesh.h"

#include <GL/glew.h>

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
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeOf0, (GLvoid*) 3);
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

void Mesh::draw() {
    glBindVertexArray(VAO);        
    glDrawArrays(GL_TRIANGLES, 0, points.size());
}
