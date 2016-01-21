/*
 * Hash set with separate chaining used for handling collisions
 */
 
#include "LinkedList.h"
#include "hashtable.h"
#include <vector>

class htsc : public hashtable
{
	std::vector<linkedlist<int>> table;
	int size;
	int hash(int);
	
	public :
	
	htsc() { size = 91; table.resize(size); }
	bool contains(int);
	void add(int);
	bool remove(int);
	void display_table();
};

void htsc::display_table()
{
	for(int i=0;i<size;i++)
	{
		std::cout<<i<<"\t";
		table[i].display_linkedlist();
		//std::cout<<std::endl;
	}
};

int htsc::hash(int key)
{
	return key % size;
}

void htsc::add(int key)
{
	int index = hash(key);
	
	if(table[index].get_item(key) == nullptr)
	{
		table[index].push_back(key);
	}
}

bool htsc::contains(int key)
{
	int index = hash(key);
	
	if(table[index].get_item(key) == nullptr)
		return false;
	else
		return true;
}

bool htsc::remove(int key)
{
	int index = hash(key);
	
	return table[index].remove(key);
}
