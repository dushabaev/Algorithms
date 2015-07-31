#pragma once
#include <fstream>

class DataBase {
public:
	DataBase();
	DataBase(std::ifstream& file);
	template<typename T>
	DataBase(T& filename);
	~DataBase();

	template<typename T>
	void load_from_file(T& filename);

	size_t get_films() const { return this->films; };
	size_t get_users() const { return this->users; };

	size_t get_inversion(size_t user_x, size_t user_y);

private:
	size_t users;
	size_t films;
	size_t **db;

	inline void parse_file(std::ifstream& file);
	inline void free();
	inline void alloc();

	inline size_t* build_array(size_t user_x, size_t user_y);
};

template<typename T>
inline DataBase::DataBase(T& filename)
{
	this->load_from_file(filename);
}

template<typename T>
inline void DataBase::load_from_file(T& filename)
{
	std::ifstream file(filename);
	this->parse_file(file);
}
