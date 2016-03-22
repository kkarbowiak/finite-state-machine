#ifndef FSM_STATE_MACHINE_H__DDK
#define FSM_STATE_MACHINE_H__DDK
/**========================================================================== *\
 * File:        fsmStateMachine.h
 *
 * Author:      Krzysztof Karbowiak
 *
 * Description: Definition of a class representing finite state machine
\*=========================================================================== */


#include "fsmStateBaseBasic.h"

#include <map>
#include <cstddef> // NULL
#include <cassert>


namespace fsm
{
    template<typename Event>
    class StateMachine
    {
        public:
            StateMachine();

            void registerState(StateBaseBasic<Event> & state);

            void setInitialState(int id);

            void jumpToState(int id);
            void jumpToStateWithEvent(int id, Event const & event);

            void handleEvent(Event const & event);

        private:
            typedef std::map<int, StateBaseBasic<Event> *> StatesMap;

        private:
            StatesMap mStatesMap;
            StateBaseBasic<Event> * mActiveState;
    };
}


namespace fsm
{
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline StateMachine<Event>::StateMachine()
  : mActiveState(NULL)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline void StateMachine<Event>::registerState(StateBaseBasic<Event> & state)
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
    assert(mActiveState == NULL);

    typename StatesMap::iterator it = mStatesMap.find(id);
    assert(it != mStatesMap.end());

    mActiveState = it->second;
    mActiveState->onEntering();
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline void StateMachine<Event>::jumpToState(int id)
{
    assert(mActiveState != NULL);

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
    assert(mActiveState != NULL);

    mActiveState->onEvent(event);
}
////////////////////////////////////////////////////////////////////////////////
}

#endif /* FSM_STATE_MACHINE_H__DDK */
