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

    // map like Java, int is a key (element), uint32_t is data (count).
    // Hash table.
    unordered_map<int, uint32_t> count;

    // Ordrdered map.
    // map<int, uint32_t> count;

    // array<uint32_t, 256> count; // Sistema più veloce che c'è.

    // set arrange element in a binary tree.
    // unordered set doesnt order element.

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