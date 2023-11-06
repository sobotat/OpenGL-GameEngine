#include "Application.h"

#include <vcruntime_typeinfo.h>

#include "Screen.h"
#include "GLFWCallbacks/ErrorGLFWCallback.hpp"
#include "Inputs/Input.h"
#include "Inputs/Listeners/TransformKeyListener.h"
#include "Lights/DirectionalLight.h"
#include "Lights/PointLight.h"
#include "Lights/SpotLight.h"
#include "Meshes/BushesMesh.h"
#include "Meshes/GiftMesh.h"
#include "Meshes/SphereMesh.h"
#include "Meshes/SquareMesh.h"
#include "Meshes/SuziSmoothMesh.h"
#include "Meshes/TreeMesh.h"
#include "Meshes\SuziMesh.h"
#include "Meshes/TriangleMesh.h"
#include "Shaders/BlinnShader.h"
#include "Shaders/BlinnUnlimitedShader.h"
#include "Shaders/ColorFragmentShader.h"
#include "Shaders/LambertShader.h"
#include "Shaders/PhongShader.h"
#include "Shaders/PhongUnlimitedShader.h"
#include "Shaders/PositionFragmentShader.h"
#include "Shaders/ShaderProgram.h"
#include "Shaders/VertexShader.h"
#include "Transformations/ContinuousRotation.h"
#include "Transformations/ContinuousRotationAroundAxis.h"
#include "Transformations/Location.h"
#include "Transformations/Rotation.h"
#include "Transformations/RotationAroundAxis.h"
#include "Transformations/Scale.h"
#include "Utils/UtilClass.h"

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
    cameraLight = make_shared<SpotLight>();
    cameraLight->setOn(false);
    cameraLight->setColor({.7, .7, 1, 1});
    cameraLight->setAngle(15);
    cameraLight->setFadeStartAngle(10);
    cameraLight->setDimmingFactor(0.05f);
    cameraLight->setDiffuseFactor(.9f);

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

    shared_ptr<PhongUnlimitedShader> phongUnlimitedShader = make_shared<PhongUnlimitedShader>();
    phongUnlimitedShader->compile();
    shaders.push_back(phongUnlimitedShader);

    shared_ptr<BlinnUnlimitedShader> blinnUnlimitedShader = make_shared<BlinnUnlimitedShader>();
    blinnUnlimitedShader->compile();
    shaders.push_back(blinnUnlimitedShader);
    
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

    shaderPrograms.insert(make_pair("phong-unlimited", make_shared<ShaderProgram>(vector<shared_ptr<Shader>>{
        phongUnlimitedShader,
        vertexShader,
    })));

    shaderPrograms.insert(make_pair("blinn-unlimited", make_shared<ShaderProgram>(vector<shared_ptr<Shader>>{
        blinnUnlimitedShader,
        vertexShader,
    })));
}

void Application::createMaterials() {
    materials.insert(make_pair("red-shiny", make_shared<Material>(vec4{1, 0, 0, 1}, 48, 1)));
    materials.insert(make_pair("blue-shiny", make_shared<Material>(vec4{.2, .2, 1, 1}, 48, 1)));
    materials.insert(make_pair("red-mat", make_shared<Material>(vec4{1, 0, 0, 1}, 8, 1)));
    materials.insert(make_pair("red-ultra-mat", make_shared<Material>(vec4{1, 0, 0, 1}, 1, 1)));
    materials.insert(make_pair("blue-mat", make_shared<Material>(vec4{.2, .2, 1, 1}, 8, 1)));
    materials.insert(make_pair("light-blue-mat", make_shared<Material>(vec4{0.5569, 0.7804, 0.8235, 1}, 8, 1)));
    materials.insert(make_pair("yellow-shiny", make_shared<Material>(vec4{1, 1, 0, 1}, 48, 1)));
    materials.insert(make_pair("yellow-mat", make_shared<Material>(vec4{1, 1, 0, 1}, 8, 1)));
    materials.insert(make_pair("green-mat", make_shared<Material>(vec4{0.6627, 0.8118, 0.3294, 1}, 8, 1)));
    materials.insert(make_pair("green-shiny", make_shared<Material>(vec4{0.6627, 0.8118, 0.3294, 1}, 48, 1)));
    materials.insert(make_pair("dark-green-mat", make_shared<Material>(vec4{0.6588, 0.7725, 0.2706, 1}, 8, 1)));
    materials.insert(make_pair("grey-shiny", make_shared<Material>(vec4{0.5, 0.5, 0.5, 1}, 48, 1)));
    materials.insert(make_pair("grey-mat", make_shared<Material>(vec4{0.5, 0.5, 0.5, 1}, 8, 1)));
    materials.insert(make_pair("brown-mat", make_shared<Material>(vec4{0.4980, 0.2745, 0.1020, 1}, 8, 1)));
    materials.insert(make_pair("dark-red-mat", make_shared<Material>(vec4{0.4588, 0.1020, 0.0706, 1}, 8, 1)));
    materials.insert(make_pair("light-blue-mat", make_shared<Material>(vec4{0.5, 0.5765, 1, 1}, 8, 1)));
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
    shared_ptr<TreeMesh> tree = make_shared<TreeMesh>();
    meshes.insert(make_pair("tree", tree));
    shared_ptr<BushesMesh> bushes = make_shared<BushesMesh>();
    meshes.insert(make_pair("bushes", bushes));
    shared_ptr<GiftMesh> gift = make_shared<GiftMesh>();
    meshes.insert(make_pair("gift", gift));

    printf("Models Created\n");
}

void Application::createScenes() {
    printf("Creating Scenes ...\n");
    
    loadSceneA();
    loadSceneB();
    loadSceneC();
    loadSceneD();
    loadSceneE();
    loadSceneF();

    if (cameraLight) {
        for (shared_ptr<Scene> scenes : scenes) {
            scenes->addLight(cameraLight);
        }

        camera->attachLight(cameraLight);
    }
    
    notifyActiveSceneChanged();
    shared_ptr<Scene> activeScene = getScene();
    for(auto shaderProgram : shaderPrograms) {
        activeScene->addLightChangedInSceneChanged(shaderProgram.second);
    }
    
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

vector<shared_ptr<Scene>> Application::getAllScenes() {
    return this->scenes;
}

shared_ptr<Camera> Application::getCamera() {
    return this->camera;
}

shared_ptr<Mesh> Application::getMesh(string name) {
    return meshes[name];
}

void Application::onKeyChanged(KeyInput keyInput) {
    if (keyInput.key == GLFW_KEY_TAB && keyInput.action == GLFW_PRESS) {
        shared_ptr<Scene> originalScene = getScene();
        originalScene->clearLightChangedInSceneChanged();
        
        if (activeScene + 1 != scenes.size()) activeScene++;    
        else activeScene = 0;
        notifyActiveSceneChanged();

        shared_ptr<Scene> activeScene = getScene();
        for(auto shaderProgram : shaderPrograms) {
            activeScene->addLightChangedInSceneChanged(shaderProgram.second);
        }
    }
}

void Application::addOnActiveSceneChanged(ActiveSceneListener* listener) {
    this->activeSceneListeners.push_back(listener);
}


void Application::onExit() {
    printf("Exiting ...");
}

void Application::loadSceneA() {
    shared_ptr<Scene> scene = make_shared<Scene>();    
    shared_ptr<Actor> sphereActor1  = make_shared<Actor>(meshes["sphere"].get(), shaderPrograms["phong"], materials["red-mat"]);
    shared_ptr<Actor> sphereActor2  = make_shared<Actor>(meshes["sphere"].get(), shaderPrograms["phong"], materials["blue-mat"]);
    shared_ptr<Actor> sphereActor3  = make_shared<Actor>(meshes["sphere"].get(), shaderPrograms["phong"], materials["blue-mat"]);
    shared_ptr<Actor> sphereActor4 = make_shared<Actor>(meshes["sphere"].get(), shaderPrograms["phong"], materials["red-mat"]);
    shared_ptr<Actor> sphereActor5 = make_shared<Actor>(meshes["sphere"].get(), shaderPrograms["phong"], materials["grey-shiny"]);
    
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
    sphereActor5
        ->addTransform(make_shared<Location>(vec3{0, 0, -4}))
        ->addTransform(make_shared<Scale>(vec3{2, 2, 2}));
    
    scene->addActor(sphereActor1);
    scene->addActor(sphereActor2);
    scene->addActor(sphereActor3);
    scene->addActor(sphereActor4);
    scene->addActor(sphereActor5);

    shared_ptr<PointLight> light1 = make_shared<PointLight>();
    light1->setPosition({0, 0, -1});
    light1->setColor({.1, .1, 1, 1});
    light1->setIntensity(0.5f);
    light1->setDimmingFactor(.005f);
    scene->addLight(light1);
    
    shared_ptr<PointLight> light2 = make_shared<PointLight>();
    light2->setPosition({0, 0, 1});
    light2->setColor({1, .1, .1, 1});
    light2->setIntensity(0.5);
    light2->setDimmingFactor(.005f);
    scene->addLight(light2);
    
    shared_ptr<DirectionalLight> light3 = make_shared<DirectionalLight>();
    light3->setColor({.3, .3, .3, 1});
    light3->setDirection({0, 1, 1});
    light3->setColor({.1, .1, .7, 1});
    scene->addLight(light3);
    
    shared_ptr<SpotLight> light4 = make_shared<SpotLight>();
    light4->setPosition({0, 0, 1});
    light4->setDirection({.3, .3, -1});
    scene->addLight(light4);
    
    scenes.push_back(scene);
}

void Application::loadSceneB() {
    shared_ptr<Scene> scene = make_shared<Scene>();
        
    shared_ptr<Actor> sun  = make_shared<Actor>(meshes["sphere"].get(), shaderPrograms["color"], materials["yellow-mat"]);
    shared_ptr<Actor> mercury  = make_shared<Actor>(meshes["sphere"].get(), shaderPrograms["blinn"], materials["grey-mat"]);
    shared_ptr<Actor> venus  = make_shared<Actor>(meshes["sphere"].get(), shaderPrograms["blinn"], materials["brown-mat"]);
    shared_ptr<Actor> earth  = make_shared<Actor>(meshes["sphere"].get(), shaderPrograms["blinn"], materials["green-mat"]);
    shared_ptr<Actor> moon  = make_shared<Actor>(meshes["sphere"].get(), shaderPrograms["blinn"], materials["grey-mat"]);
    shared_ptr<Actor> mars  = make_shared<Actor>(meshes["sphere"].get(), shaderPrograms["blinn"], materials["dark-red-mat"]);
    shared_ptr<Actor> jupiter  = make_shared<Actor>(meshes["sphere"].get(), shaderPrograms["blinn"], materials["brown-mat"]);
    shared_ptr<Actor> saturn  = make_shared<Actor>(meshes["sphere"].get(), shaderPrograms["blinn"], materials["dark-red-mat"]);
    shared_ptr<Actor> uranus  = make_shared<Actor>(meshes["sphere"].get(), shaderPrograms["blinn"], materials["blue-mat"]);
    shared_ptr<Actor> neptune  = make_shared<Actor>(meshes["sphere"].get(), shaderPrograms["blinn"], materials["light-blue-mat"]);
    
    sun
        ->addTransform(make_shared<Location>(vec3{0, 0, 0}));
    mercury
        ->addTransform(make_shared<Location>(vec3{-2, 0, 0}))
        ->addTransform(make_shared<Scale>(vec3{.1, .1, .1}));
    mercury->addTransform(make_shared<ContinuousRotationAroundAxis>( 0.0f, vec3{0, 1, 0}, mercury->getActorMatrix(), sun, 47.f));
    venus
        ->addTransform(make_shared<Location>(vec3{-4, 0, 0}))
        ->addTransform(make_shared<Scale>(vec3{.3, .3, .3}));
    venus->addTransform(make_shared<ContinuousRotationAroundAxis>( 0.0f, vec3{0, 1, 0}, venus->getActorMatrix(), sun, 35.f));
    earth
        ->addTransform(make_shared<Location>(vec3{-6, 0, 0}))
        ->addTransform(make_shared<Scale>(vec3{.3, .3, .3}));
    earth->addTransform(make_shared<ContinuousRotationAroundAxis>( 0.0f, vec3{0, 1, 0}, earth->getActorMatrix(), sun, 29.f));
    moon
        ->addTransform(make_shared<Location>(vec3{-6.5, 0, -.5}))
        ->addTransform(make_shared<Scale>(vec3{.05, .05, .05}));
    moon->addTransform(make_shared<ContinuousRotationAroundAxis>( 0.0f, vec3{0, 1, 0}, moon->getActorMatrix(), earth, -100.f));
    mars
        ->addTransform(make_shared<Location>(vec3{-8, 0, 0}))
        ->addTransform(make_shared<Scale>(vec3{.2, .2, .2}));
    mars->addTransform(make_shared<ContinuousRotationAroundAxis>( 0.0f, vec3{0, 1, 0}, mars->getActorMatrix(), sun, 24.f));
    jupiter
        ->addTransform(make_shared<Location>(vec3{-11, 0, 0}))
        ->addTransform(make_shared<Scale>(vec3{.8, .8, .8}));
    jupiter->addTransform(make_shared<ContinuousRotationAroundAxis>( 0.0f, vec3{0, 1, 0}, jupiter->getActorMatrix(), sun, 13.f));
    saturn
        ->addTransform(make_shared<Location>(vec3{-14, 0, 0}))
        ->addTransform(make_shared<Scale>(vec3{.45, .45, .45}));
    saturn->addTransform(make_shared<ContinuousRotationAroundAxis>( 0.0f, vec3{0, 1, 0}, saturn->getActorMatrix(), sun, 9.f));
    uranus
        ->addTransform(make_shared<Location>(vec3{-16, 0, 0}))
        ->addTransform(make_shared<Scale>(vec3{.2, .2, .2}));
    uranus->addTransform(make_shared<ContinuousRotationAroundAxis>( 0.0f, vec3{0, 1, 0}, uranus->getActorMatrix(), sun, 7.f));
    neptune
        ->addTransform(make_shared<Location>(vec3{-18, 0, 0}))
        ->addTransform(make_shared<Scale>(vec3{.3, .3, .3}));
    neptune->addTransform(make_shared<ContinuousRotationAroundAxis>( 0.0f, vec3{0, 1, 0}, neptune->getActorMatrix(), sun, 5.f));
    
    scene->addActor(sun);
    scene->addActor(mercury);
    scene->addActor(venus);
    scene->addActor(earth);
    scene->addActor(moon);
    scene->addActor(mars);
    scene->addActor(jupiter);
    scene->addActor(saturn);
    scene->addActor(uranus);
    scene->addActor(neptune);
    
    shared_ptr<PointLight> light1 = make_shared<PointLight>();
    light1->setColor({.7, .7, .5, 1});
    light1->setDimmingFactor(.001f);
    scene->addLight(light1);
    
    scenes.push_back(scene);
}

void Application::loadSceneC() {
    shared_ptr<Scene> scene = make_shared<Scene>();    
    shared_ptr<Actor> sphereActor1  = make_shared<Actor>(meshes["sphere"].get(), shaderPrograms["phong"], materials["red-ultra-mat"]);
    
    sphereActor1
        ->addTransform(make_shared<Location>(vec3{0, 0, 0}))
        ->addTransform(make_shared<Scale>(vec3{.6, .6, .6}));
    
    scene->addActor(sphereActor1);
    
    shared_ptr<PointLight> light1 = make_shared<PointLight>();
    light1->setPosition({0, 0, 1});
    scene->addLight(light1);
    
    scenes.push_back(scene);
}

void Application::loadSceneD() {
    shared_ptr<Scene> scene = make_shared<Scene>();    
    shared_ptr<Actor> sphereActor1  = make_shared<Actor>(meshes["sphere"].get(), shaderPrograms["phong-unlimited"], materials["red-ultra-mat"]);
    
    sphereActor1
        ->addTransform(make_shared<Location>(vec3{0, 0, 0}))
        ->addTransform(make_shared<Scale>(vec3{.6, .6, .6}));
    
    scene->addActor(sphereActor1);
    
    shared_ptr<PointLight> light1 = make_shared<PointLight>();
    light1->setPosition({0, 0, -1});
    scene->addLight(light1);
    
    scenes.push_back(scene);
}

void Application::loadSceneE() {

    shared_ptr<Scene> scene = make_shared<Scene>();
    
    shared_ptr<Actor> squareActor = make_shared<Actor>(meshes["square"].get(), shaderPrograms["color"], materials["blue-shiny"]);    
    shared_ptr<Actor> actor1  = make_shared<Actor>(meshes["suzi"].get(), shaderPrograms["lambert"], materials["red-shiny"]);
    shared_ptr<Actor> actor2  = make_shared<Actor>(meshes["suziSmooth"].get(), shaderPrograms["lambert"], materials["red-shiny"]);
    shared_ptr<Actor> actor3  = make_shared<Actor>(meshes["sphere"].get(), shaderPrograms["lambert"], materials["red-shiny"]);

    squareActor
        ->addTransform(make_shared<Rotation>(90.0f, vec3{1, 0, 0}))
        ->addTransform(make_shared<Location>(vec3{0, 0, 1}))        
        ->addTransform(make_shared<Scale>(vec3{4, 4, 4}));
    
    actor1
        ->addTransform(make_shared<Location>(vec3{0, .5, 0}))
        ->addTransform(make_shared<Scale>(vec3{.2, .2, .2}))
        ->addTransform(make_shared<ContinuousRotation>(0, vec3{0, 1, 0}, 1.5));
    actor2
        ->addTransform(make_shared<Location>(vec3{0, -.5, 0}))
        ->addTransform(make_shared<Scale>(vec3{.2, .2, .2}))
        ->addTransform(make_shared<ContinuousRotation>(0, vec3{0, 1, 0}, -1.5));
    actor3
        ->addTransform(make_shared<Location>(vec3{.5, 0, 0}))
        ->addTransform(make_shared<Scale>(vec3{.2, .2, .2}));
    
    scene->addActor(squareActor);
    scene->addActor(actor1);
    scene->addActor(actor2);
    scene->addActor(actor3);
    
    shared_ptr<PointLight> light1 = make_shared<PointLight>();
    light1->setPosition({0, 0, .5});
    light1->setColor({1, .5, .5, 1});
    scene->addLight(light1);
    
    scenes.push_back(scene);
}

void Application::loadSceneF() {
    shared_ptr<Scene> scene = make_shared<Scene>();
    
    shared_ptr<Actor> floor = make_shared<Actor>(meshes["square"].get(), shaderPrograms["phong"], materials["dark-green-mat"]);
    shared_ptr<Actor> skybox = make_shared<Actor>(meshes["sphere"].get(), shaderPrograms["color"], materials["light-blue-mat"]);
    shared_ptr<Actor> gift = make_shared<Actor>(meshes["gift"].get(), shaderPrograms["phong"], materials["red-shiny"]);

    int countOfTrees = 150;
    for(int i = 0; i < countOfTrees; i++) {
        shared_ptr<Actor> tree = make_shared<Actor>(meshes["tree"].get(), shaderPrograms["blinn"], materials["green-shiny"]);
        float scale = UtilClass::randomFloatRange(.4f, .6f);
        tree
            ->addTransform(make_shared<Location>(vec3{UtilClass::randomFloatRange(-20, 20), 0, UtilClass::randomFloatRange(-20, 20)}))
            ->addTransform(make_shared<Rotation>(UtilClass::randomFloatRange(0, 360), vec3{0, 1, 0}))
            ->addTransform(make_shared<Scale>(vec3{scale,  scale, scale}));

        scene->addActor(tree);
    }

    int countOfBushes = 1000;
    for(int i = 0; i < countOfBushes; i++) {
        shared_ptr<Actor> bush = make_shared<Actor>(meshes["bushes"].get(), shaderPrograms["blinn"], materials["green-shiny"]);
        float scale = UtilClass::randomFloatRange(0.3f, 0.5f);
        bush
            ->addTransform(make_shared<Location>(vec3{UtilClass::randomFloatRange(-20, 20), 0, UtilClass::randomFloatRange(-20, 20)}))
            ->addTransform(make_shared<Rotation>(UtilClass::randomFloatRange(0, 360), vec3{0, 1, 0}))
            ->addTransform(make_shared<Scale>(vec3{scale,  scale, scale}));

        scene->addActor(bush);
    }
    
    floor
        ->addTransform(make_shared<Location>(vec3{0, 0, 1}))
        ->addTransform(make_shared<Rotation>(-90.0f, vec3{1, 0, 0}))                
        ->addTransform(make_shared<Scale>(vec3{200, 200, 200}));

    skybox->addTransform(make_shared<Scale>(vec3{20, 20, 20}));
    
    gift
        ->addTransform(make_shared<Location>(vec3{0, 0, 1}));
    
    scene->addActor(floor);
    scene->addActor(skybox);
    scene->addActor(gift);

    
    shared_ptr<DirectionalLight> light1 = make_shared<DirectionalLight>();
    light1->setDirection({1, 1, 0});
    scene->addLight(light1);

    // shared_ptr<PointLight> light2 = make_shared<PointLight>();
    // light2->setDimmingFactor(0);
    // light2->setPosition({0, 2, 0});
    // scene->addLight(light2);
    
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
