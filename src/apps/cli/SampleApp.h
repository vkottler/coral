#pragma once

/* internal */
#include "../../io/App.h"

namespace Coral
{

class SampleApp : public App<SampleApp>
{
    using App<SampleApp>::App;

  public:
    inline void init(void)
    {
        /* need to send json message */
        std::cout << "App initialized." << std::endl;
    }

    inline void poll(InputBuffer &input)
    {
        /* need to read json message */
        (void)input;

        /*
        std::cout << "You entered character 0x" << std::setw(2)
                  << std::setfill('0') << std::hex << int(c) << "'"
                  << std::endl;
         */

        std::cout << "Polled." << std::endl;
    }
};

} // namespace Coral
