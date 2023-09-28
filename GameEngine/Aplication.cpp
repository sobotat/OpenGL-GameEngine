#include "Aplication.h"

Aplication* Aplication::instance_ = new Aplication();

Aplication* Aplication::getInstance() {
    return instance_;
}

Aplication::Aplication() {
    ratio = float(width) / float(height);
}

void Aplication::init() {    
    printf("Init\n");
    
    //glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE,
    GLFW_OPENGL_CORE_PROFILE);  //*/

    window = glfwCreateWindow(width, height, "ZPG", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

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

    glfwGetFramebufferSize(window, &width, &height);
    
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

    input = new Input(window);
}

void Aplication::createShaders() {
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
}

void Aplication::createModels() {
    printf("Creating Models ...\n");
}

void Aplication::run() {
    printf("Running ...\n");
}

GLFWwindow* Aplication::getWindow() {
    return window;
}

Input* Aplication::getInput() {
    return input;
}
