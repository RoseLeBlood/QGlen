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
#ifndef DREIECKGAMESTATE_H
#define DREIECKGAMESTATE_H

#include "gamestate.h"
#include "dreieckobject.h"

class DreieckGameState : public GameState
{
public:
    DreieckGameState(GameWindow *wnd);

    virtual bool Switch(bool , GameState* ) { return true; }

    virtual bool Render(QPainter *painter, double smoothStep)
    {
        GetGameWindow()->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        return GameState::Render(painter, smoothStep);
    }

    virtual bool Move(double renderTime, double elapsedTime)
    {
        const qreal retinaScale = GetGameWindow()->devicePixelRatio();
        GetGameWindow()->glViewport(0, 0, GetGameWindow()->width() * retinaScale, GetGameWindow()->height() * retinaScale);

        return GameState::Move(renderTime, elapsedTime);
    }
    bool Initialize();
};

#endif // DREIECKGAMESTATE_H