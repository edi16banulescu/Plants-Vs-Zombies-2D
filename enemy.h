#pragma once
#include "utils/glm_utils.h"
#include "components/simple_scene.h"
#include "lab_m1/lab3/object2D.h"
#include <vector>

namespace m1
{
    class Enemy : public gfxc::SimpleScene
    {
    public:
        glm::vec3 corner;
        glm::vec3 color1;
        glm::vec3 color2;
        int numPoints;
        float radius1;
        float radius2;
        std::string name;
        glm::mat3 modelMatrix;
        float translateX;
        int id;
        int health;
        float cx;
        float cy;
        float scaleX;
        float scaleY;
        bool isDead = false;
        Enemy(
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
            glm::mat3 modelMatrix);
    };
}
