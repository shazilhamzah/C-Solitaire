#pragma once

template <typename T>
class List
{
	struct Node {
		T data;
		Node* next;
		Node* prev;
		Node() {  this->next = nullptr; this->prev = nullptr; }
		Node(T val) { this->data = val; this->next = nullptr; this->prev = nullptr; }
	};
	Node* head;
	Node* tail;
	int length;
public:
	List();
	List(T val);
	struct Iterator {
		Iterator() { this->current = nullptr; }
		Iterator(Node* ptr) { this->current = ptr; }
		Iterator operator=(Iterator rhs) { this->current = rhs.current; return *this; }
		T operator*() { return this->current->data; }
		Iterator operator++() { this->current = this->current->next; return *this; }
		Iterator operator--() { this->current = this->current->prev; return *this; }
		bool operator==(const Iterator& right) { return this->current == right.current; }
		bool operator!=(const Iterator& right) { return this->current != right.current; }
	private:
		friend class List;
		Node* current;
	};
	Iterator begin() const;
	Iterator end() const;
	void insertAtTail(T& val);
	void removeLastElement();
	void print();
	bool isEmpty();
	int getLength();
	void setLength(int n);
	T& getLastElement();
	//List<T> operator=(List<T>& rhs);
};

/* CONSTRUCTORS	*/
template <typename T>
List<T>::List()
{
	this->head = new Node();
	this->tail = new Node();
	head->next = tail;
	tail->next = nullptr;
	head->prev = nullptr;
	tail->prev = head;
	this->length = 0;
}

template <typename T>
List<T>::List(T val)
{
	this->head = new Node();
	this->tail = new Node();
	Node* newNode = new Node(val);
	head->next = newNode;
	tail->next = nullptr;
	head->prev = nullptr;
	tail->prev = newNode;
	newNode->prev = head;
	newNode->next = tail;
	this->length = 1;
}


/* ITERATOR FUNCTIONS */
template<typename T>
typename List<T>::Iterator List<T>::begin() const
{
	if (head)
	{
		Iterator temp(head);
		return temp;
	}
	return nullptr;
}

template<typename T>
typename List<T>::Iterator List<T>::end() const
{
	if (tail) {
		Iterator temp(tail);
		return temp;
	}
	return nullptr;
}


/* LIST FUNCTIONS */
template<typename T>
void List<T>::insertAtTail(T& val) {
	Node* newNode = new Node(val);
	newNode->next = tail;
	newNode->prev = this->tail->prev;
	this->tail->prev->next = newNode;
	this->tail->prev = newNode;
	this->length++;
}

template<typename T>
inline void List<T>::removeLastElement()
{
	if (head->next != tail) {
		Node* remove = this->tail->prev;
		remove->prev->next = tail;
		this->tail->prev = remove->prev;
		delete remove;
		this->length--;
	}
}

template<typename T>
inline void List<T>::print()
{
	Node* temp = head->next;
	while (temp != tail) {
		cout << temp->data << " -> ";
		temp = temp->next;
	}
	cout << endl;
}

template<typename T>
inline bool List<T>::isEmpty()
{
	if (head) {
		if (head->next == tail) {
			return true;
		}
	}
	return false;
}

template<typename T>
inline int List<T>::getLength()
{
	return length;
}

template<typename T>
inline void List<T>::setLength(int n)
{
	this->length = n;
}

template<typename T>
inline T& List<T>::getLastElement()
{
	if (tail->prev != head) {
		return tail->prev->data;
	}
}
//
//template<typename T>
//inline List<T> List<T>::operator=(List<T>& rhs)
//{
//	this->head = rhs.head;
//	this->tail = rhs.tail;
//	this->length = rhs.length;
//	return *this;
//}