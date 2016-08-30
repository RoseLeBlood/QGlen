/*"""
    This file is part of QtOpenAl (unoficiale libary)
    Copyright (C) 2013  Anna-Sophia Schröck <annasophia.schroeck@outlook.de>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
"""
*/
#ifndef QTOPENALOUTPUTDEVICES_H
#define QTOPENALOUTPUTDEVICES_H

#include "openaloutputdevice.h"

class QOPENALSHARED_EXPORT QtOpenalOutputDevices
{
private:
    QtOpenalOutputDevices() { }
public:
    QList<QtOpenalOutputDevice*> getDevices();

    static QtOpenalOutputDevices& Instance()
    {
        if(m_pInstance != 0) m_pInstance = new QtOpenalOutputDevices();

        return *m_pInstance;
    }
public slots:
    bool enumDevices(QtOpenalOutputDevice* dev);
private:
    static QtOpenalOutputDevices* m_pInstance;
};


#endif // QTOPENALOUTPUTDEVICES_H
