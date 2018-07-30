#include "utils.h"

#include <iostream>
#include <libcec/cec.h>

void utils::signalHandler(int signal) {
    std::cerr << "Caught signal " << signal << ". Exiting..." << std::endl;
//    CECDestroy()
}
