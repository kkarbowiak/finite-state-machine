#include "catch/catch.hpp"

#include "testBasicState.h"

#include "fsm/fsmStateMachine.h"


////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests state_base_basic constructor", "[fsm][state_base_basic][constructor]")
{
    const int id = 10;
    const test::BasicState basic_state(id);

    REQUIRE(basic_state.getID() == id);
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests getID() function", "[fsm][state_base_basic][getID()]")
{
    const int id = 10;
    const test::BasicState basic_state(id);

    REQUIRE(basic_state.getID() == id);
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests setOwner() function", "[fsm][state_base_basic][setOwner()]")
{
    const int id = 1;
    test::BasicState basic_state(id);

    fsm::state_machine<test::Event> state_machine;

    basic_state.setOwner(state_machine);

    REQUIRE(&basic_state.getOwner() == &state_machine);
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests getOwner() function", "[fsm][state_base_basic][getOwner()]")
{
    const int id = 1;
    test::BasicState basic_state(id);

    fsm::state_machine<test::Event> state_machine;

    basic_state.setOwner(state_machine);

    REQUIRE(&basic_state.getOwner() == &state_machine);
}
////////////////////////////////////////////////////////////////////////////////
