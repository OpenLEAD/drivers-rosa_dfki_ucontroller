rock_library(rosa_dfki_ucontroller
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(rosa_dfki_ucontroller_bin Main.cpp
    DEPS rosa_dfki_ucontroller)

