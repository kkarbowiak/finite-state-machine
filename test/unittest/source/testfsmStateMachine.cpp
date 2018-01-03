#include "catch/catch.hpp"

#include "testBasicState.h"

#include "fsm/fsmStateMachine.h"


////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests state_machine::registerState() function", "[fsm][state_machine][registerState()]")
{
    const int id = 1;
    test::BasicState state(id);
    fsm::state_machine<test::Event> state_machine;

    state_machine.registerState(state);

    REQUIRE(!state.wasOnEnteringCalled());
    REQUIRE(!state.wasOnExitingCalled());
    REQUIRE(!state.wasOnEventCalled());
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests state_machine::setInitialState() function", "[fsm][state_machine][setInitialState()]")
{
    const int id_one = 1;
    const int id_two = 2;
    test::BasicState state_one(id_one);
    test::BasicState state_two(id_two);
    fsm::state_machine<test::Event> state_machine;

    state_machine.registerState(state_one);
    state_machine.registerState(state_two);
    state_machine.setInitialState(state_one.getID());

    REQUIRE(state_one.wasOnEnteringCalled());
    REQUIRE(!state_one.wasOnExitingCalled());
    REQUIRE(!state_one.wasOnEventCalled());

    REQUIRE(!state_two.wasOnEnteringCalled());
    REQUIRE(!state_two.wasOnExitingCalled());
    REQUIRE(!state_two.wasOnEventCalled());
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests state_machine::jumpToState() function", "[fsm][state_machine][jumpToState()]")
{
    const int id_one = 1;
    const int id_two = 2;
    test::BasicState state_one(id_one);
    test::BasicState state_two(id_two);
    fsm::state_machine<test::Event> state_machine;

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
TEST_CASE("Tests state_machine::jumpToStateWithEvent() function", "[fsm][state_machine][jumpToStateWithEvent()]")
{
    const int id_one = 1;
    const int id_two = 2;
    test::BasicState state_one(id_one);
    test::BasicState state_two(id_two);
    fsm::state_machine<test::Event> state_machine;

    state_machine.registerState(state_one);
    state_machine.registerState(state_two);
    state_machine.setInitialState(state_one.getID());

    const test::Event event_one(10, 100);
    const test::Event event_two(20, 200);

    SECTION("Tests jumping back to active state")
    {
        state_one.reset();
        state_two.reset();
        state_machine.jumpToStateWithEvent(state_one.getID(), event_one);

        REQUIRE(state_one.wasOnExitingCalled());
        REQUIRE(state_one.wasOnEnteringCalled());
        REQUIRE(state_one.wasOnEventCalled());
        REQUIRE(state_one.getEvents().size() == 1);
        REQUIRE(state_one.getEvents().front() == event_one);

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
        REQUIRE(state_two.getEvents().front() == event_two);
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests state_machine::handleEvent() function", "[fsm][state_machine][handleEvent()]")
{
    const int id = 1;
    test::BasicState state(id);
    fsm::state_machine<test::Event> state_machine;

    state_machine.registerState(state);
    state_machine.setInitialState(state.getID());

    const test::Event event_one(1, 10);
    const test::Event event_two(2, 20);
    const test::Event event_three(3, 30);

    state.reset();

    test::BasicState::events_t events;
    events.push_back(event_one);
    events.push_back(event_two);
    events.push_back(event_three);

    for (test::BasicState::events_t::const_iterator cit = events.begin();
         cit != events.end();
         ++cit)
    {
        state_machine.handleEvent(*cit);

        REQUIRE(!state.wasOnEnteringCalled());
        REQUIRE(!state.wasOnExitingCalled());
    }

    REQUIRE(state.getEvents() == events);
}
////////////////////////////////////////////////////////////////////////////////
