#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <fstream>

using std::vector;
using std::cout;
using std::set;
using std::string;
using std::fstream;

void TwoSum(vector<long>& v, set<long>& t, int val, long half_range) {
    long i = v[val];

    long begin = -half_range-i;
    long end = half_range-i;

    // decrement to make upper_bound less or equal to stop value 
    auto jmax = --upper_bound(v.begin(), v.end(), end);
    auto jmin = lower_bound(v.begin(), v.end(), begin);

    for (auto j = jmax; j >= jmin; --j) {
        t.insert(i + *j);
    }
}

int main() {
    fstream f("/Users/artemypestretsov/Downloads/2sum.txt");
    string str;
    vector<long> v;
    set<long> tmp;
    set<long> t;

    while(getline(f, str))
        tmp.insert(stol(str));

    for (auto i : tmp) {
        v.push_back(i);
    }

    std::sort(v.begin(),v.end());

    //for (auto& i : v)
    //    cout << i << " ";
    //cout << "\n\n";


    //auto up = upper(v, start, stop);


    for (int i = 0; i < v.size(); ++i) {
        TwoSum(v, t, i, 10000);
    }

    //for (auto& i : t)
    //    cout << i << " ";
    //cout << "\n\n";

    cout << "\nResult: "<< t.size() << "\n";
    //cout << "[" << start << ";" << stop << "]" <<"\n";
    //cout << "[" << *low << ";" <<*up << "]" <<"\n";

    return 0;
}
