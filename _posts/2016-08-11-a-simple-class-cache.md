---

layout: post
title: "闲来无事写个Ｃache类来练习Ｃ＋＋"
author: Zhu Yue

---

代码如下： 

```cpp
/* cache.hpp */

#include <iostream>

namespace zhuyuesut {
    template <class T> class Cache {
        T t;
    public:
        Cache() = default;
        Cache(const T &i) : t(i) {};
        template<class M> Cache<T> operator>>(M f) {
            return Cache<T>(f(t));
        }
        std::ostream &operator>>(std::ostream &os) {
            return os << t;
        }
        Cache<T> &operator<<(std::istream &is) {
            is >> t;
            return *this;
        }
        operator T() {
            return t;
        }
    };
    class CacheConstruct {
    public:
        template<class T> Cache<T> operator()(const T &i) {
            return Cache<T>(i);
        }
    } make_cache;
}
```
```cpp
/* test_cache.cpp */

#include "stdc++.h"
#include "cache.hpp"

using namespace std;
using namespace zhuyuesut;


int main(int argc, const char * argv[]) {

    cout << "Result is ";
    make_cache(1) >> [](auto i){return i*6;} >> [](auto i){return i*7;} >> cout << '.' << endl;
    
    cout << "What's is you name? ";
    Cache<string>() << cin >> [](auto i){return "Hello, " + i + "!";} >> cout << endl;
    
    return 0;
}
```
测试结果如下 

```
Result is 42.
What's is you name? ZhuYue
Hello, ZhuYue!
Program ended with exit code: 0
```