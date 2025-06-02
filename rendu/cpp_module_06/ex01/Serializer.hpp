#pragma once

#include <iostream>
#include <string>
#include <stdint.h>

	struct Data
	{
		std::string text;
		int			num;
	};

class Serializer
{
	public:
		static uintptr_t serialize(Data* ptr);
		static Data* deserialize(uintptr_t raw);

	private:
		Serializer();
		Serializer(const Serializer&);
		const Serializer& operator=(const Serializer&);
		~Serializer();
};
