#pragma once
#include "enemy.h"

namespace m1 {
    Enemy::Enemy(
        std::string name,
        int id,
        std::unordered_map<std::string, Mesh*>* meshes,
        glm::vec3 corner,
        glm::vec3 color1,
        glm::vec3 color2,
        float cx,
        float cy,
        int numPoints,
        float radius1,
        float radius2,
        glm::mat3 modelMatrix)
    {
        this->corner = corner;
        this->color1 = color1;
        this->color2 = color2;
        this->name = name;
        this->modelMatrix = modelMatrix;
        this->numPoints = numPoints;
        this->radius1 = radius1;
        this->radius2 = radius2;
        this->id = id;

        this->translateX = 0;
        this->health = 3;
        this->cx = cx;
        this->cy = cy;
        this->scaleX = 1;
        this->scaleY = 1;
        this->isDead = false;

        std::vector<VertexFormat> vertices_hexagon;

        // Calculate the vertices of the hexagon

        for (int i = 0; i < numPoints * 2; i++) {
            float angle = glm::radians(360.0f / (numPoints * 2) * i);
            float radius = (i % 2 == 0) ? radius1 : radius2;

            float x = radius * cos(angle);
            float y = radius * sin(angle);

            vertices_hexagon.push_back(VertexFormat(glm::vec3(x, y, 2), color1));
        }

        vertices_hexagon.push_back(VertexFormat(glm::vec3(0.0f, 0.0f, 2), color1));

        // Define the indices to connect the vertices
        std::vector<unsigned int> indices_hexagon;
        for (int i = 0; i < numPoints * 2; i++) {
            indices_hexagon.push_back(numPoints);
            indices_hexagon.push_back(i);
            indices_hexagon.push_back((i + 1) % (numPoints * 2));
        }

        int numPoints2 = numPoints;
        float radius12 = radius1 + 10;
        float radius22 = radius2 + 10;

        for (int i = 0; i < numPoints2 * 2; i++) {
            float angle = glm::radians(360.0f / (numPoints2 * 2) * i);
            float radius = (i % 2 == 0) ? radius12 : radius22;

            float x = radius * cos(angle);
            float y = radius * sin(angle);

            vertices_hexagon.push_back(VertexFormat(glm::vec3(x, y, 1), color2));
        }

        for (int i = 6; i < numPoints2 * 2 * 2; i++) {
            indices_hexagon.push_back(numPoints2 * 2 + 1);
            indices_hexagon.push_back(i);
            indices_hexagon.push_back((i + 1) % (numPoints2 * 2 * 2 + 2));
        }

        // Actually create the mesh from the data
        (*meshes)[name] = new Mesh(name);
        (*meshes)[name]->InitFromData(vertices_hexagon, indices_hexagon);
    };
}