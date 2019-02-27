#include "airline_ticket.h"
#include "test_runner.h"

#include <algorithm>
#include <iomanip>
#include <numeric>

#define SORT_BY(field) [](const auto& lhs, const auto& rhs) { return lhs.field < rhs.field; }

void TestSortBy() {
    vector<AirlineTicket> tixs = {
            {"VKO", "AER", "Utair",     {2018, 2, 28}, {17, 40}, {2018, 2, 28}, {20,  0}, 1200},
            {"AER", "VKO", "Utair",     {2018, 3,  5}, {14, 15}, {2018, 3,  5}, {16, 30}, 1700},
            {"AER", "SVO", "Aeroflot",  {2018, 3,  5}, {18, 30}, {2018, 3,  5}, {20, 30}, 2300},
            {"PMI", "DME", "Iberia",    {2018, 2,  8}, {23, 00}, {2018, 2,  9}, { 3, 30}, 9000},
            {"CDG", "SVO", "AirFrance", {2018, 3,  1}, {13, 00}, {2018, 3,  1}, {17, 30}, 8000},
    };

    sort(begin(tixs), end(tixs), SORT_BY(price));
    ASSERT_EQUAL(tixs.front().price, 1200);
    ASSERT_EQUAL(tixs.back().price, 9000);

    sort(begin(tixs), end(tixs), SORT_BY(from));
    ASSERT_EQUAL(tixs.front().from, "AER");
    ASSERT_EQUAL(tixs.back().from, "VKO");

    sort(begin(tixs), end(tixs), SORT_BY(arrival_date));
    ASSERT_EQUAL(tixs.front().arrival_date, (Date{2018, 2, 9}));
    ASSERT_EQUAL(tixs.back().arrival_date, (Date{2018, 3, 5}));
}

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
    os << setw(4) << dt.year << setw(2) << dt.month << setw(2) << dt.day;
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
    os << setw(2) << tm.hours << setw(2) << tm.minutes;
    return os;
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSortBy);
    return 0;
}
