package main

import (
	"os"
	"log"
	"crypto/tls"
	"net"
	"bufio"
	"runtime/trace"
	//_ "github.com/hyperledger/tls-connection/csputil"
)

const CERT_PATH = "/Users/jamesguan/go/src/github.com/hyperledger/tls-connection"
const CERT_FULL_NAME = "/Users/jamesguan/go/src/github.com/hyperledger/tls-connection/cert.pem"
const KEY_FULL_NAME = "/Users/jamesguan/go/src/github.com/hyperledger/tls-connection/key.pem"
const TEST_PORT = ":12443"

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

	cer, err := tls.LoadX509KeyPair(CERT_FULL_NAME, KEY_FULL_NAME)
	if err != nil {
		log.Println(err)
		return
	}

	config := &tls.Config{Certificates: []tls.Certificate{cer}}
	ln, err := tls.Listen("tcp", TEST_PORT, config)
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
		go handleConnection(conn)
	}
}

func handleConnection(conn net.Conn) {
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

