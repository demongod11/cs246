#include <bits/stdc++.h>
using namespace std;

typedef long double LD;
typedef long long ll;
#define int ll
#define pb push_back
#define REP(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define FAST_IO              \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0);

//global var to store all candidate keys...
vector<vector<int>> candidate_keys;


void split(string const &str, const char delim, vector<int> &out){
    stringstream ss(str);
    string s;
    while (getline(ss, s, delim)){
        stringstream Str(s);
        int x;
        Str >> x;
        out.push_back(x);
    }
}

void prtvec(vector<int> a){
    for (auto i = a.begin(); i != a.end(); ++i)
        cout << *i << " ";
}

void prtarr(int *arr, int n){
    for (int j = 0; j < n; j++)
        cout << arr[j] << " ";
    cout << endl;
}

vector<int> UNION(vector<int> A, vector<int> B){
    auto i=A.begin(), j=B.begin();
    vector<int> temp;
    for(; i<A.end();++i){
        temp.pb(*i);
    }
    i=A.begin();
    for(; j<B.end();){
        while(*j>*i)++i;
        if(*i==*j){++i;++j;}
        else{temp.pb(*j);++j;}
    }

    //auto it = set_union(A.begin(), A.end(),B.begin(),B.end(),temp.begin());
    sort(temp.begin(), temp.end());
    
    return temp;
}

bool checkSub(int *A, vector<int> B, int la, int lb){
    // check if B is subset of A...
    int i = 0;
    int j = 0;
    if (lb > la)
        return 0;
    else for (; i < lb; i++){
            // cout<<B[i]<<" : ";
            if (j < la)
                for (; j < la; j++){
                    while (B[i] > A[j])
                        j++;
                    if (A[j] == B[i]){
                        break;
                    }
                    else
                        return 0; // if does not match
                }
            else
                return 0; // if Array finishes
            // cout<<endl;
        }
    return 1;
}

vector<int> c(int *comb, int r, vector<pair<vector<int>, vector<int>>> A){
    vector<int> temp;
    for(int i=0;i<r;i++) temp.pb(comb[i]);
    for (auto i = A.begin(); i != A.end(); ++i){
        if (checkSub(comb, (*i).first, r, (*i).first.size()))
            temp = UNION(temp, (*i).second);
    }
    return temp;
}

bool checkCandidateKey(int *comb, int r, vector<pair<vector<int>, vector<int>>> A, int n_attr){
    vector<int> temp;
    for(int i=0;i<r;i++) {temp.pb(comb[i]);}
    int last=temp.size();
    while(true){
        int temp2[last];
        for(int i=0;i<last;++i)temp2[i]=temp[i];
        temp = c(temp2, last, A);      
        if(temp.size()==last)break;
        last=temp.size();
    }
    if(temp.size()==n_attr)return 1;
    else return 0;
}

void makecomb(int arr[], int *comb, int start, int end, int index, int r, vector<pair<vector<int>, vector<int>>> A,int n_attr){
    if (index == r){
        //check if is super key...
        for (auto i = candidate_keys.begin(); i != candidate_keys.end(); ++i)
            if(checkSub(comb, (*i), r, (*i).size()))return;

        /*for (int j = 0; j < r; j++)cout << comb[j] << " ";
        cout << " : ";*/
        bool iscand=checkCandidateKey(comb, r, A, n_attr);
        vector<int> temp3;
        for(int i=0;i<r;++i)temp3.pb(comb[i]);
        if(iscand)candidate_keys.pb(temp3);
        cout << endl;
        return;
    }
    for (int i = start; (i <= end) && (end - i + 1 >= r - index); i++){
        comb[index] = arr[i];
        makecomb(arr, comb, i + 1, end, index + 1, r, A, n_attr);
    }
}

void print2(vector<pair<vector<int>, vector<int>>> a){
    for (auto i = a.begin(); i != a.end(); ++i)
    {
        prtvec((*i).first);
        cout << " -> ";
        prtvec((*i).second);
        cout << endl;
    }
}

void print3(vector<vector<int>> a){
    for (auto i = a.begin(); i != a.end(); ++i){
        prtvec((*i)); cout<<endl;}
}

signed main(){
    FAST_IO
    int n_attributes;
    cin >> n_attributes;
    int n_FD;
    cin >> n_FD;

    char temp[1];
    cin.getline(temp, 1);

    // to store all FDs
    vector<pair<vector<int>, vector<int>>> A;

    REP(i, n_FD){
        vector<int> a, b;
        char s1[100], s2[100];
        cin.getline(s1, 100);
        cin.getline(s2, 100);
        split(s1, ' ', a);
        split(s2, ' ', b);
        pair<vector<int>, vector<int>> B;
        B.first = a;
        B.second = b;
        A.pb(B);
    }
    //print2(A);cout << endl;

    int arr[n_attributes];
    REP(i, n_attributes)
        arr[i] = i + 1;

    // making all combinations...
    FOR(i, 1, n_attributes + 1){
        int data[i];
        makecomb(arr, data, 0, n_attributes - 1, 0, i, A, n_attributes);
    }
    sort(candidate_keys.begin(), candidate_keys.end(), [] (const auto& lhs, const auto& rhs) 
            {return lhs.size() > rhs.size();});
    cout<<candidate_keys.size()<<endl;
    print3(candidate_keys);
}