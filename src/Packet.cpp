#include <rosa_dfki_ucontroller/Packet.hpp>
#include <bitset>
#include<iostream>

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

float Packet::unsignedMerge(byte const* buffer, const byte LSB, const byte MSB){
    word raw_data = 0;
    raw_data |= static_cast<word>(buffer[LSB]) << 0;
    raw_data |= static_cast<word>(buffer[MSB]) << 8;
    return (float) raw_data;
}

float Packet::signedMerge(byte const* buffer, const byte LSB, const byte MSB){
    word raw_data = 0;
    raw_data |= static_cast<word>(buffer[LSB]) << 0;
    raw_data |= static_cast<word>(buffer[MSB]) << 8;
    return (float) (reinterpret_cast<int16_t &>(raw_data));
}


void Packet::parse(byte const* buffer){
    if( buffer[0]!=HEADER1 || buffer[1]!=HEADER2 || buffer[17]!=FOOTER ) 
        throw InvalidPacket();
    
    //First retrive data, then scale

    pressure  = unsignedMerge(buffer, 2, 3);  
    pressure *= (5.0f/(float)((1<<16) - 1)); 

    angle_x = unsignedMerge(buffer, 10, 11);  
    angle_x *=  (10.0f/(float)((1<<12) - 1));

    angle_y = unsignedMerge(buffer, 12, 13);  
    angle_y *= (10.0f/(float)((1<<12) - 1));
  
    float acceleration_x = signedMerge(buffer, 4, 5);  
    acceleration_x *= (6.0f*g/(float)((1<<15) - 1));

    float acceleration_y = signedMerge(buffer, 6, 7);  
    acceleration_y *= (6.0f*g/(float)((1<<15) - 1));

    float acceleration_z = signedMerge(buffer, 8, 9);  
    acceleration_z *= (6.0f*g/(float)((1<<15) - 1));

    std::bitset<8> switch_water_bitfield(buffer[16]);
    water1 = switch_water_bitfield[0];
    water2 = switch_water_bitfield[1];
    con21 = switch_water_bitfield[4];
    con22 = switch_water_bitfield[5];
    con23 = switch_water_bitfield[6];
    con31 = switch_water_bitfield[7];
    
    acceleration = base::Vector3d(acceleration_x, acceleration_y, acceleration_z);

}
