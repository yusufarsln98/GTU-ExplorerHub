package lib;

import java.util.*;
import lib.MyGraph.Vertex;

/**
 * This class is used to find the difference between the total distances of the graph by BFS and DFS
 * algorithms.
 * 
 * @author Yusuf Arslan
 */
public final class BFSDifferenceDFS
{
    // ----------------------------- DFS -----------------------------
    // ---- Data fields for DFS algorithm ----
    /**
	 * A reference to the graph being searched
	 */
    private static MyGraph theGraph;
	/**
	 * Array of parents in the depth-first search tree
	 */
    private static HashMap<Vertex, Vertex> theParent;
	/**
	 * Flag to indicate whether this vertex has been visited
	 */
    private static HashMap<Vertex, Boolean> theVisited;
	/**
	 * The array that contains each vertex in discovery order
	 */
    private static Vertex[] discoveryOrder;
	/**
	 * The array that contains each vertex in finish order
	 */
    private static Vertex[] finishOrder;
	/**
	 * The index that indicates the discovery order
	 */
    private static int discoveryIndex;
	/**
	 * The index that indicates the finish order
	 */
    private static int finishIndex;

    /**
     * Keeps value of total distance during the DFS where every vertex traverses the
     * smallest edge adjacent to it
     */
    private static int totalDfsDistance;
    // ---- Data fields for DFS algorithm ----


    /**
     * This function is used to find the total distance of the DFS traversal of the graph.
     * 
     * @param graph the graph to be searched
     * @param current the current vertex
     * @return The total distance of the DFS traversal.
     */
    private static double findDfsTotalDistance(MyGraph graph, int current) 
    {
        theGraph = graph;
        int n = theGraph.getNumV();
        theParent = new HashMap<Vertex, Vertex>(n);
        theVisited = new HashMap<Vertex, Boolean>(n);
        discoveryOrder = new Vertex[n];
        finishOrder = new Vertex[n];
        discoveryIndex = 0;
        finishIndex = 0;
        // Get vertices set
        Set<Vertex> vertices = theGraph.getVertices();
        // Iterate through vertices
        for (Vertex v : vertices) {
            // If the vertex has not been visited
            theParent.put(v, null);
        }

        vertices = theGraph.getVertices();

        for (Vertex v : vertices) {
            theVisited.put(v, false);
        }

        totalDfsDistance = 0;

        vertices = theGraph.getVertices();
        for (Vertex v : vertices) {
            if (!theVisited.get(v)) {
                depthFirstSearch(v);
            }
        }
        return totalDfsDistance;
    }

    /**
     * This method iterates through the edges of the vertex, add them to an arraylist, sort them by weight, and
     * then iterate through the arraylist to find the smallest edge. After all,
     * the smallest edge is the smallest distance between the vertex and the other vertices.
     * 
     * @param v the vertex we are currently at
     */
    private static void depthFirstSearch(Vertex v) 
    {
        theVisited.put(v, true);
        discoveryOrder[discoveryIndex++] = v;
        Iterator<Edge> itr = theGraph.edgeIterator(v.getId());
        
        // Add edges to the arraylist and sort them by weight
        ArrayList<Edge> edges = new ArrayList<Edge>();
        while (itr.hasNext()) {
            edges.add(itr.next());
        }
        edges.sort(new Comparator<Edge>() {
            @Override
            public int compare(Edge o1, Edge o2) {
                return (o1.getWeight() - o2.getWeight()) >= 0 ? 1 : -1;
            }
        });
        itr = edges.iterator();

        while (itr.hasNext()) {
            Edge e = itr.next();
            Vertex w = theGraph.getVertex(e.getDest());
            if (!theVisited.get(w)) {
                theParent.put(w, v);
                totalDfsDistance += e.getWeight();
                depthFirstSearch(w);
            }
        }
        finishOrder[finishIndex++] = v;
    }
    // ----------------------------- DFS END -----------------------------
    
    // ----------------------------- BFS -----------------------------
    /**
     * This method returns the total distance of the graph from the initial vertex
     * where the distance is the weight of edges in the shortest path from the
     * initial vertex to the vertex.
     * 
     * @param graph the graph we're working with
     * @param initial the starting vertex
     * @return The total distance from initial to certain level.
     */
    private static double findBfsTotalDistance(MyGraph graph, int initial) 
    {
        // Determine the level since we are looking shortest path from initial to certain level.
        int level = 0;

        // If a vertex is identified as visited, it means that the level has been changed.
        boolean isIdentified = true;
        
        // Get initial vertex.
        Vertex start = graph.getVertex(initial);

        // Create a queue for BFS.
        Queue<Vertex> theQueue = new LinkedList<Vertex>();

        // Create a map for keep the shortest distance.
        HashMap<Vertex, Double> distances = new HashMap<Vertex, Double>();
        
        // Set distance of all vertices to 0.0
        Set<Vertex> vertices = graph.getVertices();
        for (Vertex v : vertices) 
        {
            distances.put(v, 0.0);
        }
        
        // Parent of vertices.
        HashMap<Vertex, Vertex> parent = new HashMap<Vertex, Vertex>();
        
        // Create a map to keep if a vertex is visited.
        HashMap<Vertex, Boolean> identified = new HashMap<Vertex, Boolean>();
        for (Vertex v : vertices) 
        {
            identified.put(v, false);
        }

        // Map to keep the level of each vertex.
        HashMap<Vertex, Integer> levelMap = new HashMap<>();
        
        levelMap.put(start, 0);
        identified.put(start, true);
        theQueue.offer(start);

        // BFS algorithm to find the total distance from initial to certain level.
        while (!theQueue.isEmpty())
        {
            Vertex current = theQueue.poll();
            Iterator<Edge> itr = graph.edgeIterator(current.getId());
            if (isIdentified)
                level++;
            isIdentified = false;

            while (itr.hasNext())
            {
                Edge edge = itr.next();
                Vertex neighbor = graph.getVertex(edge.getDest());
                // If the neighbor is not visited, add it to the queue.
                if (!identified.get(neighbor))
                {
                    identified.put(neighbor, true);
                    theQueue.offer(neighbor);
                    parent.put(neighbor, current);
                    distances.put(neighbor, distances.get(current) + edge.getWeight());
                    levelMap.put(neighbor, level);
                    isIdentified = true;
                }
                else
                {
                    // Check if in level - 1, there is a shortest path to the neighbor, set the short distance.
                    if (levelMap.get(neighbor) - 1 == levelMap.get(current) && 
                        distances.get(neighbor) > distances.get(current) + edge.getWeight())
                    {
                        distances.put(neighbor, distances.get(current) + edge.getWeight());
                        parent.put(neighbor, current);
                    }
                }
            }
        }

        // System.out.println("levels" + levelMap);
        int bfsDistance = 0;
        for (var d : distances.keySet())
        {
            // System.out.println("Vertex " + d.getId() + ": " + distances.get(d));
            bfsDistance += (distances.get(d) - (parent.get(d) == null ? 0 : distances.get(parent.get(d))));
        }

        // System.out.println("parent: " + parent);
        return bfsDistance;
    }
    // ----------------------------- BFS END -----------------------------

    /**
     * Find the total distances of the graph by BFS and DFS algorithm and return the difference.
     * 
     * @param graph The graph to be traversed.
     * @param initial the starting vertex
     * @return The difference between the total distances of the graph by BFS and DFS algorithm.
     */
    public static double bfsDifferenceDfs(MyGraph graph, int initial)
    {
        double bfsDistance = findBfsTotalDistance(graph, initial);
        double dfsDistance = findDfsTotalDistance(graph, initial);
        double difference = bfsDistance - dfsDistance;

        System.out.println("BFS distance: " + bfsDistance);
        System.out.println("DFS distance: " + dfsDistance);

        return difference;
    }
}
