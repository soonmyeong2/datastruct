#include <iostream>
using namespace std;

#define maxStack 100


/**
*	@brief	Exception class thrown by Push when stack is full.
*/
class FullStack
{
public:
	/**
	*	@brief	Display a message for full stack on screen.
	*/
	void print()
	{
		cout << "FullStack exception thrown." << endl;
	}
};


/**
*	@brief	Exception class thrown by Pop and Top when stack is empty.
*/
class EmptyStack
{
public:
	/**
	*	@brief	Display a message for full stack on screen.
	*/
	void print()
	{
		cout << "EmtpyStack exception thrown." << endl;
	}
};


/**
*	@brief	Stack class.
*	@details	This class processes as Last In, First Out (LIFO).
*/
template <typename T>
class Stack
{
public:

	/**
	*	@brief	Allocate dynamic array whose size is maxStack.
	*	@pre	The maxStack is defined
	*	@post	Member of items points the allocated array.
	*/
	Stack();

	Stack(const Stack<T>& stack);

	/**
	*	@brief	Destruct the object. Free the array dynamically allocated.
	*	@pre	Release memory for stack pointer.
	*	@post	none.
	*/
	~Stack();

	/**
	*	@brief	Determines whether the stack is full.
	*	@pre	Stack has been initialized.
	*	@post	Function value = (stack is full)
	*/
	bool IsFull() const;

	/**
	*	@brief	Determines whether the stack is empty.
	*	@pre	Stack has been initialized.
	*	@post	Function value = (stack is empty)
	*/
	bool IsEmpty() const;

	/**
	*	@brief	Adds newItem to the top of the stack.
	*	@pre	Stack has been initialized.
	*	@post	If (stack is full), FullStack exception is thrown; otherwise, newItem is at the top of the stack.
	*/
	void Push(T item);

	/**
	*	@brief	Removes top item from the stack.
	*	@pre	Stack has been initialized.
	*	@post	If (stack is empty), EmptyStack exception is thrown; otherwise, top element has been removed from stack.
	*/
	T Pop();

	/**
	*	@brief	Returns a copy of top item on the stack.
	*	@pre	Stack has been initialized.
	*	@post	If (stack is empty), EmptyStack exception is thrown; otherwise, top element has been removed from stack.
	*/
	T Top();

	/**
	*	@brief	Print all the items in the stack on screen
	*	@pre	Stack has been initialized.
	*	@post	None.
	*/
	void Print();
	/**
	*	@brief	대입연산자 오버로딩
	*	@post	입력받은 스택이 딥카피된다.
	*/
	Stack<T>& operator=(const Stack<T>& stack);
private:
	int top;	///< Number of elements.
	T *items;	///< Pointer for a stack.
};

// Allocate dynamic array whose size is maxStack 500.
template <typename T>
Stack<T>::Stack()
{
	items = new T[maxStack];
	top = -1;
}

template <typename T>
Stack<T>::Stack(const Stack<T>& stack)
{
	items = new T[maxStack];
	top = stack.top;
	for (int i = 0; i < maxStack; i++)
	{
		items = stack[i];
	}
}


// Destruct the object. Free the array dynamically allocated.
template <typename T>
Stack<T>::~Stack()
{
	delete[] items;
}


// Determines whether the stack is full.
template <typename T>
bool Stack<T>::IsEmpty() const
{
	if (top <= -1)
		return true;
	else
		return false;
}


// Determines whether the stack is empty.
template <typename T>
bool Stack<T>::IsFull() const
{
	if (top >= maxStack - 1)
		return true;
	else
		return false;
}

// Adds newItem to the top of the stack.
template <typename T>
void Stack<T>::Push(T newItem)
{
	if (IsFull())
		throw FullStack();
	else
	{
		top++;
		items[top] = newItem;
	}
}

// Removes top item from the stack.
template <typename T>
T Stack<T>::Pop()
{
	T temp;

	if (IsEmpty())
		throw EmptyStack();
	else
	{
		temp = Top();
		top--;
		return temp;
	}
}


// Removes top item from the stack.
template <typename T>
T Stack<T>::Top()
{
	if (IsEmpty())
		throw EmptyStack();
	else
		return items[top];
}


// Print all the items in the stack on screen
template <typename T>
void Stack<T>::Print()
{
	cout << "Stack: ";
	// Stack 내의 모든 element 출력.
	for (int i = top; i >= 0; i--)
	{
		cout << items[i] << " - ";
	}
	cout << endl;
}

//대입연산자 오버로딩
template<typename T>
inline Stack<T>& Stack<T>::operator=(const Stack<T>& stack)
{
	items = new T[maxStack];
	top = stack.top;
	for (int i = 0; i < maxStack; i++)
	{
		items[i] = stack.items[i];
	}
	return *this;
}
