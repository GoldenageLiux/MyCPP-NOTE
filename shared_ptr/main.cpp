/**
 * @Author: liuxin
 * @Date:   2022-11-05 10:31:54
 * @Last Modified by:   liuxin
 * @Last Modified time: 2022-11-05 17:32:08
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

void func1() {
    // dangling pointer 悬垂指针
    int *p = new int;  
    delete p;       /* p now becomes a dangling pointer */
    p = nullptr;    /* p is no longer dangling, and nullptr is tpye-safe*/

    if (p != nullptr)   {
        cout << *p << endl;
    }
}

void func2() {
    // wild pointer 野指针
    int *p;     /* now p is a wild pointer*/
    // int *p = nullptr;   /* method of resolution*/
}

void foo(int x) {
    int y = x * 2;
    int *p = new int[5];
    p[0] = y;
    delete[] p;     
    /*if we don`t add this delete[] p, p disappeared when foo() quit, but the memory area pointed to by p is still dangling*/
    /* This phenomenon is called a memory leak*/
}

void func3() {
    shared_ptr<Ball> p = make_shared<Ball>(3);
    // Ball* rp = p.get();
    // cout << p.use_count() << endl;
    // shared_ptr<Ball> p2 = p;
    // cout << p.use_count() << " " << p2.use_count() << endl;
    // shared_ptr<Ball> p3 = p;
    // cout << p.use_count() << " " << p2.use_count() << " " << p3.use_count() << endl;
    // p.reset();
    cout << p.use_count() << endl;
    p.reset(new Ball(5));
    // Ball* rp = p.get();
    // rp->Bounce();
    // p2.reset();
    // p3.reset();
}

void close_file(FILE* fp) {
    if (fp == nullptr) return;
    fclose(fp);
    cout << "File closed." << endl;
}

int main(int argc, char const *argv[])
{
    FILE* fp = fopen("data.txt", "w");
    /*when the use_count() of sfp is 0, the close_file() is called.*/
    shared_ptr<FILE> sfp {fp, close_file};
    if (sfp == nullptr) {
        cerr << "Error opening file" << endl;
    }
    else cout << "File opened." << endl;
    func3();
    shared_ptr<int> sp {new int(5)};
    shared_ptr<int> sp2 = sp;
    // delete sp.get(); // the operation should be banned!
    cout << "Continued " << *sp2 << endl;
    return 0;
}
