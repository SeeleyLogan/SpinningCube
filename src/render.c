#include <SpinningCube.h>

void render_start(App* app)
{
	// rad * (pi/180)
	float vertices[] =
	{
		/*      positions     */
    	cosf(0.0f),   sinf(0.0f), 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  // top right
    	cosf(120.0f * (M_PI/180.0f)), sinf(120.0f * (M_PI/180.0f)), 0.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,  // bottom right
    	cosf(240.0f * (M_PI/180.0f)), sinf(240.0f * (M_PI/180.0f)), 0.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,  // bottom left
	};

	u32 indices[] =
	{
    	0, 1, 2   // first triangle
	}; 

	memcpy(shget(app->ssbo_array, "basic_vertex").buffer_map, vertices, sizeof(float) * 24);
	memcpy(shget(app->ssbo_array, "basic_index").buffer_map,  indices,  sizeof(u32)   * 3);
   
	GL_CHECK(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));		 // window bg colour
	//GL_CHECK(glEnable(GL_PROGRAM_POINT_SIZE)));
	//GL_CHECK(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE))  // draw in wireframes
}

void render(App* app)
{
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

	GL_CHECK(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, shget(app->ssbo_array, "basic_vertex").buffer));
	GL_CHECK(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, shget(app->ssbo_array, "basic_index").buffer));
	GLint vertex_aspect_ratio_loc = GL_CHECK(glGetUniformLocation(shget(app->shader_array, "basic_shader"), "aspect_ratio"));
	GLint vertex_time_loc		  = GL_CHECK(glGetUniformLocation(shget(app->shader_array, "basic_shader"), "time"));
	GL_CHECK(glUseProgram(shget(app->shader_array, "basic_shader")));		
	GL_CHECK(glUniform1f(vertex_aspect_ratio_loc, app->aspect_ratio));
	GL_CHECK(glUniform1f(vertex_time_loc, glfwGetTime()));
	GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}
