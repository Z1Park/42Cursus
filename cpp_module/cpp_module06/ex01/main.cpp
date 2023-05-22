
#include <iostream>
#include <string>

struct Data {
	std::string data;
};

uintptr_t serialize(Data *ptr) {
	return reinterpret_cast<uintptr_t>(ptr);
}

Data* deserialize(uintptr_t raw) {
	return reinterpret_cast<Data *>(raw);
}

int main() {
	Data data;
	Data *dataPtr;
	uintptr_t uintptr;

	data.data = "data for data of data";
	std::cout << "before serialize : " << &data << ", " << data.data << std::endl;
	uintptr = serialize(&data);
	std::cout << "after serialize : " << uintptr << std::endl;
	dataPtr = deserialize(uintptr);
	std::cout << "after deserialize : " << &data << ", " << dataPtr->data << std::endl;

	return 0;
}
