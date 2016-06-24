#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "raengine_global.h"

#include <QtGui/QWindow>
#include <QtGui/QOpenGLFunctions>
#include "debuglog.h"

class QTimer;
class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;
class GameStateManager;
class GameState;
class QElapsedTimer;

#define MS_PER_UPDATE 16

class RAENGINESHARED_EXPORT GameWindow : public QWindow, public QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit GameWindow(QWindow *parent = 0);
    ~GameWindow();

    virtual void Initialize();
    virtual void Render(QPainter *painter, double smoothStep);
    virtual void Input();
    virtual void Move(double renderTime, double elapsedTime);

    void SwitchGameState(QString name);


public slots:
    void renderEvent();
protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void renderIntern();
    void exposeEvent(QExposeEvent *event) Q_DECL_OVERRIDE;

     void SetGameStateManager(GameStateManager* pManager);
     void AddGameState(QString name, GameState* pState);
protected:
    QOpenGLContext      *m_context;
    QOpenGLPaintDevice  *m_device;
    GameStateManager    *m_gameStateManager;
    QElapsedTimer       *m_pTimer;
    qint64              m_runTime;

    qint64              m_previous;
    qint64              m_lag;
    DebugLog            *m_pLog;
private:
    void printVersionInformation();

private:
    bool m_update_pending;
};

#endif // GAMEWINDOW_H
