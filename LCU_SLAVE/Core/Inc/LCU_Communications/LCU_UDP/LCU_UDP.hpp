#pragma once
#include "DatagramSocket.hpp"
#include "LCU_Mode/LCU_Mode.hpp"
#include "LCU_Pinout/Pinout.hpp"

namespace LCU{

    class UDP {
    public:
        DatagramSocket MASTER_CONNECTION{SLAVE_IP, UDP_PORT, MASTER_IP, UDP_PORT};
        UDP() {}
        void send_to_master(Packet& order){
        	MASTER_CONNECTION.send(order);
        }
    };
}
