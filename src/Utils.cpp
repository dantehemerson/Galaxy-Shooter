#include "Utils.hpp"

#include <sstream>

#define _USE_MATH_DEFINES

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#include <math.h>


using namespace std;

int Utils::strToInt(const string& str) {
	istringstream istr(str);
	int value;
	istr >> value;
	return value;
}

string Utils::intToStr(int n) {
	if (n == 0) {
		return "0";
	}
	string value;
	char mod;
	while (n > 0) {
		mod = n % 10;
		mod += 48;
		value.insert(0, 1, mod);
		n = n / 10;
	}
	return value;
}

float Utils::degressToRad(float grades) {
	return grades * (M_PI / 180.0);
}
