#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>

using namespace std;

bool isSmaller(string n1, string n2);

class myDouble
{
public:
    bool sign;
    vector<int> pre;
    vector<int> after;

    myDouble();
    ~myDouble();
    void clip();
    string toStr();

    myDouble operator+(myDouble obj)
    {
        myDouble result, temp;
        temp.sign = sign;
        temp.pre = pre;
        temp.after = after;
        if (sign == false && obj.sign == true)
        {
            temp.sign = true;
            return obj - temp;
        }
        if (sign == true && obj.sign == false)
        {
            obj.sign = true;
            return temp - obj;
        }
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
        for (int i = 0; i < result.pre.size(); i++)
        {
            sum = pre[i] + obj.pre[i] + carry;
            result.pre[i] = sum % 10;
            carry = sum / 10;
        }
        if (carry != 0)
        {
            result.pre.push_back(carry);
        }
        if (sign == false && obj.sign == false)
        {
            result.sign = false;
        }
        result.clip();

        return result;
    }

    myDouble operator-(myDouble obj)
    {
        myDouble result, temp;
        temp.sign = sign;
        temp.pre = pre;
        temp.after = after;
        if (sign == true && obj.sign == false)
        {
            obj.sign = true;
            return temp + obj;
        }
        else if (sign == false && obj.sign == true)
        {
            obj.sign = false;
            return temp + obj;
        }
        else if (sign == false && obj.sign == false)
        {
            obj.sign = true;
            temp.sign = true;
            return obj - temp;
        }
        else
        {
            result.sign = true;
            if (isSmaller(temp.toStr(), obj.toStr()))
            {
                swap(temp, obj);
                result.sign = false;
            }
            temp.after.resize(max(temp.after.size(), obj.after.size()), 0);

            obj.pre.resize(temp.pre.size(), 0);
            obj.after.resize(max(temp.after.size(), obj.after.size()), 0);

            result.pre.resize(temp.pre.size(), 0);
            result.after.resize(max(temp.after.size(), obj.after.size()), 0);
            int subtract, carry = 0;
            for (int i = result.after.size() - 1; i >= 0; i--)
            {
                subtract = temp.after[i] - obj.after[i] - carry;
                if (subtract < 0)
                {
                    subtract += 10;
                    carry = 1;
                }
                else
                {
                    carry = 0;
                }
                result.after[i] = subtract;
            }
            int i;
            for (i = 0; i < result.pre.size(); i++)
            {
                subtract = temp.pre[i] - obj.pre[i] - carry;
                if (subtract < 0)
                {
                    subtract += 10;
                    carry = 1;
                }
                else
                {
                    carry = 0;
                }
                result.pre[i] = subtract;
            }
        }
        result.clip();
        return result;
    }
};

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

bool isSmaller(string str1, string str2)
{
    myDouble n1 = convert(str1), n2 = convert(str2);
    if (n1.pre.size() < n2.pre.size())
    {
        return true;
    }
    if (n1.pre.size() > n2.pre.size())
    {
        return false;
    }
    else
    {
        for (int i = n1.pre.size() - 1; i >= 0; i--)
        {
            if (n1.pre[i] < n2.pre[i])
            {
                return true;
            }
            if (n1.pre[i] > n2.pre[i])
            {
                return false;
            }
        }
        for (int i = 0; i < min(n1.after.size(), n2.after.size()); i++)
        {
            if (n1.after[i] < n2.after[i])
            {
                return true;
            }
            if (n1.after[i] > n2.after[i])
            {
                return false;
            }
        }
        return n1.after.size() < n2.after.size() ? true : false;
    }

    return false;
}

myDouble::myDouble()
{
    this->sign = true;
    this->pre.push_back(0);
    this->after.push_back(0);
}

myDouble::~myDouble()
{
}

void myDouble::clip()
{
    for (int i = this->pre.size() - 1; i > 0 && this->pre[i] == 0; i--)
    {
        this->pre.pop_back();
    }
    for (int i = this->after.size() - 1; i > 0 && this->after[i] == 0; i--)
    {
        this->after.pop_back();
    }

    return;
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

int main()
{

    return 0;
}