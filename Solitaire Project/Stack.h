#include"List.h"

template <class T>
class Stack
{
public:
	void initializeStack();
	bool isEmptyStack() const;
	bool isFullStack() const;
	void push(T newItem);
	T top() const;
	Stack(int s);
	T pop();
	int getStackTop();
	int getMaxSize();
private:
	int maxSize;
	int stackTop; 
	List<T> linkedList;
};

template <class T>
void Stack<T>::initializeStack()
{
	stackTop = 0;
}

template <class T>
bool Stack<T>::isEmptyStack() const {
	return stackTop == 0;
}

template <class T>
bool Stack<T>::isFullStack() const
{
	return(stackTop == maxSize);
}

template <class T>
void Stack<T>::push(T newItem)
{
	if (!isFullStack()) {
		linkedList.insertAtTail(newItem);
		stackTop++;
	}
	else {
		cout << "Stack is full!" << endl;
	}
}

template<class T>
inline T Stack<T>::top() const
{
	if (!isEmptyStack()) {
		typename List<T>::Iterator i = linkedList.end();
		--i;
		return *i;
	}
	cout << "Stack is empty" << endl;
}

template<class T>
inline Stack<T>::Stack(int stackSize)
{
		if (stackSize <= 0) {
		cout << "Stack size must be positive. Setting stack size to 100." << endl;
		maxSize = 100;
		}
		else {
			maxSize = stackSize;
		}
		stackTop = 0;
		//linkedList = List<T>();
}

template<class T>
inline T Stack<T>::pop()
{
	if (!isEmptyStack()) {
		typename List<T>::Iterator i = linkedList.end();
		--i;
		T temp = *i;
		linkedList.removeLastElement();
		stackTop--;
		return temp;
	}
	else {
		cout << "Can not pop empty stack!" << endl;
	}
}

template<class T>
inline int Stack<T>::getStackTop()
{
	return this->stackTop;
}

template<class T>
inline int Stack<T>::getMaxSize()
{
	return this->maxSize;
}
