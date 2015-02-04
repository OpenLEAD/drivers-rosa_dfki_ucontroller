#include <boost/test/unit_test.hpp>
#include <rosa_dfki_ucontroller/Dummy.hpp>

using namespace rosa_dfki_ucontroller;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    rosa_dfki_ucontroller::DummyClass dummy;
    dummy.welcome();
}
