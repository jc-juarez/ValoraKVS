// *********************
// Apexia Platforms
// Valora KVS
// Server
// QueryHandler.cxx
// *********************

#include <thread>
#include <sstream>

#include <rocksdb/db.h>

#include "ValoraKVS.h"
#include "QueryHandler.h"

namespace Valora {

    QueryHandler::QueryHandler(ValoraKVS* p_ValoraKVS) {

        m_ValoraKVS = p_ValoraKVS;

        m_ZeroMQContext = zmq::context_t(1);
        m_FrontendSocket = zmq::socket_t(m_ZeroMQContext, zmq::socket_type::router);
        m_BackendSocket = zmq::socket_t(m_ZeroMQContext, zmq::socket_type::dealer);

        m_FrontendSocket.bind("tcp://*:5555");
        m_BackendSocket.bind("inproc://workers");

        m_AcceptedActions.insert("SET");
        m_AcceptedActions.insert("GET");
        m_AcceptedActions.insert("DEL");

    }

    void QueryHandler::Start() {

        for (int i = 0; i < 100; ++i) {
            std::thread HandleQueryTask(&QueryHandler::HandleQuery, this, std::ref(m_ZeroMQContext), i);
            HandleQueryTask.detach();
        }

        zmq::proxy(m_FrontendSocket, m_BackendSocket, nullptr);

    }

    void QueryHandler::Reply(int p_StatusCode, std::string p_ResponseMessage, zmq::socket_t* p_Socket) {

        std::stringstream replyMessage;

        replyMessage << p_StatusCode << "|" << p_ResponseMessage;

        zmq::message_t reply(replyMessage.str().size());
        memcpy(reply.data(), replyMessage.str().data(), replyMessage.str().size());

        (*p_Socket).send(reply);

    }

    void QueryHandler::HandleQuery(zmq::context_t& p_ZeroMQContext, int p_ThreadId) {

        zmq::socket_t socket(p_ZeroMQContext, zmq::socket_type::rep);
        socket.connect("inproc://workers");

        while (true) {

            zmq::message_t request;
            socket.recv(request);

            std::string message(static_cast<char*>(request.data()), request.size());

            if (message.size() < 5) {
                Reply(400, "Invalid request format", &socket);
                continue;
            }

            // Get Action
            std::string action = message.substr(0,3);

            if (!m_AcceptedActions.count(action)) {
                Reply(400, "Action is not supported", &socket);
                continue;
            }

            if (action == "SET") {

                // Initial Protocol assumes client first encountered ';' symbol acts as delimeter
                // and that Gateway sanitizes request data correctly.
                // Will later replace with precise bytes counting for keys and values both
                // for Server and Gateway.
                char delimeter = ';'; 
                int delimeterPointer = 3;

                while(delimeterPointer < message.size()) {
                    if (message[delimeterPointer] == ';') break;
                    ++delimeterPointer;
                }

                std::string key = message.substr(3, (delimeterPointer - 3));
                std::string value = message.substr(delimeterPointer + 1);

                // Set Key-Value pair
                rocksdb::Status status = m_ValoraKVS->m_DB->Put(rocksdb::WriteOptions(), key, value);
                
                if (!status.ok()) {
                    Reply(400, "Error on setting a key-value pair", &socket);
                    continue;
                }

            }
            else if (action == "GET") {

                std::string key = message.substr(3);
                std::string value;

                // Get value
                rocksdb::Status status = m_ValoraKVS->m_DB->Get(rocksdb::ReadOptions(), key, &value);

                if (status.IsNotFound()) {
                    Reply(400, "Key not found", &socket);
                    continue;
                } 
                else {
                    Reply(200, value, &socket);
                    continue;
                }

            }
            else if (action == "DEL") {

                // TODO

            }

            Reply(200, "Status_OK", &socket);

        }

    }

} // namespace Valora
