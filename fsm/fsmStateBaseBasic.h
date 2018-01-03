/*
    Copyright 2018 Krzysztof Karbowiak
*/

#ifndef FSM_STATE_BASE_BASIC_H__DDK
#define FSM_STATE_BASE_BASIC_H__DDK

#include <cassert>


namespace fsm
{
    template<typename Event>
    class state_machine;
}


namespace fsm
{
    template<typename Event>
    class state_base_basic
    {
        public:
            explicit state_base_basic(int id);
            virtual ~state_base_basic();

            virtual void onEntering();
            virtual void onExiting();
            virtual void onEvent(Event const & event) = 0;

            int getID() const;

            void setOwner(state_machine<Event> & owner);

        protected:
            state_machine<Event> & getOwner() const;

        private:
            int mID;
            state_machine<Event> * mOwner;
    };
}


namespace fsm
{
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline state_base_basic<Event>::state_base_basic(int id)
  : mID(id)
  , mOwner(0)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline state_base_basic<Event>::~state_base_basic()
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline void state_base_basic<Event>::onEntering()
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline void state_base_basic<Event>::onExiting()
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline int state_base_basic<Event>::getID() const
{
    return mID;
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline void state_base_basic<Event>::setOwner(state_machine<Event> & owner)
{
    assert(mOwner == 0);

    mOwner = &owner;
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline state_machine<Event> & state_base_basic<Event>::getOwner() const
{
    assert(mOwner != 0);

    return *mOwner;
}
////////////////////////////////////////////////////////////////////////////////
}

#endif /* FSM_STATE_BASE_BASIC_H__DDK */
