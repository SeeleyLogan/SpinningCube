#include <SpinningCube.h>

int main()
{
    App app = create_app(800, 800);
    glfwSetWindowUserPointer(app.window, &app);
	run_app(&app);
}

