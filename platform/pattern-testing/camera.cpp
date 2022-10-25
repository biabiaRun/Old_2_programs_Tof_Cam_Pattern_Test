#include "stdlib.h"
#include "camera.h"
#include <iostream>
#include <royale.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <royale/ICameraDevice.hpp>
#include <royale/IExtendedData.hpp>
#include <royale/Status.hpp>
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
int expectedArray[38528]; //for the matrix 172x224 -> array size 38528


Camera::CameraError Camera::RunAccessLevelTests(int user_level)
{
    // Get the access level
    royale::CameraAccessLevel level;
    royale::CameraStatus status = camera_->getAccessLevel(level);

    std::clog << "Verifying access level is 3... " << std::endl;
    if (status != royale::CameraStatus::SUCCESS)
    {
        cerr << "[ERROR] Could not grab the access level. " 
                  << royale::getStatusString(status).c_str() << endl;
        return ACCESS_LEVEL_ERROR;
    }

    // Check if access level was set properly
    access_level_ = static_cast<int>(level);
    //cout << "== Check if access level is set properly: " << int (access_level_) << endl; //Running.G Edit

    if (access_level_ != user_level)
    {
        cerr << "[ERROR] Access level mismatch. " << access_level_
                  << "!=" << user_level << endl;
        return ACCESS_LEVEL_ERROR;
    }


    std::clog << "[SUCCESS] Access level test passed\n" << std::endl;

    return NONE;
}

Camera::CameraError Camera::RunConfigTests(int testPattern)
{
    // Test if CameraDevice was created
    if(camera_ == nullptr)
    {
        std::cerr << "[ERROR] Camera device could not be created" << std::endl;
        return CAM_NOT_CREATED;
    }
    
    /*
    // Test Initialize()
    royale::CameraStatus status = camera_->initialize();
    if (status != royale::CameraStatus::SUCCESS)
    {
        std::cerr << "[ERROR] Camera device could not be initialized " 
                  << royale::getStatusString(status).c_str() << std::endl;
        return CAM_NOT_INITIALIZED;
    }
    */
    
    royale::CameraStatus status;
    // Config cam
    switch (testPattern)
    {
        case 1:
            cout << "Line counter test pattern is on... " << endl;
            status = camera_->writeRegisters({{ "0xA026", 0x1000}}); // Running.G Edit
            break;
        case 2:
            cout << "Overflow counter test pattern is on..." << endl; // Running.G Edit
            status = camera_->writeRegisters({{ "0xA026", 0x3000}}); 
            break;
        case 3:
            cout << "Alternating line counter and toggling constant test pattern is on..." << endl;
            status = camera_->writeRegisters({{ "0xA026", 0x55A5}}); 
            status = camera_->writeRegisters({{ "0xA027", 0x1A5A}}); 
            break;
        case 4:
            cout << "Toggling constant test pattern is on..." << endl;
            status = camera_->writeRegisters({{ "0xA026", 0x75A5}}); 
            status = camera_->writeRegisters({{ "0xA027", 0x1A5A}});
            break;
        case 0:
            cout << "### RESET REGISTER ###"<< endl;
            status = camera_->writeRegisters({{ "0xA026", 0x0555}}); // Running.G Edit it for Reset
            break;
    }

    std::clog << "[SUCCESS] Test pattern set\n" << std::endl;
    return NONE;
    
}


