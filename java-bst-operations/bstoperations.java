public boolean isBinarySearchTree(TreeNode<E> root) {
	if (root == null) return true;
	return (
		root.left() == null || (
			(root.left().getElement() < root.getElement())
			&& isBinarySearchTree(root.left())
		)
	) && (
		root.right() == null || (
			(root.right().getElement() >= root.getElement())
			&& isBinarySearchTree(root.right())
		)
	);
}

public TreeNode<E> removeLeaves(TreeNode<E> root) {
	if (root == null) return null;
	if (root.left() == null && root.right() == null) {
		remove(root);
		return null;
	}
	root.setLeft(removeLeaves(root.left()));
	root.setRight(removeLeaves(root.right()));
	return root;
}

public int numOfNodes(TreeNode<E> root) {
	if (root == null) return 0;
	return 1 + numOfNodes(root.left()) + numOfNodes(root.right());
}

public int numOfLeaves(TreeNode<E> root) {
	if (root == null) return 0;
	if (root.left() == null && root.right() == null) return 1;
	return numOfLeaves(root.left()) + numOfLeaves(root.right());
}

public int numOfFullNodes(TreeNode<E> root) {
	// assuming full nodes have two children
	if (root == null) return 0;
	if (root.left() != null && root.right() != null)
		return 1 + numOfFullNodes(root.left())
			+ numOfFullNodes(root.right());
	return numOfFullNodes(root.left()) + numOfFullNodes(root.right());
}	

public boolean find(TreeNode<E> root, E key) {
	if (root == null) return false;
	if (root.getElement() == key) return true;
	return (find(root.left(), key) || find(root.right(), key));
}

public Long sum(TreeNode<Long> root) {
	if (root == null) return 0;
	return root.getElement() + sum(root.left()) + sum(root.right());
}

public void descend(TreeNode<E> root) {
	if (root == null) return;
	descend(root.right());
	System.out.println(root.getElement());
	descend(root.left());
}

public int smallCount(TreeNode<Integer> root, Integer key) {
	if (root == null) return 0;
	if (root.getElement() <= key)
		return 1 + smallCount(root.left()) + smallCount(root.right());
	return smallCount(root.left()) + smallCount(root.right());
}

public void printRange(TreeNode<E> root, E low, E high) {
	if (root == null) return;
	printRange(root.left());
	if (root.getElement() >= low || root.getElement() <= high)
		System.out.println(root.getElement());
	printRange(root.right());
}
