#include "Serializer.hpp"

/*

Example of how the reinterpration works under different data type

struct Header { int   id;   // 4 bytes
				short type; // 2 bytes
				// …
			  };

Header h{ 42, 7 };
char  raw[sizeof(Header)];
des, src, n bytes;
std::memcpy(raw, &h, sizeof(Header));  // legal—treat h’s memory as bytes

// Later, reinterpret raw bytes as a Header*
Header* hp = reinterpret_cast<Header*>(raw);
std::cout << hp->id << ", " << hp->type;  // frequently works,
										  // but strictly only if alignment is correct

 */



int main()
{
	std::cout << "Test CASE: 1" << std::endl;
	std::cout << "Data struct contains \"test\" and \"42\"" << std::endl;
	Data*		data_ptr = new Data("test", 42);
	uintptr_t	int_ptr;

	std::cout << "Before serialization - data_ptr Address: " << data_ptr << std::endl;
	std::cout << "Before serialization - data_ptr Data: " << data_ptr->text << ", " << data_ptr->num << std::endl;

	int_ptr = Serializer::serialize(data_ptr);
	std::cout << "New uintptr_t of data_ptr representation: " << int_ptr << std::endl;
	data_ptr = Serializer::deserialize(int_ptr);
	std::cout << "After serialization  - data_ptr Address: " << data_ptr << std::endl;
	std::cout << "After serialization - data_ptr Data: " << data_ptr->text << ", " << data_ptr->num << std::endl;

	delete data_ptr;
	return (0);
}