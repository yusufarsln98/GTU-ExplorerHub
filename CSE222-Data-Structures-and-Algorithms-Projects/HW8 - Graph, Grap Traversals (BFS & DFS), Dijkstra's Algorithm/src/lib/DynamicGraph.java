package lib;

import java.util.*;

/**
 * Interface to specify a Graph ADT. It extends Graph interface from the book and
 * adds specific methods for the DynamicGraph class.
 * 
 * @author Yusuf Arslan
 */
public interface DynamicGraph extends Graph {
	//Interface Methods
	
    /**
     * Create a new vertex with the given label and weight.
     * @return The new vertex
     */
    MyGraph.Vertex newVertex(String label, double weight);

    /**
     * Add a new vertex to the graph.
     */
    void addVertex(MyGraph.Vertex vertex);

    /**
     * Add edge to the graph from sourceId to destinationId with the given weight.
     */
    void addEdge(int sourceId, int destinationId, double weight);

    /**
     * Remove the edge from sourceId to vertexId2.
     */
    boolean removeEdge(int sourceId, int destinationId);

    /**
     * Remove a vertex from the graph.
     */
    void removeVertex(int vertexId);

    /**
     * Remove a vertex from the graph with given label.
     */
    void removeVertex(String label);

    /**
     * Filter the vertices by the given user-defined property and returns a subgraph of the graph.
     */
    MyGraph filterVertices(String key, String filter);

    /**
     * Export graph as adjacency matrix.
     */
    double[][] exportAdjacencyMatrix();

    /**
     * Print the graph.
     */
    void printGraph();
}

