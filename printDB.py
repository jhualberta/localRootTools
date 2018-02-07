#/usr/bin/python
import sys,os,glob,fnmatch
import subprocess
path=os.getcwd()
file_list = os.listdir(path)
fList = open('dbList.dat')
runID = []
runfile = []
processfile = []
countfile = 0
for i in fList:
  runfile.append(i.rstrip())
  runID.append(i[23:29])
  countfile = countfile+1
print runID

fInfo = open('info.dat','w+')
for j in range(1,countfile+1):
  filename = runfile[j-1] 
  ftemp = open(filename)
  flist=ftemp.readlines()
  fInfo.writelines(flist)
  ftemp.close()

fInfo.close()
