#include <SpinningCube.h>

void render_start(App* app)
{
	float vertices[12] = 
	{
		-0.5f, -0.5f, 0.0f, 1.0f,
    	0.5f, -0.5f, 0.0f, 1.0f,
		0.0f,  0.5f, 0.0f, 1.0f
	};

	Storage_Buffer basic_shader_storage_buffer = shget(app->ssbo_array, "basic_shader_ssbo");
	memcpy(basic_shader_storage_buffer.buffer_map, vertices, sizeof(float) * 12);

    GL_CHECK(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));  // window bg colour
}

void render(App* app)
{
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

	GL_CHECK(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, shget(app->ssbo_array, "basic_shader_ssbo").buffer));
	GL_CHECK(glUseProgram(shget(app->shader_array, "basic_shader")));
	GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}
