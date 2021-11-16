#pragma once
#include <string>
#include <vector>
#include <iostream>

int SIZE = 25;

class hash_table
{
	const std::vector<char> alphabet =
		//{"a", "b" , "c" , "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
	{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	struct hash_element
	{
		std::string id;
		std::string data;
		int key;
		bool collision;
		bool used;
		bool terminal_flag;
		bool deleted;
		int next;
	};
	int fillness;
	std::vector <hash_element> table;

public:
	hash_table()
	{
		hash_element he;
		he.id = "";
		he.data = "";
		he.key = -1;
		he.collision = false;
		he.used = false;
		he.terminal_flag = false;
		he.deleted = false;
		he.next = -1;
		table.resize(SIZE, he);
		fillness = 0;
	}


	double fill_coefficient();

	int get_key(std::string);
	int letter_to_number(char); //char/string
	int get_hash_adress(int);

	int find_free_cell(int);
	void add(std::string, std::string);
	void del(std::string);
	std::string print_searched_element(std::string);
	void print_table();
};