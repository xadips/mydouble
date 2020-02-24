#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>

using namespace std;

class myDouble
{
public:
    bool sign;
    vector<int> pre;
    vector<int> after;

    myDouble();
    ~myDouble();
    string toStr();
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

string myDouble::toStr()
{
    if (!this->pre.empty() && !this->after.empty())
    {
        stringstream ss;
        string converted = (this->sign == true) ? "" : "-";
        copy(this->pre.begin(), this->pre.end(), ostream_iterator<int>(ss));
        converted += ss.str();
        ss.str(".");
        converted += ss.str();
        copy(this->after.begin(), this->after.end(), ostream_iterator<int>(ss));
        converted += ss.str();

        return converted;
    }
    return NULL;
}

int main()
{
    myDouble a;
    cout << a.toStr() << "\n";

    return 0;
}