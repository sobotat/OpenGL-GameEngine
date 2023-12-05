#include "Application.h"

#include "Screen.h"
#include "GLFWCallbacks/ErrorGLFWCallback.hpp"
#include "Inputs/Input.h"
#include "Inputs/Listeners/TransformKeyListener.h"
#include "Lights/DirectionalLight.h"
#include "Lights/PointLight.h"
#include "Lights/SpotLight.h"
#include "Meshes/BushesMesh.h"
#include "Meshes/ContainerLargeMesh.h"
#include "Meshes/ContainerMediumMesh.h"
#include "Meshes/CubeMesh.h"
#include "Meshes/GiftMesh.h"
#include "Meshes/HouseMesh.h"
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
#include "Meshes/PlaneMesh.h"
#include "Meshes/WallMesh.h"
#include "Shaders\TextureSkyboxShader.h"
#include "Shaders/TextureShader.h"
#include "Shaders\VertexSkyboxShader.h"
#include "Shaders\Materials\Texture\CubeMapTexture.h"
#include "Transformations/ContinuousMoveOnCurve.h"
#include "Transformations/ContinuousMoveOnLine.h"

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
    cameraLight->setColor({.9, .9, 1, 1});
    cameraLight->setAngle(18);
    cameraLight->setFadeStartAngle(12);
    cameraLight->setDimmingFactor(0.001f);
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
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    Input::getInstance()->init(Screen::getInstance()->getWindow());
    Input::getInstance()->addListenerOnKey(this);

    transformKeyListener = make_shared<TransformKeyListener>();
    Input::getInstance()->addListenerOnKey(transformKeyListener.get());
    
    selectListener = make_shared<SelectListener>();
    Input::getInstance()->addListenerOnMouse(selectListener.get());
    Input::getInstance()->addListenerOnCursor(selectListener.get());
    selectListener->addListenerOnSelected(this);


    createShaders();
    createMaterials();
    createModels();
    createScenes();
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

    shared_ptr<TextureShader> textureShader = make_shared<TextureShader>();
    textureShader->compile();
    shaders.push_back(textureShader);

    shared_ptr<TextureSkyboxShader> textureSkyboxShader = make_shared<TextureSkyboxShader>();
    textureSkyboxShader->compile();
    shaders.push_back(textureSkyboxShader);
    
    shared_ptr<VertexSkyboxShader> vertexSkyboxShader = make_shared<VertexSkyboxShader>();
    vertexSkyboxShader->compile();
    shaders.push_back(vertexSkyboxShader);
    
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

    shaderPrograms.insert(make_pair("texture", make_shared<ShaderProgram>(vector<shared_ptr<Shader>>{
        textureShader,
        vertexShader,
    })));

    shaderPrograms.insert(make_pair("texture-skybox", make_shared<ShaderProgram>(vector<shared_ptr<Shader>>{
        textureSkyboxShader,
        vertexSkyboxShader,
    })));
    shaderPrograms["texture-skybox"]->setProperty(0, "textureUnitID");
}

void Application::createMaterials() {
    materials.insert(make_pair("red-shiny", make_shared<Material>(vec4{1, 0.001, 0.001, 1}, 48, 1)));
    materials.insert(make_pair("blue-shiny", make_shared<Material>(vec4{.2, .2, 1, 1}, 48, 1)));
    materials.insert(make_pair("red-mat", make_shared<Material>(vec4{1, 0.001, 0.001, 1}, 8, 1)));
    materials.insert(make_pair("red-ultra-mat", make_shared<Material>(vec4{1, 0, 0, 1}, 1, 1)));
    materials.insert(make_pair("blue-mat", make_shared<Material>(vec4{0.001, 0.749, 1, 1}, 8, 1)));
    materials.insert(make_pair("light-blue-mat", make_shared<Material>(vec4{0.5569, 0.7804, 0.8235, 1}, 8, 1)));
    materials.insert(make_pair("yellow-shiny", make_shared<Material>(vec4{1, 1, 0.001, 1}, 48, 1)));
    materials.insert(make_pair("yellow-mat", make_shared<Material>(vec4{1, 1, 0.001, 1}, 8, 1)));
    materials.insert(make_pair("green-mat", make_shared<Material>(vec4{0.6627, 0.8118, 0.3294, 1}, 8, 1)));
    materials.insert(make_pair("green-shiny", make_shared<Material>(vec4{0.6627, 0.8118, 0.3294, 1}, 48, 1)));
    materials.insert(make_pair("dark-green-mat", make_shared<Material>(vec4{0.6588, 0.7725, 0.2706, 1}, 8, 1)));
    materials.insert(make_pair("grey-shiny", make_shared<Material>(vec4{0.5, 0.5, 0.5, 1}, 48, 1)));
    materials.insert(make_pair("grey-mat", make_shared<Material>(vec4{0.5, 0.5, 0.5, 1}, 8, 1)));
    materials.insert(make_pair("brown-mat", make_shared<Material>(vec4{0.4980, 0.2745, 0.1020, 1}, 8, 1)));
    materials.insert(make_pair("dark-red-mat", make_shared<Material>(vec4{0.4588, 0.1020, 0.0706, 1}, 8, 1)));
    materials.insert(make_pair("light-blue-mat", make_shared<Material>(vec4{0.5, 0.5765, 1, 1}, 8, 1)));
    materials.insert(make_pair("grass-texture", make_shared<Material>(vec4{0.1, 0.1, 0.1, 1}, 8, 1)));
    materials["grass-texture"]->setTexture(make_shared<Texture>("../res/grass.png"));
    materials.insert(make_pair("grass-texture-scaled", make_shared<Material>(vec4{0.1, 0.1, 0.1, 1}, 8, 1)));
    materials["grass-texture-scaled"]->setTexture(make_shared<Texture>("../res/grass.png"));
    materials["grass-texture-scaled"]->getTexture()->setTextureScale(200);
    materials.insert(make_pair("wood-texture", make_shared<Material>(vec4{0.1, 0.1, 0.1, 1}, 8, 1)));
    materials["wood-texture"]->setTexture(make_shared<Texture>("../res/wood.png"));
    materials.insert(make_pair("house-texture", make_shared<Material>(vec4{0.1, 0.1, 0.1, 1}, 8, 1)));
    materials["house-texture"]->setTexture(make_shared<Texture>("../res/obj/house/house.png"));
    materials["house-texture"]->getTexture()->setTextureScale(1);
    materials.insert(make_pair("wall-texture", make_shared<Material>(vec4{0.1, 0.1, 0.1, 1}, 8, 1)));
    materials["wall-texture"]->setTexture(make_shared<Texture>("../res/obj/wall/wall.png"));
}

void Application::createModels() {
    printf("Creating Models ...\n");

    meshes.insert(make_pair("square", make_shared<SquareMesh>()));
    meshes.insert(make_pair("triangle", make_shared<TriangleMesh>()));
    meshes.insert(make_pair("suzi", make_shared<SuziMesh>()));
    meshes.insert(make_pair("suziSmooth", make_shared<SuziSmoothMesh>()));
    meshes.insert(make_pair("sphere", make_shared<SphereMesh>()));
    meshes.insert(make_pair("tree", make_shared<TreeMesh>()));
    meshes.insert(make_pair("bushes", make_shared<BushesMesh>()));
    meshes.insert(make_pair("gift", make_shared<GiftMesh>()));
    meshes.insert(make_pair("plane", make_shared<PlaneMesh>()));
    meshes.insert(make_pair("cube", make_shared<CubeMesh>()));
    meshes.insert(make_pair("house", make_shared<HouseMesh>()));
    meshes.insert(make_pair("container-large", make_shared<ContainerLargeMesh>()));
    meshes.insert(make_pair("container-medium", make_shared<ContainerMediumMesh>()));
    meshes.insert(make_pair("wall", make_shared<WallMesh>()));

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

shared_ptr<Material> Application::getMaterial(string name) {
    return materials[name];
}

shared_ptr<ShaderProgram> Application::getShaderProgram(string name) {
    return shaderPrograms[name];
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
    } else if (keyInput.key == GLFW_KEY_B) {
        spawnActor = keyInput.action != GLFW_RELEASE ? "tree" : "";
    } else if (keyInput.key == GLFW_KEY_N) {
        spawnActor = keyInput.action != GLFW_RELEASE ? "gift" : "";
    }
}

void Application::OnSelected(SelectResult result) {
    if (!result.found) return;
    shared_ptr<Scene> scene = getScene();
    
    if (spawnActor == "tree") {        
        shared_ptr<Actor> tree = make_shared<Actor>(meshes["tree"].get(), shaderPrograms["phong"], materials["green-shiny"]);
        float scale = UtilClass::randomFloatRange(0.8f, 1.2f);
        tree
            ->addTransform(make_shared<Location>(result.position))
            ->addTransform(make_shared<Scale>(vec3{scale, scale, scale}))        
            ->addTransform(make_shared<Rotation>(UtilClass::randomFloatRange(0, 360), vec3{0, 1, 0}));
        scene->addActor(tree);
        return;
    } else if (spawnActor == "gift") {        
        shared_ptr<Actor> gift = make_shared<Actor>(meshes["gift"].get(), shaderPrograms["phong"], materials["red-shiny"]);
        gift
            ->addTransform(make_shared<Location>(result.position))
            ->addTransform(make_shared<Scale>(UtilClass::randomFloatRange(.75f, 3.0f)))
            ->addTransform(make_shared<Rotation>(UtilClass::randomFloatRange(0, 360), vec3{0, 1, 0}));
        scene->addActor(gift);
        return;
    }

    shared_ptr<Actor> actor = scene->getActor(result.index);    
    if (actor) {
        if (dynamic_cast<GiftMesh*>(actor->getMesh())) {
            scene->removeActor(actor);
            printf("Collected Gift\n");
            return;
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
    shared_ptr<Actor> plane1 = make_shared<Actor>(meshes["plane"].get(), shaderPrograms["phong"], materials["grass-texture"]);
    shared_ptr<Actor> plane2 = make_shared<Actor>(meshes["plane"].get(), shaderPrograms["phong"], materials["wood-texture"]);
    shared_ptr<Actor> plane3 = make_shared<Actor>(meshes["plane"].get(), shaderPrograms["phong"], materials["house-texture"]);
    
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

    plane1->addTransform(make_shared<Location>(vec3{0, -1, 0}));
    plane2->addTransform(make_shared<Location>(vec3{0, -2, 0}));
    plane3->addTransform(make_shared<Location>(vec3{0, -3, 0}));
    
    scene->addActor(sphereActor1);
    scene->addActor(sphereActor2);
    scene->addActor(sphereActor3);
    scene->addActor(sphereActor4);
    scene->addActor(sphereActor5);
    scene->addActor(plane1);
    scene->addActor(plane2);
    scene->addActor(plane3);

    shared_ptr<PointLight> light1 = make_shared<PointLight>();
    light1->setPosition({0, 0, -1});
    light1->setColor({.3, .3, 1, 1});
    light1->setIntensity(0.5f);
    light1->setDimmingFactor(.005f);
    scene->addLight(light1);
    
    shared_ptr<PointLight> light2 = make_shared<PointLight>();
    light2->setPosition({0, 0, 1});
    light2->setColor({1, .3, .3, 1});
    light2->setIntensity(0.5);
    light2->setDimmingFactor(.005f);
    scene->addLight(light2);
    
    shared_ptr<DirectionalLight> light3 = make_shared<DirectionalLight>();
    light3->setColor({.3, .3, .3, 1});
    light3->setDirection({.1, 1, 1});
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

    shared_ptr<Actor> skybox = make_shared<Actor>(meshes["cube"].get(), shaderPrograms["texture-skybox"], materials["grey-mat"]);    
    skybox->getMaterial()->setTexture(make_shared<CubeMapTexture>("../res/night/", ".png"));
    scene->setSkybox(skybox);
    
    shared_ptr<Actor> floor = make_shared<Actor>(meshes["plane"].get(), shaderPrograms["phong"], materials["grass-texture-scaled"]);
    shared_ptr<Actor> gift = make_shared<Actor>(meshes["gift"].get(), shaderPrograms["phong"], materials["red-shiny"]);
    shared_ptr<Actor> house = make_shared<Actor>(meshes["house"].get(), shaderPrograms["phong"], materials["house-texture"]);
    shared_ptr<Actor> container_large = make_shared<Actor>(meshes["container-large"].get(), shaderPrograms["phong"], materials["red-shiny"]);
    shared_ptr<Actor> container_medium = make_shared<Actor>(meshes["container-medium"].get(), shaderPrograms["phong"], materials["red-shiny"]);

    shared_ptr<Actor> flyingBallLine  = make_shared<Actor>(meshes["sphere"].get(), shaderPrograms["phong"], materials["red-mat"]);
    shared_ptr<Actor> flyingBallCurve  = make_shared<Actor>(meshes["sphere"].get(), shaderPrograms["phong"], materials["blue-mat"]);
    
    floor
        ->addTransform(make_shared<Location>(vec3{0, 0, 1}))                
        ->addTransform(make_shared<Scale>(vec3{200, 200, 200}));    
    gift
        ->addTransform(make_shared<Location>(vec3{0, 0, 1}))
        ->addTransform(make_shared<Scale>(vec3{3, 3, 3}));
    house
        ->addTransform(make_shared<Location>(vec3{0, 0,0}));
    container_large
        ->addTransform(make_shared<Location>(vec3{13, 1.27, 0}))
        ->addTransform(make_shared<Rotation>(-90, vec3{1, 0, 0}))
        ->addTransform(make_shared<Rotation>(25, vec3{0, 0, 1}));
    container_medium
        ->addTransform(make_shared<Location>(vec3{10, .325, 0}))
        ->addTransform(make_shared<Rotation>(-90, vec3{1, 0, 0}));    
    flyingBallLine
        ->addTransform(make_shared<Location>(vec3{7.5, 1, 8}))
        ->addTransform(make_shared<Scale>(.3))
        ->addTransform(make_shared<ContinuousMoveOnLine>(vec3{9, 0, 0}, 0.01f));

    shared_ptr<ContinuousMoveOnCurve> moveOnCurve = make_shared<ContinuousMoveOnCurve>(
            mat4{
                vec4{-1.0, 3.0, -3.0, 1},
                vec4{3.0, -6.0, 3.0, 0},
                vec4{-3.0, 3.0, 0, 0},
                vec4{1, 0, 0, 0}
            },
            mat4x3{
                vec3{0, 2, 0},
                vec3{1, 3, 0},
                vec3{2, 3, 0},
                vec3{3, 2, 0}
            }, 0.01f);
    moveOnCurve->addPoint({5, 1, 0}, {6, 2, 0});
    moveOnCurve->addPoint({8, 3, 0}, {9, 2, 0});
    
    flyingBallCurve
        ->addTransform(make_shared<Location>(vec3{7.5, 1, 10}))
        ->addTransform(make_shared<Scale>(.3))
        ->addTransform(moveOnCurve);
    
    scene->addActor(floor);
    scene->addActor(gift);
    scene->addActor(house);
    scene->addActor(container_large);
    scene->addActor(container_medium);
    scene->addActor(flyingBallLine);
    scene->addActor(flyingBallCurve);
    
    for(int i = 0; i < 8; i++) {
        shared_ptr<Actor> wall = make_shared<Actor>(meshes["wall"].get(), shaderPrograms["phong"], materials["wall-texture"]);
        wall
            ->addTransform(make_shared<Location>(vec3{0,0,20}))
            ->addTransform(make_shared<Rotation>(-15, vec3{0, 1, 0}))
            ->addTransform(make_shared<Scale>(.3f))
            ->addTransform(make_shared<Location>(vec3{(i - 2.5) * 8, 0, 0}));
        scene->addActor(wall);
    }

    int countOfTrees = 100;
    for(int i = 0; i < countOfTrees; i++) {
        shared_ptr<Actor> tree = make_shared<Actor>(meshes["tree"].get(), shaderPrograms["blinn"], materials["green-shiny"]);
        float scale = UtilClass::randomFloatRange(0.8f, 1.2f);
        float x = UtilClass::randomFloatRange(-50, 50);
        float y = UtilClass::randomFloatRange(-50, 50);
        if (x < 15 && x > -15 && y < 15 && y > -15) {
            i--;
            continue;
        }
        tree
            ->addTransform(make_shared<Location>(vec3{x, 0, y}))
            ->addTransform(make_shared<Rotation>(UtilClass::randomFloatRange(0, 360), vec3{0, 1, 0}))
            ->addTransform(make_shared<Scale>(vec3{scale,  scale, scale}));

        scene->addActor(tree);
    }

    int countOfBushes = 50;
    for(int i = 0; i < countOfBushes; i++) {
        shared_ptr<Actor> bush = make_shared<Actor>(meshes["bushes"].get(), shaderPrograms["blinn"], materials["green-shiny"]);
        float scale = UtilClass::randomFloatRange(0.3f, 0.5f);
        bush
            ->addTransform(make_shared<Location>(vec3{UtilClass::randomFloatRange(-50, 50), 0, UtilClass::randomFloatRange(-50, 50)}))
            ->addTransform(make_shared<Rotation>(UtilClass::randomFloatRange(0, 360), vec3{0, 1, 0}))
            ->addTransform(make_shared<Scale>(vec3{scale,  scale, scale}));

        scene->addActor(bush);
    }

    shared_ptr<PointLight> light2 = make_shared<PointLight>();
    light2->setPosition({10, 2, 0});
    light2->setDimmingFactor(0.1f);
    scene->addLight(light2);
    
    shared_ptr<PointLight> light3 = make_shared<PointLight>();
    light3->setPosition({8, 1, 9});
    light3->setDimmingFactor(0.1f);
    scene->addLight(light3);
    
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
