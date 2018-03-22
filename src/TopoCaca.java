import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;
import static java.util.stream.Collectors.joining;

enum Color {
	BLACK, GREY, WHITE
}

class Vertex implements Comparable {
	Integer k1;
	Integer k2;

	public Vertex(Integer k1, Integer k2) {
		this.k1 = k1;
		this.k2 = k2;
	}

	// XXX:
	// https://beginnersbook.com/2013/12/java-arraylist-of-object-sort-example-comparable-and-comparator/
	@Override
	public int compareTo(Object other) {
		Vertex otherv = (Vertex) other;
		if (otherv.k1 == this.k1) {
			return otherv.k2 - this.k2;
		} else {
			return otherv.k1 - this.k1;
		}
	}
}

class Node {
	Integer key;
	ArrayList<Node> neighbors;
	Color color;

	public Node(Integer key) {
		this.key = key;
		color = Color.WHITE;
		neighbors = new ArrayList<Node>();
	}

	public void addNeighbor(Node n) {
		neighbors.add(n);
	}

}

public class Main {

	public static Boolean topologicarSortRecursive(Node n, Deque<Node> sortedNodes) {
		Boolean done = true;
		n.color = Color.GREY;

		for (Node ne : n.neighbors) {
			switch (ne.color) {
			case WHITE:
				done = topologicarSortRecursive(ne, sortedNodes);
				break;
			case GREY:
				done = false;
				break;
			default:
				assert ne.color == Color.BLACK;
				break;
			}
			if (!done) {
				break;
			}
		}
		if (done) {
			n.color = Color.BLACK;
			sortedNodes.push(n);
		}

		return done;
	}

	public static Deque<Node> topologicalSort(Node[] adjList) {
		Boolean done = true;
		Deque<Node> sortedNodes = new ArrayDeque<Node>();
		for (int i = adjList.length - 1; i > 0; i--) {
			Node n = adjList[i];
			if (n.color == Color.WHITE) {
				done = topologicarSortRecursive(n, sortedNodes);
			}
			if (!done) {
				break;
			}
		}
		if (!done) {
			sortedNodes = null;
		}
		return sortedNodes;
	}
	/*
	 * public static int compareThem(Vertex a, Vertex b) { return a.compareTo(b); }
	 */

	public static void main(String[] args) {
		/*
		 * Enter your code here. Read input from STDIN. Print output to STDOUT. Your
		 * class should be named Solution.
		 */
		Node adjList[];
		Vertex vertices[];
		Deque<Node> sortedNodes;
		Scanner in = new Scanner(System.in);
		Integer v = in.nextInt();
		Integer e = in.nextInt();

		adjList = new Node[v + 1];
		vertices = new Vertex[e];
		for (int i = 0; i <= v; i++) {
			adjList[i] = new Node(i);
		}
		for (int i = 0; i < e; i++) {
			Integer k1 = in.nextInt();
			Integer k2 = in.nextInt();

			vertices[i] = new Vertex(k1, k2);
		}

		Arrays.sort(vertices, (a, b) -> a.compareTo(b));

		for (int i = 0; i < e; i++) {
			Vertex ve = vertices[i];
			Node n1 = adjList[ve.k1];
			Node n2 = adjList[ve.k2];
			n1.neighbors.add(n2);
		}
		sortedNodes = topologicalSort(adjList);
		if (sortedNodes != null) {
			Node[] nodes = new Node[v + 1];
			Integer i = 0;
			while (!sortedNodes.isEmpty()) {
				Node n = sortedNodes.pop();
				if (n.key != 0) {
					nodes[i++] = n;
				}
			}
			StringBuilder sb = new StringBuilder(100000);
			sb.append(nodes[0].key.toString());
			for (int j = 1; j < i; j++) {
				sb.append(" " + nodes[j].key.toString());
			}
			// String s = nodes.stream().map(n -> n.key.toString()).collect(joining(" "));
			String s = sb.toString();

			System.out.println(s);
		} else {
			System.out.println("Sandro fails.");
		}
	}
}
