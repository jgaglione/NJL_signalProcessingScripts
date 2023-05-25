for file in /mnt/ceph/home/gaglijt1/NJL_allRootFiles_wCuts_v2/*gy*.root
do
  echo ${file##*/}
  cp ./combineCardDefSys.txt ./signalCardsIncNJet/${file##*/}_combined.txt
  sed -i "s/signalName/${file##*/}/" ./signalCardsIncNJet/${file##*/}_combined.txt
done
