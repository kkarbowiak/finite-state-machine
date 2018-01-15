#include "catch/catch.hpp"

#include "testState.h"


////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests state_base constructor", "[fsm][state_base][constructor]")
{
    const int id = 10;
    const test::State state(id);

    REQUIRE(state.get_id() == id);
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests state_base::jump_to_state() function", "[fsm][state_base][jump_to_state()]")
{
    const int id_one = 1;
    const int id_two = 2;
    test::State state_one(id_one);
    test::State state_two(id_two);
    fsm::state_machine<test::EventBase> state_machine;

    state_machine.register_state(state_one);
    state_machine.register_state(state_two);
    state_machine.set_initial_state(state_one.get_id());

    SECTION("Tests jumping back to active state")
    {
        state_one.reset();
        state_two.reset();
        state_machine.jump_to_state(state_one.get_id());

        REQUIRE(state_one.was_on_exiting_called());
        REQUIRE(state_one.was_on_entering_called());
        REQUIRE(!state_one.was_on_event_called());

        REQUIRE(!state_two.was_on_entering_called());
        REQUIRE(!state_two.was_on_exiting_called());
        REQUIRE(!state_two.was_on_event_called());
    }

    SECTION("Tests jumping to another state")
    {
        state_one.reset();
        state_two.reset();
        state_machine.jump_to_state(state_two.get_id());

        REQUIRE(state_one.was_on_exiting_called());
        REQUIRE(!state_one.was_on_entering_called());
        REQUIRE(!state_one.was_on_event_called());

        REQUIRE(state_two.was_on_entering_called());
        REQUIRE(!state_two.was_on_exiting_called());
        REQUIRE(!state_two.was_on_event_called());
    }
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Tests state_base::jump_to_state_with_event() function", "[fsm][state_base][jump_to_state_with_event()]")
{
    const int id_one = 1;
    const int id_two = 2;
    test::State state_one(id_one);
    test::State state_two(id_two);
    fsm::state_machine<test::EventBase> state_machine;

    state_machine.register_state(state_one);
    state_machine.register_state(state_two);
    state_machine.set_initial_state(state_one.get_id());

    const test::EventBase event_one(10, 100);
    const test::EventBase event_two(20, 200);

    SECTION("Tests jumping back to active state")
    {
        state_one.reset();
        state_two.reset();
        state_machine.jump_to_state_with_event(state_one.get_id(), event_one);

        REQUIRE(state_one.was_on_exiting_called());
        REQUIRE(state_one.was_on_entering_called());
        REQUIRE(state_one.was_on_event_called());
        REQUIRE(state_one.get_events().size() == 1);
        REQUIRE(state_one.get_events().front() == event_one.get_value());

        REQUIRE(!state_two.was_on_entering_called());
        REQUIRE(!state_two.was_on_exiting_called());
        REQUIRE(!state_two.was_on_event_called());
    }

    SECTION("Tests jumping to another state")
    {
        state_one.reset();
        state_two.reset();
        state_machine.jump_to_state_with_event(state_two.get_id(), event_two);

        REQUIRE(state_one.was_on_exiting_called());
        REQUIRE(!state_one.was_on_entering_called());
        REQUIRE(!state_one.was_on_event_called());

        REQUIRE(state_two.was_on_entering_called());
        REQUIRE(!state_two.was_on_exiting_called());
        REQUIRE(state_two.was_on_event_called());
        REQUIRE(state_two.get_events().size() == 1);
        REQUIRE(state_two.get_events().front() == event_two.get_value());
    }
}
////////////////////////////////////////////////////////////////////////////////
