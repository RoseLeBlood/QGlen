/*
    This file is part of QGlEn.

    QGlEn is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QGlEn is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

    Diese Datei ist Teil von QGlEn.

    QGlEn ist Freie Software: Sie können es unter den Bedingungen
    der GNU General Public License, wie von der Free Software Foundation,
    Version 3 der Lizenz oder (nach Ihrer Wahl) jeder späteren
    veröffentlichten Version, weiterverbreiten und/oder modifizieren.

    QGlEn wird in der Hoffnung, dass es nützlich sein wird, aber
    OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
    Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
    Siehe die GNU General Public License für weitere Details.

    Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
    Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*/
#include "gamewindow.h"

#include <QtCore/QCoreApplication>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>
#include <Qtimer>
#include <QElapsedTimer>
#include <ctime>
#include <QOpenGLDebugLogger>
#include <qdebug.h>

#include "gamestatemanager.h"
#include <QDateTime>
#include <QThread>
#include "shaderlist.h"
#include "debuglog.h"
#include "xmlconfig.h"
#include "openglerror.h"
#include <macros.h>

GameWindow::GameWindow(XmlConfig *pConfig, QWindow *parent)
    : QWindow(parent)
    , m_update_pending(false)
    , m_context(0)
    , m_device(0),
      m_gameStateManager(new GameStateManager(this)),
      m_runTime(0)
{
    OpenGLError::pushErrorHandler(this);

    m_pConfig = pConfig;

    QSurfaceFormat format;
    format.setOption(QSurfaceFormat::DebugContext);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(pConfig->getDepth());
    format.setStencilBufferSize(pConfig->getStencil());
    format.setSamples(pConfig->getSamples());
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    format.setSwapInterval(1);

    setFormat(format);
    setTitle(pConfig->getGameName());

    resize(pConfig->getWight(), pConfig->getHeight());

    setSurfaceType(QWindow::OpenGLSurface);
    m_pTimer = new QElapsedTimer();
    m_pTimer->start();

    m_previous = QDateTime::currentMSecsSinceEpoch();
    m_lag = 0.0;

    auto gamepads = QGamepadManager::instance()->connectedGamepads();
    if (gamepads.isEmpty())
    {
        m_gamepad[0] = new QGamepad(0, this);
        m_numConnectedGamePads = 1;
    }
    else
    {
        for(int i = 0; i < gamepads.length(); i++)
            m_gamepad[i] = new QGamepad( (gamepads.at(i)) , this);
        m_numConnectedGamePads = gamepads.length();
    }

}
GameWindow::~GameWindow()
{
    delete m_device;
    delete m_pTimer;

    OpenGLError::popErrorHandler();
}


void GameWindow::printVersionInformation()
{
  QString glType;
  QString glVersion;
  QString glProfile;

  // Get Version Information
  glType = (m_context->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
  glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

  // Get Profile Information
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
  switch (format().profile())
  {
    CASE(NoProfile);
    CASE(CoreProfile);
    CASE(CompatibilityProfile);
  }
#undef CASE

  // qPrintable() will print our QString w/o quotes around it.
  qInfo() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}
void GameWindow::Initialize()
{
    printVersionInformation();
#ifdef    RAEDEBUG
  m_debugLogger = new QOpenGLDebugLogger(this);
  if (m_debugLogger->initialize())
  {
    qDebug() << "QGLen  Debug Logger" << m_debugLogger << "\n";
    connect(m_debugLogger, SIGNAL(messageLogged(QOpenGLDebugMessage)), this, SLOT(messageLogged(QOpenGLDebugMessage)));
    m_debugLogger->startLogging();
  }
#endif // GL_DEBUG

    ShaderList::instance()->loadShaders(this);
    m_gameStateManager->Initialize();
}
void GameWindow::Move(GamePadState *pStates, int numDevices, double renderTime, double elapsedTime, bool lag)
{
    m_gameStateManager->Move(pStates, numDevices, renderTime, elapsedTime, lag);
}
void GameWindow::Render(double smoothStep)
{
   m_gameStateManager->Render(smoothStep);

}
void GameWindow::SwitchGameState(QString name)
{
    m_gameStateManager->Switch(name);
}
void GameWindow::Input()
{
    for(int i=0; i < m_numConnectedGamePads; i++)
    {
        //int i = 0;
        m_pStates[i].axisLeftX = m_gamepad[i]->axisLeftX();
        m_pStates[i].axisLeftY = m_gamepad[i]->axisLeftY();
        m_pStates[i].axisRightX = m_gamepad[i]->axisRightX();
        m_pStates[i].axisRightY = m_gamepad[i]->axisRightY();
        m_pStates[i].buttonA = m_gamepad[i]->buttonA();
        m_pStates[i].buttonB = m_gamepad[i]->buttonB();
        m_pStates[i].buttonX = m_gamepad[i]->buttonX();
        m_pStates[i].buttonY = m_gamepad[i]->buttonY();
        m_pStates[i].buttonL1 = m_gamepad[i]->buttonL1();
        m_pStates[i].buttonR1 = m_gamepad[i]->buttonR1();
        m_pStates[i].buttonL2 = m_gamepad[i]->buttonL2();
        m_pStates[i].buttonR2 = m_gamepad[i]->buttonR2();
        m_pStates[i].buttonSelect = m_gamepad[i]->buttonSelect();
        m_pStates[i].buttonStart = m_gamepad[i]->buttonStart();
        m_pStates[i].buttonL3 = m_gamepad[i]->buttonL3();
        m_pStates[i].buttonR3 = m_gamepad[i]->buttonR3();
        m_pStates[i].buttonUp = m_gamepad[i]->buttonUp();
        m_pStates[i].buttonDown = m_gamepad[i]->buttonDown();
        m_pStates[i].buttonLeft = m_gamepad[i]->buttonLeft();
        m_pStates[i].buttonRight = m_gamepad[i]->buttonRight();
        m_pStates[i].buttonCenter = m_gamepad[i]->buttonCenter();
        m_pStates[i].buttonGuide = m_gamepad[i]->buttonGuide();
    }
    if( m_pStates[0].buttonY == true)
        this->close();
}


void GameWindow::renderIntern()
{
    qint64 current =  QDateTime::currentMSecsSinceEpoch();
    qint64 elapsed = current - m_previous;

    m_previous = current;
    m_lag += elapsed;


    Input();
    Move(m_pStates, m_numConnectedGamePads, m_runTime, elapsed, false);
    while (m_lag >= MS_PER_UPDATE)
    {
        Move(m_pStates, m_numConnectedGamePads, m_runTime, elapsed, true);
        m_lag -= MS_PER_UPDATE;
    }

    Render(m_lag / MS_PER_UPDATE);
    m_context->swapBuffers(this);

    m_runTime += elapsed;
}


bool GameWindow::event(QEvent *event)
{
    if (event->type() == OpenGLError::type())
    {
        errorEventGL(static_cast<OpenGLError*>(event));
        return true;
    }
    switch (event->type()) {
    case QEvent::UpdateRequest:
        m_update_pending = false;
        renderEvent();
        return true;
    default:
        return QWindow::event(event);
    }
}
void GameWindow::errorEventGL(OpenGLError *event)
{
  qFatal("%s::%s => Returned an error!", event->callerName(), event->functionName());
}

void GameWindow::exposeEvent(QExposeEvent *event)
{
    Q_UNUSED(event);

    if (isExposed())
    {
        renderEvent();
    }
}


void GameWindow::renderEvent()
{
    if (!isExposed())
        return;

    bool needsInitialize = false;

    if (!m_context) {
        m_context = new QOpenGLContext(this);
        m_context->setFormat(requestedFormat());
        m_context->create();


        needsInitialize = true;
    }

    m_context->makeCurrent(this);

    if (needsInitialize) {
        initializeOpenGLFunctions();
        Initialize();
    }

    renderIntern();




    if (!m_update_pending) {
        m_update_pending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}
GamePadState GameWindow::getState(GamePadDevice::GamePadDevice_t id)
{
    if(id < m_numConnectedGamePads )
        { return m_pStates[id]; }

    // TODO: FallBack to KeyBoard and Mouse
    return GamePadState();
}

void GameWindow::SetGameStateManager(GameStateManager* pManager) { m_gameStateManager =  pManager; }
void GameWindow::AddGameState(QString name, GameState* pState) { m_gameStateManager->Add(name, pState); }

void GameWindow::messageLogged(const QOpenGLDebugMessage &msg)
{
  QString error;

  // Format based on severity
  switch (msg.severity())
  {
  case QOpenGLDebugMessage::NotificationSeverity:
    error += "--";
    break;
  case QOpenGLDebugMessage::HighSeverity:
    error += "!!";
    break;
  case QOpenGLDebugMessage::MediumSeverity:
    error += "!~";
    break;
  case QOpenGLDebugMessage::LowSeverity:
    error += "~~";
    break;
  }

  error += " (";

  // Format based on source
#define CASE(c) case QOpenGLDebugMessage::c: error += #c; break
  switch (msg.source())
  {
    CASE(APISource);
    CASE(WindowSystemSource);
    CASE(ShaderCompilerSource);
    CASE(ThirdPartySource);
    CASE(ApplicationSource);
    CASE(OtherSource);
    CASE(InvalidSource);
  }
#undef CASE

  error += " : ";

  // Format based on type
#define CASE(c) case QOpenGLDebugMessage::c: error += #c; break
  switch (msg.type())
  {
    CASE(ErrorType);
    CASE(DeprecatedBehaviorType);
    CASE(UndefinedBehaviorType);
    CASE(PortabilityType);
    CASE(PerformanceType);
    CASE(OtherType);
    CASE(MarkerType);
    CASE(GroupPushType);
    CASE(GroupPopType);
  }
#undef CASE

  error += ")";
  qDebug() << qPrintable(error) << "\n" << qPrintable(msg.message()) << "\n";
}
