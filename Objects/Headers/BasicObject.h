#pragma once
#include "IDrawable.h"
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "../../tigl.h"

struct BasicShape {
	std::vector<tigl::Vertex> vertices;
	const char* textureFilePath;
};


class BasicObject : public IDrawable {
	BasicShape shape;

	std::vector<tigl::Vertex> generateSquareFace(glm::vec3 topLeft, glm::vec3 bottomLeft, glm::vec3 topRight, glm::vec3 bottomRight, glm::vec4 facecolor);
public: 
	BasicObject();
	~BasicObject() = default;
	
	void GenerateHexahedron(
		glm::vec3 vertices[8],
		const glm::vec4 colors[6] = nullptr,
		const char* textureFilePath = ""
	);

	void draw() override;
};
