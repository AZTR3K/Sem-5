
// https://codeforces.com/problemset/problem/1935/B

#include<vector>
#include<iostream>
using namespace std;
void Solve(int n,vector<int> &vt)
{
    vector<int> pre(n),suffix(n),count(n+2);
    int leftcount =0,rightcount = 0;


    // Logic : if there are more than 2 such regions having same MEX , we can prove that there are also 2 such regions having the same mex
    // so we find left and right MEX and find the point where pre[i] == suf[i+1] the regions are then (1,i) , (i+1,n); if no such point we return -1
    for(int i=0;i<n;i++)
    {
        count[vt[i]]++;
        // event tho the loop is nested in the worst case it will run for n+n and not n*n;
        while(count[leftcount])
            leftcount++;
        pre[i]= leftcount;
    }
    count.assign(n,0);
    for(int i=n-1;i>=0;i--)
    {
        count[vt[i]]++;
        while(count[rightcount])
            rightcount++;
        suffix[i]= rightcount;
    }
    for(int i=0;i<n-1;i++)
    {
        if(pre[i]==suffix[i+1])
        {
            // count of regions
            cout <<"2\n";
            cout <<"1 "<<i+1 <<"\n";
            cout <<i+2<<" "<<n<<"\n";
            // print i+1 and i+2 as the arrays are 0- indexed and not 1.
            return;
        }
        if(i==n-2)
            cout <<-1<<endl;
    }
    return;
}
int main()
{
    // imput 
    int t=1;
    // cin>>t;
    for(int i=0;i<t;i++)
    {
        int n;
        cin>>n;
        vector<int> vt(n);
        for (int j=0;j<n;j++)
            cin>>vt[j];
        Solve(n,vt);
    }
}