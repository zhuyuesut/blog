---
layout: post
title: "quick sort"
author: Zhu Yue
categories: other
---

```c++

//quick_sort(T entry[],int count); 
template<class T>
int partition(T entry[],int low,int high)
{
    T pivot;
    int i,last_small;
    swap(entry[low],entry[(low+high)/2]);
    pivot=entry[low];
    last_small=low;
    for(i=low+1;i<=high;i++)
        if(entry[i]<pivot)
        {
            last_small=last_small+1;
            swap(entry[last_small],entry[i]);
        }
    swap(entry[low],entry[last_small]);
    return last_small;
}

template<class T>
void recursive_quick_sort(T entry[],int low,int high)
{
    int pivot_position;
    if(low<high)
    {
        pivot_position=partition(entry,low,high);
        recursive_quick_sort(entry,low,pivot_position-1);
        recursive_quick_sort(entry,pivot_position+1,high);
    }
}

template<class T>
void quick_sort(T entry[],int count)
{
    recursive_quick_sort(entry,0,count-1);
}
```
