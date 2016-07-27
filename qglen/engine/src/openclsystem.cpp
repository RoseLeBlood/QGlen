#include "include/openclsystem.h"
#include "gamewindow.h"
#include "QDebug"

#ifdef WIN32
#include "GL/wglext.h"
#endif

//#ifdef(WIN32)
//#include <qopengln
//#endif

QGLEN_BEGIN

int getCurrentContext()
{
#ifdef WIN32
    return (int)wglGetCurrentContext();
#endif

#ifdef _UNIX_
    return glXGetCurrentContext();
#endif
}



OpenCLSystem::OpenCLSystem()
{

}
bool OpenCLSystem::Initialize(OpenClDeviceType::OpenClDeviceType_t type)
{

    std::vector<cl::Platform> all_platforms;
    cl::Platform::get(&all_platforms);

    if(all_platforms.size()==0){
         qInfo() <<"OpenCL]  No platforms found. Check OpenCL installation!\n";
    }

    cl::Platform default_platform = all_platforms[0];
    std::string buf = default_platform.getInfo<CL_PLATFORM_NAME>();
    qInfo() << "[OpenCL] Using platform: " + QString(buf.c_str());
    //get default device of the default platform
    std::vector<cl::Device> all_devices;

    default_platform.getDevices(type, &all_devices);

    if(all_devices.size()==0){
        qInfo()<<"[OpenCL] No devices found. Check OpenCL installation!\n";
        return false;
    }
   for(int i=0; i < all_devices.size(); i++)
    {
        //
        cl_context_properties lContextProperties[] = {
               // We need to add information about the OpenGL context with
               // which we want to exchange information with the OpenCL context.
               CL_GL_CONTEXT_KHR , (cl_context_properties)getCurrentContext(),
    #ifdef WIN32
               CL_WGL_HDC_KHR , (cl_context_properties) wglGetCurrentDC() ,
    #endif
            #if(MAC)
               CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE , (cl_context_properties) CGLGetShareGroup( CGLGetCurrentContext() ) ,
               #endif
           };
        int lError = 0;

        m_clContext = new cl::Context(all_devices[i],
                    lContextProperties,0,0,&lError);
        if ( lError == CL_SUCCESS )
        {
            //cl::Device default_device=all_devices[i];
            buf = all_devices[i].getInfo<CL_DEVICE_NAME>();
            qInfo()<< "[OpenCL]  Using device: "<< buf.c_str();

            return true;
        }
    }
    return false;
}

bool OpenCLSystem::Destroy()
{

}

QGLEN_END
