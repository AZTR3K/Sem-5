
// https://codeforces.com/contest/1195/problem/C

#include<iostream>
#include<vector>
using namespace std;
void Updatevals(long long& max,long long &row,long long& SecondMax,vector<vector<long long>> & grid ,long long column)
{
    max = SecondMax =  -(1<<30);
    row =-1;
    for(int i=0;i<grid.size();i++)
    {
        if(grid[i][column] > max)
        {
            SecondMax = max;
            max = grid[i][column];
            row = i;
            continue;
        }
        if(grid[i][column] > SecondMax)
            SecondMax= grid[i][column];
    }
}
long long Solve(long long rows,long long cols,vector<vector<long long>> & grid)
{
    vector<vector<long long >> dp(rows,vector<long long>(cols,0));
    long long OverallMax=0;
    // initial states for dp
    for(long long i=0;i<rows;i++)
    {
        dp[i][0] = grid[i][0];
        OverallMax=max(OverallMax,dp[i][0]);
    }
    for(long long i=1;i<cols;i++)
    {
        // Maximum in the previous column, its row and Second Max in the column
        long long pMax,pRow,psMax;
        // Maximum in the [CurColumn-2] column, its row and Second Max column
        long long ppMax=0,ppRow=-1,ppsMax=0;
        //n*m total m for the function and n for above loop 
        Updatevals(pMax,pRow,psMax,dp,i-1);
        if(i!=1)
        //n*m total m for the function and n for above loop 
            Updatevals(ppMax,ppRow,ppsMax,dp,i-2);
        //n*m total
        for(long long j=0;j<rows;j++)
        {
            // usign Result of prevColumn -- if Row is same as prevMax Row we use SecondMax
            if(pRow==j)
                dp[j][i] = max(dp[j][i] ,psMax+grid[j][i]);
            else
                dp[j][i] = max(dp[j][i],pMax+grid[j][i]);
            // We can also use the result of prevprev column -- same logic as above
            // we dont't need to go further back in columns, only prev and 2ndprev column is enough
            if(ppRow==j)
                dp[j][i] = max(dp[j][i] ,ppsMax+grid[j][i]);
            else
                dp[j][i] = max(dp[j][i],ppMax+grid[j][i]);
            OverallMax=max(OverallMax,dp[j][i]);
        }
    }
    //complexity = n*m + n*m + n*m = O(nm)
    return OverallMax;    
}
int main()
{
    long long n,m=2;
    cin>>m;
    cin>>n;
    // m rows and n columns
    vector<vector<long long>> grid(m,vector<long long>(n ,0));
    for (long long i=0;i<m;i++)
        for (long long j=0;j<n;j++)
            cin>>grid[i][j];
    cout <<Solve(m,n,grid);
}