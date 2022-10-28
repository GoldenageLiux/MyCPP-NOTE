/**
 * @Author: liuxin
 * @Date:   2022-10-28 21:28:24
 * @Last Modified by:   liuxin
 * @Last Modified time: 2022-10-28 21:28:28
 */
#include <stdio.h>
#include <iostream>
using namespace std;

extern int test;
class A
{
private:
    //静态成员变量, 在类中的是声明, 要在类外进行定义
	static int _count;  
public:
	A(){   //构造函数
		_count++;
	}
	A(const A& y){   //拷贝构造函数
		_count++;
	}

	static int GetCount() {    //静态成员函数
    // int GetCount() {  // 非静态成员引用必须与特定对象相对
		return _count;
	}
    // 1. 静态成员函数没有隐藏的 this 指针，不能访问非静态成员（变量、 函数）！
    // 因为静态成员函数没有隐藏的 this 指针所以也不能定义成const成员函数 const 本质就是修饰隐藏参数 this
    // 2. 静态成员函数不能调用非静态成员函数
    // 3. 非静态成员函数可以调用静态成员函数
public:      
	int a;
	static int value;
	static const int sa = 99;
	const static int sb;
	static const int sc;
};

int A::_count = 0;   //静态变量 _count 定义
const int A::sb = 88;
const int A::sc = 77;

void TestA() {
	cout << "A::GetCount() = " << A::GetCount() << endl;  // 类静态成员通过 类名::静态成员 来访问
	A a1, a2; 
	A a3(a1);
    // 静态成员变量的访问-> 类名::静态成员变量名 或 对象.静态成员变量名
	cout << "A::GetCount() = " << A::GetCount() << endl;
    cout << "A::GetCount() = " << a3.GetCount() << endl;
    cout << "A::sa() = " << a3.sa << endl;
    cout << "A::sb() = " << a3.sb << endl;
    // 静态成员变量为所有类对象所共享, 并没有包含在具体的对象中, 所以并不影响 sizeof() 大小
    cout << "sizeof(a1) = " << sizeof(a1) << endl;
}


void fun()
{
    // 当 static 修饰局部变量时
    // 变量的存储区域由栈变为静态常量区
    // 变量的生命周期由局部变为全局
    // 变量的作用域不变
	static int val = 0; 
	val++;
	printf("%d\n", val);
}

int value = 5;
// 静态变量默认初始化值为0
int A::value;
// 全局变量如果没有显示初始化, 会默认初始化为 0, 
// 或者显示初始化为 0 , 则保存在程序的 BSS 段, 如果初始化不为 0 则保存在程序的 DATA 段.
// BSS段通常是指用来存放程序中未初始化的或者初始化为0的全局变量和静态变量的一块内存区域;
// 特点是可读写的, 在程序执行之前BSS段会自动清0

int main()
{
	for (int i = 0; i < 7; i++){
		fun();
	}
    cout << "test.c->test = " << test << endl;
    TestA();

    int value = 10;
    A::value++;
    value++;
    cout << ::value << ", " << A::value << ", " << value << endl;
	return 0;
}
