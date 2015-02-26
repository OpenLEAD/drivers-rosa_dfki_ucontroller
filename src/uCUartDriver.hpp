#ifndef ROSA_DFKI_UCONTROLLER_UCUARTDRIVER_HPP
#define ROSA_DFKI_UCONTROLLER_UCUARTDRIVER_HPP


#include <iodrivers_base/Driver.hpp>
#include <rosa_dfki_ucontroller/Packet.hpp>


namespace rosa_dfki_ucontroller
{
	class uCUartDriver: public iodrivers_base::Driver 
	{
	public: 
            uCUartDriver();
            Packet getPacket();


        protected:
            int extractPacket(boost::uint8_t const* buffer, size_t buffer_size) const;
	};

} // end namespace rosa_dfki_ucontroller

#endif // ROSA_DFKI_UCONTROLLER_UCUARTDRIVER_HPP
