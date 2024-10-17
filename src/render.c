#include <SpinningCube.h>

void render_start(App* app)
{
	GL_CHECK(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));		 // window bg colour
	//GL_CHECK(glEnable(GL_PROGRAM_POINT_SIZE)));
	//GL_CHECK(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE))  // draw in wireframes

	float spinning_vertices[] =
	{
		/*               positions                */	/*   colors   */   /*textures*/
    	cosf(radf(  0.0f)), sinf(  radf(0.0f)), 0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
    	cosf(radf(120.0f)), sinf(radf(120.0f)), 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
    	cosf(radf(240.0f)), sinf(radf(240.0f)), 0.0f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f
	};

	u32 spinning_indices[] =
	{
    	0, 1, 2   // first triangle
	}; 

	copy_to_storage_buffer(shget(app->sb_array, "spinning_vertex"), spinning_vertices, sizeof(float) * 24);
	copy_to_storage_buffer(shget(app->sb_array, "spinning_index"),  spinning_indices,  sizeof(u32)   * 3);

	float square_vertices[] =
	{
		/*      positions      */
    	 1.0f,  1.0f, 0.0f, 1.0f,
    	-1.0f,  1.0f, 0.0f, 1.0f,
    	-1.0f, -1.0f, 0.0f, 1.0f,
    	 1.0f, -1.0f, 0.0f, 1.0f
	};

	u32 square_indices[] =
	{
    	0, 1, 2,   // first triangle
		0, 2, 3
	}; 

	copy_to_storage_buffer(shget(app->sb_array, "square_vertex"), square_vertices, sizeof(float) * 16);
	copy_to_storage_buffer(shget(app->sb_array, "square_index"),  square_indices,  sizeof(u32)   * 6);
}

void render(App* app)
{
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

	GL_CHECK(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, shget(app->sb_array, "square_vertex")->buffer));
	GL_CHECK(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, shget(app->sb_array, "square_index")->buffer));
	GL_CHECK(glUseProgram(shget(app->shader_array, "square_shader")));
	GLint square_time_loc		  = GL_CHECK(glGetUniformLocation(shget(app->shader_array, "square_shader"), "iTime"));
	GLint square_resolution_loc  = GL_CHECK(glGetUniformLocation(shget(app->shader_array, "square_shader"), "iResolution"));
	GLint width, height;
	glfwGetWindowSize(app->window, &width, &height);
	GL_CHECK(glUniform1f(square_time_loc, glfwGetTime()));	
	GL_CHECK(glUniform2f(square_resolution_loc, (float) width, (float) height));
	GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 6));

	/*
	GL_CHECK(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, shget(app->sb_array, "spinning_vertex")->buffer));
	GL_CHECK(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, shget(app->sb_array, "spinning_index")->buffer));
	GLint spinning_aspect_ratio_loc = GL_CHECK(glGetUniformLocation(shget(app->shader_array, "spinning_shader"), "aspect_ratio"));
	GLint spinning_time_loc = GL_CHECK(glGetUniformLocation(shget(app->shader_array, "spinning_shader"), "time"));
	GL_CHECK(glUseProgram(shget(app->shader_array, "spinning_shader")));
	GL_CHECK(glUniform1f(spinning_aspect_ratio_loc, app->aspect_ratio));
	GL_CHECK(glUniform1f(spinning_time_loc, glfwGetTime()));
	GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
	*/
}
