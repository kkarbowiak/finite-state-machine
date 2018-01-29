/*
    Copyright 2018 Krzysztof Karbowiak
*/

#ifndef FSM_STATE_BASE_BASIC_H__DDK
#define FSM_STATE_BASE_BASIC_H__DDK

#include <cassert>


namespace fsm
{
    template<typename Event, typename Id>
    class state_machine;
}


namespace fsm
{
    template<typename Event, typename Id = int>
    class state_base_basic
    {
        public:
            explicit state_base_basic(Id id);
            virtual ~state_base_basic();

            virtual void on_entering();
            virtual void on_exiting();
            virtual void on_event(Event const & event) = 0;

            Id get_id() const;

            void set_owner(state_machine<Event, Id> & owner);

        protected:
            state_machine<Event, Id> & get_owner() const;

        private:
            Id m_id;
            state_machine<Event, Id> * m_owner;
    };
}


namespace fsm
{
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline state_base_basic<Event, Id>::state_base_basic(Id id)
  : m_id(id)
  , m_owner(0)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline state_base_basic<Event, Id>::~state_base_basic()
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline void state_base_basic<Event, Id>::on_entering()
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline void state_base_basic<Event, Id>::on_exiting()
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline Id state_base_basic<Event, Id>::get_id() const
{
    return m_id;
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline void state_base_basic<Event, Id>::set_owner(state_machine<Event, Id> & owner)
{
    assert(m_owner == 0);

    m_owner = &owner;
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline state_machine<Event, Id> & state_base_basic<Event, Id>::get_owner() const
{
    assert(m_owner != 0);

    return *m_owner;
}
////////////////////////////////////////////////////////////////////////////////
}

#endif /* FSM_STATE_BASE_BASIC_H__DDK */
