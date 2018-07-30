#include <iostream>
#include <signal.h>
#include <libcec/cec.h>
#include <libcec/cecloader.h>
#include <libcec/cectypes.h>

#include "utils.h"
#include "callbacks.h"

const std::string CLIENT_NAME("BroMansion");

static CEC::ICECAdapter *g_adapter = nullptr;

void signalHandler(int signal) {
    std::cerr << "Caught signal " << signal << ". Exiting..." << std::endl;
    if (g_adapter) {
        g_adapter->Close();
        UnloadLibCec(g_adapter);
        exit(0);
    }
}

int main(int argc, char* argv[]) {
    if (signal(SIGINT, &signalHandler) == SIG_ERR) {
        std::cerr << "unable to register unix signal handler" << std::endl;
        return -1;
    }

    std::cout << "starting fakeTv..." << std::endl;

    CEC::libcec_configuration config;
    config.Clear();
    config.deviceTypes.Add(CEC::CEC_DEVICE_TYPE_TV);
    config.bMonitorOnly = true;

    auto callbacks = createCallbacks();
    config.callbacks = &callbacks;

    // I think they used a C-style array to restrict name to 13 chars
    strncpy(config.strDeviceName, CLIENT_NAME.c_str(), CLIENT_NAME.length() + 1);

    g_adapter = LibCecInitialise(&config);

    g_adapter->Open("RPI");

    std::string dummy;
    while (true) {
        std::cin >> dummy;
        CEC::cec_command command;
//        command.destination
        auto ack = g_adapter->SendKeypress(CEC::CECDEVICE_AUDIOSYSTEM, CEC::CEC_USER_CONTROL_CODE_VOLUME_UP, true);
        if (!ack) {
            continue;
        }
        g_adapter->SendKeyRelease(CEC::CECDEVICE_AUDIOSYSTEM, true);
    }

    return 0;
}
