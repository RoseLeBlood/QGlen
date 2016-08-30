#include "qglenenapplication.h"
#include <QDir>
#include <QCoreApplication>
#include <debuglog.h>
#include <iostream>
#include "shaderlist.h"
#include <QDebug>
#include "jsonshader.h"

void myMessageOutput(QtMsgType type, const QMessageLogContext &, const QString & str)
{
    QString _str = str;
    _str = _str.replace("\n","<br>");
    //in this function, you can write the message to any stream!
    switch (type) {
    case QtDebugMsg:
        qglen::DebugLog::instance()->info(_str);
        break;
    case QtWarningMsg:
        qglen::DebugLog::instance()->warning(_str);
        break;
    case QtCriticalMsg:
        qglen::DebugLog::instance()->error(_str);
        break;
    case QtInfoMsg:
        qglen::DebugLog::instance()->info(_str);
        break;
    case QtFatalMsg:
        qglen::DebugLog::instance()->error(_str);
        abort();
    }
}
QGlenEnApplication::QGlenEnApplication(int argc, char *argv[]) : QApplication(argc, argv)
{
    //m_clContext = NULL;

    QDir( QCoreApplication::applicationDirPath() ).mkdir(XmlConfigDir);
    QDir( QCoreApplication::applicationDirPath() ).mkdir(XmlShaderDir);

    qglen::DebugLog::instance()->InitLog("qglen_log.html");
    qInstallMessageHandler(myMessageOutput);  //install : set the callback

    qglen::JSonShader* shader = new qglen::JSonShader();
    shader->setVertexShaderCode("#version 330 core\n"
                                "layout (location = 0) in vec3 position;\n"
                                "layout (location = 1) in vec3 normal;\n"
                                "\n"
                                "out vec3 Normal;\n"
                                "out vec3 FragPos;\n"
                                "\n"
                                "uniform mat4 model;\n"
                                "uniform mat4 view;\n"
                                "uniform mat4 projection;\n"
                                "\n"
                                "void main()\n"
                                "{\n"
                                "    gl_Position = projection * view *  model * vec4(position, 1.0f);\n"
                                "    FragPos = vec3(model * vec4(position, 1.0f));\n"
                                "    Normal = mat3(transpose(inverse(model))) * normal;\n"
                                "}");
    shader->setFragmentShaderCode("#version 330 core\n"
                                  "struct Material {\n"
                                  "    vec3 ambient;\n"
                                  "    vec3 diffuse;\n"
                                  "    vec3 specular;\n"
                                  "    vec3 emission;\n"
                                  "    float shininess;\n"
                                  "};\n"
                                  "\n"
                                  "struct DirLight {\n"
                                  "    vec3 direction;\n"
                                  "    \n"
                                  "    vec3 ambient;\n"
                                  "    vec3 diffuse;\n"
                                  "    vec3 specular;\n"
                                  "};\n"
                                  "\n"
                                  "struct PointLight {\n"
                                  "    vec3 position;\n"
                                  "    \n"
                                  "    float constant;\n"
                                  "    float linear;\n"
                                  "    float quadratic;\n"
                                  "    \n"
                                  "    vec3 ambient;\n"
                                  "    vec3 diffuse;\n"
                                  "    vec3 specular;\n"
                                  "    bool enable;\n"
                                  "};\n"
                                  "\n"
                                  "#define NR_POINT_LIGHTS 4\n"
                                  "\n"
                                  "in vec3 FragPos;\n"
                                  "in vec3 Normal;\n"
                                  "\n"
                                  "out vec4 color;\n"
                                  "\n"
                                  "uniform vec3 viewPos;\n"
                                  "uniform DirLight dirLight;\n"
                                  "uniform PointLight pointLights[NR_POINT_LIGHTS];\n"
                                  "uniform Material material;\n"
                                  "uniform float gamma = 2.2;\n"
                                  "\n"
                                  "// Function prototypes\n"
                                  "vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);\n"
                                  "vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);\n"
                                  "\n"
                                  "void main()\n"
                                  "{    \n"
                                  "    // Properties\n"
                                  "    vec3 norm = normalize(Normal);\n"
                                  "    vec3 viewDir = normalize(viewPos - FragPos);\n"
                                  "    // Phase 1: Directional lighting\n"
                                  "    vec3 result = CalcDirLight(dirLight, norm, viewDir);\n"
                                  "    // Phase 2: Point lights\n"
                                  "    for(int i = 0; i < NR_POINT_LIGHTS; i++)\n"
                                  "        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    \n"
                                  "    // Phase 3: Spot light\n"
                                  "    // result += CalcSpotLight(spotLight, norm, FragPos, viewDir);\n"
                                  "\n"
                                  "    //result = pow(result, vec3(1.0/gamma));\n"
                                  "     color = vec4(result, 1.0f);\n"
                                  "}\n"
                                  "\n"
                                  "// Calculates the color when using a directional light.\n"
                                  "vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)\n"
                                  "{\n"
                                  "    vec3 lightDir = normalize(-light.direction);\n"
                                  "    // Diffuse shading\n"
                                  "    float diff = max(dot(normal, lightDir), 0.0);\n"
                                  "    // Specular shading\n"
                                  "    vec3 halfwayDir = normalize(lightDir + viewDir);\n"
                                  "    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess );\n"
                                  "    // Combine results\n"
                                  "    vec3 ambient = light.ambient * material.ambient;\n"
                                  "    vec3 diffuse = light.diffuse * diff * material.diffuse;\n"
                                  "    vec3 specular = light.specular * (vec3(0.3) * spec) * material.specular;\n"
                                  "    return (ambient + diffuse + specular);\n"
                                  "}\n"
                                  "\n"
                                  "// Calculates the color when using a point light.\n"
                                  "vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)\n"
                                  "{\n"
                                  "    if(light.enable == false)\n"
                                  "         return vec3(0,0,0);\n"
                                  "    vec3 lightDir = normalize(light.position - fragPos);\n"
                                  "    // Diffuse shading\n"
                                  "    float diff = max(dot(normal, lightDir), 0.0);\n"
                                  "    // Specular shading\n"
                                  "    vec3 reflectDir = reflect(-lightDir, normal);\n"
                                  "    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);\n"
                                  "    // Attenuation\n"
                                  "    float distance = length(light.position - fragPos);\n"
                                  "    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));\n"
                                  "    // Combine results\n"
                                  "    vec3 ambient = light.ambient * material.ambient;\n"
                                  "    vec3 diffuse = light.diffuse * diff * material.diffuse;\n"
                                  "    vec3 specular = light.specular * spec * material.specular;\n"
                                  "    ambient *= attenuation;\n"
                                  "    diffuse *= attenuation;\n"
                                  "    specular *= attenuation;\n"
                                  "    return (ambient + diffuse + specular);\n"
                                  "}\n");
    shader->setGeometryShaderCode("");
    shader->setName("Basic");

    qglen::JSonShaderLoader::instance()->setShader(shader);
    delete shader;

    qglen::ConfigLoader::instance()->setConfig(new qglen::Config());

    m_pConfig = qglen::ConfigLoader::instance()->getConfig();
}



