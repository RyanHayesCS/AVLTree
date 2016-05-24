//Ryan Hayes
//Project 1
//Spring 2015
//LCMap AVL implementation

#ifndef LCMAP_H
#define LCMAP_H

#include <list>
#include <cstddef>
#include <functional>
#include <stack>
#include <algorithm>

template<class K,class V,class Comparator = std::less<K> >
class LCMap{
private:
	class LCMapNode{//nested node class for LCMap
	public:
		K key_;
		V value_;
		int height_;//keep track of heights
		LCMapNode* left_;
		LCMapNode* right_;

		LCMapNode() : key_(K()), value_(V()), height_{0}, left_(NULL), right_(NULL) 
		{
		}
		LCMapNode(K key, V value) : key_(key), value_(value), height_{0}, left_(NULL), right_(NULL) 
		{
		}	
		
		//LCMapNode(K key, V value, int height) : key_(key), value_(value), height_(height), left_(NULL), right_(NULL){}

		LCMapNode& operator =(const LCMapNode& rhs)
		{
			key_ = rhs.key_;
			value_ = rhs.value_;
			height_ = rhs.height_;
		}		
	};

public:
	class Iterator{
	private:
		std::stack<LCMapNode*> path_;

	protected:
		friend class LCMap<K, V, Comparator>;

	public:
		Iterator (LCMapNode* n = NULL)//Constructor
		{
			path_.push(NULL);
			normalize(n);	
		}
		/* Derefernces the iterator */
		std::pair<K,V> operator *() const
		{
			std::pair<K,V> keyValuePair;
			if(path_.top() != NULL)//if there is a node
			{
				keyValuePair.first = path_.top()->key_;
				keyValuePair.second = path_.top()->value_;
			}
			return keyValuePair;
		}
	
		/* prefix increment: increment then return reference to current iterator */
		Iterator& operator ++() /*throw(OutOfBoundsException)*/
		{
			if(path_.top() != NULL)
			{
				LCMapNode* old = path_.top();
				path_.pop();
				normalize(old->right_);//update path with right children
			}
			return *this;
		}

		/* postfix increment: should return current iterator and then increment */
		Iterator operator ++(int) /*throw(OutOfBoundsException)*/
		{
			Iterator old = *this;
			++(*this);
			return old;
		}

		/* equality */
		bool operator ==(const Iterator& rhs) const
		{
			return path_.top() == rhs.path_.top();
		}

		/* inequality */
		bool operator !=(const Iterator& rhs) const
		{
			return path_.top() != rhs.path_.top();
		}

	private:
		void normalize(LCMapNode* n)
		{
			if(n != NULL) //if n points to a tree
			{
				path_.push(n);
				while(path_.top()->left_ != NULL)//While we havent reached the left most item
				{
					path_.push(path_.top()->left_);
				}
			}	
		}
		//use stack
	};

private:
	int size_;
	LCMapNode* root_;
	Comparator isLessThan;
		
public:
	/* constructor */
	LCMap(Comparator c = Comparator())
	{
		root_ = NULL;
		size_ = 0;
	}
	/* copy constructor */
	LCMap(const LCMap<K,V,Comparator>& orig)
	{
		root_ = NULL;
		size_ = orig.size_;
		copyLCMapNodes(orig.root_, root_);
	}
	
	/* cleans up all memory for storage and calls the destructor for the
	keys and values stored */
	virtual ~LCMap()
	{
		clear();
	}
	/* assignment operator */
	LCMap<K,V,Comparator>& operator =(const LCMap<K,V,Comparator>& rhs)
	{
		if(&rhs != this)
		{
			clear();
			copyLCMapNodes(rhs.root_, root_);
			size_ = rhs.size_;
		}
		return *this;
	}

	/*inserts the key value pair, only if key not already in map.
	  returns true if insert is successful */

	bool insert(const K& key, const V& value)
	{
		bool retval = insert(root_, key, value);
		if(retval == true)
		{
			size_++;
		}
		return retval;
	}
	
	/* erases key value pair referenced by key.
        returns true if successful */
	bool erase (const K& key)
	{
		bool retval = erase(root_, key);
		if(retval == true)
                {
                        size_--;
                }
                return retval;
	}

	/* lookup the value associated with a key. if the key is not in the
	map, insert it with default value. Should provide l-value access to
	value.*/
	V& operator[] (const K& key)
	{
		bool in = false; 
		LCMapNode* retNode = bracketSearch(root_, key, in);//search to see if key is in tree
		return retNode->value_;
	}

	/* returns true if this key maps to a value */
	bool in (const K& key)
	{
		return(*lookup(key) != NULL); //dont update heights
	}

	/* returns a list of keys in this map */
	std::list<K> keys()
	{
		std::list<K> keysList;
		keys(root_, keysList);
		return keysList;
	}

	/* returns true if the map is empty */
	bool empty() const
	{
		return root_ == NULL;
	}

	/* number of key value pairs stored */
	int size() const 
	{ 
		return size_; 
	}

	/* empties the map */
	void clear()
	{
		clear(root_);
		size_ = 0;
	}
	
	/* returns the height of the node that stores this key
	* this is for me to test your code an ordinary map would not expose
	 its implementation in this way.
	*/
	int height(const K& key)
	{
		LCMapNode** retNode = lookup(key); //dont update heights
		
		int retval = -1; 
		if((*retNode) != NULL)
		{	
			retval = (*retNode)->height_;
		}
		return retval;
	}
	
	/* returns a forward iterator that points to the first item.
	* must perform an in-order traversal
	*/
	Iterator begin()
	{
		return Iterator(root_);
	}
	
	/* returns a forward iterator that points to one item past the last */
	Iterator end()
	{
		return Iterator();
	}
	
private:
	/*lookup function used to return a point to a node pointer*/
	LCMapNode** lookup(const K& key)
        {
                return lookup(root_, key);
        }

        LCMapNode** lookup(LCMapNode*& n, const K& key)
        {
                LCMapNode** retval = &n;
                if(*retval != NULL && (isLessThan(key, n->key_) || (isLessThan(n->key_, key))))
                {
                        if(isLessThan(key, n->key_))//go left if key is less than n's key
                        {
                                retval = lookup(n->left_, key);
                        }
                        else
                        {
                                retval = lookup(n->right_, key);
                        }
                }
                return retval;
        }


	//helper function for keys
	void keys(LCMapNode*& n, std::list<K>& keysList)
        {
                if(n != NULL)
                {
                        keysList.push_back(n->key_);//go through whole BST and push each key onto keysList
                        keys(n->left_, keysList);
                        keys(n->right_, keysList);
                }        
	}

	//helper fucntion for clear
	void clear(LCMapNode*& n)
        {
                if(n != NULL)
                {
                        clear(n->left_);
                        clear(n->right_);
                        delete n;
                        n = NULL;
                }
        }

	bool insert(LCMapNode*& n, const K& key, V value)
	{
		bool inserted = false;
                if(n == NULL)//if node isnt there
                {
                        n = new LCMapNode(key, value);//create a new one
                        inserted = true;
                }
                else if(isLessThan(key, n->key_))//go left if key is less than n's key
                {
                        inserted = insert(n->left_, key, value);
                }
                else if(isLessThan(n->key_, key))
                {
                        inserted = insert(n->right_, key, value);
                }
		if(inserted)//if inserted, rebalance
		{
			reBalance(n);
		}
		return inserted;
	}

	LCMapNode* bracketSearch(LCMapNode*& n, const K& key, bool& in)//search function for brackets operator
        {
		LCMapNode* retval = n;
                if(n == NULL)//if node isnt there
                {
                        n = new LCMapNode(key, V());//create a new one
			retval = n;
			in = true;
			size_++;
                }
                else if(isLessThan(key, n->key_))//go left if key is less than n's key
                {
                        retval = bracketSearch(n->left_, key, in);
                }
                else if(isLessThan(n->key_, key))
                {
                        retval = bracketSearch(n->right_, key, in);
                }
                if(in)//if inserted, rebalance
                {
                        reBalance(n);	
                }
                return retval;
        }

	//helper function for erase
	bool erase(LCMapNode*& n, const K& key)
	{
		std::stack<LCMapNode**> path_;
		bool retval = true;
		if(n == NULL)//if node isnt there
		{
			retval = false;//return false
  		}
		else if(isLessThan(key, n->key_))//go left if key is less than n's key
		{
			path_.push(&n);
			retval = erase(n->left_, key);
		}
		else if(isLessThan(n->key_, key))
		{
			path_.push(&n);
			retval = erase(n->right_, key);
		}
		else if((n->left_ != NULL) && (n->right_ != NULL))//handles two children
		{
			LCMapNode** tmp = findMin(path_, &n->right_);
			n->key_ = (*tmp)->key_;
			n->value_ = (*tmp)->value_;
			/*removeNodeSimple(*tmp);
			tmp = NULL;	
			while(!path_.empty())
			{
				if(path_.top() != NULL)
				{
					reBalance((*path_.top()));
					path_.pop();
				}		
			}*/
			erase(n->right_, n->key_);
		}
		else//handles one or no children
		{
			removeNodeSimple(n);
		}
		if(retval && n != NULL)//check to see if rebalances are needed
		{
			reBalance(n);
		}
		
		return retval;
	}
	
	void removeNodeSimple(LCMapNode*& n)//removes node to be deleted and sets n equal to its  child
	{
		if(n->right_ != NULL)//if node has right child or no children
		{
			LCMapNode* tmp = n->right_;
			delete n;
			n = tmp;
		}
		else//if node has left child or is childless
		{
			LCMapNode* tmp = n->left_;
			delete n;
			n = tmp;
		}
	}
		
	LCMapNode** findMin(std::stack<LCMapNode**>& path_, LCMapNode** n)//finds smallest node in right subtree
	{
		while((*n)->left_ != NULL)//while there is still a smaller node
		{
			path_.push(n);//push current node onto path
			n = &(*n)->left_;//keep searching to the left
		}
		return n;
	}

	/* copies a tree starting at a certain root*/
        void copyLCMapNodes(LCMapNode* orig, LCMapNode*& newTree)
        {
                if(orig != NULL)//recursively copy nodes
                {
                        newTree = new LCMapNode(orig->key_, orig->value_, orig->height_);
                        copyLCMapNodes(orig->left_, newTree->left_);
                        copyLCMapNodes(orig->right_, newTree->right_);
                }
        }

	/*checks for balance issues within tree
	  balance issues are used using AVL methods*/
	void reBalance(LCMapNode*& n)
	{
		int bFactor = balanceFactor(n);
		if(bFactor == -2)//if right tree too heavy
		{
			bFactor = balanceFactor(n->right_);//check balance factor of right subtree
			if(bFactor > 0)
			{
				rotateWithLeftChild(n->right_);//rotate with left child if heavy on right
			}
			rotateWithRightChild(n);//always rotate with right child
		}
		else if(bFactor == 2)
		{
			bFactor = balanceFactor(n->left_);//check balance factor of left subtree
                        if(bFactor < 0)
                        {
                                rotateWithRightChild(n->left_);//rotate with right child if heavy on left
                        }
                        rotateWithLeftChild(n);//always rotate with left child
		}	
		else
		{
			updateHeights(n);
		}	
	}

	/*rotates an LCMapNode with it's left child*/
        void rotateWithLeftChild(LCMapNode*& k2)
        {
                LCMapNode* k1 = k2->left_;
                k2->left_ = k1->right_;
                k1->right_ = k2;
	        updateHeights(k2);//because rotations cause height 
                updateHeights(k1);//changes in both nodes being rotated
	        k2 = k1;
        }

        /*rotates an LCMapNode withs it's right child*/
        void rotateWithRightChild(LCMapNode*& k2)//send in reference to pointer to m
        {
                LCMapNode* k1 = k2->right_;	//create new node pointer that points to m's right child (b)
                k2->right_ = k1->left_;		
                k1->left_ = k2;			
                updateHeights(k2);
                updateHeights(k1);
                k2 = k1;
        }
	
	/*finds balance factor of node by subtracting height of right child from height of left*/
	int balanceFactor (LCMapNode*& n)
	{
   		return height(n->left_) - height(n->right_);
  	}
	
	/*updates heights of nodes depending on the heights of left and right children*/
	void updateHeights(LCMapNode*& n)
	{
		n->height_ = (std::max(height(n->left_), height(n->right_)) + 1);
	}
	
	/*overloaded height function takes in a pointer to a node*/
	int height(LCMapNode*& n)
        {
                int retval = -1;//default value of -1 in case theres no node
                if(n != NULL)//if there is a node
                {
                        retval = n->height_;
                }
                return retval;
        }
};

#endif
