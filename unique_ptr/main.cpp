/**
 * @Author: liuxin
 * @Date:   2022-11-07 16:37:10
 * @Last Modified by:   liuxin
 * @Last Modified time: 2022-11-07 20:19:10
 */
#include <iostream>
#include <memory>
using namespace std;

class Ball
{
private:
    /* data */
    int x;
public:
    Ball(int x){
        this->x = x;
        cout << "A ball named " << this->x << " appears."  << endl;
    }
    ~Ball() {
        cout << "A ball named " << this->x << " disappears."  << endl;
    }
    void Bounce() {
        cout << "A ball jump." << endl;
    }
};

void func() {
    cout << "Now in func." << endl;
    unique_ptr<Ball> up {make_unique<Ball>(1)};
    up->Bounce();
    cout << "Before quiting func." << endl;

    // we can`t cpoy the Control, but can move the Control
    unique_ptr<Ball> up2(up.release());
    // unique_ptr<Ball> up2 = move(up);
    up2->Bounce();
}

int* my_alloc(int v) {
    cout << "Allocating " << v << endl;
    return new int{v};
}

void my_dealloc(int *p) {
    cout << "Deallocating " << *p << endl;
    delete p;
}

int main(int argc, char const *argv[])
{
    cout << "Now in main." << endl;
    func();
    cout << "End Executing func." << endl;

    // Now in main.
    // Now in func.
    // A ball named 1 appears.
    // A ball jump.
    // Before quiting func.
    // A ball jump.
    // A ball named 1 disappears.
    // End Executing func.

    // initial by {}
    int *a = new int{5};
    int *b = new int[5];
    
    cout << "*a = " << *a << endl;  //print 5
    cout << "*b = " << *b << endl;  //print 0
    
    // The unique_ptr binding release function is at compile time
    // The shared_ptr binding release function is at running time
    unique_ptr<int, decltype(&my_dealloc)> cup {my_alloc(100), my_dealloc};
    return 0;
}
