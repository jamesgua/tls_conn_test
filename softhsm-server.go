
package main

import (
	"github.com/miekg/pkcs11"
	"fmt"
)

func main() {

	p := pkcs11.New("/usr/local/lib/softhsm/libsofthsm2.so")
	err := p.Initialize()
	if err != nil {
		panic(err)
	}

	defer p.Destroy()
	defer p.Finalize()
	var loop = 0

	slots, err := p.GetSlotList(true)
	if err != nil {
		panic(err)
	}
	fmt.Println("slots: %v", slots)
	mechanism, err := p.GetMechanismList(slots[0])
	if err != nil {
		panic(err)
	}
	for range mechanism {
		fmt.Println("mechanism[%v]: %v", loop, mechanism[loop])
		fmt.Printf("\n\t mech %x\n", mechanism[loop].Mechanism)
		//var inner = 0
		//for range mechanism[loop].Parameter {
		//	fmt.Printf("%x|", mechanism[loop].Parameter)
		//	inner++
		//}
		//fmt.Printf("\n\tTotal %v params", inner)
		//inner = 0
		loop++
	}
	loop = 0
	//fmt.Println("mechnism: %v", mechanism)

	session, err := p.OpenSession(slots[0], pkcs11.CKF_SERIAL_SESSION|pkcs11.CKF_RW_SESSION)
	if err != nil {
		panic(err)
	}
	fmt.Println("session: %v", session)
	defer p.CloseSession(session)

	err = p.Login(session, pkcs11.CKU_USER, "1234")
	if err != nil {
		panic(err)
	}
	defer p.Logout(session)

	p.DigestInit(session, []*pkcs11.Mechanism{pkcs11.NewMechanism(pkcs11.CKM_SHA_1, nil)})
	hash, err := p.Digest(session, []byte("this is a string"))
	if err != nil {
		panic(err)
	}

	for _, d := range hash {
		fmt.Printf("%x", d)
		loop++
	}
	fmt.Println("\nhash has %v bytes", loop)
	fmt.Println()
}
