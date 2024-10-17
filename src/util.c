#include <SpinningCube.h>

inline double rad(double deg)
{
	return deg * (M_PI/180.0);
}

inline float radf(float deg)
{
	return deg * (M_PI/180.0f);
}

inline bool is_key_down(App* app, u16 key)
{
    return (glfwGetKey(app->window, key) == GLFW_PRESS);
}
