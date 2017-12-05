#version 130

in vec3 position; 
in vec3 normal;

uniform mat4 u_Projection;
uniform mat4 u_Transform;

uniform vec3 u_LightPos;

out vec3 pass_normal;
out vec3 pass_position;
out vec3 pass_to_light_vec;

void main()
{
	vec4 world_pos = u_Transform * vec4(position, 1.0);
	pass_normal = (u_Transform * vec4(normal, 0.0f)).xyz;
	pass_position = position;
    gl_Position = u_Projection * world_pos;
	pass_to_light_vec = u_LightPos - world_pos.xyz;
}     
