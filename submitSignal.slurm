#!/bin/bash
#SBATCH --mail-user=jethro.t.gaglione@vanderbilt.edu
#SBATCH --mail-type=FAIL
#SBATCH --ntasks=1
#SBATCH --time=3-00:00:00 
#SBATCH --job-name=batch_MYPROCESS
#SBATCH --mem-per-cpu=8G
#SBATCH --output=batch_MYPROCESS.out

module load GCC/6.4.0-2.28
module load OpenMPI/2.1.1
module load Intel/2017.4.196
module load IntelMPI/2017.3.196
module load ROOT/6.10.08-Python-2.7.14


for file in MYPROCESS/*; do root -l -q $file; done

echo "Done."
