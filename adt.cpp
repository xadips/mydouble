#include <iostream>
#include <iomanip>
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
    myDouble operator+(myDouble &obj)
    {
        myDouble result;
        int carry = 0, sum;

        after.resize(max(after.size(), obj.after.size()), 0);
        obj.after.resize(max(after.size(), obj.after.size()), 0);

        pre.resize(max(pre.size(), obj.pre.size()), 0);
        obj.pre.resize(max(pre.size(), obj.pre.size()), 0);
        // Make result's floating part size match
        result.after.resize(after.size(), 0);
        result.pre.resize(pre.size(), 0);
        // First make the floating portions of the numbers equal in size
        // Add up the digits
        for (int i = result.after.size() - 1; i >= 0; i--)
        {
            sum = after[i] + obj.after[i] + carry;
            result.after[i] = sum % 10;
            carry = sum / 10;
        }
        // Check if there's something to carry on to the integer part of the number
        if (carry != 0)
        {
            result.pre[0] += carry;
            int i;
            carry = 0;
            for (i = result.pre.size() - 1; result.pre[i] > 9 && i > 0; i--)
            {
                carry = result.pre[i] / 10;
                result.pre[i] %= 10;
                result.pre[i - 1] += carry;
            }
            if (carry != 0)
            {
                result.pre[i] %= 10;
                result.pre[0] = carry;
            }
        }
        carry = 0;
        for (int i = 0; i < result.pre.size(); i++)
        {
            sum = pre[i] + obj.pre[i] + carry + result.pre[i];
            result.pre[i] = sum % 10;
            carry = sum / 10;
        }
        if (carry != 0)
        {
            result.pre.push_back(carry);
        }

        return result;
    }
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

string myDouble::toStr()
{
    if (!this->pre.empty() && !this->after.empty())
    {
        ostringstream ss;
        string converted = (this->sign == true) ? "" : "-";
        copy(this->pre.rbegin(), this->pre.rend(), ostream_iterator<int>(ss));
        converted += ss.str();
        ss.str(".");
        converted += ss.str();
        copy(this->after.begin(), this->after.end(), ostream_iterator<int>(ss));
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
    value.pre[0] = number[pointPos - 1] - '0';
    value.after[0] = number[pointPos + 1] - '0';
    for (size_t i = 1; i < pointPos; i++)
    {
        value.pre.push_back(number[pointPos - i - 1] - '0');
    }
    for (size_t i = pointPos + 2; i < number.length(); i++)
    {
        value.after.push_back(number[i] - '0');
    }

    return value;
}

int main()
{
    myDouble a, b, c;
    a = convert("9945.9679");
    b = convert("9945.0689");
    long double d = 9945.9679;
    long double e = 9945.0689;
    long double f = d + e;
    c = a + b;
    cout << c.toStr() << "\n";
    cout << fixed << f;
    return 0;
}