#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct meeting_t {
	int begin;
	int end;

	meeting_t() { }
	meeting_t(int _begin, int _end) : begin(_begin), end(_end) { }
};

bool meeting_t_comparator (meeting_t i, meeting_t j) {
	return i.end < j.end;
}

void read_input(vector<meeting_t> &meetings) {
	while (true) {
		if (cin.eof()) {
			break;
		}

		int begin, end;

		cin >> begin;
		cin >> end;

		meetings.push_back(meeting_t(begin, end));
	}
}

int count_max_meetings(vector<meeting_t> &meetings) {
	std::sort(meetings.begin(), meetings.end(), meeting_t_comparator);

	int reserved_count = 1;
	int j = 0;

	for (size_t i = 1; i < meetings.size(); ++i) {
		if (meetings[i].begin >= meetings[j].end) {
			++reserved_count;
			j = i;
		}
	}

	return reserved_count;
}

int main() {
	vector<meeting_t> meetings;

	read_input(meetings);

	std::cout << count_max_meetings(meetings);

	return 0;
}
