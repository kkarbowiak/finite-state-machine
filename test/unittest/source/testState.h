#ifndef STATE_BASE_H__DDK
#define STATE_BASE_H__DDK

#include "fsm/fsmStateBase.h"

#include "testEventBase.h"

#include <vector>


namespace test
{
    class state
      : public fsm::state_base<test::event_base>
    {
        public:
            typedef std::vector<int> events_t;

        public:
            explicit state(int id);

            virtual void on_entering();
            virtual void on_exiting();

            virtual void on_event(test::event_base const & event);

            void on_event_base(int value);

            using fsm::state_base<test::event_base>::jump_to_state;
            using fsm::state_base<test::event_base>::jump_to_state_with_event;

            bool was_on_entering_called() const;
            bool was_on_exiting_called() const;
            bool was_on_event_called() const;

            int get_on_entering_call_count() const;
            int get_on_exiting_call_count() const;

            events_t const & get_events() const;

            void reset();

        private:
            events_t m_events;
            int m_on_entering_calls;
            int m_on_exiting_calls;
    };
}

#endif /* STATE_BASE_H__DDK */
