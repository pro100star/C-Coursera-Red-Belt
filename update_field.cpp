#include "airline_ticket.h"
#include "test_runner.h"

#include <iomanip>
#include <sstream>

using namespace std;

bool operator < (const Date& lhs, const Date& rhs) {
    if (lhs.year < rhs.year) {
        return true;
    } else if (lhs.year == rhs.year) {
        if (lhs.month < rhs.month) {
            return true;
        } else if (lhs.month == rhs.month) {
            return lhs.day < rhs.day;
        }
    }
    return false;
}

bool operator == (const Date& lhs, const Date& rhs) {
    return lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day;
}

std::ostream& operator << (std::ostream& os, const Date& dt) {
    os << setw(4) << dt.year << '-' << setw(2) << dt.month << '-' << setw(2) << dt.day;
    return os;
}

bool operator == (const Time& lhs, const Time& rhs) {
    return lhs.hours == rhs.hours && lhs.minutes == rhs.minutes;
}

bool operator < (const Time& lhs, const Time& rhs) {
    if (lhs.hours < rhs.hours) {
        return true;
    } else if (lhs.hours == rhs.hours) {
        return lhs.minutes < rhs.minutes;
    }
    return false;
}

std::ostream& operator << (std::ostream& os, const Time& tm) {
    os << setw(2) << tm.hours << ':' << setw(2) << tm.minutes;
    return os;
}

#define UPDATE_FIELD(ticket, field, values) { \
    map<string, string>::const_iterator it; \
    it = values.find(#field); \
    if (it != values.end()) { \
        istringstream is(it->second);\
        is >> ticket.field; \
    }\
}

std::istream& operator >> (istream& is, Date& dt) {
    is >> dt.year;
    is.ignore(1);
    is >> dt.month;
    is.ignore(1);
    is >> dt.day;
    return is;
}

std::istream& operator >> (istream& is, Time& tm) {
    is >> tm.hours;
    is.ignore(1);
    is >> tm.minutes;
    return is;
}

void TestUpdate() {
    AirlineTicket t;
    t.price = 0;

    const map<string, string> updates1 = {
            {"departure_date", "2018-2-28"},
            {"departure_time", "17:40"},
    };
    UPDATE_FIELD(t, departure_date, updates1);
    UPDATE_FIELD(t, departure_time, updates1);
    UPDATE_FIELD(t, price, updates1);

    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 0);

    const map<string, string> updates2 = {
            {"price", "12550"},
            {"arrival_time", "20:33"},
    };
    UPDATE_FIELD(t, departure_date, updates2);
    UPDATE_FIELD(t, departure_time, updates2);
    UPDATE_FIELD(t, arrival_time, updates2);
    UPDATE_FIELD(t, price, updates2);

    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 12550);
    ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}


int main() {
    TestRunner tr;
    RUN_TEST(tr, TestUpdate);
}
