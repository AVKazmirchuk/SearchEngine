//
// Created by Alexander on 31.03.2025.
//



#include "general.h"


#include "kav/logger.h"





bool castJSONToBool(JSON& objectJSON)
{
    return !objectJSON.is_discarded();
}

namespace constants
{

    const std::string configFilePath{"config.json"};
    const std::string requestsFilePath{"requests.json"};
    const std::string answersFilePath{"answers.json"};
    const std::string configLoggerFilePath{"logger.json"};
    const std::string configWriterMessageFilePath{"messageQueue.json"};

    const int precision{6};
    const int formatByWidth{2};

}

