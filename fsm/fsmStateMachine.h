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
    template<typename Event>
    class StateMachine
    {
        public:
            StateMachine();

            void registerState(state_base_basic<Event> & state);

            void setInitialState(int id);

            void jumpToState(int id);
            void jumpToStateWithEvent(int id, Event const & event);

            void handleEvent(Event const & event);

        private:
            typedef std::map<int, state_base_basic<Event> *> StatesMap;

        private:
            StatesMap mStatesMap;
            state_base_basic<Event> * mActiveState;
    };
}


namespace fsm
{
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline StateMachine<Event>::StateMachine()
  : mActiveState(0)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline void StateMachine<Event>::registerState(state_base_basic<Event> & state)
{
    int state_id = state.getID();

    assert(mStatesMap.find(state_id) == mStatesMap.end());

    mStatesMap[state_id] = &state;
    state.setOwner(*this);
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline void StateMachine<Event>::setInitialState(int id)
{
    assert(mActiveState == 0);

    typename StatesMap::iterator it = mStatesMap.find(id);
    assert(it != mStatesMap.end());

    mActiveState = it->second;
    mActiveState->onEntering();
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline void StateMachine<Event>::jumpToState(int id)
{
    assert(mActiveState != 0);

    typename StatesMap::iterator it = mStatesMap.find(id);
    assert(it != mStatesMap.end());

    mActiveState->onExiting();
    mActiveState = it->second;
    mActiveState->onEntering();
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline void StateMachine<Event>::jumpToStateWithEvent(int id, Event const & event)
{
    jumpToState(id);
    handleEvent(event);
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline void StateMachine<Event>::handleEvent(Event const & event)
{
    assert(mActiveState != 0);

    mActiveState->onEvent(event);
}
////////////////////////////////////////////////////////////////////////////////
}

#endif /* FSM_STATE_MACHINE_H__DDK */
