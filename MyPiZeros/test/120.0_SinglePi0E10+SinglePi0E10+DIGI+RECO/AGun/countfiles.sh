count=0
#f_name="0_2_GeV_set5"
f_name="Barrel_extended_samples/EB_extended_sample_set1"
for file in $(xrdfs se01.indiacms.res.in:1094 ls -R /store/user/sosaha/test/A_sample/$f_name); do
  count=$((count + 1))
done
echo "Total number of files: $count"

