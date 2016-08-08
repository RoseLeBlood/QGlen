#ifndef ICONFIGURE_H
#define ICONFIGURE_H

#include "raengine_global.h"

QGLEN_BEGIN

class RAENGINESHARED_EXPORT IConfigure
{
public:
    virtual void readFromConfig(const QJsonObject &json) = 0;
    virtual void writeToConfig(QJsonObject &json) const = 0;

};

QGLEN_END

#endif // ICONFIGURE_H
