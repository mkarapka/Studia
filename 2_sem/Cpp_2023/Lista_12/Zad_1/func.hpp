#pragma once
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <iostream>


template <typename T>
class Sumator
{
public:
    T sum;
    int count;
    Sumator() : sum(0), count(0) {}

    void operator () (T value)
    {
        sum += value;
        ++count;
    }

    T getSum() const { return sum; }
    T getAverage() const { return sum / count; }
    int getCount() const { return count; }

};
