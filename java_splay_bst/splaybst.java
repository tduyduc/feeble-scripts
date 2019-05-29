public class BSTEntry<E extends Integer> {
	public E value;
	public BSTEntry parent, left, right;
	public BSTEntry(E v) {
		value = v;
		parent = left = right = null;
	}
}

public class SplayTree<E extends Integer> {
	public BSTEntry root;
	SplayTree() { root = null; }

	private BSTEntry findHelp(E key) {
		BSTEntry prev, curr;
		prev = curr = root;
		while (curr != null) {
			if (key < curr.value) { // left child
				prev = curr;
				curr = curr.left;
			} else if (key > curr.value) { // right child
				prev = curr;
				curr = curr.right;
			} else return curr; // found
		}
		return prev;
	}

	public boolean find(E key) {
		BSTEntry node = findHelp(key); // find matching node
		splay(node);
		if (node == null) return false;
		return key == node.value;
	}

	public void insert(E key) {
		if (root == null) {
			root = new BSTEntry(key);
			return;
		}
		BSTEntry parent = findHelp(key), node = new BSTEntry(key);
		node.parent = parent;
		if (key < parent.value) parent.left = node;
		else parent.right = node;
		splay(node);
	}

	public void remove(E key) {
		BSTEntry node = findHelp(key), parent, succ;
		if (key != node.value) return; // not found, no deletion
		splay(node);
		if (node.left == null && node.right == null) { // leaf node
			parent = node.parent;
			if (parent.left == node)
				parent.left = null;
			else
				parent.right = null;
		} else if (node.left == null) { // has right child only
			parent = node.parent;
			if (parent.left == node)
				parent.left = node.right;
			else
				parent.right = node.right;
		} else if (node.right == null) { // has left child only
			parent = node.parent;
			if (parent.left == node)
				parent.left = node.left;
			else
				parent.right = node.left;
		} else { // has two children
			succ = node.right; // start with right child
			while (succ.left != null)
				succ = succ.left; // find the minimum value of the right child, go all the way to the left
			node.value = succ.value; // put the right child's minimum to the node to be deleted
			parent = succ.parent;
			parent.left = succ.right; // assign the right child because the left child is now empty
		}
	}

	private void rotateLeft(BSTEntry node) {
		BSTEntry succ = node.right;
		if (succ != null) {
			node.right = succ.left;
			if (succ.left != null) succ.left.parent = node;
			succ.parent = node.parent;
		}
		if (node.parent == null) root = succ;
		else if (node == node.parent.left) node.parent.left = succ;
		else node.parent.right = succ;
		if (succ != null) succ.left = node;
		node.parent = succ;
	}

	private void rotateRight(BSTEntry node) {
		BSTEntry succ = node.left;
		if (succ != null) {
			node.left = succ.right;
			if (succ.right != null) succ.right.parent = node;
			succ.parent = node.parent;
		}
		if (node.parent == null) root = succ;
		else if (node == node.parent.left) node.parent.left = succ;
		else node.parent.right = succ;
		if (succ != null) succ.right = node;
		node.parent = succ;
	}

	public void splay(BSTEntry node) {
		if (node == null) return;
		while (node.parent != null) {
			if (node.parent.parent == null) {
				// zig: has parent but no grandparent
				if (node.parent.left == node) rotateRight(node.parent);
				else rotateLeft(node.parent);
			} else if (node.parent.left == node && node.parent.parent.left == node.parent) {
				// zig-zig: grandparent --(left)--> parent --(left)--> current
				rotateRight(node.parent.parent);
				rotateRight(node.parent);
			} else if (node.parent.right == node && node.parent.parent.right == node.parent) {
				// zig-zig: grandparent --(right)--> parent --(right)--> current
				rotateLeft(node.parent.parent);
				rotateLeft(node.parent);
			} else if (node.parent.left == node && node.parent.parent.right == node.parent) {
				// zig-zag: grandparent --(right)--> parent --(left)--> current
				rotateRight(node.parent);
				rotateLeft(node.parent);
			} else {
				// zig-zag: grandparent --(left)--> parent --(right)--> current
				rotateLeft(node.parent);
				rotateRight(node.parent);
			}
		}
	}

	public void printNode(BSTEntry node, int depth) {
		if (node == null) return;
		for (int i = 0; i < depth; i++)
			System.out.print("\t");
		System.out.println(node.value);
	}

	public void preorder(BSTEntry node, int depth) {
		if (node == null) return;
		printNode(node, depth);
		preorder(node.left, depth + 1);
		preorder(node.right, depth + 1);
	}

	public void inorder(BSTEntry node, int depth) {
		if (node == null) return;
		inorder(node.left, depth + 1);
		printNode(node, depth);
		inorder(node.right, depth + 1);
	}
}

public class Program {
    public static void main(String... args) {
        System.out.println("Creating a splay tree...");
        SplayTree bst = new SplayTree();
        bst.insert(5);
        bst.insert(3);
        bst.insert(6);
        bst.insert(8);
        bst.insert(2);
        bst.insert(1);
        bst.insert(4);
        bst.remove(4);
        bst.inorder(bst.root, 0);
    }
}
