from xml.dom import minidom
import nltk
import sys
import os
import collections

sys.stdout = os.fdopen(sys.stdout.fileno(), 'w', 0)
def extract_phrases(text):
  phrases = []
  for i in xrange(0, len(text)-2):
    w1 = text[i][1]
    w2 = text[i+1][1]
    w3 = text[i+2][1]
    if w1 == 'JJ' and w2 in ["NN","NNS"]\
    or w1 in ['RB','RBR','RBS'] and w2 == 'JJ' and w3 not in ['NN','NNS']\
    or w1 == 'JJ' and w2 == 'JJ' and w3 not in ['NN','NNS']\
    or w1 in ['NN','NNS'] and w2 == 'JJ' and w3 not in ['NN','NNS']\
    or w1 in ['RB','RBR','RBS'] and w2 in ['VB','VBD','VBN','VBG']:
      phrases.append(tuple([text[i][0], text[i+1][0]]))
  return phrases

filename = "dir.txt" # change to xml-files.txt
fin = open(filename, "r")
numForums = int(fin.readline())

hot = 0
cold = 0
positiveWords = ["hot", "warm", "good", "excellent", "fantastic"]
negativeWords = ["cold", "terrible", "dead", "pathetic", "miserable", "bad", "awful", "painful", "horrid", "mediocre", "worst", "worse"]
allPhrases = {}

for i in xrange(numForums):
  forumName = fin.readline().rstrip()
  print >> sys.stderr, "Forum: " + str(i) + "/" + str(numForums)
  numTopics = int(fin.readline())
  for j in xrange(numTopics):
    print >> sys.stderr, str(j) + "/" + str(numTopics)
    numComments = int(fin.readline())
    for k in xrange(numComments):
      commentFile = open("topics/"+forumName+"/"+str(j)+"/"+str(k), "r")
      comment = " ".join([x.rstrip() for x in commentFile.readlines()])
      commentFile.close()
      tokens = [x.lower() for x in nltk.word_tokenize(comment)]
      for w in tokens:
        if w in positiveWords:
          hot += 1
        elif w in negativeWords:
          cold += 1
      tagged = nltk.pos_tag(tokens)
      phrases = extract_phrases(tagged)
      for p in phrases:
        allPhrases[(p)] = allPhrases.get((p), 0) + 1

print "There are " + str(len(allPhrases)) + " items in the dict."

for key, value in allPhrases.iteritems():
  try:
    print str(key[0]) + " " + str(key[1]) + " " + str(value)
  except:
    continue
print "NUM OF HOT:  " + str(hot)
print "NUM OF COLD: " + str(cold)
