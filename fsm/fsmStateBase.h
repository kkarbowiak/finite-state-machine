/*
    Copyright 2018 Krzysztof Karbowiak
*/

#ifndef FSM_STATE_BASE_H__DDK
#define FSM_STATE_BASE_H__DDK

#include "fsmStateBaseBasic.h"
#include "fsmStateMachine.h"


namespace fsm
{
    template<typename Event>
    class state_base
      : public state_base_basic<Event>
    {
        public:
            explicit state_base(int id);

        protected:
            void jump_to_state(int id) const;
            void jump_to_state_with_event(int id, Event const & event) const;
    };
}


namespace fsm
{
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline state_base<Event>::state_base(int id)
  : state_base_basic<Event>(id)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline void state_base<Event>::jump_to_state(int id) const
{
    state_base<Event>::get_owner().jump_to_state(id);
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline void state_base<Event>::jump_to_state_with_event(int id, Event const & event) const
{
    state_base<Event>::get_owner().jump_to_state_with_event(id, event);
}
////////////////////////////////////////////////////////////////////////////////
}

#endif /* FSM_STATE_BASE_H__DDK */
