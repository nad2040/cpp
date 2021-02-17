#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

struct Family {
    bool hasGirl;
    int numChild;
    Family() : hasGirl(false), numChild(0) {}
    friend std::ostream& operator<<(std::ostream& os, const Family& f);
};

std::ostream& operator<<(std::ostream& os, const Family& f)
{
    os << f.hasGirl << ' ' << f.numChild;
    return os;
}

int main() {
    int numF = 1000000;

    // Generate and populate array

    std::vector<Family> families(numF);
    // for (auto& f : families)
    //     std::cout << f << std::endl;
    
    // Run simulation on each family

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0,3);
    for (int i=0; i<numF; ++i) {
        while (families[i].hasGirl == false) {
            int random = distribution(gen);
            families[i].numChild++;
            families[i].hasGirl = (random%2 == 1);
        }
    }

    //Count Boys and Girls
    int boys = 0;
    int girls = 0;
    for (int i=0; i<numF; ++i) {
        girls++;
        boys += families[i].numChild - 1;
    }
    
    std::cout << "Num girls = " << girls << "\nNum boys = " << boys << std::endl;

    const auto [min_it, max_it] = std::minmax_element(families.begin(), families.end(), [](const Family& f1, const Family& f2) { return f1.numChild < f2.numChild; });
    std::cout << "Min = " << *min_it << "\nMax = " << *max_it << std::endl;

    //int histogram[max] = {0};
    // for (auto& f:families) {
    //     histogram[f.numChild-1]++;
    // }
    // for (auto i : histogram) std::cout << i << " ";
    // std::cout << std::endl;
}