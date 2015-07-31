#include "DataBase.h"
#include <bitset>
#include <string>

template<size_t size>
std::bitset<size> make_first_bits(size_t bits) {
	return std::bitset<size>(std::string(size - bits, '0') += std::string(bits, '1'));
}

DataBase::DataBase() : users{0}, films{0}, db{nullptr}
{
}

DataBase::DataBase(std::ifstream& file)
{
	if (!file.is_open()) {
		this->users = 0;
		this->films = 0;
		this->free();
		throw("file must be opened");
	}
	this->parse_file(file);
}

DataBase::~DataBase()
{
	if (this->db)
		this->free();
}

size_t DataBase::get_inversion(size_t user_x, size_t user_y)
{
	using std::bitset;
	bitset<101> visited;
	size_t res{};

	size_t* arr = this->build_array(user_x, user_y);
	for (size_t i = 0; i < this->films; i++) {
		res += arr[i] -(visited.set(arr[i]) & make_first_bits<101>(arr[i])).count()-1;
	}
	return res;
}

inline void DataBase::parse_file(std::ifstream & file)
{
	file >> this->users >> this->films;
	this->alloc();

	for (size_t i = 0; i < this->users; i++) {
		file.ignore(std::numeric_limits<int>::max(), ' '); // skip first column (because it is index)

		for (size_t j = 0; j < this->films; j++) 
			file >>  this->db[i][j];
	}
}

inline void DataBase::free()
{
	for (size_t i = 0; i < this->users; i++) {
		delete[] this->db[i];
	}
	delete[] this->db;
	this->db = nullptr;
}

inline void DataBase::alloc()
{
	if (this->db)
		this->free();
	this->db = new size_t*[this->users];
	for (size_t i = 0; i < this->users; i++) {
		this->db[i] = new size_t[this->films];
	}
}

inline size_t * DataBase::build_array(size_t user_x, size_t user_y)
{
	size_t* res = new size_t[this->films];

	for (size_t j = 0; j < this->films; j++) 
		res[this->db[user_x][j]-1] = this->db[user_y][j];

	return res;
}
