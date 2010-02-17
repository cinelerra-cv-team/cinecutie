#!/bin/bash
#THEME
THEME=themepink
THEMENAME=PinkLady
THFUNC=PINKLADY
BGCOLOR=d40055
BBCOLOR=ff277e
TEXT=ff80b2
#SVG
INBGCOLOR=4d4d4d
INBBCOLOR=333333
INTEXT=bfbfbf
INICON=cccccc
OUTICON=ffd5e5
INCHECKED=ff6600
OUTCHECKED=0000ff
INBORDER=666666
OUTBORDER=70002d
INMISC=803300
OUTMISC=660080
INDBUTTON=989898
OUTDBUTTON=78216f
INBASE=ff0000
OUTBASE=0000ff
rm -rf ../themes/$THEME
cp -a MODEL ../themes/$THEME
cd ../themes/$THEME

for i in `ls`;
	do
	if [ ! -d $i ]
		then
		sed -i s/THEME/$THEME/g $i
		sed -i s/THEMENAME/$THEMENAME/g $i
		sed -i s/THFUNC/$THFUNC/g $i
		sed -i s/BGCOLOR/$BGCOLOR/g $i
		sed -i s/BBCOLOR/$BBCOLOR/g $i
		sed -i s/TEXT/$TEXT/g $i
	fi
done
mv THEME.C $THEME.C
mv THEME.h $THEME.h
mv .deps/THEME.Plo .deps/$THEME.Plo

cd data
for i in `ls | grep svg`
	do
	sed -i /\#/s/$INBGCOLOR/$BGCOLOR/g $i
	sed -i /\#/s/$INBBCOLOR/$BBCOLOR/g $i
	sed -i /\#/s/$INTEXT/$TEXT/g $i
	sed -i /\#/s/$INICON/$OUTICON/g $i
	sed -i /\#/s/$INCHECKED/$OUTCHECKED/g $i
	sed -i /\#/s/$INBORDER/$OUTBORDER/g $i
	sed -i /\#/s/$INMISC/$OUTMISC/g $i
	sed -i /\#/s/$INDBUTTON/$OUTDBUTTON/g $i
	sed -i /\#/s/$INBASE/$OUTBASE/g $i
done

#cd ../../
#rm -rf ../../plugins/$THEME
#cp -a $THEME ../../plugins

#make -C ../../plugins/$THEME
#sudo make -C ../../plugins/$THEME install


