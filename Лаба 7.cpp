#include <iostream>
#include <string>
#include <exception>
#include<time.h>
#include <cstdlib>        

using namespace std;

template <class T>
class Ring;

class Kotik {
private:
	int id;
	string name;
	string diagnos;
public:
	Kotik() :id(0), name("Blank "), diagnos("Blank ") { }
	Kotik(string t_name, string t_diagnos, int id) :name(t_name),diagnos(t_diagnos),id(id) { }
	~Kotik() { }
	bool operator< (const Kotik& kot) { return id < kot.id; }
	bool operator> (const Kotik& kot) { return id > kot.id; }
	bool operator== (const Kotik& kot) { return id == kot.id && name == kot.name; }
	friend ostream& operator<< (ostream& out, const Kotik& Kotik)
	{
		out << Kotik.id << ' ' << Kotik.name << ' ' << Kotik.diagnos << '\n'; return out;
	}

};

class Exception
{
public:
	Exception(const string errorMessage = "Something wrong") : m_ErrorMessage(errorMessage) { }
	friend ostream& operator<< (ostream& out, const Exception& ex) { out << ex.m_ErrorMessage << '\n'; return out; }
private:
	string m_ErrorMessage;
};

template <class T>
struct Node {
	T value;
	Node* left, * right;
	Node() : value() { left = right = nullptr; }
};

template <class T>
class Iterator
{
public:
	friend class Ring<T>;
	//friend void swomp(Iterator<T> , Iterator<T> );
	Iterator(Node<T>* node = nullptr) : node(node) { }
	~Iterator() { }
	Iterator(const Iterator& it) { node = it.node; }
	Iterator& operator=(const Iterator& it) { node = it.node; return *this; }
	T& operator*() {
		if (node == nullptr)
			throw Exception("Empty iterator");
		return node->value;
	}
	T* operator->() { if (node == nullptr) throw Exception("Empty iterator"); return &node->value; }
	Iterator& operator++() { if (node == nullptr) throw Exception("Empty iterator"); node = node->right; return *this; }
	Iterator& operator--() { if (node == nullptr) throw Exception("Empty iterator"); node = node->left; return *this; }
	Iterator operator++(int unused) { if (node == nullptr) throw Exception("Empty iterator"); Iterator res = *this; node = node->right; return res; }
	Iterator operator--(int unused) { if (node == nullptr) throw Exception("Empty iterator"); Iterator res = *this; node = node->left; return res; }
	bool operator== (const Iterator& it) { return node == it.node; }
	bool operator!= (const Iterator& it) { return node != it.node; }
private:
	Node<T>* node;
};

template<class T>
class Ring
{
public:
	typedef Iterator<T> Iterator;
public:
	Ring() : head(nullptr) {}
	~Ring()
	{
		Node<T>* it = head;
		while (it->right != nullptr)
			it = it->right;
		while (it != nullptr) {
			Node<T>* temp = it;
			it = it->left;
			temp->right = nullptr;
			delete temp;
		}
	}
	void push(T value, bool unique=false)
	{
		if (unique) {
			Iterator it = find(value);
			if (it != null()) {
				throw Exception("duplicate value find");
			}
		}
		Node<T>* newNode = new Node<T>();
		newNode->value = value;
		newNode->right = nullptr;
		newNode->left = nullptr;
		if (head != nullptr) {
			head->right = newNode;
			newNode->left = head;
		}
		head = newNode;
	}
	void pop()
	{
		if (head == nullptr)
			throw Exception("Ring is empty");
		Node<T>* temp = head;
		head = head->left;
		head->right = nullptr;
		delete temp;
	}
	Iterator erase(Iterator);
	Iterator find(T value) const;
	void show() const;
	Iterator begin() { return Iterator(head); }
	Iterator null() { return Iterator(); }
private:
	Node<T>* head;
};

template<class T>
typename Ring<T>::Iterator Ring<T>::erase(Ring<T>::Iterator it)
{
	if (head == nullptr)
		throw Exception("Ring is empty");
	if (it == null())
		throw Exception("Invalid iterator");
	Node<T>* temp = it.node;
	if (it.node->left != nullptr) {
		it.node = it.node->left;
		it.node->right = temp->right;
		if(temp->right!=nullptr)
			temp->right->left = it.node;
		delete temp;
		return it;
	}
	else {
		Node<T>* temp = it.node;
		it.node = it.node->right;
		it.node->left = nullptr;
		delete temp;
		return it;
	}
}

template<class T>
typename Ring<T>::Iterator Ring<T>::find(T value) const
{
	Node<T>* it = head;
	do
	{
		if (it->value == value)
			return Iterator(it);
		it = it->left;
	} while (it != nullptr);
	return Iterator();
}

template<class T>
void Ring<T>::show() const
{
	Node<T>* it = head;
	do
	{
		cout << ' ' << it->value;
		it = it->left;
	} while (it != nullptr);
	cout << '\n';
}

template<class T>
void fastSort(Iterator<T> begin, int l,int r,int all)
{
	if (begin == Iterator<T>())
		throw Exception("Invalid iterator");
	Iterator<T> it = begin;
	Iterator<T> en = begin;
	if (all-l >=all- r) return;
	for (int i = 0;i < l-1;i++)en--;
	cout << "\n" << *en << "\n";
	cout << "\n" << *begin << "\n";
	
	/*for (int i = 0;i < l / 2;i++)
		it--;
	T mid = *it;
	cout <<"\n" <<mid<<"\n";
	for (int i = 0;i < l / 2;i++)
		it++;	swap(*it,mid);*/
	for(int i=all-l;i<=all-r;i++)
	{
		cout << i<<" *en1 " << *en << " *it1 " << *it;
		if (*en < *it) { swap(*it, *en); }
		cout << " *en2 " << *en << " *it2 " << *it;
		en++;
		
	}
	fastSort(begin,l,r+1,all);
	fastSort(begin, l - 1, r, all);
}
template<class T>
void bubbleSort(Iterator<T> begin) {
	if (begin == Iterator<T>())
		throw Exception("Invalid iterator");
	Iterator<T> it = begin;
	Iterator<T> end = --begin;
	++begin;
	while (begin != end) {
		it = begin;
		while (it != end) {
			Iterator<T> prev = it++;
			if (*it < *prev) {
				T temp = *prev;
				*prev = *it;
				*it = temp;
			}
		}
		--end;
	}
}
template<class T>
void swomp(Iterator<T> begin, Iterator<T> end)
{
	Iterator<T> it = begin;
	Iterator<T> en = end;
	//Iterator<T> temp = it;
	//it.node->right = en.node->right;
	//en.node->right = temp.node->right;
	//it.node->left = en.node->left;
	//en.node->left = temp.node->left;
	//delete(temp);
	T temz = *it;
	*it = *en;
	*en = temz;
}
void my_terminate() {
	cerr << "terminate handler called\n";
	abort();
}
void my_unexpected_handler()
{
	cerr << "Unexpected exception\n";
	terminate();
}

int main() {
	srand(time(NULL));
	set_terminate(my_terminate);
	set_unexpected(my_unexpected_handler);
	Ring<Kotik> ring;
	try {
		ring.pop();
	}
	catch (Exception ex) {
		cerr << ex;
	}
	cout << "Inserting\n";
	try {
		ring.push(Kotik("Stas", "Beba",11));
		ring.show();
		ring.push(Kotik("Danila","Beba", 20));
		ring.show();
		ring.push(Kotik("Anzelika","Beba", 6));
		ring.show();
		ring.push(Kotik("Kek","Beba", 5));
		ring.show();
		ring.push(Kotik("Max", "Beba", 7));
		ring.show();
		ring.push(Kotik("Xim", "Beba", 8));
		ring.show();
	}
	catch (Exception ex) {	cerr << ex;	}
	try {
		int gg = 0;
		ring.pop();
		ring.show();
		ring.erase(ring.find(Kotik("Kek", "Beba", 5)));
		ring.show();
		swomp(ring.find(Kotik("Danila", "Beba", 20)), ring.find(Kotik("Anzelika", "Beba", 6)));
		fastSort(ring.begin(),4,0,4);
		ring.show();
	}
	catch (Exception ex) { cerr << ex; }
	/*
	cout << "After sort\n";
	try {
		bubbleSort(ring.begin());
	}
	catch (Exception ex) {
		cerr << ex;
	}
	ring.show();
	cout << '\n';
	/*cout << "Popping\n";
	try {
		ring.pop_back();
		ring.show();
		ring.pop_front();
		ring.show();
		ring.erase(ring.find(Kotik("Max","Beba", 6)));
		ring.show();
	}
	catch (Exception ex) {
		cerr << ex;
	}

	cout << '\n';

	cout << "Setting same value\n";
	try {
		ring.push(Kotik("Kek", "Beba", 5), true);
	}
	catch (Exception ex) {
		cerr << ex;
	}
	ring.show();

	Ring<double> ring1;
	try {
		ring1.push(4);
		ring1.show();
		ring1.push(2);
		ring1.show();
		ring1.push(1);
		ring1.show();
		ring1.push(0);
		ring1.show();
		ring1.push(3);
		ring1.show();
		ring1.push(7);
		ring1.show();
	}
	catch (Exception ex) {
		cerr << ex;
	}
	
	try {
		bubbleSort(ring1.begin());
	}
	catch (Exception ex) {
		cerr << ex;
	}
	ring1.show();

	return 0;*/
}