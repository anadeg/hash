#include "inner_adressing.h"
#include <cassert>
double hash_table::fill_coefficient()
{
	return static_cast<double>(this->fillness) / this->table.size();
}

int hash_table::letter_to_number(char letter)
{
	for (int i = 0; i < alphabet.size(); i++)
	{
		if (alphabet[i] == letter)
		{
			return i;
		}
	}
}

int hash_table::get_key(std::string id)
{
	int range_for_key = 0;
	int key = 0;
	if (id.size() > 3)
	{
		range_for_key = 3;
	}
	else
	{
		range_for_key = id.size();
	}
	for (int i = 0; i < range_for_key; i++)
	{
		key += alphabet.size() * letter_to_number(id[i]);
	}
	return key;
}

int hash_table::get_hash_adress(int v)
{
	return v % (this->table.size());
}

int hash_table::find_free_cell(int used_index)
{
	for (int i = 0; i < this->table.size(); i++)
	{
		if (i == used_index)
		{
			continue;
		}
		if (this->table[i].used == false)
		{
			return i;
		}
	}
	return -1;
}

void hash_table::add(std::string id, std::string data)
{
	assert(this->fillness < this->table.size());
	int key = get_key(id);
	int hash_adress = get_hash_adress(key);
	int ha = hash_adress;
	if (this->table[ha].id == id && this->table[ha].data == data)
	{
		return;
	}
	if (this->table[hash_adress].used == true)
	{
		//int ha = hash_adress;
		/*
		if (this->table[ha].id == id && this->table[ha].data == data)
		{
			return;
		}
		*/
		while (this->table[ha].next != -1)
		{
			if (this->table[ha].id == id && this->table[ha].data == data)
			{
				return;
			}
			ha = this->table[ha].next;
		}

		int collision_index = find_free_cell(ha);

		this->table[ha].next = collision_index;
		this->table[ha].collision = true;

		this->table[collision_index].id = id;
		this->table[collision_index].data = data;
		this->table[collision_index].key = key;
		this->table[collision_index].collision = true;
		this->table[collision_index].used = true;
	}
	else
	{
		this->table[hash_adress].id = id;
		this->table[hash_adress].data = data;
		this->table[hash_adress].key = key;
		this->table[hash_adress].used = true;
	}
	this->fillness++;
}

void hash_table::del(std::string id)
{
	assert(this->fillness > 0);
	int key = get_key(id);
	int hash_adress = get_hash_adress(key);
	int previous_ha = hash_adress;
	int ha = hash_adress;

 	if (this->table[hash_adress].used == false)
	{
		return;
	}

	if (this->table[hash_adress].collision == true)
	{
		while (this->table[ha].id != id)
		{
			previous_ha = ha;
			ha = this->table[ha].next;
		}
		/*if (this->table[ha].next == -1)
		{
			if (previous_ha == hash_adress)
			{
				this->table[previous_ha].collision = false;
			}
			//this->table[previous_ha].next = -1;
		}
		//this->table[previous_ha].next = this->table[ha].next;
		/*else
		{
			this->table[previous_ha].next = this->table[ha].next;
		}*/
	}
	this->table[ha].used = false;
	this->table[ha].deleted = true;
	this->fillness--;
}

std::string bool_to_string(bool b)
{
	if (b == false)
	{
		return "0";
	}
	else
	{
		return "1";
	}
}

std::string hash_table::print_searched_element(std::string id)
{
	std::string result;
	int key = get_key(id);
	int hash_adress = get_hash_adress(key);
	int ha = hash_adress;
	if (this->table[hash_adress].collision == true)
	{
		while (this->table[ha].id != id)
		{
			if (this->table[ha].next != -1)
			{
				ha = this->table[ha].next;
			}
		}
	}
	if(this->table[ha].id != id)
	{
		return "\nno such element";
	}
	result += "\nid: " + this->table[ha].id + "\ndata: " + this->table[ha].data + "\nkey: " + std::to_string(this->table[ha].key)
		+ "\ncollision: " + bool_to_string(this->table[ha].collision) + "\nused: " + bool_to_string(this->table[ha].used) +
		"\ndeleted: " + bool_to_string(this->table[ha].deleted) + "\nnext: " + std::to_string(this->table[ha].next);
	return result;
}

void hash_table::print_table()
{
	std::cout << "\n  id   | data | key |collision| used | deleted | next";
	for (int i = 0; i < this->table.size(); i++)
	{
		std::cout << std::endl << this->table[i].id << '\t' << this->table[i].data << '\t' << this->table[i].key << '\t' << this->table[i].collision
			<< '\t' << this->table[i].used << '\t' << this->table[i].deleted << '\t' << this->table[i].next;
	}
	std::cout << "\n--------------------------------------------------------\n";
}

int main()
{
	hash_table ht;
	ht.add("yoi", "hsdf");
	ht.add("oiy", "kwnx");//collision
	ht.add("ioy", "qmsa");//collision
	ht.add("tde", "amxl");//collision
	ht.add("aai", "kajs");

	ht.add("yoi", "hsdf");
	ht.add("zzz", "kwnx");//collision
	ht.add("ysf", "qmsa");//collision
	ht.add("oiu", "amxl");//collision
	ht.add("atr", "kajs");

	ht.print_table();

	ht.del("aai");
	std::cout << ht.print_searched_element("aai");

	std::cout << std::endl;

	ht.del("oiu");
	std::cout << ht.print_searched_element("oiu");

	std::cout << std::endl;

	ht.del("zzz");
	std::cout << ht.print_searched_element("zzz");

	ht.print_table();
};