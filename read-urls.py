from xml.dom import minidom
import nltk
import sys
import os
import collections

sys.stdout = os.fdopen(sys.stdout.fileno(), 'w', 0)
filename = "xml-files.txt" # change to xml-files.txt 
fin = open(filename, "r")
allFiles = [x.rstrip() for x in fin.readlines()]
#print >> sys.stderr, "There are " + str(len(allFiles)) + " files."
K = 0
for thisFile in allFiles:
  #print >> sys.stderr, "====== Reading " + str(thisFile) + " =========="
  #print >> sys.stderr, "====== " + str(K) + "/" + str(len(allFiles)) + " =========="
  xmldoc = minidom.parse("xml-files/"+thisFile)
  itemlist = xmldoc.getElementsByTagName('topic')
  i = 0
  for s in itemlist:
    if i < -15:
      break
    directory = "topics/" + thisFile + "/" + str(i)
    if not os.path.exists(directory):
      os.makedirs(directory)
    comments = s.getElementsByTagName('url')
    j = 0
    for comment in comments:
      for word in comment.childNodes:
        try:
          print K, i, word.data.lower()
          f.close()
          j = j + 1
        except:
          continue
    i = i + 1
    #print >> sys.stderr, str(i) + "/" + str(len(itemlist)) + " => " + str(float(i)/len(itemlist)*100) + "%"
  K = K + 1
