#!/bin/bash

# List of block names defined in the script
BLOCKS=("/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#08d3d945-67dc-4213-b07c-cfe189796919" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#14be6a38-cbda-4582-812a-cc50b95b5623" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#561f26aa-5a21-4686-a138-67c9943ee6f6" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#35505c42-20f5-45b0-9ddd-446212d8a761" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#3a106ee4-3be9-4bf7-a045-d6f7912317af" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#85f01d46-29a9-487c-87a6-b70506059457" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#61799dbf-9a06-4c4c-8f47-3ea468c4307b" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#831f90e4-8f0d-439b-8012-4cefb0a9932d" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#688ab1e9-e17f-40ea-bea9-44f87692d124" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#72e7e007-a684-4696-b43a-3f89272b8a2b"  "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#5f2982a3-bbb6-4ddd-a11d-dd7802db8aeb" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#21e6a84f-ebde-43c5-978e-ece5e6576bd0" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#22a073eb-4698-437c-9ff1-f0dad571394a" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#32b23303-4cb9-4230-b7c2-97e462504f50" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#40abcced-0c6b-4f56-9bc6-6ce8373f740c" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#337c4048-df56-4e1e-9545-61fa5a0d32fd" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#1aa5b619-086f-4f40-af5f-60cfe677e44b" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#080fef7b-ddf5-49e6-9830-e6be3ffe5f76" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#19a8cdb8-71f8-4bf5-bd59-b69e0c23b4f7" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#25d8acc0-50f1-464c-9e9c-639317ef8985" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#0405ae31-0ab6-48e5-9252-130138a472bc" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#1363a234-7174-46c5-b95e-074ed952583b" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#1363a234-7174-46c5-b95e-074ed952583b" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#381b9b9e-45ee-43de-818d-8c083c3d496b" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#5cfd2f73-d35c-4f7d-9fbf-83049a6f7035" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#2ed886ab-a51e-4138-9d95-404c3420db82" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#2900774b-3867-4887-b1e4-f6f7e9b90f7a" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#494e4f9c-342a-42fd-b77a-62a3a4954991" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#18825f2e-e5a0-4c52-8c4e-8da7417168c8" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#08d3d945-67dc-4213-b07c-cfe189796919" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#23771b4c-6d7f-4d81-984f-e74919fb5410" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#313ff713-0ac6-4a48-9b8a-e849932021c6" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#1610a66f-3001-4bab-a86b-53ab810c1d4f" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#137716ff-527b-403b-b9e5-430e9a3e273c" "/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX#490020be-1362-41ca-a315-0370237eccd5")  # Add your block names here

# Output file where the accessible files will be written
OUTPUT_FILE="accessible_files_old.txt"  # Specify your desired output filename here

# Initialize the output file (clear it if it already exists)
> "$OUTPUT_FILE"

# Loop through the block names
for BLOCK_NAME in "${BLOCKS[@]}"; do
    echo "Processing block: $BLOCK_NAME"
    
    # List the files in the block using Rucio
    FILES=$(rucio list-files "cms:$BLOCK_NAME" | awk '{print $2}' | grep -v '^#')
    while IFS= read -r FILE; do
        # Remove the "cms:" prefix from the file path
        FILE_PATH="${FILE#cms:}"

        # Form the full URL for the file (using CMS XRD Global redirector)
        FILE_URL="root://cms-xrd-global.cern.ch/$FILE_PATH"
        
        root -b -l -q <<EOF &>/dev/null
            TFile *f = TFile::Open("$FILE_URL");
            if (f && !f->IsZombie()) {
                f->Close();
                std::cout << "accessible" << std::endl;
            }
EOF

        # If the file was successfully opened, append the stripped filename to the output file
        if [ $? -eq 0 ]; then
            echo "$FILE_PATH" >> "$OUTPUT_FILE"
            echo "File $FILE_PATH is accessible and added to $OUTPUT_FILE"
        else
            echo "File $FILE_PATH is not accessible."
        fi
    done <<< "$FILES"
done

echo "Finished processing. Accessible files have been written to '$OUTPUT_FILE'."

