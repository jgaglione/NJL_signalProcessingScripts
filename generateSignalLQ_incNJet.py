# Get's cross-sections from a list of event directories, must be rean in a process directory 

import os
import glob

processes=["NJL_ee_1J_ap_pid23_ptjmin10_Events","NJL_ee_1J_ap_pi53_ptjmin10_Events"]

for process in processes: 
  for runFile in os.listdir("/mnt/ceph/home/gaglijt1/%s" % process):
     
     # get cross section
     bannerPath=glob.glob("/mnt/ceph/home/gaglijt1/" + process + "/" + runFile + "/" + "*_tag_1_banner.txt")
     if not bannerPath:
       continue
     print(bannerPath)
     with open(bannerPath[0],"r") as f:
#         xLine=[line for line in f if "Matched Integrated weight (pb)" in line]
         xLine=[line for line in f if "Integrated weight (pb)" in line]
         if xLine:
             xLineSplit = xLine[0].split()
         else:
             print("No Xsec found")
#         xSec = float(xLineSplit[6])
         xSec = float(xLineSplit[5])
         print(xSec)
  
     #get and set input/output file names
     runDir = runFile      #this replaces "runFolder" in script
     splitRunFile = runFile.split("_")
     splitProcess = process.split("_")
     coup = ""
     for x in splitRunFile:
        if x == '.49':
           coup = '0p5'
        elif x == '1.00':
           coup = '1p0'
        elif x == '1.48':
           coup = '1p5'
        elif x == '1.98':
           coup = '2p0'
        elif x == '2.49':
           coup = '2p5'
  
     if "ap" in process:
       outFile = splitProcess[0] + "_" + splitProcess[1] + "_" + splitProcess[2] + "_" + splitProcess[3] + "_" + splitProcess[4] + "_" + splitRunFile[1] + "_gy" + coup
     else:
       outFile = splitProcess[0] + "_" + splitProcess[1] + "_" + splitProcess[2] + "_" + splitProcess[3] +  "_" + splitRunFile[1] + "_gy" + coup
     print(runDir)
  
     f = open("lqAnalysisIncNJetSignal.C",'r')
     filedata = f.read()
     f.close()
  
     newdata = filedata.replace("outputName", outFile)
     newdata = newdata.replace("processFolder", process)
     newdata = newdata.replace("runFolder", runDir)
     newdata = newdata.replace("xSecValue", str(xSec))
     newdata = newdata.replace("scriptName", str(outFile + "_lqScript"))
     if not os.path.exists(process + "_lqScripts_incNJet"): 
       os.mkdir(process + "_lqScripts_incNJet")
     f = open(process + "_lqScripts_incNJet/" + outFile + "_lqScript.C" ,'w')
     f.write(newdata)
     f.close()   
   
   





