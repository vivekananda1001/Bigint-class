#include<bits/stdc++.h>
#include"BigInt.h"


using namespace std;

/*
    Program to print any large power of number.
*/

/*
    INPUT : n
    OUTPUT : n^n
*/


signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    BigInt pow(1),n,cnt(1);
    cin>>n;
    auto temp=n+1;
    while(temp>cnt)
    {
        pow=pow*n;
        cnt=cnt+1;
    }

    cout<<"\n";
    cout<<pow<<"\n";

    return 0;
}





