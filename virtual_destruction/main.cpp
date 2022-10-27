/**
 * @Author: liuxin
 * @Date:   2022-10-27 11:58:12
 * @Last Modified by:   liuxin
 * @Last Modified time: 2022-10-27 12:43:25
 */

//先初始化基类的构造函数，再初始化派生类的构造函数
//先调用派生类的析构函数释放派生类的资源，再调用基类的析构函数析构基类的资源
#include <iostream>

using namespace std;

class ClxBase{
public:
    int *a;
    ClxBase() {
        cout<<"Constructor from the class ClxBase!"<<endl;
        a = new int[100];
    };
    virtual ~ClxBase() {
        cout << "Output from the destructor of class ClxBase!" << endl;
        delete []a;
    };
    // ~ClxBase() {
    //     cout << "Output from the destructor of class ClxBase!" << endl;
    //     delete a;
    // };
    virtual void DoSomething() { cout << "Do something in class ClxBase!" << endl; };
};
 
class ClxDerived : public ClxBase{
public:
    int *a = new int[100];
    ClxDerived() {
        cout<<"Constructor from the class ClxDerived!"<<endl;
        
    };
    ~ClxDerived() { 
        cout << "Output from the destructor of class ClxDerived!" << endl; 
        delete []a;
    };
    void DoSomething() { cout << "Do something in class ClxDerived!" << endl; };
};
 
int main(){  
    ClxBase *p =  new ClxDerived;
    p->DoSomething();
    // 同时隐式的调用了ClxBase中的析构函数
    // 只有将基类的析构函数设置为虚函数时，才会同时调用派生类的析构函数
    // 为了防止出现内存泄漏，C++中基类的析构函数应采用virtual虚析构函数
    // 内存泄漏检测工具-> valgrind --tool=memcheck --leak-check=full
    delete p;
    return 0;
}