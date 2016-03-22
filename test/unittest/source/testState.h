#ifndef STATE_BASE_H__DDK
#define STATE_BASE_H__DDK

#include "fsm/fsmStateBase.h"

#include "testEventBase.h"

#include <vector>


namespace test
{
    class State
      : public fsm::StateBase<test::EventBase>
    {
        public:
            typedef std::vector<int> events_t;

        public:
            explicit State(int id);

            virtual void onEntering();
            virtual void onExiting();

            virtual void onEvent(test::EventBase const & event);

            void onEventBase(int value);

            using fsm::StateBase<test::EventBase>::jumpToState;
            using fsm::StateBase<test::EventBase>::jumpToStateWithEvent;

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

#endif /* STATE_BASE_H__DDK */
