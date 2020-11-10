#include "addable_sqrt_number.hpp"

addable_sqrt_number addable_sqrt_number::operator=(const addable_sqrt_number& b)
{
	elements = b.elements;
	return *this;
}

addable_sqrt_number addable_sqrt_number::operator=(addable_sqrt_number&& b)
{
	elements = std::move(b.elements);
	return *this;
}
