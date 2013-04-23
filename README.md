File descriptions:
  - read-all.py -> reads xml and organizes all comments to files in respective directories
  - read-xml.py -> reads all comments and finds all phrases
  - cold_words.txt -> list of all negative words in our dictionary
  - hot_words.txt -> list of all positive words in our dictionary
  - dir.txt -> lists the number of comments on each thread/discussion topic
  - phrase_scores.txt -> gives phrase, its number of hits, its number of positive hits and number of negative hits
  - cpp-hits-near.cpp -> calculates everything in phrase_scores.txt
  - hits-near.py -> replaced with faster cpp-hits-near.cpp
  - phrase-sent.cpp -> given the data on phrase_scores.txt, it calculates the sentiment of each phrase
  - sorting.cpp -> deletes invalid phrases, phrases that do not occur too often and sorts all phrases to words.sorted
  - determineSentiment.cpp -> determines the sentiment of each comment and thread 

How to use:
  - run read-all.py to read the xml contents for later use
    - python read-all.py
  - run read-xml.py to extract all phrases from the xml file
    - python read-xml.py | tee words.out
  - run sorting.cpp to sort all phrases from words.out. This will
  produce the 'words.sorted' file
    - g++ sorting.cpp; ./a.out
  - run cpp-hits-near.cpp to count occurrances of each phrase
  plus the number of hot and cold hits. This will produce a 
  'phrase_scores.txt' file
    - g++ cpp-hits-near.cpp; ./a.out
  - run phrase-sent.cpp to calculate the sentiment of each phrase
  This will generate a 'words.sentiment' file
    - g++ phrase-sent.cpp; ./a.out
  - run determineSentiment.cpp to calculate the sentiment of
  each comment and threads
    - g++ determineSentiment.cpp; ./a.out

