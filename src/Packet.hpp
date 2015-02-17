#ifndef ROSA_DFKI_UCONTROLLER_PACKET_HPP
#define ROSA_DFKI_UCONTROLLER_PACKET_HPP

#include <boost/cstdint.hpp>
#include <base/Pressure.hpp>
#include <base/Eigen.hpp>
#include <stdexcept>

namespace rosa_dfki_ucontroller
{

    typedef boost::uint8_t byte;
    
    struct InvalidPacket: public std::runtime_error
    {
        InvalidPacket() : std::runtime_error("invalid header or footer in received message"){};
    };
    
    class Packet
    {
    public:
        static const int PACKET_SIZE = 18;
        static const byte HEADER1 = 'D';
        static const byte HEADER2 = ':';
        static const byte FOOTER = '\n';

        bool getCon21() const {return con21;};
        bool getCon22() const {return con22;};
        bool getCon23() const {return con23;};
        bool getCon31() const {return con31;};
        bool getWater1() const {return water1;};
        bool getWater2() const {return water2;};
        float getAngleX() const {return angle_x;};
        float getAngleY() const {return angle_y;};
        base::Pressure getPressure() const {return base::Pressure::fromBar(pressure);};
        base::Vector3d getAcceleration() const {return acceleration;}

        Packet();
        void parse(byte const* buffer);
    protected:
        float unsignedMerge(byte const* buffer, const byte LSB, const byte MSB);
        float signedMerge(byte const* buffer, const byte LSB, const byte MSB);

        bool con21, con22, con23, con31, water1, water2;
        float angle_x, angle_y, pressure;
        base::Vector3d acceleration;

    };


}

#endif // ROSA_DFKI_UCONTROLLER_PACKET_HPP
