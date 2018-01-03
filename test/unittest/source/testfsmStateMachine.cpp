#include "catch/catch.hpp"

#include "testBasicState.h"

#include "fsm/fsmStateMachine.h"


////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests state_machine::register_state() function", "[fsm][state_machine][register_state()]")
{
    const int id = 1;
    test::BasicState state(id);
    fsm::state_machine<test::Event> state_machine;

    state_machine.register_state(state);

    REQUIRE(!state.wason_enteringCalled());
    REQUIRE(!state.wason_exitingCalled());
    REQUIRE(!state.wason_eventCalled());
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests state_machine::set_initial_state() function", "[fsm][state_machine][set_initial_state()]")
{
    const int id_one = 1;
    const int id_two = 2;
    test::BasicState state_one(id_one);
    test::BasicState state_two(id_two);
    fsm::state_machine<test::Event> state_machine;

    state_machine.register_state(state_one);
    state_machine.register_state(state_two);
    state_machine.set_initial_state(state_one.get_id());

    REQUIRE(state_one.wason_enteringCalled());
    REQUIRE(!state_one.wason_exitingCalled());
    REQUIRE(!state_one.wason_eventCalled());

    REQUIRE(!state_two.wason_enteringCalled());
    REQUIRE(!state_two.wason_exitingCalled());
    REQUIRE(!state_two.wason_eventCalled());
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests state_machine::jump_to_state() function", "[fsm][state_machine][jump_to_state()]")
{
    const int id_one = 1;
    const int id_two = 2;
    test::BasicState state_one(id_one);
    test::BasicState state_two(id_two);
    fsm::state_machine<test::Event> state_machine;

    state_machine.register_state(state_one);
    state_machine.register_state(state_two);
    state_machine.set_initial_state(state_one.get_id());

    SECTION("Tests jumping back to active state")
    {
        state_one.reset();
        state_two.reset();
        state_machine.jump_to_state(state_one.get_id());

        REQUIRE(state_one.wason_exitingCalled());
        REQUIRE(state_one.wason_enteringCalled());
        REQUIRE(!state_one.wason_eventCalled());

        REQUIRE(!state_two.wason_enteringCalled());
        REQUIRE(!state_two.wason_exitingCalled());
        REQUIRE(!state_two.wason_eventCalled());
    }

    SECTION("Tests jumping to another state")
    {
        state_one.reset();
        state_two.reset();
        state_machine.jump_to_state(state_two.get_id());

        REQUIRE(state_one.wason_exitingCalled());
        REQUIRE(!state_one.wason_enteringCalled());
        REQUIRE(!state_one.wason_eventCalled());

        REQUIRE(state_two.wason_enteringCalled());
        REQUIRE(!state_two.wason_exitingCalled());
        REQUIRE(!state_two.wason_eventCalled());
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests state_machine::jump_to_state_with_event() function", "[fsm][state_machine][jump_to_state_with_event()]")
{
    const int id_one = 1;
    const int id_two = 2;
    test::BasicState state_one(id_one);
    test::BasicState state_two(id_two);
    fsm::state_machine<test::Event> state_machine;

    state_machine.register_state(state_one);
    state_machine.register_state(state_two);
    state_machine.set_initial_state(state_one.get_id());

    const test::Event event_one(10, 100);
    const test::Event event_two(20, 200);

    SECTION("Tests jumping back to active state")
    {
        state_one.reset();
        state_two.reset();
        state_machine.jump_to_state_with_event(state_one.get_id(), event_one);

        REQUIRE(state_one.wason_exitingCalled());
        REQUIRE(state_one.wason_enteringCalled());
        REQUIRE(state_one.wason_eventCalled());
        REQUIRE(state_one.getEvents().size() == 1);
        REQUIRE(state_one.getEvents().front() == event_one);

        REQUIRE(!state_two.wason_enteringCalled());
        REQUIRE(!state_two.wason_exitingCalled());
        REQUIRE(!state_two.wason_eventCalled());
    }

    SECTION("Tests jumping to another state")
    {
        state_one.reset();
        state_two.reset();
        state_machine.jump_to_state_with_event(state_two.get_id(), event_two);

        REQUIRE(state_one.wason_exitingCalled());
        REQUIRE(!state_one.wason_enteringCalled());
        REQUIRE(!state_one.wason_eventCalled());

        REQUIRE(state_two.wason_enteringCalled());
        REQUIRE(!state_two.wason_exitingCalled());
        REQUIRE(state_two.wason_eventCalled());
        REQUIRE(state_two.getEvents().size() == 1);
        REQUIRE(state_two.getEvents().front() == event_two);
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests state_machine::handle_event() function", "[fsm][state_machine][handle_event()]")
{
    const int id = 1;
    test::BasicState state(id);
    fsm::state_machine<test::Event> state_machine;

    state_machine.register_state(state);
    state_machine.set_initial_state(state.get_id());

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
        state_machine.handle_event(*cit);

        REQUIRE(!state.wason_enteringCalled());
        REQUIRE(!state.wason_exitingCalled());
    }

    REQUIRE(state.getEvents() == events);
}
////////////////////////////////////////////////////////////////////////////////
