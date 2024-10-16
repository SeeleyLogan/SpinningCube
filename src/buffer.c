#include <SpinningCube.h>

#define STORAGE_FLAGS GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT | GL_MAP_READ_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT
#define MAPPING_FLAGS GL_MAP_WRITE_BIT | GL_MAP_READ_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT

void create_buffers(App* app)
{
	// never think about this VAO ever again
	GLuint VAO;
	GL_CHECK(glGenVertexArrays(1, &VAO));
	GL_CHECK(glBindVertexArray(VAO));

	GLuint buffers[2];
	GL_CHECK(glCreateBuffers(2, buffers));  // amount of buffers to make, must match buffers size
	
	// basic vertex buffer
	GL_CHECK(glNamedBufferStorage(buffers[0], DEFAULT_STORAGE_BUFFER_SIZE, NULL, STORAGE_FLAGS));
	u8* basic_vertex_buffer_map = GL_CHECK(glMapNamedBufferRange(buffers[0], 0, DEFAULT_STORAGE_BUFFER_SIZE, MAPPING_FLAGS));
	Storage_Buffer basic_vertex_buffer =
	{
		buffers[0],
		basic_vertex_buffer_map,
		0,
		DEFAULT_STORAGE_BUFFER_SIZE
	};
	shput(app->ssbo_array, "basic_vertex", basic_vertex_buffer);

	// basic shader index buffer
	GL_CHECK(glNamedBufferStorage(buffers[1], DEFAULT_STORAGE_BUFFER_SIZE, NULL, STORAGE_FLAGS));
	u8* basic_index_buffer_map = GL_CHECK(glMapNamedBufferRange(buffers[1], 0, DEFAULT_STORAGE_BUFFER_SIZE, MAPPING_FLAGS));
	Storage_Buffer basic_index_buffer =
	{
		buffers[1],
		basic_index_buffer_map,
		0,
		DEFAULT_STORAGE_BUFFER_SIZE
	};
	shput(app->ssbo_array, "basic_index", basic_index_buffer);
}

