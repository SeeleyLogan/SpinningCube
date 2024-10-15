#include <SpinningCube.h>

void compile_shaders(App* app)
{
	Glob shader_files = glob_files("./assets/shaders/.glsl$");

	for (u16 i = 0; i < shader_files.file_count; i++)
	{
		char* shader_file_name = shader_files.file_array[i];
		char* shader_file_path = MALLOC_CHECK(REALLOC(NULL, strlen(ASSETS_PATH"/shaders/") + strlen(shader_file_name) + 1));
		sprintf(shader_file_path, "%s", ASSETS_PATH"/shaders/");
		strcat(shader_file_path, shader_file_name);
	
		FILE* shader_file = FILE_OPEN(shader_file_path, "rb");

		// shader file size can't be larger than 4GB
		fseek(shader_file, 0L, SEEK_END);
		long shader_file_size = ftell(shader_file) + 1;
		rewind(shader_file);

		char* shader_contents = MALLOC_CHECK(REALLOC(NULL, shader_file_size));
		fread(shader_contents, 1, shader_file_size-1, shader_file);
		shader_contents[shader_file_size-1] = 0;

		fprintf(DBG, "%s", shader_contents);

		// compile shader
		// ...

		FREE(shader_file_path);
		FREE(shader_contents);
		fclose(shader_file);
	}

	free_glob(&shader_files);
}
