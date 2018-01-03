/*
    Copyright 2018 Krzysztof Karbowiak
*/

#ifndef FSM_STATE_BASE_BASIC_H__DDK
#define FSM_STATE_BASE_BASIC_H__DDK

#include <cassert>


namespace fsm
{
    template<typename event>
    class state_machine;
}


namespace fsm
{
    template<typename event>
    class state_base_basic
    {
        public:
            explicit state_base_basic(int id);
            virtual ~state_base_basic();

            virtual void on_entering();
            virtual void on_exiting();
            virtual void on_event(event const & event) = 0;

            int get_id() const;

            void set_owner(state_machine<event> & owner);

        protected:
            state_machine<event> & get_owner() const;

        private:
            int m_id;
            state_machine<event> * m_owner;
    };
}


namespace fsm
{
////////////////////////////////////////////////////////////////////////////////
template<typename event>
inline state_base_basic<event>::state_base_basic(int id)
  : m_id(id)
  , m_owner(0)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename event>
inline state_base_basic<event>::~state_base_basic()
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename event>
inline void state_base_basic<event>::on_entering()
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename event>
inline void state_base_basic<event>::on_exiting()
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename event>
inline int state_base_basic<event>::get_id() const
{
    return m_id;
}
////////////////////////////////////////////////////////////////////////////////
template<typename event>
inline void state_base_basic<event>::set_owner(state_machine<event> & owner)
{
    assert(m_owner == 0);

    m_owner = &owner;
}
////////////////////////////////////////////////////////////////////////////////
template<typename event>
inline state_machine<event> & state_base_basic<event>::get_owner() const
{
    assert(m_owner != 0);

    return *m_owner;
}
////////////////////////////////////////////////////////////////////////////////
}

#endif /* FSM_STATE_BASE_BASIC_H__DDK */
