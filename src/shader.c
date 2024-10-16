#include <SpinningCube.h>

void compile_shaders(App* app)
{
	GLuint basic_shaders[2] =
	{
		compile_shader(ASSETS_PATH"/shaders/basic_vert_shader.glsl", GL_VERTEX_SHADER),
		compile_shader(ASSETS_PATH"/shaders/basic_frag_shader.glsl", GL_FRAGMENT_SHADER)
	};
	GLuint basic_shader_program = create_shader_program(basic_shaders, 2);
	shput(app->shader_array, "basic_shader", basic_shader_program);
}

GLuint compile_shader(const GLchar* source, GLenum shader_type)
{
	FILE* shader_file = FILE_OPEN(source, "rb");

	// shader file size can't be larger than 4GB
	fseek(shader_file, 0L, SEEK_END);
	long shader_file_size = ftell(shader_file) + 1;
	rewind(shader_file);

	char* shader_contents = MALLOC_CHECK(REALLOC(NULL, shader_file_size));
	fread(shader_contents, 1, shader_file_size, shader_file);
	shader_contents[shader_file_size-1] = 0;

	GLuint shader = GL_CHECK(glCreateShader(shader_type));
	GL_CHECK(glShaderSource(shader, 1, (const char**) &shader_contents, NULL));
	GL_SHADER_CHECK(glCompileShader, glGetShaderiv, shader, GL_COMPILE_STATUS, "error: compiling shader failed at %s:%i -> %s\n", __FILE__, __LINE__, info_log);

	FREE(shader_contents);
	fclose(shader_file);

	return shader;
}

GLuint create_shader_program(GLuint* shaders, u8 count)
{
	GLuint shader_program = GL_CHECK(glCreateProgram());

	for (u8 i = 0; i < count; i++)
	{
		GL_CHECK(glAttachShader(shader_program, shaders[i]));
		GL_CHECK(glDeleteShader(shaders[i]))
	}

	GL_SHADER_CHECK(glLinkProgram, glGetProgramiv, shader_program, GL_LINK_STATUS, "error: linking shader program failed at %s:%i -> %s\n", __FILE__, __LINE__, info_log);

	return shader_program;
}

