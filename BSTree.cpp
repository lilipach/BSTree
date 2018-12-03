#include "BSTree.h"
#include <iostream>

using namespace std;   

  //////////////////////////////////
 //  Node and Tree consturctors  //
//////////////////////////////////
//
// Supporting Function Implementations //////////////////////////////
//
/** 
 * BSTreeNode parametarised constructor.
 * 
 * @param char element for data, and a left and right BSTnode pointers pointer
 * @return none
 * 
 * @pre none
 * @post creates an expression tree node  
 * 
 */
template <typename DataType, class KeyType>
BSTree<DataType, KeyType> :: BSTreeNode :: BSTreeNode ( const DataType &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr )
{
	dataItem = nodeDataItem;
	left = leftPtr;
	right = rightPtr;
}

/** 
 *	default constructor for BSTree 
 *
 * @param none
 * @return none
 * 
 * @pre none
 * @post creates a default expression tree/ empty BSTree
 * 
 */
template <typename DataType, class KeyType>
BSTree<DataType, KeyType> :: BSTree ()
{
	root = NULL;
}

  ///////////////////////////
 //  End of constructors  //
///////////////////////////

/*********************************************************************/

  ///////////////////////////////////////////////////
 //  destructor, clear function, and clearHelper  //
///////////////////////////////////////////////////
/** 
 * BSTree destructor neccessary due to memory allocation
 *
 * @param none
 * @return none
 * 
 * @pre none
 * @post deletes an expression tree and takes care of  all memory allocations  
 */
template <typename DataType, class KeyType>
BSTree<DataType, KeyType> :: ~BSTree ()
{
	clear();
}

/** 
 * The clear function deletes all existing nodes in the Binary tree by using the clearHelper 
 * function. Also takes care of setting root to NULL. 
 *
 * @param none
 * @return none
 * 
 * @pre none
 * @post deletes all of an expression tree's nodes 
 */
template <typename DataType, class KeyType>
void BSTree<DataType, KeyType> :: clear ()
{
	clearHelper(root);
	root = NULL;
}

/** 
 * ClearHelper takes care of recursively deleting the nodes of a  tree
 * 
 * @param A BSTreeNode pointer signaling which nodes to delete
 * @return none
 * 
 * @pre none
 * @post helps to recursively delete a tree's nodes  
 */
template <typename DataType, class KeyType>
void BSTree<DataType, KeyType> :: clearHelper(BSTreeNode * subRoot)
{
	if(subRoot != NULL)
	{
		clearHelper(subRoot -> left);
		clearHelper(subRoot -> right);
		delete subRoot;
	}	
	subRoot = NULL;
}

  //////////////////////////////////
 //  End of deleting functions   //
//////////////////////////////////

/*********************************************************************/

  /////////////////////////////////////////////////////
 //  copy constructor, copyHelper, and operator =   //
/////////////////////////////////////////////////////
/** 
 * 
 * @param an expression tree
 * @return an expression tree
 * 
 * @pre none
 * @post copies the passed expression tree to calling tree stucture
 */
template <typename DataType, class KeyType>
BSTree<DataType, KeyType> :: BSTree ( const BSTree<DataType,KeyType>& other )
{
	copyHelper(root, other.root);
}


/** 
 * 
 * @param an expression tree
 * @return an expression tree
 * 
 * @pre none
 * @post copies the passed expression tree to calling tree stucture using the 
 * overloaded = operator
 */
template <typename DataType, class KeyType>
BSTree<DataType, KeyType>& BSTree<DataType, KeyType> :: operator= ( const BSTree<DataType,KeyType>& other )
{
	if(this == &other)
		return *this;

	clear();
	
	copytHelper(root, other.root);
}

/** 
 * 
 * @param the root of a tree to be copied and the root of a tree that is to be 
 * over writen
 * 
 * @return none
 * 
 * @pre none
 * @post copies over the other root to subroot/ creates copy
 */
template <typename DataType, class KeyType>
void BSTree<DataType, KeyType> ::  copyHelper(BSTreeNode * &subRoot, BSTreeNode * otherRoot)
{
	if( otherRoot != NULL)
	{
		BSTreeNode *l = NULL;
		BSTreeNode *r = NULL;
	
		copyHelper(l, otherRoot -> left);
		copyHelper(r, otherRoot -> right);

		subRoot = new BSTreeNode(otherRoot -> dataItem, l, r);
	}
}

  //////////////////////////////////
 //  End of copy set functions   //
//////////////////////////////////

/*********************************************************************/

/** 
 * 
 * @param none
 * 
 * @return bool that signifies if the tree is empty or not
 * 
 * @pre none
 * @post none
 */
template <typename DataType, class KeyType>
bool BSTree<DataType, KeyType> :: isEmpty () const
{
	if(root == NULL)
		return true;
	else
		return false;
}

/*********************************************************************/
/** 
 * 
 * @param an index key to find the node that is to be deleted
 * 
 * @return bool that signifies if the node to be removed has been removed successfully
 *         if false then the specific key node does not exist
 * 
 * @pre none
 * @post deletes the specified node by the key from the tree 
 */
template <typename DataType, class KeyType>
bool BSTree<DataType, KeyType> :: remove ( const KeyType& deleteKey )
{
	return removeHelper(root, deleteKey);
}

/** 
 * 
 * @param BSTreeNode pointer signifying which tree to search, key signifying which node is being 
 * looked for
 * 
 * @return bool that signifies if the Node signaled by the passed key has been found and deleted or
 * not 
 * 
 * @pre none
 * @post removes a specified node
 */
template <typename DataType, class KeyType>
bool BSTree<DataType, KeyType> :: removeHelper(BSTreeNode * &subRoot, const KeyType& removeKey)
{

	if(subRoot == NULL)
	{
		return false;
	}


	if(subRoot -> dataItem.getKey() < removeKey)
	{
		return( removeHelper(subRoot -> right, removeKey) );		
	}	
	else if(subRoot -> dataItem.getKey() > removeKey)
	{
		return( removeHelper(subRoot -> left, removeKey) );
	}


		if( (subRoot -> left == NULL) && (subRoot -> right == NULL) )
		{
			delete subRoot;
			subRoot = NULL;
			return true;
		}
		else if( (subRoot -> left == NULL) && (subRoot -> right != NULL) )
		{
			BSTreeNode * temp = subRoot;
			subRoot = subRoot -> right;
			delete temp;
			return true;
		}
		else if( (subRoot -> right == NULL) && (subRoot -> left != NULL) )
		{
			BSTreeNode * temp = subRoot;
			subRoot = subRoot -> left;
			delete temp;
			return true;
		}	
		else if( (subRoot -> left != NULL) && (subRoot -> right != NULL) )
		{
			BSTreeNode * temp = subRoot -> left;
				

			while(temp -> right != NULL)
			{
				temp = temp -> right;
			}

			subRoot -> dataItem = temp -> dataItem;
	
			removeHelper( subRoot -> left, temp -> dataItem.getKey());
			return true;	
		}
}

/** 
 * 
 * @param a dataItem to be inserted into the binary tree
 * 
 * @return none
 * 
 * @pre none
 * @post inserts a node into the BSTree with the given data
 */
template <typename DataType, class KeyType>
void BSTree<DataType, KeyType> :: insert ( const DataType& newDataItem )
{
	insertHelper(newDataItem, root);
}

/** 
 * 
 * @para dataType to be inserted to the tree and pointer to BSTree to which the item should be 
 * inserted to
 * 
 * @return none
 * 
 * @pre none
 * @post inserts a node into tree in the proper location
 */
template <typename DataType, class KeyType>
void BSTree<DataType, KeyType> :: insertHelper(const DataType& newData, BSTreeNode * &subRoot)
{
	if(subRoot == NULL)
	{	
		subRoot = new BSTreeNode(newData, NULL, NULL);
	}
	else
	{
		if(newData.getKey() < subRoot -> dataItem.getKey())
			insertHelper(newData, subRoot -> left);
		else if (newData.getKey() > subRoot -> dataItem.getKey())
			insertHelper(newData, subRoot -> right);
		else
			subRoot -> dataItem = newData;	
	}	
}

/** 
 * 
 * @param key to item that is being looked for/retrieved and a dataType item on to which the  
 * retrieved items data will be copied over too
 * 
 * @return bool that signifing if the specified item has been found and retrieved
 * 
 * @pre none
 * @post copies searched items data onto passed dataType object
 */
template <typename DataType, class KeyType>
bool BSTree<DataType, KeyType> :: retrieve ( const KeyType& searchKey, DataType& searchDataItem ) const
{
	if(root == NULL)
	{
		return false;
	}

	return retrieveHelper(searchKey, searchDataItem, root);		
}

/** 
 * 
 * @param keyType for searched item, BStreeNode for tree that is to be searched, and a DataType item 
 *        onto which data is copied
 * 
 * @return bool that signifing if the specified item has been found and retrieved
 * 
 * @pre none
 * @post copies searched items data onto passed dataType object
 */
template <typename DataType, class KeyType>
bool BSTree<DataType, KeyType> ::retrieveHelper(const KeyType& searchKey, DataType& searchDataItem, BSTreeNode * subRoot) const
{
	if(subRoot != NULL)
	{
		if(searchKey < subRoot -> dataItem.getKey())
		{
			return ( retrieveHelper(searchKey, searchDataItem, subRoot -> left) );
		}
		else if(searchKey > subRoot -> dataItem.getKey())
		{
			return ( retrieveHelper(searchKey, searchDataItem, subRoot -> right) );
		}
		else if(searchKey == subRoot -> dataItem.getKey())
		{
			searchDataItem = subRoot -> dataItem;
			return true;
		}
	}
return false;
}

/** 
 * 
 * @param none
 * 
 * @return none
 * 
 * @pre none
 * @post print out all BSTree keys in asceding order
 */
template <typename DataType, class KeyType>
void BSTree<DataType, KeyType> :: writeKeys () const
{
	writeKeysHelper(root);
}

/** 
 * 
 * @param none
 * 
 * @return none
 * 
 * @pre none
 * @post print out all BSTree keys in asceding order
 */
template <typename DataType, class KeyType>
void BSTree<DataType, KeyType> :: writeKeysHelper (BSTreeNode * subRoot) const
{
	if(subRoot != NULL)
	{
		writeKeysHelper(subRoot -> left);
		cout<<subRoot -> dataItem.getKey()<<" ";
		writeKeysHelper(subRoot -> right);
	}
}

/*********************************************************************/
/** 
 * 
 * @param none
 * 
 * @return int value that is the height of the BSTree 
 * 
 * @pre none
 * @post none
 */
template <typename DataType, class KeyType>
int BSTree<DataType, KeyType> ::getHeight () const
{
	getHHelper(0, root);
}

/** 
 * 
 * @param int value count to hold the number of nodes so far in one tree branch and a pointer to the 
 * BSTree
 * 
 * @return int value that is the height of the BSTree
 * 
 * @pre none
 * @post none
 */
template <typename DataType, class KeyType>
int BSTree<DataType, KeyType> ::getHHelper (int count, BSTreeNode * subRoot) const
{
	if(subRoot != NULL)
	{
		int l, r;

		l = getHHelper(count + 1, subRoot -> left);
		r = getHHelper(count + 1, subRoot -> right);

		if(l>r)
			return l;
		else 
			return r;
	}

return count;
}

/** 
 * 
 * @param none
 * 
 * @return int value for the number of nodes in the BSTree
 * 
 * @pre none
 * @post none
 */
template <typename DataType, class KeyType>
int BSTree<DataType, KeyType> :: getCount () const
{
	getCHelper(root);
}

/** 
 * 
 * @param a pointer to the BSTree
 * 
 * @return int value for the total numebr of nodes int the BSTree
 * 
 * @pre none
 * @post none
 */
template <typename DataType, class KeyType>
int BSTree<DataType, KeyType> :: getCHelper (BSTreeNode * subRoot) const
{
	if(subRoot != NULL)
	{
		int total = 1;
		total = total + getCHelper(subRoot -> left);
		total = total + getCHelper(subRoot -> right);

		return total;
	}
return 0; 
}


//--------------------------------------------------------------------
//
//  Laboratory 9                                         show9.cpp
//
//  Linked implementation of the showStructure operation for the
//  Binary Search Tree ADT
//
//--------------------------------------------------------------------

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: showStructure () const

// Outputs the keys in a binary search tree. The tree is output
// rotated counterclockwise 90 degrees from its conventional
// orientation using a "reverse" inorder traversal. This operation is
// intended for testing and debugging purposes only.

{
    if ( root == 0 )
       cout << "Empty tree" << endl;
    else
    {
       cout << endl;
       showHelper(root,1);
       cout << endl;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: showHelper ( BSTreeNode *p,
                               int level             ) const

// Recursive helper for showStructure. 
// Outputs the subtree whose root node is pointed to by p. 
// Parameter level is the level of this node within the tree.

{
     int j;   // Loop counter

     if ( p != 0 )
     {
        showHelper(p->right,level+1);         // Output right subtree
        for ( j = 0 ; j < level ; j++ )    // Tab over to level
            cout << "\t";
        cout << " " << p->dataItem.getKey();   // Output key
        if ( ( p->left != 0 ) &&           // Output "connector"
             ( p->right != 0 ) )
           cout << "<";
        else if ( p->right != 0 )
           cout << "/";
        else if ( p->left != 0 )
           cout << "\\";
        cout << endl;
        showHelper(p->left,level+1);          // Output left subtree
    }
}



