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
#ifndef QTOPENALSOURCE_H
#define QTOPENALSOURCE_H

#include "openalcontext.h"
#include "QVector"

class QtOpenalBuffer;

namespace SourceState
{
    enum SourceState_t
    {
        Initial = 0x1011,
        Playing = 0x1012,
        Paused  = 0x1013,
        Stopped = 0x1014
    };
}
class QOPENALSHARED_EXPORT QtOpenalSource
{
public:
    QtOpenalSource();
    QtOpenalSource(QString name, QtOpenalContext *context);
    QtOpenalSource(QtOpenalSource& other);

    virtual ~QtOpenalSource();

    void Bind(QtOpenalBuffer* buffer);
    void Play();
    void Stop();
    void Pause();
    void Rewind();

    void QueueBuffers(QVector<QtOpenalBuffer*> buffers);
    void QueueBuffers(unsigned int size, const unsigned int *id);
    void UnqueueBuffers(QVector<QtOpenalBuffer*> buffers);
    void UnqueueBuffers(unsigned int size, unsigned int *id);

    void setPosition(glm::vec3 position);
    void setVelocity(glm::vec3 velocity);
    void setDirection(glm::vec3 direction);
    void setGain(float gain);
    void setPitch(float pitch);
    void setLooping(bool looping);
    void setMaxDistance(float maxDist);
    void setRollOffFactor(float rollOff);
    void setReferenceDistance(float refDis);
    void setMinGain(float mGain);
    void setMaxGain(float mGain);
    void setConeOuterGain(float cone);
    void setConeInnerAngle(int angle);
    void setConeOuterAngle(int angle);

    glm::vec3 getPosition();
    glm::vec3 getVelocity();
    glm::vec3 getDirection();
    float getGain();
    float getPitch();
    bool getLooping();
    float getMaxDistance();
    float getRollOffFactor();
    float getReferenceDistance();
    float getMinGain();
    float getMaxGain();
    float getConeOuterGain();
    int getConeInnerAngle();
    int getConeOuterAngle();

    double getLatency();
    double getOffsetLastRead();

    unsigned int handle() { return m_iId; }

    SourceState::SourceState_t getState();
private:
    QtOpenalContext *m_pContext;
    QString m_strName;
    unsigned int m_iId;
};

#endif // QTOPENALSOURCE_H
