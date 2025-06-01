#include "Dummy.hpp"

Dummy::Dummy() : ATarget("Target Practice Dummy")
{}

Dummy::~Dummy(){}

Dummy* Dummy::clone()
{
	return (new Dummy());
}