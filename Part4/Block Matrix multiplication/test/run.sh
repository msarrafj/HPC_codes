if ! grep -q "running" ./test.dat; then
    echo "" >> dump.dat
else awk '$1=="Hossein" {print $3}' ./test.dat >> dump.dat
     awk '$1=="Hasan" {print $3}' ./test.dat >> dump.dat
fi


