#version 330 core

in vec2 UV0;
in vec2 UV1;
in vec2 UV2;

out vec4 color;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	color = texture2D( texture0, UV0 );	
	color = vec4(texel1.a) * texel1 + vec4(1.0 - texel1.a) * color;
	color = vec4(texel2.a) * texel2 + vec4(1.0 - texel2.a) * color;
}