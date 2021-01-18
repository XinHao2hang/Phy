#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec3 position;
uniform mat4 transform;

void main()
{
	vec4 tpos = transform * vec4(aPos, 1.0f);
	gl_Position = vec4(tpos.x+position.x,tpos.y+position.y,0,1.0f);
}