
#ifndef EP11GRPC_H
#define EP11GRPC_H

#include <memory>
#include <thread>
#include <string>
#include <random>

#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>
#include "grep11.grpc.pb.h"

using std::unique_ptr;
using std::shared_ptr;

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;

using grep11protos::GenerateInfo;
using grep11protos::GenerateStatus;
using grep11protos::Grep11;
using grep11protos::Grep11Manager;
using grep11protos::LoadInfo;
using grep11protos::LoadStatus;
using grep11protos::SignInfo;
using grep11protos::SignStatus;
using grep11protos::VerifyInfo;
using grep11protos::VerifyStatus;

class Grep11ManagerClient {
public:
    Grep11ManagerClient(shared_ptr<Channel> channel) : stub_(Grep11Manager::NewStub(channel)){ctx_ = new ClientContext;}
    bool Load(const LoadInfo& info, LoadStatus* status);
    static bool isLoaded(void);
    ~Grep11ManagerClient() {delete ctx_; ctx_ = NULL;}
private:
    unique_ptr<Grep11Manager::Stub> stub_;
    ClientContext* ctx_;
    static bool loaded_;
};

class Grep11Client {
public:
    Grep11Client(shared_ptr<Channel> channel) : stub_(Grep11::NewStub(channel)){ctx_ = new ClientContext;}
    bool GenerateECKey(GenerateInfo& info, GenerateStatus* status);
    bool SignP11ECDSA(SignInfo& info, SignStatus* status);
    bool VerifyP11ECDSA(VerifyInfo& info, VerifyStatus* status);
    ~Grep11Client() {delete ctx_; ctx_ = NULL;}
private:
    unique_ptr<Grep11::Stub> stub_;
    ClientContext* ctx_;
};

#endif //EP11GRPC_H