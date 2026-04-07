#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>
using namespace std;
const int MAX=100000;
const int MAX_VERTICES =20;
template <class T>
struct Edge
{  T vertex;
   int weight;
   Edge(){ vertex=T(); weight=0;} 
};
template <class T>
struct GNode
{   T vertex;
    list<Edge<T>> adjList;
    GNode(){ vertex=T();} 
};
template <class T>
class Graph
{    private:
      GNode <T> arr[MAX_VERTICES];
      int vcount;
      bool isDirected; 
    public:
       Graph(bool directed = false)
       {   vcount = 0;
           isDirected = directed;
       }
       ~Graph()
       {  for (int i=0; i <vcount ;i++)
         { arr[i].adjList.clear();}
         vcount =0;
       } 
       bool isEmpty()
       { return vcount==0;}
       int getVertices()
       { return vcount;}
       int getEdges()
       {
        int count =0;
        for(int i=0; i <vcount ;i++)
        { count += arr[i].adjList.size();}
        if (isDirected) return count; 
        return count/2;               
       }
       int searchVert(T vert)
       {  for (int i=0; i <vcount ;i++)
          { if(arr[i].vertex ==vert)
            return i;   
          }
          return -1;    
       }
       void insertVertex(T vert)
       {   if(vcount >= MAX_VERTICES)
           { cout << "Graph full\n";
             return;
           }
           if(searchVert(vert) != -1)
           { return;}
           arr[vcount].vertex = vert;
           vcount++;
       }
       bool edgeExists(T vert1, T vert2)
       {  int loc = searchVert(vert1);
          if(loc==-1) 
          { return false;}
          typename list<Edge<T>>::iterator temp = arr[loc].adjList.begin();
          while(temp!= arr[loc].adjList.end())
          { if(temp->vertex == vert2)
            { return true;}
            temp++;
          }
          return false;
       }
       void insertEdge(T vert1, T vert2, int weight)
       {int loc1 = searchVert(vert1);
        int loc2 = searchVert(vert2);
        if( loc1!= -1 && loc2!= -1 && !edgeExists(vert1,vert2))
        {   Edge <T> e1;  
            e1.vertex = vert2;
            e1.weight = weight;
            arr[loc1].adjList.push_back(e1);
            if (!isDirected) 
            {   Edge <T> e2;  
                e2.vertex = vert1;
                e2.weight = weight;
                arr[loc2].adjList.push_back(e2);
            }
        }
       }
       void deleteEdge(T vert1,T vert2)
       {  int loc1 = searchVert(vert1);
          int loc2 = searchVert(vert2);
          if(loc1!= -1)
          { typename list <Edge<T>>::iterator temp = arr[loc1].adjList.begin();
            while(temp!= arr[loc1].adjList.end())
            {   if(temp->vertex == vert2) 
                { temp= arr[loc1].adjList.erase(temp);}
                else
                { temp++;}
            }
          }
          if (!isDirected && loc2 != -1)
          { typename list <Edge<T>>::iterator temp = arr[loc2].adjList.begin();
            while(temp != arr[loc2].adjList.end())
            {   if (temp->vertex == vert1) 
                { temp = arr[loc2].adjList.erase(temp);}
                else
                { temp++;}
            }
          }
       }
       void deleteVertex(T vert)
       {int loc = searchVert(vert);
        if(loc== -1)
        { return ;}
        for (int i=0; i<vcount ;i++)
        {  typename list <Edge<T>>::iterator temp = arr[i].adjList.begin();
           while(temp!= arr[i].adjList.end())
           { if(temp-> vertex == vert)
             { temp = arr[i].adjList.erase(temp);}
             else
             { temp++;}
           }
        }
        for (int i=loc ;i<vcount-1;i++)
        { arr[i] = arr[i + 1];}
        vcount--;
       }
       void displayOutgoing(T vert)
       { int loc = searchVert(vert);
         if(loc == -1) return;
         cout << "Outgoing flights from " << vert << ":\n";
         typename list<Edge<T>>::iterator it = arr[loc].adjList.begin();
         while(it != arr[loc].adjList.end())
         { cout << " - " << it->vertex << "  Cost: Rs." << it->weight << "\n"; it++; }
       }
       void displayIncoming(T vert)
       { cout << "Incoming flights to " << vert << ":\n";
         for(int i=0; i<vcount; i++)
         { typename list<Edge<T>>::iterator it = arr[i].adjList.begin();
           while(it != arr[i].adjList.end())
           { if(it->vertex == vert) cout << " - " << arr[i].vertex << " Cost: Rs." << it->weight << "\n"; it++; }
         }
       }
       void BFS(T start)
       { int startLoc = searchVert(start);
        if (startLoc == -1) return;
        bool visited[MAX_VERTICES];
        for (int i =0; i < vcount ;i++) visited[i] = false;
        queue<T> q;
        visited[startLoc] = true;
        q.push(start);
        cout << "BFS Exploration: ";
        while(!q.empty())
        {   T curr = q.front();
            q.pop();
            cout << curr << " " ;
            int loc = searchVert(curr);
            typename list<Edge<T>>::iterator temp = arr[loc].adjList.begin();
           while(temp!= arr[loc].adjList.end()) 
           {  int destLoc = searchVert(temp->vertex);
              if (!visited[destLoc])
              {  visited[destLoc] = true; 
                 q.push(temp->vertex);
              }
              temp++;
           }
        }          
        cout << "\n";
       }
       void DFS(T start)
       { int startLoc = searchVert(start);
        if (startLoc == -1) return;
        bool visited[MAX_VERTICES];
        for (int i =0; i < vcount ;i++) visited[i] = false;
        stack<T> s;
        s.push(start);
        cout << "DFS Network Analysis: ";
        while(!s.empty())
        {  T curr = s.top();
           s.pop();
           int loc = searchVert(curr);
           if(!visited[loc])
           { cout << curr << " ";
             visited[loc] = true;
             typename list<Edge<T>>::iterator temp =arr[loc].adjList.begin();
             while (temp!= arr[loc].adjList.end())
             {  int destLoc = searchVert(temp->vertex);
                if (!visited[destLoc])
                { s.push(temp->vertex);}
                temp++;
             }
            }
        }
        cout<< "\n";
        }
        void shortestPath(T start,T end)
        {  int startLoc = searchVert(start);
           int endLoc = searchVert(end);
           if( startLoc == -1 || endLoc == -1)
           { return ;}
           int dist[MAX_VERTICES];
           int parent[MAX_VERTICES];
           bool visited[MAX_VERTICES];
           for (int i=0; i< vcount; i++)
           { dist[i] = MAX;
             parent[i] = -1;
             visited[i] = false;
            }
            dist[startLoc] =0;
            for (int i=0; i<vcount; i++) 
            {   int u =-1;
                int minD = MAX;
                for(int j=0; j <vcount ;j++)
                { if(!visited[j] && dist[j] <minD)
                  { minD = dist[j];
                    u=j;}
                }
            if (u==-1 || u== endLoc){ break;}
            visited[u] = true;
            typename list <Edge<T>>::iterator temp = arr[u].adjList.begin();
            while(temp != arr[u].adjList.end())
            {   int v = searchVert(temp->vertex);
                if(!visited[v] && dist[u] != MAX && dist[u] + temp->weight < dist[v])
                {  dist[v] = dist[u] + temp->weight;
                   parent[v] = u;}
                temp++;
            }
          }
            if (dist[endLoc] == MAX)
            { cout <<" No path exists\n"; 
             return; }
            list <T> path;
            int currLoc = endLoc;
            while (currLoc!=-1)
            { path.push_front(arr[currLoc].vertex);
              currLoc = parent[currLoc];}
            cout << "Optimal Route: ";
            typename list<T>::iterator temp = path.begin();
            while(temp != path.end())
            { cout << *temp << (next(temp) != path.end() ? " -> " : "");
              temp++;
            }
            cout << "\nTotal Cost: Rs." << dist[endLoc] << "\n";
        }
};
int main() 
{   
    Graph<string> airline(true); 
    airline.insertVertex("Karachi"); 
    airline.insertVertex("Riyadh"); 
    airline.insertVertex("AbuDhabi"); 
    airline.insertVertex("Lahore"); 
    airline.insertVertex("Jeddah"); 
    airline.insertEdge("Karachi", "Riyadh", 500); 
    airline.insertEdge("Riyadh", "AbuDhabi", 400); 
    airline.insertEdge("Karachi", "AbuDhabi", 1000); 
    airline.insertEdge("AbuDhabi", "Lahore", 600); 
    airline.insertEdge("Riyadh", "Lahore", 1200); 
    airline.insertEdge("Lahore", "Jeddah", 300); 
    airline.insertEdge("Jeddah", "Karachi", 800); 
    cout << "    Airline Route System    \n";
    cout << "Total Airports: " << airline.getVertices() << "\n";
    cout << "Total Flight Routes: " << airline.getEdges() << "\n\n";
    airline.displayOutgoing("Riyadh"); 
    airline.displayIncoming("AbuDhabi");
    cout << "\n";
    airline.BFS("Karachi"); 
    airline.DFS("Karachi");
    cout << "\n    Route Optimization    \n";
    airline.shortestPath("Karachi", "Lahore"); 
    cout << "\nRemoving Airport AbuDhabi\n";
    airline.deleteVertex("AbuDhabi");
    airline.shortestPath("Karachi", "Lahore");
    return 0;
}