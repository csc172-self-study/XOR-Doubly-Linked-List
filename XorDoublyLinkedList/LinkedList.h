/*
 * LinkedList.h
 *
 *  Created on: Jul 10, 2019
 *      Author: alex
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "Link.h"

template <typename E>
class LinkedList {
private:
	Link<E>* head;
	Link<E>* tail;
	// Need to track pointers to both current and previous links in list, so that we can XOR to get the next pointer
	Link<E>* currLink;
	Link<E>* prevLink;
	int size;

	// Initialize list with separate head and tail (head <-> tail)
	void init() {
		head = new Link<E>;
		tail = new Link<E>;
		head->setNext(Link<E>::nullLink, tail);
		tail->setPrev(Link<E>::nullLink, head);
		currLink = head;
		prevLink = head->getPrev(tail);	// For consistency - should always be nullLink
		size = 0;
	}

	// Remove all links from list
	void removeall() {
		prevLink = Link<E>::nullLink;
		while(head != Link<E>::nullLink) {
			currLink = head;
			head = head->getNext(prevLink);
			prevLink = currLink;
			delete currLink;
		}
	}

public:
	// Constructor
	LinkedList(int size = 0) {
		init();
	}

	// Destructor removes to freelist
	virtual ~LinkedList() {
		removeall();
	}

	// Clear removes to freelist and reinitializes list
	void clear() {
		removeall();
		init();
	}

	// Insert link at current position
	void insert(const E& elem) {
		// prev -> current -> new -> next -> later
		// Get next pointer
		Link<E>* nextLink = currLink->getNext(prevLink);
		// Create new link
		Link<E>* newLink = new Link<E>(elem, nextLink, currLink);
		// Set new link to be left of "next"
		nextLink->setPrev(currLink, newLink);
		// Update current link pointer
		currLink->setNext(nextLink, newLink);
		// Update tail if required
		if (tail == currLink) tail = newLink;
		size++;
	}

	// Append link to tail of list
	void append(const E& elem) {
		Link<E>* tailPrev = tail->getPrev(Link<E>::nullLink);
		Link<E>* newLink = new Link<E>(elem, tailPrev, tail);
		tailPrev->setNext(tail, newLink);
		tail->setPrev(tailPrev, newLink);
		size++;
	}

	// Remove link from current position and return item
	E remove() {
		// prev -> current -> || next || -> later
		if (currLink->getNext(prevLink) == tail) throw "No element.";
		E elem = (currLink->getNext(prevLink))->getVal();
		Link<E>* next = currLink->getNext(prevLink);
		Link<E>* later = next->getNext(currLink);
		later->setPrev(next, currLink);
		currLink->setNext(next, later);
		delete next;
		size--;
		return elem;
	}

	// Move to head of list
	void moveToFront() {
		currLink = head;
		prevLink = Link<E>::nullLink;
	}

	// Move to tail of list
	void moveToEnd() {
		currLink = tail->getPrev(Link<E>::nullLink);
		prevLink = currLink->getPrev(tail);
	}

	// Move to previous link
	void prev() {
		if (currLink == head) throw "Already at head of list.";
		Link<E>* newNext = currLink;
		currLink = prevLink;
		prevLink = currLink->getPrev(newNext);
	}

	// Move to next link
	void next() {
		if (currLink == tail->getPrev(Link<E>::nullLink)) throw "Already at tail of list.";
		Link<E>* newPrev = prevLink;
		prevLink = currLink;
		currLink = currLink->getNext(newPrev);
	}

	// Return length of list
	int length() {
		return size;
	}

	// Return current position in list
	int getPos() {
		Link<E>* tempNext = Link<E>::nullLink;
		Link<E>* temp = head;
		Link<E>* tempPrev = Link<E>::nullLink;
		int i;
		for (i = 0; currLink != temp; i++) {
			tempNext = temp->getNext(tempPrev);
			tempPrev = temp;
			temp = tempNext;
		}
		return i;
	}

	// Move to given position
	void moveToPos(int pos) {
		if (pos < 0 || pos > size) throw "Position out of range of list.";
		this->moveToFront();
		for (int i = 0; i < pos; i++) {
			this->next();
		}
	}

	// Return value at current position
	const E& getVal() {
		if (currLink->getNext(prevLink) == Link<E>::nullLink) throw "No value.";
		Link<E>* link = currLink->getNext(prevLink);
		return link->getVal();
	}
};

#endif /* LINKEDLIST_H_ */
