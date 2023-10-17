#include "Application.h"

#include <vcruntime_typeinfo.h>

#include "Screen.h"
#include "GLFWCallbacks/ErrorGLFWCallback.hpp"
#include "Inputs/Input.h"
#include "Inputs/Listeners/TransformKeyListener.h"
#include "Meshes/SphereMesh.h"
#include "Meshes/SquareMesh.h"
#include "Meshes/SuziSmoothMesh.h"
#include "Meshes\SuziMesh.h"
#include "Meshes/TriangleMesh.h"
#include "Shaders/ColorFragmentShader.h"
#include "Shaders/PositionFragmentShader.h"
#include "Shaders/ShaderProgram.h"
#include "Shaders/VertexShader.h"
#include "Transformations/Location.h"
#include "Transformations/Rotation.h"
#include "Transformations/Scale.h"

shared_ptr<Application> Application::instance_ = make_shared<Application>();

shared_ptr<Application> Application::getInstance() {
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
    camera = make_shared<Camera>();
    camera->initInput();

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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    Input::getInstance()->init(Screen::getInstance()->getWindow());
    scene = make_shared<Scene>();

    Input::getInstance()->addListenerOnKey(make_shared<TransformKeyListener>());
}

void Application::createShaders() {
    printf("Creating Shaders ...\n");
    shared_ptr<PositionFragmentShader> positionFragmentShader = make_shared<PositionFragmentShader>();
    positionFragmentShader->compile();
    shaders.push_back(positionFragmentShader);

    shared_ptr<ColorFragmentShader> colorFragmentShader = make_shared<ColorFragmentShader>();
    colorFragmentShader->compile();
    shaders.push_back(colorFragmentShader);
    
    shared_ptr<VertexShader> vertexShader = make_shared<VertexShader>();
    vertexShader->compile();
    shaders.push_back(vertexShader);
    printf("Shaders Created\n");

    shared_ptr<ShaderProgram> sharedProgram1 = make_shared<ShaderProgram>(vector<shared_ptr<Shader>>{
        positionFragmentShader,
        vertexShader,
    });
    sharedProgram1->initCameraListener();
    shaderPrograms.push_back(sharedProgram1);

    shared_ptr<ShaderProgram> shaderProgram2 = make_shared<ShaderProgram>(vector<shared_ptr<Shader>>{
        colorFragmentShader,
        vertexShader,
    });
    shaderProgram2->initCameraListener();
    shaderPrograms.push_back(shaderProgram2);
}

void Application::createModels() {
    printf("Creating Models ...\n");

    SquareMesh* square = new SquareMesh();
    TriangleMesh* triangle = new TriangleMesh();
    SuziMesh* suzi = new SuziMesh();
    SuziSmoothMesh* suziSmooth = new SuziSmoothMesh();
    SphereMesh* sphere = new SphereMesh(); 

    shared_ptr<Actor> squareActor = make_shared<Actor>(square, shaderPrograms[1]);
    shared_ptr<Actor> suziActor1  = make_shared<Actor>(suzi, shaderPrograms[0]);
    shared_ptr<Actor> suziActor2  = make_shared<Actor>(suziSmooth, shaderPrograms[0]);
    shared_ptr<Actor> sphereActor = make_shared<Actor>(sphere, shaderPrograms[0]);

    squareActor
        ->addTransform(make_shared<Rotation>(90.0f, vec3{1, 0, 0}))
        ->addTransform(make_shared<Location>(vec3{0, 0, 1}))        
        ->addTransform(make_shared<Scale>(vec3{4, 4, 4}));
    suziActor1
        ->addTransform(make_shared<Location>(vec3{0, .5, 0}))
        ->addTransform(make_shared<Scale>(vec3{.2, .2, .2}));
    suziActor2
        ->addTransform(make_shared<Location>(vec3{0, -.5, 0}))
        ->addTransform(make_shared<Scale>(vec3{.2, .2, .2}));
    sphereActor
        ->addTransform(make_shared<Location>(vec3{.5, 0, 0}))
        ->addTransform(make_shared<Scale>(vec3{.2, .2, .2}));
    
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

shared_ptr<Scene> Application::getScene() {
    return this->scene;
}

shared_ptr<Camera> Application::getCamera() {
    return this->camera;
}


void Application::onExit() {
    printf("Exiting ...");
}

Application::~Application() {
    shaderPrograms.clear();
    shaders.clear();
}
