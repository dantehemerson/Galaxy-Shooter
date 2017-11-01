#pragma once
#ifndef RESOURCENOTLOADED_HPP
#define RESOURCENOTLOADED_HPP

#include <string>

#include "Exception.hpp"

class ResourceNotLoaded : public Exception {
public:
	ResourceNotLoaded(const std::string& urlResource);
};

#endif // !RESOURCENOTLOADED_HPP
