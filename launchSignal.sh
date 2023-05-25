
for proc in NJL_ee_1J_ap_pi53_ptjmin10_Events_lqScripts_incNJet NJL_ee_1J_ap_pid23_ptjmin10_Events_lqScripts_incNJet 
do
        echo "copying and submitting ${proc}"
        cp ./submitSignal.slurm ./submitSignal${proc}.slurm
	sed -i "s/MYPROCESS/${proc}/" ./submitSignal${proc}.slurm
	sbatch ./submitSignal${proc}.slurm

done
