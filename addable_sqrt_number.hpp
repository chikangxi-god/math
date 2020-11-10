#include "sqrt_number.hpp"
#include <vector>

class addable_sqrt_number
{
private:
	std::vector<sqrt_number> elements;

public:
	addable_sqrt_number():elements(){}
	addable_sqrt_number(const addable_sqrt_number& b):elements(b.elements){}
	addable_sqrt_number(addable_sqrt_number&& b):elements(std::move(b.elements)){}
	addable_sqrt_number(const sqrt_number& b):elements({b}){}
	addable_sqrt_number(sqrt_number&& b):elements(){elements.push(std::move(b));}

	addable_sqrt_number operator=(const addable_sqrt_number&);
	addable_sqrt_number operator=(addable_sqrt_number&&);
