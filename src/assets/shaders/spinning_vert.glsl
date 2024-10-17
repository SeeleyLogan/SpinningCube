#version 460 core

#define M_PI 3.1415926535897932384626433832795

layout(std430, binding = 0) buffer vertex_data
{
	float vct[];  // vertex color texture
};

layout (std430, binding = 1) buffer index_data
{
	uint indices[];
};

out vec4 vert_color;

uniform float time;

mat4 rotation_matrix;

void main()
{
	rotation_matrix[0] = vec4( cos(time), sin(time), 0.0, 0.0);
	rotation_matrix[1] = vec4(-sin(time), cos(time), 0.0, 0.0);
	rotation_matrix[2] = vec4(0.0, 0.0, 1.0, 0.0);
	rotation_matrix[3] = vec4(0.0, 0.0, 0.0, 1.0);
	
	uint vertex_index = indices[gl_VertexID]*8;
	uint color_index  = indices[gl_VertexID]*8+3;
	uint tex_index    = indices[gl_VertexID]*8+6;

	gl_Position    = vec4(vct[vertex_index], vct[vertex_index+1], vct[vertex_index+2], 1.0f) * rotation_matrix;
	vert_color	   = vec4(vct[color_index], vct[color_index+1], vct[color_index+2], 1.0f);
}

