/*
 * Array based generic queue
 */

#include <iostream>

template <class t>
class arrayqueue
{
	int m_size;
	int m_front;
	int m_rear;
	t *queue;
	void restructure();
	void readjust();
	
	public :
	
	arrayqueue() : m_size(10), m_front(0), m_rear(-1), queue(new t[m_size]) {};
	void push(t);
	int pop();
	t front();
	t back();
	int size();
	bool empty();
	void display();
};

template <class t>
void arrayqueue<t>::display()
{
	for(int i=0;i<m_size;i++)
		std::cout<<queue[i]<<std::endl;
};

template <class t>
void arrayqueue<t>::restructure()
{
	m_size *= 2;
	t *newqueue = new t[m_size];
	
	for(int i=m_front;i<=m_rear;i++)
		newqueue[i] = queue[i];
	
	delete[] queue;
	queue = newqueue;	
};

template <class t>
void arrayqueue<t>::readjust()
{
	int j = 0;
	for(int i=m_front;i<=m_rear;i++,j++)
		queue[j] = queue[i];
	
	m_front = 0;
	m_rear = j-1;
};

template <class t>
void arrayqueue<t>::push(t ele)
{
	if(m_rear == m_size-1)
	{
		if(m_front == 0)
			restructure();
		else
			readjust();
	}
	
	queue[++m_rear] = ele;
};

template <class t>
int arrayqueue<t>::pop()
{
	if(m_front > m_rear)
	{
		m_front = 0;
		m_rear = -1;
		return 0;
	}
	
	m_front++;
	return 1;
};

template <class t>
t arrayqueue<t>::front()
{
	if(m_front > m_rear)
		return t();
	
	return queue[m_front];
};

template <class t>
t arrayqueue<t>::back()
{
	if(m_front > m_rear)
		return t();
	
	return queue[m_rear];
};

template <class t>
int arrayqueue<t>::size()
{
	return m_rear - m_front + 1;
};

template <class t>
bool arrayqueue<t>::empty()
{
	return size() == 0;
};
