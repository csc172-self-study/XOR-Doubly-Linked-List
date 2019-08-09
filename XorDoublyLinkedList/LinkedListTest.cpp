/*
 * LinkedListTest.cpp
 *
 * Driver to test the XOR doubly linked list.
 *
 *  Created on: Aug 8, 2019
 *      Author: alex
 */

#include "LinkedList.h"
#include <iostream>
using std::cout;

int main() {
	LinkedList<int> list;

	// Test append and length
	for (int i = 0; i < 100; ++i) {
		list.append(i);
	}
	cout << "List should be 100 elements long: " << list.length() << "\n";

	// Why not?
	for (int i = 100; i < 1000; ++i) {
		list.append(i);
	}
	cout << "List should be 1000 elements long: " << list.length() << "\n";

	// Test moveToFront and getVal
	list.moveToFront();
	cout << "First value is " << list.getVal() << "\n";

	// Test next
	list.next();
	cout << "Next value is " << list.getVal() << "\n";

	// Test moveToPos, getPos
	list.moveToPos(176);
	cout << "The value at " << list.getPos() << " is " << list.getVal() << "\n";

	// Test prev, insert
	list.prev();
	list.insert(929);
	cout << "The value at " << list.getPos() << " is " << list.getVal() << "; the length is now " << list.length() << "\n";

	// Test remove
	list.moveToPos(100);
	cout << "The value at " << list.getPos() << " was " << list.remove() << "; after removing this value, the length is now " << list.length() << " and the value at " << list.getPos() << " is " << list.getVal() << "\n";

	// Test moveToEnd, freelist
	cout << "Testing freelist... \n";
	list.moveToEnd();
	list.insert(2201);
	cout << "List value at end is " << list.getVal() << ", which should be in a space that used to be on the freelist. \n";

	// Test clear
	list.clear();
	cout << "List should be cleared: " << list.length() << "\n";

}


