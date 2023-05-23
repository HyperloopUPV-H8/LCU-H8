#pragma once
#include "ST-LIB.hpp"
#include "LCU_Mode/LCU_Mode.hpp"

namespace LCU{
    template<LCU::MASTER_MODE> class UDP;
    
    template<>
    class UDP<LPU_VALIDATION> {
    public:
    	DatagramSocket BACKEND_CONNECTION{MASTER_IP, UDP_PORT, BACKEND_IP, UDP_PORT};
        UDP() {}
        void send_to_backend(Packet& order){
            BACKEND_CONNECTION.send(order);
        }
    };

    template<>
    class UDP<TESTBENCH_1DOF> {
    public:
    	DatagramSocket BACKEND_CONNECTION{MASTER_IP, UDP_PORT, BACKEND_IP, UDP_PORT};
        UDP() {}
        void send_to_backend(Packet& order){
            BACKEND_CONNECTION.send(order);
        }
    };

    template<>
    class UDP<VEHICLE_1DOF> {
    public:
        DatagramSocket BACKEND_CONNECTION{MASTER_IP, UDP_PORT, BACKEND_IP, UDP_PORT};
        DatagramSocket SLAVE_CONNECTION{MASTER_IP, UDP_PORT, SLAVE_IP, UDP_PORT};
        UDP() {}
        void send_to_backend(Packet& order){
            BACKEND_CONNECTION.send(order);
        }
        void send_to_slave(Packet& order){
            SLAVE_CONNECTION.send(order);
        }
    };

    template<>
    class UDP<VEHICLE_5DOF> {
    public:
    	DatagramSocket BACKEND_CONNECTION{MASTER_IP, UDP_PORT, BACKEND_IP, UDP_PORT};
        DatagramSocket SLAVE_CONNECTION{MASTER_IP, UDP_PORT, SLAVE_IP, UDP_PORT};
        UDP() {}
        void send_to_backend(Packet& order){
            BACKEND_CONNECTION.send(order);
        }
        void send_to_slave(Packet& order){
            SLAVE_CONNECTION.send(order);
        }
    };
}
