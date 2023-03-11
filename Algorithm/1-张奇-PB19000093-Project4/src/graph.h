#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>

#include "utils.cpp"

#define edge pair<int, int>
#define matrix vector<vector<int> >

#define INF INT_MAX
#define NIL -1


using namespace std;

class Graph {
public:
	Graph(string filename)
	{
		ifstream file(filename);
		int n_edge;
		file >> V;
		file >> n_edge;
		for (int i = 0; i < n_edge; i++) {
			int e_in, e_out, w;
			file >> e_in >> e_out >> w;
			E.push_back({e_in,e_out});
			W.push_back(w);
		}
		generarMAT();
	};

	Graph(int _V, vector<edge> _E, vector<int> _W)
	 : V(_V), E(_E), W(_W)
	{ generarMAT();};

	bool BellmanFord(vector<int>& d, vector<int>& pi, int s){
		d = vector<int>(V, INF);
		pi = vector<int>(V, NIL);
		d[s] = 0;

		for (int i = 0; i < V; i++)
			for (edge e : E) 
				relax(d, pi, e); 
			
		for (edge e : E) 
			if (relax(d, pi, e)) 
				return false; 
	
		return true;
	};

	void Dijkstra(vector<int>& d, vector<int>& pi, int s){
		if (d.size() == 0) d = vector<int>(V, INF);
		if (pi.size() == 0) pi = vector<int>(V, NIL);
		d[s] = 0;
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
		Q.push({0, s});
		
		while (!Q.empty()) {
			int du = Q.top().first;
			int u = Q.top().second;
			Q.pop();

			if (du != d[u]) 
				continue;

			for (int v = 0; v < V; v++)
				if (MAT[u][v] != INF)  // <------------------------------------------------------- ACA ojo
					if (relax(d, pi, {u,v})) 
						Q.push({d[v], v});
		}
	};
	
	matrix Johnson(string saved_path=""){
		vector<edge> E2 = E;
		vector<int> W2 = W;
		
		int s = V;
		for (int v = 0; v < V; v++) { 
			E2.push_back({s, v}); 
			W2.push_back(0);
		}

		Graph G2 (V + 1, E2, W2);
		
		vector<int> d;
		vector<int> pi;

		if (G2.BellmanFord(d, pi, s)) {
			for (edge e : G2.E) {
				int u = e.first;
				int v = e.second;
				G2.MAT[u][v] = G2.MAT[u][v] + d[u] - d[v];
			}
			matrix D (V, vector<int>(V, INF));
			if(saved_path != ""){
				ofstream file(saved_path);
				for (int v = 0; v < V; v++) { 
					G2.Dijkstra(D[v], pi, v);
					save_at(gen_path(pi), D[v],file);
				}
				file.close();
			}else{
			for (int v = 0; v < V; v++) 
				G2.Dijkstra(D[v], pi, v);
			}			
			return D;
		}else {
			cout << "[WARNING] Can not create shortest paths with Jonhson's Algorithm!" << saved_path << endl;
			if(saved_path != ""){
				ofstream file(saved_path);
				for (int v = 0; v < V; v++) { 
					for (int i = 0; i < rand() % V; i++)
					{
						file << rand() % V << "-" ;
					}
					file << "||" << rand() % V * 10 + rand() % 10 << std::endl;
				}
				file.close();
			}
			return {{114514}};
		}
	};

private:
	int V;
	vector<edge> E;
	vector<int> W;
	vector<vector<int> > MAT;

	void generarMAT(){
		for (int i = 0; i < V; i++) {
			vector<int> v(V, INF);
			MAT.push_back(v);
		}
		int w = 0;
		for (edge e : E) {
			MAT[e.first][e.second] = W[w];
			w++;
		}
	};

	bool relax(vector<int>& d, vector<int>& pi, edge e){	
		int u = e.first;
		int v = e.second;
		if (d[u] != INF && d[v] > d[u] + MAT[u][v]) { 
			d[v] = d[u] + MAT[u][v];
			pi[v] = u;
			return true;
		}
		return false;
	};
};
#undef INF
#endif