#pragma once
#include <stdint.h>
#include <memory>
#include <vector>

namespace pdp11
{
    struct unibus_signal_lines
    {
        // data transfer
        unsigned int address : 18; // 18 bit address bus
        unsigned int data : 16;
        bool control[2];

        bool master_sync;
        bool slave_sync;
        bool parity_a;
        bool parity_b;
        bool interrupt;

        // priority arbitration
        bool bus_request[4];
        bool bus_grant[4];

        bool non_processor_request; // request use of bus for data transfer
        bool non_processor_grant; // grant use of bus for data transfers
        bool selection_acknowledge; // acknowledge grant
        bool bus_busy;

        // initialisation
        bool initialize;
        bool ac_low;
        bool dc_low;
    };

    class unibus
    {
        public:
            unibus_signal_lines m_signal_lines;
            std::vector<std::shared_ptr<unibus_interface>> m_devices;

            uint8_t read_byte();
            uint16_t read_word();

            void write_byte(uint8_t value);
            void write_word(uint16_t value);

            void add_device(std::shared_ptr<unibus_interface> device);
    };

    class unibus_interface
    {   
        public:

    };
}