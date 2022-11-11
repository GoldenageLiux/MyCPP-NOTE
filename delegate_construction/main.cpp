/**
 * @Author: liuxin
 * @Date:   2022-11-11 11:21:16
 * @Last Modified by:   liuxin
 * @Last Modified time: 2022-11-11 11:32:27
 */
#include <iostream>

using namespace std;

class base
{
protected:
    /* data */
    int a;
public:
    // base(){
        
    // }
    base(int a) {
        this->a = a;
    }
    ~base();
};

class child : public base {
private:
    int b;
public:
    // Subclass calls superclass constructor
    // delegate construcation
    child(int a, int b) : base(a) {
        this->b = b;
    }
    ~child();
    void child_print() {
        cout << this->a << " " << this->b << endl;
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    child *c = new child(1, 2);
    c->child_print();
    return 0;
}
