#include "Application.h"

#include "Screen.h"
#include "GLFWCallbacks/ErrorGLFWCallback.hpp"
#include "Inputs/Input.h"
#include "Meshes/SphereMesh.h"
#include "Meshes/SquareMesh.h"
#include "Meshes\SuziMesh.h"
#include "Meshes/TriangleMesh.h"
#include "Shaders/ColorFragmentShader.h"
#include "Shaders/PositionFragmentShader.h"
#include "Shaders/ShaderProgram.h"
#include "Shaders/VertexShader.h"
#include "Transformations/Location.h"
#include "Transformations/Rotation.h"
#include "Transformations/Scale.h"
#include "Transformations/TransformComposite.h"

Application* Application::instance_ = new Application();

Application* Application::getInstance() {
    return instance_;
}

void Application::init() {    
    printf("Init\n");
    
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }
    
    Screen::getInstance()->init();

    glewExperimental = GL_TRUE;
    glewInit();

    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);   

    Input::getInstance()->init(Screen::getInstance()->getWindow());
    scene = new Scene();
}

void Application::createShaders() {
    printf("Creating Shaders ...\n");
    PositionFragmentShader* positionFragmentShader = new PositionFragmentShader();
    positionFragmentShader->compile();
    shaders.push_back(positionFragmentShader);

    ColorFragmentShader* colorFragmentShader = new ColorFragmentShader();
    colorFragmentShader->compile();
    shaders.push_back(colorFragmentShader);
    
    VertexShader* vertexShader = new VertexShader();
    vertexShader->compile();
    shaders.push_back(vertexShader);
    printf("Shaders Created\n");
    
    shaderPrograms.push_back(new ShaderProgram({
        positionFragmentShader,
        vertexShader,
    }));

    shaderPrograms.push_back(new ShaderProgram({
        colorFragmentShader,
        vertexShader,
    }));
}

void Application::createModels() {
    printf("Creating Models ...\n");

    SquareMesh* square = new SquareMesh();
    TriangleMesh* triangle = new TriangleMesh();
    SuziMesh* suzi = new SuziMesh();
    SphereMesh* sphere = new SphereMesh(); 

    Actor* squareActor = new Actor(square, shaderPrograms[1]);
    Actor* suziActor1 = new Actor(suzi, shaderPrograms[0]);
    Actor* suziActor2 = new Actor(suzi, shaderPrograms[0]);
    Actor* sphereActor = new Actor(sphere, shaderPrograms[0]);

    squareActor
        ->addTransform(new Location({-.5, 0, 0}))
        ->addTransform(new Scale({.3, .3, .3}));
    suziActor1
        ->addTransform(new Location({0, .5, 0}))
        ->addTransform(new Scale({.2, .2, .2}));
    suziActor2
        ->addTransform(new Location({0, -.5, 0}))
        ->addTransform(new Scale({.2, .2, .2}));
    sphereActor
        ->addTransform(new Location({.5, 0, 0}))
        ->addTransform(new Scale({.2, .2, .2}));
    
    scene->addActor(squareActor);
    scene->addActor(suziActor1);
    scene->addActor(suziActor2);
    scene->addActor(sphereActor);

    printf("Models Created\n");
}

void Application::run() {
    printf("Running ...\n");
    while (!glfwWindowShouldClose(Screen::getInstance()->getWindow())) {
        scene->draw();
    }

    onExit();
    
    glfwDestroyWindow(Screen::getInstance()->getWindow());
    glfwTerminate();
}


void Application::onExit() {
    printf("Exiting ...");
}

Application::~Application() {
    for(ShaderProgram* program : shaderPrograms) {
        delete program;
    }
    shaderPrograms.clear();
    for(Shader* shader : shaders) {
        delete shader;
    }
    shaders.clear();
    delete scene;
}
