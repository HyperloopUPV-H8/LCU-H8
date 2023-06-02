#pragma once
#include "LCU_Pinout/Pinout.hpp"
#include "Socket.hpp"
#include "ServerSocket.hpp"

namespace LCU{

    class TCP{
    public:
        ServerSocket MASTER_CONNECTION;
        TCP() {}
        void init(){
        	MASTER_CONNECTION = ServerSocket(SLAVE_IP, SERVER_PORT);
        }
        void send_to_master(Order& order){
        	MASTER_CONNECTION.send_order(order);
        }
    };
    
}
