class BinomialHeap {
	class BHNode {
		public long key;
		public int degree;
		public BHNode parent, sibling, child;
		BHNode(long value) {
			key = value;
			degree = 0;
			parent = sibling = child = null;
		}
		public BHNode reverse(BHNode s) {
			BHNode ret = this;
			if (sibling != null)
				ret = sibling.reverse(this);
			sibling = s;
			return ret;
		}
		public BHNode find(long value) {
			BHNode temp = nodes, node = null;
			while (temp != null) {
				if (temp.key == value) return temp;
				if (temp.child == null) temp = temp.sibling;
				else {
					node = temp.child.find(value);
					if (node != null) return node;
					temp = temp.sibling;
				}
			}
			return null;
		}
	}
	public BHNode nodes;
	BinomialHeap() {
		nodes = null;
	}

	public void merge(BHNode heap) {
		BHNode temp1 = nodes, temp2 = heap, temp;
		while (temp1 != null && temp2 != null) {
			if (temp1.degree == temp2.degree) {
				temp = temp2;
				temp2 = temp2.sibling;
				temp.sibling = temp1.sibling;
				temp1.sibling = temp;
				temp1 = temp.sibling;
			} else if (temp1.degree < temp2.degree) {
				if (temp1.sibling == null || temp1.sibling.degree > temp2.degree) {
					temp = temp2;
					temp2 = temp2.sibling;
					temp.sibling = temp1.sibling;
					temp1.sibling = temp;
					temp1 = temp.sibling;
				} else temp1 = temp1.sibling;
			} else {
				temp = temp1;
				temp1 = temp2;
				temp2 = temp2.sibling;
				temp1.sibling = temp;
				if (temp == nodes) nodes = temp1;
			}
		}
		if (temp1 == null) {
			temp1 = nodes;
			while (temp1.sibling != null)
				temp1 = temp1.sibling;
			temp1.sibling = temp2;
		}
	}

	public void unionNodes(BHNode heap) {
		merge(heap);
		BHNode prev = null, temp = nodes, next = nodes.sibling;
		while (next != null) {
			if (temp.degree != next.degree || (next.sibling != null && next.sibling.degree == temp.degree)) {
				prev = temp;
				temp = next;
			} else if (temp.key <= next.key) {
				temp.sibling = next.sibling;
				next.parent = temp;
				next.sibling = temp.child;
				temp.child = next;
				temp.degree++;
			} else {
				if (prev == null) nodes = next;
				else prev.sibling = next;
				temp.parent = next;
				temp.sibling = next.child;
				next.child = temp;
				next.degree++;
				temp = next;
			}
			next = temp.sibling;
		}
	}

	public void insert(long value) {
		BHNode temp = new BHNode(value);
		if (nodes == null) nodes = temp;
		else unionNodes(temp);
	}

	public BHNode findMin() {
		BHNode curr = nodes, prev = nodes;
		long min = curr.key;
		while (curr != null) {
			if (curr.key < min) {
				prev = curr;
				min = curr.key;
			}
			curr = curr.sibling;
		}
		return prev;
	}

	public BHNode find(long value) {
		return nodes.find(value);
	}

	public void decreaseKey(long old, long newVal) {
		BHNode temp = find(old);
		if (temp == null) return;
		temp.key = newVal;
		BHNode p = temp.parent;
		while (p != null && temp.key < p.key) {
			long x = temp.key;
			temp.key = p.key;
			p.key = x;
			temp = p;
			p = p.parent;
		}
	}

	public void remove(long value) {
		if (nodes == null || find(value) == null) return;
		decreaseKey(value, findMin().key - 1);
		extractMin();
	}

	public long extractMin() {
		if (nodes == null) return 0;
		BHNode min = findMin(), temp = nodes, prev = null;
		while (temp.key != min.key) {
			prev = temp; temp = temp.sibling;
		}
		if (prev == null) nodes = temp.sibling;
		else prev.sibling = temp.sibling;
		temp = temp.child;
		BHNode dummy = temp;
		while (temp != null) {
			temp.parent = null;
			temp = temp.sibling;
		}
		if (nodes == null) {
			if (dummy != null) nodes = dummy.reverse(null);
		} else if (dummy != null) unionNodes(dummy.reverse(null));
		return min.key;
	}

	public void display() {
		System.out.print("\nHeap:\t");
		display(nodes);
		System.out.println();
	}

	private void display(BHNode node) {
		if (node == null) return;
		display(node.child);
		System.out.print(node.key + "\t");
		display(node.sibling);
	}
}
