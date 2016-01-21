/*
 * Abstract interface for hashtables
 */
 
#include <string>

template <class t>
class hash_entry
{
	std::string key;
	t value;
	
	public:
	hash_entry() { key = ""; value = t(); };
	hash_entry(std::string k, t v) : key(k), value(v) {};
	std::string get_key() { return key; };
	t get_value() { return value; };
	void set_key(std::string k) { key = k; }
	void set_value(t v) { value = v; }
};

class hashtable
{	
	public :
	
	virtual int hash(int) = 0;
	virtual bool contains(int) = 0;
	virtual void add(int) = 0;
	virtual bool remove(int) = 0;	
};

