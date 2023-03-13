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

size_t count_element(char *argv[], int val){
    using namespace std;
    size_t count = 0;
    ifstream is(argv[1], ios::binary);

    while(1){
        int tmp;
        tmp = is.get();

        if (tmp == EOF){
            break;
        }

        if (tmp == val){
            count++;
        }
    }

    return count;
}

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

    vector<int> element_checked;

    while(1){
        int val;
        val = is.get(); // C style, it return -1 if fails.

        if (val == EOF){
            cout << "EOF reached.\n";
            break;
        }

        if(std::count(element_checked.begin(), element_checked.end(), val) == 0){
            // The element is not present.
            size_t count = count_element(argv, val);
            // setbase() set the number base, it keep set like this in the stream,
            // so you need to change is back after.
            // setw() set dimension, setfill() set what char to insert to fill.
            // uppercase to set output uppercase.
            /*
            os << setbase(16) << setw(2) << setfill('0') << uppercase << val;
            os << '\t' << setbase(10) << count << '\n';
            */

            // Alt version
            os << hex << setw(2) << setfill('0') << uppercase << val;
            os << '\t' << setbase(10) << count << '\n';
            element_checked.push_back(val);

            // Format Python style, only CPP v.20 and after.
            // os << format("{}\t{}\n", val, count);

        }
    }
    



    return 0;
}