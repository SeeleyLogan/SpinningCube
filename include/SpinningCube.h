#if !defined(linux) && !defined(_WIN32)
    #error "This operating system is not supported"
#endif

#ifndef SPINNING_CUBE_H
#define SPINNING_CUBE_H

#define ASSETS_PATH "./assets"
#define DEFAULT_STORAGE_BUFFER_SIZE 65536

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_ds.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef linux
    #include <dirent.h>
	#include <regex.h>
#else						
   	#include <windows.h>
#endif

typedef unsigned char      u8;
typedef char               i8;
typedef unsigned short     u16;
typedef short              i16;
typedef unsigned int       u32;
typedef int                i32;
typedef unsigned long long u64;
typedef long long          i64;
typedef float              f32;

#define OUT stdout
#define DBG stdout
#define IN  stdin
#define ERR stderr

#define REALLOC(...) realloc(__VA_ARGS__)
#define FREE(...)	 free(__VA_ARGS__)

#define ERROR(err_lvl, ...) { fprintf(ERR, __VA_ARGS__); exit(err_lvl); terminate_app(NULL); }

#ifdef DEBUG
#define GL_CHECK(...) \
    __VA_ARGS__; \
    do { \
    GLenum gl_err = glGetError(); \
    if (gl_err != GL_NO_ERROR) \
    { \
        fprintf(ERR, "error: OpenGL %08x at %s:%i -> %s\n", gl_err, __FILE__, __LINE__, #__VA_ARGS__); \
        exit(-1); \
    } \
    } while (0)
#else
    #define GL_CHECK(...) __VA_ARGS__
#endif

#define MALLOC_CHECK(...) \
    ({ \
	 	void* ptr = __VA_ARGS__; \
		if (!ptr) \
			ERROR(1, "error: memory allocation returned null at %s:%i -> %s\n", __FILE__, __LINE__, #__VA_ARGS__) \
	 	ptr; \
	})

#define FILE_OPEN(file, mode) \
    ({ \
	 	void* ptr = fopen(file, mode); \
		if (!ptr) \
			ERROR(1, "error: failed to open file '%s' at %s:%i\n", file, __FILE__, __LINE__) \
	 	ptr; \
	})

typedef struct Storage_Buffer
{
	GLuint buffer;
	u32 occupied;
	u32 capacity;
}
Storage_Buffer;

typedef struct App
{
    GLFWwindow* window;
	struct
	{
		char* key;
		Storage_Buffer value; 
	} 
	*ssbo_array;
}
App;

typedef struct Glob
{
    char** file_array;
    u32    file_count;
}
Glob;

typedef struct Shader
{

}
Shader;

// =====
// app.c
// =====

App create_app(u16 width, u16 height);
void run_app(App* app);
void terminate_app(App* app);

// ======
// util.c
// ======

bool is_key_down(App* app, u16 key);

// ======
// glob.c
// ======

Glob glob_files(const char* restrict pattern);
void free_glob(Glob* glob);

// ========
// buffer.c
// ========

void create_buffers(App* app);

// ========
// shader.c
// ========

void compile_shaders(App* app);

// =======
// start.c
// =======

void start(App* app);

// ========
// update.c
// ========

void update(App* app);

// ========
// render.c
// ========

void render(App* app);

#endif
