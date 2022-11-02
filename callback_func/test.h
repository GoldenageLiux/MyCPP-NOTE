/**
 * @Author: liuxin
 * @Date:   2022-11-02 14:42:48
 * @Last Modified by:   liuxin
 * @Last Modified time: 2022-11-02 15:00:09
 */
#include <stdint.h>
#include <functional>

#ifndef __TEST_H__
#define __TEST_H__

class Test
{
private:
    /* data */
    std::function<void()> on_first_callback_;
    std::function<void()> on_second_callback_;

public:
    Test(/* args */);
    ~Test();

    void OnFirst(std::function<void()> fn);
    void OnSecond(std::function<void()> fn);

    void doFirst();
    void doSecond();

    std::function<void()> getFirst();
    std::function<void()> getSecond();
    
    
};

Test::Test(/* args */)
{

}

Test::~Test()
{

}

void Test::OnFirst(std::function<void()> fn) {
    on_first_callback_ = std::move(fn);
}

void Test::OnSecond(std::function<void()> fn) {
    on_second_callback_ = std::move(fn);
}

void Test::doFirst() {
    on_first_callback_();
}

void Test::doSecond() {
    on_second_callback_();
}

std::function<void()> Test::getFirst() {
    return this->on_first_callback_;
}

std::function<void()> Test::getSecond() {
    return this->on_second_callback_;
}


#endif /* __TEST_H__ */
