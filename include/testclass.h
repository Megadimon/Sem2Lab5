#include <iostream>
#include <string>
#include <fstream>
using namespace std;

template <typename T>
struct Node {
	T key;
	Node<T>* leftNode;
	Node<T>* rightNode;

	Node(T key) {
		this->key = key;
		leftNode = nullptr;
		rightNode = nullptr;
	}
};

template <typename T>
class BinarySearchTree {
	Node<T>* root_;
	void	 addNode(Node<T>* &node, const T &key);
	Node<T>* findNode(const T& key) const;
	void	 deleteTree(Node<T>* node);
	void     inorderPrint(Node<T>* node, unsigned int level);

public:
	BinarySearchTree();
	~BinarySearchTree();

	T            key() const;
	unsigned int count(const Node<T>* node) const;
	Node<T>*     leftNode() const;
	Node<T>*     rightNode() const;
	Node<T>*     root() const;

    void         add(const T& value);
	void         rmv(const T& value);
	bool         isFound(const T& value) const;
	void         paintTree();
	
	void         fileIn(string filename);
	void         fileOut(Node<T>* node, ostream& fileOut, unsigned int level) const;
	void         Out(string filename) const;
};

template<typename T>
void BinarySearchTree<T>::addNode(Node<T>*& node, const T & key)
{
	if (node) {
		if (key < node->key)
			addNode(node->leftNode, key);
		else if (key > node->key)
			addNode(node->rightNode, key);
		else {
			return;
		}
	}
	else {
		node = new Node<T>(key);
	}
}

template<typename T>
Node<T>* BinarySearchTree<T>::findNode(const T & key) const
{
	Node<T>* currentNode = root_;

	while (currentNode) {
		if (currentNode->key == key) break;
		else {
			if (currentNode->key < key) currentNode = currentNode->rightNode;
			else currentNode = currentNode->leftNode;
		}
	}

	return currentNode;
}

template<typename T>
void BinarySearchTree<T>::deleteTree(Node<T>* node)
{
	if (!node) return;
	deleteTree(node->leftNode);
	deleteTree(node->rightNode);
}



template<typename T>
void BinarySearchTree<T>::inorderPrint(Node<T>* node, unsigned int level)
{
	if (!node) { return; }
	
	level++;
	inorderPrint(node->rightNode, level);

	for (unsigned int i = 0; i < level; ++i) {
		cout << ">";
	}
	cout << node->key << endl;

	inorderPrint(node->leftNode, level);
	level--;
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree()
{
	root_ = nullptr;
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
	deleteTree(root_);
}

template<typename T>
T BinarySearchTree<T>::key() const
{
	return root->key;
}

template<typename T>
unsigned int BinarySearchTree<T>::count(const Node<T>* node) const
{
	if (node) {
		return count(node->leftNode) + count(node->rightNode) + 1;
	}
	else return 0;
}

template<typename T>
Node<T>* BinarySearchTree<T>::leftNode() const
{
	return root_->leftNode;
}

template<typename T>
Node<T>* BinarySearchTree<T>::rightNode() const
{
	return root_->rightNode;
}

template<typename T>
Node<T>* BinarySearchTree<T>::root() const
{
	return root_;
}

template<typename T>
void BinarySearchTree<T>::add(const T & key)
{
	addNode(root_, key);
}

template<typename T>
void BinarySearchTree<T>::rmv(const T& key)
{
	bool found = false;
	Node<T>* currentNode;
	Node<T>* parentNode;
	currentNode = root_;
	parentNode = (Node<T>*)NULL;
	
	while (currentNode != NULL)
	{
		if (currentNode->key == key) {
			found = true;
			break;
		}
		else {
			parentNode = currentNode;
			if (key > currentNode->key) currentNode = currentNode->rightNode;
			else currentNode = currentNode->leftNode;
		}
	}
	
	if (!found) {
		cout << "Key to delete has not been found" << endl;
		return;
	}
	
	if ((currentNode->leftNode == NULL && currentNode->rightNode != NULL) || (currentNode->leftNode != NULL
		&& currentNode->rightNode == NULL)) {
		if (currentNode->leftNode == NULL && currentNode->rightNode != NULL) {
			if (parentNode->leftNode == currentNode) {
				parentNode->leftNode = currentNode->rightNode;
				delete currentNode;
			}
			else {
				parentNode->rightNode = currentNode->rightNode;
				delete currentNode;
			}
		}
		else {
			if (parentNode->leftNode == currentNode) {
				parentNode->leftNode = currentNode->leftNode;
				delete currentNode;
			}
			else {
				parentNode->rightNode = currentNode->leftNode;
				delete currentNode;
			}
		}
		return;
	}

	if (currentNode->leftNode == NULL && currentNode->rightNode == NULL)
	{
		if (parentNode == NULL)
		{
			delete currentNode;

		}
		else
			if (parentNode->leftNode == currentNode) parentNode->leftNode = NULL;
			else parentNode->rightNode = NULL;
			delete currentNode;
			return;
	}

	if (currentNode->leftNode != NULL && currentNode->rightNode != NULL)
	{
		Node<T>* chkr;
		chkr = currentNode->rightNode;
		if ((chkr->leftNode == NULL) && (chkr->rightNode == NULL))
		{
			currentNode = chkr;
			delete chkr;
			currentNode->rightNode = NULL;
		}
		else 
		{
		
			if ((currentNode->rightNode)->leftNode != NULL)
			{
				Node<T>* lcurr;
				Node<T>* lcurrp;
				lcurrp = currentNode->rightNode;
				lcurr = (currentNode->rightNode)->leftNode;
				while (lcurr->leftNode != NULL)
				{
					lcurrp = lcurr;
					lcurr = lcurr->leftNode;
				}
				currentNode->key = lcurr->key;
				delete lcurr;
				lcurrp->leftNode = NULL;
			}
			else
			{
				Node<T>* tmp;
				tmp = currentNode->rightNode;
				currentNode->key = tmp->key;
				currentNode->rightNode = tmp->rightNode;
				delete tmp;
			}

		}
		return;
	}
}

template<typename T>
bool BinarySearchTree<T>::isFound(const T & key) const
{
	Node<T>* retNode = findNode(key);
	if (retNode)
		return true;
	else
		return false;
}

template<typename T>
void BinarySearchTree<T>::paintTree()
{
	unsigned int level = 0;
	inorderPrint(root_, level);
}

template<typename T>
void BinarySearchTree<T>::fileIn(string filename)
{
	ifstream inFile;
	inFile.open(filename);
	if (!inFile) { cout << "error"; return; }
	T key;
	unsigned int count;
	inFile >> count;
	while (count--) {
		inFile >> key;
		add(key);
	}
	inFile.close();
}

template<typename T>
void BinarySearchTree<T>::fileOut(Node<T>* node, ostream &outstream, unsigned int level) const
{
	
	if (!node) { return; }

	level++;
	fileOut(node->rightNode, outstream, level);

	for (unsigned int i = 0; i < level; ++i) {
		outstream << ">";
	}
	outstream << node->key << endl;

	fileOut(node->leftNode, outstream, level);
	level--;
}

template<typename T>
void BinarySearchTree<T>::Out(string filename) const
{
	unsigned int lvl = 0;
	ofstream OutFile(filename);
	unsigned int cnt = count(root_);
	if (!OutFile) cout << "Error" << endl;
	else {
		OutFile << "Number of elemets: ";
		OutFile << cnt << endl;
	}
	fileOut(root_, OutFile, lvl);
	OutFile.close();
}