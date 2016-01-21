#include <iostream>

template <class t>
struct linkedlistNode
{
	t data;
	linkedlistNode *next;
};

template <class t>
class linkedlist
{
	linkedlistNode<t> *head;
	linkedlistNode<t> *tail;
	
	public:
	
	linkedlist() : head(nullptr), tail(nullptr) {};
	linkedlistNode<t>* get_head() { return head; };
	linkedlistNode<t>* get_tail() { return tail; };
	linkedlistNode<t>* get_item(t data);
	bool is_empty() { return head == nullptr; };
	void push_back(t data);
	void pop_back();
	void push_front(t data);
	void pop_front();
	bool remove(t data);
	void reverse_linkedlist();
	void display_linkedlist();
	void destroy();
};

template <class t>
linkedlistNode<t>* linkedlist<t>::get_item(t data)
{
	linkedlistNode<t> *curr = head;
	
	while(curr)
	{
		if(curr->data == data)
			return curr;
		
		curr = curr->next;
	}
	
	return curr;
}

template <class t>
void linkedlist<t>::destroy()
{
	if(head)
	{
		while(head != nullptr)
		{
			linkedlistNode<t> *temp = head;
			head = head->next;
			free(temp);
		}
	}
	
	head = tail = nullptr;
	//free(this);
}

template <class t>
void linkedlist<t>::display_linkedlist()
{
	linkedlistNode<t> *curr = head;
	
	while(curr)
	{
		std::cout<<curr->data<<"->";
		curr = curr->next;
	}
	
	std::cout<<"NULL"<<std::endl;
};

template <class t>
void linkedlist<t>::push_back(t data)
{
	linkedlistNode<t> *ele = new linkedlistNode<t>;
	ele->data = data;
	ele->next = nullptr;
	
	if(head == nullptr)
	{
		head = tail = ele;
	}
	else
	{
		tail->next = ele;
		tail = ele;
	}
}

template <class t>
void linkedlist<t>::pop_back()
{
	if(head != nullptr)
	{
		if(head == tail)
		{
			head = tail = nullptr;
		}
		else
		{
			linkedlistNode<t> *curr = head;
			
			while(curr->next != tail)
			{
				curr = curr->next;
			}
			
			curr->next = nullptr;
			free(tail);
			tail = curr;
		}
	}
}

template <class t>
void linkedlist<t>::push_front(t data)
{
	linkedlistNode<t> *ele = new linkedlistNode<t>;
	ele->data = data;
	ele->next = head;
	
	if(head == nullptr)
		head = tail = ele;
	else
		head = ele;
}

template <class t>
void linkedlist<t>::pop_front()
{
	if(head != nullptr)
	{
		if(head == tail)
			head = tail = nullptr;
		else
		{
			linkedlistNode<t> *temp = head;
			head = head->next;
			free(temp);
		}
	}
}

template <class t>
bool linkedlist<t>::remove(t data)
{
	if(head->data == data)
	{
		this->pop_front();		
		return true;
	}
	
	if(tail->data == data)
	{
		this->pop_back();
		return true;
	}
	
	linkedlistNode<t> *curr = head->next, *prev = curr;
	
	while(curr != tail)
	{
		if(curr->data == data)
			break;
		
		prev = curr;
		curr = curr->next;
	}
	
	if(curr == nullptr)
		return false;
	else
	{
		prev->next = curr->next;
		free(curr);
		
		return true;
	}
}
