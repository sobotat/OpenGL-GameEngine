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
#include "Shaders/BlinnShader.h"
#include "Shaders/ColorFragmentShader.h"
#include "Shaders/LambertShader.h"
#include "Shaders/PhongShader.h"
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
    Input::getInstance()->addListenerOnKey(this);

    transformKeyListener = make_shared<TransformKeyListener>();
    Input::getInstance()->addListenerOnKey(transformKeyListener.get());
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

    shared_ptr<LambertShader> lambertShader = make_shared<LambertShader>();
    lambertShader->compile();
    shaders.push_back(lambertShader);

    shared_ptr<PhongShader> phongShader = make_shared<PhongShader>();
    phongShader->compile();
    shaders.push_back(phongShader);

    shared_ptr<BlinnShader> blinnShader = make_shared<BlinnShader>();
    blinnShader->compile();
    shaders.push_back(blinnShader);
    
    printf("Shaders Created\n");

    shaderPrograms.insert(make_pair("color", make_shared<ShaderProgram>(vector<shared_ptr<Shader>>{
        colorFragmentShader,
        vertexShader,
    })));
     
    shaderPrograms.insert(make_pair("lambert", make_shared<ShaderProgram>(vector<shared_ptr<Shader>>{
        lambertShader,
        vertexShader,
    })));

    shaderPrograms.insert(make_pair("phong", make_shared<ShaderProgram>(vector<shared_ptr<Shader>>{
        phongShader,
        vertexShader,
    })));

    shaderPrograms.insert(make_pair("blinn", make_shared<ShaderProgram>(vector<shared_ptr<Shader>>{
        blinnShader,
        vertexShader,
    })));
}

void Application::createModels() {
    printf("Creating Models ...\n");

    shared_ptr<SquareMesh> square = make_shared<SquareMesh>();
    meshes.insert(make_pair("square", square));
    shared_ptr<TriangleMesh> triangle = make_shared<TriangleMesh>();
    meshes.insert(make_pair("triangle", triangle));
    shared_ptr<SuziMesh> suzi = make_shared<SuziMesh>();
    meshes.insert(make_pair("suzi", suzi));
    shared_ptr<SuziSmoothMesh> suziSmooth = make_shared<SuziSmoothMesh>();
    meshes.insert(make_pair("suziSmooth", suziSmooth));
    shared_ptr<SphereMesh> sphere = make_shared<SphereMesh>();
    meshes.insert(make_pair("sphere", sphere));

    printf("Models Created\n");
}

void Application::createScenes() {
    printf("Creating Scenes ...\n");
    
    loadSceneA(meshes["square"], meshes["sphere"]);
    loadSceneB(meshes["square"], meshes["sphere"]);
    loadSceneC(meshes["square"], meshes["suzi"], meshes["suziSmooth"], meshes["sphere"]);

    notifyActiveSceneChanged();
    
    printf("Scenes Created\n");
}

void Application::run() {
    printf("Running ...\n");
    while (!glfwWindowShouldClose(Screen::getInstance()->getWindow())) {
        getScene()->draw();
    }

    onExit();
    
    glfwDestroyWindow(Screen::getInstance()->getWindow());
    glfwTerminate();
}

shared_ptr<Scene> Application::getScene() {
    return scenes.at(activeScene);
}

shared_ptr<Camera> Application::getCamera() {
    return this->camera;
}

void Application::onKeyChanged(KeyInput keyInput) {
    if (keyInput.key == GLFW_KEY_TAB && keyInput.action == GLFW_PRESS) {
        if (activeScene + 1 != scenes.size()) activeScene++;    
        else activeScene = 0;
        notifyActiveSceneChanged();
    }
}

void Application::addOnActiveSceneChanged(ActiveSceneListener* listener) {
    this->activeSceneListeners.push_back(listener);
}


void Application::onExit() {
    printf("Exiting ...");
}

void Application::loadSceneA(shared_ptr<Mesh> plane, shared_ptr<Mesh> mesh) {
    
    shared_ptr<Scene> scene = make_shared<Scene>();
    
    shared_ptr<Actor> squareActor = make_shared<Actor>(plane.get(), shaderPrograms["color"]);    
    shared_ptr<Actor> sphereActor1  = make_shared<Actor>(mesh.get(), shaderPrograms["blinn"]);

    squareActor
        ->addTransform(make_shared<Rotation>(90.0f, vec3{1, 0, 0}))
        ->addTransform(make_shared<Location>(vec3{0, 0, 1}))        
        ->addTransform(make_shared<Scale>(vec3{4, 4, 4}));
    
    sphereActor1
        ->addTransform(make_shared<Location>(vec3{0, 0, .5}))
        ->addTransform(make_shared<Scale>(vec3{.2, .2, .2}));
    
    scene->addActor(squareActor);
    scene->addActor(sphereActor1);

    scene->addLight(make_shared<Light>(vec3{0, 0, 0}));
    
    scenes.push_back(scene);
}

void Application::loadSceneB(shared_ptr<Mesh> plane, shared_ptr<Mesh> mesh) {
    shared_ptr<Scene> scene = make_shared<Scene>();
    
    shared_ptr<Actor> squareActor = make_shared<Actor>(plane.get(), shaderPrograms["color"]);    
    shared_ptr<Actor> sphereActor1  = make_shared<Actor>(mesh.get(), shaderPrograms["blinn"]);
    shared_ptr<Actor> sphereActor2  = make_shared<Actor>(mesh.get(), shaderPrograms["blinn"]);
    shared_ptr<Actor> sphereActor3  = make_shared<Actor>(mesh.get(), shaderPrograms["blinn"]);
    shared_ptr<Actor> sphereActor4 = make_shared<Actor>(mesh.get(), shaderPrograms["blinn"]);

    squareActor
        ->addTransform(make_shared<Rotation>(90.0f, vec3{1, 0, 0}))
        ->addTransform(make_shared<Location>(vec3{0, 0, 1}))        
        ->addTransform(make_shared<Scale>(vec3{4, 4, 4}));
    
    sphereActor1
        ->addTransform(make_shared<Location>(vec3{0, .5, 0}))
        ->addTransform(make_shared<Scale>(vec3{.2, .2, .2}));
    sphereActor2
        ->addTransform(make_shared<Location>(vec3{0, -.5, 0}))
        ->addTransform(make_shared<Scale>(vec3{.2, .2, .2}));
    sphereActor3
        ->addTransform(make_shared<Location>(vec3{.5, 0, 0}))
        ->addTransform(make_shared<Scale>(vec3{.2, .2, .2}));
    sphereActor4
        ->addTransform(make_shared<Location>(vec3{-.5, 0, 0}))
        ->addTransform(make_shared<Scale>(vec3{.2, .2, .2}));
    
    scene->addActor(squareActor);
    scene->addActor(sphereActor1);
    scene->addActor(sphereActor2);
    scene->addActor(sphereActor3);
    scene->addActor(sphereActor4);

    scene->addLight(make_shared<Light>(vec3{0, 0, 0}, vec4{0, 1, 0, 1}));
    
    scenes.push_back(scene);
}

void Application::loadSceneC(shared_ptr<Mesh> plane, shared_ptr<Mesh> mesh1, shared_ptr<Mesh> mesh2,
    shared_ptr<Mesh> mesh3) {

    shared_ptr<Scene> scene = make_shared<Scene>();
    
    shared_ptr<Actor> squareActor = make_shared<Actor>(plane.get(), shaderPrograms["color"]);    
    shared_ptr<Actor> actor1  = make_shared<Actor>(mesh1.get(), shaderPrograms["blinn"]);
    shared_ptr<Actor> actor2  = make_shared<Actor>(mesh2.get(), shaderPrograms["phong"]);
    shared_ptr<Actor> actor3  = make_shared<Actor>(mesh3.get(), shaderPrograms["lambert"]);

    squareActor
        ->addTransform(make_shared<Rotation>(90.0f, vec3{1, 0, 0}))
        ->addTransform(make_shared<Location>(vec3{0, 0, 1}))        
        ->addTransform(make_shared<Scale>(vec3{4, 4, 4}));
    squareActor->setColor({.2,.2,.2,1});
    
    actor1
        ->addTransform(make_shared<Location>(vec3{0, .5, 0}))
        ->addTransform(make_shared<Scale>(vec3{.2, .2, .2}));
    actor1->setColor({1, 1, 1, 1});
    actor2
        ->addTransform(make_shared<Location>(vec3{0, -.5, 0}))
        ->addTransform(make_shared<Scale>(vec3{.2, .2, .2}));
    actor1->setColor({.2, .2, .2, 1});
    actor3
        ->addTransform(make_shared<Location>(vec3{.5, 0, 0}))
        ->addTransform(make_shared<Scale>(vec3{.2, .2, .2}));
    actor1->setColor({.5, .5, .5, 1});
    
    scene->addActor(squareActor);
    scene->addActor(actor1);
    scene->addActor(actor2);
    scene->addActor(actor3);

    scene->addLight(make_shared<Light>(vec3{0, 0, .5}, vec4{1, 0, 0, 1}));
    
    scenes.push_back(scene);
}

void Application::notifyActiveSceneChanged() {
    for(ActiveSceneListener* listener : activeSceneListeners) {
        listener->onActiveSceneChanged(getScene());
    }
}

Application::~Application() {
    shaderPrograms.clear();
    shaders.clear();
    scenes.clear();
    meshes.clear();    
}
