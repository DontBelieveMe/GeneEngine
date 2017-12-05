#version 130

out vec4 color;

uniform sampler2D texture_Sampler;

in vec3 pass_normal;
in vec3 pass_position;
in vec3 pass_to_light_vec;

void main()
{
	vec3 unit_normal = normalize(pass_normal);
	vec3 unit_light_vec = normalize(pass_to_light_vec);

	float _dot = dot(unit_normal, unit_light_vec);
	float _bright = max(_dot, 0.0);
	if(_bright < 0.2f)
		_bright = 0.2f;
	vec3 diffuse = _bright * vec3(1.0f, 0.0f, 0.0f);

    color = vec4(diffuse, 1.0) * vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
