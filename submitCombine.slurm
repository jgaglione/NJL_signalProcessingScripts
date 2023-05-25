#!/bin/bash
#SBATCH --mail-user=jethro.t.gaglione@vanderbilt.edu
#SBATCH --mail-type=FAIL
#SBATCH --ntasks=1
#SBATCH --time=1-00:00:00 
#SBATCH --job-name=submitCombine
#SBATCH --mem-per-cpu=8G
#SBATCH --output=submitCombine_incNjet.out

source /cvmfs/cms.cern.ch/cmsset_default.sh
cmsenv
for file in ./signalCardsIncNJet/*; do combine -M Significance ${file} -t -1 --expectSignal=1 &> ./combinedOut_incNJet/result_${file##*/}; done

echo "Done."
