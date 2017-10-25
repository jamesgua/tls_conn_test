
#include "ep11grpc.h"
#include <iostream>

using std::cout;
using std::endl;

bool Grep11ManagerClient::loaded_ = false;

bool Grep11ManagerClient::isLoaded(void) {
    return loaded_;
}
bool Grep11ManagerClient::Load(const LoadInfo& info, LoadStatus* status) {
    if(loaded_) {
        return loaded_;
    }
    cout << "Loading Grep11Manager" << endl;
    Status grpcStatus = stub_->Load(ctx_, info, status);
    if(!grpcStatus.ok()) {
        cout << "Error in loading Grep11Manager " << status->error() << endl;
    }
    else {
        loaded_ = true;
        cout << "grpc status OK, grep11 server " << status->address() << ", is session " << status->session() << endl;
    }
    return loaded_;
}

bool Grep11Client::GenerateECKey(GenerateInfo& info, GenerateStatus* status) {
    bool success = false;
    if(!Grep11ManagerClient::isLoaded()) {
        return success;
    }
    cout << "Generating ECDSA Key" << endl;
    if (stub_->GenerateECKey(ctx_, info, status).ok()) {
        success = true;
        //cout << "ECDSA pubkey: " << status->pubkey() << ", privkey: " << status->privkey() << endl;
    }
    else {
        cout << "ECDSA key generation error: " << status->error() << endl;
    }
    return success;
}

bool Grep11Client::SignP11ECDSA(SignInfo& info, SignStatus* status) {
    bool success = false;
    if(!Grep11ManagerClient::isLoaded()) {
        return success;
    }
    cout << "Signing Grep11 ECDSA" << endl;
    if(stub_->SignP11ECDSA(ctx_, info, status).ok()) {
        success = true;
    }
    else {
        cout << "Signing ECDSA failure: " << status->error() << endl;
    }
    return success;
}

bool Grep11Client::VerifyP11ECDSA(VerifyInfo& info, VerifyStatus* status) {
    bool success = false;
    if(!Grep11ManagerClient::isLoaded()) {
        return success;
    }
    cout << "Verifying Grep11 ECDSA" << endl;
    if(stub_->VerifyP11ECDSA(ctx_, info, status).ok()) {
        success = true;
    }
    else {
        cout << "Verify ECDSA failure " << status->error() << endl;
    }
    return success;
}