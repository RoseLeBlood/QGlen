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
#ifndef QTOPENALDEVICE_H
#define QTOPENALDEVICE_H

#include <QObject>
#include "qopenal_global.h"
#include <QList>
#include <QString>
#include <QDebug>

typedef struct ALCdevice_struct ALCdevice;

namespace MaxAuxiliarySends
{
    enum MaxAuxiliarySends_t
    {
        Default = 0,
        One = 1,
        Two = 2,
        Three = 3,
        Four = 4,
    };
}
class QOPENALSHARED_EXPORT QtOpenalOutputDevice : public QObject
{
    Q_OBJECT
public:
    QtOpenalOutputDevice(ALCdevice* device, QObject *parent = 0);
    explicit QtOpenalOutputDevice(QString name, QObject *parent = 0);

    bool Open();
    bool Close();

    bool IsExtensionPresent(QString extension);
    bool IsEAXSupport();

    bool IsOpen() { return m_bIsOpen; }
    void* GetProcAddress(QString strproc);
    QString getName();
    QString getError();

    MaxAuxiliarySends::MaxAuxiliarySends_t getMaxAuxiliarySends();

     ALCdevice* handle() { return m_pDevice; }

signals:

public slots:
    void OnError(int iALCenum) { qDebug() << "[OpenAl]" << iALCenum;  }
private:
    QString m_strName;
    ALCdevice* m_pDevice;
    bool       m_bIsOpen;
};

#endif // QTOPENALDEVICE_H
