#include "catch/catch.hpp"

#include "testState.h"


////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests state_base constructor", "[fsm][state_base][constructor]")
{
    const int id = 10;
    const test::State state(id);

    REQUIRE(state.getID() == id);
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests state_base::jumpToState() function", "[fsm][state_base][jumpToState()]")
{
    const int id_one = 1;
    const int id_two = 2;
    test::State state_one(id_one);
    test::State state_two(id_two);
    fsm::StateMachine<test::EventBase> state_machine;

    state_machine.registerState(state_one);
    state_machine.registerState(state_two);
    state_machine.setInitialState(state_one.getID());

    SECTION("Tests jumping back to active state")
    {
        state_one.reset();
        state_two.reset();
        state_machine.jumpToState(state_one.getID());

        REQUIRE(state_one.wasOnExitingCalled());
        REQUIRE(state_one.wasOnEnteringCalled());
        REQUIRE(!state_one.wasOnEventCalled());

        REQUIRE(!state_two.wasOnEnteringCalled());
        REQUIRE(!state_two.wasOnExitingCalled());
        REQUIRE(!state_two.wasOnEventCalled());
    }

    SECTION("Tests jumping to another state")
    {
        state_one.reset();
        state_two.reset();
        state_machine.jumpToState(state_two.getID());

        REQUIRE(state_one.wasOnExitingCalled());
        REQUIRE(!state_one.wasOnEnteringCalled());
        REQUIRE(!state_one.wasOnEventCalled());

        REQUIRE(state_two.wasOnEnteringCalled());
        REQUIRE(!state_two.wasOnExitingCalled());
        REQUIRE(!state_two.wasOnEventCalled());
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests state_base::jumpToStateWithEvent() function", "[fsm][state_base][jumpToStateWithEvent()]")
{
    const int id_one = 1;
    const int id_two = 2;
    test::State state_one(id_one);
    test::State state_two(id_two);
    fsm::StateMachine<test::EventBase> state_machine;

    state_machine.registerState(state_one);
    state_machine.registerState(state_two);
    state_machine.setInitialState(state_one.getID());

    const test::EventBase event_one(10, 100);
    const test::EventBase event_two(20, 200);

    SECTION("Tests jumping back to active state")
    {
        state_one.reset();
        state_two.reset();
        state_machine.jumpToStateWithEvent(state_one.getID(), event_one);

        REQUIRE(state_one.wasOnExitingCalled());
        REQUIRE(state_one.wasOnEnteringCalled());
        REQUIRE(state_one.wasOnEventCalled());
        REQUIRE(state_one.getEvents().size() == 1);
        REQUIRE(state_one.getEvents().front() == event_one.getValue());

        REQUIRE(!state_two.wasOnEnteringCalled());
        REQUIRE(!state_two.wasOnExitingCalled());
        REQUIRE(!state_two.wasOnEventCalled());
    }

    SECTION("Tests jumping to another state")
    {
        state_one.reset();
        state_two.reset();
        state_machine.jumpToStateWithEvent(state_two.getID(), event_two);

        REQUIRE(state_one.wasOnExitingCalled());
        REQUIRE(!state_one.wasOnEnteringCalled());
        REQUIRE(!state_one.wasOnEventCalled());

        REQUIRE(state_two.wasOnEnteringCalled());
        REQUIRE(!state_two.wasOnExitingCalled());
        REQUIRE(state_two.wasOnEventCalled());
        REQUIRE(state_two.getEvents().size() == 1);
        REQUIRE(state_two.getEvents().front() == event_two.getValue());
    }
}
////////////////////////////////////////////////////////////////////////////////
