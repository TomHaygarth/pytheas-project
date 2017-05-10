#version 330 core

in vec2 UV;

out vec4 color;

uniform sampler2D myTextureSampler;
uniform vec3 SpriteColor;

void main()
{
	color = texture( myTextureSampler, UV ) * vec4(SpriteColor, 1.0);	
}