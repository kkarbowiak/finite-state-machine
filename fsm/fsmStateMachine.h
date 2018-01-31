/*
    Copyright 2018 Krzysztof Karbowiak
*/

#ifndef FSM_STATE_MACHINE_H__DDK
#define FSM_STATE_MACHINE_H__DDK

#include <map>
#include <cassert>


namespace fsm
{
    template<typename Event, typename Id>
    class state_machine
    {
        public:
            class state_base_basic
            {
                public:
                    explicit state_base_basic(Id id);
                    virtual ~state_base_basic();

                    virtual void on_entering();
                    virtual void on_exiting();
                    virtual void on_event(Event const & event) = 0;

                    Id get_id() const;

                    void set_owner(state_machine & owner);

                protected:
                    state_machine & get_owner() const;

                private:
                    Id m_id;
                    state_machine * m_owner;
            };

            class state_base
                : public state_base_basic
            {
                public:
                    explicit state_base(Id id);

                protected:
                    void jump_to_state(Id id) const;
                    void jump_to_state_with_event(Id id, Event const & event) const;
            };

        public:
            state_machine();

            void register_state(state_base_basic & state);

            void set_initial_state(Id id);

            void jump_to_state(Id id);
            void jump_to_state_with_event(Id id, Event const & event);

            void handle_event(Event const & event);

        private:
            typedef std::map<Id, state_base_basic *> states_map;

        private:
            states_map m_states_map;
            state_base_basic * m_active_state;
    };
}


namespace fsm
{
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline state_machine<Event, Id>::state_base_basic::state_base_basic(Id id)
    : m_id(id)
    , m_owner(0)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline state_machine<Event, Id>::state_base_basic::~state_base_basic()
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline void state_machine<Event, Id>::state_base_basic::on_entering()
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline void state_machine<Event, Id>::state_base_basic::on_exiting()
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline Id state_machine<Event, Id>::state_base_basic::get_id() const
{
    return m_id;
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline void state_machine<Event, Id>::state_base_basic::set_owner(state_machine & owner)
{
    assert(m_owner == 0);

    m_owner = &owner;
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline state_machine<Event, Id> & state_machine<Event, Id>::state_base_basic::get_owner() const
{
    assert(m_owner != 0);

    return *m_owner;
}
////////////////////////////////////////////////////////////////////////////////
}

namespace fsm
{
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline state_machine<Event, Id>::state_base::state_base(Id id)
    : state_machine<Event, Id>::state_base_basic(id)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline void state_machine<Event, Id>::state_base::jump_to_state(Id id) const
{
    state_base::get_owner().jump_to_state(id);
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline void state_machine<Event, Id>::state_base::jump_to_state_with_event(Id id, Event const & event) const
{
    state_base::get_owner().jump_to_state_with_event(id, event);
}
////////////////////////////////////////////////////////////////////////////////
}

namespace fsm
{
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline state_machine<Event, Id>::state_machine()
  : m_active_state(0)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline void state_machine<Event, Id>::register_state(state_base_basic & state)
{
    Id state_id = state.get_id();

    assert(m_states_map.find(state_id) == m_states_map.end());

    m_states_map[state_id] = &state;
    state.set_owner(*this);
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline void state_machine<Event, Id>::set_initial_state(Id id)
{
    assert(m_active_state == 0);

    typename states_map::iterator it = m_states_map.find(id);
    assert(it != m_states_map.end());

    m_active_state = it->second;
    m_active_state->on_entering();
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline void state_machine<Event, Id>::jump_to_state(Id id)
{
    assert(m_active_state != 0);

    typename states_map::iterator it = m_states_map.find(id);
    assert(it != m_states_map.end());

    m_active_state->on_exiting();
    m_active_state = it->second;
    m_active_state->on_entering();
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline void state_machine<Event, Id>::jump_to_state_with_event(Id id, Event const & event)
{
    jump_to_state(id);
    handle_event(event);
}
////////////////////////////////////////////////////////////////////////////////
template<typename Event, typename Id>
inline void state_machine<Event, Id>::handle_event(Event const & event)
{
    assert(m_active_state != 0);

    m_active_state->on_event(event);
}
////////////////////////////////////////////////////////////////////////////////
}

#endif /* FSM_STATE_MACHINE_H__DDK */
