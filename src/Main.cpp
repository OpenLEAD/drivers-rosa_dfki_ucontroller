#include <iostream>
#include <rosa_dfki_ucontroller/uCUartDriver.hpp>
#include <raw_io/Digital.hpp>

using namespace rosa_dfki_ucontroller;


int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "usage: " << argv[0] << " DEVICE" <<  std::endl;
        return 1;
    }

    uCUartDriver driver;
    driver.openURI(argv[1]);

    while (true)
    {
        Packet new_packet = driver.getPacket();
         std::cout<< std::boolalpha
            << "Con2.1: " << new_packet.getCon21()
            << "|Con2.2: " << new_packet.getCon22()
            << "|Con2.3: " << new_packet.getCon23()
            << "|Con3.1: " << new_packet.getCon31()
            << "|Water1: " << new_packet.getWater1() 
            << "|Water2: " << new_packet.getWater2() 
            << "|AngleX: " << new_packet.getAngleX() 
            << "|AngleY: " << new_packet.getAngleY() 
            << "|Pressure: " << new_packet.getPressure().toBar()
            << "                                "
            << "\r" << std::flush;

    }

    return 0;
}
