#pragma once
#ifndef EXCEPTION
#define EXCEPTION

#include <string>

class Exception {
public:
	Exception(const std::string& description);
	virtual const std::string& what() const;

protected:
	std::string description;
};

#endif // !EXCEPTION
