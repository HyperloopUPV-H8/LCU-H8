#pragma once
#include "LCU_Mode/LCU_Mode.hpp"

namespace LCU{
    template<MASTER_MODE> class TCP;

    template<>
    class TCP<LPU_VALIDATION> {
    public:
        ServerSocket BACKEND_CONNECTION{MASTER_IP, SERVER_PORT};
        TCP() {}
    };

    template<>
    class TCP<TESTBENCH_1DOF> {
    public:
        ServerSocket BACKEND_CONNECTION{MASTER_IP, SERVER_PORT};
        TCP() {}
    };

    template<>
    class TCP<VEHICLE_1DOF> {
    public:
        ServerSocket BACKEND_CONNECTION{MASTER_IP, SERVER_PORT};
        Socket SLAVE_CONNECTION{MASTER_IP, CLIENT_PORT, SLAVE_IP, SERVER_PORT};
        TCP() {}
        void send_to_slave(Order& order){
            SLAVE_CONNECTION.send_order(order);
        }
    };

    template<>
    class TCP<VEHICLE_5DOF> {
    public:
        ServerSocket BACKEND_CONNECTION{MASTER_IP, SERVER_PORT};
        Socket SLAVE_CONNECTION{MASTER_IP, CLIENT_PORT, SLAVE_IP, SERVER_PORT};
        TCP() {}
        void send_to_slave(Order& order){
            SLAVE_CONNECTION.send_order(order);
        }
    };
    
}
