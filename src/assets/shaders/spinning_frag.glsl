#version 460 core

in  vec4 vert_color;
out vec4 frag_color;

void main()
{
	vec2 pos = gl_FragCoord.xy / vec2(800, 600) - 0.5;
	
	vec2 top    = pos - vec2(1.0, 0.0)/2;
	vec2 left   = pos - vec2(cos(radians(240.0)), sin(radians(240.0)))/2;
	vec2 right  = pos - vec2(cos(radians(120.0)), sin(radians(120.0)))/2;

	frag_color = vec4(1.0-length(top), 1.0-length(left), 1.0-length(right), 1.0);
}
