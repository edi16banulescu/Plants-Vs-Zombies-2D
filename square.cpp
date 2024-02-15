#pragma once
#include "square.h"

namespace m1
{
	Square::Square(
		std::string name,
		std::unordered_map<std::string, Mesh*>* meshes,
		glm::vec3 corner,
		glm::vec3 color,
		float squareSide,
		glm::mat3 modelMatrix,
		bool filled)
	{
		this->corner = corner;
		this->color = color;
		this->squareSide = squareSide;
		this->name = name;
		this->modelMatrix = modelMatrix;
		this->filled = filled;

		isOcupied = false;
		cx = corner.x + squareSide / 2;
		cy = corner.y + squareSide / 2;

		Mesh* square = object2D::CreateSquare(name, corner, squareSide, color, filled);
		(*meshes)[name] = square;
	}
}

