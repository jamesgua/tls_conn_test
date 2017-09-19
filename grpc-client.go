
package main

// cmd to generate go file from .proto file
//protoc -I tls-connection/ tls-connection/grpc-tls-bccsp.proto --go_out=plugins=grpc:tls-connection

import (
	//"crypto/tls"

	"log"
	//"os"
	//"github.com/hyperledger/fabric-ca/util"
	//"github.com/hyperledger/fabric/bccsp/pkcs11"
	//"github.com/hyperledger/fabric/bccsp/factory"
	//pbHello "google.golang.org/grpc/examples/helloworld/helloworld"
	//pbRoute "google.golang.org/grpc/examples/route_guide/routeguide"

	"google.golang.org/grpc"
	pb "github.com/hyperledger/tls-connection/tls-connection"
	"google.golang.org/grpc/credentials"
	"context"
	"fmt"
)

const CERT_FILE = "/Users/jamesguan/go/src/github.com/hyperledger/fabric-ca/bin/ca-cert.pem"

func main() {
	var opts []grpc.DialOption
	creds, err := credentials.NewClientTLSFromFile(CERT_FILE, "localhost:12443")

	if err != nil {
		fmt.Println("Failed to extract credentials from certificate %v", err)
	}
	opts = append(opts, grpc.WithTransportCredentials(creds))

	conn, err := grpc.Dial("localhost:12443", opts...)
	if err != nil {
		log.Println("Can't dial grpc!")
	}
	defer conn.Close()

	client := pb.NewGrpcBccspManagerClient(conn)

	cfgopts := &pb.ConfigOpts {
		"empty",
	}

	cfg, err := client.GetConfig(context.Background(), cfgopts)
	if err != nil {
		fmt.Println("Why can't get config? %v", err)
	}
	fmt.Println("Get config %v from cfg option", cfg, cfgopts)

}
