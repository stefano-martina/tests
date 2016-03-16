#$\bin\bash

for file in `ls *IMG_*`
do
    echo "processing $file"
    mv $file `echo "$file" | sed s/IMG_//`
done
