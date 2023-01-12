package lib;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;

import lib.MyGraph.Vertex;

/**
 * This class has a static dijkstra method that takes a graph and a source vertex and returns the
 * shortest path from the source vertex to all other vertices in the graph.
 * 
 * This method is a modified version of the Dijkstra's algorithm that was in the Koffman and Wolfgang textbook.
 * 
 * @author Yusuf Arslan
 */
public final class Dijkstras 
{
    // Prevent instantiate a Dijkstras class object
    private Dijkstras() {}

    /**
     * The function takes in a graph, a starting vertex, and two maps, one for the predecessor of each
     * vertex and one for the distance from the starting vertex to each vertex. It then finds the
     * shortest path from the starting vertex to every other vertex in the graph.
     * 
     * @param graph The graph we're working with
     * @param start The starting vertex
     * @param pred A map of vertices to vertices. The key is the vertex and the value is the vertex's
     * predecessor.
     * @param dist A map of vertices to their distances from the start vertex.
     */
    public static void dijkstras(MyGraph graph, Vertex start, Map<Vertex,Vertex> pred, Map<Vertex, Double> dist)
    {
        int numV = graph.getNumV();
		//Initialize V - S
        HashSet<Vertex> vMinusS = new HashSet<Vertex>(numV);
        Iterator<Vertex> itr = graph.getVertices().iterator();
        while (itr.hasNext())
        {
            Vertex v = itr.next();
            if (!v.equals(start))
            {
                vMinusS.add(v);
            }
        }
        for (Vertex v : vMinusS)
        {
            pred.put(v, start);
            Edge edge = graph.getEdge(start.getId(), v.getId());

            if (edge != null)
                dist.put(v, edge.getWeight());
            else
                dist.put(v, Double.POSITIVE_INFINITY);
        }

		//Main loop
        while (!vMinusS.isEmpty())
        {
			//Find the value u in V - S with the smallest dist of u
            double minDist = Double.POSITIVE_INFINITY;
            Vertex u = null;
            for (Vertex v : vMinusS)
            {
                if (dist.get(v) < minDist)
                {
                    minDist = dist.get(v);
                    u = v;
                }
            }

			// Remove u from vMinusS
            vMinusS.remove(u);

			//Update the distances
            Iterator<Edge> edgeIter = graph.edgeIterator(u.getId());
            while (edgeIter.hasNext())
            {
                Edge edge = edgeIter.next();
                Vertex v = graph.getVertex(edge.getDest());
                if (vMinusS.contains(v))
                {
                    // Get the boosting value, if the new distance is smaller then the previous 
                    // value, change the distance.
                    double weight = edge.getWeight();
                    String boosting = u.getProperty("boosting");
                    double boostValue = (boosting == null ? 0 : Double.parseDouble(boosting));
                    if (dist.get(u) + weight - boostValue < dist.get(v))
                    {
                        dist.put(v, dist.get(u) + weight - boostValue);
                        pred.put(v, u);
                    }
                }
            } 
        }
    }
}
