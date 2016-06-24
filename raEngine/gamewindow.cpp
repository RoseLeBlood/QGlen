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

#include <qdebug.h>

#include "gamestatemanager.h"
#include <QDateTime>
#include <QThread>

GameWindow::GameWindow(QWindow *parent)
    : QWindow(parent)
    , m_update_pending(false)
    , m_context(0)
    , m_device(0),
      m_gameStateManager(new GameStateManager(this)),
      m_runTime(0)
{
    setSurfaceType(QWindow::OpenGLSurface);
    m_pTimer = new QElapsedTimer();
    m_pTimer->start();

    m_previous = QDateTime::currentMSecsSinceEpoch();
    m_lag = 0.0;
    m_pLog = new DebugLog();
    m_pLog->InitLog("raEngineLog.html");
    m_pLog->OK("Log Created");
}
GameWindow::~GameWindow()
{
    delete m_device;
    delete m_pTimer;
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
  qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";

  m_pLog->OK(glType + glVersion + "(" + glProfile + ")");
}
void GameWindow::Initialize()
{
    printVersionInformation();
    m_gameStateManager->Initialize();
}
void GameWindow::Move(double renderTime, double elapsedTime)
{
    m_gameStateManager->Move(renderTime, elapsedTime);
}
void GameWindow::Render(QPainter *painter, double smoothStep)
{
   m_gameStateManager->Render(painter, smoothStep);
}
void GameWindow::SwitchGameState(QString name)
{
    m_gameStateManager->Switch(name);
}
void GameWindow::Input()
{
    m_gameStateManager->Input();
}


void GameWindow::renderIntern()
{
    qint64 current =  QDateTime::currentMSecsSinceEpoch();
    qint64 elapsed = current - m_previous;

    m_previous = current;
    m_lag += elapsed;


    if (!m_device)
        m_device = new QOpenGLPaintDevice;

    Input();

    while (m_lag >= MS_PER_UPDATE)
    {
        Move(m_runTime, elapsed);
        m_lag -= MS_PER_UPDATE;
    }


    m_device->setSize(size());

    QPainter painter(m_device);
    Render(&painter, m_lag / MS_PER_UPDATE);

    m_runTime += elapsed;

    QThread::msleep(m_lag);
}


bool GameWindow::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::UpdateRequest:
        m_update_pending = false;
        renderEvent();
        return true;
    default:
        return QWindow::event(event);
    }
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


    m_context->swapBuffers(this);

    if (!m_update_pending) {
        m_update_pending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}
void GameWindow::SetGameStateManager(GameStateManager* pManager) { m_gameStateManager =  pManager; }
void GameWindow::AddGameState(QString name, GameState* pState) { m_gameStateManager->Add(name, pState); }
