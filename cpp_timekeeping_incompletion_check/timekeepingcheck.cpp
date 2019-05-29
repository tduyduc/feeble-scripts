#include <cstdio>

class Time {
public:
	unsigned char hour, minute;
	Time() { hour = minute = 0; }	
	Time(unsigned char h, unsigned char m): hour(h), minute(m) {}
	Time(unsigned char h): hour(h) { minute = 0; }
	bool isNull() { return !hour && !minute; }
	char *toString() {
		if (isNull()) return (char*)"--:--";
		char *temp;
		sprintf(temp, "%02i:%02i", hour, minute);
		return temp;
	}
	bool operator < (Time t) {
		return (this->hour < t.hour) ||
			((this->hour == t.hour) && (this->minute < t.minute));
	}
	bool operator > (Time t) {
		return (this->hour > t.hour) ||
			((this->hour == t.hour) && (this->minute > t.minute));
	}
	bool operator == (Time t) {
		return (this->hour == t.hour) && (this->minute == t.minute);
	}
	operator bool() { return !isNull(); }
	operator float() { return hour / 24. + minute / 1440.; }
};

int main() {
	const unsigned char len = 16;
	unsigned char ids[len] = {
		1, 2, 3, 3, 4, 5, 5, 6, 7, 7, 8, 9, 10, 10, 11, 12
	}, i = 0;
	Time t[len][2] = {
		{ Time(8, 0), Time(17, 0) },
		{ Time(7, 59), Time(8, 0) },
		{ Time(7, 59), Time(8, 0) },
		{ Time(17, 0), Time() },
		{ Time(17, 0), Time() },
		{ Time(8, 0), Time(17, 0) },
		{ Time(17, 1), Time() },
		{ Time(17, 0), Time(17, 1) },
		{ Time(7, 59), Time(8, 0) },
		{ Time(17, 0), Time(17, 1) },
		{ Time(13, 0), Time(17, 0) },
		{ Time(8, 0), Time(11, 0) },
		{ Time(8, 0), Time(11, 0) },
		{ Time(13, 0), Time(17, 0) },
		{ Time(11, 0), Time(12, 30) },
		{ Time(8, 0), Time(8, 30) }
	}, in, out, temp;
	/* In this example, IDs 2, 4, 6, 12 have not completed a working day. */
	for (; i < len; i++) {
		if (i > 0 && ids[i - 1] == ids[i])
			out = t[i][1] ? t[i][1] : t[i][0];
		else {
			in = t[i][0]; out = t[i][1];
		}
		if (i < len - 1) {
			if ((float)out - (float)in > 1 / 24. || ids[i] == ids[i + 1])
				continue;
		} else if ((float)out - (float)in > 1 / 24.) continue;
		if ((in && in > out && in > Time(12)) || (out && !in)) {
			temp = Time(in.hour, in.minute);
			in = Time(out.hour, out.minute);
			out = Time(temp.hour, temp.minute);
		} else if (in && out) out = Time();
		printf("%01i:\t%s\t%s\n", ids[i], in.toString(), out.toString());
	}
	return 0;
}
