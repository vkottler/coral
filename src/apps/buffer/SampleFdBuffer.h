#pragma once

#include "common.h"

class SampleFdBuffer
    : public FullDuplexBuffer<SampleFdBuffer, depth, depth, element_t>
{
  public:
    inline void service_tx_impl(TxBuffer *buf)
    {
        (void)buf;
        std::cout << "Serviced TX." << std::endl;
    }

    inline void service_rx_impl(RxBuffer *buf)
    {
        (void)buf;
        std::cout << "Serviced RX." << std::endl;
    }
};
