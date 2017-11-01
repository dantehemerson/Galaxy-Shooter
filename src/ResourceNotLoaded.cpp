#include "ResourceNotLoaded.hpp"

ResourceNotLoaded::ResourceNotLoaded(const std::string& urlResource) :
	Exception("Error Este recurso no se cargo correctamente " + urlResource) {

}