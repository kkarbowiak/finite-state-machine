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
    class state_machine
    {
        public:
            state_machine();

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
inline state_machine<Event>::state_machine()
  : mActiveState(0)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline void state_machine<Event>::registerState(state_base_basic<Event> & state)
{
    int state_id = state.getID();

    assert(mStatesMap.find(state_id) == mStatesMap.end());

    mStatesMap[state_id] = &state;
    state.setOwner(*this);
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline void state_machine<Event>::setInitialState(int id)
{
    assert(mActiveState == 0);

    typename StatesMap::iterator it = mStatesMap.find(id);
    assert(it != mStatesMap.end());

    mActiveState = it->second;
    mActiveState->onEntering();
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline void state_machine<Event>::jumpToState(int id)
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
inline void state_machine<Event>::jumpToStateWithEvent(int id, Event const & event)
{
    jumpToState(id);
    handleEvent(event);
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline void state_machine<Event>::handleEvent(Event const & event)
{
    assert(mActiveState != 0);

    mActiveState->onEvent(event);
}
////////////////////////////////////////////////////////////////////////////////
}

#endif /* FSM_STATE_MACHINE_H__DDK */
