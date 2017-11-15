#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <list>
#include <iomanip>
#include <limits.h>
#include <utility>

using namespace std;

vector<vector<int> > graph; // graph
// vector<int> cost;
vector<pair<int, int> > heap_v;
vector<int> pre;


//declaration of functions
void execute(); // all executable lines
void prepareGraph(); // prepare the graph
void MST(); // Minimum spenning tree
void miniHeapify(const int i, int n); // miniHeapify the cost
pair<int, int> removeMini();
void printGraph(); // print graph using list
void printCost();
void printTree();

int main(int argc, char const *argv[]) {
  execute();
  return 0;
}

// implementation of functions

void execute() {
  srand(time(NULL));
  string input = "";
  bool sign = true;
  while (sign) {
    prepareGraph();
    MST();

    cout << "Press any other button to continue." << endl;
    cout << "Press e to Exit." << endl;
    cin >> input;
    if (input[0] == 'e' || input[0] == 'E') {
      sign = false;
    }

    while (cin.fail()) {
      cin.clear();
      cin.ignore();
      cin >> input;
      if (input[0] == 'e' || input[0] == 'E') {
         sign = false;
      }
    }
  }
  cout << "Successfully Exited" << endl;
}

// get graph prepared
void prepareGraph(){
  int size = rand()%6+5;
  graph = vector<vector<int> >(size, vector<int>(size));
  pre = vector<int>();

  for (int i = 0; i < size; i++) {
    pre.push_back(i);
    for (int j = 0; j <= i; j++) {
      if (i == j) {
        graph.at(i).at(j) = 0;
      } else {
        graph.at(i).at(j) = rand()%10+1;
        graph.at(j).at(i) = graph.at(i).at(j);
      }
    }
  }
  cout << "Graph.\n";

  printGraph();
}

// Minimum Spanning Tree
void MST() {
  heap_v = vector<pair<int, int> >(graph.size(), pair<int, int>(0, INT_MAX));
  int root = rand()%graph.size();
  for (int i = 0; i < heap_v.size(); i ++) {
    if (i == root) {
      heap_v.at(i).second = 0;
      pre.at(i) = -1;
    }
    heap_v.at(i).first = i;
  }
  for (int i = heap_v.size()/2; i >= 0; i--) {
    miniHeapify(i, heap_v.size());
  }
  printCost();
  printTree();
  // for each v not in the tree
  while (heap_v.size() != 0) {
    printCost();
    pair<int, int> v = removeMini();
    // for each v not in the tree
    for (int i = 0; i < heap_v.size(); i++) {
      int w = graph.at(heap_v.at(i).first).at(v.first);
      if(heap_v.at(i).second > w) {
        // update the shorest distance to the graph
        heap_v.at(i).second = w;
        pre.at(heap_v.at(i).first) = v.first;
        // decrease key

      }
    }
  }
  printTree();
}

// miniHeapify cost
void miniHeapify(const int i, int n) {
  int smallest = i;
  int left = i*2+1;
  int right = i*2+2;

  if (left < n  && heap_v.at(left).second < heap_v.at(i).second) {
    smallest = left;
  }
  if (right < n && heap_v.at(right).second < heap_v.at(smallest).second) {
    smallest = right;
  }
  if (smallest != i) {
    pair<int, int> temp = heap_v.at(i);
    heap_v.at(i) = heap_v.at(smallest);
    heap_v.at(smallest) = temp;
    miniHeapify(smallest, n);
  }
}

pair<int, int> removeMini() {
  if (heap_v.size() == 0) return make_pair<int, int>(0, -1);

  pair<int, int> mini = heap_v.at(0);
  heap_v.at(0) = heap_v.at(heap_v.size()-1);
  heap_v.pop_back();
  miniHeapify(0, heap_v.size());
  return mini;
}


// print the graph
void printGraph() {
  for (int i = 0; i < graph.size(); i++){
    for (int j = 0; j < graph.at(i).size(); j++) {
      cout << setw(3) << setfill(' ')<< graph.at(i).at(j);
    }
    cout << endl;
  }
}

// print cost
void printCost() {
  for (int i = 0; i < heap_v.size(); i++) {
    cout << "first: " << heap_v.at(i).first;
    cout << "  second: " << heap_v.at(i).second << endl;
  }
  cout << endl;
}

void printTree() {
  for (int i = 0; i < pre.size(); i++) {
    cout << "v: " << i << "    pre: "<< pre.at(i) << endl;
  }
}
