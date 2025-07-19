from rucio.client import Client
from rucio.common.exception import RuleNotFound, AccessDenied

def delete_specific_rules(account='sosaha', prefix='cms:/store/'):
    """
    Deletes Rucio rules for a given account where the file name starts with a specific prefix.

    :param account: The Rucio account for which rules should be deleted.
    :param prefix: The prefix to match (e.g., 'cms:/store/').
    """
    client = Client()

    try:
        # Fetch all rules for the account
        rules = client.list_account_rules(account=account)

        for rule in rules:
            rule_id = rule['id']
            dids = rule.get('dids', [])
            delete_rule = False

            # Check if any DID matches the prefix
            for did in dids:
                scope = did['scope']
                name = did['name']
                full_name = f"{scope}:{name}"

                if full_name.startswith(prefix):
                    delete_rule = True
                    break  # If one DID matches, decide to delete the rule

            if delete_rule:
                print(f"Attempting to delete rule: {rule_id} (matches prefix '{prefix}')")
                try:
                    client.delete_replication_rule(rule_id)
                    print(f"Successfully deleted rule: {rule_id}")
                except RuleNotFound:
                    print(f"Rule not found: {rule_id}")
                except AccessDenied:
                    print(f"Access denied for rule: {rule_id}")
                except Exception as e:
                    print(f"Unexpected error while deleting rule {rule_id}: {e}")

    except Exception as e:
        print(f"Failed to retrieve rules for account {account}: {e}")

if __name__ == "__main__":
    # Replace 'your_account_name' with your actual Rucio account name
    account_name = "your_account_name"
    prefix = "cms:/store/"  # Prefix to match

    # Confirm with the user before proceeding
    confirm = input(f"Are you sure you want to delete rules for account '{account_name}' where files start with '{prefix}'? (yes/no): ")
    if confirm.lower() == 'yes':
        delete_specific_rules(account_name, prefix)
    else:
        print("Operation cancelled.")

