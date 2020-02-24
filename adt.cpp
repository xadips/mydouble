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

string toStr(myDouble number)
{
    if (!number.pre.empty() && !number.after.empty())
    {
        stringstream ss;
        string converted = (number.sign == true) ? "" : "-";
        copy(number.pre.begin(), number.pre.end(), ostream_iterator<int>(ss));
        converted += ss.str();
        ss.str(".");
        converted += ss.str();
        copy(number.after.begin(), number.after.end(), ostream_iterator<int>(ss));
        converted += ss.str();

        return converted;
    }
    return NULL;
}

int main()
{
    myDouble a;
    cout << toStr(a) << "\n";

    return 0;
}