#version 460 core

layout(std430, binding = 0) buffer vertexData
{
	vec4 vertices[];
};

void main()
{
	gl_Position = vertices[gl_VertexID];
}

