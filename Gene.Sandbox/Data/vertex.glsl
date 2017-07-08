#version 130

in vec3 position; 
//in vec3 color;	
//in vec2 uv;
  
//out vec3 pass_Color; 
//out vec2 pass_Uv;

uniform mat4 u_Matrix;
uniform mat4 u_Transform;

void main()
{
    gl_Position = u_Matrix * u_Transform * vec4(position, 1.0);
    //pass_Color  = color;
	//pass_Uv     = uv;
}     
