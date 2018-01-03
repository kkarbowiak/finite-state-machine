#ifndef TEST_BASIC_STATE_H__DDK
#define TEST_BASIC_STATE_H__DDK

#include "fsm/fsmStateBaseBasic.h"

#include "testEvent.h"

#include <vector>


namespace test
{
    class BasicState
      : public fsm::state_base_basic<test::Event>
    {
        public:
            typedef std::vector<test::Event> events_t;

        public:
            explicit BasicState(int id);

            virtual void on_entering();
            virtual void on_exiting();

            virtual void on_event(test::Event const & event);

            using fsm::state_base_basic<test::Event>::get_owner;

            bool wason_enteringCalled() const;
            bool wason_exitingCalled() const;
            bool wason_eventCalled() const;

            int geton_enteringCallCount() const;
            int geton_exitingCallCount() const;

            events_t const & getEvents() const;

            void reset();

        private:
            events_t mEvents;
            int mon_enteringCalls;
            int mon_exitingCalls;
    };
}

#endif /* TEST_BASIC_STATE_H__DDK */
