#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include "graph.h"

using namespace std;

void print(matrix t){
	for (int i = 0; i < t.size(); i++)
	{
		for (int j = 0; j < t[i].size(); j++)
		{
			if (t[i][j] == INT_MAX){
				std::cout << " INF" << "\t";
			}
			else if(t[i][j] == -INT_MAX){
				std::cout << "-INF" << "\t";
			}
			else{
				std::cout << t[i][j] << "\t";
			}
		}
		std::cout << std::endl;
	}
}

int main() {
	// _main(1);	// 11 12 21 32  works

	ofstream used_time("./output/time.txt");

	function<void(string, string, string)> exp_once = [&](
		string input, string output, string info)
	{	
		Graph G(input);
		clock_t begin = std::clock();
		matrix mat = G.Johnson(output);
		clock_t end = std::clock();
		used_time << info << "\t" << double(end - begin) << "\t" << double(end - begin)/CLOCKS_PER_SEC << "s" << endl;
		// std::cout << "Using seed " << seed << std::endl;
		// } 
	};
//
	exp_once("./input/input11.txt", "./output/result11.txt", "11");
	exp_once("./input/input12.txt", "./output/result12.txt", "12");
	
	exp_once("./input/input21.txt", "./output/result21.txt", "21");
	exp_once("./input/input22.txt", "./output/result22.txt", "22");
 


	exp_once("./input/input31.txt", "./output/result31.txt", "31");
	exp_once("./input/input32.txt", "./output/result32.txt", "32");

	exp_once("./input/input41.txt", "./output/result41.txt", "41");
	exp_once("./input/input42.txt", "./output/result42.txt", "42");
	// print(t);
	used_time.close();
	return 0;
}
