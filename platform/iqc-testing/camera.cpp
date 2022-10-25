#include "stdlib.h"
#include "camera.h"
#include <iostream>
#include <royale.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <royale/ICameraDevice.hpp>
#include <CameraFactory.hpp>
#include <iomanip>
#include <list>
#include <iterator>
#include <array>
#include <vector>
#include <fstream>
#include <cstdlib> 


using namespace std;
using namespace royale;
using namespace platform;
using std::ofstream;


int depthImageNumber = 0;
int arraySize = 38528;
int firstPxlValue;
list<int> testResult;
const uint16_t* rawPixelArray;
int rowNum = 172;
int colNum = 224; 
int counter = 0;
int testPattern;
int expectedArray[38528]; //for the matrix 172x224 -> array size 38528



Camera::CameraError Camera::RunAccessLevelTests(int user_level)
{
    // Get the access level
    royale::CameraAccessLevel level;
    royale::CameraStatus status = camera_->getAccessLevel(level);
    std::clog << "[---------------- Print /level/ under 'RunAccessLevel' function---------------- ] " << std::endl;
    std::clog << int (level) << std::endl; //Running.G Edit

    if (status != royale::CameraStatus::SUCCESS)
    {
        std::cerr << "[ERROR] Could not grab the access level. " 
                  << royale::getStatusString(status).c_str() << std::endl;
        return ACCESS_LEVEL_ERROR;
    }

    // Check if access level was set properly
    access_level_ = static_cast<int>(level);
    std::clog << "[---------------- Print /access_level_/ under 'Check if access level was set properly' function---------------- ] " << std::endl;
    std::clog << int (access_level_) << std::endl; //Running.G Edit

    if (access_level_ != user_level)
    {
        std::cerr << "[ERROR] Access level mismatch. " << access_level_
                  << "!=" << user_level << std::endl;
        return ACCESS_LEVEL_ERROR;
    }

    std::clog << "[SUCCESS] All access level tests passed. " << std::endl;

    status = camera_->writeRegisters({{ "0xA0A3", 0x1000}});
    if (status == CameraStatus::SUCCESS)
    {
        std::clog << "[SUCCESS] successfully used the writeRegisters API" << std::endl;
    }
    else
    {
        std::clog << "[ERROR] failed to use the writeRegisters API" << std::endl;
    }

    return NONE;
}

Camera::CameraError Camera::RunConfigTests(int testPattern)
{
    // Test if CameraDevice was created
    if(camera_ == nullptr)
    {
        std::cerr << "[ERROR] Camera device could not be created." << std::endl;
        return CAM_NOT_CREATED;
    }
    // Test Initialize()
    royale::CameraStatus status = camera_->initialize();
    if (status != royale::CameraStatus::SUCCESS)
    {
        std::cerr << "[ERROR] Camera device could not be initialized. " 
                  << royale::getStatusString(status).c_str() << std::endl;
        return CAM_NOT_INITIALIZED;
    }

    switch (testPattern)
    {
        case 1:
            cout << "### LINE COUNTER TEST PATTERN NOW ###" << endl;
            status = camera_->writeRegisters({{ "0xA026", 0x1000}}); // Running.G Edit
            break;
        case 2:
            cout << "### OVERFLOW COUNTER TEST PATTERN NOW ###" << endl; // Running.G Edit
            status = camera_->writeRegisters({{ "0xA026", 0x3000}}); 
            break;
        case 3:
            cout << "### ALTERNATING LINE COUNTER AND TOGGLING CONSTANT TEST PATTERN NOW ###" << endl;
            status = camera_->writeRegisters({{ "0xA026", 0x55A5}}); 
            status = camera_->writeRegisters({{ "0xA027", 0x1A5A}}); 
            break;
        case 4:
            cout << "### TOGGLING CONSTANT TEST PATTERN NOW ###" << endl;
            status = camera_->writeRegisters({{ "0xA026", 0x75A5}}); 
            status = camera_->writeRegisters({{ "0xA027", 0x1A5A}});
            break;
        case 0:
            cout << "### RESET NOW ###"<< endl;
            status = camera_->writeRegisters({{ "0xA026", 0x0555}}); // Running.G Edit it for Reset
            break;

    }

    std::clog << "[SUCCESS] Test pattern is set. " << std::endl;
    return NONE;
    
}


Camera::CameraError Camera::RunPatternTest()
{



  return NONE;
}
