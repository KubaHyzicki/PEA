#!/usr/bin/python3
import os
import sys
from random import randint

filename='testDataX.txt'
projectDir='/home/kuba/Qt/build-PEA-Desktop_Qt_5_7_0_GCC_64bit-Profile'

filePath='{}/{}'.format(projectDir,filename)
cities=int(sys.argv[1])
maxWeight=10

os.system('echo "{}" > {}'.format(cities,filePath))

for lineNr in range(0,cities):
  line=''
  for i in range(0,cities):
    if i==lineNr:
      weight=0
    else:
      weight=randint(1,maxWeight)
    line='{}{} '.format(line,weight)
  os.system('echo "{}" >> {}'.format(line,filePath))