rock_library(rosa_dfki_ucontroller
    SOURCES Packet.cpp uCUartDriver.cpp
    HEADERS Packet.hpp uCUartDriver.hpp
    DEPS_PKGCONFIG iodrivers_base base-lib)


rock_executable(rosa_dfki_ucontroller_bin Main.cpp
    DEPS rosa_dfki_ucontroller)

