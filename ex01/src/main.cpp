#include "../includes/Serializer.hpp"

int main()
{
	Data a = {42, "Cenas"};
	uintptr_t	address_serialized = Serializer::serialize(&a);
	Data		*address_deserialized = Serializer::deserialize(address_serialized);

	std::cout << "[Data before]:\n";
	std::cout << "important_number: " << a.important_number << "\n";
	std::cout << "import_str: " << a.import_str << "\n\n";

	std::cout << "This is the address in uint: " << std::hex << address_serialized << "\n" << std::dec;
	std::cout << "This is the address in uint: " << address_deserialized << "\n";

	std::cout << "\n[Data After]:\n";
	std::cout << "important_number: " << address_deserialized->important_number << "\n";
	std::cout << "import_str: " << address_deserialized->import_str << "\n";

}