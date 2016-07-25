<?xml version="1.0" encoding="UTF-8"?>
<rae>
    <FragmentCode>#version 330 core
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;  
    vec3 emission; 
    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    int enable;
};

in vec3 FragPos;
in vec3 Normal;  
  
out vec4 color;
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform float gamma = 2.2;
void main()
{
    // Ambient
    vec3 ambient = light.ambient * material.ambient;
    
    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec *  material.specular;  
        

    vec3 result = ambient + diffuse + specular + material.emission;
  //  result = pow(result, vec3(1.0 / gamma));
    color = vec4(result, 1.0f);
}</FragmentCode>
    <GeometryCode></GeometryCode>
    <Name>Basic</Name>
    <Version>4097</Version>
    <VertexCode>#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view *  model * vec4(position, 1.0f);
    FragPos = vec3(model * vec4(position, 1.0f));
    Normal = mat3(transpose(inverse(model))) * normal;
}</VertexCode>
</rae>
