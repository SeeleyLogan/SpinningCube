#version 460 core

#define M_PI 3.1415926535897932384626433832795

layout(std430, binding = 0) buffer vertex_data
{
	vec4 vertices[];
};

layout (std430, binding = 1) buffer index_data
{
	uint indices[];
};

void main()
{
	gl_Position = vertices[indices[gl_VertexID]];
}

