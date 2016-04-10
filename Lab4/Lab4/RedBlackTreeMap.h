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

   std::shared_ptr<Node> bstFind(const TKey &key, Node *currentNode) {
      // TODO: write this method. Given a key to find and a node to start at,
      // proceed left/right from the current node until finding a node whose 
      // key is equal to the given key.
      // Hint: from a std::shared_ptr<Node> value, you can get a raw Node* using the 
      // .get() function, as in:
      // Node *temp = currentNode->mLeft.get();
      // Use < and > to compare the keys of nodes to determine left/right.
      return nullptr;
   }

   std::shared_ptr<Node> getGrandparent(Node *n) {
      // TODO: return the grandparent of n
      return null;
   }

   // Gets the uncle (parent's sibling) of n.
   std::shared_ptr<Node> getUncle(Node *n) {
      // TODO: return the uncle of n
      return null;
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

   // Applies rules 1-5 to check the balance of a tree with newly inserted
   // node n.  
   void checkBalance(std::shared_ptr<Node> n) {
      if (n == mRoot) {
         // case 1: n is the root
         n->mIsRed = false;
      }
      // handle additional insert cases here.
      // Note that each case is mutually exclusive, EXCEPT THAT case 4 must flow
      // into case 5.
      // Also note that case 3 recursively examines the grandparent after the
      // recoloring.
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