#!/usr/bin/env bash
mkdir -p out/
if [ -n "$1" ] && [ -f "$1" ]; then
gs -q -dNOPAUSE -dBATCH -P- -dSAFER -sDEVICE=pdfwrite -sOutputFile=${1/.pdf/-Q1.pdf} -c "[/CropBox [0 298 421 842] /PAGES pdfmark" -f $1 #lefttop
gs -q -dNOPAUSE -dBATCH -P- -dSAFER -sDEVICE=pdfwrite -sOutputFile=${1/.pdf/-Q2.pdf} -c "[/CropBox [421 298 840 595] /PAGES pdfmark" -f $1 #rightup
gs -q -dNOPAUSE -dBATCH -P- -dSAFER -sDEVICE=pdfwrite -sOutputFile=${1/.pdf/-Q3.pdf} -c "[/CropBox [0 0 421 298] /PAGES pdfmark" -f $1 #leftbot
gs -q -dNOPAUSE -dBATCH -P- -dSAFER -sDEVICE=pdfwrite -sOutputFile=${1/.pdf/-Q4.pdf} -c "[/CropBox [421 0 840 298] /PAGES pdfmark" -f $1 #rightbot
#pdftk ${1/.pdf/-Q1.pdf} burst output page_%02d_1.pdf
#pdftk ${1/.pdf/-Q2.pdf} burst output page_%02d_2.pdf
#pdftk ${1/.pdf/-Q3.pdf} burst output page_%02d_3.pdf
#pdftk ${1/.pdf/-Q4.pdf} burst output page_%02d_4.pdf

stapler split ${1/.pdf/-Q1.pdf}
stapler split ${1/.pdf/-Q2.pdf}
stapler split ${1/.pdf/-Q3.pdf}
stapler split ${1/.pdf/-Q4.pdf}

rm ${1/.pdf/-Q1.pdf}
rm ${1/.pdf/-Q2.pdf}
rm ${1/.pdf/-Q3.pdf}
rm ${1/.pdf/-Q4.pdf}

COUNTER=0
for f in *-Q1_*.pdf; do 
 mv $f ${COUNTER}_$f
 let COUNTER=COUNTER+4
done

COUNTER=1
for f in *-Q2_*.pdf; do 
 mv $f ${COUNTER}_$f
 let COUNTER=COUNTER+4
done

COUNTER=2
for f in *-Q3_*.pdf; do 
 mv $f ${COUNTER}_$f
 let COUNTER=COUNTER+4
done

COUNTER=3
for f in *-Q4_*.pdf; do 
 mv $f ${COUNTER}_$f
 let COUNTER=COUNTER+4
done

a="";
for f in `ls *${1/.pdf/-Q}* | sort -g`; do
 a="$a $f"
done

stapler cat $a ${1/.pdf/1x1.pdf}

#a=""; for f in page_*.pdf; do rm $f; done;
#rm ${1/.pdf/-Q1.pdf} ${1/.pdf/-Q2.pdf} ${1/.pdf/-Q3.pdf} ${1/.pdf/-Q4.pdf}

rm *${1/.pdf/-Q}*

else
	echo "No input file"
fi


