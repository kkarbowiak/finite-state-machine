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
            void jumpToState(int id) const;
            void jumpToStateWithEvent(int id, Event const & event) const;
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
inline void state_base<Event>::jumpToState(int id) const
{
    state_base<Event>::getOwner().jumpToState(id);
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline void state_base<Event>::jumpToStateWithEvent(int id, Event const & event) const
{
    state_base<Event>::getOwner().jumpToStateWithEvent(id, event);
}
////////////////////////////////////////////////////////////////////////////////
}

#endif /* FSM_STATE_BASE_H__DDK */
