{
    "FragmentCode": "#version 330 core\nstruct Material {\n    vec3 ambient;\n    vec3 diffuse;\n    vec3 specular;\n    vec3 emission;\n    float shininess;\n};\n\nstruct DirLight {\n    vec3 direction;\n    \n    vec3 ambient;\n    vec3 diffuse;\n    vec3 specular;\n};\n\nstruct PointLight {\n    vec3 position;\n    \n    float constant;\n    float linear;\n    float quadratic;\n    \n    vec3 ambient;\n    vec3 diffuse;\n    vec3 specular;\n    bool enable;\n};\n\n#define NR_POINT_LIGHTS 4\n\nin vec3 FragPos;\nin vec3 Normal;\n\nout vec4 color;\n\nuniform vec3 viewPos;\nuniform DirLight dirLight;\nuniform PointLight pointLights[NR_POINT_LIGHTS];\nuniform Material material;\nuniform float gamma = 2.2;\n\n// Function prototypes\nvec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);\nvec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);\n\nvoid main()\n{    \n    // Properties\n    vec3 norm = normalize(Normal);\n    vec3 viewDir = normalize(viewPos - FragPos);\n    // Phase 1: Directional lighting\n    vec3 result = CalcDirLight(dirLight, norm, viewDir);\n    // Phase 2: Point lights\n    for(int i = 0; i < NR_POINT_LIGHTS; i++)\n        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    \n    // Phase 3: Spot light\n    // result += CalcSpotLight(spotLight, norm, FragPos, viewDir);\n\n    //result = pow(result, vec3(1.0/gamma));\n     color = vec4(result, 1.0f);\n}\n\n// Calculates the color when using a directional light.\nvec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)\n{\n    vec3 lightDir = normalize(-light.direction);\n    // Diffuse shading\n    float diff = max(dot(normal, lightDir), 0.0);\n    // Specular shading\n    vec3 halfwayDir = normalize(lightDir + viewDir);\n    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess );\n    // Combine results\n    vec3 ambient = light.ambient * material.ambient;\n    vec3 diffuse = light.diffuse * diff * material.diffuse;\n    vec3 specular = light.specular * (vec3(0.3) * spec) * material.specular;\n    return (ambient + diffuse + specular);\n}\n\n// Calculates the color when using a point light.\nvec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)\n{\n    if(light.enable == false)\n         return vec3(0,0,0);\n    vec3 lightDir = normalize(light.position - fragPos);\n    // Diffuse shading\n    float diff = max(dot(normal, lightDir), 0.0);\n    // Specular shading\n    vec3 reflectDir = reflect(-lightDir, normal);\n    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);\n    // Attenuation\n    float distance = length(light.position - fragPos);\n    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));\n    // Combine results\n    vec3 ambient = light.ambient * material.ambient;\n    vec3 diffuse = light.diffuse * diff * material.diffuse;\n    vec3 specular = light.specular * spec * material.specular;\n    ambient *= attenuation;\n    diffuse *= attenuation;\n    specular *= attenuation;\n    return (ambient + diffuse + specular);\n}\n",
    "GeometryCode": "",
    "Name": "Basic",
    "VertexCode": "#version 330 core\nlayout (location = 0) in vec3 position;\nlayout (location = 1) in vec3 normal;\n\nout vec3 Normal;\nout vec3 FragPos;\n\nuniform mat4 model;\nuniform mat4 view;\nuniform mat4 projection;\n\nvoid main()\n{\n    gl_Position = projection * view *  model * vec4(position, 1.0f);\n    FragPos = vec3(model * vec4(position, 1.0f));\n    Normal = mat3(transpose(inverse(model))) * normal;\n}"
}