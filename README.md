# G4EXAMPLE

This is a Geant4 example for generating a neutron energy spectrum of SiC detector.

Using guide

open shell in Ubuntu system

mkdir example

cd example

git clone git@github.com:lunse/G4EXAMPLE.git 

cd G4EXAMPLE

mkdir build

cd build

cmake ../1

make -j 12
#12 is the number of your cpu core 

./beam 0.0253.in 12
#12 is the number of your cpu core 

#wait till program stop running

root plotHisto.C

#get root histogram









