#include <SpinningCube.h>

void update(App* app)
{
    if (is_key_down(app, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(app->window, true);
}