#ifndef TEST_BASIC_STATE_H__DDK
#define TEST_BASIC_STATE_H__DDK

#include "fsm/fsmStateBaseBasic.h"

#include "testEvent.h"

#include <vector>


namespace test
{
    class basic_state
      : public fsm::state_base_basic<test::event>
    {
        public:
            typedef std::vector<test::event> events_t;

        public:
            explicit basic_state(int id);

            virtual void on_entering();
            virtual void on_exiting();

            virtual void on_event(test::event const & event);

            using fsm::state_base_basic<test::event>::get_owner;

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

#endif /* TEST_BASIC_STATE_H__DDK */
