#pragma once

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

class Utils {
public:
	/* Convierte una cadena de texto en entero. */
	static int strToInt(const std::string& str);

	/* Convierte un entero a cadena de texto(string). */
	static std::string intToStr(int n);

	static float degressToRad(float grades);
};
#endif // !UTILS_HPP
