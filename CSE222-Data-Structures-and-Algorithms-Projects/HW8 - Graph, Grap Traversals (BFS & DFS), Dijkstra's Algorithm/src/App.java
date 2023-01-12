import java.util.HashMap;
import java.util.Set;

import lib.*;
import lib.MyGraph.Vertex;

/**
 * This class represents the main application.
 * It includes tester methods for the MyGraph implementation and
 * BFS/DFS algorithms and the Dijkstra's algorithm.
 * 
 * @author Yusuf Arslan
 */
public class App {
    public static void main(String[] args) throws Exception {

        myGraphTester();    
        bfsDifferenceDfsTester();
        dijkstrasTester();
    }

    /**
     * This function creates a graph, adds vertices and edges to it, prints the graph, exports the
     * graph to an adjacency matrix, removes edges and vertices from the graph, filters the graph to
     * only show vertices with the property "Color" = "Blue", and prints the filtered graph.
     */
    private static void myGraphTester() 
    {
        System.out.println("----- MyGraph Implementation and Running Tests -----" + "\n");
        
        MyGraph graph = new MyGraph(false);
        System.out.println("--Echo[1] An undirected graph has been created." + "\n");
        

        MyGraph.Vertex v0 = graph.newVertex("Zero", 0);
        v0.addProperty("Color", "Purple");
        System.out.println("vertex 0: " + v0);

        MyGraph.Vertex v1 = graph.newVertex("One", 1);
        v1.addProperty("Color", "Blue");
        System.out.println("vertex 1: " + v1);

        MyGraph.Vertex v2 = graph.newVertex("Two", 2);
        v2.addProperty("Color", "Grey");
        System.out.println("vertex 2: " + v2);
        
        MyGraph.Vertex v3 = graph.newVertex("Three", 3);
        v3.addProperty("Color", "Grey");
        System.out.println("vertex 3: " + v3);

        MyGraph.Vertex v4 = graph.newVertex("Four", 4);
        v4.addProperty("Color", "Blue");
        System.out.println("vertex 4: " + v4);

        MyGraph.Vertex v5 = graph.newVertex("Five", 5);
        v5.addProperty("Color", "Blue");
        System.out.println("vertex 5: " + v5);

        MyGraph.Vertex v6 = graph.newVertex("Six", 6);
        v6.addProperty("Color", "Blue");
        System.out.println("vertex 6: " + v6);

        MyGraph.Vertex v7 = graph.newVertex("Seven", 7);
        v7.addProperty("Color", "Purple");
        System.out.println("vertex 7: " + v7);

        MyGraph.Vertex v8 = graph.newVertex("Eight", 8);
        v8.addProperty("Color", "Purple");
        System.out.println("vertex 8: " + v8);

        MyGraph.Vertex v9 = graph.newVertex("Nine", 9);
        v9.addProperty("Color", "Blue");
        System.out.println("vertex 9: " + v9 + "\n");

        System.out.println("--Echo[2] Vertices have been created." + "\n");

        graph.addVertex(v0);
        graph.addVertex(v1);
        graph.addVertex(v2);
        graph.addVertex(v3);
        graph.addVertex(v4);
        graph.addVertex(v5);
        graph.addVertex(v6);
        graph.addVertex(v7);
        graph.addVertex(v8);
        graph.addVertex(v9);

        System.out.println("--Echo[3] Vertices have been added to the graph." + "\n");
        System.out.println("The Graph");
        graph.printGraph();
        System.out.println("\n");


        graph.addEdge(0, 1, 2);
        graph.addEdge(0, 3, 10);
        graph.addEdge(1, 4, 7);
        graph.addEdge(1, 6, 8);
        graph.addEdge(1, 7, 6);
        graph.addEdge(1, 2, 1);
        graph.addEdge(2, 3, 32);
        graph.addEdge(2, 8, 17);
        graph.addEdge(2, 9, 15);
        graph.addEdge(4, 5, 5);
        graph.addEdge(4, 6, 26);
        graph.addEdge(4, 7, 12);
        graph.addEdge(6, 7, 14);
        
        System.out.println("--Echo[4] Edges have been added to the graph." + "\n");
        System.out.println("The Graph");
        graph.printGraph();
        System.out.println("\n");

        double[][] adjacencyMatix = graph.exportAdjacencyMatrix();
        System.out.println("--Echo[5] Adjacency Matrix exported." + "\n");
        System.out.println("The Matrix");
        MyGraph.printMatrix(adjacencyMatix);
        System.out.println("\n");

        // Remove edge from graph.
        graph.removeEdge(0, 1);
        System.out.println("--Echo[6] Edge (0,1) has been removed." + "\n");
        System.out.println("The Graph");
        graph.printGraph();
        System.out.println("\n");

        // Remove another edge from graph.
        graph.removeEdge(2, 3);
        System.out.println("--Echo[7] Edge (2,3) has been removed." + "\n");
        System.out.println("The Graph");
        graph.printGraph();
        System.out.println("\n");

        // Remove a vertex from graph.
        graph.removeVertex(1);
        System.out.println("--Echo[8] Vertex 1 has been removed." + "\n");
        System.out.println("The Graph");
        graph.printGraph();
        System.out.println("\n");

        // Export the graph to the matrix and print it.
        adjacencyMatix = graph.exportAdjacencyMatrix();
        System.out.println("--Echo[9] Adjacency Matrix exported." + "\n");
        System.out.println("The Matrix");
        MyGraph.printMatrix(adjacencyMatix);
        System.out.println("\n");
        
        // Filter the graph to only show vertices with the property "Color" = "Blue".
        MyGraph filteredGraph = graph.filterVertices("Color", "Blue");
        System.out.println("--Echo[10] Graph filtered to only show vertices with the property \"Color\" = \"Blue\"." + "\n");
        System.out.println("The Filtered Graph");
        filteredGraph.printGraph();
        System.out.println("\n");

        // Export the filtered graph to the matrix and print it.
        adjacencyMatix = filteredGraph.exportAdjacencyMatrix();
        System.out.println("--Echo[11] Adjacency Matrix of filtered graph exported." + "\n");
        System.out.println("The Matrix");
        MyGraph.printMatrix(adjacencyMatix);
        System.out.println("\n");
    }

    /**
     * The function takes a graph and a source vertex as input and returns the difference between the
     * distances of the shortest path between the source vertex from the initial vertex and all other vertices in the graph
     * using BFS, and if smallest edge will be choosen in DFS algorithms.
     */
    private static void bfsDifferenceDfsTester() {

        System.out.println("\n----- BFS and DFS Difference Test ----- \n");
        MyGraph graph = new MyGraph(8, false);
        System.out.println("--Echo[1] A graph with size 8 created." + "\n");

        graph.addEdge(0, 1, 1);
        graph.addEdge(0, 2, 3);
        graph.addEdge(0, 3, 2);
        graph.addEdge(1, 4, 10);
        graph.addEdge(2, 4, 1);
        graph.addEdge(3, 4, 4);
        graph.addEdge(4, 5, 5);
        graph.addEdge(4, 6, 4);
        graph.addEdge(5, 6, 1);
        graph.addEdge(5, 7, 2);
        graph.addEdge(6, 7, 6);

        System.out.println("--Echo[2] Edges have been added to the graph." + "\n");


        System.out.println("The Graph");
        graph.printGraph();
        System.out.println("\n");

        System.out.println("--Echo[3] Print the difference of distances between BFS" + 
                           "and DFS algorithm if the smallest path choosen." + "\n");
        
        System.out.println("Difference: " + BFSDifferenceDFS.bfsDifferenceDfs(graph, 0));
        System.out.println("\n");
    }

    private static void dijkstrasTester() {
            
        System.out.println("\n----- Dijkstras Test ----- \n");
        MyGraph graph = new MyGraph(true);
        System.out.println("--Echo[1] A graph with size 5 created." + "\n");

        Vertex v0 = graph.newVertex("", 1);

        Vertex v1 = graph.newVertex("", 1);

        Vertex v2 = graph.newVertex("", 1);

        Vertex v3 = graph.newVertex("", 1);

        Vertex v4 = graph.newVertex("", 1);

        graph.addVertex(v0);
        graph.addVertex(v1);
        graph.addVertex(v2);
        graph.addVertex(v3);
        graph.addVertex(v4);


        graph.addEdge(0, 1, 10);
        graph.addEdge(0, 3, 30);
        graph.addEdge(0, 4, 100);
        graph.addEdge(1, 2, 50);
        graph.addEdge(2, 4, 10);
        graph.addEdge(3, 2, 20);
        graph.addEdge(3, 4, 60);


        System.out.println("--Echo[2] Edges have been added to the graph." + "\n");

        System.out.println("The Graph");
        graph.printGraph();
        System.out.println("\n");

        Vertex start = graph.getVertex(0);

        HashMap<Vertex,Vertex> pred = new HashMap<Vertex,Vertex>(); 
        HashMap<Vertex, Double> dist = new HashMap<Vertex, Double>();


        Set<Vertex> vertices = graph.getVertices();

        for (Vertex v : vertices)
        {
            pred.put(v, null);
            dist.put(v, Double.POSITIVE_INFINITY);
        }
        Dijkstras.dijkstras(graph, start, pred, dist);
        System.out.println("--Echo[3] Dijkstras algorithm has been run." + "\n");

        System.out.println("Results before boosting" + "\n");

        System.out.println("The Predecessor Map");
        System.out.println(pred);
        System.out.println("\n");
        System.out.println("The Distance Map");
        System.out.println(dist);
        System.out.println("\n");

        System.out.println("--Echo[4] Boost the 1st vertex with 20." + "\n");
        v1.addProperty("boosting", "20");

        Dijkstras.dijkstras(graph, start, pred, dist);

        System.out.println("Results after boosting" + "\n");

        System.out.println("The Predecessor Map");
        System.out.println(pred);
        System.out.println("\n");
        System.out.println("The Distance Map");
        System.out.println(dist);
        System.out.println("\n");
        
    }
}
