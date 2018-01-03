/*
    Copyright 2018 Krzysztof Karbowiak
*/

#ifndef FSM_STATE_BASE_H__DDK
#define FSM_STATE_BASE_H__DDK

#include "fsmStateBaseBasic.h"
#include "fsmStateMachine.h"


namespace fsm
{
    template<typename event>
    class state_base
      : public state_base_basic<event>
    {
        public:
            explicit state_base(int id);

        protected:
            void jump_to_state(int id) const;
            void jump_to_state_with_event(int id, event const & event) const;
    };
}


namespace fsm
{
////////////////////////////////////////////////////////////////////////////////
template<typename event>
inline state_base<event>::state_base(int id)
  : state_base_basic<event>(id)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename event>
inline void state_base<event>::jump_to_state(int id) const
{
    state_base<event>::get_owner().jump_to_state(id);
}
////////////////////////////////////////////////////////////////////////////////
template<typename event>
inline void state_base<event>::jump_to_state_with_event(int id, event const & event) const
{
    state_base<event>::get_owner().jump_to_state_with_event(id, event);
}
////////////////////////////////////////////////////////////////////////////////
}

#endif /* FSM_STATE_BASE_H__DDK */
