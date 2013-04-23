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
  double so_;
  Phrase(string s, double so) : phrase_(s), so_(so) {}
};

string intToStr (int x) {
  stringstream ss;
  ss << x;
  return ss.str();
}

void read_phrases (vector<Phrase>& phrases) {
  ifstream fin("words.sentiment");
  string word1, word2;
  double so;
  while (fin >> word1 >> word2 >> so) {
    phrases.push_back(Phrase(word1 + " " + word2, so));
  }
}

int main ()
{
  // this method reads in all phrases with their 
  // semantic orientation from an external file
  vector<Phrase> phrases;
  read_phrases(phrases);

  ifstream fin("dir.txt");
  string dir;
  string forumName;
  int numForums;
  fin >> numForums;
  for (int K = 0; K < numForums; K++) {
    fin >> forumName;
    cerr << "Forum: " << forumName << ". " << K << "/" << numForums << endl;
    int numTopics;
    if (fin >> numTopics) {
      if (numTopics != 0) {
        for (int k = 0; k < numTopics; k++) {
          cerr << "Topic: " << k << "/" << numTopics << endl;
          int numGood = 0;
          int numBad = 0;
          double totalSO = 0;
          int numComments;
          fin >> numComments;
          if (numComments != 0) {
            for (int i = 0; i < numComments; i++) {
              string filename("topics/" + forumName + "/" + intToStr(k) + "/" + intToStr(i));
              ifstream topic(filename.c_str());
              stringstream ss;
              string line;
              while (getline(topic, line)) {
                ss << line;
              }
              string text = ss.str();

              // if only one of them is found then go through all
              // phrases and try to find them here
              double counter = 0.0;
              bool foundSomething = false;
              for (vector<Phrase>::iterator it = phrases.begin();
                  it != phrases.end();
                  it++) {
                if (text.find(it->phrase_) != string::npos) {
                  foundSomething = true;
                  //cout << "Phrase found: " << it->phrase_ <<  " " << it->so_ << endl;
                  counter += it->so_;
                  totalSO += it->so_;
                }
              }
              if (foundSomething) {
                /*
                cout << "Here is the text: " << endl;
                cout << text << endl;
                cout << "And the semantic orientation was: " << counter << endl;
                cout << " ============== \n\n";
                */
              }
              if (counter > 0.0)
                ++numGood;
              else if (counter < 0.0)
                ++numBad;

              topic.close();
            }
            cout << "The semantic orientation of topic ";
            cout << k << " in forum " << K << " which has " << numComments << " comments is: ";
            cout << totalSO << ". There were " << numGood << " good comments and";
            cout << " " << numBad << " bad comments." << endl;
          }
          else {
            //cout << "Topic " << k << " has no comments" << endl;
          }
        }
      }
      else {
        //cout << "Forum " << K << " has no topics" << endl;
      }
    }
  }
  fin.close();
}
