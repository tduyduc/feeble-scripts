#include <iostream>
#include <string>
using namespace std;

const string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-_";

string toRadix(unsigned long long source, unsigned radix) {
	if (radix < 2 || radix > 64) return string();
	if (source < 0) return toRadix(-source, radix);
	if (source == 0) return "0";
	if (source / radix)
		return toRadix(source / radix, radix) + digits[source % radix];
	return string() + digits[source % radix];
}

unsigned long long fromRadix(string source, unsigned radix) {
	if (radix < 2 || radix > 64) return 0;
	unsigned len = source.length(), i = 0, j, digitsLen = digits.length();
	unsigned long long dest = 0;
	for (; i < len; i++)
		for (j = 0; j < radix; j++)
			if (digits[j] == source[i]) {
				dest = dest * radix + j;
				break;
			}
	return dest;
}

unsigned long long strToInt(string source) {
	unsigned len = source.length(), i = 0;
	unsigned long long dest = 0;
	for (; i < len; i++)
		dest = dest * 10 + (source[i] - '0');
	return dest;
}

int main(int argc, char *argv[]) {
	if (argc != 4) {
		cerr << "Usage: " << argv[0] << " NUMBER {from | to} RADIX" << endl
			<< "Converts a non-negative integer from/to decimal." << endl
			<< "Accepted radix range is from 2 to 64 inclusive." << endl;
			<< "Digits are case-sensitive (i.e. 0123456789ABCDEF for radix 16)." << endl;
		return 1;
	}
	string source = string(argv[1]), oper = string(argv[2]);
	unsigned radix = strToInt(string(argv[3]));
	if (radix < 2 || radix > 64) {
		cerr << "Radix out of range: " << argv[3] << endl;
		return 2;
	} else if (oper == "from")
		cout << fromRadix(source, radix) << endl;
	else if (oper == "to")
		cout << toRadix(strToInt(source), radix) << endl;
	else {
		cerr << "Unknown operator: " << argv[2] << endl;
		return 3;
	}
	return 0;
}
