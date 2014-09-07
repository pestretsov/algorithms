#include <map>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef std::pair<long, long> xy;

long TwoSum(map<long, int>& m, long t) {
    for (auto& x : m) {
        long y = t-(x.first);
        if (m[y])
            return x.first+y;
    }
    return 0;
}

int main() {
    fstream f("2sum.txt");
    map<long, int> m;
    string str;
    long t = -10000;
    long stop = 10000;
    map<long, int> res;
    int count = 0;

    while(getline(f, str))
        m[stol(str)]++;

    while (t <= stop) {
         res[TwoSum(m, t)]++;
         count = res.size();
         cout << count <<"\n";
         t++;
    }
    cout << "\nResult:" << count << endl;
    //cout << m.size();
    return 0;
}
