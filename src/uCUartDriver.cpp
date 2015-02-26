#include <rosa_dfki_ucontroller/Packet.hpp>
#include <base/Logging.hpp>
#include <rosa_dfki_ucontroller/uCUartDriver.hpp>

namespace rosa_dfki_ucontroller
{

    uCUartDriver::uCUartDriver(): iodrivers_base::Driver(3*Packet::PACKET_SIZE){
    setWriteTimeout(base::Time::fromSeconds(1));
    setReadTimeout(base::Time::fromSeconds(1));    
    }

    Packet uCUartDriver::getPacket(){
        byte buffer[Packet::PACKET_SIZE * 3];
        iodrivers_base::Driver::readPacket(buffer,Packet::PACKET_SIZE * 3);
        Packet packet;
        packet.parse(buffer);
        return packet;
    }

    
    int uCUartDriver::extractPacket(boost::uint8_t const* buffer, size_t buffer_size) const{
        LOG_DEBUG_S << "parsing " << buffer_size << " bytes: " << binary_com(buffer, buffer_size);
        if(buffer_size < Packet::PACKET_SIZE)
            return 0;

        if(buffer[0] != Packet::HEADER1 || buffer[1]!= Packet::HEADER2 || buffer[17]!= Packet::FOOTER){
            LOG_DEBUG_S << " bad message structure, moving to the next byte";
            return -1;
        }

        return Packet::PACKET_SIZE;
    }
}
