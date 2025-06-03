#include "Serializer.hpp"

Serializer::Serializer() {}
Serializer::Serializer(const Serializer& refObj) { *this = refObj; }
const Serializer& Serializer::operator=(const Serializer& refObj) { (void) refObj; return(*this); }
Serializer::~Serializer() {};

// simple re-iterpration of pointer address into int.
// uintptr_t guarantess that the pointer address will always fit into the type on any system

// operations is onloy valid in the same process memory space / data exist

uintptr_t Serializer::serialize(Data* ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
};


Data* Serializer::deserialize(uintptr_t raw) 
{
	return (reinterpret_cast<Data*>(raw));
};
