#include <SpinningCube.h>

#define STORAGE_FLAGS GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT | GL_MAP_READ_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT
#define MAPPING_FLAGS GL_MAP_WRITE_BIT | GL_MAP_READ_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT

void create_buffers(App* app)
{	
	GLuint buffers[1];
	GL_CHECK(glCreateBuffers(1, buffers));  // amount of buffers to make, must match buffers size
	
	GL_CHECK(glNamedBufferStorage(buffers[0], DEFAULT_STORAGE_BUFFER_SIZE, NULL, STORAGE_FLAGS));
	GL_CHECK(glMapNamedBufferRange(buffers[0], 0, DEFAULT_STORAGE_BUFFER_SIZE, MAPPING_FLAGS));

	Storage_Buffer storage_buffer =
	{
		buffers[0],
		0,
		DEFAULT_STORAGE_BUFFER_SIZE
	};

	shput(app->ssbo_array, "vert_shdr_ssbo", storage_buffer);
}

