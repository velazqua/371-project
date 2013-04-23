#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct A {
  int o_;
  string s1_;
  string s2_;
  A (int o, string s1, string s2) : o_(o), s1_(s1), s2_(s2) {}
};

bool operator < (A const& a, A const& b) {
  if (a.o_ != b.o_)
    return a.o_ > b.o_;
  else
    return a.s1_.compare(b.s1_) || a.s2_.compare(b.s2_);
}

bool is_good(string word) {
  for(string::iterator it = word.begin();
      it != word.end();
      it++) {
    if (!((*it >= 65 && *it <= 90) || 
        (*it >= 97 && *it <= 122) ||
        (*it == 39)))
      return false;
  }
  return true;
}

int main ()
{
  ifstream fin("words.out");
  ofstream fout("words.sorted");
  string line;
  vector<A> stuff;
  while (getline(fin, line)) {
    stringstream ss(line);
    int n;
    string s1, s2;
    ss >> s1 >> s2 >> n;
    if (n > 3 && is_good(s1) && is_good(s2))
      stuff.push_back(A(n, s1, s2));
  }
  sort(stuff.begin(), stuff.end());
  for(vector<A>::iterator it = stuff.begin();
      it != stuff.end();
      it++) {
    fout << it->s1_ << " " << it->s2_ << " " << it->o_ << endl;
  }
  fin.close();
  fout.close();
}
