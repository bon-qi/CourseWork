#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>

using match = std::pair<std::string, std::string>;

std::vector<match> read_data(std::string filename){
    std::vector<match> ret;
    std::ifstream file(filename);

    std::string descrip;
    while (std::getline(file,descrip))
    {
        std::string line1, line2;
        std::getline(file, line1);
        std::getline(file, line2);
        ret.push_back({line1, line2});
    }
    file.close();
    return ret; 
}

void print(std::vector<match> matches){
    for (int i = 0; i < matches.size(); i++)
    {
        std::cout << matches[i].first << std::endl;
        std::cout << matches[i].second << std::endl;
    }
    std::cout << std::endl;
}

void print(std::vector<std::vector<bool>> mat){
    for (int i = 0; i < mat.size(); i++)
    {
        std::cout << "\t";
        for (int j = 0; j < mat[0].size(); j++)
        {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;   
    }
}

void print(std::vector<std::vector<int>> mat){
    for (int i = 0; i < mat.size(); i++)
    {
        std::cout << "\t";
        for (int j = 0; j < mat[0].size(); j++)
        {
            std::cout << mat[i][j] << "\t";
        }
        std::cout << std::endl;   
    }
}

std::vector<std::pair<int,int>> Match(match words){
    /// @brief match two strings with lcp
    /// @param words 
    /// @return a pair of {first_sub, second_sub}
    int n = words.first.size()-1;
    int m = words.second.size()-1;
    // std::cout << n << "," << m << std::endl;
    std::vector<std::vector<bool>> mat(n, std::vector<bool>(m, false));
    
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++){
        if(words.first[i] == words.second[j]){
            mat[i][j] = true;
        }
    }

    enum {
        col_minus1 = -1,
        eq = 0,
        row_minus1 = 1,
        none = -2
    };

    std::vector<std::vector<int>> l(n, std::vector<int>(m, 0));
    std::vector<std::vector<int>> d(n, std::vector<int>(m, none));


    l[0][0] = mat[0][0];

    for (int j = 1; j < m; j++){
        if (mat[0][j] == true)
        {
            l[0][j] = 1;
            d[0][j] = eq;
        }
        else {
            l[0][j] = l[0][j-1];
            d[0][j] = row_minus1;
        }
    }

    for (int i = 1; i < n; i++){
        if (mat[i][0] == true)
        {
            l[i][0] = 1;
            d[i][0] = eq;
        }
        else {
            l[i][0] = l[i-1][0];
            d[i][0] = col_minus1;
        }
    }
    
    for (int i = 1; i < n; i++) for (int j = 1; j < m; j++)
    {
        if (mat[i][j] == true)
        {
            l[i][j] = l[i-1][j-1] + 1;
            d[i][j] = eq;
        }
        else if (l[i][j-1] > l[i-1][j])
        {
            l[i][j] = l[i][j-1];
            d[i][j] = row_minus1;
        }
        else {
            l[i][j] = l[i-1][j];
            d[i][j] = col_minus1;
        }
    }

    // print(mat);
    // std::cout << std::endl;
    // print(l);
    // std::cout << std::endl;
    // print(d);

    int sub_col = n-1;
    int sub_row = m-1;
    std::vector<std::pair<int,int>> sub_seq;

    while (sub_col != 0 && sub_row != 0)
    {
        // std::cout << "(" << sub_col << "," << sub_row << ") -> ";
        if (d[sub_col][sub_row] == eq){
            sub_seq.push_back({sub_col, sub_row});
            sub_col--;
            sub_row--;
        }
        else if(d[sub_col][sub_row] == row_minus1)
            sub_row--;
        else if(d[sub_col][sub_row] == col_minus1)
            sub_col--;
    }
    if (sub_col == 0 && sub_row != 0)
    {
        while (d[sub_col][sub_row] != eq && sub_row != 0)
        {
            sub_row--;
        }
    }
    else if(sub_row == 0 && sub_row !=0)
    {
        while (d[sub_col][sub_row] != eq && sub_col != 0)
        {
            sub_col--;
        }
    }
    if (d[sub_col][sub_row] == eq)
    {
        sub_seq.push_back({sub_col, sub_row});
    }
    return sub_seq;
}

void do_question(match m, bool verbose=false){

    std::vector<std::pair<int,int>> sub_seq = Match(m);

    std::cout << "Size: "<< sub_seq.size() << std::endl;
    for (int i = 0; i < sub_seq.size(); i++)
            std::cout << m.first[sub_seq[i].first] << " ";
    std::cout << std::endl;


    if(verbose){
        std::cout << m.first << std::endl;
        std::cout << m.second << std::endl;
        for (int i = 0; i < sub_seq.size(); i++)
        {
            std::cout << "(" << sub_seq[i].first << "," << sub_seq[i].second << ")" << "\t";
        }
        std::cout << std::endl;
        std::cout << "a.k.a" << std::endl;
        for (int i = 0; i < sub_seq.size(); i++)
        {
            std::cout << m.first[sub_seq[i].first] << " ";
        }
        std::cout << std::endl;
        for (int i = 0; i < sub_seq.size(); i++)
        {
            std::cout << m.second[sub_seq[i].second] << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
}

int main(){
    std::vector<match> matches = read_data("../input/2_2_input.txt");
    for (int i = 0; i < matches.size(); i++)
    {
        auto begin = std::chrono::high_resolution_clock::now();
        do_question(matches[i]);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Using time " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << std::endl;
        std::cout << std::endl;
    }
    return 0;
}