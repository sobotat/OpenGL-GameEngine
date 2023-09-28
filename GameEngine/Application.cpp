#include "Application.h"

#include "Meshes/SquareMesh.h"
#include "Meshes/TriangleMesh.h"

Application* Application::instance_ = new Application();

Application* Application::getInstance() {
    return instance_;
}

Application::Application() {
    ratio = float(width) / float(height);
}

void Application::init() {    
    printf("Init\n");
    
    glfwSetErrorCallback(error_callback);
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

    glfwSetWindowFocusCallback(window, window_focus_callback);
    glfwSetWindowIconifyCallback(window, window_iconify_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);

    input = new Input(window);
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
    while (!glfwWindowShouldClose(window)) {
        scene->draw();
    }

    onExit();
    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}


void Application::onExit() {
    printf("Exiting ...");
}

GLFWwindow* Application::getWindow() {
    return window;
}

Input* Application::getInput() {
    return input;
}
