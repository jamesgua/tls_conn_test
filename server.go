package main

import (
	"os"
	"log"
	"crypto/tls"
	"net"
	"bufio"
	"runtime/trace"
	"github.com/hyperledger/fabric-ca/util"
	"github.com/hyperledger/fabric/bccsp/factory"
	// "github.com/hyperledger/fabric/bccsp/pkcs11"
	// "golang.org/x/crypto/sha3"
	"github.com/hyperledger/fabric/bccsp/pkcs11"
)

// const TLS_CERT_PATH = "/Users/jamesguan/go/src/github.com/hyperledger/tls-connection"
const SSL_CERT_FULL_NAME = "/Users/jamesguan/go/src/github.com/hyperledger/fabric-ca/bin/ca-cert.pem"
// const SSL_KEY_FULL_NAME = "/Users/jamesguan/go/src/github.com/hyperledger/tls-connection/key.pem"
const SSL_TEST_PORT = ":12443"

func main() {
	file, traceErr := os.Create("tlstrace.out")
	if traceErr != nil {
		panic(traceErr)
	}
	defer file.Close()
	traceErr = trace.Start(file)
	if traceErr != nil {
		panic(traceErr)
	}
	defer trace.Stop()

	log.SetFlags(log.Lshortfile)

	cfg := &factory.FactoryOpts{
		ProviderName: "PKCS11",
		Pkcs11Opts: &pkcs11.PKCS11Opts{
			SecLevel:      256,
			HashFamily:    "SHA2",
			Ephemeral:	   true,
			Label:         "ForFabric",
			Pin:	       "98765432",
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

	config := &tls.Config{Certificates: []tls.Certificate{*cer}}
	ln, err := tls.Listen("tcp", SSL_TEST_PORT, config)
	if err != nil {
		log.Println(err)
		return
	}
	defer ln.Close()

	for {
		conn, err := ln.Accept()
		if err != nil {
			log.Println(err)
			continue
		}
		go handlelocalConnection(conn)
	}
}

func handlelocalConnection(conn net.Conn) {
	defer conn.Close()
	r := bufio.NewReader(conn)
	for {
		msg, err := r.ReadString('\n')
		if err != nil {
			log.Println(err)
			return
		}

		println(msg)

		n, err := conn.Write([]byte("world\n"))
		if err != nil {
			log.Println(n, err)
			return
		}
	}
}


