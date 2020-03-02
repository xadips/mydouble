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

    myDouble operator*(myDouble obj)
    {
        myDouble result, temp, middle;
        clip();
        obj.clip();
        int multiplication, carry = 0;
        result.pre.resize(pre.size() + obj.pre.size(), 0);
        result.after.resize(after.size() + obj.after.size(), 0);
        int j;
        for (int i = after.size() - 1; i >= 0; i--)
        {

            for (j = obj.after.size() - 1; j >= 0; j--)
            {
                multiplication = after[i] * obj.after[j] + result.after[i + j + 1] + carry;
                carry = multiplication / 10;
                result.after[i + j + 1] = multiplication % 10;
            }
            if (carry > 0)
            {
                result.after[i + j + 1] += carry;
            }
            carry = 0;
        }
        temp.pre[0] = obj.after[obj.after.size() - 1];
        for (int i = obj.after.size() - 2; i >= 0; i--)
        {
            temp.pre.push_back(obj.after[i]);
        }
        middle.pre.resize(pre.size() + temp.pre.size(), 0);
        for (int i = 0; i < pre.size(); i++)
        {

            for (j = 0; j < temp.pre.size(); j++)
            {
                multiplication = pre[i] * temp.pre[j] + middle.pre[i + j] + carry;
                carry = multiplication / 10;
                middle.pre[i + j] = multiplication % 10;
            }
            if (carry > 0)
            {
                middle.pre[i + j] += carry;
            }
            carry = 0;
        }
        middle.after[0] = middle.pre[temp.pre.size() - 1];
        for (int i = temp.pre.size() - 2; i >= 0; i--)
        {
            middle.after.push_back(middle.pre[i]);
        }
        middle.pre.erase(middle.pre.begin(), middle.pre.begin() + temp.pre.size());
        result = result + middle;

        temp.pre.clear();
        temp.after.clear();
        middle.pre.clear();
        middle.after.clear();

        for (int i = after.size() - 1; i >= 0; i--)
        {
            temp.pre.push_back(after[i]);
        }
        middle.pre.resize(obj.pre.size() + temp.pre.size(), 0);
        for (int i = 0; i < obj.pre.size(); i++)
        {

            for (j = 0; j < temp.pre.size(); j++)
            {
                multiplication = obj.pre[i] * temp.pre[j] + middle.pre[i + j] + carry;
                carry = multiplication / 10;
                middle.pre[i + j] = multiplication % 10;
            }
            if (carry > 0)
            {
                middle.pre[i + j] += carry;
            }
            carry = 0;
        }
        for (int i = temp.pre.size() - 1; i >= 0; i--)
        {
            middle.after.push_back(middle.pre[i]);
        }
        middle.pre.erase(middle.pre.begin(), middle.pre.begin() + temp.pre.size());
        result = result + middle;

        middle.pre.clear();
        middle.after.clear();
        middle.after.push_back(0);
        middle.pre.resize(pre.size() + obj.pre.size(), 0);
        for (int i = 0; i < pre.size(); i++)
        {

            for (j = 0; j < obj.pre.size(); j++)
            {
                multiplication = pre[i] * obj.pre[j] + middle.pre[i + j] + carry;
                carry = multiplication / 10;
                middle.pre[i + j] = multiplication % 10;
            }
            if (carry > 0)
            {
                middle.pre[i + j] += carry;
            }
            carry = 0;
        }
        result = result + middle;
        result.clip();
        if (sign == obj.sign)
        {
            result.sign = true;
        }
        else
        {
            result.sign = false;
        }
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
    myDouble a = convert("894798489.894984894"), b = convert("894984984984.89416567854178451");
    cout << (a * b).toStr() << "\n";

    return 0;
}