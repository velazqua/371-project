#include <iostream>
#include <fstream>

using namespace std;

int main ()
{
  ifstream fin("phrase_scores.txt");
  ofstream fout("phrase_scores.txt2");
  string w1, w2;
  int total, pos, neg;
  while (fin >> w1 >> w2 >> total >> pos >> neg) {
    if (pos + neg != 0) {
      fout << w1 << " " << w2 << " " << total;
      fout << " " << pos << " " << neg << endl;
    }
  }
  fin.close();
  fout.close();
}
