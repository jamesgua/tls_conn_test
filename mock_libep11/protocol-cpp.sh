#!/bin/bash
protoc -I ../../protos --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` $PROTO_FILE
protoc -I ../../protos --cpp_out=. $PROTO_FILE
