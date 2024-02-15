#pragma once
#include "utils/glm_utils.h"
#include "components/simple_scene.h"
#include "lab_m1/lab3/object2D.h"
#include <vector>

#define shootRatioGlobal 2.5

namespace m1
{
	class Turret : public gfxc::SimpleScene
	{
	public:
		glm::vec3 corner;
		glm::vec3 color;
		float rombSide;
		std::string name;
		glm::mat3 modelMatrix;
		bool canShoot;
		float cx;
		float cy;
		float shootRatio;
		int starsCost;
		bool isMoved;
		bool isSelected;
		float scaleX;
		float scaleY;
		bool isDead;
		Turret(
			std::string name,
			std::unordered_map<std::string, Mesh*>* meshes,
			glm::vec3 corner,
			glm::vec3 color,
			float rombSide,
			int starsCost,
			glm::mat3 modelMatrix);
	};
}