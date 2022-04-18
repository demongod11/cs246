#include <bits/stdc++.h>
#include <stdio.h>

using namespace std;

#define ll long long
#define vll vector<ll>
#define pb push_back

struct fd { 
    ll left[50];
    ll right[50];
    ll lcount,rcount;
} f[100];


int main(){
    
    string n1, n2;
    getline(cin, n1);
    getline(cin, n2);
    int n = stoi(n1);
    int m = stoi(n2);

    int fdcount;

    int attr[n];

    for(int i=0; i<n; i++){
        attr[i]=i+1;
    }

    for(int i= 0; i<m; i++){
        f[i].lcount = 0;
        f[i].rcount = 0;
    }


    vector<string> s11;
    vector<string> s12;

    for(int i = 0; i<m; i++){
        string s;
        getline(cin, s);
        string s1;
        getline(cin, s1);
        s11.push_back(s);
        s12.push_back(s1);
    }

    fdcount = -1;
    for(int i = 0; i<m; i++){
        fdcount++;
        int j = 0;
        char temp[100];
        int k = 0;

        for(int y = 0; y<s11[i].size(); y++){
            if(s11[i][y]==' '){
                temp[k] = '\0';
                k = 0;
                int ans = atoi(temp);

                f[fdcount].left[f[fdcount].lcount] = ans;
                f[fdcount].lcount++;
            }
            else{
                temp[k] = s11[i][y];
                k++;
            }
        }

        temp[k] = '\0';
                k = 0;
                int ans = atoi(temp);
                f[fdcount].left[f[fdcount].lcount] = ans;
                f[fdcount].lcount++;

        k = 0;

        for(int y = 0; y<s12[i].size(); y++){
            if(s12[i][y]==' '){
                temp[k] = '\0';
                k = 0;
                int ans = atoi(temp);
                f[fdcount].right[f[fdcount].rcount] = ans;
                f[fdcount].rcount++;
            }
            else{
                temp[k] = s12[i][y];
                k++;
            }
        }
        temp[k] = '\0';
        k = 0;
        ans = atoi(temp);

        f[fdcount].right[f[fdcount].rcount] = ans;
        f[fdcount].rcount++;
    }

    set<set<ll>> s_key,c_key;

    for(int x=1;x<int(pow(2,n));x++){
        
        int arr[n]={0};
        ll a=x;
        ll i=0;
        while(a!=0){
           arr[i]=a%2;
           a/=2;
           i++;
        }
        set<ll> s,s2;
        for(int y=0;y<n;y++){
            if(arr[y]==1){
                s.insert(y+1);
            }
        }
        s2=s;
    
        while(1){
            int high=s2.size();
            for(int y=0;y<m;y++){
                ll t=1;
                for(int z=0;z<f[y].lcount;z++){
                    if(s2.find(f[y].left[z])==s2.end())
                    t=0;
                }
                if(t==1){
                    for(int z=0;z<f[y].rcount;z++){
                        s2.insert(f[y].right[z]);
                    }
                }
            }
          if(high==s2.size())
          break;
        }
        
        if(s2.size()==n){
            s_key.insert(s);
        }
    }

    for(int x=1;x<=n;x++){
        for(auto it:s_key){
            if(it.size()==x){
                bool t=1;
                for(auto itr:s_key){
                    if(itr!=it){
                        bool tt=1; 
                        for(auto itrr:itr){
                            if(it.find(itrr)==it.end())
                            tt=0;
                        }
                        if(tt==1)
                        t=0;
                    }
                }
                if(t==1){
                    c_key.insert(it);
                }
            }
        }
    }

    cout<<c_key.size()<<endl;

    for(int x=1;x<=n;x++){
        for(auto it:c_key){
            if(it.size()==x){
            for(auto itr:it){
                cout<<itr<<" ";
            }
            cout<<endl;
            }
        }
    }    
}