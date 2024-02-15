#pragma once
#include "utils/glm_utils.h"
#include "components/simple_scene.h"
#include "lab_m1/lab3/object2D.h"
#include <vector>
#include "turret.h"

namespace m1
{
	class Star : public gfxc::SimpleScene
	{
	public:
		glm::vec3 corner;
		glm::vec3 color;
        float armLength;
        float innerArmLength;
        int numPoints;
        float radius1;
        float radius2;
		std::string name;
		glm::mat3 modelMatrix;
        float translateX;
        float angularStep;
        float cx;
        float cy;
        Star(
            std::string name,
            std::unordered_map<std::string, Mesh*>* meshes,
            glm::vec3 corner,
            glm::vec3 color,
            float cx,
            float cy,
            int numPoints,
            float radius1,
            float radius2,
            glm::mat3 modelMatrix);
	};
}