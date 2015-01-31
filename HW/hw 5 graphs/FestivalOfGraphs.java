  
import java.util.Set;
import java.util.HashSet;
import java.util.List;
import java.util.ArrayList;
import java.util.Stack;
import java.util.Deque;
import java.util.Map;
import java.util.ArrayDeque;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.FileNotFoundException;

class FestivalOfGraphs
{
	private Graph g;
	
	public void init(String graphFile) 
	{
		System.out.println(graphFile);
		// open the file
		BufferedReader br = null;
		
		try
		{
			// open the file called "graph.txt"
			br = new BufferedReader(new FileReader(graphFile));
		
			// read the first line
			String line = br.readLine();	
			
			// convert the first line (a string) to an integer (numberOfVertices)
			Integer n = Integer.parseInt(line);
			
			g = new Graph(n);
		
			for (int fromVertex = 0; fromVertex < n; ++fromVertex)
			{
				line = br.readLine();
				if (line.length() > 0)
				{
					int pos = 0;
					while (line.indexOf("{", pos) > -1)
					{
						String sub = line.substring(line.indexOf("{", pos) + 1, line.indexOf("}", pos + 1));
						Integer toVertex = Integer.parseInt(sub.substring(0, sub.indexOf(",")));
						Integer weightOfEdge = Integer.parseInt(sub.substring(sub.indexOf(",") + 1, sub.length()));
						pos = line.indexOf("}", pos + 1);
						if (!g.hasEdge(fromVertex, toVertex))
							g.addEdge(fromVertex, toVertex, weightOfEdge);
					}	
				}	
			}
		}
		catch (FileNotFoundException ex) {
			// handle FileNotFoundException
			System.out.println("No such file as " + graphFile + " in your directory");
		}
		catch (IOException ex) {
			// handle IOException
			System.out.println("Ran into problems processing " + graphFile);
		}
		finally {
			if (br != null) {
				try {
					br.close();
				}
				catch (IOException ex) {
					// handle IOException
					System.out.println("Ran into unrecoverable problems processing " + graphFile);
				}
			}
		}
		
	}
	
	public List<Integer> DepthFirstList(Integer v)
	{
		List<Integer> vertices = new ArrayList<Integer>();
		Deque<Integer> toExplore = new ArrayDeque<Integer>();
		List<Integer> visited = new ArrayList<Integer>();
		vertices.add(v);
		for(Integer q: g.getAdjList(v).keySet()){
			toExplore.addFirst(q);
		}
		while(!toExplore.isEmpty()){
			Integer r=toExplore.removeFirst();
			if(!vertices.contains(r)){
				vertices.add(r);
			}	
			for(Integer q: g.getAdjList(r).keySet()){
				if(!vertices.contains(q)){
					toExplore.addFirst(q);
				}	
			}
		}		
		return vertices;
	}
	
	public List<Integer> BreadthFirstList(Integer v) 
	{
		List<Integer> vertices = new ArrayList<Integer>();
		Deque<Integer> toExplore = new ArrayDeque<Integer>();
		List<Integer> visited = new ArrayList<Integer>();
		vertices.add(v);
		for(Integer q: g.getAdjList(v).keySet()){
			toExplore.addFirst(q);
		}
		while(!toExplore.isEmpty()){
			Integer r=toExplore.removeLast();
			if(!vertices.contains(r)){
				vertices.add(r);
			}	
			for(Integer q: g.getAdjList(r).keySet()){
				if(!vertices.contains(q)){
					toExplore.addFirst(q);
				}	
			}
		}
		return vertices;
	}

	
	public Graph DepthFirstSpanningTree(Integer v) 
	{
		Graph t = new Graph(g.getNumVertices()); 
		Deque<Integer> toExplore = new ArrayDeque<Integer>();
		List<Integer> visited = new ArrayList<Integer>();
		List<Integer> list=DepthFirstList(v);
		for(int q=0; q <g.getNumVertices();q++){
			Map m=g.getAdjList(list.get(q));
			for(int i=(q-1); i>=0;i--){
				if(m.containsKey(list.get(i))){
					t.addEdge(list.get(q),list.get(i),g.getEdgeWeight(list.get(q),list.get(i)));
					break;
				}
			}
		}			
		return t;
	}
	
	
	public Graph BreadthFirstSpanningTree(Integer v) 
	{
		Graph f = new Graph(g.getNumVertices()); 
		Deque<Integer> toExplore = new ArrayDeque<Integer>();
		List<Integer> visited = new ArrayList<Integer>();
		List<Integer> list=BreadthFirstList(v);
		for(int q=0; q <g.getNumVertices();q++){
			Map m=g.getAdjList(list.get(q));
			for(int i=0; i<q;i++){
				if(m.containsKey(list.get(i))){
					f.addEdge(list.get(q),list.get(i),g.getEdgeWeight(list.get(q),list.get(i)));
					break;
				}
			}
		}			
		return f;
	}

	List<String> DijkstrasShortestPath(Integer t)
	{
		List<Integer> initialized = new ArrayList<Integer>();
		List<Integer> pathWeights = new ArrayList<Integer>();
		List<String> prettyWeights = new ArrayList<String>();
		
		Set<Integer> vertexSet = new HashSet<Integer>();
		
		return prettyWeights;
	}
	
	public Graph PrimsAlgorithm(Integer v) 
	{
		Graph t = new Graph(g.getNumVertices()); 
		return t;
	}
	
	
}

