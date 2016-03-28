#!/bin/bash

if [ $# -lt 2 ]
	then
		echo "build-tool.sh <version-num> <counter>"
		echo "Sample: ./build-tool.sh 13 000"
		exit 1
fi

curPath=`pwd`
date=`date +%y%m%d`
versionMajor=0
versionMinor=$1
update=_update_V$versionMajor\_$versionMinor\_$2\_$date

outFile=HB-UW-Mot-BL1$update
outPath=../Firmware-Release
fullFile=$outPath/$outFile

if [ $# -lt 3 ]
	then
		# hexfile to eq3
		./hex2eq3.php --inFile ../Firmware-Src/Release/HB-UW-Mot-BL1.hex --spmPageSize 128 --outFormat eq3 --outFile $fullFile.eq3 --withCrcCheck
		
		cp $fullFile.eq3 ./

		rm -rf ../Firmware-Release/tmp
		mkdir ../Firmware-Release/tmp
		cp $fullFile.eq3 ../Firmware-Release/tmp
		cp ../Firmware-Src/ccu-changelog.txt ../Firmware-Release/tmp/changelog.txt
		
		echo "TypeCode=61698"                               > ../Firmware-Release/tmp/info
		echo "Name=HB-UW-Mot-BL1"                          >> ../Firmware-Release/tmp/info
		echo "CCUFirmwareVersionMin=2.9.0"                 >> ../Firmware-Release/tmp/info
		echo "FirmwareVersion=$versionMajor.$versionMinor" >> ../Firmware-Release/tmp/info
		cd $outPath/tmp
		tar -H gnu -zcvf $outFile.tgz ./*
		cd $curPath
		mv $outPath/tmp/$outFile.tgz $outPath
		
		rm -rf ../Firmware-Release/tmp
		mkdir ../Firmware-Release/tmp

		echo "TypeCode=61698"                               > ../Firmware-Release/tmp/info
		echo "Name=HB-UW-Mot-BL1"                          >> ../Firmware-Release/tmp/info
		echo "CCUFirmwareVersionMin=2.9.0"                 >> ../Firmware-Release/tmp/info
		echo "FirmwareVersion=$versionMajor.$versionMinor" >> ../Firmware-Release/tmp/info
		cd $outPath/tmp

	else
		cp ../Firmware-Src/Release/HB-UW-Mot-BL1.hex $outFile.hex
fi

