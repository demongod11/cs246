#include <bits/stdc++.h>
using namespace std;

void merge(vector<vector<int>>& runs, vector<int>& temp){
    vector<int> pointer;
    int num = 0, min, k, i, j;
    // Initialize the pointer with the first location for each run
    for (i = 0; i < runs.size(); i++){
        pointer.push_back(0);
        num += runs[i].size();
    }
    // For each element in the pages, find the smallest record and add into output page
    for (i = 0; i < num; i++){
        min = INT_MAX;
        k = 0;
        for (j = 0; j < pointer.size(); j++){
            if (pointer[j] < runs[j].size() && runs[j][pointer[j]] < min){
                min = runs[j][pointer[j]];
                k = j;
            }
        }
        // Add the smallest record into the output page
        temp.push_back(min);
        // Increment the pointer corresponding to the smallest record
        pointer[k]++;
    }
}

void external_sort(vector<vector<int>>& runs, int buffer, int runs_to_merge, int itr_num, int page_num, int rec_per_page, int total_rec, vector<int>& ans){
    // Intially sorting each page
    for (int i = 0; i < runs.size(); i++){
        sort(runs[i].begin(), runs[i].end());
    }

    if(itr_num == 0){
        for(int j=0; j<runs[page_num].size(); j++){
            ans.push_back(runs[page_num][j]);
        }
    }else{
        vector<vector<int>> sorted_runs, temp;
        int k = 0, i = 0;
        vector<int> temp1;

        while (i < runs.size()){
            temp.clear();
            for (k = 0; k < buffer && i + k < runs.size(); k++){
                temp.push_back(runs[i + k]);
            }
            temp1.clear();
            // Merging
            merge(temp, temp1);
            // Add the merged pages into the next round.
            sorted_runs.push_back(temp1);
            i += k;
        }
        runs.clear();
        runs = sorted_runs;

        sorted_runs.clear();
        k=0; i=0;

        int itr=0;

        // Recursively merge the pages taking (buffer - 1) pages at a time
        while (itr < itr_num){
            // Group (runs_to_merge) pages and merge them
            while (i < runs.size()){
                temp.clear();
                for (k = 0; k < runs_to_merge && i + k < runs.size(); k++){
                    temp.push_back(runs[i + k]);
                }
                temp1.clear();
                // Merging
                merge(temp, temp1);
                // Add the merged pages into the next round.
                sorted_runs.push_back(temp1);
                i += k;
            }
            runs.clear();
            runs = sorted_runs;
            itr++;
        }
        int starting_rec_num = (page_num)*(rec_per_page);
        int ran=0,flag=1;
        for(int j=0;j<runs.size(); j++){
            for(int p=0; p<runs[j].size(); p++){
                if(ran==starting_rec_num){
                    int waq=rec_per_page;
                    while(waq){
                        ans.push_back(runs[j][p]);
                        p++;
                        waq--;
                    }
                    flag=0;
                    break;
                }else{
                    ran++;
                }
            }
            if(flag == 0){
                break;
            }
        }
    }
}

int main(){
    int buffer, runs_to_merge, rec_per_page, total_rec, itr_num, page_num;
    cin >> buffer >> runs_to_merge >> rec_per_page >> total_rec;
    vector<vector<int>> runs;
    int k = 0, i = 0, a;
    vector<int> temp;
    // Taking input
    while (i < total_rec){
        temp.clear();
        for (k = 0; k < rec_per_page && i + k < total_rec; k++){
            cin >> a;
            temp.push_back(a);
        }
        runs.push_back(temp);
        i += k;
    }
    
    cin>>itr_num>>page_num;
    vector<int> ans;
    ans.clear();

    // Sorting the records
    external_sort(runs, buffer, runs_to_merge, itr_num, page_num, rec_per_page, total_rec, ans);
    // Printing the sorted records
    for (i = 0; i < ans.size(); i++){
        cout << ans[i] << "\n";
    }
    return 0;
}