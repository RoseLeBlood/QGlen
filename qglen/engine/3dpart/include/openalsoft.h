#ifndef OPENALSOFT_H
#define OPENALSOFT_H

#include <AL/alext.h>

    extern LPALBUFFERSAMPLESSOFT alBufferSamplesSOFT;
    extern LPALISBUFFERFORMATSUPPORTEDSOFT alIsBufferFormatSupportedSOFT;

    extern LPALSOURCEDSOFT alSourcedSOFT;
    extern LPALSOURCE3DSOFT alSource3dSOFT;
    extern LPALSOURCEDVSOFT alSourcedvSOFT;
    extern LPALGETSOURCEDSOFT alGetSourcedSOFT;
    extern LPALGETSOURCE3DSOFT alGetSource3dSOFT;
    extern LPALGETSOURCEDVSOFT alGetSourcedvSOFT;
    extern LPALSOURCEI64SOFT alSourcei64SOFT;
   extern  LPALSOURCE3I64SOFT alSource3i64SOFT;
    extern LPALSOURCEI64VSOFT alSourcei64vSOFT;
    extern LPALGETSOURCEI64SOFT alGetSourcei64SOFT;
   extern  LPALGETSOURCE3I64SOFT alGetSource3i64SOFT;
    extern LPALGETSOURCEI64VSOFT alGetSourcei64vSOFT;

    extern void alCreateHelpers();

#endif // OPENALSOFT_H
