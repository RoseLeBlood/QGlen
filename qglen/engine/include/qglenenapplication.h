#ifndef QGLENENAPPLICATION_H
#define QGLENENAPPLICATION_H

#include <raengine_global.h>

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

    qglen::Config*  GetConfig() { return m_pConfig; }
private:
    qglen::Config     *m_pConfig;
    qglen::GameWindow   *m_pWindow;

} ;



#endif // QGLENENAPPLICATION_H
