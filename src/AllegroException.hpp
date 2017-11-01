#pragma once
#ifndef ALLEGROEXCEPTION_HPP
#define ALLEGROEXCEPTION_HPP

#include <string>

#include "Exception.hpp"

class AllegroException : public Exception {
public:
	explicit AllegroException(const std::string& except);

};

#endif // !ALLEGROEXCEPTION_HPP
