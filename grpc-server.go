package main

import (
	"crypto/tls"

	"log"
	"os"
	"github.com/hyperledger/fabric-ca/util"
	"github.com/hyperledger/fabric/bccsp/pkcs11"
	"github.com/hyperledger/fabric/bccsp/factory"
	//pbHello "google.golang.org/grpc/examples/helloworld/helloworld"
	//pbRoute "google.golang.org/grpc/examples/route_guide/routeguide"

	"google.golang.org/grpc"
	pb "github.com/hyperledger/tls-connection/tls-connection"
	"google.golang.org/grpc/credentials"
	"context"
)

type pkcs11BccspServer struct {

}
const SSL_CERT_FULL_NAME = "/Users/jamesguan/go/src/github.com/hyperledger/fabric-ca/bin/ca-cert.pem"

// const SSL_KEY_FULL_NAME = "/Users/jamesguan/go/src/github.com/hyperledger/tls-connection/key.pem"
const SSL_TEST_PORT = ":12443"

func (s *pkcs11BccspServer)GetConfig(ctx context.Context, cfgopts *pb.ConfigOpts)(*pb.Config, error) {
	var cfg = &pb.Config{
		Provider: cfgopts.Opts,
	}
	return cfg, nil
}

func (s *pkcs11BccspServer)SetConfig(ctx context.Context, cfgopts *pb.ConfigOpts)(*pb.Config, error) {
	return nil, nil
}

func newServer() *pkcs11BccspServer {
	s := new(pkcs11BccspServer)
	return s
}

func main() {
	// first have tls configured

	cfg := &factory.FactoryOpts{
		ProviderName: "PKCS11",
		Pkcs11Opts: &pkcs11.PKCS11Opts{
			SecLevel:      256,
			HashFamily:    "SHA2",
			Ephemeral:     true,
			Label:         "GuanTao",
			Pin:           "1234",
			Library:       "/usr/local/Cellar/softhsm/2.2.0/lib/softhsm/libsofthsm2.so",
			FileKeystore:  nil,
			DummyKeystore: nil,
			Sensitive:     false,
			SoftVerify:    false,
		},
		//ProviderName: "SW",
		//SwOpts: &factory.SwOpts{
		//	HashFamily: "SHA2",
		//	SecLevel:   256,
		//
		//	Ephemeral: true,
		//},
	}

	factory.InitFactories(cfg)
	csp, err := factory.GetBCCSPFromOpts(cfg)
	if err != nil {
		log.Panicln(err)
		return
	}

	cer, err := util.LoadX509KeyPair(SSL_CERT_FULL_NAME, "", csp)
	if err != nil {
		log.Println(err)
		return
	}
	w := os.Stdout
	config := &tls.Config{Certificates: []tls.Certificate{*cer}, KeyLogWriter: w}
	ln, err := tls.Listen("tcp", SSL_TEST_PORT, config)
	if err != nil {
		log.Println(err)
		return
	}
	defer ln.Close()

	var opts []grpc.ServerOption
	creds := credentials.NewServerTLSFromCert(cer)
	if err != nil {
		log.Fatalf("Failed to extract credentials %v", err)
	}
	opts = []grpc.ServerOption{grpc.Creds(creds)}
	server := grpc.NewServer(opts...)
	pb.RegisterGrpcBccspManagerServer(server, newServer())
	server.Serve(ln)


}

// Note that you have to provide your own implementations of each service.
//var route pbRoute.RouteServer
//var hello pbHello.GreeterServer
//
//func Serve() error {
//	lis, err := net.Listen("tcp", fmt.Sprintf(":%d", 443))
//	if err != nil {
//		return nil
//	}
//
//	// You should setup TLS certificates here
//	var conf *tls.Config
//	creds := credentials.NewTLS(conf)
//	opts := []grpc.ServerOption{grpc.Creds(creds)}
//
//	grpcServer := grpc.NewServer(opts...)
//
//	pbRoute.RegisterRouteGuideServer(grpcServer, route)
//	pbHello.RegisterGreeterServer(grpcServer, hello)
//
//	return grpcServer.Serve(lis)
//}

