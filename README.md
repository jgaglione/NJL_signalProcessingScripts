#Guide for Signal Processing at ACCRE
###jethro.t.gaglione@vanderbilt.edu


Note: These instructions are under the assumption that signal events in the Delphes ROOT format have been produced.

1. The general analysis script supplied by Francesco is “lqAnalysis.C”. We require one of these scripts for each signal sample (e.g. if we run over  5 couplings and 10 masses, we will need 50 of these, per process). Edits have been made to this default script in order to prepare it for copying and adding information particular to each individual sample. This is named “lqAnalysisIncNJetSignal.C” in the “NJL_signalProcessingScripts” supplied on github. Here is a general summary of the changes:
   - The “process” and “sample” names have been changed to a generic term that will be used in search-and-replace in a script to be described later. 
   - “InputFile” path on line 362 may need to be changed depending on the sample. Madspin-decayed background samples will have the “decayed_1” path while others will not. Signal does not have this decayed path, so “decayed_1” has been removed accordingly.
   - Lines 383-385 will move the ROOT files produced to the specified directory. This needs to be updated depending on your path. You will need to create the directory yourself if it doesn’t exist.
2. The “generateSignalLQ_incNJet.py” script will take this default file and write what needs to be written for each individual signal sample. It takes as input the process directory names for the raw samples and outputs all the analysis scripts to a specified directory.
   - One must specify the list of process folders in the”processes” list at the beginning of the file. One must also adjust the full path where these are found in lines 9 and 11.
   - Lines 16-25 take care of extracting the cross-sections from the banner files in the sample directory. It’s worth noting that if the samples are jet-matched, one needs to adjust the parsing details. "Integrated weight (pb)" will need to be changed to “Matched Integrated weight (pb)” or similar to what is in the banner file. If this is changed, one also has to change the index on line 24 to match where the cross-section is on the whitespace-seperated line.
   - Line 50 will take the name of the default script you are using to write the individual scripts. In this case it’s “lqAnalysisIncNJetSignal.C”
   - Lines 59-63 control output names and creats directories to store analysis scripts for each process. These should be adjusted for paths etc. and it may be best to keep these in the Delphes directory, as this is where they will run. 
   - Launch with command “python3 generateSignalLQ_incNJet.py”
3. After the scripts are created, they must be submitted to tha ACCRE cluster via SLURM. This is handled by the “launchSignal.sh” script. This script needs the file “submitSignal.slurm”, which it well then edit according to the scripts to run and submit to the cluster.
   - One needs to add the name of the directories holding the scripts for each process in “launchSignal.sh”
   - In lines 1-8 of “submitSignal.slurm” one must specify the scheduler directive, i.e. how long one is requesting, the email you want any failed jobs to go, and the name of the output file you want to write to monitor the job and see standard output.
   - It is worth noting that at the moment of writing, this specific workflow was designed to be parallel from signal process to signal process, but not for signal sample to signal sample. I.e. this will run all the analysis scripts for one process linearly, and in parallel the analysis scripts for other processes. This was designed in this fashion when the analysis script only took a minute or two to run over each individual sample, though this will take longer if the analysis script is made more complex.
   - Launch with command “./launchSignal.sh” and analyzed ROOT files will write the directory specified. 
4. Once the analyzed ROOT files are available, they need to be run through the Higgs Combine tool. You’ll need to install CMSSW at ACCRE (Andrew Melo is a good resource if you’re not sure how to do this). I am using version 10_2_13. Then you will need to install the Higgs combine tool (We confirmed with Alfredo it is ok to install the CMSSW version). Matteo sent directions for this. 
5. The default card for Combine written by matteo is in the git repository named “combineCardDefSys.txt”. This will be used as the default to create one card for each sample. You will need to change the path on each channel and sample to the location they are. Make sure to leave the signal sample file name as “signalName” as this will be searched-and-replaced to produce all needed cards. 
   - The “writeCombineCards.sh” is in charge of launching the writing of all needed cards.You will need to create a directory where you want to store these, and then add that directory in “writeCombineCards.sh”. 
   - Launch card generation as “/writeCombineCards.sh.” This will run on your terminal and not the cluster. It should be quick.
6. Once the cards have all been written, you need to submit the Combine jobs to the cluster. This is done via the “submitCombine.slurm” where you will again need to adjust scheduler directives, and the path to your combine cards as well as the directory you want the Combine output in. You will need to create this directory. This will run all the cards in the cluster linearly as it only takes about 10 seconds per card to run at the moment of this writing. 
   - Launch combine via command “sbatch submitCombine.slurm”
   - Note: The naming conventions of the output Combine files will be used in further scripts, so you may want to keep this.
7. Once you have your output combine cards, the significance values need to be extracted and organized. You can use the “getSigFiles.py” script for this. 
   - You will need to specify the process name at the top of the file, as well as the paths of your Combine output files. 
   - Run as “python3 getSigFiles.py” and it will generate a space-seperated file with the format “mass coupling significance” with the name “NJL_sig_<process>.txt”
8. Finally, to plot the significance you can use the “makeContourPlot.C” to plot the sensitivity curves. You need to specify the “.txt” files you want to plot produced in the last step. The variable “contours[0]” defines what sigma you want the significance to be. 
