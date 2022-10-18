#include <iostream>
#include "stdlib.h"
#include <royale.hpp>
#include "camera.h"
#include <royale.hpp>
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

using namespace royale;
using namespace platform;
using namespace std;

Camera::CameraError Camera::RunInitializeTests(royale::String useCase)
{
    // Test if CameraDevice was created
    if(camera_ == nullptr)
    {
        cerr << "[ERROR] Camera device could not be created." << endl;
        return CAM_NOT_CREATED;
    }
    // Test Initialize()
    royale::CameraStatus status = camera_->initialize();
    if (status != royale::CameraStatus::SUCCESS)
    {
        cerr << "[ERROR] Camera device could not be initialized. " 
                  << royale::getStatusString(status).c_str() << endl;
        return CAM_NOT_INITIALIZED;
    }
    use_case_ = useCase;
    royale::Vector<royale::String> useCaseList;
    status = camera_->getUseCases (useCaseList);
    if (status != royale::CameraStatus::SUCCESS || useCaseList.empty())
    {
        cerr << "[ERROR] Could not get use cases. " 
                  << royale::getStatusString(status).c_str() << endl;
        return USE_CASE_ERROR;
    }

    for (auto i = 0u; i < useCaseList.size(); ++i) {
      if (useCaseList.at(i) == use_case_) {
        status = camera_->setUseCase(useCaseList.at(i));
        if (status != royale::CameraStatus::SUCCESS) {
            cerr << "[ERROR] Could not set a new use case. " << useCaseList[i].c_str() << "   " 
                  << royale::getStatusString(status).c_str() << endl;
            return USE_CASE_ERROR;
        }else{
          cout << "== Setting user case: " << useCaseList[i].c_str() << endl;
          status = camera_->getFrameRate(fps_);
          if (status != royale::CameraStatus::SUCCESS)
          {
              cerr << "[ERROR] Could not get camera frame rate. "
                        << royale::getStatusString(status).c_str() << endl;
              return USE_CASE_ERROR;
          }
        }
      }
    }

    // Check frame rate setting
    std::string delimiter1 = "_";
    std::string delimiter2 = "FPS";
    // find first "_"
    size_t first = use_case_.find(delimiter1);
    first = first + delimiter1.size();
    // find second "_"
    size_t second = use_case_.find(delimiter1, first);
    // position of fist character of frame rate
    second = second + delimiter1.size();
    size_t last = use_case_.find(delimiter2);
    std::string fps_string(&use_case_[second], &use_case_[last]);
    int fps_int(std::stoi(fps_string));
    uint16_t usecase_fps = static_cast<uint16_t>(fps_int);

    if ( usecase_fps == fps_) {
      cout << "== Frame Rate " << fps_ << " set correctly" << endl;
    }else{
      cerr << "[ERROR] Camera Device frame rate "
                << fps_ << " not equal to use case "
                << fps_int << endl;
      return USE_CASE_ERROR;
    }

    // std::clog << "[SUCCESS] All initialize tests passed. " << std::endl;
    cout << "== ToF Camera Is Initialized " << endl; //Running.G Edit
    return NONE;
}


Camera::CameraError Camera::RunAccessLevelTests(int user_level)
{
    // Get the access level
    royale::CameraAccessLevel level;
    royale::CameraStatus status = camera_->getAccessLevel(level);


    if (status != royale::CameraStatus::SUCCESS)
    {
        cerr << "[ERROR] Could not grab the access level. " 
                  << royale::getStatusString(status).c_str() << endl;
        return ACCESS_LEVEL_ERROR;
    }

    // Check if access level was set properly
    access_level_ = static_cast<int>(level);
    cout << "== Check if access level is set properly: " << int (access_level_) << endl; //Running.G Edit

    if (access_level_ != user_level)
    {
        cerr << "[ERROR] Access level mismatch. " << access_level_
                  << "!=" << user_level << endl;
        return ACCESS_LEVEL_ERROR;
    }

    if (status == CameraStatus::SUCCESS)
    {
        // std::clog << "[SUCCESS] successfully used the writeRegisters API" << std::endl;
        cout << "== Successfully Write Register" << endl; // Running.G Edit
    }
    else
    {
        cout << "[ERROR] failed to use the writeRegisters API" << endl;
    }

    // std::clog << "[SUCCESS] All access level tests passed. " << std::endl;
    cout << "== Access Level Test Passed" << endl; // Running.G Edit

    return NONE;
}


Camera::CameraError Camera::RunPatternTest(int testPattern) 
{
    royale::CameraStatus status;

    switch (testPattern){
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
    
    //status = camera_->writeRegisters({{ "0xA0A3", 0x1000}}); // Default code
    
    return NONE;
    
}








