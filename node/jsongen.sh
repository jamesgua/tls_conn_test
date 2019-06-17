#!/bin/bash

if [ $# -ne 1 ]; then
  echo "must provide wrapped secret_id!"
  echo "usage: $0 \$wrapped_secret_id"
  exit 1
fi
jsonfile=$HOME/.appRoleIDs.json
touch $jsonfile
if [ $? -ne 0 ]; then
	echo "No write permission, failed to generate json file"
	exit 1
fi

export role_id="$role_id"
curl -H "X-Vault-Token: $1" -X POST $VAULT_ADDR/v1/sys/wrapping/unwrap > $jsonfile
export secret_id=$( jq -r ".data.secret_id" $jsonfile )

echo "{" | cat > $jsonfile
echo "\"role_id\":\"$role_id\"," | cat >> $jsonfile
echo "\"secret_id\":\"$secret_id\"" | cat >> $jsonfile
echo "}" | cat >> $jsonfile
