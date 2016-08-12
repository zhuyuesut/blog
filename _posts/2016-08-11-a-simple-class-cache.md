---

layout: post
title: "闲来无事写个Ｃache类来练习Ｃ＋＋"
author: Zhu Yue

---

代码如下： 

```cpp
/* cache.hpp */

#ifndef cache_hpp
#define cache_hpp

#include <iostream>

namespace zhuyuesut {
    template <typename ValueType>
    class Cache {
        ValueType value;
        
    public:
        Cache () = default;
        
        Cache (const ValueType& i) : value(i) {};
        
        Cache (ValueType&& i) : value(std::move(i)) {};
        
        template<typename FunctionType>
        Cache operator>> (FunctionType func) {
            return Cache(func(value));
        }
        
        std::ostream& operator>> (std::ostream &os) {
            return os << value;
        }
        
        Cache& operator<< (std::istream &is) {
            is >> value;
            return *this;
        }
        
        operator ValueType () {
            return value;
        }
    };
    
    class CacheConstruct {
    public:
        template<typename ValueType>
        Cache<ValueType> operator() (const ValueType& i) {
            return Cache<ValueType>(i);
        }
        
        template<typename ValueType>
        Cache<ValueType> operator() (ValueType&& i) {
            return Cache<ValueType>(std::move(i));
        }
    } make_cache;
}

#endif /* cache_hpp */
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