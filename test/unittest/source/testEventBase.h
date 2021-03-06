#ifndef TEST_EVENT_BASE_H__DDK
#define TEST_EVENT_BASE_H__DDK

namespace test { class State; }

namespace test
{
    class EventBase
    {
        public:
            explicit EventBase(int id);
            EventBase(int id, int value);

            int get_id() const;
            int get_value() const;

            void forward_data_to_state(State & state) const;

        private:
            int m_id;
            int m_value;
    };
}

namespace test
{
    bool operator==(EventBase const & lhs, EventBase const & rhs);
    bool operator!=(EventBase const & lhs, EventBase const & rhs);
}

#endif /* TEST_EVENT_BASE_H__DDK */
