/**
 * @Author: liuxin
 * @Date:   2022-11-07 16:37:10
 * @Last Modified by:   liuxin
 * @Last Modified time: 2022-11-07 22:02:44
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

void pass_up1(int& value) {
    cout << "In pass_up1: " << value << endl;
}

void pass_up2(int* up) {
    cout << "In pass_up2: " << *up << endl;
}

void pass_up3(unique_ptr<int>& up) {
    cout << "In pass_up3: " << *up << endl;
    up.reset();
}

void pass_up4(unique_ptr<int> up) {
    cout << "In pass_up4: " << *up << endl;
}

unique_ptr<int> return_uptr(int value) {
    unique_ptr<int> up = make_unique<int>(value);
    // NRVO
    // The compiler automatically uses the move construction/ rvalue
    // return up;
    return std::move(up);
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

    auto up = make_unique<int>(123);
    // pass_up1(*up);
    // pass_up2(up.get());
    // pass_up3(up);
    // if (up == nullptr) cout << "up is reset." << endl;
    pass_up4(std::move(up));
    if (up == nullptr) cout << "up is moved." << endl;

    unique_ptr<int> up2 = return_uptr(456);
    cout << "up2 is " << *up2 << endl;
    
    return 0;
}
