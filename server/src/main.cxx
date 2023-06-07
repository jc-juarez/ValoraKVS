// *********************
// Apexia Platforms
// Valora KVS
// Server
// main.cxx
// *********************

#include <iostream>
#include <memory>

#include "ValoraKVS.h"

int main(int argc, char** argv) {

    std::shared_ptr<Valora::ValoraKVS> valoraKVS = std::make_shared<Valora::ValoraKVS>();

    valoraKVS->Run();

    return 0;
}
