#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "CameraHandling/Headers/CameraStrategy.h"
#include "CameraHandling/Headers/KeyboardAndMouse_Camera.h"
#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb/stb_image.h"
#include "Objects/Headers/BasicObject.h"

using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;
std::shared_ptr<ICameraStrategy> cameraControl;
float rotationY;

void init();
void update();
void draw();

int main(void)
{
    if (!glfwInit())
        throw "Could not initialize glwf";
    window = glfwCreateWindow(1400, 800, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw "Could not initialize glwf";
    }
    glfwMakeContextCurrent(window);

    tigl::init();

    init();

    while (!glfwWindowShouldClose(window))
    {
        update();
        draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();


    return 0;
}


void init()
{
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if (key == GLFW_KEY_ESCAPE)
                glfwSetWindowShouldClose(window, true);
        });
    cameraControl = std::make_shared<KeyboardAndMouseCamera>(KeyboardAndMouseCamera(window));
    rotationY = 0.0f;
}


void update()
{
    cameraControl->update(window);
    rotationY += 0.005f;
}

void loadImage() {
    int width, height, bpp;
    unsigned char* imgData = stbi_load("Recources/Bob.png", &width, &height, &bpp, 4);

    glTexImage2D(GL_TEXTURE_2D,
        0, //level
        GL_RGBA, //internal format
        507, //width
        537, //height
        0, //border
        GL_RGBA, //data format
        GL_UNSIGNED_BYTE, //data type
        imgData); //data
    stbi_image_free(imgData);
    stbi_set_flip_vertically_on_load(true);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void draw()
{
    glm::mat4 projectionMatrix, modelMatrix, viewMatrix;
    GLuint textureId;

    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);


    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    projectionMatrix = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 100.0f);

    tigl::shader->setProjectionMatrix(projectionMatrix);
    tigl::shader->setViewMatrix(cameraControl->getMatrix());

    tigl::shader->enableColor(true);
    tigl::shader->enableTexture(false);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    tigl::shader->setModelMatrix(model);
    tigl::begin(GL_TRIANGLES);
    tigl::addVertex(Vertex::PTC(glm::vec3(-10, -1, -10), glm::vec2(0.0f, 0.0f), glm::vec4(1, 0, 0, 1))); //left front
    tigl::addVertex(Vertex::PTC(glm::vec3(-10, -1, 10), glm::vec2(0.0f, 0.0f), glm::vec4(0, 1, 0, 1))); //left behind
    tigl::addVertex(Vertex::PTC(glm::vec3(10, -1, 10), glm::vec2(0.0f, 0.0f), glm::vec4(0, 0, 1, 1))); //right behind

    tigl::addVertex(Vertex::PTC(glm::vec3(-10, -1, -10), glm::vec2(0.0f, 0.0f), glm::vec4(1, 0, 0, 1))); //left front
    tigl::addVertex(Vertex::PTC(glm::vec3(10, -1, -10), glm::vec2(0.0f, 0.0f), glm::vec4(1, 0, 1, 1))); //right front
    tigl::addVertex(Vertex::PTC(glm::vec3(10, -1, 10), glm::vec2(0.0f, 0.0f), glm::vec4(0, 0, 1, 1))); //right behind
    tigl::end();


    loadImage();


    glm::mat4 model2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 5.0f));
    model2 = glm::rotate(model2, rotationY, glm::vec3(0, 1, 0));
    tigl::shader->setModelMatrix(model2);

    tigl::shader->enableTexture(true);
    tigl::shader->enableColor(false);
    glm::vec3 verteces[8] = {
        glm::vec3( 2, 1,-2),
        glm::vec3(-2, 1,-2),
        glm::vec3( 2,-1,-2),
        glm::vec3(-2,-1,-2),
        glm::vec3( 2, 1, 2),
        glm::vec3(-2, 1, 2),
        glm::vec3( 2,-1, 2),
        glm::vec3(-2,-1, 2),
    };

    glm::vec4 colors[6] = {
        glm::vec4(1, 1, 1, 1),
        glm::vec4(1, 1, 1, 1),
        glm::vec4(1, 1, 1, 1),
        glm::vec4(1, 1, 1, 1),
        glm::vec4(1, 1, 1, 1),
        glm::vec4(1, 1, 1, 1)
    };

    BasicObject cube;
    cube.GenerateHexahedron(verteces, colors);
    cube.draw();

   
}