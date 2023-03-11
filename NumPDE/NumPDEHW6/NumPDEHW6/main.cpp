#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>

using namespace std;


class Solver_FTBS{
public:
    double dx;
    double dt;
    int nx;
    int nt;
    vector<double> u_last;
    vector<double> u_this;
    vector<double> x_value;
public:
    Solver_FTBS(std::pair<double,double> x, std::pair<double,double> d, double t, std::function<double(double)> f)
        : dx(d.first), dt(d.second)
    {
        double x_l = x.first;
        double x_r = x.second;
        nx = (x_r - x_l) / dx; 
        nt = t / dt;
        double x_b = x_l - dx * nt;
        for (int i = 0; i < nx+nt+1; i++)
            u_last.push_back(f(x_b + i * dx));
        for (int i = 0; i < nx+1; i++)
            x_value.push_back(x_l + i * dx); 
    };
  std::pair<std::vector<double>, std::vector<double>> solve(){
        for (int i = 0; i < nt; i++)
        {
            u_this = vector<double>();
            for (int j = 0; j< u_last.size() - 1; j++)
                u_this.push_back(u_last[j+1]+dt/dx*(u_last[j+1]-u_last[j]));
           u_last = u_this; 
        } 
        return {x_value, u_this};
    }
    ~Solver_FTBS(){};
};

class Solver_FTCS{
public:
    double dx;
    double dt;
    int nx;
    int nt;
    vector<double> u_last;
    vector<double> u_this;
    vector<double> x_value;
public:
    Solver_FTCS(std::pair<double,double> x, std::pair<double,double> d, double t, std::function<double(double)> f)
        : dx(d.first), dt(d.second)
    {
        double x_l = x.first;
        double x_r = x.second;
        nx = (x_r - x_l) / dx; 
        nt = t / dt;
        double x_b = x_l - dx * nt;
        for (int i = 0; i < nx+2*nt+1; i++)
            u_last.push_back(f(x_b + i * dx));
        for (int i = 0; i < nx+1; i++)
            x_value.push_back(x_l + i * dx); 
    };
  std::pair<std::vector<double>, std::vector<double>> solve(){
        for (int i = 0; i < nt; i++)
        {
            u_this = vector<double>();
            for (int j = 0; j< u_last.size() - 2; j++)
                u_this.push_back(u_last[j+1]+dt/dx*(u_last[j+2]-u_last[j])/2.);
           u_last = u_this; 
        } 
        return {x_value, u_this};
    }
    ~Solver_FTCS(){};
};

class Solver_LaxW{
public:
    double dx;
    double dt;
    int nx;
    int nt;
    vector<double> u_last;
    vector<double> u_this;
    vector<double> x_value;
public:
    Solver_LaxW(std::pair<double,double> x, std::pair<double,double> d, double t, std::function<double(double)> f)
        : dx(d.first), dt(d.second)
    {
        double x_l = x.first;
        double x_r = x.second;
        nx = (x_r - x_l) / dx; 
        nt = t / dt;
        double x_b = x_l - dx * nt;
        for (int i = 0; i < nx+2*nt+1; i++)
            u_last.push_back(f(x_b + i * dx));
        for (int i = 0; i < nx+1; i++)
            x_value.push_back(x_l + i * dx); 
    };
  std::pair<std::vector<double>, std::vector<double>> solve(){
        for (int i = 0; i < nt; i++)
        {
            u_this = vector<double>();
            for (int j = 0; j< u_last.size() - 2; j++)
                u_this.push_back(u_last[j+1]+dt/dx*(u_last[j+2]-u_last[j])/2.+dt*dt/2. * (u_last[j+2]+u_last[j]-2*u_last[j+1]) /(dx*dx) );
           u_last = u_this; 
        } 
        return {x_value, u_this};
    }
    ~Solver_LaxW(){};
};

double f(double x){
    // return x;
    if (x >= 0.4 && x <= 0.6)
        return 1;
    return 0;
}

void print(std::pair<std::vector<double>, std::vector<double>> x){
    std::cout << std::endl;
    for (int i = 0; i < x.first.size(); i++)
    {
        std::cout << x.first[i] << "\t" ; 
    }
    std::cout << std::endl;
    for (int i = 0; i < x.second.size(); i++)
    {
        std::cout << x.second[i] << "\t";
    }
    std::cout << std::endl;
     
}

void save(std::ofstream& file,std::pair<std::vector<double>, std::vector<double>> x, std::string words, int order_){
    file << "#" << words << std::endl;
    file << "x" << order_ << " = [";
    for (int i = 0; i < x.first.size(); i++)
    {
        file << x.first[i] << "," ; 
    }
    file << "]" << std::endl;
    file << "fx" << order_ << " = [";
    for (int i = 0; i < x.second.size(); i++)
    {
        file << x.second[i] << ",";
    }
    file << "]" << std::endl;
    file << std::endl;
     
}

int main(int argc, const char * argv[]) {
    // Solver_XXX a({x_l, x_r}, {dx, dt}, t, f)
    double x_l = -1, x_r = 1;
    Solver_FTCS a({x_l, x_r}, {0.2, 0.1}, 1, f);
    Solver_FTBS b({x_l, x_r}, {0.2, 0.1}, 1, f);
    auto x = a.solve();
    std::vector<double> t = {0.05, 0.2, 0.8, 3.2};
    int order = 0;


    order = 0;
    std::ofstream data_FTBS("FTBS.py"); 
    for (auto t : {0.05, 0.2, 0.8, 3.2}) for (auto dt : {0.01, 0.04})
    {
        double dx = 0.05;
        double x_l = 0;
        double x_r = 4;
        Solver_FTBS x({x_l, x_r}, {dx, dt}, t, f);
        save(data_FTBS, x.solve(), "t:"+std::to_string(t)+",dt:"+std::to_string(dt), order++);
    }
    data_FTBS.close();
    
    order = 0;
    std::ofstream data_FTCS("FTCS.py"); 
    for (auto t : {0.05, 0.2, 0.8, 3.2}) for (auto dt : {0.01, 0.04})
    {
        double dx = 0.05;
        double x_l = 0;
        double x_r = 4;
        Solver_FTCS x({x_l, x_r}, {dx, dt}, t, f);
        save(data_FTCS, x.solve(), "t:"+std::to_string(t)+",dt:"+std::to_string(dt), order++);
    }
    data_FTCS.close();
     
    order = 0;
    std::ofstream data_LaxW("LaxW.py"); 
    for (auto t : {0.05, 0.2, 0.8, 3.2}) for (auto dt : {0.01, 0.04})
    {
        double dx = 0.05;
        double x_l = 0;
        double x_r = 4;
        Solver_LaxW x({x_l, x_r}, {dx, dt}, t, f);
        save(data_LaxW, x.solve(), "t:"+std::to_string(t)+",dt:"+std::to_string(dt),order++);
    }
    data_LaxW.close();   
    return 0;
}