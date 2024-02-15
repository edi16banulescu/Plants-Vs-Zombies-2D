#pragma once
#include "star.h"

namespace m1
{
    Star::Star(
        std::string name,
        std::unordered_map<std::string, Mesh*>* meshes,
        glm::vec3 corner,
        glm::vec3 color,
        float cx,
        float cy,
        int numPoints,
        float radius1,
        float radius2,
        glm::mat3 modelMatrix)
    {
        this->corner = corner;
        this->color = color;
        this->name = name;
        this->modelMatrix = modelMatrix;
        this->numPoints = numPoints;
        this->radius1 = radius1;
        this->radius2 = radius2;
        this->cx = cx;
        this->cy = cy;

        translateX = 0;
        angularStep = 0;

        std::vector<VertexFormat> vertices_star;

        // Calculate the vertices of the star
        for (int i = 0; i < numPoints * 2; i++) {
            float angle = glm::radians(360.0f / (numPoints * 2) * i);
            float radius = (i % 2 == 0) ? radius1 : radius2;

            float x = radius * cos(angle);
            float y = radius * sin(angle);

            vertices_star.push_back(VertexFormat(corner + glm::vec3(x, y, 1), color));
        }

        // Add the center of the star
        vertices_star.push_back(VertexFormat(corner + glm::vec3(0.0f, 0.0f, 1), color));

        // Define the indices to connect the vertices
        std::vector<unsigned int> indices_star;
        for (int i = 0; i < numPoints * 2; i++) {
            indices_star.push_back(numPoints);
            indices_star.push_back(i);
            indices_star.push_back((i + 1) % (numPoints * 2));
        }

        // Actually create the mesh from the data
        (*meshes)[name] = new Mesh(name);
        (*meshes)[name]->InitFromData(vertices_star, indices_star);
    };
}