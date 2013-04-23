#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <map>
#include <utility>
#include <ctime>
#include <cstdlib>

using namespace std;

int main ()
{
  ifstream fin("selected-topics.txt");
  ifstream fin2("output.txt");
  int forum, topic;
  map< pair<int,int>, pair<char, char> > algo;
  char SO, CO;
  while (fin >> forum >> topic >> SO >> CO)
    algo.insert(make_pair(make_pair(forum, topic), make_pair(SO, CO)));
  fin.close();
  
  char D;
  int SO_MATCH = 0, CO_MATCH = 0;
  int POS = 57;
  int NEG = 43;
  int pos = 0;
  int neg = 0;
  while (fin2 >> forum >> topic >> D) {
    pair<char, char> result = algo[make_pair(forum, topic)];
    if (result.first == D) {
      SO_MATCH++;
    }
    if (result.second == D) {
      CO_MATCH++;
      if (D == 'P')
        pos++;
      else
        neg++;
    }
    else
      cout << "No match for CO: " << forum << " " << topic << " " << result.second << " " << D << endl;
    //else
    //  cout << "No match for CO: " << forum << " " << topic << " " << result.second << " " << D << endl;
  }
  cout << "FINAL RESULTS:" << endl;
  cout << "Semantic Orientation measure: " << SO_MATCH << "/" << 100 << endl;
  cout << "Simple counter measure: " << CO_MATCH << "/" << 100 << endl;
  cout << "Positive matches: " << pos << "/" << POS << ". Negative: " << neg << "/" << NEG << endl;
  fin2.close();
}
