#ifndef TEST_EVENT_H__DDK
#define TEST_EVENT_H__DDK

namespace test
{
    class event
    {
        public:
            explicit event(int id);
            event(int id, int value);

            int get_id() const;
            int get_value() const;

        private:
            int m_id;
            int m_value;
    };
}

namespace test
{
    bool operator==(event const & lhs, event const & rhs);
    bool operator!=(event const & lhs, event const & rhs);
}

#endif /* TEST_EVENT_H__DDK */
