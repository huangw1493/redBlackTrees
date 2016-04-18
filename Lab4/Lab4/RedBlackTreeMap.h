#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>

template<typename TKey, typename TValue>
class RedBlackTreeMap {
private:
	class Node {
	public:
		TKey mKey;
		TValue mValue;
		// A weak_ptr does not contribute to a shared_ptr's reference count.
		// This avoids having circular references.
		std::weak_ptr<typename Node> mParent;
		std::shared_ptr<Node> mLeft;
		std::shared_ptr<Node> mRight;
		bool mIsRed;

		Node(const TKey &key, const TValue &value, bool isRed)
			: mKey(key), mValue(value), mIsRed(isRed), mParent(),
			mLeft(), mRight() {
		}
	};

	std::shared_ptr<Node> mRoot;
	int mCount;
	static std::shared_ptr<Node> NIL_NODE;
	//Given a key to find and a node to start at,
	// proceed left/right from the current node until finding a node whose 
	// key is equal to the given key.
	std::shared_ptr<Node> bstFind(const TKey &key, Node *currentNode) {
		// TODO: write this method. 
		// Hint: from a std::shared_ptr<Node> value, you can get a raw Node* using the 
		// .get() function, as in:
		// Node *temp = currentNode->mLeft.get();
		// Use < and > to compare the keys of nodes to determine left/right.
		//return nullptr;
		Node *seeker = currentNode;

		//Run until key is found. Break within loop
		while (seeker.key != key) {
			//reached end of tree. not found
			if (seeker->key == null) {
				return null;
			}
			//travel to left node if key is smaller or equal to current node
			else if (key <= seeker->key) {
				seeker = seeker->mleft;
			}
			//travel to right node if key is greater than current node
			else if (key > seeker->key) {
				seeker = seeker->mRight;
			}
			//If we found the value, return the sharedptr
			else if (key == seeker->key)
				return seeker;
			//Keep this line here just for debugging. We'll delete it when we confirm that the first
			//statement catches all the bad things.
			else {
				std::cout << "something went horribly wrong" << std::endl;
				return null;
			}
		}
	}

	std::shared_ptr<Node> getGrandparent(Node *n) {
		// TODO: return the grandparent of n
		//return null;
		Node * tmp = n->mParent;
		return tmp->mParent
	}

	// Gets the uncle (parent's sibling) of n.
	std::shared_ptr<Node> getUncle(Node *n) {
		// TODO: return the uncle of n
		 //If your parent is the left child of your grandparent, return the right child of your grandparent
		if (n->mParent == getGrandparent(n)->mleft) { return getGrandparent(n)->mRight; }
		//If your parent is the right child of your grandparent, return the left child of your grandparent
		else if (n->mParent == getGrandparent(n)->mRight) { return getGrandparent(n)->mLeft; }
		//If grandparent only has one child or you have no uncle, return null
		else { return null; }
	}

	// Rotate the tree right at the given node.
	void rotateRight(std::shared_ptr<Node> n) {
		std::shared_ptr<Node> l = n->mLeft, lr = l->mRight,
			p = n->mParent.lock();

		n->mLeft = lr;
		lr->mParent = n;

		l->mRight = n;
		if (n == mRoot) {
			mRoot = l;
			l->mParent.reset(); // sets to nullptr
		}
		else if (p->mLeft == n) {
			p->mLeft = l;
			l->mParent = p;
		}
		else {
			p->mRight = l;
			l->mParent = p;
		}
		n->mParent = l;
	}

	// Rotate the tree left at the given node.
	void rotateLeft(Node n) {
		// TODO: do a single left rotation (AVL tree calls this a "rr" rotation)
// at n.
 //I just inverted everything. Will change if problems occur
std::shared_ptr<Node> r = n->mRight, rl = r->mleft,
p = n->mParent.lock();

n->mRight = rl;
rl->mParent = n;

r->mLeft = n;
if (n == mRoot) {
	mRoot = l;
	l->mParent.reset(); // sets to nullptr
}
else if (p->mRight == n) {
	p->mRight = l;
	r->mParent = p;
}
else {
	p->mLeft = r;
	r->mParent = p;
}
n->mParent = l;

	}

	// This method is used by insert. It is complete.
	// Inserts the key/value into the BST, and returns true if the key wasn't 
	// previously in the tree.
	bool bstInsert(std::shared_ptr<Node> newNode, std::shared_ptr<Node> currentNode) {
		if (mRoot == nullptr) {
			// case 1
			mRoot = newNode;
			return true;
		}
		else {
			if (currentNode->mKey < newNode->mKey) {
				// newNode is larger; go right.
				if (currentNode->mRight != NIL_NODE)
					return bstInsert(newNode, currentNode->mRight);
				else {
					currentNode->mRight = newNode;
					newNode->mParent = currentNode;
					mCount++;
					return true;
				}
			}
			else if (currentNode->mKey > newNode->mKey) {
				if (currentNode->mLeft != NIL_NODE)
					return bstInsert(newNode, currentNode->mLeft);
				else {
					currentNode->mLeft = newNode;
					newNode->mParent = currentNode;
					mCount++;
					return true;
				}
			}
			else {
				// found a node with the given key; update value.
				currentNode->mValue = newNode->mValue;
				return false; // did NOT insert a new node.
			}
		}
	}


	//This helper function was adapted from code I found here: http://goo.gl/kUoa0u
	//Recursively checks and counts number of black nodes. Paramter must be root.
	//After implementing the check balance, I don't believe I need this, however I'll keep it 
	//for possible use.
	int BlackHeight(std::shared_ptr<Node> n) {
		if (root == nullptr)
			return 1;

		int lHeight = BlackHeight(n->mLeft);
		if (lHeight == 0)
			return lHeight;

		int rHeight = BlackHeight(n->mRight);
		if (rHeight == 0)
			return rHeight;

		if (lHeight != rHeight)
			return 0;
		else
			return (lHeight + n->isRed) ? 1 : 0;
	}
	
	//This function inverts the grandparent's color of the node and the parents color.
	//Used in check 5 of checkbalance
	void invertGP(std::shared_ptr<Node> n) {
		if (n->mParent.isRed == true) {
			n->mParent.isRed = false;
		}
		else
			n->mParent.isRed = true;
		if (getGrandparent(n).isRed == true) {
			n->mParent.isRed = false;
		}
		else
			n->mParent.isRed = true;
	}


	// Applies rules 1-5 to check the balance of a tree with newly inserted node n.  
	void checkBalance(std::shared_ptr<Node> n) {
		mRoot->isRed = false;
		//Case 1: If(n == root){return;}
		if (mRoot == n) { return; }
		//Case 2: if(parent = black){return;}
		if (n->mParent.isRed() == false) { return; }
		//Case 3: if(parent == red && uncle == red){
		//	parent = black; uncle = black;
		//	grandparent = red;
		// checkbalance(g);
		if ((n->mParent.isRed() == true) && (getUncle(n).isRed == true)) {
			n->mParent.isRed = false;
			getUncle(n).isRed = false;
			getGrandparent(n).isRed = true;
		}
		checkBalance(getGrandparent(n));

		/*Case 4: if(n is rl}{
					rotate left(parent)
					checkbalacne(parent)
				else if(n is lr){
					rotate right(parent)
					checkbalacne(parent)
		*/
		if (n->mKey >= n->mParent.mKey && n->mParent.mKey < getGrandparent(n).mKey) {
			rotateLeft(n->mParent);
			checkBalance(n->mParent);
		}
		else if ((n->mKey <= n->mParent.mKey && n->mParent.mKey > getGrandparent(n).mKey) {
			rotateRight(n->mParent);
			checkBalance(n->mParent);
		}

		//Case 5: 
		// Note that each case is mutually exclusive, EXCEPT THAT case 4 must flow
		// into case 5.
		// Also note that case 3 recursively examines the grandparent after the
		// recoloring.
		/*
		if(N is ll)
			rotate right(g)
			invertgp(n);
		if(N is rr)
			rotate left(g)
			invertgp(n);
		*/
		if (n->mKey >= n->mParent.mKey && n->mParent.mKey > getGrandparent(n).mKey) {
			rotateRight(n->mParent);
			invertgp(n);
		}
		if (n->mKey <= n->mParent.mKey && n->mParent.mKey < getGrandparent(n).mKey) {
			rotateLeft(n->mParent);
			invertGP(n);
		}
	}


public:

	inline int count() const {
		return mCount;
	}

	// Inserts a key/value pair into the tree, updating the red/black balance
	// of nodes as necessary. Starts with a normal BST insert, then adjusts.
	void insert(const TKey &key, const TValue &value) {
		std::shared_ptr<Node> n = std::make_shared<Node>(key, value, true);
		// the node starts red, with null parent, left, and right.

		// normal BST insert; n will be placed into its initial position.
		// returns false if an existing node was updated (no rebalancing needed)
		bool insertedNew = bstInsert(n, mRoot);
		if (!insertedNew)
			return;
		// check cases 1-5 for balance.
		checkBalance(n);
	}

	TValue& find(const TKey &key) {
		Node *n = bstFind(key, mRoot);
		if (n == nullptr || n == NIL_NODE) {
			throw std::out_of_range("Key not found");
		}
		return n->Value;
	}

	// Returns true if the given key is in the tree.
	bool containsKey(const TKey &key) const {
		// TODO: using at most three lines of code, finish this method.
		// HINT: write the bstFind method first.
		return false;
	}


	// Prints a pre-order traversal of the tree's nodes, printing the key, value,
	// and color of each node.
	void printStructure() {
		// TODO: a pre-order traversal. Will need recursion.
	}


};

template<typename TK, typename TV>
std::shared_ptr<typename RedBlackTreeMap<TK, TV>::Node> RedBlackTreeMap<TK, TV>::NIL_NODE =
std::make_shared<typename RedBlackTreeMap<TK, TV>::Node>(TK(), TV(), false);