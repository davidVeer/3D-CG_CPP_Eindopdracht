#include "Headers/BasicObject.h"
#include "../Services/Headers/Textureloader.h"


BasicObject::BasicObject() {
}

std::vector<tigl::Vertex> BasicObject::generateSquareFace(glm::vec3 topLeft, glm::vec3 bottomLeft, glm::vec3 topRight, glm::vec3 bottomRight, glm::vec4 facecolor) {
    std::vector<tigl::Vertex> faceVerteces = {
    tigl::Vertex::PTC(topLeft,    glm::vec2(0.0f, 1.0f),  facecolor),
    tigl::Vertex::PTC(bottomLeft, glm::vec2(0.0f, 0.0f),  facecolor),
    tigl::Vertex::PTC(bottomRight,glm::vec2(1.0f, 0.0f),  facecolor),
        
    tigl::Vertex::PTC(topRight,   glm::vec2(1.0f, 1.0f),  facecolor),
    tigl::Vertex::PTC(bottomRight,glm::vec2(1.0f, 0.0f),  facecolor),
    tigl::Vertex::PTC(topLeft,    glm::vec2(0.0f, 1.0f),  facecolor)
    };
    return faceVerteces;
}

void BasicObject::GenerateHexahedron(glm::vec3 vertices[8],const glm::vec4 colors[6], const char* textureFilePath)
{
    shape.textureFilePath = textureFilePath;

    std::vector<tigl::Vertex> frontFace = generateSquareFace(vertices[0], vertices[2], vertices[1], vertices[3], colors[0]);
    std::vector<tigl::Vertex> backFace = generateSquareFace(vertices[5], vertices[7], vertices[4], vertices[6], colors[0]);
    std::vector<tigl::Vertex> leftFace = generateSquareFace(vertices[1], vertices[3], vertices[5], vertices[7], colors[0]);
    std::vector<tigl::Vertex> rightFace = generateSquareFace(vertices[4], vertices[6], vertices[0], vertices[2], colors[0]);
    std::vector<tigl::Vertex> topFace = generateSquareFace(vertices[4], vertices[0], vertices[5], vertices[1], colors[0]);
    std::vector<tigl::Vertex> bottomFace = generateSquareFace(vertices[2], vertices[6], vertices[3], vertices[7], colors[0]);
    shape.vertices.insert(shape.vertices.end(),frontFace.begin(), frontFace.end());
    shape.vertices.insert(shape.vertices.end(), backFace.begin(), backFace.end());
    shape.vertices.insert(shape.vertices.end(), leftFace.begin(), leftFace.end());
    shape.vertices.insert(shape.vertices.end(), rightFace.begin(), rightFace.end());
    shape.vertices.insert(shape.vertices.end(), topFace.begin(), topFace.end());
    shape.vertices.insert(shape.vertices.end(), bottomFace.begin(), bottomFace.end());
}

void BasicObject::draw() {
    loadImage(shape.textureFilePath);
    tigl::shader->enableTexture(true);
    tigl::begin(GL_TRIANGLES);
    for (const tigl::Vertex& v : shape.vertices) {
        tigl::addVertex(v);
    }
    tigl::end();
}