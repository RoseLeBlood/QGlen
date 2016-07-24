#include "qglenenapplication.h"
#include <QDir>
#include <QCoreApplication>
#include <debuglog.h>

void myMessageOutput(QtMsgType type, const QMessageLogContext &, const QString & str)
{
    QString _str = str;
    _str = _str.replace("\n","<br>");
    //in this function, you can write the message to any stream!
    switch (type) {
    case QtDebugMsg:
        qglen::DebugLog::instance()->ok(_str);
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
    QDir( QCoreApplication::applicationDirPath() ).mkdir(XmlConfigDir);
    QDir( QCoreApplication::applicationDirPath() ).mkdir(XmlShaderDir);

    qglen::DebugLog::instance()->InitLog("qglen_log.html");
    qInstallMessageHandler(myMessageOutput);  //install : set the callback

    qglen::XmlShader* shader = new qglen::XmlShader();
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
                                  "    vec3 specular;  \n"
                                  "    vec3 emission; \n"
                                  "    float shininess;\n"
                                  "}; \n"
                                  "\n"
                                  "struct Light {\n"
                                  "    vec3 position;\n"
                                  "\n"
                                  "    vec3 ambient;\n"
                                  "    vec3 diffuse;\n"
                                  "    vec3 specular;\n"
                                  "};\n"
                                  "\n"
                                  "in vec3 FragPos;\n"
                                  "in vec3 Normal;  \n"
                                  "  \n"
                                  "out vec4 color;\n"
                                  "  \n"
                                  "uniform vec3 viewPos;\n"
                                  "uniform Material material;\n"
                                  "uniform Light light;\n"
                                  "uniform float gamma = 2.2;\n"
                                  "void main()\n"
                                  "{\n"
                                  "    // Ambient\n"
                                  "    vec3 ambient = light.ambient * material.ambient;\n"
                                  "    \n"
                                  "    // Diffuse\n"
                                  "    vec3 norm = normalize(Normal);\n"
                                  "    vec3 lightDir = normalize(light.position - FragPos);\n"
                                  "    float diff = max(dot(norm, lightDir), 0.0);\n"
                                  "    vec3 diffuse = light.diffuse * (diff * material.diffuse);\n"
                                  "    \n"
                                  "    // Specular\n"
                                  "    vec3 viewDir = normalize(viewPos - FragPos);\n"
                                  "    vec3 reflectDir = reflect(-lightDir, norm);  \n"
                                  " \n"
                                  "    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);\n"
                                  "    vec3 specular = light.specular * spec *  material.specular;  \n"
                                  "        \n"
                                  "\n"
                                  "    vec3 result = ambient + diffuse + specular + material.emission;\n"
                                  "  //  result = pow(result, vec3(1.0 / gamma));\n"
                                  "    color = vec4(result, 1.0f);\n"
                                  "}" );
    shader->setGeometryShaderCode("");
    shader->setName("Basic");

    qglen::XmlConfigReader::instance()->saveShader(shader);
    delete shader;

    qglen::XmlConfigReader::instance()->saveConfig(qglen::XmlConfigReader::instance()->getConfig());


   m_pConfig = qglen::XmlConfigReader::instance()->getConfig();
}



