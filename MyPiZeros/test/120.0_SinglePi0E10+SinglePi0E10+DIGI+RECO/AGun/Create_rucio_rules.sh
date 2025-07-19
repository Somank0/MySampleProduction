#!/bin/bash

# Set paths and variables
DATASET_NAME="/Neutrino_E-10_gun/RunIISummer20ULPrePremix-UL18_106X_upgrade2018_realistic_v11_L1v1-v2/PREMIX"  # Replace with your dataset name
DISK_STORAGE_AREA="T1_US_FNAL_Disk"  # Replace with the desired disk storage area
RSE="T1_US_FNAL_Disk"  # Replace with your RSE (e.g., CERN-PROD_DATADISK)

# Function to fetch file list from the dataset using Rucio
fetch_files_from_dataset() {
    local dataset=$1
    # Use the `rucio list-files` command to fetch the list of files in the dataset
    echo "Fetching files from dataset: $dataset"
    rucio list-files "$dataset" | awk '{print $2}'  # Extract the file names from the list
}

BASE_URL="root://cms-xrd-global.cern.ch//"


# Function to check if a ROOT file can be opened using TFile::Open()
check_root_file() {
    local file_path=$1
    # Prepend the base URL to the file path
    local full_path="${BASE_URL}${file_path}"
    
    # Use a ROOT script to check file
    root -b -q -l <<EOF
{
    TFile *f = TFile::Open("$full_path");
    if (f && !f->IsZombie()) {
        std::cout << "SUCCESS: ROOT file is valid: $full_path" << std::endl;
        f->Close();
        return;
    }
    std::cerr << "ERROR: Cannot open ROOT file: $full_path" << std::endl;
}
EOF
    if [ $? -ne 0 ]; then
        return 1
    else
        return 0
    fi
}

# Function to create a Rucio rule for a file
create_rucio_rule() {
    local file_path=$1
    echo "Creating Rucio rule to move $file_path to $DISK_STORAGE_AREA..."
    rucio add-rule "$file_path" 1 "$RSE" --lifetime 14688000 --ask-approval --activity 'User AutoApprove' --grouping 'ALL' --comment "Need urgently, keep till May 2025"  # Adjust lifetime as needed
    if [ $? -eq 0 ]; then
        echo "Rucio rule created successfully for $file_path"
    else
        echo "Failed to create Rucio rule for $file_path"
    fi
}

# Check if Rucio is available
command -v rucio >/dev/null 2>&1 || { echo "Rucio command not found. Please install it."; exit 1; }

# Fetch files from the dataset and extract the file names (using awk to get the 2nd column)
file_list=$(rucio list-files "$DATASET_NAME" | awk '{print $2}')  # File names are in the second column

if [ -z "$file_list" ]; then
    echo "No files found in the dataset $DATASET_NAME."
    exit 1
fi

# Loop through the list of files
for root_file in $file_list; do
    echo "Processing file: $root_file"

    # Check if the ROOT file can be opened
    check_root_file "$root_file"
    if [ $? -ne 0 ]; then
        # If the ROOT file is invalid, create a Rucio rule to move it
        create_rucio_rule "$root_file"
    fi
done

echo "Processing completed."

