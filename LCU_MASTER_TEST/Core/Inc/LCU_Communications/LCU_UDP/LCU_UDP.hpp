#pragma once
#include "DatagramSocket.hpp"
#include "LCU_Mode/LCU_Mode.hpp"
#include "LCU_Pinout/Pinout.hpp"

namespace LCU{
    template<LCU::MASTER_MODE> class UDP;
    
    template<>
    class UDP<LPU_VALIDATION> {
    public:
    	DatagramSocket BACKEND_CONNECTION;
        UDP() {}
        void init(){
        	BACKEND_CONNECTION = DatagramSocket(MASTER_IP,UDP_PORT,BACKEND_IP,UDP_PORT);
        	BACKEND_CONNECTION.reconnect();
        }
        void send_to_backend(Packet& packet){
            BACKEND_CONNECTION.send(packet);
        }
    };

    template<>
    class UDP<TESTBENCH_1DOF> {
    public:
    	DatagramSocket BACKEND_CONNECTION;
        UDP() {}
        void init(){
        	BACKEND_CONNECTION = DatagramSocket(MASTER_IP,UDP_PORT,BACKEND_IP,UDP_PORT);
        	BACKEND_CONNECTION.reconnect();
        }
        void send_to_backend(Packet& packet){
            BACKEND_CONNECTION.send(packet);
        }
    };

    template<>
    class UDP<VEHICLE_TESTING> {
    public:
        DatagramSocket BACKEND_CONNECTION;
        DatagramSocket SLAVE_CONNECTION;
        UDP() {}
        void init(){
        	BACKEND_CONNECTION = DatagramSocket(MASTER_IP,UDP_PORT,BACKEND_IP,UDP_PORT);
        	BACKEND_CONNECTION.reconnect();
        	SLAVE_CONNECTION = DatagramSocket(MASTER_IP, UDP_PORT, SLAVE_IP, UDP_PORT);
        	SLAVE_CONNECTION.reconnect();
        }
        void send_to_backend(Packet& packet){
            BACKEND_CONNECTION.send(packet);
        }
        void send_to_slave(Packet& packet){
            SLAVE_CONNECTION.send(packet);
        }
    };

    template<>
    class UDP<VEHICLE_5DOF> {
    public:
    	DatagramSocket BACKEND_CONNECTION;
        DatagramSocket SLAVE_CONNECTION;
        UDP(){}

        void init(){
        	BACKEND_CONNECTION = DatagramSocket(MASTER_IP,UDP_PORT,BACKEND_IP,UDP_PORT);
        	BACKEND_CONNECTION.reconnect();
        	SLAVE_CONNECTION = DatagramSocket(MASTER_IP, UDP_PORT, SLAVE_IP, UDP_PORT);
        	SLAVE_CONNECTION.reconnect();
        }

        void send_to_backend(Packet& packet){
            BACKEND_CONNECTION.send(packet);
        }
        void send_to_slave(Packet& packet){
            SLAVE_CONNECTION.send(packet);
        }
    };
}