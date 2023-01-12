package lib;

import java.util.*;

/**
 * MyGraph implements DynamicGraph interface.
 * 
 * @author Yusuf Arslan
 */
public class MyGraph implements DynamicGraph {
    
    // To prevent the user from creating Vertex object explicitly, I created a protected class Vertex.
    public static class Vertex {

        // Data fields
        public static final double UNWEIGHTED_VERTEX = 1.0;
        
        private int id;
        private String label;
        private double weight;
        private HashMap<String, String> properties;

        // Constructor
        /**
         * Constructor for Vertex with given label and weight.
         * 
         * @param label
         * @param weight
         */
        private Vertex(String label, double weight)
        {
            this.id = -1;
            this.label = label;
            this.weight = weight;
            this.properties = new HashMap<String, String>();
        }

        /**
         * Construct a vertex with given label, weight and ID.
         * 
         * @param label The label for the vertex
         * @param weight The weight of the vertex
         * @param id The ID of the vertex
         */
        private Vertex(String label, double weight, int id) {
            this.id = id;
            this.label = label;
            this.weight = weight;
            this.properties = new HashMap<String, String>();
        }
        
        /**
         * Construct a vertex with given ID.
         * This method will be used as anoymous object when searching required in the graph.
         * @param id
         */
        private Vertex(int id) {
            this.id = id;
            this.label = "";
            this.weight = UNWEIGHTED_VERTEX;
            this.properties = new HashMap<String, String>();
        }
         

        /**
         * Add property to the vertex.
         * 
         * @param key The key of the property
         * @param value The value of the property
         */
        public void addProperty(String key, String value) {
            properties.put(key, value);
        }

        /**
         * Get the value of the property with the given key.
         * 
         * @param key The key of the property
         * @return The value of the property
         */
        public String getProperty(String key) {
            return properties.get(key);
        }
        
        /**
         * This function sets the id of the object to the value of the parameter id.
         * 
         * @param id The id of the user.
         */
        private void setId(int id) {
            this.id = id;
        }

        /**
         * This function returns the id of the object.
         * 
         * @return The id of the object.
         */
        public int getId() {
            return id;
        }

        /**
         * This function sets the weight of the object to the value of the parameter weight.
         * 
         * @param weight The weight of the edge.
         */
        private void setWeight(double weight) {
            this.weight = weight;
        }

        /**
         * This function returns the weight of the object
         * 
         * @return The weight of the object.
         */
        public double getWeight() {
            return weight;
        }

        /**
         * This function sets the label of the current object to the label passed in as a parameter
         * 
         * @param label The label of the button.
         */
        public void setLabel(String label) {
            this.label = label;
        }

        /**
         * This function returns the label of the node
         * 
         * @return The label of the card.
         */
        private String getLabel() {
            return label;
        }

        /**
         * Hash code for the vertex object.
         */
        @Override
        public int hashCode() {
            return Integer.hashCode(id);
        }

        /**
         * Returns true if the ID of the object is equal to the ID of the parameter.
         */
        @Override
        public boolean equals(Object obj) {
            if (this == obj)
                return true;
            if (obj == null)
                return false;
            if (getClass() != obj.getClass())
                return false;
            Vertex other = (Vertex) obj;
    
            if (id != other.id)
                return false;
            return true;
        }

        @Override
        @SuppressWarnings("unchecked")
        protected Object clone() {
            // Clone all the properties and return a new Vertex object.
            Vertex newVertex = new Vertex(label, weight);
            newVertex.properties = (HashMap<String, String>) properties.clone();
            return newVertex;
        }
        /**
         * Returns a string representation of the vertex.
         */
        @Override
        public String toString() {
            return "[" + "(" + id + " : \"" + label + "\"" + ")" + " : " + weight + "]";
        }
    }
    
    /**
     * Static int to keep track of next available ID.
     */
    private int NEXT_ID = 0;

    /**
	 * Number of vertices
	 */
	private int numV;

	/**
	 * Flag to indicate whether this is a directed graph
	 */
	private boolean directed;

    /**
     * The adjacency list of the graph.
     */
    private HashMap<Vertex, List<Edge>> adjList;

    /**
     * Construct a graph setting directed to false.
     */
    public MyGraph() {
        this(false);
    }

    /**
     * Construct a graph with the boolean flag to indicate whether it is directed.
     */
    public MyGraph(boolean directed) {
        this.numV = 0;
        this.directed = directed;
        this.adjList = new HashMap<Vertex, List<Edge>>();
    }

    /**
     * Construct a graph with the given number of vertices and directed value.
     */
    public MyGraph(int numV, boolean directed) {
        this.numV = numV;
        this.directed = directed;
        this.adjList = new HashMap<Vertex, List<Edge>>();
        for (int i = 0; i < numV; i++) {
            this.adjList.put(new Vertex(i), new LinkedList<Edge>());
        }
        NEXT_ID = numV;
    }

    /**
     * Get number of vertices in the graph.
     */
    @Override
    public int getNumV() {
        return numV;
    }

    /**
     * Return true if it is directed, false otherwise.
     */
    @Override
    public boolean isDirected() {
        return directed;
    }

    /**
     * If the edge is not already in the graph, add it to the source vertex and, if the graph is not
     * directed, add it to the destination vertex as well.
     * 
     * @param edge The edge to be inserted.
     */
    @Override
public void insert(Edge edge) {
    
    // Do not allow duplicate edges.
    if (isEdge(edge.getSource(), edge.getDest()))
        return;
    
    List<Edge> sourceEdges = adjList.get(new Vertex(edge.getSource()));
    sourceEdges.add(edge);
    if (!isDirected() && edge.getSource() != edge.getDest()) {
        List<Edge> destEdges = adjList.get(new Vertex(edge.getDest()));
        destEdges.add(new Edge(edge.getDest(), edge.getSource(), edge.getWeight()));
    }
}

    /**
     * If the source vertex has an edge to the destination vertex, return true, otherwise return false.
     * 
     * @param source The id of the source vertex.
     * @param dest The id of the destination vertex.
     * @return A boolean value.
     */
    @Override
    public boolean isEdge(int source, int dest) {
        // Get the edge list of source vertex and check if edge exists. 
        return adjList.get(new Vertex(source)).
                       contains(new Edge(source, dest));
    }

    /**
     * Get the edge from the source vertex to the destination vertex.
     * 
     * @param source The id of the source vertex.
     * @param dest The id of the destination vertex.
     * @return The edge between the source and destination vertices.
     */
    @Override
    public Edge getEdge(int source, int dest) {
        // Get the edge list of source vertex and return the edge if it is exists, or null.
        List<Edge> edges = adjList.get(new Vertex(source));
        if (edges == null || !edges.contains(new Edge(source, dest)))
            return null;

        return edges.get(edges.indexOf(new Edge(source, dest)));
    }

    /**
     * Return an iterator over the edges of the vertex with the given id.
     * 
     * @param id The id of the vertex to get the edge iterator for.
     * @return An iterator of edges.
     */
    @Override
    public Iterator<Edge> edgeIterator(int id) {
        return adjList.get(new Vertex(id)).iterator();
    }

    /**
     * This function creates a new vertex with the given label and weight
     * 
     * @param label The label of the vertex.
     * @param weight The weight of the vertex.
     * @return A new vertex with the given label and weight.
     */
    @Override
    public Vertex newVertex(String label, double weight) {
        return new Vertex(label, weight);
    }

    /**
     * If there is a removed ID in the queue, set the id of the vertex to the removed ID. Otherwise,
     * set the id of the vertex to the next ID
     * 
     * @param vertex The vertex to be added to the graph.
     */
    @Override
    public void addVertex(Vertex vertex) {
        vertex.setId(NEXT_ID++);
        adjList.put(vertex, new LinkedList<Edge>());
        numV++;
    }

    private void addVertex(Vertex vertex, int id) {
        vertex.setId(id);
        adjList.put(vertex, new LinkedList<Edge>());
        numV++;
    }

    /**
     * If the graph is not directed, remove all edges in the destination vertices and then set the
     * corresponding vertex to null
     * 
     * @param id The id of the vertex to be removed.
     */
    @Override
    public void removeVertex(int id) {
        // Remove all edges in the destination vertices.
        if (!isDirected()) {
            // If graph is not directed, find all edges in destination vertices and remove them.
            Iterator<Edge> edgeIterator = edgeIterator(id);
            while (edgeIterator.hasNext()) {
                Edge edge = edgeIterator.next();
                edgeIterator.remove();
                removeEdge(edge.getDest(), edge.getSource());
            }
        }
        else {
            // If graph is directed, remove all edges that connected to the vertex.
            Iterator<Vertex> vertices = adjList.keySet().iterator();
            while (vertices.hasNext()) {
                Vertex current = vertices.next();
                removeEdge(current.getId(), id);
            }
        }
        // Then set corresponding vertex to null.
        adjList.remove(new Vertex(id));
        // Add the id to the queue of removed vertices.
        numV--;
    }

    /**
     * Find the vertex with the given label and remove it.
     * 
     * @param label The label of the vertex to remove.
     */
    @Override
    public void removeVertex(String label) {
        // Find the vertex with the given label and remove it.
        Iterator<Vertex> vertices = adjList.keySet().iterator();
        
        while (vertices.hasNext())
        {
            Vertex current = vertices.next();
            if (current.getLabel().equals(label))
            {
                removeVertex(current.getId());
                return;
            }
        }
    }

    /**
     * The addEdge function adds an edge to the graph.
     * If the edge is not already in the graph, add it to the source vertex and, if the graph is not
     * directed, add it to the destination vertex as well.
     * 
     * @param source The ID of the source vertex.
     * @param dest The ID of the destination vertex.
     * @param weight The weight of the edge.
     */
    @Override
    public void addEdge(int source, int dest, double weight) {
        // Create edge with IDs of source and destination and weight.
        Edge edge = new Edge(source, dest, weight);
        
        insert(edge);
    }

    /**
     * If the edge is in the graph, remove it from the source vertex and, if the graph is not
     * directed, remove it from the destination vertex as well.
     */
    @Override
    public boolean removeEdge(int source, int dest) {
        // Remove the edge from the vertices.

        // Get list of edges from source vertex.
        List<Edge> sourceEdges = adjList.get(new Vertex(source));

        boolean removed = sourceEdges.remove(new Edge(source, dest));

        if (removed && !isDirected() && source != dest)
            adjList.get(new Vertex(dest)).remove(new Edge(dest, source));

        return removed;
    }

    /**
     * We create a new array with the number of vertices. Then, we change ID's to 0-based index. To
     * compress the matrix, we will ignore null indexes and store wieghts from 0 to number of vertices.
     * 
     * @return The adjacency matrix of the graph.
     */
    @Override
    public double[][] exportAdjacencyMatrix() {
        
        // To create the adjacency matrix, create a new array with the number of vertices.
        // Then, change ID's to 0-based index. 
        // To compress the matrix, we will ignore null 
        // indexes and store wieghts from 0 to number of vertices.

        // Create the adjacency matrix.
        double adjacencyMatix[][] = new double[numV][numV];
        // Fill the array with Double.POSITIVE_INFINITY.
        for (int i = 0; i < numV; i++) {
            for (int j = 0; j < numV; j++) {
                adjacencyMatix[i][j] = Double.POSITIVE_INFINITY;
            }
        }

        // Iterate through the vertices and rearrange the previous IDs with the matrix graph IDs from 0 to n - 1.
        Iterator<Vertex> vertices = adjList.keySet().iterator();
        HashMap<Integer, Integer> idMap = new HashMap<Integer, Integer>();
        for (int i = 0; i < numV; i++)
        {
            Vertex current = vertices.next();
            idMap.put(current.getId(), i);
        }

        vertices = adjList.keySet().iterator();
        while (vertices.hasNext()) {
            Vertex current = vertices.next();
            // Get the list of edges from the current vertex.
            List<Edge> edges = adjList.get(current);
            // Iterate through the edges.
            for (Edge edge : edges) {
                // Set the weight of the edge in the adjacency matrix.
                adjacencyMatix[idMap.get(current.getId())][idMap.get(edge.getDest())] = edge.getWeight();
            }
        }

        return adjacencyMatix;
    }

    @Override
    public MyGraph filterVertices(String key, String filter) {
        
        MyGraph filteredGraph = new MyGraph(isDirected());

        // Iterate through the vertices and add the vertices that match the filter.
        Iterator<Vertex> vertices = adjList.keySet().iterator();
        
        while (vertices.hasNext()) {
            Vertex current = vertices.next();
            if (current.getProperty(key).equals(filter))
            {
                filteredGraph.addVertex(((Vertex)current.clone()), current.getId());
            }
        }

        Iterator<Vertex> filteredVertices = filteredGraph.adjList.keySet().iterator();
        while (filteredVertices.hasNext()) {
            Vertex current = filteredVertices.next();
            // Get the list of edges from the current vertex.
            List<Edge> edges = adjList.get(current);
            for (Edge edge : edges) {
                if (filteredGraph.getVertex(edge.getDest()) != null)
                {
                    filteredGraph.addEdge(edge.getSource(), edge.getDest(), edge.getWeight());
                }
            }
        }
        return filteredGraph;
    }

    /**
     * For each vertex in the graph, print the vertex, then iterate through all of its edges and print
     * the edge weight and the destination vertex.
     */
    @Override
    public void printGraph() {
        
        Iterator<Vertex> vertices = adjList.keySet().iterator();
        while (vertices.hasNext()) {
            Vertex vertex = vertices.next();
            System.out.print(vertex);
            Iterator<Edge> edges = edgeIterator(vertex.getId());
            while (edges.hasNext()) {
                Edge edge = edges.next();
                System.out.print(" —> " + edge);
            }
            System.out.println();
        }
    }

    // Helpers
    /**
     * Get vertex with the given ID.
     * @param id
     * @return Vertex with the given ID, null if it does not exists.
     */
    public Vertex getVertex(int id) {
        Iterator<Vertex> vertices = adjList.keySet().iterator();
        while (vertices.hasNext()) {
            Vertex current = vertices.next();
            if (current.getId() == id) {
                return current;
            }
        }
        return null;
    }
    
    /**
     * Print 2d the matrix.
     */
    public static void printMatrix(double[][] matrix) {
        for (int i = 0; i < matrix.length; i++)
        {
            System.out.print("\t" + i);
        }
        System.out.println();
        for (int i = 0; i < matrix.length; i++) {
            System.out.print(i + "\t");
            for (int j = 0; j < matrix[i].length; j++) {
                if (matrix[i][j] == Double.POSITIVE_INFINITY) {
                    System.out.print("inf \t");
                }
                else {
                    System.out.print(matrix[i][j] + " \t");
                }
            }
            System.out.println();
        }
    }

    // They are not safe but necessary for the project.
    public Set<Vertex> getVertices() {
        return adjList.keySet();
    }
    
}

