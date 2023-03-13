#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>

#include <util.h>
#include <iostream>

#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>

#include<iomanip> // Library used to manipulate output.
#include<format> // Lib for more advaced output manipulation.

// Now CountT have a default, 'uint32_t'.
template<typename T, typename CountT = uint32_t>
struct freq {
    std::unordered_map<T, CountT> count_;

    // un oggetto che si comporta come funzione di chaima functon,
    // ovvimanete hanno anche uno stanto interno invece delle funzioni.
    void operator()(const T &val){
        ++count_[val];
    }

    auto begin(){ return count_.begin(); }
    auto end(){ return count_.end(); }

    auto cbegin() const { return count_.begin(); }  // La count_.cbegin() ritorna una const.
                                                    // con 'const' all'inizio la forziamo.
    auto cend(){ return count_.end(); }
};

int main(int argc, char *argv[]) {
    using namespace std;

    if(argc != 3){
        std::cout << "Error arguments.\n";
        return 1;
    }

    ifstream is(argv[1], ios::binary);      // Binary file read.
    if (is.fail()) {
        std::cout << "Error opening input file.\n";
        return 1;
    }

    ofstream os(argv[2]);
    if (os.fail()) {
        std::cout << "Error opening output file.\n";
        return 1;
    }

    freq<int> count;

    while(1){
        int val;
        val = is.get(); // C style, it return -1 if fails.

        if (val == EOF){
            cout << "EOF reached.\n";
            break;
        }

        ++count[val]; // If we cant find val, a instance is created.
    }
    
    for (const auto &e : count){
        os << hex << setw(2) << setfill('0') << uppercase << e.first;
        os << '\t' << setbase(10) << e.second << '\n';
    }



    return 0;
}