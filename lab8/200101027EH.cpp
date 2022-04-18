#include <bits/stdc++.h>
using namespace std;

class Bucket
{
public:
    int capacity;
    vector<int> data;
    vector<int> extra_data;
    int valid;
    int local_depth;
    int no_of_keys;

    Bucket(int capacity, int local_depth);
    void insert(int data);
    bool isFull();
    int search(int data);
};

Bucket::Bucket(int cap, int local_dep)
{

    capacity = cap;
    local_depth = local_dep;
    no_of_keys = 0;
    vector<int> temp_data(cap, 0);
    data = temp_data;
    valid = 0;
}

void Bucket::insert(int dat)
{

    if (isFull())
    {
        return;
    }
    data[no_of_keys] = dat;
    no_of_keys++;
}

bool Bucket::isFull()
{
    return (no_of_keys == capacity);
}
int Bucket::search(int dat)
{

    for (int i = 0; i < no_of_keys; i++)
    {
        if (data[i] == dat)
        {
            return i;
        }
    }
    return -1;
}
class Directory
{
public:
    Directory(int global_depth, int bucket_capacity, int M);
    vector<Bucket *> dir;
    int global_depth;
    int bucket_capacity;
    int no_of_valid;
    int M;
    vector <Bucket*> ascending;

    bool isPresent(int data);
    void insert(int data);
    void delete_elem(int data);
    void print_bucket(int index);
    void display();
    void printDirectory();
    
};

Directory::Directory(int glob, int cap, int Masd)
{
    global_depth = glob;
    bucket_capacity = cap;
    M = Masd;
    int sz = (1 << glob);
    vector<Bucket *> temp_dir(sz, nullptr);
    dir = temp_dir;
    no_of_valid = 0;

    for (int i = 0; i < sz; i++)
    {
        auto b = new Bucket(cap, global_depth);
        ascending.push_back(b);
        dir[i] = b;
    }
}

void Directory::insert(int dat)
{
    if(global_depth==22){
        return;
    }
    int sz = (1 << global_depth);
    int index = dat % sz;
    if (dir[index]->isFull())
    {
        if(dir[index]->local_depth == global_depth){

            if(dir[index]->valid == 1){
                dir[index]->extra_data.push_back(dat);
            }else{
                dir[index]->valid = 1;
                dir[index]->extra_data.push_back(dat);
                no_of_valid++;

                if((no_of_valid)*100 >= M*(ascending.size())){
                    vector <int> presentvalues;

                    for(int i=0; i<sz; i++){
                        if(dir[i]->valid == 1){
                            for(auto it: dir[i]->extra_data){
                                presentvalues.push_back(it);
                            }
                            dir[i]->valid = 0;
                            no_of_valid--;
                            dir[i]->extra_data.clear();
                        }
                    }

                    vector <Bucket*> temp_dir(2*sz);
                    for(int i = 0;i<sz;i++){
                        temp_dir[i] = dir[i];                       
                        temp_dir[i+sz] = dir[i];
                    }
                    dir = temp_dir;
                    global_depth++;
                    for(auto it: presentvalues){
                        insert(it);
                    }
                }
            }
        }
        else{
            vector <int> curvalues;

            for(auto x: dir[index]->data){
                curvalues.push_back(x);
            }
            curvalues.push_back(dat);
            int current_local_depth = dir[index]->local_depth;
            int first_index =index% (1<<current_local_depth);
            int second_index = first_index + (1<<current_local_depth);
            dir[index]->no_of_keys = 0;
            dir[index]->local_depth++;

            auto first_pointer = dir[index];
            auto second_pointer = new Bucket(bucket_capacity,current_local_depth+1);

            for(int i = 0;i<dir.size();i++){
                if(i%(1<<(current_local_depth+1)) == first_index){
                    dir[i] = first_pointer;
                }
                if(i%(1<<(current_local_depth+1)) == second_index){
                    dir[i] = second_pointer;
                }
            }      
            ascending.push_back(second_pointer);
            for(auto x: curvalues){
                insert(x);
            }
        }
    }
    else
    {
        dir[index]->insert(dat);
    }
}

bool Directory::isPresent(int dat)
{
    bool yes = 0;
    int sz = (1 << global_depth);
    yes = ((dir[dat % sz]->search(dat)) != -1) ? 1 : 0;

    return yes;
}

void Directory::display(){
    int noofbuckets = 0;
    int directory_size = (1<<global_depth);
    cout <<global_depth<<" ";

    set <Bucket*> s;
    for(auto x: dir){
        s.insert(x);
    }
    cout <<s.size()<<endl;

}

int main()
{

    int global_depth, bucket_capacity, M;

    cin >> global_depth>>bucket_capacity>>M;
    Directory d(global_depth, bucket_capacity, M);
    while(1){
        int x;
        cin >> x;
        if(x==2){
            int y;
            cin >> y;
            d.insert(y);
        }
        else if(x==5){
            d.display();
        }
        else if(x==6){
            break;
        }
    }
    return 0;
}