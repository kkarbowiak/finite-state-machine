/*
    Copyright 2018 Krzysztof Karbowiak
*/

#ifndef FSM_STATE_BASE_BASIC_H__DDK
#define FSM_STATE_BASE_BASIC_H__DDK

#include <cassert>


namespace fsm
{
    template<typename Event>
    class StateMachine;
}


namespace fsm
{
    template<typename Event>
    class StateBaseBasic
    {
        public:
            explicit StateBaseBasic(int id);
            virtual ~StateBaseBasic();

            virtual void onEntering();
            virtual void onExiting();
            virtual void onEvent(Event const & event) = 0;

            int getID() const;

            void setOwner(StateMachine<Event> & owner);

        protected:
            StateMachine<Event> & getOwner() const;

        private:
            int mID;
            StateMachine<Event> * mOwner;
    };
}


namespace fsm
{
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline StateBaseBasic<Event>::StateBaseBasic(int id)
  : mID(id)
  , mOwner(0)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline StateBaseBasic<Event>::~StateBaseBasic()
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline void StateBaseBasic<Event>::onEntering()
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline void StateBaseBasic<Event>::onExiting()
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline int StateBaseBasic<Event>::getID() const
{
    return mID;
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline void StateBaseBasic<Event>::setOwner(StateMachine<Event> & owner)
{
    assert(mOwner == 0);

    mOwner = &owner;
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline StateMachine<Event> & StateBaseBasic<Event>::getOwner() const
{
    assert(mOwner != 0);

    return *mOwner;
}
////////////////////////////////////////////////////////////////////////////////
}

#endif /* FSM_STATE_BASE_BASIC_H__DDK */
