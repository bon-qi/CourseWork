#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
#include <fstream>
#include <functional>
#include <chrono>

template <typename T=int>
using mat = std::vector<std::vector<T>>;
using mat_size = std::pair<int,int>;
using mat_sizes = std::vector<std::pair<int,int>>;


std::vector<mat_size> to_mat_sizes(std::vector<int> t){
    std::vector<mat_size> ret;
    for (int i = 0; i < t.size()-1; i++)
        ret.push_back({t[i], t[i+1]});
    return ret;
}

template<typename T=int>
void print_mat(mat<T> mat){
    for (int i = 0; i < mat.size(); i++)
    {
        std::cout << "\t";
        for (int j = 0; j < mat[i].size(); j++)
        {
            std::cout << mat[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

template<typename T=int>
void init_size(mat<T>& mat, int rows, int cols, T default_value = {}){
    mat.resize(rows);
    for (int i = 0; i < rows; i++){
        mat[i].resize(cols);
        for (int j = 0; j < cols; j++)
            mat[i][j] = default_value;
    }
}

template< typename T = std::string>
void print(std::vector<T> x){
    std::cout << " ";
    for (int i = 0; i < x.size(); i++)
       std::cout << x[i] << "\t";
    std::cout << std::endl;
}

std::vector<std::string> split(std::string words, char s = ' ')
{
    std::vector<std::string> ret{{}};
    for (int i = 0; i < words.size(); i++)
    {
        if(words[i] != s) 
            ret.back().push_back(words[i]);
        else if(words[i] == s)
            ret.push_back({});
    }
    return ret;
}

std::vector<int> to_int(std::vector<std::string> s){
    std::vector<int> ret;
    for (int i = 0; i < s.size(); i++)
        ret.push_back(std::atoi(s[i].c_str()));
    return ret;
}

std::vector<mat_sizes> read_input(std::string filepath){
    std::vector<mat_sizes> ret;
    std::ifstream file(filepath);
    std::string temp;
    while (std::getline(file, temp))
    {
        std::vector<std::string> s = split(temp);
        if(s.size() != 1) ret.push_back(to_mat_sizes(to_int(s)));
    }
    file.close();
    return ret;
}

template<typename T =long unsigned int>
void solve(mat_sizes mats, bool verbose=true){
    int n_mat = mats.size();
    mat<T> costs;
    mat<int> chose;
    init_size<T>(costs, n_mat, n_mat); 
    init_size<int>(chose, n_mat, n_mat); 

    for (int i = 0; i < n_mat; i++)
        costs[i][i] = 0;

    for (int i = 0; i < n_mat; i++)
        chose[i][i] = i;

    auto cost = [&costs,&mats](int i, int k, int j){
        // cacu cost from (i-th mat -> k-th mat) x (k+1-th mat, j-th mat)
        // k is the order of "|" <=> k-th mat
        T ret = costs[i][k] + costs[k+1][j] + 1L * mats[i].first * mats[k].second * mats[j].second;
        if(ret > pow(2,sizeof(T)*8-2)) std::cout << "Warning! Overflow Possible! : " << ret << "=" << costs[i][k] << "+" << costs[k+1][j] << "+" << mats[i].first << "*" <<  mats[k].second << "*" <<  mats[j].second << "|||" << 1L * mats[i].first * mats[k].second * mats[j].second  << std::endl;
        return ret;
    };

    for (int j = 1; j < n_mat; j++)
    {
        for (int i = 0; i < n_mat-j; i++)
        {
            std::vector<T> costs_;
            std::vector<int> costs_chose;
            for (int k = i; k <= i+j-1; k++)
            {   
                costs_.push_back(cost(i,k,i+j));
                costs_chose.push_back(k);
            }
            if(costs_.size() != 0){
                // std::cout << "Optimize: " << i << "->" << i+j << ", size: " << costs_.size() << std::endl;
                // print<T>(costs_);
                // print<int>(costs_chose);
                T cost_ = costs_[0];
                int cost_chose = costs_chose[0];
                for (int t = 0; t < costs_.size(); t++)
                {
                    if( cost_ > costs_[t] )
                        cost_ = costs_[t], cost_chose = costs_chose[t];
                 }
                costs[i][i+j] = cost_;
                chose[i][i+j] = cost_chose;
            // std::cout << "costs(" << i << "," << i+j << ") = " << cost_ << std::endl;
            // std::cout << "chose(" << i << "," << i+j << ") = " << cost_chose << std::endl;
            }
        }
    }

    if(verbose){
        print_mat<T>(costs);
        std::cout << std::endl;
        print_mat<int>(chose);
    }


    std::vector<int> chose_summary(n_mat,0);
    std::vector<std::pair<int,int>> summary;

    int order = 1;
    int chose_ = chose[0][n_mat-1];
    chose_summary[chose_] = order++;
    summary.push_back({0, chose_});
    summary.push_back({chose_+1, n_mat-1});

    if(verbose){
        std::cout << "==> chose: " << 0 << "," << chose_ << "," << n_mat-1 << "|" <<  summary.size( ) << std::endl;
        std::cout << "\t\t| Stack: ";
        for (int i = 0; i < summary.size(); i++)
            std::cout << "(" << summary[i].first << "," << summary[i].second << ") ";
        std::cout << std::endl;
        std::cout << "\t\t| Summary: ";
        for (int i = 0; i < chose_summary.size(); i++)
            std::cout << " " << chose_summary[i];
        std::cout << std::endl;
    }

    while (summary.size() != 0)
    {
        std::pair<int,int> chose_ij = summary.back();
        summary.pop_back();
        int chose_ = chose[chose_ij.first][chose_ij.second];
        if(chose_ != chose_ij.first) chose_summary[chose_] = order++;
        if(chose_ij.first < chose_) summary.push_back({chose_ij.first, chose_});
        if(chose_+1 < chose_ij.second) summary.push_back({chose_+1, chose_ij.second});

        if(verbose){
            std::cout << "==> chose: " << chose_ij.first << "," << chose_ << "," << chose_ij.second << "|" <<  summary.size( ) << std::endl;
            std::cout << "\t\t| Stack: ";
            for (int i = 0; i < summary.size(); i++)
                std::cout << "(" << summary[i].first << "," << summary[i].second << ") ";
            std::cout << std::endl;
            std::cout << "\t\t| Summary: ";
            for (int i = 0; i < chose_summary.size(); i++)
                std::cout << " " << chose_summary[i];
            std::cout << std::endl;
        }

    }

    if(verbose){
        for (int i = 0; i < chose_summary.size(); i++)
            std::cout << chose_summary[i] << "\t";
        std::cout << std::endl;
    }
}

int main(){
    // std::cout << sizeof(unsigned long int) << pow(2,64) <<  std::endl;
    // std::cout << sizeof(int) << pow(2,sizeof(int)*8) <<  std::endl;
    // std::cout << sizeof(unsigned int) << pow(2,sizeof(unsigned int)*8) <<  std::endl;
    std::vector<mat_sizes> nums = read_input("../input/2_1_input.txt");
    for (int i = 0; i < nums.size(); i++)
    {
        auto begin = std::chrono::high_resolution_clock::now();
        solve(nums[i], false);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Using time " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << std::endl;
    }
    
    return 0;
}