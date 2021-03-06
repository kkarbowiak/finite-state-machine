#ifndef TEST_EVENT_H__DDK
#define TEST_EVENT_H__DDK

namespace test
{
    class Event
    {
        public:
            explicit Event(int id);
            Event(int id, int value);

            int get_id() const;
            int get_value() const;

        private:
            int m_id;
            int m_value;
    };
}

namespace test
{
    bool operator==(Event const & lhs, Event const & rhs);
    bool operator!=(Event const & lhs, Event const & rhs);
}

#endif /* TEST_EVENT_H__DDK */
