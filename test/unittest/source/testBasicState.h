#ifndef TEST_BASIC_STATE_H__DDK
#define TEST_BASIC_STATE_H__DDK

#include "fsm/fsmStateBaseBasic.h"

#include "testEvent.h"

#include <vector>


namespace test
{
    class BasicState
      : public fsm::StateBaseBasic<test::Event>
    {
        public:
            typedef std::vector<test::Event> events_t;

        public:
            explicit BasicState(int id);

            virtual void onEntering();
            virtual void onExiting();

            virtual void onEvent(test::Event const & event);

            using fsm::StateBaseBasic<test::Event>::getOwner;

            bool wasOnEnteringCalled() const;
            bool wasOnExitingCalled() const;
            bool wasOnEventCalled() const;

            int getOnEnteringCallCount() const;
            int getOnExitingCallCount() const;

            events_t const & getEvents() const;

            void reset();

        private:
            events_t mEvents;
            int mOnEnteringCalls;
            int mOnExitingCalls;
    };
}

#endif /* TEST_BASIC_STATE_H__DDK */
