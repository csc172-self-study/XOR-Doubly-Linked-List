/*
 * XDLL.h
 *
 *  Created on: Jul 10, 2019
 *      Author: alex
 *
 *      Node for doubly linked list class, with next and previous stored as XOR of pointers
 */

#ifndef LINK_H_
#define LINK_H_

#include <cstddef>
#include <stddef.h>
#include <stdint.h>

template <typename E>
class Link {
private:
	static Link<E>* freelist;
	Link<E>* nextXORprev;
	E element;

public:
	static Link<E>* nullLink;

	Link(const E& elem, Link<E>* prev, Link<E>* next) {
		element = elem;
		nextXORprev = XOR(next,prev);
	}

	Link(Link<E>* prev = nullLink, Link<E>* next = nullLink) {
		nextXORprev = XOR(next,prev);
	}

	void* operator new(size_t) {
		if (freelist == nullLink) return ::new Link<E>;
		Link<E>* temp = freelist;
		freelist = XOR(freelist->nextXORprev, nullLink);
		return temp;
	}

	// Freelist is only singly-linked
	void operator delete(void* ptr) {
		((Link<E>*) ptr)->nextXORprev = freelist;
		freelist = (Link<E>*)ptr;
	}

	// Retrieve pointer to next link
	Link<E>* getNext(Link<E>* prev) {
		return XOR(nextXORprev, prev);
	}

	// Retrieve pointer to previous link
	Link<E>* getPrev(Link<E>* next) {
		return XOR(nextXORprev, next);
	}

	Link<E>* setNext(Link<E>* oldNext, Link<E>* newNext) {
		nextXORprev = XOR(getPrev(oldNext), newNext); // retrieve pointer to prev link, then XOR with new next link
		return nextXORprev;
	}

	Link<E>* setPrev(Link<E>* oldPrev, Link<E>* newPrev) {
		nextXORprev = XOR(getNext(oldPrev), newPrev); // retrieve pointer to next link, then XOR with new previous link
		return nextXORprev;
	}

	const E& getVal() {
		return element;
	}

};

template <typename E>
Link<E>* XOR(Link<E>* prev, Link<E>* next) {
	return (Link<E>*) ((uintptr_t) prev ^ (uintptr_t) next);
}

template <typename E>
Link<E>* Link<E>::freelist = NULL;

template <typename E>
Link<E>* Link<E>::nullLink = NULL;

#endif /* LINK_H_ */
