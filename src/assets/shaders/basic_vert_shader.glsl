#version 460 core

layout(std430, binding = 0) buffer vertex_data
{
	vec4 vertices[];
};

layout(std430, binding = 1) buffer index_data
{
	uint indices[];
};

void main()
{
	gl_Position = vertices[indices[gl_VertexID]];  // make this work by passing in a second SSBO with the indices includes
}

