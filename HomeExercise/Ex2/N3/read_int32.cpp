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

template<typename T>
T& raw_read(std::istream &is, size_t size = sizeof(T)){
    T val;
    is.read(reinterpret_cast<char*>(&val), size);
    return val;
}

int main(int argc, char *argv[]) {
    using namespace std;

    if(argc != 3){
        cout << "Error arguments.\n";
        return 1;
    }

    ifstream is(argv[1], ios::binary);
    if (is.fail()) {
        cout << "Error opening input file.\n";
        return 1;
    }

    ofstream os(argv[2]);
    if (os.fail()) {
        cout << "Error opening output file.\n";
        return 1;
    }


    while(1){
        int32_t num = raw_read<int32_t>(is);

        if(is.good()){
            os << num << '\n';
        }
        else if (is.eof()){
            cout << "End of input file reached.\n";
            break;
        }
        else{
            cout << "Error input file formatt.\n";
            break;
        }
    }



    return 0;
}