/*
Name of Program: BenyamainYacoob_Project1.cpp
Purpose of Program: Create your own Stack methods
Author: B. Yacoob
*/

#include <iostream>
using namespace std;

class DLLNode {
public:
	// Declaration of variables
	char info;	// Stores data inside a node
	DLLNode* next, * prev;	// Move between predecessor and successor nodes

	// Default constructor
	DLLNode() {
		next = prev = 0;
	}
	// More specified constructor that looks for certain parameters
	DLLNode(int i, DLLNode* n = 0, DLLNode* p = 0) {
		info = i; next = n; prev = p;
	}
};

class StackByDLL {
private:
	// Declaration of variables
	DLLNode* head, * tail, * tmp;	// Pointers
	int size;	// Number of elements in the stack

public:
	bool isEmpty() {	// Checks if list is empty
		if (tail != 0) {
			return false;	// List is not empty
		}
		else return true;	// List is empty; return true to method call
	}
	void push(char val) {	// Storing a value inside the Stack (LIFO)

		if (tail != 0) {	// If list is not empty, create a new node
			tail = new DLLNode(val, 0, tail);
			tail->prev->next = tail;	// Set the new tail
		}
		else head = tail = new DLLNode(val);	// First node, which both the head and tail points to

		++size;	// Add one element
	}
	void pop() {	// Removing a node (LIFO)
		if (head == tail) {	// Same memory address (node) to which it points to, then delete
			delete head;
			head = tail = 0;	// Set to null
		}
		else {	// If more than one node in the list
			tail = tail->prev;	// Set tail pointer to previous node address
			delete tail->next;	// Current tail pointer next 
			tail->next = 0;
		}

		--size;	// Remove one element
	}

	bool removeStackContent(char val) {	// Method for actual content deletion
		if (val == ']' && top() == '[') {	// Most recent matches closing, pop the top
			pop();
			return true;
		}
		else if (val == ')' && top() == '(') {	// Those in top are in the list, val is not
			pop();
			return true;
		}
		else if (val == '}' && top() == '{') {
			pop();
			return true;
		}
		else return false;	// There is no balanced expression
	}
	char top() {	// Informs us of the top value on the Stack
		if (tail != 0) {
			return tail->info;	// Tail pointer reveals most recent addition to the list
		}
	}
	void clear() {	// Clear the contents in the Stack
		while (size != 0) {	// If size of Stack list is not empty, delete list
			pop();	// Keep popping until size == 0
		}
	}
	void display() {	// Displays the contents in the Stack
		tmp = head;	// Get copy of where head is at in order to trace code

		// OUTPUT
		if (!isEmpty()) {
			cout << "Stack elements are: ";
			for (int i = 0; i < size; i++) {
				cout << tmp->info << ' ';
				tmp = tmp->next;	// Update the tmp pointer
			}
			cout << "\n\n";
		}
		else {
			cout << "Stack is empty.\n\n";
		}
	}
};

int main() {
	// Declaration of variables
	StackByDLL* s = new StackByDLL();
	bool balancedFlag = true;
	string expr;

	// INPUT
	cout << "Enter an expression (* to terminate): ";
	cin >> expr;

	while (expr != "*") {	// Do not terminate loop as long as '*' is not pressed

		s->clear();	// Previous content in list is cleared

		// Enter your implementation to parse the input expression here
		for (int i = 0; i < expr.length(); i++) {
			switch (expr[i]) {
				case '[': case '(': case '{':
					s->push(expr[i]);	// Push into Stack list
					break;
				case ']': case ')': case '}':
					balancedFlag = s->removeStackContent(expr[i]);	// Return boolean if there is a balance
					break;
				default:	// Do nothing if program runs into a number or non-accepted character
					break;
			}

			// If not balanced expression, break out of for loop to prevent unnecessary popping
			if (balancedFlag == false) {
				break;
			}
		}

		// Still need to evaluate characters that were not potentially popped
		if (!s->isEmpty()) {
			balancedFlag = false;
		}

		// Conditional statement that determines if input expression is balanced or not
		if (balancedFlag)
			cout << "Expression is balanced! \n";
		else
			cout << "Expression is not balanced! \n";

		s->display();	// Method call to then display content of the Stack (balanced or not)

		cout << "Enter an expression (* to terminate): ";
		cin >> expr;

		balancedFlag = true;	// Still in the while loop, so original boolean value declared is never referenced
	}
	cout << "\nEND OF PROGRAM. \n";

	return 0;
}

