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
#include "trianglewindow.h"
#include <QApplication>
#include "qglen.h"
#include <gamebatch.h>
#include "qglenenapplication.h"

TriangleWindow::TriangleWindow(qglen::Config *cfg) : qglen::GameWindow(cfg)
{
    m_pBatch = new qglen::gameBatch(this);
    this->AddGameState("Dreieck_test", new DreieckGameState(this));

}
int main(int argc, char *argv[])
{

    QGlenEnApplication app(argc, argv);

    return app.Play<TriangleWindow>("OpenGLDEmo");
    /*qglen::XmlConfig *cfg = qglen::startQGlEn();

    TriangleWindow window(cfg);
    window.show();

    return qglen::endQGlEn(app.exec());*/
}
