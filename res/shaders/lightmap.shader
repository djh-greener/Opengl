#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat3 NormalMat;
uniform vec3 lightPos;

out vec3 FragPos;
out vec3 Normal;
out vec3 LightPos;
out vec2 TexCoords;
void main()
{
    gl_Position = u_projection * u_view * u_model * vec4(aPos, 1.0);//裁剪空间,之后自动进行透视除法

	FragPos = vec3(u_view*u_model * vec4(aPos, 1.0));//观察空间
    Normal = NormalMat*aNormal;//法向量矫正
	TexCoords = aTexCoords;
	LightPos=vec3(u_view  * vec4(lightPos, 1.0));
}

#shader fragment
#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec3 LightPos;
in vec2 TexCoords;

struct Material {
	sampler2D diffuse;
    sampler2D specular;
	sampler2D text;
    float     shininess;
}; 

uniform Material material;
uniform vec3 lightColor;
uniform float time;

out vec4 FragColor;

void main()
{
    float ambientStrength = 0.2;
    vec3 ambient = lightColor* vec3(texture(material.diffuse, TexCoords))*ambientStrength;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - FragPos);
	float diff = max(dot(norm, lightDir),0.0);
	vec3 diffuse = lightColor * diff * vec3(texture(material.diffuse, TexCoords));

	vec3 EyeDir = -normalize(FragPos);
	vec3 h=normalize(EyeDir+lightDir);
	float spec = pow(abs(dot(norm, h)),material.shininess);
	vec3 specular = spec * lightColor*vec3(texture(material.specular, TexCoords));


	float tmp=time;
	if(TexCoords.y+time>1)
		tmp=tmp-1;
	vec3 text=vec3(texture(material.text, TexCoords+vec2(0,tmp)));

    vec3 result = ambient+diffuse+specular+text;
    FragColor = vec4(result, 1.0);
}