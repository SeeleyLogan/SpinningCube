#define STB_DS_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include <SpinningCube.h>

void update_viewport(GLFWwindow* window, i32 width, i32 height);

// GLFW and GLAD boilerplate
App create_app(u16 width, u16 height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // MacOS... but who supports that?

    GLFWwindow* window = glfwCreateWindow(width, height, "Spinning Cube", NULL, NULL);
    if (!window)
        ERROR(1, "GLFW failed to create a window")

    glfwMakeContextCurrent(window);  // so we don't have to keep passing window to every glfw methods

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        ERROR(1, "Glad was not very glad...")

    glViewport(0, 0, width, height);  // used to map 2d space to screen space (not that fucking hard)
    glfwSetFramebufferSizeCallback(window, update_viewport);  // update the viewport on window resize

    return (App)
    {
        window,
		NULL,
		NULL
    };
}

void run_app(App* app)
{
	create_buffers(app);
	compile_shaders(app);

	update_start(app);
	render_start(app);

    // game loop? render loop? IT'S A GOD DAMN LOOP!
    while(!glfwWindowShouldClose(app->window))
    {
        update(app);
        render(app);

        glfwSwapBuffers(app->window);
        glfwPollEvents();    
    }
}

void terminate_app(App* app)
{
    glfwTerminate();
}

// =============
// local methods
// =============

void update_viewport(GLFWwindow* window, i32 width, i32 height)
{
    GL_CHECK(glViewport(0, 0, width, height));
}
