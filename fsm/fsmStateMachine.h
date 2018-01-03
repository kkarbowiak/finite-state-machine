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
    template<typename event>
    class state_machine
    {
        public:
            state_machine();

            void register_state(state_base_basic<event> & state);

            void set_initial_state(int id);

            void jump_to_state(int id);
            void jump_to_state_with_event(int id, event const & event);

            void handle_event(event const & event);

        private:
            typedef std::map<int, state_base_basic<event> *> states_map;

        private:
            states_map m_states_map;
            state_base_basic<event> * m_active_state;
    };
}


namespace fsm
{
////////////////////////////////////////////////////////////////////////////////
template<typename event>
inline state_machine<event>::state_machine()
  : m_active_state(0)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename event>
inline void state_machine<event>::register_state(state_base_basic<event> & state)
{
    int state_id = state.get_id();

    assert(m_states_map.find(state_id) == m_states_map.end());

    m_states_map[state_id] = &state;
    state.set_owner(*this);
}
////////////////////////////////////////////////////////////////////////////////
template<typename event>
inline void state_machine<event>::set_initial_state(int id)
{
    assert(m_active_state == 0);

    typename states_map::iterator it = m_states_map.find(id);
    assert(it != m_states_map.end());

    m_active_state = it->second;
    m_active_state->on_entering();
}
////////////////////////////////////////////////////////////////////////////////
template<typename event>
inline void state_machine<event>::jump_to_state(int id)
{
    assert(m_active_state != 0);

    typename states_map::iterator it = m_states_map.find(id);
    assert(it != m_states_map.end());

    m_active_state->on_exiting();
    m_active_state = it->second;
    m_active_state->on_entering();
}
////////////////////////////////////////////////////////////////////////////////
template<typename event>
inline void state_machine<event>::jump_to_state_with_event(int id, event const & event)
{
    jump_to_state(id);
    handle_event(event);
}
////////////////////////////////////////////////////////////////////////////////
template<typename event>
inline void state_machine<event>::handle_event(event const & event)
{
    assert(m_active_state != 0);

    m_active_state->on_event(event);
}
////////////////////////////////////////////////////////////////////////////////
}

#endif /* FSM_STATE_MACHINE_H__DDK */
