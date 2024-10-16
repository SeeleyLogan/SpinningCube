#define STB_DS_IMPLEMENTATION
#include <SpinningCube.h>

int main()
{
    App app = create_app(800, 600);
    glfwSetWindowUserPointer(app.window, &app);
	run_app(&app);
}

