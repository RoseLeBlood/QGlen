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
private:
    void printVersionInformation();

private:
    bool m_update_pending;
};

#endif // GAMEWINDOW_H
