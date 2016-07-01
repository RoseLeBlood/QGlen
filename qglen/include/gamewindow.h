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
#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "raengine_global.h"

#include <QtGui/QWindow>
#include <QtGui/QOpenGLFunctions>
#include <xmlconfig.h>
#include <QtGamepad/QGamepadManager>
#include <QtGamepad/QGamepad>

class QTimer;
class QOpenGLContext;
class QOpenGLPaintDevice;
class GameStateManager;
class GameState;
class QElapsedTimer;

#define MS_PER_UPDATE 16

namespace GamePadDevice
{
    enum GamePadDevice_t
    {
        One = 0,
        First = 1,
        Three = 2,
        Four = 3,

        MAX = 4
    };
}
struct RAENGINESHARED_EXPORT GamePadState
{
    double axisLeftX;
    double axisLeftY;
    double axisRightX;
    double axisRightY;
    bool buttonA;
    bool buttonB;
    bool buttonX;
    bool buttonY;
    bool buttonL1;
    bool buttonR1;
    double buttonL2;
    double buttonR2;
    bool buttonSelect;
    bool buttonStart;
    bool buttonL3;
    bool buttonR3;
    bool buttonUp;
    bool buttonDown;
    bool buttonLeft;
    bool buttonRight;
    bool buttonCenter;
    bool buttonGuide;
};
struct RAENGINESHARED_EXPORT GamePadStates;

class RAENGINESHARED_EXPORT GameWindow : public QWindow, public QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit GameWindow( XmlConfig* pConfig, QWindow *parent = 0);
    ~GameWindow();

    virtual void Initialize();
    virtual void Render(double smoothStep);
    virtual void Input();
    virtual void Move(double renderTime, double elapsedTime);

    void SwitchGameState(QString name);

    GamePadState getState(GamePadDevice::GamePadDevice_t id);
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

    XmlConfig           *m_pConfig;
    int                 m_numConnectedGamePads;
    QGamepad            *m_gamepad[GamePadDevice::MAX];
    GamePadState        m_pStates[GamePadDevice::MAX];
private:
    void printVersionInformation();

private:
    bool m_update_pending;
};

#endif // GAMEWINDOW_H
