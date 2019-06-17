curl -H "X-Vault-Token: $VAULT_TOKEN" -X PUT $VAULT_ADDR/v1/auth/token/revoke-self
rm -f $HOME/.vault-token
