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
}

string toStr(myDouble number)
{
    if (!number.pre.empty() && !number.after.empty())
    {
        ostringstream ss;
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

myDouble convert(string number)
{
    myDouble value;
    if (number[0] == '-')
    {
        value.sign = false;
        number = number.substr(1, number.length() - 1);
    }
    else
    {
        value.sign = true;
    }
    size_t pointPos = number.find(".");
    value.pre[0] = number[0] - '0';
    value.after[0] = number[pointPos + 1] - '0';
    for (size_t i = 1; i < pointPos; i++)
    {
        value.pre.push_back(number[i] - '0');
    }
    for (size_t i = pointPos + 2; i < number.length(); i++)
    {
        value.after.push_back(number[i] - '0');
    }

    return value;
}

int main()
{
    myDouble a;
    cout << toStr(a) << "\n";
    a = convert("-12345.48974");
    cout << toStr(a);
    return 0;
}