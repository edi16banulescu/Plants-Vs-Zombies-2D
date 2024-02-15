#pragma once
#include "turret.h"

#define shootRatioGlobal 2.5

namespace m1
{
	Turret::Turret(
		std::string name,
		std::unordered_map<std::string, Mesh*>* meshes,
		glm::vec3 corner,
		glm::vec3 color,
		float rombSide,
		int starsCost,
		glm::mat3 modelMatrix)
	{
		this->corner = corner;
		this->color = color;
		this->rombSide = rombSide;
		this->name = name;
		this->modelMatrix = modelMatrix;
		this->starsCost = starsCost;
		this->isSelected = false;
		this->isMoved = false;
		this->isDead = false;
		this->scaleX = 1;
		this->scaleY = 1;
		float smallRectangleSide = 12;
		canShoot = false;
		float cSmallRectangleX = corner.x + smallRectangleSide / 2;
		float cSmallRectangleY = corner.y + smallRectangleSide / 2;
		glm::vec3 cornerSmallRectangle = glm::vec3(cSmallRectangleX, cSmallRectangleY - 11, 0);

		cx = corner.x + rombSide / 2;
		cy = corner.y + rombSide / 2;
		shootRatio = shootRatioGlobal;

		std::vector<VertexFormat> vertices_romb
		{
			VertexFormat(corner + glm::vec3(0, rombSide, 1), color),
			VertexFormat(corner + glm::vec3(-rombSide / 2, 0, 1), color),
			VertexFormat(corner + glm::vec3(0, -rombSide, 1), color),
			VertexFormat(corner + glm::vec3(rombSide / 2, 0, 1), color),

			VertexFormat(cornerSmallRectangle + glm::vec3(0, 0, 1), color),
			VertexFormat(cornerSmallRectangle + glm::vec3(3 * smallRectangleSide, 0, 1), color),
			VertexFormat(cornerSmallRectangle + glm::vec3(3 * smallRectangleSide, smallRectangleSide, 1), color),
			VertexFormat(cornerSmallRectangle + glm::vec3(0, smallRectangleSide, 1), color)
		};

		std::vector<unsigned int> indices_romb =
		{
			0, 1, 2,
			2, 3, 0,

			4, 5, 6,
			4, 7, 6
		};

		// Actually create the mesh from the data
		(*meshes)[name] = new Mesh(name);
		(*meshes)[name]->InitFromData(vertices_romb, indices_romb);
	}
}