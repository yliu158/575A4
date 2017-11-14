#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <iomanip>

using namespace std;

vector<vector<int> > graph; // graph


//declaration of functions
void execute(); // all executable lines
void prepareGraph(); // prepare the graph
void printGraph(); // print graph using list

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

  for (int i = 0; i < size; i++) {
    for (int j = 0; j <= i; j++) {
      if (i == j) {
        graph.at(i).at(j) = 0;
      } else {
        graph.at(i).at(j) = rand()%10+1;
        graph.at(j).at(i) = graph.at(i).at(j);
      }
    }
  }
  printGraph();
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
