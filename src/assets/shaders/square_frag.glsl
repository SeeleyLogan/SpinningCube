#version 460 core

#define M_PI 3.1415926535897932384626433832795

#define RED   vec4(1.0, 0.0, 0.0, 1.0)
#define BLACK vec4(0.0, 0.0, 0.0, 1.0)

#define RAINBOW vec3(0.5, 0.5, 0.5), vec3(0.5, 0.5, 0.5), vec3(1.0, 1.0, 1.0), vec3(0.00, 0.33, 0.67)
#define CANDY   vec3(0.5, 0.5, 0.5), vec3(0.5, 0.5, 0.5), vec3(2.0, 1.0, 0.0), vec3(0.50, 0.20, 0.25)
#define MYSTIC  vec3(0.5, 0.5, 0.5), vec3(0.5, 0.5, 0.5), vec3(1.0, 1.0, 1.0), vec3(0.236, 0.416, 0.557)

uniform float iTime;
uniform vec2  iResolution;

out vec4 frag_color;

vec3 palette(float t, vec3 a, vec3 b, vec3 c, vec3 d)
{
	return a + b * cos(M_PI*2.0*(c*t+d));
}

float dot2(vec2 v) { return dot(v,v); }
float sd_heart(vec2 p)
{
    p.x = abs(p.x);
	p.y += 0.5;

    if( p.y+p.x>1.0 )
        return sqrt(dot2(p-vec2(0.25,0.75))) - sqrt(2.0)/4.0;
    return sqrt(min(dot2(p-vec2(0.00,1.00)),
                    dot2(p-0.5*max(p.x+p.y,0.0)))) * sign(p.x-p.y);
}

void main()
{
	vec2 uv  = (gl_FragCoord.xy * 2.0 - iResolution) / iResolution.y * 2.0;
	vec2 uv0 = uv;
	vec3 final_color = vec3(0.0);

	for (int i = 0; i < 5; i++)
	{
		uv = fract(uv * 1.5) - 0.5;

		float magic = length(uv) * exp(-length(uv0));
		vec3 color = palette(length(uv0)/2.0 + i*0.4 - iTime * 0.4, CANDY);
		magic = sin(magic*8.0 + iTime) / 8.0;
		magic = abs(magic);
		magic = pow(0.01 / magic, 2.0);

		final_color += color * magic;
	}

	frag_color = vec4(final_color, 1.0);
}

