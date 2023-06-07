// *********************
// Apexia Platforms
// Valora KVS
// Server
// ValoraKVS.h
// *********************

#ifndef VALORA_KVS_
#define VALORA_KVS_

#include <memory>

#include <rocksdb/db.h>

#include "QueryHandler.h"

namespace Valora {

    class ValoraKVS {

        friend class QueryHandler;

        public:

            ValoraKVS();

        public:

            void Run();

        private:

            rocksdb::DB* m_DB;
            rocksdb::Options m_DBOptions;
            std::unique_ptr<Valora::QueryHandler> m_QueryHandler;

    };

} // namespace Valora

#endif
