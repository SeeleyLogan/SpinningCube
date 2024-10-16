#version 460 core

#define M_PI 3.1415926535897932384626433832795

layout(std430, binding = 0) buffer vertex_data
{
	vec4 vertices_colors[];
};

layout (std430, binding = 1) buffer index_data
{
	int indices[];
};

out vec4 vert_color;

uniform float aspect_ratio;
uniform float time;

mat4 rotation_matrix;

void main()
{
	rotation_matrix[0] = vec4( cos(time), sin(time), 0.0, 0.0);
	rotation_matrix[1] = vec4(-sin(time), cos(time), 0.0, 0.0);
	rotation_matrix[2] = vec4(0.0, 0.0, 1.0, 0.0);
	rotation_matrix[3] = vec4(0.0, 0.0, 0.0, 1.0);
	
	gl_Position  = vertices_colors[indices[gl_VertexID]*2] * rotation_matrix;
	gl_Position.x /= aspect_ratio;
	gl_PointSize = 10;
	vert_color	 = vertices_colors[indices[gl_VertexID]*2+1];
}

