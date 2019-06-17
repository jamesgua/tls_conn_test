const express = require('express');
const server = express();
//const async = require('async');
//const exec = require('child_process').exec;
const https = require('https');
const fs = require('fs');
//process.env.HOME + "/.vault-token";
var shell = require('shelljs');
shell.exec("vault login -method=github token=" + process.env.GITHUB_TOKEN);
//console.log(shell.cat(path).stdout);
var vaultToken = shell.cat(process.env.HOME + "/.vault-token").stdout;

server.get('/github/:id/:token', (req,res) => {
  var dateString = new Date();
  var requestor = "githubid " + req.params.id;
  var dataJson = {
    requestor : dateString
  };
  var credential = req.params.id + ":" + req.params.token;
  var vaultOption = {
    "host": "$VAULT_HOST",
    "port": "$VAULT_PORT",
    "path": "$VAULT_PROJECT_PATH",
    "headers": {
      "X-Vault-Token": vaultToken,
      "X-Vault-Wrap-TTL": "6h",
      "data": dataJson
    },
    "method": "POST"
  };
  var githubOption = {
    "host": "$GIT_REPO_HOST",
    "port": "$HTTPS_PORT",
    "path": "/api/v3/user",
    "method": "GET",
    "json": true,
    "auth": credential
  };
  https.request(githubOption, function(response) {
    if(200 != response.statusCode) {
      console.log("github authentication failure");
      res.send("github id not authenticated");
    } else {
      https.request(vaultOption, (cb) => {
        if(200 != cb.statusCode) {
          console.log("vault wrap secret_id error ");
          res.send("vault server suspending, open ServiceNow ticket");
        }
        cb.on('data', (chunk) => {
          console.log(`BODY: ${chunk}`);
          var respondeString = JSON.parse(chunk).wrap_info.token;
          res.send(respondeString);
        });
      }).end();
    }
  }).end();

});

server.listen(3000, () => console.log('Listening on server port...'));
