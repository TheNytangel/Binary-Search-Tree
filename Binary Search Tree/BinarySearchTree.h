#pragma once

#include <memory>

using namespace std;


template <class T>
class BinarySearchTree
{
public:
	class Node;

	bool add(T dataToAdd)
	{
		// If the root doesn't exist, make the new value the root
		if (root == NULL)
		{
			root = make_shared<typename BinarySearchTree<T>::Node>(dataToAdd);

			return true;
		}

		// A root exists, so go to the bottom/top of the tree and make a new leaf
		shared_ptr<typename BinarySearchTree<T>::Node> currentNode = root;
		while (true)
		{
			// The data is a duplicate so stop
			if (currentNode->data == dataToAdd)
			{
				return false;
			}

			// Go left of the tree
			if (dataToAdd < currentNode->data)
			{
				// The data doesn't exist on the left of the tree
				if (currentNode->lessThanSide == NULL)
				{
					currentNode->lessThanSide = make_shared<typename BinarySearchTree<T>::Node>(dataToAdd);

					return true;
				}

				// Go down the left side
				currentNode = currentNode->lessThanSide;
				continue;
			}

			// Go right of the tree
			if (dataToAdd > currentNode->data)
			{
				// The data doesn't exist on the right of the tree
				if (currentNode->greaterThanSide == NULL)
				{
					currentNode->greaterThanSide = make_shared<typename BinarySearchTree<T>::Node>(dataToAdd);

					return true;
				}

				// Go down the right side
				currentNode = currentNode->greaterThanSide;
				continue;
			}
		}
	}

	// Find a value and return its node so the user has something to pass into delete function
	shared_ptr<typename BinarySearchTree<T>::Node> find(T dataToFind)
	{
		shared_ptr<typename BinarySearchTree<T>::Node> tempNode = root;
		// This will check if root is null or if we got to the end of the tree without finding a value
		while (tempNode != NULL)
		{
			// If data matches, return the pointer
			if (tempNode->data == dataToFind)
			{
				return tempNode;
			}

			// Go down the left side if the data is less than the node's data
			if (dataToFind < tempNode->data)
			{
				tempNode = tempNode->lessThanSide;
				
				continue;
			}

			// Go down the right side if the data is greater than the node's data
			if (dataToFind > tempNode->data)
			{
				tempNode = tempNode->greaterThanSide;

				continue;
			}
		}

		// Return null if nothing was found or tree is empty
		return tempNode;
	}

	void remove(shared_ptr<typename BinarySearchTree<T>::Node> nodeToDelete)
	{
		// Tree is empty so do nothing || the passed-in node is null and you can't delete that
		if (root == NULL || nodeToDelete == NULL)
		{
			return;
		}

		// Check if the node has both things extending from the bottom - if both, do something
		if (nodeToDelete->lessThanSide != NULL && nodeToDelete->greaterThanSide != NULL)
		{
			// Find the minimum value on this branch's right side and set this one's value to that
			shared_ptr<typename BinarySearchTree<T>::Node> min = findMin(nodeToDelete->greaterThanSide);

			// Temporarily store the data. Can't set the data right away because then when it does
			// the remove function right below it, there is duplicate data and there is infinite recursion
			// and it breaks
			T tempData = min->data;
			
			// Then delete the old min that we just got rid of
			// Recursive function! Ahhh!!
			remove(min);

			// Now set the data
			nodeToDelete->data = tempData;

			return;
		}

		// Find parent branch
		shared_ptr<typename BinarySearchTree<T>::Node> parent = findParentNode(nodeToDelete);

		// Check if just one - if just one, put that one in this node's place
		// There is something on the left side of this node
		if (nodeToDelete->lessThanSide != NULL)
		{
			// If parent is null (this is the root) just set the root to the left side
			if (parent == NULL)
			{
				root = nodeToDelete->lessThanSide;

				return;
			}
			
			// Put what was on this node's left hand side in the correct position in the parent
			// This checks what side the deleted node was on in the parent and puts the left side there
			if (parent->lessThanSide == nodeToDelete)
				parent->lessThanSide = nodeToDelete->lessThanSide;
			else
				parent->greaterThanSide = nodeToDelete->lessThanSide;

			return;
		}

		// There is something on the right side of this node
		if (nodeToDelete->greaterThanSide != NULL)
		{
			// If parent is null (this is the root) just set the root to the right side
			if (parent == NULL)
			{
				root = nodeToDelete->greaterThanSide;

				return;
			}

			// Put what was on this node's right hand side in the correct position in the parent
			// This checks what side the deleted node was on in the parent and puts the right side there
			if (parent->greaterThanSide == nodeToDelete)
				parent->greaterThanSide = nodeToDelete->greaterThanSide;
			else
				parent->lessThanSide = nodeToDelete->greaterThanSide;

			return;
		}

		// Check if no extending nodes - if none, just remove it
		if (nodeToDelete->lessThanSide == NULL && nodeToDelete->greaterThanSide == NULL)
		{
			// If it's the parent is null, this is root, so set root to null to delete it
			if (parent == NULL)
			{
				root = NULL;
				
				return;
			}

			// Check which side the node to delete is on. Whichever it's on, set that node to null
			if (parent->lessThanSide == nodeToDelete)
			{
				parent->lessThanSide = NULL;

				return;
			}

			// Check which side the node to delete is on. Whichever it's on, set that node to null (part 2)
			if (parent->greaterThanSide == nodeToDelete)
			{
				parent->greaterThanSide = NULL;

				return;
			}
		}
	}

	T maximum()
	{
		// Nothing exists in the BST so return 0
		if (root == NULL)
		{
			return 0;
		}

		// Temporary node to find the max
		shared_ptr<typename BinarySearchTree<T>::Node> tempNode = root;

		// loop through until there is no greater side of the BST
		while (tempNode->greaterThanSide != NULL)
		{
			tempNode = tempNode->greaterThanSide;
		}

		// Return the greatest side
		return tempNode->data;
	}

	shared_ptr<typename BinarySearchTree<T>::Node> getRoot()
	{
		return root;
	}

private:
	shared_ptr<typename BinarySearchTree<T>::Node> root = NULL;

	shared_ptr<typename BinarySearchTree<T>::Node> findParentNode(shared_ptr<typename BinarySearchTree<T>::Node> child)
	{
		// If this is the root, it has no parent, so return null
		if (child == root)
		{
			return NULL;
		}

		// Store a temporary pointer and traverse the tree looking for the parent node
		shared_ptr<typename BinarySearchTree<T>::Node> currentNode = root;
		// Check if the curren't node's children are the node we are looking for
		while (currentNode->lessThanSide != child && currentNode->greaterThanSide != child)
		{
			// If the node whose parent we're looking for's data is less than the current node's data, go left down the tree
			if (child->data < currentNode->data)
			{
				currentNode = currentNode->lessThanSide;
				continue;
			}

			// If the node whose parent we're looking for's data is greater than the current node's data, go right down the tree
			if (child->data > currentNode->data)
			{
				currentNode = currentNode->greaterThanSide;
				continue;
			}
		}

		return currentNode;
	}

	shared_ptr<typename BinarySearchTree<T>::Node> findMin(shared_ptr<typename BinarySearchTree<T>::Node> currentNode)
	{
		// Can't find the min of no pointer so return nothing
		if (currentNode == NULL)
		{
			return NULL;
		}

		// Temp pointer
		shared_ptr<typename BinarySearchTree<T>::Node> tempNode = currentNode;
		// Loop through until there is no more left side
		while (tempNode->lessThanSide != NULL)
		{
			tempNode = tempNode->lessThanSide;
		}

		// Return the min's pointer
		return tempNode;
	}

public:
	class Node
	{
		friend class BinarySearchTree;

		shared_ptr<typename BinarySearchTree<T>::Node> lessThanSide = NULL;
		shared_ptr<typename BinarySearchTree<T>::Node> greaterThanSide = NULL;

	public:
		Node(T newData) : data(newData) {}
		T data;

		shared_ptr<typename BinarySearchTree<T>::Node> getLessThanSide()
		{
			return lessThanSide;
		}
		shared_ptr<typename BinarySearchTree<T>::Node> getGreaterThanSide()
		{
			return greaterThanSide;
		}
	};
};
