#include <rosa_dfki_ucontroller/Packet.hpp>
#include <bitset>

using namespace rosa_dfki_ucontroller;

typedef boost::uint16_t word;

Packet::Packet():
    con21(false),
    con22(false),
    con23(false),
    con31(false),
    water1(false),
    water2(false),
    angle_x(0),
    angle_y(0),
    pressure(0)
{
}


void Packet::parse(byte const* buffer){
    if( buffer[0]!=HEADER1 || buffer[1]!=HEADER2 || buffer[17]!=FOOTER ) 
        throw InvalidPacket();
    
    
    word raw_pressure = 0; 
    raw_pressure |= static_cast<word>(buffer[2]) << 0;
    raw_pressure |= static_cast<word>(buffer[3]) << 8; 
    pressure = ((float)raw_pressure) * (5.0f/(float)((1<<16) - 1)); 

    word raw_angle_x = 0; 
    raw_angle_x |= static_cast<word>(buffer[10]) << 0;
    raw_angle_x |= static_cast<word>(buffer[11]) << 8; 
    angle_x = ((float)raw_angle_x) * (10.0f/(float)((1<<12) - 1));

    word raw_angle_y = 0; 
    raw_angle_y |= static_cast<word>(buffer[12]) << 0;
    raw_angle_y |= static_cast<word>(buffer[13]) << 8; 
    angle_y = ((float)raw_angle_y) * (10.0f/(float)((1<<12) - 1));

    std::bitset<8> switch_water_bitfield(buffer[16]);
    water1 = switch_water_bitfield[0];
    water2 = switch_water_bitfield[1];
    con21 = switch_water_bitfield[4];
    con22 = switch_water_bitfield[5];
    con23 = switch_water_bitfield[6];
    con31 = switch_water_bitfield[7];

}
