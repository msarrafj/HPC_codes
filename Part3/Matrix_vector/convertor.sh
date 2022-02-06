#! /bin/bash
cat resultVEC.dat | cut -f 4 | awk '
{ 
    for (i=1; i<=NF; i++)  {
        a[NR,i] = $i
    }
}
NF>p { p = NF }
END {    
    for(j=1; j<=p; j++) {
        str=a[1,j]
        for(i=2; i<=NR; i++){
            str=str" "a[i,j];
        }
        print str
    }
}' | sed 's/ExeTime/\'$'\n/g'> convertedVEC.dat
cat resultVEC.dat | cut -f 7-8 | sed -r '/^\s*$/d' | sed '/dramPower/d'> energyVEC.dat

cat resultVEC.dat | cut -f 5 > TIMEVEC.dat


cat resultMKL.dat | cut -f 4 | awk '
{ 
    for (i=1; i<=NF; i++)  {
        a[NR,i] = $i
    }
}
NF>p { p = NF }
END {    
    for(j=1; j<=p; j++) {
        str=a[1,j]
        for(i=2; i<=NR; i++){
            str=str" "a[i,j];
        }
        print str
    }
}' |sed 's/ExeTime/\'$'\n/g' > convertedMKL.dat

cat resultMKL.dat | cut -f 7-8 | sed -r '/^\s*$/d' | sed '/dramPower/d'> energyMKL.dat
#
cat resultMKL.dat | cut -f 5 > TIMEMKL.dat




