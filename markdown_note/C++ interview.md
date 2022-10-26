## C++ 11新特性

[1. Lambda表达式](### 1. Lambda表达式)

[2. 函数对象容器](###2. 函数对象容器)

[3. 右值引用](###3. 右值引用)

[4. 容器](###4. 容器)

[5. 对c++中的smart pointer四个智能指针的理解](###5. 对c++中的smart pointer四个智能指针的理解)

[6. 对虚函数和多态的理解](###6. 对虚函数和多态的理解)

### 1. Lambda表达式

Lambda 表达式的基本语法如下：

```c++
[捕获列表] (参数列表) mutable(可选) 异常属性-> 返回类型{
// 函数体
}
```

上面的语法规则除了[捕获列表] 内的东西外，其他部分都很好理解，只是一般函数的函数名被略去，返回值使用了一个-> 的形式进行（我们在上一节前面的尾返回类型已经提到过这种写法了）。
所谓捕获列表，其实可以理解为参数的一种类型，Lambda 表达式内部函数体在默认情况下是不能够使用函数体外部的变量的，这时候捕获列表可以起到传递外部数据的作用。根据传递的行为，捕获列表也分为以下几种：

1. 值捕获
2. 引用捕获
3. 隐式捕获
4. 表达式捕获
---

### 2. 函数对象容器 

#### std::function

C++11 `std::function`是一种通用、多态的函数封装。

它的实例可以对任何可以调用的目标实体进行存储、复制和调用操作，它也是对C++ 中现有的可调用实体的一种类型安全的包裹（相对来说，函数指针的调用不是类型安全的）。

换句话说，就是**函数的容器**。当我们有了函数的容器之后便能够更加方便的将函数、函数指针作为对象进行处理。

#### std::bind 和 std::placeholder

`std::bind`则是用来绑定函数调用的参数的，它解决的需求是我们有时候可能并不一定能够一次性获得调用某个函数的全部参数，通过这个函数，我们可以将部分调用参数提前绑定到函数身上成为一个新的对象，然后在参数齐全后，完成调用。

```C++
int foo(int a，int b，int c) {
	;
}
int main() {
    // 将参数1，2 绑定到函数foo 上，但是使用std::placeholders::_1 来对第一个参数进行占位
    auto bindFoo = std::bind(foo，std::placeholders::_1，1，2);
    // 这时调用bindFoo 时，只需要提供第一个参数即可
	bindFoo(1);
}
```

---

### 3. 右值引用

#### std::move 移动构造函数

在C++11中，标准库在中提供了一个有用的函数`std::move`，`std::move`并不能移动任何东西，它唯一的功能是将一个左值引用强制转化为右值引用，继而可以通过右值引用使用该值，以用于移动语义。从实现上讲，`std::move`基本等同于一个类型转换： `static_cast<T&&>(Ivalue)`；

使用前提：1 定义的类使用了资源并定义了移动构造函数和移动赋值运算符，2 该变量即将不再使用

`std::move`语句可以将左值变为右值而**避免拷贝构造**。
`std::move`是将对象的状态或者所有权从一个对象转移到另一个对象，只是转移，没有内存的搬迁或者内存拷贝。

#### std::forward 完美转发

所谓完美转发，就是为了让我们在传递参数的时候，保持原来的参数类型（左引用保持左引用，右引用保持右引用）。为了解决这个问题，我们应该使用`std::forward`来进行参数的转发（传递）。

---

### 4. 容器

#### **无序容器**

C++11 引入了两组无序容器：

`std::unordered_map`/`std::unordered_multimap`和 `std::unordered_set`/`std::unordered_multiset`。

无序容器中的元素是不进行排序的，内部通过 Hash 表实现，插入和搜索元素的平均复杂度为 O(constant)。

#### **元组 std::tuple**

元组的使用有三个核心的函数：

- `std::make_tuple`: 构造元组
- `std::get`: 获得元组某个位置的值
- `std::tie`: 元组拆包

---

### 5. 对c++中的smart pointer四个智能指针的理解

C + + 里面的四个智能指针：`auto_ptr`，`shared_ptr`，`unique_ptr`，`weak_ptr`。其中后三个是c + +11支持，并且第一个已经被11弃用。

智能指针的作用是管理一个指针，因为存在以下这种情况：申请的空间在函数结束时忘记释放，造成内存泄漏。使用智能指针可以很大程度上的避免这个问题，因为智能指针就是一个类，当超出了类的作用域时，类会自动调用析构函数，析构函数会自动释放资源。所以智能指针的作用原理就是在函数结束时自动释放内存空间，不需要手
动释放内存空间。

- **unique_ptr **实现独占式拥有或严格拥有概念，保证同一时间内只有一个智能指针可以指向该对象。它对于避免资源泄露( 例如“ 以new创建对象后因为发生异常而忘记调用delete” ) 特别有用。

- **shared_ptr **实现共享式拥有概念。多个智能指针可以指向相同对象，该对象和其相关资源会在“ 最后一个引用被销毁” 时候释放。从名字share就可以看出了资源可以被多个指针共享，它使用计数机制来表明资源被几个指针共享。可以通过成员函数use_count( )来查看资源的所有者个数。除了可以通过new来构造，还可以通过传入auto_ ptr，unique_ptr，weak_ptr来构造。当我们调用release( ) 时，当前指针会释放资源所有权，计数减一。当计数等于0 时，资源会被释放。
  shared_ptr是为了解决auto_ptr 在对象所有权上的局限性(auto_ptr是独占的) ，在使用引用计数的机制上提供了可以共享所有权的智能指针。
  
- **weak_ptr **是一种不控制对象生命周期的智能指针，它指向一个shared_ptr管理的对象. 进行该对象的内存管理的是那个强引用的shared_ptr。weak_ptr只是提供了对管理对象的一个访问手段。weak_ptr设计的目的是为配合 shared_ptr而引入的一种智能指针来协助 shared_ptr工作，它只可以从一个 shared_ptr或另一个 weak_ptr 对象构造，它的构造和析构不会引起引用记数的增加或减少。
  weak_ptr是用来解决shared_ptr相互引用时的死锁问题，如果说两个shared_ptr相互引用，那么这两个指针的引用计数永远不可能下降为0 ，资源永远不会释放。它是对对象的一种弱引用，不会增加对象的引用计数，和shared_ptr之间可以相互转化，shared_ptr可以直接赋值给它，它可以通过调用lock函数来获得shared_ptr。
  
---

### 6. 对虚函数和多态的理解

多态的实现主要分为静态多态和动态多态，**静态多态主要是重载**，在编译的时候就已经确定；动态多态是用**虚函数机制**实现的，在运行期间动态绑定。

举个例子：一个父类类型的指针指向一个子类对象时候，使用父类的指针去调用子类中重写了的父类中的虚函数的时候，会调用子类重写过后的函数，在父类中声明为加了`virtual`关键字的函数，在子类中重写时候不需要加`virtual`也是虚函数。

**虚函数的实现**：在有虚函数的类中，类的最开始部分是一个虚函数表的指针，这个指针指向一个虚函数表，表中放了虚函数的地址，实际的虚函数在代码段`(.text)` 中。
当子类继承了父类的时候也会继承其虚函数表，当子类重写父类中虚函数时候，会将其继承到的虚函数表中的地址替换为重新写的函数地址。使用了虚函数，会增加访问内存开销，降低效率。

---

### 7. 面向对象

#### 委托构造

#### 继承构造

#### 显示虚函数承载

- override
- final

#### 显式禁用默认函数

#### 强类型枚举