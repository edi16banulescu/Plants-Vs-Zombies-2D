#pragma once
#include "utils/glm_utils.h"
#include "components/simple_scene.h"
#include "object2D.h"

namespace m1
{
	class Square : public gfxc::SimpleScene
	{
	public:
		glm::vec3 corner;
		glm::vec3 color;
		float squareSide;
		std::string name;
		glm::mat3 modelMatrix;
		float cx;
		float cy;
		bool filled;
		bool isOcupied;
		Square(
			std::string name,
			std::unordered_map<std::string, Mesh*>* meshes,
			glm::vec3 corner,
			glm::vec3 color,
			float squareSide,
			glm::mat3 modelMatrix,
			bool filled);
	};
}

