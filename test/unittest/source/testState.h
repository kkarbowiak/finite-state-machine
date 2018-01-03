#ifndef STATE_BASE_H__DDK
#define STATE_BASE_H__DDK

#include "fsm/fsmStateBase.h"

#include "testEventBase.h"

#include <vector>


namespace test
{
    class State
      : public fsm::state_base<test::EventBase>
    {
        public:
            typedef std::vector<int> events_t;

        public:
            explicit State(int id);

            virtual void on_entering();
            virtual void on_exiting();

            virtual void on_event(test::EventBase const & event);

            void on_eventBase(int value);

            using fsm::state_base<test::EventBase>::jump_to_state;
            using fsm::state_base<test::EventBase>::jump_to_state_with_event;

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

#endif /* STATE_BASE_H__DDK */
