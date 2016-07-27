#ifndef OPENCLSYSTEM_H
#define OPENCLSYSTEM_H

#include "raengine_global.h"
#include <CL/cl.hpp>
#include <CL/cl_gl.h>

#include "QVector"

QGLEN_BEGIN

class GameWindow;

namespace OpenClDeviceType {
    enum OpenClDeviceType_t
    {
       Cpu = CL_DEVICE_TYPE_CPU,
       Gpu = CL_DEVICE_TYPE_GPU,
       Accelerator = CL_DEVICE_TYPE_ACCELERATOR,

       Default = Gpu | Accelerator
    };
}
class RAENGINESHARED_EXPORT OpenCLSystem
{
public:
    OpenCLSystem();

    virtual bool Initialize(OpenClDeviceType::OpenClDeviceType_t type);
    virtual bool Destroy() ;

    cl::Context* getOpenCLContext() { return m_clContext; }
protected:
    cl::Context* m_clContext;
};

QGLEN_END
#endif // OPENCLSYSTEM_H
