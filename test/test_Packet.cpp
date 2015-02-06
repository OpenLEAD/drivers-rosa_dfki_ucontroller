#include <boost/test/unit_test.hpp>
#include <iodrivers_base/Driver.hpp>
#include <rosa_dfki_ucontroller/Packet.hpp>
#include <rosa_dfki_ucontroller/uCUartDriver.hpp>

using namespace std;
using namespace rosa_dfki_ucontroller;

namespace boost {
    namespace test_tools {
        template<>
        struct print_log_value< vector<byte> > {
            void operator()( std::ostream& out, vector<byte> const& buffer)
            {
                out << iodrivers_base::Driver::binary_com(&buffer[0], buffer.size());
            }
        };
    }
}

byte marshalled[18] = { 0x44, 0x3A, //HEADERS
                        0x0F, 0xDA, //Pressure (4.259021897 bar)
                        0x00, 0x00, //Acceleration X 
                        0x00, 0x00, //Acceleration Y
                        0x00, 0x00, //Acceleration Z
                        0x74, 0x05, //Angle X (3.409035409 V)
                        0x52, 0x0F, //Angle Y (9.577533578 V)
                        0x00, 0x00, //Angle Z
                        0x20, //Switch / Watersense bitfield
                        0x0A }; //FOOTER
Packet packet;

BOOST_AUTO_TEST_CASE(Packet_parse)
{
    packet.parse(marshalled);
}


BOOST_AUTO_TEST_CASE(Packet_getCon21)
{
    BOOST_CHECK(!packet.getCon21());
}

BOOST_AUTO_TEST_CASE(Packet_getCon22)
{
    BOOST_CHECK(packet.getCon22());
}

BOOST_AUTO_TEST_CASE(Packet_getCon23)
{
    BOOST_CHECK(!packet.getCon23());
}

BOOST_AUTO_TEST_CASE(Packet_getCon31)
{
    BOOST_CHECK(!packet.getCon31());
}

BOOST_AUTO_TEST_CASE(Packet_getWater1)
{
    BOOST_CHECK(!packet.getWater1());
}

BOOST_AUTO_TEST_CASE(Packet_getWater2)
{
    BOOST_CHECK(!packet.getWater2());
}

BOOST_AUTO_TEST_CASE(Packet_getAngleX)
{
    BOOST_CHECK_CLOSE(3.409035409f, packet.getAngleX(), 0.0001);
}

BOOST_AUTO_TEST_CASE(Packet_getAngleY)
{
    BOOST_CHECK_CLOSE(9.577533578f, packet.getAngleY(), 0.0001);
}

BOOST_AUTO_TEST_CASE(Packet_getPressure)
{
    BOOST_CHECK_CLOSE(4.259021897f, packet.getPressure().toBar(), 0.0001);
}
