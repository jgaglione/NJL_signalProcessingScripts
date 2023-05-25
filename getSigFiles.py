# Get's cross-sections from a list of event directories, must be rean in a process directory 

import os
import glob

processes=["NJL_ee_0123j_pi53", "NJL_ee_0123j_pid23"]

for process in processes:
  f = open("significance_" + process + ".txt",'w')
  outFile = "NJL_sig_" + process + ".txt"
  for runFile in os.listdir("/home/gaglijt1/CMSSW_10_2_13/src/combinedOut_incNJet/"):
     # get significance
     if process in runFile:
       bannerPath=glob.glob("/home/gaglijt1/CMSSW_10_2_13/src/combinedOut_incNJet/" + runFile )
       with open(bannerPath[0],"r") as g:
           xLine=[line for line in g if "Significance:" in line]
           if xLine:
               xLineSplit = xLine[0].split()
           elif "ap" in runFile:
               noAP = noAP+1
               print("No Significance found")
               print(runFile)
           else:
               noPP = noPP+1
               print("No Significance found")
               print(runFile)
           sig = float(xLineSplit[1])
           print(sig)
       if "ap" in process:
         mass = runFile.split("_")[6]
         gy = runFile.split("_")[7]
       else:
         mass =runFile.split("_")[5]
         gy = runFile.split("_")[6]
       
       mass = mass[1:]
       #get and set input/output file names
       coup = ""
       
       if "0p5" in gy:
         coup = '0.5'
       elif "1p0" in gy:
         coup = '1.0'
       elif "1p5" in gy:
         coup = '1.5'
       elif "2p0" in gy:
         coup = '2.0'
       elif "2p5" in gy:
         coup = '2.5'

       f.write(str(mass) + " " + str(coup) + " " + str(sig) + "\n")
  f.close()  
