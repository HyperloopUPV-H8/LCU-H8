#pragma once
#include "DatagramSocket.hpp"
#include "LCU_Pinout/Pinout.hpp"

namespace LCU{

    class UDP {
    public:
        DatagramSocket MASTER_CONNECTION;
        UDP() {}
        void init(){
        	MASTER_CONNECTION = DatagramSocket(SLAVE_IP, UDP_PORT, MASTER_IP, UDP_PORT);
        	MASTER_CONNECTION.reconnect();
        }
        void send_to_master(Packet& packet){
        	MASTER_CONNECTION.send(packet);
        }
    };
}
