#ifndef UTILS_CPP
#define UTILS_CPP
#include <random>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

bool check(std::vector<int> v, int t){
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == t)
            return false;
    }
    return true;
}

void gen_save(int n_vertices, int n_degree, std::pair<int,int> w_itv, std::string filename, int seed=1){
    std::ofstream file(filename);
    srand(seed);
    file << n_vertices << "\t" << n_vertices * n_degree << std::endl;
    int l_w_itv = w_itv.second - w_itv.first;
    for (int i = 0; i < n_vertices; i++)
    {
        std::vector<int> to;
        std::vector<int> w;
        while (to.size() < n_degree)
        {
            int to_edge = rand() % n_vertices;
            int to_weight = rand() % l_w_itv + w_itv.first;
            if (check(to,to_edge))
            {
                to.push_back(to_edge);
                w.push_back(to_weight);
            }
        }
        
        for (int j = 0; j < n_degree; j++)
        {
            file << i << "\t" << to[j] << "\t" << w[j] << std::endl;
        }
    }
    file.close();
}

int _main(int seed=1){
    srand(seed);
    gen_save(27,int(log(27)/log(5)),{-10,50},"./input/input11.txt");
    gen_save(27,int(log(27)/log(7)),{-10,50},"./input/input12.txt");

    gen_save(81,int(log(81)/log(5)),{-10,50},"./input/input21.txt");
    gen_save(81,int(log(81)/log(7)),{-10,50},"./input/input22.txt");

    gen_save(243,int(log(243)/log(5)),{-10,50},"./input/input31.txt");
    gen_save(243,int(log(243)/log(7)),{-10,50},"./input/input32.txt");

    gen_save(729,int(log(729)/log(5)),{-10,50},"./input/input41.txt");
    gen_save(729,int(log(729)/log(7)),{-10,50},"./input/input42.txt");

    return 0;
}


vector<vector<int>> gen_path(vector<int> pi){
	vector<vector<int>> ret(pi.size()-1);
	
	for (int i = 0; i < pi.size()-1; i++)
		ret[i].push_back(i);
	
	for (int i = 0; i < pi.size(); i++)
	{
		int t = pi[i];
		while (t != -1 && check(ret[i],t))
		{
			ret[i].push_back({t});
			t = pi[t];
		}
	}
	return ret;
}

void save_at(vector<vector<int>> paths, vector<int> dv, ofstream& file){
	for (int i = 0; i < paths.size(); i++)
	{
		for (int j = 0; j < paths[i].size(); j++)
		{
			file << paths[i][j] << "-";
		}
		file << " | " << dv[i] << std::endl;
	}
}
#endif //UTILS_CPP