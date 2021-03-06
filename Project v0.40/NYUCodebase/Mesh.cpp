//
//  Mesh.cpp
//  NYUCodebase
//
//  Created by Errol Elbasan on 5/12/16.
//  Copyright © 2016 Ivan Safrin. All rights reserved.
//

#include "Mesh.hpp"
using namespace std;

void Mesh::loadOBJ(const char *fileName) {
    ifstream infile(fileName);
    string line;
    std::vector<float> fileVertices;
    std::vector<float> fileUVs;
    std::vector<float> fileNormals;
    while (getline(infile, line)) {
        istringstream sStream(line);
        string token;
        getline(sStream, token, ' ');
        if (token == "v") {
            while (getline(sStream, token, ' ')) {
                fileVertices.push_back(atof(token.c_str()));
            }
        }
        else if (token == "vn") {
            while (getline(sStream, token, ' ')) {
                fileNormals.push_back(atof(token.c_str()));
            }
        }
        else if (token == "vt") {
            while (getline(sStream, token, ' ')) {
                fileUVs.push_back(atof(token.c_str()));
            }
        }
        else if (token == "f") {
            while (getline(sStream, token, ' ')) {
                istringstream faceStream(token);
                string faceToken;
                int type = 0;
                while (getline(faceStream, faceToken, '/')) {
                    int index = atoi(faceToken.c_str()) - 1;
                    switch (type) {
                        case 0:
                            vertices.push_back(fileVertices[index * 3]);
                            vertices.push_back(fileVertices[(index * 3) + 1]);
                            vertices.push_back(fileVertices[(index * 3) + 2]);
                            break;
                        case 1:
                            uvs.push_back(fileUVs[(index * 2)]);
                            uvs.push_back(1.0f - fileUVs[(index * 2) + 1]);
                            break;
                        case 2:
                            normals.push_back(fileNormals[(index * 3)]);
                            normals.push_back(fileNormals[(index * 3) + 1]);
                            normals.push_back(fileNormals[(index * 3) + 2]);
                            break;
                    }
                    type++;
                }
            }
        }
    }
}

void Mesh::Render(ShaderProgram *program) {
    glVertexAttribPointer(program->positionAttribute, 3, GL_FLOAT, false, 0, vertices.data());
    glEnableVertexAttribArray(program->positionAttribute);
    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, uvs.data());
    glEnableVertexAttribArray(program->texCoordAttribute);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}
