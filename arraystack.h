/*
 * Array backed generic stack
 */

template <class t>
class arraystack
{
	int m_top;
	int m_size;
	t* stack;
	void restructure();
	
	public :
	
	arraystack() : m_top(0), m_size(10), stack(new t[m_size]) {};
	int size();
	bool empty();
	int pop();
	void push(t);
	t top();
	void display();
};

template <class t>
void arraystack<t>::display()
{
	for(int i=0;i<m_top;i++)
		std::cout<<stack[i]<<std::endl;
};

template <class t>
int arraystack<t>::size()
{
	return m_top;
};

template <class t>
bool arraystack<t>::empty()
{
	return m_top == 0;
};

template <class t>
int arraystack<t>::pop()
{
	if(m_top == 0)
		return 0;
	
	stack[m_top--] = t();
	return 1;
};

template <class t>
void arraystack<t>::push(t ele)
{
	if(m_top == m_size)
		restructure();
		
	stack[m_top] = ele;	
	m_top++;
};

template <class t>
t arraystack<t>::top()
{
	return stack[m_top-1];
};

template <class t>
void arraystack<t>::restructure()
{
	m_size *= 2;
	t *newstack = new t[m_size];
	
	for(int i=0;i<m_top;i++)
		newstack[i] = stack[i];
	
	delete[] stack;
	stack = newstack;	
};
