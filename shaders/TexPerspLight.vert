#version 400

layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal;
layout(location=2) in vec2 in_TexCoord;
layout(location=3) in uint in_TexID;

out vec3 vert_Pos;
out vec3 vert_Normal;
out vec2 vert_TexCoord;
flat out uint vert_texID;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main(void)
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4( in_Position.xyz, 1.0 );
	
	vert_Pos    = in_Position;
	vert_Normal = in_Normal;
	vert_TexCoord = in_TexCoord;
	vert_texID = in_TexID;
}
