package main

import (
	"log"
	"io/ioutil"
	"crypto/tls"
	"crypto/x509"
)

const TEST_ADDRESS = "127.0.0.1:12443"
const PEM_FILE = "/Users/jamesguan/go/src/github.com/hyperledger/fabric-ca/bin/ca-cert.pem"

func main() {
	rootPEM, err := ioutil.ReadFile(PEM_FILE)
	if err != nil {
		log.Panicln(err)
		return
	}
	roots := x509.NewCertPool()
	ok := roots.AppendCertsFromPEM([]byte(rootPEM))
	if !ok {
		panic("Failed to parse self-signed root certificate")
	}
	log.SetFlags(log.Lshortfile)


	conf := &tls.Config{RootCAs: roots}
	//tr := &http.Transport{TLSClientConfig: conf}
	//client := &http.Client{Transport: tr}

	conn, err := tls.Dial("tcp", TEST_ADDRESS, conf)
	if err != nil {
		log.Println(err)
		return
	}
	defer conn.Close()

	n, err := conn.Write([]byte("hello\n"))
	if err != nil {
		log.Println(n, err)
		return
	}

	buf := make([]byte, 100)
	n, err = conn.Read(buf)
	if err != nil {
		log.Println(n, err)
		return
	}

	println(string(buf[:n]))
}


