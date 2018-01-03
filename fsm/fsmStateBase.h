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
    class StateBase
      : public state_base_basic<Event>
    {
        public:
            explicit StateBase(int id);

        protected:
            void jumpToState(int id) const;
            void jumpToStateWithEvent(int id, Event const & event) const;
    };
}


namespace fsm
{
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline StateBase<Event>::StateBase(int id)
  : state_base_basic<Event>(id)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline void StateBase<Event>::jumpToState(int id) const
{
    StateBase<Event>::getOwner().jumpToState(id);
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline void StateBase<Event>::jumpToStateWithEvent(int id, Event const & event) const
{
    StateBase<Event>::getOwner().jumpToStateWithEvent(id, event);
}
////////////////////////////////////////////////////////////////////////////////
}

#endif /* FSM_STATE_BASE_H__DDK */
