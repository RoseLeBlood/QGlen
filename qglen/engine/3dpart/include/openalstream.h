#ifndef QTOPENALSTREAM_H
#define QTOPENALSTREAM_H

#include <QObject>
#include "qopenal_global.h"
#include "openalbuffer.h"
#include "openalsource.h"
#include "circularbuffer.h"

namespace StreamInfo
{
    enum StreamInfo_t
    {
        Title,   //Track/Work name
        Version, //The version (e.g. remix info)
        Album,   //The collection name to which this track belongs
        TrackNummer, //The track number of this piece
        Artist,
        Performer,
        Copyright,
        License,
        Organization,
        Description,
        Genre,
        Date,
        Location,
        Contact,
        ISRC
    };
}

class QOPENALSHARED_EXPORT QtOpenalStream : public QObject
{
    Q_OBJECT
public:
    QtOpenalStream(QString name, QtOpenalContext *context,  QObject* p = 0,
                   int iNnumBuffer = 3);

    virtual ~QtOpenalStream();

    virtual bool LoadFile(QString strFile);
    virtual bool Play();
    virtual void Release();

    virtual bool IsPlaying();
    virtual bool Update();

    virtual QString getInformation(StreamInfo::StreamInfo_t info) = 0;

    QtOpenalSource * getSource() { return m_pSource; }

protected:
    virtual bool stream(QtOpenalBuffer* buffer, int size = 0);
    QtOpenalBuffer* find(int id);

    void setFormat(unsigned short channels, unsigned short bits, bool rear);
protected:
    QVector<QtOpenalBuffer*> m_pBuffers;
    QtOpenalSource* m_pSource;
    QtOpenalContext *m_pContext;
    unsigned int m_uiFrequency;
    unsigned int m_uiChannels;
    unsigned int m_uuType;
    unsigned int m_uiFormat;
    char* m_pBuffer;

    unsigned int m_iBufferSize;
};

#endif // QTOPENALSTREAM_H
