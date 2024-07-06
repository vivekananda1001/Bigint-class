#include<bits/stdc++.h>
#include"BigInt.h"


using namespace std;

/*
  Program to print very big factorial values.
*/

/*
   INPUT : n
   OUTPUT will be factorial of all the numbers from 1 to n
   each in new line.
*/


signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    BigInt fact(1),n,curr(1);
    cin>>n;
    n=n+1;
    while(n>curr)
    {
        fact=fact*curr;
        curr=curr+1;
        cout<<fact<<"\n";
    }


    return 0;
}





