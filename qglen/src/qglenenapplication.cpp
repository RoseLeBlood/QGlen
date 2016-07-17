#include "qglenenapplication.h"
#include <QDir>
#include <QCoreApplication>
#include <debuglog.h>

void myMessageOutput(QtMsgType type, const QMessageLogContext &, const QString & str)
{
    //in this function, you can write the message to any stream!
    switch (type) {
    case QtDebugMsg:
        qglen::DebugLog::instance()->ok(str);
        break;
    case QtWarningMsg:
        qglen::DebugLog::instance()->warning(str);
        break;
    case QtCriticalMsg:
        qglen::DebugLog::instance()->error(str);
        break;
    case QtInfoMsg:
        qglen::DebugLog::instance()->info(str);
        break;
    case QtFatalMsg:
        qglen::DebugLog::instance()->error(str);
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
    shader->setVertexShaderCode("in vec3 position;\n"
                                "in vec3 color;\n"
                                "out vec4 vColor;\n"
                                "uniform highp mat4 matCamera;\n"
                                "void main() {\n"
                                "   gl_Position = matCamera * vec4(position, 1.0);\n"
                                "   vColor = vec4(color, 1.0);\n"
                                "}\n");
    shader->setFragmentShaderCode("in highp vec4 vColor;\n"
                                  "out highp vec4 fColor;\n"
                                  "void main() {\n"
                                  "   fColor = vColor;\n"
                                  "}\n");
    shader->setGeometryShaderCode("");
    shader->setName("Basic");

    qglen::XmlConfigReader::instance()->saveShader(shader);
    delete shader;

    qglen::XmlConfigReader::instance()->saveConfig(qglen::XmlConfigReader::instance()->getConfig());


   m_pConfig = qglen::XmlConfigReader::instance()->getConfig();
}



