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
#ifndef QTOPENALBUFFER_H
#define QTOPENALBUFFER_H

#include "qopenal_global.h"
#include <QString>

class QtOpenalSource;
class QtOpenalContext;

namespace BufferFormat
{
    enum BufferFormat_t
    {
        Mono8 = 0x1100,
        Mono16 = 0x1101,
        Stereo8 = 0x1102,
        Stereo16 = 0x1103
    };
}
class QOPENALSHARED_EXPORT QtOpenalBuffer
{
public:
    QtOpenalBuffer(QString name, unsigned int bufferSize, QtOpenalContext* context );
    QtOpenalBuffer(unsigned int id, QtOpenalContext* context);

    void Delete();

    void BufferData(BufferFormat::BufferFormat_t format, const void *data,
                    size_t size, size_t freq);

    int getBits();
    int getChannels();
    int getFrequenz();
    int getSize();

  //  void* getBuffer() { return m_pBuffer; }

    unsigned int handle() { return m_iId; }

    static bool IsBuffer(const QtOpenalBuffer& buffer);

protected:
    QtOpenalContext *m_pContext;
    QString m_strName;
    //void* m_pBuffer;
    unsigned int m_iId;
};

#endif // QTOPENALBUFFER_H
