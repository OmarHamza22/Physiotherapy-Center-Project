#pragma once
#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"

#include <iostream>
#include <time.h>
using namespace std;

template <typename T>
class LinkedList
{
private:
	Node<T>* Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
public:
	LinkedList()
	{
		Head = nullptr;
	}

	// creates random n node values and add them to the linked list
	LinkedList(int n)
	{
		Head = nullptr;
		if (n < 1)
			return;

		// adding the first Node --> Must be separated from the original loop
		// because it updates the head
		srand((int)time(NULL));
		int data = rand() % 10; // random from 0 to 9
		Head = new Node<T>(data);

		Node<T>* tail = Head;
		for (int i = 0; i < n - 1; i++)
		{
			data = rand() % 10; // random from 0 to 9
			Node<T>* ptr = new Node<T>(data);

			tail->setNext(ptr);
			tail = ptr;
		}
	}

	// creates linked list from the passed array
	LinkedList(T* arr, int size)
	{
		Head = nullptr;
		if (size < 1)
			return;

		// adding the first Node --> Must be separated from the original loop
		// because it updates the head
		Head = new Node<T>(arr[0]);

		Node<T>* tail = Head;
		for (int i = 1; i < size; i++)
		{
			Node<T>* ptr = new Node<T>(arr[i]);

			tail->setNext(ptr);
			tail = ptr;
		}
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	void PrintList()	const
	{
		cout << "\nprinting list contents:\n\n";
		Node<T>* current = Head;

		while (current)
		{
			cout << "[ " << current->getItem() << " ]";
			cout << "--->";
			current = current->getNext();
		}
		cout << "*\n";
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	*
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T& data)
	{
		Node<T>* R = new Node<T>(data);

		R->setNext(Head);
		Head = R;
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}

	////////////////////////////////////////////////////////////////////////
	//InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd(const T& data)
	{
		Node<T>* R = new Node<T>(data);

		Node<T>* P = Head;
		if (!P)
		{
			P = R;
		}
		while (P->getNext())
			P = P->getNext();

		P->setNext(R);
	}

	////////////////////////////////////////////////////////////////////////
	//RemoveFirst
	//removes and returns the first node from the list
	Node<T>* RemoveFirst()
	{
		Node<T>* p = Head;
		if (Head)
		{
			Head = Head->getNext();
			p->setNext(nullptr);
		}
		return p;

	}

	////////////////////////////////////////////////////////////////////////
	/*
	* Function: Copy Constructor
	* Copies all nodes of the passed linked list to this list.
	*
	* Parameters:
	*	- data : The linked list to be copied to the current list (this list).
	*/

	LinkedList(const LinkedList<T>& L)
	{
		if (!L.Head)	//L is empty
		{
			Head = nullptr;
			count = 0;
			return;
		}

		Head = new Node<T>(L.Head->getItem());	//allocate head node
		Node<T>* tail = Head;
		Node<T>* p = L.Head->getNext();
		while (p)
		{
			Node<T>* R = new Node<T>(p->getItem());	//create a new node
			tail->setNext(R);
			tail = R;
			p = p->getNext();
		}
	}

	////////////////////////////////////////////////////////////////////////
	/*
	* Function: Assignment operator overloading
	* Assigns RHS to this list by copiing all nodes of the passed linked list to this list.
	*
	* Parameters:
	*	- data : The linked list to be copied to the current list (this list).
	*
	* Return:
	*	a copy of the linked list to enable assignment cascading  L1 = L2 = L3;
	*/

	const LinkedList<T>& operator =(const LinkedList<T>& RHS)
	{
		if (Head == RHS.Head) return *this;	//RHS of "=" operator is the same as LHS

		if (!RHS.Head)	//L is empty
		{
			Head = nullptr;
			count = 0;
			return *this;
		}

		Head = new Node<T>(RHS.Head->getItem());	//allocate head node
		Node<T>* tail = Head;

		Node<T>* p = RHS.Head->getNext();

		while (p)
		{
			Node<T>* R = new Node<T>(p->getItem());	//create a new node
			tail->setNext(R);
			tail = R;
			p = p->getNext();
		}
		return *this;
	}

	// NEW FUNCTIONS --> from Exercises =================

	// Removes the last element from the list and returns a Node * to the removed node
	Node<T>* RemoveLast()
	{
		if (!Head)
			return nullptr;

		Node<T>* p = Head;

		if (!p->getNext()) // only one node
		{
			Head = nullptr;
			return p;
		}

		while (p->getNext()->getNext())
			p = p->getNext();

		Node<T>* q = p->getNext(); // last node

		p->setNext(nullptr);
		return q;
	}

	// Delete ALL Nodes that contains the passed value
	void DeleteNodesVal(int value)
	{
		if (!Head)
			return;

		// remove any equal values from the beginning
		// should be in a separate condition because it updates the "Head" itself not a temporary pointer
		while (Head && Head->getItem() == value)
		{
			Node<T>* temp = Head;
			Head = Head->getNext();
			delete temp;
		}
		Node<T>* prev = Head;



		// here is the main loop (will not update the Head)
		while (prev && prev->getNext()) // prev will go out from the loop pointing to the last element
		{
			if (prev->getNext()->getItem() == value)
			{
				Node<T>* temp = prev->getNext();
				prev->setNext(temp->getNext());
				delete temp;
			}
			prev = prev->getNext();
		}

	}
};

#endif	


