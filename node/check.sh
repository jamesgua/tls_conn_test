#!/bin/bash
VAULT_ADDR=$VAULT_HOST:$VAULT_PORT
SECRET_PATH=$SECRET_PATH
if ! [ -x "$(command -v curl)" ]; then
	echo "Error: command curl not available"
	exit 1
fi
if ! [ -x "$(command -v jq)" ]; then
	echo "Error: command jq not available"
	exit 1
fi
if ! [ -x "$(command -v base64)" ]; then
	echo "Error: command base64 not available"
	exit 1
fi

export AppRoleIDsFILE=$HOME/.approleIDs.json
# create token with rold_id and secret_id
if [ -s "$AppRoleIDsFILE" ]; then
	export VAULT_TOKEN=$(curl -X POST --data @$AppRoleIDsFILE $VAULT_ADDR/$LOGIN_PATH | jq -r ".level1.level2")
	echo $VAULT_TOKEN > $HOME/.vault-token
else	
        echo "role_id and secret_id needed to generate token, ask owner to get it!"
        echo "unwrapping secret_id cmd example:"
        echo "curl -H \"X-Vault-Token: $wrapped_secret_id\" -X POST $VAULT_ADDR/v1/sys/wrapping/unwrap"
	echo "generated json file with name $AppRoleIDsFILE and format:"
	echo -e "{'\n'\"role_id\":\"\$role_id,\"'\n'\"secret_id\":\"\$secret_id\"'\n'\"}\""
	exit 1
fi
