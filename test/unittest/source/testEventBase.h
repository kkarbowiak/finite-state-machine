#ifndef TEST_EVENT_BASE_H__DDK
#define TEST_EVENT_BASE_H__DDK

namespace test { class state; }

namespace test
{
    class event_base
    {
        public:
            explicit event_base(int id);
            event_base(int id, int value);

            int get_id() const;
            int get_value() const;

            void forward_data_to_state(state & state) const;

        private:
            int m_id;
            int m_value;
    };
}

namespace test
{
    bool operator==(event_base const & lhs, event_base const & rhs);
    bool operator!=(event_base const & lhs, event_base const & rhs);
}

#endif /* TEST_EVENT_BASE_H__DDK */
