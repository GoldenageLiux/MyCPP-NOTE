std::bind和std::function配合使用非常的强大

```c++
std::function<void(Socket *)> cb = std::bind(&Server::NewConnection, this, std::placeholders::_1);
std::function<void()> sub_loop = std::bind(&EventLoop::Loop, sub_reactors_[i]);
//绑定类的成员函数时，需要把对象指针(sub_reactors_[i])传进去，成员函数编译器在使用时会自动传入一个this指针，所以在绑定时需要额外传一个对象的地址
```