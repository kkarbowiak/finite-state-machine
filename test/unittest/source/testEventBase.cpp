#include "testEventBase.h"
#include "testState.h"


namespace test
{
////////////////////////////////////////////////////////////////////////////////
EventBase::EventBase(int id)
  : m_id(id)
  , mValue(0)
{
}
////////////////////////////////////////////////////////////////////////////////
EventBase::EventBase(int id, int value)
  : m_id(id)
  , mValue(value)
{
}
////////////////////////////////////////////////////////////////////////////////
int EventBase::get_id() const
{
    return m_id;
}
////////////////////////////////////////////////////////////////////////////////
int EventBase::getValue() const
{
    return mValue;
}
////////////////////////////////////////////////////////////////////////////////
void EventBase::forwardDataToState(State & state) const
{
    state.on_eventBase(mValue);
}
////////////////////////////////////////////////////////////////////////////////
bool operator==(EventBase const & lhs, EventBase const & rhs)
{
    return (
        (lhs.get_id() == rhs.get_id()) &&
        (lhs.getValue() == rhs.getValue()));
}
////////////////////////////////////////////////////////////////////////////////
bool operator!=(EventBase const & lhs, EventBase const & rhs)
{
    return !(lhs == rhs);
}
////////////////////////////////////////////////////////////////////////////////
}
