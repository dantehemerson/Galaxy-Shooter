#include "Exception.hpp"

using std::string;

Exception::Exception(const string& description) : description(description) {

}

const std::string& Exception::what() const {
	return description;
}