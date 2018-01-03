#include "catch/catch.hpp"

#include "testBasicState.h"

#include "fsm/fsmStateMachine.h"


////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests StateBaseBasic constructor", "[fsm][StateBaseBasic][constructor]")
{
    const int id = 10;
    const test::BasicState basic_state(id);

    REQUIRE(basic_state.getID() == id);
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests getID() function", "[fsm][StateBaseBasic][getID()]")
{
    const int id = 10;
    const test::BasicState basic_state(id);

    REQUIRE(basic_state.getID() == id);
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests setOwner() function", "[fsm][StateBaseBasic][setOwner()]")
{
    const int id = 1;
    test::BasicState basic_state(id);

    fsm::StateMachine<test::Event> state_machine;

    basic_state.setOwner(state_machine);

    REQUIRE(&basic_state.getOwner() == &state_machine);
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests getOwner() function", "[fsm][StateBaseBasic][getOwner()]")
{
    const int id = 1;
    test::BasicState basic_state(id);

    fsm::StateMachine<test::Event> state_machine;

    basic_state.setOwner(state_machine);

    REQUIRE(&basic_state.getOwner() == &state_machine);
}
////////////////////////////////////////////////////////////////////////////////
