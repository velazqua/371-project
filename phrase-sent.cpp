#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <string>
#include <cmath>
#include <set>

using namespace std;

// These numbers change often. Remember to update them!
#define NUM_POS_WORDS 26693.0
#define NUM_NEG_WORDS 9659.0

struct Phrase {
  string s1_;
  string s2_;
  double sentiment_;
  int pos_;
  int neg_;
  Phrase (string s1, string s2, double s, int pos, int neg) : s1_(s1), s2_(s2), sentiment_(s), pos_(pos), neg_(neg) {}
};

bool operator < (Phrase const& A, Phrase const& B) {
  if (A.sentiment_ != B.sentiment_)
    return A.sentiment_ > B.sentiment_;
  else
    return A.s1_.compare(B.s1_) || A.s2_.compare(B.s2_);
}

double SO (int pos, int neg) {
  return log2((double(pos) * NUM_NEG_WORDS)/(neg * NUM_POS_WORDS));
}

int main ()
{
  ifstream phrases("phrase_scores.txt");
  ofstream sentiment("words.sentiment");
  string word, word2;
  int val, pos, neg;
  set<Phrase> s;
  while (phrases >> word >> word2 >> val >> pos >> neg) {
    if (pos > 0 && neg > 0) {
      double so = SO(pos, neg);
      /*
      if (!word.compare("n't") || !word.compare("not"))
        so *= -1;
      */
      s.insert(Phrase(word, word2, so, pos, neg));
    }
  }

  for (set<Phrase>::iterator it = s.begin();
      it != s.end();
      it++) {
    sentiment << it->s1_ << " " << it->s2_ << " " << it->sentiment_ << endl; 
  }

  phrases.close();
  sentiment.close();
}
