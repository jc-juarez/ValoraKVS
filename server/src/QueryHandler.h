// *********************
// Apexia Platforms
// Valora KVS
// Server
// QueryHandler.h
// *********************

#ifndef QUERY_HANDLER_
#define QUERY_HANDLER_

#include <string>
#include <unordered_set>

#include <zmq.hpp>

namespace Valora {

    class ValoraKVS;

    class QueryHandler {

        public:

            QueryHandler(ValoraKVS* p_ValoraKVS);

        public:

            void Start();
            void Reply(int p_StatusCode, std::string p_ResponseMessage, zmq::socket_t* p_Socket);

        public:

            void HandleQuery(zmq::context_t& p_ZeroMQContext, int p_ThreadId);

        private:

            ValoraKVS* m_ValoraKVS;
            zmq::context_t m_ZeroMQContext;
            zmq::socket_t m_FrontendSocket;
            zmq::socket_t m_BackendSocket;
            std::unordered_set<std::string> m_AcceptedActions;

    };

} // namespace Valora

#endif
