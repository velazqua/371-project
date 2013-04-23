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

struct Phrase {
  string phrase_;
  int num_occurrances_;
  int pos_hits_;
  int neg_hits_;

  Phrase(string s, int o) : phrase_(s),
    num_occurrances_(o), pos_hits_(0), neg_hits_(0) {}
};



string intToStr (int x) {
  stringstream ss;
  ss << x;
  return ss.str();
}

void read_hot_and_cold_words (vector<string>& hotWords, vector<string>& coldWords){
  ifstream hot_words("hot_words.txt");
  ifstream cold_words("cold_words.txt");
  string line;
  while (hot_words >> line) {
    hotWords.push_back(line);
  }
  while (cold_words >> line) {
    coldWords.push_back(line);
  }
  hot_words.close();
  cold_words.close();
}

void read_phrases (vector<Phrase>& phrases) {
  ifstream fin("words.sorted");
  string word1, word2;
  int amount;
  while (fin >> word1 >> word2 >> amount) {
    phrases.push_back(Phrase(word1 + " " + word2, amount));
  }
}

int main ()
{
  // this method reads in all hot words and cold words
  // from an external file
  vector<string> hotWords;
  vector<string> coldWords;
  read_hot_and_cold_words(hotWords, coldWords);

  // this method reads in all phrases with occurrances
  // from an external file
  vector<Phrase> phrases;
  read_phrases(phrases);

  ifstream fin("dir.txt");
  string dir;
  int numTopics;
  int numForums;
  fin >> numForums;
  for (int K = 0; K < numForums; K++) {
    string forumName;
    fin >> forumName;
    cerr << "forum: " << forumName << endl;
    if (fin >> numTopics) {
      if (numTopics != 0) {
        for (int i = 0; i < numTopics; i++) {
          cerr << "topic: " << i << "/" << numTopics << endl;
          int numComments;
          fin >> numComments;
          for (int j = 0; j < numComments; j++) {
            string filename("topics/" + forumName + "/" + intToStr(i) + "/" + intToStr(j));
            ifstream topic(filename.c_str());
            stringstream ss;
            string line;
            while (getline(topic, line)) {
              ss << line;
            }
            string text = ss.str();
#if 0
            cout << "======== TEXT ============" << endl;
            cout << text << endl;
            cout << "==========================\n" << endl;
#endif

            // find any instances of a hot word or cold word
            bool hotFound = false, coldFound = false;
            for (vector<string>::iterator it = hotWords.begin();
                it != hotWords.end();
                it++) {
              if (text.find(*it) != string::npos) {
                hotFound = true;
                break;
              }
            }

            for (vector<string>::iterator it = coldWords.begin();
                it != coldWords.end();
                it++) {
              if (text.find(*it) != string::npos) {
                coldFound = true;
                break;
              }
            }
     
            // if both are found, then ignore this post
            if ((hotFound && coldFound) || (!hotFound && !coldFound))
              continue;

            // if only one of them is found then go through all
            // phrases and try to find them here
            for (vector<Phrase>::iterator it = phrases.begin();
                it != phrases.end();
                it++) {
              if (text.find(it->phrase_) != string::npos) {
                if (hotFound) 
                  it->pos_hits_++;
                else
                  it->neg_hits_++;
              }
            }
            topic.close();
          }
        }
      }
    }
  }
  ofstream fout("phrase_scores.txt");
  for (vector<Phrase>::iterator it = phrases.begin();
      it != phrases.end();
      it++) {
    fout << it->phrase_ << " " << it->num_occurrances_ << " ";
    fout << it->pos_hits_ << " " << it->neg_hits_ << endl;
  }
  fout.close();
  fin.close();
}
