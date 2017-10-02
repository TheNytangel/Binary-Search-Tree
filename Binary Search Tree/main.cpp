/*
	Binary Search Tree
	Christopher Peterson
	6/10/17
*/

#include <ctime>
#include <iostream>
#include "BinarySearchTree.h"

int main()
{
	// Seed the "random" number generator
	srand(time(0));

	// Custom test case
	{
		BinarySearchTree<int> tree;

		// Add 2, -2, 4, -4, 6, -6, 8, -8, 10, -10
		for (int i = 2; i <= 10; i += 2)
		{
			tree.add(i);
			tree.add(-1 * i);
		}

		// Add 1, -1, 3, -3, 5, -5, 7, -7, 9, -9, 11, -11
		for (int i = 1; i <= 11; i += 2)
		{
			tree.add(i);
			tree.add(-1 * i);
		}

		// Show the root and some values that we will remove
		cout << "The root of the tree is " << tree.getRoot()->data << "\n";
		cout << "2 was " << (tree.find(2) ? "found" : "not found") << "\n";
		cout << "-11 was " << (tree.find(-11) ? "found" : "not found") << "\n";
		cout << "11 was " << (tree.find(11) ? "found" : "not found") << "\n";
		cout << "5 was " << (tree.find(5) ? "found" : "not found") << "\n";
		cout << "-6 was " << (tree.find(-6) ? "found" : "not found") << "\n\n";

		// Remove the values
		tree.remove(tree.find(2));
		tree.remove(tree.find(-11));
		tree.remove(tree.find(11));
		tree.remove(tree.find(5));
		tree.remove(tree.find(-6));

		// Show the new root and prove that the values are gone
		cout << "The root of the tree is " << tree.getRoot()->data << "\n";
		cout << "2 was " << (tree.find(2) ? "found" : "not found") << "\n";
		cout << "-11 was " << (tree.find(-11) ? "found" : "not found") << "\n";
		cout << "11 was " << (tree.find(11) ? "found" : "not found") << "\n";
		cout << "5 was " << (tree.find(5) ? "found" : "not found") << "\n";
		cout << "-6 was " << (tree.find(-6) ? "found" : "not found") << "\n\n";

		// Test the maximum function
		cout << "The maximum value in the tree is " << tree.maximum() << "\n" << endl;
	}

	// Array of integers test case
	{
		BinarySearchTree<int> tree;

		// Random numbers courtesy of random.org
		int intArray[30] = { 9, 85, 389, 483, 440, 450, 281, 477, 390, 64,
							 108, 50, 291, 122, 370, 153, 358, 368, 216, 277,
							 361, 13, 381, 457, 394, 1, 240, 388, 442, 397 };

		// Add the 30 numbers to the tree
		for (int i = 0; i < 30; ++i)
		{
			tree.add(intArray[i]);
		}

		// Generate a random index
		int randomIndex = rand() % 30;

		// Show that the number is found in the tree
		cout << intArray[randomIndex] << " is currently " << (tree.find(intArray[randomIndex]) ? "" : "not ") << "in the tree\n";
		// Remove the number from the tree
		tree.remove(tree.find(intArray[randomIndex]));
		// Show that the number is no longer in the tree
		cout << intArray[randomIndex] << " is currently " << (tree.find(intArray[randomIndex]) ? "" : "not ") << "in the tree" << endl;
	}

	system("pause");
	return 0;
}