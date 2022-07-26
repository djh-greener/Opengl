#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat3 NormalMat;

uniform vec3 lightPos;

out vec3 FragPos;
out vec3 Normal;
out vec3 LightPos;
void main()
{
    gl_Position = u_projection * u_view * u_model * vec4(aPos, 1.0);
	FragPos = vec3(u_view*u_model * vec4(aPos, 1.0));
    Normal = NormalMat*aNormal;
	LightPos=vec3(u_view * vec4(lightPos, 1.0));
}

#shader fragment
#version 330 core
in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

out vec4 FragColor;
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

uniform Material material;
uniform vec3 lightColor;
void main()
{
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor*material.ambient;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - FragPos);
	float diff = max(dot(norm, lightDir),0.0);
	vec3 diffuse = diff * lightColor*material.diffuse;

	vec3 EyeDir = -normalize(FragPos);
	vec3 h=normalize(EyeDir+lightDir);
	float spec = pow(abs(dot(norm, h)),material.shininess);
	vec3 specular = spec * lightColor*material.specular;

    vec3 result = ambient+diffuse+specular;
    FragColor = vec4(result, 1.0);
}