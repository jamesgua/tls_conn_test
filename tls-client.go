package main

import (
	"log"
	"crypto/tls"
	"crypto/x509"
	_"net/http"
	_ "net"
)

const TEST_ADDRESS = "127.0.0.1:12443"

func main() {
	rootPEM := `-----BEGIN CERTIFICATE-----
MIICNjCCAeCgAwIBAgIJAJbTD9Rc+DlqMA0GCSqGSIb3DQEBBQUAMIGUMQswCQYD
VQQGEwJDQTEQMA4GA1UECAwHT250YXJpbzEQMA4GA1UEBwwHVG9yb250bzETMBEG
A1UECgwKSUJNIENhbmFkYTETMBEGA1UECwwKQmxvY2tDaGFpbjETMBEGA1UEAwwK
SmFtZXMgR3VhbjEiMCAGCSqGSIb3DQEJARYTamFtZXNndWFAY2EuaWJtLmNvbTAe
Fw0xNzA4MTQyMDE4NTNaFw0yNzA4MTIyMDE4NTNaMIGUMQswCQYDVQQGEwJDQTEQ
MA4GA1UECAwHT250YXJpbzEQMA4GA1UEBwwHVG9yb250bzETMBEGA1UECgwKSUJN
IENhbmFkYTETMBEGA1UECwwKQmxvY2tDaGFpbjETMBEGA1UEAwwKSmFtZXMgR3Vh
bjEiMCAGCSqGSIb3DQEJARYTamFtZXNndWFAY2EuaWJtLmNvbTBcMA0GCSqGSIb3
DQEBAQUAA0sAMEgCQQCY7dbLxrIggggVhwFLy12iSAaStyzmJvKGhN6Zm4x0qxn5
jCPq+JpKbsK+b67GVRcwf4aZSW4zcFxuzt20L6kLAgMBAAGjEzARMA8GA1UdEQQI
MAaHBH8AAAEwDQYJKoZIhvcNAQEFBQADQQALpIPp1ZuAhBK5O7DmOj6x8/Xz/gcp
RUNiFi44jIZRbsR1u+U4J5dug+t3rnr/w+jt4jbV5Ei7srtYAW2rE8lK
-----END CERTIFICATE-----`
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
	//conn, err := tls.Dial("tcp", "9.23.30.85:443", conf)
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

