#include<bits/stdc++.h>
#define pb push_back

using namespace std;

class BigInt
{
private:


    //digit at 0th index is least significant digit (LSB)
    vector<int> digit;


    // this denotes the sign of the integer,
    // -1 for negative, 1 for positive and 0 for zero.
    int sign;


    // this denotes the number of digits in decimal representation of the number.
    int size;

    // function of karatsuba multiplication
    void karatsubaMultiply(int *a,int n,int *b,int m,int *res);

public:

    BigInt();                               // Default constructor, in case no argument is passed
    BigInt(long long x);                    // Constructor, when an integer is passed as argument
    BigInt(const string &s);                // Constructor, when a string is passed as a argument
    void removeZeros();                            // function to remove leading zeros from integer in string
    void readString(const string &s);       // function to read string and convert in into vector<int>
    void operator=(long long v);            // operator overloading for '=' if user try to input long long into BigInt class
    void operator=(const string &s);        // operator overloading for '=' if user inputs string into bigInt class


    // Declaring comparison operator
    bool operator>(const BigInt &b) const;
    bool operator<(const BigInt &b) const;

    // Function to calculate absolute value of integer
    BigInt abs() const;

    // Overloading unary minus operator for usage in situations like b=-b
    BigInt operator-() const;

    // Declaring operator overloading for '+'
    BigInt operator+(const BigInt &b) const;

    // Declaring operator overloading for '-'
    BigInt operator-(const BigInt &b) const;

    // overloading '<<' operator
    friend ostream& operator<<(ostream &output, BigInt const &b);

    // overloading '>>' operator
    friend istream& operator>>(istream &input, BigInt const &b);

    // overloading '*' operator
    BigInt operator *(BigInt &b);

    // overloading '==' operator
    bool operator ==(const BigInt &b) const;

    // overloading '!=' operator
    bool operator !=(const BigInt &b) const;


};

BigInt::BigInt()
{
    sign=0;
    size=0;
}

BigInt::BigInt(long long x)
{
    if(x==0)
    {
        sign=0;
        size=0;
        return ;
    }
    if(x<0)
    {
        sign=-1;
        x*=-1;
    }
    else
        sign=1;

    while(x)
    {
        digit.pb(x%10);
        x/=10;
    }

}

BigInt::BigInt(const string &s)
{
    readString(s);
}

void BigInt::removeZeros()
{
    while(!digit.empty() && digit.back()==0)
        digit.pop_back();

    if(digit.empty())
      sign=0;

}

void BigInt::readString(const string &s)
{
    digit.clear();
    sign=1;
    if(s[0]=='-')
        sign=-1;

    for(int i=s.size()-1 ; i>=0 ; i--)
    {
        if(s[i]>='0' && s[i]<='9')
        {
            int di=(int)(s[i]-'0');
            digit.pb(di);
        }
    }
    removeZeros();
}

void BigInt::operator=(long long v)
{
    digit.clear();

    if(v>0)
        sign=1;
    if(v<0)
    {
        sign=-1;
        v*=-1;
    }
    if(v==0)
        sign=0;

    while(v>0)
    {
        digit.pb(v%10);
        v/=10;
    }
}

void BigInt::operator=(const string &s)
{
    readString(s);
}

BigInt BigInt::operator-() const
{
    BigInt out;
    out.digit=digit;
    out.sign*=-1;
    return out;
}

BigInt BigInt::operator+(const BigInt &b) const
{
    // if same sign then perform addition
    if(sign == b.sign)
    {
        BigInt ans;
        ans=b;
        int carry=0;

        for(int i=0; i<max(digit.size(),b.digit.size()) || carry ; i++)
        {
            if(i==ans.digit.size())
                ans.digit.pb(0);

            int ad=0;
            if(i<digit.size())
                ad=digit[i];
            ans.digit[i] += carry + ad;

            carry = (int)(ans.digit[i]>=10);
            if(carry)
                ans.digit[i]-=10;
        }

        return ans;

    }

    // else return output of subtraction
    // note that now they will have same sign
    return *this - (-b);
}

BigInt BigInt::operator-(const BigInt &b) const
{
    // if same sign then perform subtraction
    if(sign == b.sign)
    {
        // performing subtraction when absolute value *this is > b
        if(abs() > b.abs())
        {
            BigInt ans=*this;
            int l1=ans.digit.size();
            int l2=b.digit.size();

            vector<int> v;
            int x=0;

            while(x<l2)
            {
                v.pb(b.digit[x]);
                x++;
            }

            while(x<l1)
            {
                v.pb(0);
                x++;
            }

            for(int i=0;i<l1;i++)
            {
                ans.digit[i]-=v[i];
                int carry=(int)(ans.digit[i] < 0);
                if(carry)
                {
                    ans.digit[i]+=10;
                    ans.digit[i+1]-=-1;
                }
            }
            ans.removeZeros();
            return ans;
        }

        // else reversing the subtraction
        return -(b - *this);
    }
    // if opposite sign then change sign and perform addition.
    return *this + (-b);
}

bool BigInt::operator>(const BigInt &b) const
{
    if(sign != b.sign)
        return (sign > b.sign);

    if(sign == 0)
        return false;

    if(digit.size() != b.digit.size())
        return (digit.size()*sign > b.digit.size()*b.sign);

    for(int i=digit.size()-1 ; i>=0; i--)
    {
        if(digit[i]==b.digit[i])
            continue;
        return (digit[i]*sign > b.digit[i]*b.sign);
    }

    // return false is number is exactly same
    return false;
}

bool BigInt::operator<(const BigInt &b) const
{
    return *this > b;
}

BigInt BigInt::abs() const
{
    BigInt ans=(*this);
    ans.sign*=ans.sign;
    return ans;
}

ostream& operator<<(ostream &output , const BigInt &b)
{
    if(b.sign==0)
        output<<0;

    if(b.sign==-1)
        output<<'-';

    for(int i=b.digit.size()-1 ; i>=0; i--)
        output<<b.digit[i];

    return output;
}

istream& operator>>(istream &input, BigInt &b)
{
    string s;
    input>>s;
    b.readString(s);
    return input;
}

bool BigInt::operator==(const BigInt& b) const
{
    if(sign != b.sign)
        return false;

    if(digit.size() != b.digit.size())
        return false;

    for(int i=0;i<digit.size();i++)
    {
        if(digit[i]!=b.digit[i])
            return false;
    }

    return true;
}

bool BigInt::operator!=(const BigInt &b) const
{
    BigInt x= *this;
    if(x==b)
        return false;
    else
        return true;
}



void BigInt::karatsubaMultiply(int* a, int n, int *b, int m, int* res)
{
    // base case when length of either number less than 32
    if(min(n,m) <= 32)
    {

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
                res[i+j] += a[i] * b[j];
        }
        return;
    }

    const int x = min(n, m);
    if(n > m)
        karatsubaMultiply(a + x, n - x, b, m, res + x);
    if(m > n)
        karatsubaMultiply(a, n, b + x, m - x, res + x);

    // a0 -> LSB half of a
    // a1 -> MSB half of a
    // b0 -> LSB half of b
    // b1 -> MSB half of b
    // z0 = a0 * b0, z1 = a1 * b1, z2 = (a0 + a1) * (b0 + b1) - z1 - z0

    const int left = (x + 1)/2;
    const int right = x/2;

    vector<int> v(left + right - 1);


    karatsubaMultiply(a, left, b, left, v.data()); // z0

    for(int i = 0; i < 2 * left - 1; i++)
    {
        res[i] += v[i]; // adding z0
        res[i + left] -= v[i]; // subtracting z0 from z2
        v[i] = 0;
    }

    karatsubaMultiply(a + left, right, b + left, right, v.data());  // z1

    for(int i = 0; i < 2 * right - 1; i++)
    {
        res[i + 2*left] += v[i]; // adding z1
        res[i + left] -= v[i];   // subtracting z1 from z2
    }


    // if x is odd
    v[left - 1] = a[left - 1];
    v[left + left - 1] = b[left - 1];

    // storing (a0 + a1) and (b0 + b1) in vector v
    for(int i = 0; i < right; i++)
    {
        v[i] = a[i] + a[right + i];
        v[i + left] = b[i] + b[left + i];
    }

    karatsubaMultiply(v.data(), left, v.data() + left, left, res);

}


BigInt BigInt::operator*(BigInt &b)
{
    BigInt res;
    res.sign = sign * b.sign;

    vector<int> temp(digit.size() + b.digit.size() - 1, 0);

    karatsubaMultiply(digit.data(), digit.size(), b.digit.data(), b.digit.size(), temp.data());
    int carry = 0;

    for(int u: temp)
    {
        res.digit.push_back((carry + u)%10);
        carry = (carry + u)/10;
    }

    while(carry != 0)
    {
        res.digit.push_back(carry%10);
        carry /= 10;
    }

    res.removeZeros();

    return res;
}


