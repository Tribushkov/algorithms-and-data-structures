#include <iostream>
#include <cstdio>

#define EVENT_TYPE_BECAME_MATURE 0
#define EVENT_TYPE_DIED_OR_TOO_OLD 1

struct Event {
	int type;
	int day;
	int month;
	int year;

	Event(int type, int day, int month, int year) {
		this->type = type;
		this->day = day;
		this->month = month;
		this->year = year;
	}
};

namespace std {
template<>
struct less<Event *>
{
   bool operator()(const Event *obj1, const Event *obj2) const
   {
	   if (obj1->year < obj2->year) return true;
	   else if (obj1->year == obj2->year && obj1->month < obj2->month) return true;
	   else if (obj1->year == obj2->year && obj1->month == obj2->month && obj1->day < obj2->day) return true;
	   else if (obj1->year == obj2->year && obj1->month == obj2->month && obj1->day == obj2->day && obj1->type > obj2->type) return true;
	   else return false;
   }
};
}

bool isMature(int born_day, int born_month, int born_year, int died_day, int died_month, int died_year) {
	return (died_year < born_year + 18)
			|| (died_year == born_year + 18 && died_month < born_month)
			|| (died_year == born_year + 18 && died_month == born_month && died_day < born_day);
}

bool isDied(int born_day, int born_month, int born_year, int died_day, int died_month, int died_year) {
	return (died_year < born_year + 80)
			|| (died_year == born_year + 80 && died_month < born_month)
			|| (died_year == born_year + 80 && died_month == born_month && died_day < born_day);
}

Event **CreateEventsByPersons(size_t &n) {
	Event **events = new Event*[n * 2];

	for (size_t i = 0; i < n; ++i) {
		int born_day, born_month, born_year;
		int died_day, died_month, died_year;

		scanf("%u %u %u %u %u %u", &born_day, &born_month, &born_year, &died_day, &died_month, &died_year);

		if (isMature(born_day, born_month, born_year, died_day, died_month, died_year)) {
			--i;
			--n;

			continue;
		}

		Event *became_mature_event = new Event(EVENT_TYPE_BECAME_MATURE, born_day, born_month, born_year + 18);

		events[2 * i] = became_mature_event;

		if (isDied(born_day, born_month, born_year, died_day, died_month, died_year)) {
			Event *died_event = new Event(EVENT_TYPE_DIED_OR_TOO_OLD, died_day, died_month, died_year);

			events[2 * i + 1] = died_event;
		} else {
			Event *too_old_event = new Event(EVENT_TYPE_DIED_OR_TOO_OLD, born_day, born_month, born_year + 80);

			events[2 * i + 1] = too_old_event;
		}
	}

	return events;
}

template <typename T>
void quick_sort(T *a, size_t n) {
    size_t i = 0;
    size_t j = n - 1;
    bool side = 0;

    while (i != j) {
		if (!std::less<T>()(a[i], a[j])) {
            std::swap(a[i], a[j]);
            side = !side;
        }

        if (side) {
            ++i;
        } else {
            --j;
        }
    }

    if (i > 1) quick_sort(a, i);
    if (i + 1 < n) quick_sort(a + i + 1, n - (i + 1));
}

int FindMaxValid(Event **events, size_t events_num) {
	int valid = 0;
	int valid_max = 0;

	for (size_t i = 0; i < events_num; ++i) {
		if (events[i]->type == EVENT_TYPE_BECAME_MATURE) {
			++valid;
		} else if (events[i]->type == EVENT_TYPE_DIED_OR_TOO_OLD) {
			--valid;
		}

		if (valid > valid_max) {
			valid_max = valid;
		}
	}

	return valid_max;
}

int main() {
	size_t n;

	scanf("%u", (unsigned *)&n);

	Event **events = CreateEventsByPersons(n);
	size_t events_num = n * 2;

	quick_sort<Event *>(events, events_num);

	int valid_max = FindMaxValid(events, events_num);

	printf("%u", valid_max);

	return 0;
}
