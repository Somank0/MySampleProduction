#!/bin/bash

# Usage: ./delete_rucio_rules.sh <account_name> <prefix>
# Example: ./delete_rucio_rules.sh your_account_name cms:/store/

# Check if the account name and prefix are provided
if [ $# -ne 2 ]; then
  echo "Usage: $0 <account_name> <prefix>"
  exit 1
fi

ACCOUNT_NAME=$1
PREFIX=$2

# Load Rucio environment (adjust this if needed)
source /cvmfs/cms.cern.ch/rucio/setup.sh

# List all rules for the account and filter by the prefix
echo "Fetching rules for account: $ACCOUNT_NAME with prefix: $PREFIX"
RULE_IDS=$(rucio list-rules --account "$ACCOUNT_NAME" | grep "$PREFIX" | /usr/bin/awk '{print $1}')

if [ -z "$RULE_IDS" ]; then
  echo "No rules found with prefix '$PREFIX'."
  exit 0
fi

# Confirm deletion with the user
echo "The following rules will be deleted:"
echo "$RULE_IDS"
read -p "Are you sure you want to delete these rules? (yes/no): " CONFIRM

if [[ "$CONFIRM" != "yes" ]]; then
  echo "Operation cancelled."
  exit 1
fi

# Delete each rule
for RULE_ID in $RULE_IDS; do
  echo "Deleting rule: $RULE_ID"
  rucio delete-rule "$RULE_ID"
  if [ $? -eq 0 ]; then
    echo "Successfully deleted rule: $RULE_ID"
  else
    echo "Failed to delete rule: $RULE_ID"
  fi
done

echo "Rule deletion process complete."

