#include "Application.h"

#include "GLFWCallbacks/ErrorGLFWCallback.hpp"
#include "Meshes/SquareMesh.h"
#include "Meshes/TriangleMesh.h"

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

    screen = new Screen();

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

    input = new Input(getWindow());
    scene = new Scene();
}

void Application::createShaders() {
    printf("Creating Shaders ...\n");
    FragmentShader fragmentShader = FragmentShader();
    fragmentShader.compile();
    printf("FragmentShader Created\n");
    
    VertexShader vertexShader = VertexShader();
    vertexShader.compile();
    printf("VertexShader Created\n");
    
    printf("Shaders Created\n");

    printf("Setting Shader Program ...\n");
    const GLuint shaderProgram = glCreateProgram();
    fragmentShader.attach(shaderProgram);
    vertexShader.attach(shaderProgram);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    printf("Shader Program Set\n");

    printf("Checking Shaders ...\n");
    GLint status;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }
    printf("Shaders Check\n");
}

void Application::createModels() {
    printf("Creating Models ...\n");
    TriangleMesh* triangle = new TriangleMesh();
    scene->addMesh(triangle);

    SquareMesh* square = new SquareMesh();
    scene->addMesh(square);

    printf("Models Created\n");
}

void Application::run() {
    printf("Running ...\n");
    while (!glfwWindowShouldClose(getWindow())) {
        scene->draw();
    }

    onExit();
    
    glfwDestroyWindow(getWindow());
    glfwTerminate();
    exit(EXIT_SUCCESS);
}


void Application::onExit() {
    printf("Exiting ...");
}

GLFWwindow* Application::getWindow() {
    return screen->getWindow();
}

Input* Application::getInput() {
    return input;
}

Screen* Application::getScreen() {
    return screen;
}
