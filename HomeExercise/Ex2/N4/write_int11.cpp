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

#include<iomanip>
#include<format>

size_t extract_bit(int val, size_t index){
    // Shift to right, so that the bit i want is in the LSP,
    // then i apply a musk to extract the LSP bit.
    // equals 1 if the LSP is 1, equals 0 if the LSP is 0.
}


int main(int argc, char* argv[]){
    // We organize data so that we can write a byte at a time in memory.
    // We use a buffer of 8 bit.
    using namespace std;

    if(argc != 3){
        cout << "Error arguments.\n";
        return 1;
    }

    ifstream is(argv[1]);
    if (is.fail()) {
        cout << "Error opening input file.\n";
        return 1;
    }

    ofstream os(argv[2], ios::binary);
    if (os.fail()) {
        cout << "Error opening output file.\n";
        return 1;
    }

    std::vector<int32_t> v{
        std::istream_iterator<int32_t>(is),
        std::istream_iterator<int32_t>()
    };


    return 0;
}