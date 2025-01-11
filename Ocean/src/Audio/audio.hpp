#pragma once

#include <phonon.h>

namespace sonar{
    class steamaudio{
        public:
            static steamaudio* instance(IPLuint32 steamversion,IPLSIMDLevel smidlevel,IPLAllocateFunction allocation , IPLFreeFunction freemem);
        

            static steamaudio* struct_pointer;

            static IPLContext* context;
            static IPLContextSettings settings;


        private:
            //makes the instance
            steamaudio(IPLuint32 steamversion,IPLSIMDLevel smidlevel,IPLAllocateFunction allocation , IPLFreeFunction freemem);
            ~steamaudio();


            //Do not implement
            steamaudio(const steamaudio&);
            steamaudio& operator=(const steamaudio&);

    };
};