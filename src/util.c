#include <SpinningCube.h>

inline bool is_key_down(App* app, u16 key)
{
    return (glfwGetKey(app->window, key) == GLFW_PRESS);
}