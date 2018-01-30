/*
    Copyright 2018 Krzysztof Karbowiak
*/

#ifndef FSM_STATE_BASE_H__DDK
#define FSM_STATE_BASE_H__DDK

#include "fsmStateMachine.h"


namespace fsm
{
    template<typename Event, typename Id>
    class state_base
      : public state_machine<Event, Id>::state_base_basic
    {
        public:
            explicit state_base(Id id);

        protected:
            void jump_to_state(Id id) const;
            void jump_to_state_with_event(Id id, Event const & event) const;
    };
}


namespace fsm
{
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline state_base<Event, Id>::state_base(Id id)
  : state_machine<Event, Id>::state_base_basic(id)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline void state_base<Event, Id>::jump_to_state(Id id) const
{
    state_base<Event, Id>::get_owner().jump_to_state(id);
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline void state_base<Event, Id>::jump_to_state_with_event(Id id, Event const & event) const
{
    state_base<Event, Id>::get_owner().jump_to_state_with_event(id, Event);
}
////////////////////////////////////////////////////////////////////////////////
}

#endif /* FSM_STATE_BASE_H__DDK */
