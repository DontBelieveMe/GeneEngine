#version 130

out vec4 color;

uniform sampler2D texture_Sampler;
uniform vec3 light_pos;

in vec3 pass_position;
in vec2 pass_tex_coord;
in vec3 pass_normal;

void main()
{
    vec3 light_color = vec3(1.0f, 1.0f, 1.0f);
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * light_color;

    vec3 norm = normalize(pass_normal);
    vec3 lightDir = normalize(light_pos - pass_position);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light_color;
    vec3 result = (ambient + diffuse) * vec3(texture(texture_Sampler, pass_tex_coord));
    
    color = vec4(result, 1.0f);
}
