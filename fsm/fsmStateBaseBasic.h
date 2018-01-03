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

            virtual void on_entering();
            virtual void on_exiting();
            virtual void on_event(Event const & event) = 0;

            int get_id() const;

            void set_owner(state_machine<Event> & owner);

        protected:
            state_machine<Event> & get_owner() const;

        private:
            int m_id;
            state_machine<Event> * m_owner;
    };
}


namespace fsm
{
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline state_base_basic<Event>::state_base_basic(int id)
  : m_id(id)
  , m_owner(0)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline state_base_basic<Event>::~state_base_basic()
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline void state_base_basic<Event>::on_entering()
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline void state_base_basic<Event>::on_exiting()
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline int state_base_basic<Event>::get_id() const
{
    return m_id;
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline void state_base_basic<Event>::set_owner(state_machine<Event> & owner)
{
    assert(m_owner == 0);

    m_owner = &owner;
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event>
inline state_machine<Event> & state_base_basic<Event>::get_owner() const
{
    assert(m_owner != 0);

    return *m_owner;
}
////////////////////////////////////////////////////////////////////////////////
}

#endif /* FSM_STATE_BASE_BASIC_H__DDK */
