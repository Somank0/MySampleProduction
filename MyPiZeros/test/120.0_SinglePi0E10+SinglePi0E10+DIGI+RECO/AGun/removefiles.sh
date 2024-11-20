f_name="160K_0p1_to_2_sample"
for file in $(xrdfs root://se01.indiacms.res.in ls /store/user/sosaha/test/A_sample/$f_name); do
    xrdfs root://se01.indiacms.res.in rm $file
done

