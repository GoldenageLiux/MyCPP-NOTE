/**
 * @Author: liuxin
 * @Date:   2022-11-13 13:50:07
 * @Last Modified by:   liuxin
 * @Last Modified time: 2022-11-13 13:52:29
 */
#include <iostream>
#include <string.h>

using namespace std;

class A{//虚函数示例代码
    public:
        virtual void fun()  {cout << 1 << endl;}
        virtual void fun2() {cout << 2 <<endl;}
};
class B : public A{
    public:
        void fun()  {cout << 3 << endl;}
        void fun2() {cout << 4 << endl;}
};

int main(int argc, char const *argv[])
{
    // 定义一个函数指针fun，而且有一个A*类型的参数，用来保存从vtbl里取出的函数地址。
    void(*fun)(A*);
    A *p = new B;
    long lVptrAddr;
    // 一个指针的长度是 8 bytes，把p所指的8bytes内存里的东西复制到lVptrAddr中，所以复制出来的8bytes内容就是vptr的值，即vtbl的地址
    memcpy(&lVptrAddr, p, 8);
    // 取出vtbl第一个slot里的内容，并存放在函数指针fun里。
    // 需要注意的是lVptrAddr里面是vtbl的地址，但lVptrAddr不是指针，所以我们要把它先转变成指针类型
    memcpy(&fun, reinterpret_cast<long*>(lVptrAddr) + 1, 8);
    fun(p);
    delete p;
//    system("pause");
    return 0;
}
