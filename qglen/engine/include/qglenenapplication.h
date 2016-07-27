#ifndef QGLENENAPPLICATION_H
#define QGLENENAPPLICATION_H

#include <raengine_global.h>
#include <CL/cl.hpp>


#include <xmlconfig.h>
#include <gamewindow.h>
#include <QApplication>

class RAENGINESHARED_EXPORT QGlenEnApplication : public QApplication
{
public:
    QGlenEnApplication(int argc, char *argv[]);

    template <class G> int Play(QString gameName)
    {
        m_pConfig->setGameName(gameName);
        m_pWindow = new G(m_pConfig);
        if(m_pWindow != 0)
        {
            m_pWindow->show();
            return exec();
        }
        return -1;
    }

    qglen::XmlConfig*  GetConfig() { return m_pConfig; }
private:
    qglen::XmlConfig     *m_pConfig;
    qglen::GameWindow   *m_pWindow;

} ;



#endif // QGLENENAPPLICATION_H
