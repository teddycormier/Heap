// This program creates and maintains a heap class

#include <iostream>
using namespace std;

struct node
{
	int num;
	node *parent;
	node *left;
	node *right;
	node *prev;
	node *next;
};

class heap
{
public:
	node *root;
	node *last;
	node *next_parent;
	node *temp;

	heap() // Constructor
	{
		root = NULL;
		last = NULL;
		next_parent = NULL;
	}

	void search(node *temp, int value) // Searches the heap for the user's request and prints a family summary
	{
		if (temp == NULL)
		{
			cout << "The number is not in the tree\n";
		}
		else if (temp->num == value)
		{
			cout << "Your number is in the tree\n";
		}
		else if (value < temp->num)
		{
			temp = temp->left;
			search(temp, value);
		}
		else
		{
			temp = temp->right;
			search(temp, value);
		}
	}

	void down_heapify(node *temp) // Recursively down heapifies after a deletion
	{
		int dummy;

		// Base Cases
		if (temp->left == NULL && temp->right == NULL) // If you reach the bottom of the tree, stop
		{
			cout << "You've reach the bottom and it's been down heapified.\n";
		}
		else if (temp->right == NULL && temp->left != NULL)
		{
			if (temp->left->num > temp->num)
			{
				dummy = temp->num; // Swap the values
				temp->num = temp->left->num;
				temp->left->num = dummy;
				down_heapify(temp->left); // Call the function, but send it the left
			}
			else
			{
				cout << "It's been down heapified.\n";
			}
		}
		else
		{
			if (temp->num > temp->left->num && temp->num > temp->right->num) // bigger than two kids
			{
				cout << "It's been down heapified.\n";
			}

			// Recursive Case
			else if (temp->num < temp->left->num && temp->num > temp->right->num) // swap left
			{
				dummy = temp->num; // Swap the values
				temp->num = temp->left->num;
				temp->left->num = dummy;
				down_heapify(temp->left); // Call the function, but send it the left
			}
			else if (temp->num > temp->left->num && temp->num < temp->right->num) // swap right
			{
				dummy = temp->num; // Swap the values
				temp->num = temp->right->num;
				temp->right->num = dummy;
				down_heapify(temp->right); // Call the function, but send it the parent
			}
			else if (temp->num < temp->left->num && temp->num < temp->right->num)
			{
				if (temp->left->num > temp->right->num)
				{
					dummy = temp->num; // Swap the values
					temp->num = temp->left->num;
					temp->left->num = dummy;
					down_heapify(temp->left); // Call the function, but send it the parent
				}
				else // go right
				{
					dummy = temp->num; // Swap the values
					temp->num = temp->right->num;
					temp->right->num = dummy;
					down_heapify(temp->right); // Call the function, but send it the parent
				}
			}
		}
	}

	void remove(node *temp, int value) // Removes + replaces the root and calls down_heapify
	{
		node *temp2 = last;

		if (last == root)
		{
			delete root;
			root = NULL;
			last = NULL;
			next_parent = NULL;
			return;
		}

		cout << "This is the root of the heap --> " << root->num;

		root->num = last->num; // copying last value into root

		last = last->prev; // old last->prev becomes last

		last->next = NULL;

		// Toggle the next_parent pointer if needed
		if (temp2 == temp2->parent->left) // case that last is now on prev parent right
		{
			temp2->parent->left = NULL;
		}
		else // case that last is on same parent left
		{
			temp2->parent->right = NULL;
			next_parent = last->parent;
		}

		delete temp2;

		down_heapify(root);
	}

	// These functions are already complete
	void heapify(node *temp)
	{
		int dummy;

		// Base Cases
		if (temp->parent == NULL) // If you reach the top of the tree, stop
		{
			cout << "You've reach the top and it's been heapified.\n";
		}
		else if (temp->parent->num > temp->num) // If you didn't need to swap, stop
		{
			cout << "No swap needed, so it's been heapified.\n";
		}
		// Recursive Case
		else
		{
			dummy = temp->num; // Swap the values
			temp->num = temp->parent->num;
			temp->parent->num = dummy;
			heapify(temp->parent); // Call the function, but send it the parent
		}
	}

	void insert()
	{
		if (root == NULL)
		{
			root = new node;
			cout << "What's the first value to add to the heap: ";
			cin >> root->num;
			root->left = NULL;
			root->right = NULL;
			root->parent = NULL;
			root->next = NULL;
			root->prev = NULL;
			last = root;
			next_parent = root;
		}
		else // Makes a new node and links it in with the tree and linked list
		{
			last->next = new node;
			last->next->prev = last;
			last = last->next;
			cout << "What's the next number: ";
			cin >> last->num;
			last->left = NULL;
			last->right = NULL;
			last->next = NULL;
			last->parent = next_parent;

			// Toggle the next_parent pointer if needed
			if (next_parent->left == NULL)
			{
				next_parent->left = last;
			}
			else
			{
				next_parent->right = last;
				next_parent = next_parent->next;
			}
		}

		heapify(last);
		print();
	}

	void print()
	{
		if (root == NULL)
		{
			cout << "The heap is empty!\n";
			return;
		}

		node *temp = root;

		cout << endl
			 << endl;

		for (int j = 0; j < 5; j++)
		{
			cout << '\t';
		}
		cout << temp->num << endl
			 << endl;
		temp = temp->next;

		for (int j = 1; j < 5; j++)
		{
			cout << '\t';
		}
		for (int i = 0; i < 2; i++)
		{
			if (temp != NULL)
			{
				cout << temp->num << '\t' << '\t';
				temp = temp->next;
			}
		}
		cout << endl
			 << endl;

		cout << "                          ";
		for (int i = 0; i < 4; i++)
		{
			if (temp != NULL)
			{
				cout << temp->num << "        ";
				temp = temp->next;
			}
		}
		cout << endl
			 << endl;

		cout << "                      ";
		for (int i = 0; i < 8; i++)
		{
			if (temp != NULL)
			{
				cout << temp->num << "    ";
				temp = temp->next;
			}
		}
		cout << endl;
	}
};

int main()
{
	heap tree;
	int value;
	int ans = 0;

	// This menu lets you add, delete or print the heap. 1 & 3 already work
	while (ans != 5)
	{
		cout << endl;
		cout << "_______________________________________\n"
			 << "| 1. Print the heap                   |\n"
			 << "| 2. Search the heap                  |\n"
			 << "| 3. Add to the heap                  |\n"
			 << "| 4. Delete the root                  |\n"
			 << "| 5. Quit                             |\n"
			 << "--------------------------------------- \n"
			 << "What do you want to do --> ";
		cin >> ans;

		if (ans == 1)
		{
			tree.print();
		}
		else if (ans == 2)
		{
			cout << "\nWhat number do you want to search for: ";
			cin >> value;
			tree.search(tree.root, value);
		}
		else if (ans == 3)
		{
			tree.insert();
		}
		else if (ans == 4)
		{
			cout << "\nWhat number do you want to delete: ";
			cin >> value;
			tree.remove(tree.root, value);
		}
	}

	return 0;
}
