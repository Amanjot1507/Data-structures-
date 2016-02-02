/*
 * Priority queue implementation using heaps with distinct priorities
 */

#include <vector>
#include <iostream>

template <class t>
struct node
{
	public:
	
	int priority;
	t data;
};

template <class t>
class priorityqueue
{
	std::vector<node<t>> heap;	
	void heapify(int);
	
	public :
	
	priorityqueue() : heap(std::vector<node<t>>()) {};
	priorityqueue(std::vector<t>);
	void insert(int, t);
	t extract_max();
	t find_max();
	bool increase_priority(t, int);
	int size() { return heap.size(); };
	void display();
};

template <class t>
bool priorityqueue<t>::increase_priority(t val, int new_priority)
{
	int i = 0;
	bool found = false;
	
	for(i=0;i<heap.size();i++)
	{
		if(heap[i].data == val)
		{
			heap[i].priority = new_priority;
			found = true;
			break;
		}
	}
	
	if(found == true)
	{
		while(i > 0)
		{
			int p = (i % 2 == 0 ? (i-2)/2 : (i-1)/2);
		
			if(heap[p].priority > heap[i].priority)
				break;
		
			node<t> temp = heap[p];
			heap[p] = heap[i];
			heap[i] = temp;
			
			i = p;
		}
		
		return true;
	}
	else
		return false;
};

template <class t>
void priorityqueue<t>::display()
{
	for(int i=0;i<heap.size();i++)
	{
		std::cout<<heap[i].priority<<"\t"<<heap[i].data<<"\n";
	}
	std::cout<<std::endl;
};

template <class t>
priorityqueue<t>::priorityqueue(std::vector<t> arr)
{
	heap = std::vector<node<t>>();
	
	for(int i=0;i<arr.size();i++)
		insert(i,arr[i]);
};

template <class t>
void priorityqueue<t>::heapify(int i)
{
	int left = 2*i+1, right = 2*i+2, largest = i;
	
	if(left < heap.size() && heap[left].priority > heap[largest].priority)
		largest = left;
	if(right < heap.size() && heap[right].priority > heap[largest].priority) 
		largest = right;
	
	if(largest != i)
	{
		node<t> temp = heap[largest];
		heap[largest] = heap[i];
		heap[i] = temp;
		
		heapify(largest);
	}
};

template <class t>
void priorityqueue<t>::insert(int p, t val)
{	
	node<t> n;
	n.priority = p;
	n.data = val;
	
	heap.push_back(n);
	
	for(int i=heap.size()-1;i>0;)
	{
		int p = (i % 2 == 0 ? (i-2)/2 : (i-1)/2);
		
		if(heap[p].priority > heap[i].priority)
			break;
		
		node<t> temp = heap[p];
		heap[p] = heap[i];
		heap[i] = temp;
		
		i = p;
	}
	
};

template <class t>
t priorityqueue<t>::find_max()
{
	if(heap.size() != 0)
		return heap[0].data;
	else
		return t();
};

template <class t>
t priorityqueue<t>::extract_max()
{
	if(heap.size() != 0)
	{
		node<t> temp = heap[0];
		heap[0] = heap[heap.size()-1];
		heap[heap.size()-1] = temp;
		heap.pop_back();
		
		heapify(0);
		
		return temp.data;
	}
	else
		return t();
};
