#version 130

in vec3 position; 
in vec3 normal;

uniform mat4 u_Projection;
uniform mat4 u_Transform;

out vec3 pass_normal;
out vec3 pass_position;

void main()
{
	pass_normal = normal;
	pass_position = normal;
    gl_Position = u_Projection * u_Transform * vec4(position, 1.0);
}     
