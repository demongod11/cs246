#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#define ll long long
#define pll pair<ll,ll>
#define rep(i,n) for(ll i=0;i<n;i++)
#define mod 1000000007
#define INF 10000000000000000
#define ff first
#define ss second
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define pie 3.141592653589793238462643383279
#define PYES cout<<"YES"<<"\n"
#define PNO cout<<"NO"<<"\n"
#define SB(a) sort(a.begin(),a.end(),greater<ll>());
#define SS(a) sort(a.begin(),a.end());
#define vll vector<ll>
#define vpll vector<pll>
#define vvll vector<vll>
#define umll unordered_map<ll,ll>
#define mll map<ll,ll>
#define vbl vector <bool>
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
using namespace std;
int MAX1;
int MAX2;

// BP node
class Node {
  bool IS_LEAF;
  int *key, size;
  Node **ptr;
  friend class BPTree;

   public:
  Node(int ind);
};

// BP tree
class BPTree {
  Node *root;
  void insertInternal(int, Node *, Node *);
  Node *findParent(Node *, Node *);

   public:
  BPTree();
  void search(int);
  void insert(int);
  void display(Node *cursor,ll *noofindex,ll *noofdata);
  void displayroot(Node *cursor);
  Node *getRoot();
};

Node::Node(int ind) {
    if(ind==0)
    {
         key = new int[MAX1];
        ptr = new Node *[MAX1 + 1];
    }
    else
    {
         key = new int[MAX2];
        ptr = new Node *[MAX2 + 1];
    }

}


BPTree::BPTree() {
  root = NULL;
}

// Search operation
void BPTree::search(int x) {
  if (root == NULL) {
    cout << "Tree is empty\n";
  } else {
    Node *cursor = root;
    while (cursor->IS_LEAF == false) {
      for (int i = 0; i < cursor->size; i++) {
        if (x < cursor->key[i]) {
          cursor = cursor->ptr[i];
          break;
        }
        if (i == cursor->size - 1) {
          cursor = cursor->ptr[i + 1];
          break;
        }
      }
    }
    for (int i = 0; i < cursor->size; i++) {
      if (cursor->key[i] == x) {
        cout << "Found\n";
        return;
      }
    }
    cout << "Not found\n";
  }
}

// Insert Operation
void BPTree::insert(int x) {
    if (root == NULL) {
        root = new Node(0);
        root->key[0] = x;
        root->IS_LEAF = true;
        root->size = 1;
    }else{
        Node *cursor = root;
        Node *parent;
        while (cursor->IS_LEAF == false) {
        parent = cursor;
        for (int i = 0; i < cursor->size; i++) {
            if (x < cursor->key[i]) {
                cursor = cursor->ptr[i];
                break;
            }
            if (i == cursor->size - 1) {
                cursor = cursor->ptr[i + 1];
                break;
            }
        }
    }
    if (cursor->size < MAX1) {
      int i = 0;
      while (x > cursor->key[i] && i < cursor->size)
        i++;
      for (int j = cursor->size; j > i; j--) {
        cursor->key[j] = cursor->key[j - 1];
      }
      cursor->key[i] = x;
      cursor->size++;
      cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
      cursor->ptr[cursor->size - 1] = NULL;
    } else {
      Node *newLeaf = new Node(0);
      int virtualNode[MAX1 + 1];
      for (int i = 0; i < MAX1; i++) {
        virtualNode[i] = cursor->key[i];
      }
      int i = 0, j;
      while (x > virtualNode[i] && i < MAX1)
        i++;
      for (int j = MAX1; j > i; j--) {
        virtualNode[j] = virtualNode[j - 1];
      }
      virtualNode[i] = x;
      newLeaf->IS_LEAF = true;
      cursor->size = (MAX1 + 1) / 2;
      newLeaf->size = MAX1 + 1 - (MAX1 + 1) / 2;
      cursor->ptr[cursor->size] = newLeaf;
      newLeaf->ptr[newLeaf->size] = cursor->ptr[MAX1];
      cursor->ptr[MAX1] = NULL;
      for (i = 0; i < cursor->size; i++) {
        cursor->key[i] = virtualNode[i];
      }
      for (i = 0, j = cursor->size; i < newLeaf->size; i++, j++) {
        newLeaf->key[i] = virtualNode[j];
      }
      if (cursor == root) {
        Node *newRoot = new Node(1);
        newRoot->key[0] = newLeaf->key[0];
        newRoot->ptr[0] = cursor;
        newRoot->ptr[1] = newLeaf;
        newRoot->IS_LEAF = false;
        newRoot->size = 1;
        root = newRoot;
      } else {
        insertInternal(newLeaf->key[0], parent, newLeaf);
      }
    }
  }
}

// Insert Operation
void BPTree::insertInternal(int x, Node *cursor, Node *child) {
  if (cursor->size < MAX2) {
    int i = 0;
    while (x > cursor->key[i] && i < cursor->size)
      i++;
    for (int j = cursor->size; j > i; j--) {
      cursor->key[j] = cursor->key[j - 1];
    }
    for (int j = cursor->size + 1; j > i + 1; j--) {
      cursor->ptr[j] = cursor->ptr[j - 1];
    }
    cursor->key[i] = x;
    cursor->size++;
    cursor->ptr[i + 1] = child;
  } else {
    Node *newInternal = new Node(1);
    int virtualKey[MAX2 + 1];
    Node *virtualPtr[MAX2 + 2];
    for (int i = 0; i < MAX2; i++) {
      virtualKey[i] = cursor->key[i];
    }
    for (int i = 0; i < MAX2 + 1; i++) {
      virtualPtr[i] = cursor->ptr[i];
    }
    int i = 0, j;
    while (x > virtualKey[i] && i < MAX2)
      i++;
    for (int j = MAX2; j > i; j--) {
      virtualKey[j] = virtualKey[j - 1];
    }
    virtualKey[i] = x;
    for (int j = MAX2 + 1; j > i + 1; j--) {
      virtualPtr[j] = virtualPtr[j - 1];
    }
    virtualPtr[i + 1] = child;
    newInternal->IS_LEAF = false;
    cursor->size = MAX2 - (MAX2 + 1) / 2 ;
    newInternal->size = (MAX2 + 1) / 2;
    for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++) {
      newInternal->key[i] = virtualKey[j];
    }
    for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++) {
      newInternal->ptr[i] = virtualPtr[j];
    }
    if (cursor == root) {
      Node *newRoot = new Node(1);
      newRoot->key[0] = virtualKey[((MAX2+1)/2)-1];
      newRoot->ptr[0] = cursor;
      newRoot->ptr[1] = newInternal;
      newRoot->IS_LEAF = false;
      newRoot->size = 1;
      root = newRoot;
    } else {
      insertInternal(virtualKey[((MAX2+1)/2)-1], findParent(root, cursor), newInternal);
    }
  }
}

// Find the parent
Node *BPTree::findParent(Node *cursor, Node *child) {
  Node *parent;
  if (cursor->IS_LEAF || (cursor->ptr[0])->IS_LEAF) {
    return NULL;
  }
  for (int i = 0; i < cursor->size + 1; i++) {
    if (cursor->ptr[i] == child) {
      parent = cursor;
      return parent;
    } else {
      parent = findParent(cursor->ptr[i], child);
      if (parent != NULL)
        return parent;
    }
  }
  return parent;
}

// Print the tree
void BPTree::displayroot(Node *cursor)
{
    if (cursor != NULL) {
    for (int i = 0; i < cursor->size; i++) {
      cout << cursor->key[i] << " ";
    }
    cout << "\n";
}
}
void BPTree::display(Node *cursor,ll *noofindex,ll *noofdata) {

  if (cursor != NULL) {

            if(cursor->IS_LEAF)
            (*noofdata)++;
           else
             (*noofindex)++;

     //cout << cursor->key[i] << " ";
    //cout << "\n";
    if (cursor->IS_LEAF != true) {
      for (int i = 0; i < cursor->size + 1; i++) {
        display(cursor->ptr[i],noofindex,noofdata);
      }
    }
  }




   //if (cursor != NULL) {
   // for (int i = 0; i < cursor->size; i++) {
    //  cout << cursor->key[i] << " ";
    //}
    //cout << "\n";
    //if (cursor->IS_LEAF != true) {
     // for (int i = 0; i < cursor->size + 1; i++) {
     //   display(cursor->ptr[i]);
     // }
    //}
 // }
}

// Get the root
Node *BPTree::getRoot() {
  return root;
}

int main() {
  int d,t;cin>>d>>t;
  MAX1=2*d;MAX2=2*t+1; BPTree node;
  int temp;int data;
  while(true)
  {
      bool f=true;
      cin>>temp;ll noindex=0,nodata=0;
      switch(temp)
      {
          case 1:
          cin>>data;
          node.insert(data);
          break;
          case 2:
            noindex=0;nodata=0;
            node.display(node.getRoot(),&noindex,&nodata);
            cout << noindex << " " << nodata << " ";
            node.displayroot(node.getRoot());
            break;
          case 3:
            f=false;break;
      }

        if(f==false)
            break;

  }


}