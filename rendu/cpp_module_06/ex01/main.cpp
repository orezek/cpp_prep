#include "Serializer.hpp"

int main()
{
	Data*		data_ptr = new Data;
	uintptr_t	int_ptr;

	std::cout << "Before serialization - Data_ptr: " << data_ptr << std::endl;
	int_ptr = Serializer::serialize(data_ptr);
	std::cout << "uintptr_t of data_ptr: " << int_ptr << std::endl;
	data_ptr = Serializer::deserialize(int_ptr);
	std::cout << "After serialization  - Data_ptr: " << data_ptr << std::endl;

	delete data_ptr;
	return (0);
}