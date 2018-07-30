#include "callbacks.h"

#include <iostream>

//static CEC::ICECCallbacks g_callbacks;
void logMessage(void *cbParam, const CEC::cec_log_message* message)
{
    std::string strLevel;
    switch (message->level)
    {
    case CEC::CEC_LOG_ERROR:
      strLevel = "ERROR:   ";
      break;
    case CEC::CEC_LOG_WARNING:
      strLevel = "WARNING: ";
      break;
    case CEC::CEC_LOG_NOTICE:
      strLevel = "NOTICE:  ";
      break;
    case CEC::CEC_LOG_TRAFFIC:
      strLevel = "TRAFFIC: ";
      break;
    case CEC::CEC_LOG_DEBUG:
      strLevel = "DEBUG:   ";
      break;
    default:
      break;
    }

//    printf("%s[%16lld]\t%s", strLevel.c_str(), message->time, message->message);
    std::cerr << strLevel << "[" << message->time << "]\t" << message->message << std::endl;
}


CEC::ICECCallbacks createCallbacks() {
    CEC::ICECCallbacks result;
    result.Clear();
    result.logMessage = &logMessage;

    return result;
}
