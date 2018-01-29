/*
    Copyright 2018 Krzysztof Karbowiak
*/

#ifndef FSM_STATE_MACHINE_H__DDK
#define FSM_STATE_MACHINE_H__DDK

#include "fsmStateBaseBasic.h"

#include <map>
#include <cassert>


namespace fsm
{
    template<typename Event, typename Id = int>
    class state_machine
    {
        public:
            state_machine();

            void register_state(state_base_basic<Event, Id> & state);

            void set_initial_state(Id id);

            void jump_to_state(Id id);
            void jump_to_state_with_event(Id id, Event const & event);

            void handle_event(Event const & event);

        private:
            typedef std::map<Id, state_base_basic<Event, Id> *> states_map;

        private:
            states_map m_states_map;
            state_base_basic<Event, Id> * m_active_state;
    };
}


namespace fsm
{
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline state_machine<Event, Id>::state_machine()
  : m_active_state(0)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline void state_machine<Event, Id>::register_state(state_base_basic<Event, Id> & state)
{
    Id state_id = state.get_id();

    assert(m_states_map.find(state_id) == m_states_map.end());

    m_states_map[state_id] = &state;
    state.set_owner(*this);
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline void state_machine<Event, Id>::set_initial_state(Id id)
{
    assert(m_active_state == 0);

    typename states_map::iterator it = m_states_map.find(id);
    assert(it != m_states_map.end());

    m_active_state = it->second;
    m_active_state->on_entering();
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline void state_machine<Event, Id>::jump_to_state(Id id)
{
    assert(m_active_state != 0);

    typename states_map::iterator it = m_states_map.find(id);
    assert(it != m_states_map.end());

    m_active_state->on_exiting();
    m_active_state = it->second;
    m_active_state->on_entering();
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline void state_machine<Event, Id>::jump_to_state_with_event(Id id, Event const & event)
{
    jump_to_state(id);
    handle_event(event);
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline void state_machine<Event, Id>::handle_event(Event const & event)
{
    assert(m_active_state != 0);

    m_active_state->on_event(event);
}
////////////////////////////////////////////////////////////////////////////////
}

#endif /* FSM_STATE_MACHINE_H__DDK */
