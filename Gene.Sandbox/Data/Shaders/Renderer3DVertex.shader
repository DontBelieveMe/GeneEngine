#version 330 core

layout(location = 0) in vec3 position; 
layout(location = 1) in vec2 tex_coord;
layout(location = 2) in vec3 normal;

uniform mat4 u_Projection;
uniform mat4 u_Transform;

out vec3 pass_position;
out vec2 pass_tex_coord;
out vec3 pass_normal;

void main()
{
	vec4 world_pos = u_Transform * vec4(position, 1.0);
    gl_Position = u_Projection * world_pos;
    pass_position = vec3(world_pos);
    pass_tex_coord = tex_coord;
    pass_normal = normal;
}     
