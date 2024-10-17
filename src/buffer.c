#include <SpinningCube.h>

#define STORAGE_FLAGS GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT | GL_MAP_READ_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT
#define MAPPING_FLAGS GL_MAP_WRITE_BIT | GL_MAP_READ_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT

void create_buffers(App* app)
{
	// never think about this VAO ever again
	GLuint VAO;
	GL_CHECK(glGenVertexArrays(1, &VAO));
	GL_CHECK(glBindVertexArray(VAO));

	GLuint buffers[4];
	GL_CHECK(glCreateBuffers(4, buffers));  // amount of buffers to make, must match buffers size
	
	shput(app->sb_array, "spinning_vertex", create_storage_buffer(buffers[0]));
	shput(app->sb_array, "spinning_index", create_storage_buffer(buffers[1]));

	shput(app->sb_array, "square_vertex", create_storage_buffer(buffers[2]));
	shput(app->sb_array, "square_index",  create_storage_buffer(buffers[3]));
}

Storage_Buffer* create_storage_buffer(GLuint buffer)
{
	GL_CHECK(glNamedBufferStorage(buffer, DEFAULT_STORAGE_BUFFER_SIZE, NULL, STORAGE_FLAGS));
	Storage_Buffer* storage_buffer = MALLOC_CHECK(REALLOC(NULL, sizeof(Storage_Buffer)));
	void* map = GL_CHECK(glMapNamedBufferRange(buffer, 0, DEFAULT_STORAGE_BUFFER_SIZE, MAPPING_FLAGS));
	
	*storage_buffer = (Storage_Buffer)
	{
		buffer,
		map, map,
		map + DEFAULT_STORAGE_BUFFER_SIZE
	};

	return storage_buffer;
}

inline void copy_to_storage_buffer(Storage_Buffer* sb, void* src, u32 size)
{
	memcpy(sb->map_unoccupied, src, size);
	sb->map_unoccupied += size;
}

