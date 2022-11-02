/**
 * @Author: liuxin
 * @Date:   2022-11-02 14:42:19
 * @Last Modified by:   liuxin
 * @Last Modified time: 2022-11-02 15:08:31
 */
#include <iostream>
#include "test.h"
using namespace std;

int main(int argc, char const *argv[])
{
    Test *test = new Test();

    // if(test->getFirst()) {
    //     cout << "first_callback had not been set!" << endl;
    // }

    std::cout << "first_callback is " << (test->getFirst() ? "not empty" : "empty") << ".\n";
    test->OnFirst(
        []() {
            std::cout << "OnFirst is called!" << std::endl;
        }
    );

    test->doFirst();
    
    // if(test->getSecond()) {
    //     cout << "second_callback had not been set!" << endl;
    // }
    std::cout << "second_callback is " << (test->getSecond() ? "not empty" : "empty") << ".\n";
    
    test->OnSecond(
        []() {
            std::cout << "OnSecond is called!" << std::endl;
        }
    );

    test->doSecond();

    return 0;
}
