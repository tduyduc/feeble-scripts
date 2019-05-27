#include <iostream>
using namespace std;

template <typename E> class List {
public:
	virtual void 	clear() = 0;
	virtual bool 	isEmpty() = 0;
	virtual void 	insert(E item) = 0;
	virtual void 	append(E item) = 0;
	virtual E 		remove() = 0;
	virtual E 		getValue() = 0;
	virtual void	setValue(E item) = 0;
	virtual void 	moveToStart() = 0;
	virtual void 	moveToEnd() = 0;
	virtual void	prev() = 0;
	virtual void 	next() = 0;
	virtual int 	length() = 0;
	virtual int 	currPos() = 0;
	virtual void 	moveToPos(int pos) = 0;
	virtual bool	endOfList() = 0;
};

template <typename E> class Stack {
public:
	virtual void 	clear() = 0;
	virtual void 	push(E item) = 0;
	virtual E 		pop() = 0;
	virtual E  		topValue() = 0;
	virtual int 	length() = 0;
	virtual bool 	isEmpty() = 0;
};

template <typename E> class Queue {
public:
	virtual void 	clear() = 0;
	virtual void 	enqueue(E item) = 0;
	virtual E 		dequeue() = 0;
	virtual E 		frontValue() = 0;
	virtual int 	length() = 0;
	virtual bool 	isEmpty() = 0;
};

template <typename E> class Node {
private: E element; Node<E> *next;
public:
	Node(E item, Node<E> *nextval) {
		element = item; next = nextval;
	}
	Node(Node<E> *nextval) { next = nextval; }
	Node<E> *nextNode() const { return next; }
	Node<E> *setNext(Node<E> *nextval) {
		return next = nextval;
	}
	E getElement() const { return element; }
	E setElement(E item) { return element = item; }
};

template <typename E> class AList: public List<E> {
private:
	int maxSize, listSize, curr; E *listArray;
public:
	AList(int size) {
		maxSize = size;
		listSize = curr = 0;
		listArray = new E[size];
	}
	void clear() { listSize = curr = 0; }
	void moveToStart() { curr = 0; }
	void moveToEnd() { curr = listSize; }
	void prev() { if (curr > 0) curr--; }
	void next() { if (curr < listSize) curr++; }
	int length() { return listSize; }
	int currPos() { return curr; }
	bool isEmpty() { return listSize == 0; }
	bool endOfList() { return curr >= listSize; }
	void moveToPos(int pos) {
		if (pos < 0 || pos > listSize) return;
		curr = pos;
	}
	E getValue() {
		if (curr < 0 || curr > listSize) return;
		return listArray[curr];
	}
	void setValue(E item) { listArray[curr] = item; }
	void insert(E item) {
		if (listSize >= maxSize) return;
		int i = listSize;
		for (; i > curr; i--)
			listArray[i] = listArray[i - 1];
		listArray[curr] = item;
		listSize++;
	}
	void append(E item) {
		if (listSize >= maxSize) return;
		listArray[listSize++] = item;
	}
	E remove() {
		if (curr < 0 || curr > listSize) return;
		E item = listArray[curr];
		int i = curr;
		for (; i < listSize - 1; i++)
			listArray[i] = listArray[i + 1];
		listSize--;
		return item;
	}
};

template <typename E> class LList: public List<E> {
private: Node<E> *head, *tail; int len;
protected: Node<E> *curr;
public:
	LList() {
		curr = tail = head = new Node<E>(NULL);
		len = 0;
	}
	void moveToStart() { curr = head; }
	void moveToEnd() { curr = tail; }
	int length() { return len; }
	bool isEmpty() { return len == 0; }
	void clear() {
		moveToStart();
		while (curr->nextNode() != NULL) remove();
		delete curr;
		curr = tail = head = new Node<E>(NULL);
		len = 0;
	}
	void prev() {
		if (curr == head) return;
		Node<E> *temp = head;
		while (temp->nextNode() != curr)
			temp = temp->nextNode();
		curr = temp;
	}
	void next() {
		if (curr != tail) curr = curr->nextNode();
	}
	void insert(E item) {
		curr->setNext(new Node<E>(item, curr->nextNode()));
		if (curr == tail) tail = curr->nextNode();
		len++;
	}
	void append(E item) {
		tail = tail->setNext(new Node<E>(item, NULL));
		len++;
	}
	E getValue() {
		if (curr->nextNode() == NULL) return;
		return curr->nextNode()->getElement();
	}
	void setValue(E item) { curr->setElement(item); }
	E remove() {
		Node<E> *temp = curr->nextNode();
		if (curr->nextNode() == NULL) return;
		E item = curr->nextNode()->getElement();
		if (tail == curr->nextNode()) tail = curr;
		curr->setNext(curr->nextNode()->nextNode());
		len--;
		delete temp;
		return item;
	}
	int currPos() {
		Node<E> *temp = head;
		int i = 0;
		for (; curr != temp; i++)
			temp = temp->nextNode();
		return i;
	}
	void moveToPos(int pos) {
		if ((pos < 0) || (pos > len)) return;
		curr = head;
		int i = 0;
		for (; i < pos; i++)
			curr = curr->nextNode();
	}
	bool endOfList() {
		return curr->nextNode() == NULL;
	}
};

template <typename E> class DNode {
private: E element; DNode<E> *next, *prev;
public:
	DNode(E item, DNode<E> *p, DNode<E> *n) {
		element = item; prev = p; next = n;
	}
	DNode(DNode<E> *p, DNode<E> *n) {
		prev = p; next = n;
	}
	DNode<E> *nextNode() const { return next; }
	DNode<E> *setNext(DNode<E> *n) { return next = n; }
	DNode<E> *prevNode() const { return prev; }
	DNode<E> *setPrev(DNode<E> *p) { return prev = p; }
	E getElement() const { return element; }
	E setElement(E item) { return element = item; }
};

template <typename E> class DList: public List<E> {
private: DNode<E> *head, *tail; int len;
protected: DNode<E> *curr;
public:
	DList() {
		curr = tail = head = new DNode<E>(NULL, NULL);
	}
	void moveToStart() { curr = head; }
	void moveToEnd() { curr = tail; }
	int length() { return len; }
	bool isEmpty() { return len == 0; }
	void clear() {
		moveToStart();
		while (curr->nextNode() == NULL) remove();
		delete curr;
		curr = tail = head = new DNode<E>(NULL, NULL);
		len = 0;
	}
	void prev() {
		if (curr != head) curr = curr->prevNode();
	}
	void next() {
		if (curr != tail) curr = curr->nextNode();
	}
	void insert(E item) {
		curr->setNext(new DNode<E>(item, curr, curr->nextNode()));
		curr->nextNode()->nextNode()->setPrev(curr->nextNode());
		len++;
	}
	void append(E item) {
		tail->setPrev(new DNode<E>(item, tail->prevNode(), tail));
		tail->prevNode()->prevNode()->setNext(tail->prevNode());
		len++;
	}
	E getValue() {
		if (curr->nextNode() == tail) return;
		return curr->nextNode()->getElement();
	}
	void setValue(E item) { curr->setElement(item); }
	E remove() {
		DNode<E> *temp = curr->nextNode();
		if (curr->nextNode() == tail) return;
		E item = curr->nextNode()->getElement();
		curr->nextNode()->nextNode()->setPrev(curr);
		curr->setNext(curr->nextNode()->nextNode());
		len--;
		delete temp;
		return item;
	}
	int currPos() {
		DNode<E> *temp = head;
		int i = 0;
		for (; curr != temp; i++)
			temp = temp->nextNode();
		return i;
	}
	void moveToPos(int pos) {
		if ((pos < 0) || (pos > len)) return;
		curr = head;
		int i = 0;
		for (; i < pos; i++)
			curr = curr->nextNode();
	}
	bool endOfList() {
		return curr->nextNode() == NULL;
	}
};

template <typename E> class AStack: public Stack<E> {
private: E *stackArray; int len, maxSize;
public:
	AStack(int size) {
		stackArray = new E[size];
		maxSize = size;
		len = 0;
	}
	void clear() { len = 0; }
	void push(E item) {
		if (len >= maxSize) return;
		stackArray[len++] = item;
	}
	E pop() {
		if (len == 0) return;
		return stackArray[--len];
	}
	E topValue() {
		if (len == 0) return;
		return stackArray[len - 1];
	}
	int length() { return len; }
	bool isEmpty() { return len == 0; }
};

template <typename E> class LStack: public Stack<E> {
private: Node<E> *top; int len;
public:
	LStack() { top = NULL; len = 0; }
	void clear() {
		while (top != NULL) pop();
	}
	void push(E item) {
		top = new Node<E>(item, top);
		len++;
	}
	E pop() {
		if (top == NULL) return;
		E item = top->getElement();
		Node<E> *temp = top;
		top = top->nextNode();
		delete temp;
		len--;
		return item;
	}
	E topValue() {
		if (top == NULL) return;
		return top->getElement();
	}
	int length() { return len; }
	bool isEmpty() { return len == 0; }
};

template <typename E> class AQueue: public Queue<E> {
private: E *queueArray; int maxSize, front, rear;
public:
	AQueue(int size) {
		maxSize = size + 1;
		rear = 0; front = 1;
		queueArray = new E[maxSize];
	}
	void clear() { rear = 0; front = 1; }
	int length() {
		return ((rear + maxSize) - front + 1) % maxSize;
	}
	void enqueue(E item) {
		if ((rear + 2) % maxSize == front) return;
		rear = (rear + 1) % maxSize;
		queueArray[rear] = item;
	}
	E dequeue() {
		if (length() == 0) return;
		E item = queueArray[front];
		front = (front + 1) % maxSize;
		return item;
	}
	E frontValue() { return queueArray[front]; }
	bool isEmpty() {
		return (rear + 1) % maxSize == front;
	}
};

template <typename E> class LQueue: public Queue<E> {
private: Node<E> *front, *rear; int len;
public:
	LQueue() {
		rear = front = new Node<E>(NULL);
		len = 0;
	}
	void clear() {
		while (front->nextNode() != NULL) dequeue();
		delete front;
		rear = front = new Node<E>(NULL);
		len = 0;
	}
	void enqueue(E item) {
		rear = rear->setNext(new Node<E>(item, NULL));
		len++;
	}
	E dequeue() {
		if (front->nextNode() == NULL) return;
		Node<E> *temp = front->nextNode();
		E item = temp->getElement();
		front->setNext(temp->nextNode());
		delete temp;
		len--;
		return item;
	}
	E frontValue() {
		if (front->nextNode() == NULL) return;
		return front->nextNode()->getElement();
	}
	int length() { return len; }
	bool isEmpty() { return len == 0; }
};

template <typename E> class BinNode {
private: E element; BinNode<E> *left, *right;
public:
	BinNode() { left = right = NULL; }
	BinNode(E item) { element = item; left = right = NULL; }
	BinNode(E item, BinNode<E> *lchild, BinNode<E> *rchild) {
		element = item; left = lchild; right = rchild;
	}
	BinNode(BinNode<E> *lchild, BinNode<E> *rchild) {
		left = lchild; right = rchild;
	}
	E getElement() { return element; }
	void setElement(E item) { element = item; }
	BinNode<E> *leftChild() { return left; }
	BinNode<E> *setLeft(BinNode *child) { return left = child; }
	BinNode<E> *rightChild() { return right; }
	BinNode<E> *setRight(BinNode *child) { return right = child; }
	bool isLeaf() {
		return (left == NULL) && (right == NULL);
	}
};

class Traversal {
public:
	template <typename E> static void preorder(BinNode<E> *root) {
		if (root == NULL) return;
		visit(root);
		preorder(root->leftChild());
		preorder(root->rightChild());
	}
	template <typename E> static void inorder(BinNode<E> *root) {
		if (root == NULL) return;
		inorder(root->leftChild());
		visit(root);
		inorder(root->rightChild());
	}
	template <typename E> static void postorder(BinNode<E> *root) {
		if (root == NULL) return;
		postorder(root->leftChild());
		postorder(root->rightChild());
		visit(root);
	}
	template <typename E> static void visit(BinNode<E> *root) {
		cout << root->getElement() << "\t";
	}
};

template <typename E> class BST {
private: BinNode<E> *root; int nodeCount;
public:
	BST() { root = NULL; nodeCount = 0; }
	void clear() { deleteNode(root); nodeCount = 0; }
	void insert(E item) {
		root = insertHelp(root, item);
		nodeCount++;
	}
	void remove(E item) {
		if (findHelp(root, item)) {
			root = removeHelp(root, item);
			nodeCount--;
		}
	}
	E removeAny() {
		if (root != NULL) {
			E temp = root->getElement();
			root = removeHelp(root, temp);
			nodeCount--;
			return temp;
		} else return;
	}
	bool find(E item) const { return findHelp(root, item); }
	int size() const { return nodeCount; }
	BinNode<E> *getRoot() { return root; }
private:
	void deleteNode(BinNode<E> *&node) {
		if (node == NULL) return;
		deleteNode(node->leftChild());
		deleteNode(node->rightChild());
		delete node;
		nodeCount--;
	}
	bool findHelp(BinNode<E> *node, E item) const {
		if (node == NULL) return false;
		if (node->getElement() > item)
			return findHelp(node->leftChild(), item);
		else if (node->getElement() < item)
			return findHelp(node->rightChild(), item);
		else return true;
	}
	bool findHelp2(BinNode<E> *node, E item) const {
		BinNode<E> *root = node;
		if (root == NULL) return false;
		while (root->getElement() != item) {
			if (root->getElement() > item)
				root = root->leftChild();
			else root = root->rightChild();
			if (root == NULL) return false;
		}
		return true;
	}
	BinNode<E> *insertHelp(BinNode<E> *&node, E item) {
		if (node == NULL) return new BinNode<E>(item);
		if (node->getElement() > item)
			node->setLeft(insertHelp(node->leftChild(), item));
		else
			node->setRight(insertHelp(node->rightChild(), item));
		return node;
	}
	BinNode<E> *removeHelp(BinNode<E> *node, E item) {
		if (node == NULL) return NULL;
		if (node->getElement() > item)
			removeHelp(node->leftChild(), item);
		else if (node->getElement() < item)
			removeHelp(node->rightChild(), item);
		else if (node->leftChild() == NULL)
			return node->rightChild();
		else if (node->rightChild() == NULL)
			return node->leftChild();
		else {
			BinNode<E> *temp = getMin(node->rightChild());
			node->setElement(temp->getElement());
			deleteMin(node->rightChild());
		}
	}
	BinNode<E> *getMin(BinNode<E> *node) {
		return (node->leftChild() == NULL) ? node
				: getMin(node->leftChild());
	}
	BinNode<E> *deleteMin(BinNode<E> *node) {
		if (node->leftChild() == NULL)
			return node->rightChild();
		else {
			node->setLeft(deleteMin(node->leftChild()));
			return node;
		}
	}
};

class Polynomial {
public:
	static LList<float> add(LList<float> a, LList<float> b) {
		LList<float> result;
		for (a.moveToStart(), b.moveToStart();
				!a.endOfList() && !b.endOfList();
				a.next(), b.next())
			result.append(a.getValue() + b.getValue());
		for (; !a.endOfList(); a.next())
			result.append(a.getValue());
		for (; !b.endOfList(); b.next())
			result.append(b.getValue());
		return result;
	}
	
	static LList<float> multiply(LList<float> a, LList<float> b) {
		LList<float> result;
		int len = a.length() + b.length() - 1, i, j;
		for (i = 0; i < len; i++) result.append(0.);
		for (a.moveToStart(), i = 0; !a.endOfList(); a.next(), i++) {
			for (b.moveToStart(), j = 0; !b.endOfList(); b.next(), j++) {
				result.moveToPos(i + j);
				result.setValue(a.getValue() * b.getValue()
						+ result.getValue());
			}
		}
		return result;
	}
	
	static void printPolynomial(float coeff, float expo) {
		if (coeff == 0) return;
		if (coeff < 0) cout << "- " << -coeff;
		else cout << "+ " << coeff;
		if (expo != 0) {
			cout << "x";
			if (expo != 1) cout << "^" << expo;
		}
		cout << " ";
	}
};

void printLots(LList<int> l, LList<int> p) {
	for (p.moveToStart(); !p.endOfList(); p.next()) {
		l.moveToPos(p.getValue());
		cout << l.getValue() << "\t";
	}
	cout << endl;
}

template <typename E> LList<E> listIntersection(
		LList<E> a, LList<E> b) {
	LList<E> result;
	a.moveToStart(); b.moveToStart();
	while (!a.endOfList() && !b.endOfList()) {
		if (a.getValue() == b.getValue()) {
			result.append(a.getValue());
			a.next(); b.next();
		} else if (a.getValue() < b.getValue())
			a.next();
		else b.next();
	}
	return result;
}

template <typename E> LList<E> listUnion(LList<E> a, LList<E> b) {
	LList<E> result;
	a.moveToStart(); b.moveToStart();
	while (!a.endOfList() && !b.endOfList()) {
		if (a.getValue() == b.getValue()) {
			result.append(a.getValue());
			a.next(); b.next();
		} else if (a.getValue() < b.getValue()) {
			result.append(a.getValue());
			a.next();
		} else {
			result.append(b.getValue());
			b.next();
		}
	}
	while (!a.endOfList()) {
		result.append(a.getValue());
		a.next();
	}
	while (!b.endOfList()) {
		result.append(b.getValue());
		b.next();
	}
	return result;
}

template <typename E> void reverse1(LList<E> &a) {
	LList<E> temp;
	for (a.moveToStart(); !a.endOfList(); a.next())
		temp.insert(a.getValue());
	a.clear();
	for (temp.moveToStart(); !temp.endOfList(); temp.next())
		a.append(temp.getValue());
}

template <typename E> void reverse2(LList<E> &a) {
	LList<E> temp;
	a.moveToStart();
	while (!a.isEmpty()) temp.insert(a.remove());
	while (!temp.isEmpty()) a.append(temp.remove());
}

template <typename E> void removeStackValue(AStack<E> &s, E k) {
	AStack<E> temp; E i;
	while (!s.isEmpty()) {
		i = s.pop();
		if (i != k) temp.push(i);
	}
	while (!temp.isEmpty()) s.push(temp.pop());
}

bool balancingSymbols(char s[]) {
	LStack<char> temp; int i = 0;
	for (; s[i]; i++)
		switch (s[i]) {
			case '(': case '[': case '{':
				temp.push(s[i]);
				break;
			case ')':
				if (temp.topValue() == '(') temp.pop();
				else return false;
				break;
			case ']':
				if (temp.topValue() == '[') temp.pop();
				else return false;
				break;
			case '}':
				if (temp.topValue() == '{') temp.pop();
				else return false;
				break;
		}
	return temp.isEmpty();
}

bool palindromeCheck(char s[]) {
	LStack<char> temp; int i = 0;
	for (; s[i] != '$'; i++) {
		temp.push(s[i]);
		if (!s[i]) return false;
	}
	for (i++; s[i]; i++) {
		if (temp.isEmpty()) return false;
		if (temp.topValue() == s[i]) temp.pop();
		else return false;
	}
	return temp.isEmpty();
}

template <typename E> class StackWithMin: public LStack<E> {
private: E minValue;
public:
	E findMin() {
		if (LStack<E>::isEmpty()) return;
		return minValue;
	}
	void push(E item) {
		if (LStack<E>::isEmpty()) minValue = item;
		LStack<E>::push(item);
		if ((LStack<E>::topValue() == item) && (item < minValue))
			minValue = item;
	}
};

template <typename E> class DoubleStack {
private: E *stackArray; int len[2], maxSize;
public:
	DoubleStack(int size) {
		stackArray = new E[size * 2];
		maxSize = size * 2;
		len[0] = len[1] = 0;
	}
	void clear(bool id) { len[id] = 0; }
	void push(bool id, E item) {
		if (isFull()) return;
		if (id) {
			stackArray[maxSize - len[1] - 1] = item;
			len[1]++;
		} else stackArray[len[0]++] = item;
	}
	E pop(bool id, E item) {
		if (len[id] == 0) return;
		if (id)
			return stackArray[maxSize - (--len[1]) - 1];
		else return stackArray[--len[0]];
	}
	E topValue(bool id) {
		if (len[id] == 0) return;
		if (id)
			return stackArray[maxSize - len[1] - 1];
		else return stackArray[len[0] - 1];
	}
	int length(bool id) { return len[id]; }
	bool isEmpty(bool id) { return len[id] == 0; }
private:
	bool isFull() const {
		return len[0] + len[1] >= maxSize;
	}
};

template <typename E> class TripleStack {
private: E *stackArray; int len[3], maxSize;
public:
	TripleStack(int size) {
		stackArray = new E[size * 3];
		maxSize = size * 3;
		len[0] = len[1] = len[2] = 0;
	}
	void clear(int id) {
		if (!boundCheck()) return;
		len[id] = 0;
	}
	void push(int id, E item) {
		if (!boundCheck()) return;
		if (len[id] >= maxSize / 3) return;
		stackArray[3 * (len[id]++) + id] = item;
	}
	E pop(int id, E item) {
		if (!boundCheck()) return;
		if (len[id] == 0) return;
		return stackArray[3 * (--len[id]) + id];
	}
	E topValue(int id) {
		if (!boundCheck()) return;
		if (len[id] == 0) return;
		return stackArray[3 * (len[id] - 1) + id];
	}
	int length(int id) {
		if (!boundCheck) return;
		return len[id];
	}
	bool isEmpty(int id) {
		if (!boundCheck) return true;
		return len[id] == 0;
	}
private:
	bool boundCheck(int id) const {
		return id >= 0 && id <= 2;
	}
};

template <typename E> class SQueue: public Queue<E> {
	/*
	enQueue(q,  x)
	  1) Push x to stack1 (assuming size of stacks is unlimited).

	deQueue(q)
	  1) If both stacks are empty then error.
	  2) If stack2 is empty
	       While stack1 is not empty, push everything
	       from stack1 to stack2.
	  3) Pop the element from stack2 and return it.
	*/
private: LStack<E> s1, s2;
public:
	void clear() { s1.clear(); s2.clear(); }
	void enqueue(E item) { s1.push(item); } // O(1)
	E dequeue() { // O(n)
		if (s2.isEmpty()) {
			if (s1.isEmpty()) return;
			while (!s1.isEmpty())
				s2.push(s1.pop());
		}
		return s2.pop();
	}
	E frontValue() {
		if (s2.isEmpty()) {
			if (s1.isEmpty()) return;
			while (!s1.isEmpty())
				s2.push(s1.pop());
		}
		return s2.topValue();
	}
	int length() {
		return s1.length() + s2.length();
	}
	bool isEmpty() {
		return s1.isEmpty() && s2.isEmpty();
	}
};

template <typename E> class Deque {
private: DList<E> dequeList;
public:
	void clear() { dequeList.clear(); }
	void push(E item) {
		dequeList.moveToStart();
		dequeList.insert(item);
	}
	E pop() {
		dequeList.moveToStart();
		return dequeList.remove();
	}
	E frontValue() {
		dequeList.moveToStart();
		return dequeList.getValue();
	}
	void inject(E item) {
		dequeList.append(item);
	}
	E eject() {
		dequeList.moveToEnd();
		dequeList.prev();
		return dequeList.remove();
	}
	E rearValue() {
		dequeList.moveToEnd();
		dequeList.prev();
		return dequeList.getValue();
	}
	int length() const { return dequeList.length(); }
	bool isEmpty() const { return dequeList.isEmpty(); }
};

namespace Demo {
	void demoListStackQueue() {
		List<int> *l; Stack<int> *s; Queue<int> *q;
		l = new LList<int>;
		s = new LStack<int>;
		q = new LQueue<int>;
		int i = 2;
		for (; i <= 14; i += 2) {
			l->append(i);
			s->push(i);
			q->enqueue(i);
		}
		cout << endl << "List: \t";
		for (l->moveToStart(); !l->endOfList(); l->next())
			cout << l->getValue() << "\t";
		cout << endl << "Stack:\t";
		while (!s->isEmpty()) cout << s->pop() << "\t";
		cout << endl << "Queue:\t";
		while (!q->isEmpty()) cout << q->dequeue() << "\t";
		cout << endl;
	}
	
	void demoListIntersectionUnion() {
		LList<int> a, b, c;
		a.append(0); b.append(1);
		a.append(2); b.append(2);
		a.append(4); b.append(3);
		c = listIntersection(a, b);
		for (c.moveToStart(); !c.endOfList(); c.next())
			cout << c.getValue() << "\t";
		cout << endl;
		c = listUnion(a, b);
		for (c.moveToStart(); !c.endOfList(); c.next())
			cout << c.getValue() << "\t";
		cout << endl;
	}
	
	void demoPolynomials() {
		LList<float> a, b, c; int i;
		a.append(-1); b.append(9);
		a.append(12); b.append(2);
		a.append(-7); b.append(5);
		c = Polynomial::add(a, b);
		for (i = c.length() - 1, c.moveToPos(i);
				i >= 0; c.prev(), i--) {
			Polynomial::printPolynomial(c.getValue(), i);
		}
		cout << endl;
		c = Polynomial::multiply(a, b);
		for (i = c.length() - 1, c.moveToPos(i);
				i >= 0; c.prev(), i--) {
			Polynomial::printPolynomial(c.getValue(), i);
		}
		cout << endl;
	}
	
	void demoBinarySearchTree() {
		BST<int> t;
		t.insert(8); t.insert(3); t.insert(10);
		t.insert(1); t.insert(6); t.insert(14);
		t.insert(4); t.insert(7); t.insert(13);
		cout << t.size() << endl;
		Traversal::preorder(t.getRoot()); cout << endl;
		Traversal::inorder(t.getRoot()); cout << endl;
		Traversal::postorder(t.getRoot()); cout << endl;
	}
	
	void demoStack() {
		// cout << balancingSymbols("(){[()]}") << endl;
		// cout << palindromeCheck("abc$cba") << endl;
		LStack<int> a; StackWithMin<int> b;
		SQueue<int> c; Deque<int> d;
	}
};

int main() {
	Demo::demoStack();
	return 0;
}
