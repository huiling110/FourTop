#!/bin/bash


#for filename in /publicfs/cms/data/TopQuark/FourTop/v002/mc/2016/; do
for filename in /publicfs/cms/data/TopQuark/FourTop/v002/mc/2016/*root; do
#    if [  "${filename##*.}"x == "root"x ]; then
#        root -b -q 'GetEntry.cpp("${filename}")'
#    fi

#    echo ${filename}
    prefix="/publicfs/cms/data/TopQuark/FourTop/v002/mc/2016/"
    filename="${filename#$prefix}"
#    echo ${filename}
#    if [ "${filename}" == "TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root" ]; then
#        echo ${filename}
#        echo "${filename}"
#        root -b -q "GetEntry.cpp("${filename}")"
#        root -b -q "GetEntry.cpp(\"${filename}\")"
#    fi
     root -b -q "GetEntry.cpp(\"${filename}\")"
done
