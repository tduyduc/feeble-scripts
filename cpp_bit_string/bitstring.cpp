// A space-efficient implementation of bit strings which condenses 8 bits in one byte.
// Each variable of bool type takes 1 byte, so 15 bool variables take 15 bytes.
// In this implementation, 15 Boolean bits take 4 bytes (2 bytes for counting length).
// The length attribute's type can be adjusted to size_t or unsigned char as necessary.

#include <iostream>
using namespace std;

class BitString {
protected: unsigned char *bits; unsigned short len;
public:
	BitString(const unsigned short n): len(n) {
		// n bits requires ceiling(n / 8) bytes, excluding length attribute
		unsigned char chars = n / 8;
		(n % 8) && chars++;
		bits = new unsigned char[chars];
		clearAll();
	}
	BitString(const bool *b, unsigned short n): len(n) {
		// initialize bits from a bool array
		unsigned short i = 0, chars = n / 8;
		(n % 8) && chars++;
		bits = new unsigned char[chars];
		clearAll();
		for (; i < n; i++)
			if (b[i]) setBit(i);
	}
	BitString(const char *s) {
		// initialize bits from a string containing binary digits
		unsigned short i;
		for (i = 0; s[i] == '0' || s[i] == '1'; i++);
		len = i;
		unsigned short chars = len / 8;
		(len % 8) && chars++;
		bits = new unsigned char[chars];
		clearAll();
		for (i = 0; ; i++)
			if (s[i] == '1') setBit(len - i - 1);
			else if (s[i] == '0');
			else break;
	}
	BitString(const BitString &bs): len(bs.len) {
		// copy from another bit string
		unsigned short i = 0, n = sizeof(bs.bits), chars = n / 8;
		bits = new unsigned char[bs.len];
		for (; i < n; i++)
			bits[i] = bs.bits[i];
	}
	bool setBit(unsigned short pos) {
		// set the bit in a specified position to 1
		if (pos >= len) return false;
		unsigned char mask = 1 << (pos % 8);
		bits[pos / 8] |= mask; // bit-or the mask
		return true;
	}
	bool clearBit(unsigned short pos) {
		// set the bit in a specified position to 0
		if (pos >= len) return false;
		unsigned char mask = ~(1 << (pos % 8)); // tilde is the complement operator (toggle all bits)
		bits[pos / 8] &= mask; // bit-and the mask
		return false;
	}
	bool toggleBit(unsigned short pos) {
		if (pos >= len) return false;
		unsigned char mask = 1 << (pos % 8);
		bits[pos / 8] ^= mask; // bit-xor the mask
		return ((bits[pos / 8] >> (pos % 8)) & 1); // get bit
	}
	inline bool getBit(unsigned short pos) {
		if (pos >= len) return false;
		return ((bits[pos / 8] >> (pos % 8)) & 1);
	}
	void clearAll() {
		unsigned short i = 0, n = sizeof(bits);
		while (i < n) bits[i++] = 0;
	}
	void setAll() {
		unsigned short i = 0, n = sizeof(bits);
		while (i < n) bits[i++] = 255;
	}
	void toggleAll() {
		unsigned short i = 0, n = sizeof(bits);
		while (i < n) bits[i++] ^= 255;
	}
	bool *toBoolArray() {
		unsigned short i = 0;
		bool *ret = new bool[len];
		while (i < len) ret[i] = getBit(i), i++;
		return ret;
	}
	char *toString() {
		char *ret = new char(len + 1);
		unsigned short i = 0;
		for (; i < len; i++)
			ret[i] = getBit(len - i - 1) ? '1' : '0';
		ret[i] = 0;
		return ret;
	}
	static BitString bitAnd(BitString bs1, BitString bs2) {
		BitString ret(bs1.len > bs2.len ? bs1.len : bs2.len);
		unsigned short i = 0,
			n = sizeof(bs1.bits) > sizeof(bs2.bits)
				? sizeof(bs1.bits) : sizeof(bs2.bits);
		for (; i < n; i++) ret.bits[i] = bs1.bits[i] & bs2.bits[i];
		return ret;
	}
	static BitString bitOr(BitString bs1, BitString bs2) {
		BitString ret(bs1.len > bs2.len ? bs1.len : bs2.len);
		unsigned short i = 0,
			n = sizeof(bs1.bits) > sizeof(bs2.bits)
				? sizeof(bs1.bits) : sizeof(bs2.bits);
		for (; i < n; i++) ret.bits[i] = bs1.bits[i] | bs2.bits[i];
		return ret;
	}
	static BitString bitXor(BitString bs1, BitString bs2) {
		BitString ret(bs1.len > bs2.len ? bs1.len : bs2.len);
		unsigned short i = 0,
			n = sizeof(bs1.bits) > sizeof(bs2.bits)
				? sizeof(bs1.bits) : sizeof(bs2.bits);
		for (; i < n; i++) ret.bits[i] = bs1.bits[i] ^ bs2.bits[i];
		return ret;
	}
	void bitAnd(BitString bs2) { *this = bitAnd(*this, bs2); }
	void bitOr(BitString bs2) { *this = bitOr(*this, bs2); }
	void bitXor(BitString bs2) { *this = bitXor(*this, bs2); }
	inline unsigned short length() const { return len; }
	bool operator [](unsigned short pos) { return getBit(pos); }
	BitString operator &(BitString bs2) { return bitAnd(*this, bs2); }
	BitString operator |(BitString bs2) { return bitOr(*this, bs2); }
	BitString operator ^(BitString bs2) { return bitXor(*this, bs2); }
	BitString operator !() {
		BitString ret(*this);
		ret.toggleAll();
		return ret;
	}
	friend ostream &operator <<(ostream &os, BitString bs);
	operator char*() { return toString(); }
	operator bool*() { return toBoolArray(); }
};
ostream &operator <<(ostream &os, BitString bs) {
	os << bs.toString(); return os;
}

int main() {
	bool bits[] = { 0, 1, 0, 1, 1 };
	BitString bs(bits, sizeof(bits) / sizeof(bool));
	cout << string(bs.toString()) << endl;
	bs.setBit(0);
	bs.clearBit(4);
	bs.toggleBit(3);
	bs = !bs;
	int i = 0;
	for (; i < bs.length(); i++) { cout << bs[i]; }
	cout << endl;
	delete[] bits;
	bool *bits2 = bs.toBoolArray();
	for (i = 0; i < bs.length(); i++) { cout << bits2[i]; }
	cout << endl << BitString("0100110") << endl;
	return 0;
}

