/*
 * Hash table with collisions handled by linear probing 
 * key type = string
 * value type = any
 */

#include <iostream>
#include <vector>
#include <string>

template <class t>
class hash_entry
{
	std::string key;
	t value;
	
	public:
	hash_entry() { key = ""; value = t(); };
	hash_entry(std::string k) : key(k) , value() {};
	hash_entry(std::string k, t v) : key(k), value(v) {};
	bool is_null(hash_entry<t> h) { return h.get_key() == ""; };
	std::string get_key() { return key; };
	t get_value() { return value; };
	void set_key(std::string k) { key = k; }
	void set_value(t v) { value = v; }
};

template <class t>
class htlp
{
	const std::string deleted_flag = "##";	
	int size;
	int num_elements;
	int num_deleted;
	std::vector<hash_entry<t>> table;	
	
	public:
	
	htlp(int n) : size(n), num_elements(0), num_deleted(0), table(size) { };
	int hash(std::string);
	hash_entry<t> contains(std::string, t);
	int add(std::string, t);
	int remove(std::string, t);
	void display_htlp();
	void restructure();
};

template <class t>
void htlp<t>::display_htlp()
{
	for(int i=0;i<size;i++)
		std::cout<<table[i].get_key()<<"\t"<<table[i].get_value()<<std::endl;
}

template<class t>
int htlp<t>::hash(std::string key)
{
	int res = 0;
	
	for(auto it=key.begin();it!=key.end();it++)
		res += *it;
		
	return res % size;
}

template <class t>
int htlp<t>::add(std::string key, t value)
{
	if(num_elements == size || key == "")
		return 0;
		
	if(num_deleted == size/2)
		restructure();
		
	hash_entry<t> h(key, value);
		
	int index = hash(key), orig = index;
	
	do
	{
		if(table[index].get_key() == "" || table[index].get_key() == deleted_flag)
		{
			table[index] = h;
			num_elements++;
			return 1;
		}
		
		index = (index + 1) % size;
		
	}while(index != orig);
	
	return 0;	
}

template <class t>
hash_entry<t> htlp<t>::contains(std::string key, t value)
{
	if(num_elements == 0 || key == "")
		return hash_entry<t>();
		
	int index = hash(key), orig = index;
	
	do
	{
		if(table[index].get_key() == "")
			return hash_entry<t>();
		if(table[index].get_key() == key && table[index].get_value() == value)
			return table[index];
		
		index = (index + 1) % size;
	}while(index != orig);
	
	return hash_entry<t>();
}

template <class t>
int htlp<t>::remove(std::string key, t value)
{
	if(num_elements == 0 || key == "")
		return 0;
		
	int index = hash(key), orig = index;
	
	do
	{
		if(table[index].get_key() == "")
			return 0;
		if(table[index].get_key() == key && table[index].get_value() == value)
		{
			table[index] = hash_entry<t>(deleted_flag);
			num_deleted++;
			num_elements--;
			return 1;
		}
		
		index = (index + 1) % size;
		
	}while(index != orig);
	
	return 0;
}

template <class t>
void htlp<t>::restructure()
{
	std::vector<hash_entry<t>> newtable(size);
	
	for(int i=0;i<size;i++)
	{
		std::string k = table[i].get_key();
		
		if(k == "" || k == deleted_flag)
			continue;
		
		int index = hash(k);
	
		if(table[index].get_key() == "")
			newtable[index] = table[i];
		else
		{		
			while(newtable[index].get_key() != "")
				index = (index + 1) % size;
			
			newtable[index] = table[i];
		}
	}
	
	table = newtable;
}
