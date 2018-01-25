#/usr/bin/python
import sys,os
import collections 
path=os.getcwd()
file_list = os.listdir(path)
fList = open('N16SimuList.dat')
processfile = []
count = 0
runList = []
rootfileList = []


for line in fList:
 processfile.append(line.rstrip())
 count = count+1
 run = line[line.index('r10')+1:line.index('r10')+1+6] 
 runList.append(run)
 rootfileList.append(line)

counter = collections.Counter(runList)
mainrun = counter.keys()
repeat = counter.values()

countSplit = len(mainrun)

newfileList = []
countNewFile = 0 
iterflag = 0
for val in repeat:
  f = open("processList"+str(countNewFile+1)+".txt",'w')
  for i in range(iterflag, iterflag+val):
    f.write(rootfileList[i])
  f.close()
  iterflag = iterflag + val 
  countNewFile = countNewFile+1

if countSplit != countNewFile:
 print "check data, something wrong!"

print str(count)+" files in total"
print "splitted files "+str(countNewFile)

