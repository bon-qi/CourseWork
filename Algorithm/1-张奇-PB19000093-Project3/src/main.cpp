#include <iostream>
#include <fstream>

#include "intervaltree.hpp"
#define N 50
using namespace Intervals;

int main()
{
    // Create an interval tree
    IntervalTree<int> tree;
    std::vector<Interval<int>> intervals;

    // Print all intervals
    std::function<void(std::string)> printall = [&](std::string s){
        std::cout << std::endl;
        std::cout << s << ", all intervals:" << std::endl;
        int i = 1;
        for (const auto &interval : tree.intervals()) {
            std::cout << interval << "\t (No." <<  i++ << ")." << std::endl;
        }
        std::cout << std::endl;
    };

    // Middle traverse and storage
    std::function<void(std::string)> saveall = [&](std::string out_name){
        std::ofstream out(out_name);
        for (const auto &interval : tree.intervals()) {
            out << interval.low << "\t" << interval.high << std::endl;
        }
        out.close();
    };

    // Get intervals to the tree
    std::ifstream in_data("./input/input.txt");
    int l, r;
    while ((in_data >> l >> r))
    {
        std::cout << l << ", " << r << std::endl;
        tree.insert({l, r});
        intervals.push_back({l,r});
    }
    in_data.close();
    

    printall("After initialization");
    saveall("./output/inorder.txt");

    // Delete by random choice
    std::ofstream del_data("./output/delete_data.txt");
    for (int i = 0; i < 3; i++)
    {
        int t = rand() % intervals.size();
        std::cout << "Selected " << intervals[t] << std::endl;
        del_data << intervals[t].low << "\t" << intervals[t].high << std::endl;
        tree.remove(intervals[t]);
    }
    std::cout << std::endl;
    
    del_data << std::endl;
    for (const auto &interval : tree.intervals()) {
        del_data << interval.low << "\t" << interval.high << std::endl;
    }
    del_data.close();
    printall("After delete 3 nodes");
  
    std::function<void(Interval<int>, std::ofstream&)> search_print = [&](Interval<int> itv, std::ofstream& file){

        std::cout << "Search and print of " << itv << std::endl;
        file <<itv.low << "\t" << itv.high << std::endl << std::endl;

        const auto &overlaps = tree.findOverlappingIntervals(itv);

        std::cout << "Overlapping of " << itv << ":" << std::endl;
        for (const auto &interval : overlaps) {
            std::cout << interval << std::endl;
            file << interval.low << "\t" << interval.high << std::endl;
        }
        file << std::endl << std::endl;
    };

    // Wanted interval and point
    Interval<int> wantedInterval1(rand()%N, rand()%N);
    Interval<int> wantedInterval2(rand()%N, rand()%N);
    Interval<int> wantedInterval3(26, 28);
    
    std::ofstream search_txt("./output/search.txt");
    search_print(wantedInterval1,search_txt);
    search_print(wantedInterval2,search_txt);
    search_print(wantedInterval3,search_txt);

    return 0;
}
