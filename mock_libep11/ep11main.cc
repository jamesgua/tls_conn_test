
#include "ep11grpc.h"
#include <unistd.h>
#include <time.h>


using namespace std;
using namespace grpc;

/*
0:6	1:5	2:2b	3:81	4:4	5:0	6:21
oidNamedCurveP256:
0:6	1:8	2:2a	3:86	4:48	5:ce	6:3d	7:3	8:1	9:7
oidNamedCurveP384:
0:6	1:5	2:2b	3:81	4:4	5:0	6:22
oidNamedCurveP521:
0:6	1:5	2:2b	3:81	4:4	5:0	6:23
*/

const unsigned char hexOidP224[] = {0X6, 0X5, 0X2B, 0X81, 0X4, 0X0, 0X21};
const unsigned char hexOidP256[] = {0X6, 0X8, 0X2A, 0X86, 0X48,0XCE,0X3D, 0X3, 0X1,0X7};
const unsigned char hexOidP384[] = {0X6, 0X5, 0X2B, 0X81, 0x4, 0X0, 0X22};
const unsigned char hexOidP521[] = {0X6, 0X5, 0X2B, 0X81, 0X4, 0X0, 0X23};

// generated on csz25085.canlab.ibm.com:/root/temp.txt using sha256sum
const char* hashvalue = "0643185b2b3682f3fd9d7e3eed1c2d7e0736214176986949e877c5a351de7e45";

void displayStringInHex(string input);

int main(int argc, char** argv) {
    cout << "Start testing ep11server" << endl;
    std::shared_ptr<Channel> channel = grpc::CreateChannel("localhost:9876", grpc::InsecureChannelCredentials());

    int result = 1;
    LoadStatus status;
    LoadInfo info;

    Grep11ManagerClient client(channel);
    if (!client.Load(info, &status)) {
        cout << "Quit due to unsuccessful load" << endl;
        return result;
    }
    cout << "Trying to connect to " << status.address() << endl;

    GenerateInfo oidinfo;
    switch(argc) {
    case 1:
        oidinfo.set_oid((const void*)(&hexOidP224), sizeof(hexOidP224));
        break;
    case 2:
        oidinfo.set_oid((const void*)(&hexOidP256), sizeof(hexOidP256));
        break;
    case 3:
        oidinfo.set_oid((const void*)(&hexOidP384), sizeof(hexOidP384));
        break;
    case 4:
        oidinfo.set_oid((const void*)(&hexOidP521), sizeof(hexOidP521));
        break;
    default:
        return result;
    }
    // retrieve address and create another channel
    std::shared_ptr<Channel> returnedChannel = grpc::CreateChannel(status.address(), grpc::InsecureChannelCredentials());
    Grep11Client grep11(returnedChannel);
    GenerateStatus grepstatus;
    if(!grep11.GenerateECKey(oidinfo, &grepstatus)){
        cout << "Fail to generate ECDSA key with " << oidinfo.oid() << endl;
        return result;
    }
    displayStringInHex(grepstatus.pubkey());
    displayStringInHex(grepstatus.privkey());
    grep11.~Grep11Client();


    SignInfo signinfo;
    signinfo.set_privkey(grepstatus.privkey());
    signinfo.set_hash(hashvalue);
    SignStatus signstatus;
//    if(GRPC_CHANNEL_READY != returnedChannel->GetState(true) || GRPC_CHANNEL_IDLE != returnedChannel->GetState(true)) {
//        time_t now = time(NULL);
//        cout << ctime(&now) << "Grep11 channel not in working state, wait till connected!" << endl;
//        gpr_timespec gprtime;
//        gprtime.tv_sec = now + 100;
//        gprtime.tv_nsec = 0;
//        gprtime.clock_type = GPR_CLOCK_REALTIME;
//
//        returnedChannel->WaitForConnected(gprtime);
//        now = time(NULL);
//        cout << ctime(&now) << "Finally channel connected!" << endl;
//    }
    returnedChannel = grpc::CreateChannel(status.address(), grpc::InsecureChannelCredentials());
    Grep11Client grep11sign(returnedChannel);
    if(!grep11sign.SignP11ECDSA(signinfo, &signstatus)) {
        cout << "Fail to sign ECDSA with private key" << endl;
        return result;
    }
    displayStringInHex(signstatus.sig());
    grep11sign.~Grep11Client();

    VerifyInfo veryinfo;
    veryinfo.set_pubkey(grepstatus.pubkey());
    veryinfo.set_hash(hashvalue);
    veryinfo.set_sig(signstatus.sig());
    VerifyStatus verystatus;
    returnedChannel = grpc::CreateChannel(status.address(), grpc::InsecureChannelCredentials());
    Grep11Client grep11verify(returnedChannel);
    if(!grep11verify.VerifyP11ECDSA(veryinfo, &verystatus)) {
        cout << "Can't verify signed ECDSA info" << endl;
        return result;
    }
    cout << "Chech verify status: " << verystatus.valid() << ", error: " << verystatus.error() << endl;
    cout << "All operation succeed!" << endl;
    result = 0;
    return result;
}

void displayStringInHex(string input) {
    size_t index = 0;
    for(; index < input.size(); ++index) {
        cout.width(2);
        cout.fill('0');
        cout << hex << static_cast<int>(input[index]);
    }
    cout << endl << "string size " << index << endl;
//    for(index = 0; index < input.size(); ++ index) {
//        printf("%2X", input[index]);
//    }
//    printf("\n");
}
