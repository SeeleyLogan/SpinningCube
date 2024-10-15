#version 460

layout(std460, binding = 0) buffer vertexData
{
	vec3 vertices[];
};

void main()
{
	vec3 aPos 	= vertices[gl_VertexID];
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
