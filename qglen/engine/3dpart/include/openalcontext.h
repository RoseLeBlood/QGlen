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
#ifndef QOPENALSYSTEM_H
#define QOPENALSYSTEM_H

#include "qopenal_global.h"
#include <QObject>
#include "openaloutputdevice.h"

#include "glm/vec3.hpp"

typedef struct ALCcontext_struct ALCcontext;

namespace OpenalContextFormat {
    enum OpenalContextFormat_t
    {
        s16Bit = 0x1402,
        s32Bit = 0x1404,
        Float = 0x1406,
    };

}
namespace OpenalContextChannel
{
    enum OpenalContextChannel_t
    {
        Mono = 0x1500,
        Stereo = 0x1501,
        Quad = 0x1503,
        FivePointOne = 0x1504,
        SevenPointOne = 0x1506,
    };
}
class QOPENALSHARED_EXPORT QtOpenalContext : public QObject
{
   Q_OBJECT
public:
    QtOpenalContext(ALCcontext *context, QObject *parent = 0);
    QtOpenalContext(QtOpenalOutputDevice *pDevice, QObject *parent = 0);

    bool Create(int freq, OpenalContextFormat::OpenalContextFormat_t format,
                OpenalContextChannel::OpenalContextChannel_t channels,
                MaxAuxiliarySends::MaxAuxiliarySends_t efxAuxiliarySends = MaxAuxiliarySends::Default);
    bool Destroy();

    bool IsCurrent();
    void MakeCurrent();
    void Release();

    void ProcessContext();
    void Suspend();
    ALCcontext* handle();

    void setPosition(glm::vec3 position);
    void setVelocity(glm::vec3 velocity);
    void setOrientation(glm::vec3 at, glm::vec3 up = glm::vec3(0,1,0));

    glm::vec3 getPosition()  const  { return m_vecPosition; }
    glm::vec3 getVelocity() const  { return m_vecVelocity; }
    glm::vec3 getAt()  const  { return m_vecAt; }
    glm::vec3 getUp()  const  { return m_vecUp; }

    QtOpenalOutputDevice& getDevice() const { return *m_pDevice; }
    static QtOpenalContext *getCurrentContext();


protected:
    glm::vec3 m_vecPosition;
    glm::vec3 m_vecVelocity;
    glm::vec3 m_vecUp;
    glm::vec3 m_vecAt;
private:
    QtOpenalOutputDevice *m_pDevice;
    ALCcontext* m_pContext;
};

#endif // QOPENALSYSTEM_H
