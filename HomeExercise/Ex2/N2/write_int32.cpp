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
std::ostream& raw_write(std::ostream &os, const T& val, size_t size = sizeof(T)){
    return os.write(reinterpret_cast<const char*>(&val), size);
}

int main(int argc, char *argv[]) {
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

    ofstream os(argv[2], ios::binary);  // In MacOS you dont have to do this,
                                        // but if you run it on windows whitout this
                                        // it brake (every time you write 10 windows add 13).
                                        // In binary mode this doesn't happen.
    if (os.fail()) {
        cout << "Error opening output file.\n";
        return 1;
    }

    // int x{ 5 }; // Uniform initialization.

    // The most vexing parse.
    // This is a definition of a prototype function, it's not calling v passing start and stop
    // iterator of the is stream.
    /*
    std::vector<int32_t> v(
        std::istream_iterator<int32_t>(is),
        std::istream_iterator<int32_t>()
    );
    */
    // That why we are going to use '{}', so that the compiler cant misundestand.
    /*
    std::vector<int32_t> v{
        std::istream_iterator<int32_t>(is),
        std::istream_iterator<int32_t>()
    };
    */

    while(1){
        int32_t num;
        is >> num;


        /*
        int a = 7;
        double b = a / 10; // b = 0, division with decimal.
        double b = (double) a / 10; // b = 0.7, C version.
        double b = static_cast<double>(a) / 10; // CPP Version.
                                                // static_cast produce a variable cast.
                                                // with static cast you cant change
                                                // pointer type.

        const char s[] = "Prova";
        const char *p = s;          // OK.
        //char *q = s;              // NOT OK, beacuse q it's not const.
        //char *q = static_cast<char*>(s);  // NOT OK, Static cast cant remove const.
                                            // this protect cast that should not be done.
        */

        if(is.good()){
            //char *qx = reinterpret_cast<char*>(&num);   // It can be used insetad of C cast
                                                        // when static_cast doesnt let you
                                                        // cast, but you need to be carefull.
            // os.write((const char*) &num, 4);        // Casting pointer type must be explicit.

            raw_write(os, num);    // Template deduction, he get the type by
                                            // the parameter passed.


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