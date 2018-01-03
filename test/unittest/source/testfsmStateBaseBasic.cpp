#include "catch/catch.hpp"

#include "testBasicState.h"

#include "fsm/fsmStateMachine.h"


////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests state_base_basic constructor", "[fsm][state_base_basic][constructor]")
{
    const int id = 10;
    const test::BasicState basic_state(id);

    REQUIRE(basic_state.get_id() == id);
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests get_id() function", "[fsm][state_base_basic][get_id()]")
{
    const int id = 10;
    const test::BasicState basic_state(id);

    REQUIRE(basic_state.get_id() == id);
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests set_owner() function", "[fsm][state_base_basic][set_owner()]")
{
    const int id = 1;
    test::BasicState basic_state(id);

    fsm::state_machine<test::Event> state_machine;

    basic_state.set_owner(state_machine);

    REQUIRE(&basic_state.get_owner() == &state_machine);
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests get_owner() function", "[fsm][state_base_basic][get_owner()]")
{
    const int id = 1;
    test::BasicState basic_state(id);

    fsm::state_machine<test::Event> state_machine;

    basic_state.set_owner(state_machine);

    REQUIRE(&basic_state.get_owner() == &state_machine);
}
////////////////////////////////////////////////////////////////////////////////
