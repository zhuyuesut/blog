---
layout: post
title: Class Time
author: Zhu Yue
categories: other
---

```c++
#include<iostream>
using namespace std;

class Time
{
public:
    Time():hour(0),minute(0),second(0){}
    
    void set(int h=0,int m=0,int s=0){
		hour=h%24;
		minute=m%60;
		second=s%60;
	}
    
	void display(int n=12){
		cout<<(n==12&&hour>12?hour-12:hour)
            <<':'<<minute<<':'<<second
            <<(n==12?(hour>11?"PM":"AM"):"")
			<<endl;
	}
private:
    int hour,minute,second;
};

int main()
{
	Time now;
	now.display();
	now.set(15,45,35);

	now.display(12);
	now.display(24);

	return 0;
}
```
