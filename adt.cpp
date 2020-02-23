#include <iostream>
#include <vector>

using namespace std;

const char SIGNS[] = {'-', ' '};

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
    cout << SIGNS[a.sign] << a.pre[0] << "." << a.after[0] << "\n";

    return 0;
}