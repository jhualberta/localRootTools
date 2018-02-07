#dump db from files, print values from dictionary
#NOTE: change "true" to "True", remove the un-formated items
#/usr/bin/python
import sys,os,glob,fnmatch
import subprocess
import ast
path=os.getcwd()
file_list = os.listdir(path)
fList = open('info.dat')
runID = []
runfile = []
processfile = []
db = []
countfile = 0
for i in fList:
  db.append(ast.literal_eval(i.rstrip()))
  countfile = countfile+1

for j in range(0,len(db)): 
  runID = db[j]["run_range"][0]
  position_pivot = db[j]["position_pivot"]
  err_position = db[j]["err_position"]
  position = db[j]["position"]
  #print str(runID)+" "+str(position_pivot[0])+", "+str(position_pivot[1])+", "+str(position_pivot[2])
  print str(err_position[0])+", "+str(err_position[1])+", "+str(err_position[2])
  #print str(position[0])+", "+str(position[1])+", "+str(position[2])
