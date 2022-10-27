/**
 * @Author: liuxin
 * @Date:   2022-10-26 21:43:29
 * @Last Modified by:   liuxin
 * @Last Modified time: 2022-10-26 23:07:53
 */
#include <iostream>
#include <string>
using namespace std;

static int objectCount = 0;

class HowMany {
public:
    HowMany() {
        objectCount++;
        print("HowMany()");
    }

    HowMany(int i) {
        objectCount++;
        print("HowMany(int)");
    }

    HowMany(const HowMany& o) {
    // HowMany(HowMany o) {    
        objectCount++;
        print("HowMany(HM)");
    }
    
    void print(const string& msg = "") {
        if(msg.size() != 0) 
            cout << msg << ": ";
        cout << "objectCount = " << objectCount << endl;
    }
    
    ~HowMany() {
        objectCount--;
        print("~HowMany()");
    }
};

// During call by value, copy ctor called!!
HowMany f(HowMany x) {
    cout << "begin of f" << endl;
    x.print("x argument inside f()");
    cout << "end of f" << endl;

    // During function return, copy ctor called!!
    return x;
}

int main()
{
    HowMany h;
    h.print("after construction of h");
    // C++ builds a copy ctor for you if you don't provide one!
    // -Copies each member variable. Good for numbers, objects, arrays
    // -Copies each pointer. Data may become shared!
    HowMany h2 = f(h);
    // HowMany h2(10);
    // like a CString class can be initialized by a string
    // HowMany h2 = 10;
    // HowMany h2 = h;
    h.print("after call to f()");
}
