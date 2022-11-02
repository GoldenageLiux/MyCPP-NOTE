/**
 * @Author: liuxin
 * @Date:   2022-11-02 14:10:59
 * @Last Modified by:   liuxin
 * @Last Modified time: 2022-11-02 14:35:41
 */
#include <iostream>
#include <functional>
#include <typeinfo> 

class NativeWindow {
public:
    typedef std::function<void(int)> KeyFunc;
    void set_key_callback(KeyFunc func) {
        m_key_callback = func;
    }
    void run() {
        if (m_key_callback) {
            m_key_callback(42);
        }
    }
private:
    KeyFunc m_key_callback;
};

class MyWindow {
public:
    MyWindow() {
        m_window = new NativeWindow();
        // m_window->set_key_callback([this](int key) {
        //     this->on_key(key);
        // });
        // OK: capturing lambda to std::function

        m_window->set_key_callback(std::bind(&MyWindow::on_key, this, std::placeholders::_1));

        std::cout << "MyWindow() ctor is called! " << std::endl;
        // OK: works, but not as clear as capturing lambda
    }
    ~MyWindow() {
        std::cout << "MyWindow() dtor is called! " << std::endl;
        delete m_window;
    }
    void run() {
        m_window->run();
    }
    void on_key(int key) {
        std::cout << typeid(this).name() << " key: " << key << "\n";
    }

private:
    NativeWindow *m_window;
};


int main() {
    MyWindow *my_window = new MyWindow();
    // MyWindow my_window;
    my_window->run();
    // delete my_window;
    return 0;
}
