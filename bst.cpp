#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class bstnode
{
	int val;
	bstnode *left_child;
	bstnode *right_child;
	
	public:
	bstnode() : val(int()), left_child(nullptr), right_child(nullptr) {};
	bstnode(int d) : val(d), left_child(nullptr), right_child(nullptr) {};
	int data() { return val; };
	bstnode* left() { return left_child; };
	bstnode* right() { return right_child; };
	void set_data(int value) { val = value; };
	void set_left(bstnode *left) { left_child = left; };
	void set_right(bstnode *right) { right_child = right; };
};

class bst
{
	bstnode *root;
	
	public :
	bst() : root(nullptr) {};
	bool insert(int);
	int delete_node(int);
	void level_order_traversal();
	bstnode* search(int);
	int height();
};

void bst::level_order_traversal()
{
	if(root)
	{		
		queue<bstnode*> q;
		q.push(root);
		
		while(!q.empty())
		{
			int n = q.size();
			
			for(int i=0;i<n;i++)
			{
				bstnode *curr = q.front();
				q.pop();
				
				cout<<curr->data()<<"\t";
				
				if(curr->left() != nullptr)
					q.push(curr->left());
				if(curr->right() != nullptr)
					q.push(curr->right());				
			}
			
			cout<<"\n";
		}
	}
};

bool bst::insert(int val)
{
	bstnode *node = new bstnode(val);
	
	if(root == nullptr)
		root = node;
	else
	{
		bstnode* parent = root, *curr = root;
		
		while(curr != nullptr)
		{
			parent = curr;
			
			if(node->data() < curr->data())
				curr = curr->left();
			else if(node->data() > curr->data())
				curr = curr->right();
			else
				return false;
		}
		
		if(node->data() > parent->data())
			parent->set_right(node);
		else
			parent->set_left(node);
	}
	
	return true;
};

bstnode* bst::search(int val)
{
	if(root == nullptr)
		return nullptr;
		
	bstnode *curr = root;
	
	while(curr != nullptr)
	{
		if(curr->data() == val)
			break;
		else if(val > curr->data())
				curr = curr->right();
		else curr = curr->left();
	}
	
	return curr;
};

int bst::height()
{
	if(root == nullptr)
		return 0;
		
	int h = 1;
	queue<bstnode*> q;
	q.push(root);
	
	while(!q.empty())
	{
		h++;
		int n = q.size();
		for(int i=0;i<n;i++)
		{
			bstnode *curr = q.front();
			q.pop();
			
			if(curr->left() != nullptr)
				q.push(curr->left());
			if(curr->right() != nullptr)
				q.push(curr->right());				
		}
	}
	
	return h;
};

int bst::delete_node(int val)
{
	bstnode *curr = root, *parent = nullptr;
	
	while(curr != nullptr)
	{
		if(val > curr->data())
		{
			parent = curr;
			curr = curr->right();			
		}
		else
		if(val < curr->data())
		{
			parent = curr;
			curr = curr->left();			
		}
		else
		{
			if(curr->left() == nullptr && curr->right() == nullptr)
			{
				///cout<<parent->data();
				if(parent->left() == curr)
					parent->set_left(nullptr);
				else
					parent->set_right(nullptr);
				
				free(curr);
			}
			else if(curr->left() == nullptr && curr->right() != nullptr)
			{
				if(parent->left() == curr)
					parent->set_left(curr->right());
				else
					parent->set_right(curr->right());
				
				free(curr);
			}
			else if(curr->right() == nullptr && curr->left() != nullptr)
			{
				if(parent->left() == curr)
					parent->set_left(curr->right());
				else
					parent->set_right(curr->right());
				
				
				free(curr);
			}
			else
			{
				bstnode *successor = curr->right();
				
				while(successor->left())
					successor = successor->left();
				
				int succ = successor->data();				
				delete_node(succ);
				curr->set_data(succ);
			}
			
			return true;
		}
		
	}
	
	return false;
};

int main()
{
	int i=0;
	while(true)
		cout<<i++<<"\n";
	return 0;
}
