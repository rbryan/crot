a=1
for i in ./[!anin]*.png; do
    new=$(printf "%09d.png" ${a}) #04 pad to length of 4
    mv ${i} ${new}
    let a=a+1
done
