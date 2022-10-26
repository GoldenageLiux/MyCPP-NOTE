# Race condition和线程安全

## Race condition

从定义来说，race condition是代码中一些执行结果取决于其执行的相对时间或者多线程交错执行的判断条件。它的结果是不可预测的。如何一个程序中不存在race condition，那么它就是[线程安全](https://so.csdn.net/so/search?q=线程安全&spm=1001.2101.3001.7020)的（thread-safe）。

## 如何检测race condition

race condition通常很难重现，定位和排除，因为问题发生依赖于特定的场景。即使写一个多线程的单元也不可以保证程序的100%的正确定，但有一些方法可以排除race condition。

## 如何避免race condition

### 1.避免使用共享变量

在多线程环境中，race condtion的出现往往伴随着共享变量，如上面例子中的账户余额和count变量，都可以被多个线程读取操作，那么避免问题发生最简单直接的办法就是避免使用共享变量。可以使用不可变对象或者线程本地对象（例如java中的threadlocal）。

### 2.使用同步或者原子操作

使用同步可以避免race condition的问题，但是线程同步往往伴随很多同步的性能开销，还可能导致死锁。两个办法是使用原子操作，例如java中的提供的原子类。