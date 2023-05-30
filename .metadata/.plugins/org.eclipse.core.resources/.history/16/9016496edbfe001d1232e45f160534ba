#pragma once
#include "LCU_Mode/LCU_Mode.hpp"
#include "LCU_Pinout/Pinout.hpp"
#include "Socket.hpp"
#include "ServerSocket.hpp"

namespace LCU{

    class TCP{
    public:
        ServerSocket MASTER_CONNECTION{SLAVE_IP, SERVER_PORT};
        TCP() {}
        void send_to_master(Order& order){
        	MASTER_CONNECTION.send_order(order);
        }
    };
    
}
