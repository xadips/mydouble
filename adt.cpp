#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class myDouble
{
public:
    bool sign;
    vector<int> pre;
    vector<int> after;

    myDouble();
    ~myDouble();
};

myDouble::myDouble()
{
    this->sign = true;
    this->pre.push_back(0);
    this->after.push_back(0);
}

myDouble::~myDouble()
{
    delete (&sign);
    this->pre.clear();
    this->after.clear();
}

int main()
{
    myDouble a;

    return 0;
}