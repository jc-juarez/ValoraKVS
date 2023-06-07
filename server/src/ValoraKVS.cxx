// *********************
// Apexia Platforms
// Valora KVS
// Server
// ValoraKVS.cxx
// *********************

#include "ValoraKVS.h"

namespace Valora {

    ValoraKVS::ValoraKVS() {

        m_DBOptions.create_if_missing = true;
        rocksdb::Status status = rocksdb::DB::Open(m_DBOptions, "/tmp/valorakvs", &m_DB);
        
        if (!status.ok()) {
            throw std::runtime_error("<!> Valora KVS Error. An error has ocurred while trying to create the Key-Value Store");
        }
        
        m_QueryHandler = std::make_unique<Valora::QueryHandler>(this);

    }

    void ValoraKVS::Run() {

        m_QueryHandler->Start();

        // Run forever
        for(;;) {}

    }

} // namespace Valora
