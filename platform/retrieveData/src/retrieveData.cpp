/****************************************************************************\
* Copyright (C) 2017 pmdtechnologies ag
*
* THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
\****************************************************************************/

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


//#include <sample_utils/PlatformResources.hpp>  Running.G Edit

#ifndef ROYALE_ACCESS_CODE_LEVEL2
//#define ROYALE_ACCESS_CODE_LEVEL2 "" // Insert activation code here
#endif

//using namespace sample_utils;
using namespace std;
using namespace royale;
using namespace platform;
using std::ofstream;


class MyRawListener : public royale::IExtendedDataListener
{
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

    
    void onNewData (const royale::IExtendedData *data) override
    {
        if (data->hasRawData())
        {
            const royale::RawData* rawData =  data->getRawData();

            // for (int rawFrameIdx = 0; rawFrameIdx < rawData->rawData.size(); rawFrameIdx++)
            for (int rawFrameIdx = 0; rawFrameIdx < 1; rawFrameIdx++)
            {
                /*
                cout << "\n-- Observing raw frame #" << rawFrameIdx
                     << " used to generate depth image # " << depthImageNumber
                     << " --" << std::endl;
                */
                //const uint16_t* rawPixelArray = rawData->rawData[rawFrameIdx];
                rawPixelArray = rawData->rawData[rawFrameIdx];

                for (int row = 0; row < rowNum; row++)
                {
                     for (int col = 0; col < colNum; col++)
                    {   
                        size_t rawPixelIdx = row * rawData->width + col;
                        //cout << left << setfill(' ') << setw(7) << hex << rawPixelArray[rawPixelIdx];
                        //cout << left << setfill(' ') << setw(5) << rawPixelArray[rawPixelIdx];  
                        testResult.push_back(rawPixelArray[rawPixelIdx]);  

                    }
                    //cout << std::endl;
                }
                firstPxlValue = rawData->rawData[0][0 * rawData->width + 0];
                cout << "First pixel value: " << firstPxlValue << endl; 
            }
        }

    
        //GENERATE EXPECTED LIST
        testPattern = 1;
        switch (testPattern)
        {
            case 1:
                // ! THIS MACHANISM IS DESIGNED FOR - LINE COUNTER TEST MODE; 
                expectedArray[0] = 0;
                //cout << "\n====== PRINT OUT EXPECTED ARRAY ====== \n";
                for (counter = 0; counter < arraySize - 1 + 10; counter++)
                {
                    if (expectedArray[counter] < 0xdf){
                        //cout << left << setfill(' ') << setw(5) << hex << expectedArray[counter] << " ";
                        //expectedArray[counter + 1] = expectedArray[counter] + inc; 
                        expectedArray[counter + 1] = expectedArray[counter] + 0x1; 

                    }
                    else{
                        expectedArray[counter + 1] = 0x0;
                    } 
                }
                break;
        
            case 2:
                // ! THIS MACHANISM IS DESIGNED FOR - OVERFLOW TEST MODE
                expectedArray[0] = firstPxlValue;
                //const int inc = 0x1;
                //cout << "\n====== PRINT OUT EXPECTED ARRAY ====== \n";
                for (counter = 0; counter < arraySize - 1 + 10; counter++){
                    if (expectedArray[counter] < 0xfff){
                        //cout << left << setfill(' ') << setw(5) << hex << expectedArray[counter] << " ";
                        expectedArray[counter + 1] = expectedArray[counter] + 0x1; 
                    }
                    else{
                        expectedArray[counter + 1] = 0x0;
                    } 
                }
                break;
        
            case 3:
                // ! THIS MACHANISM IS DESIGNED FOR - ALTERNATING LINE COUNTER AND TOGGLING TEST PATTERN
                while (counter != arraySize)
                {
                    for (int row = 0; row < rowNum; row++)
                    {
                        for (int col = 0; col < colNum; col++) 
                        {
                            if (row % 2 == 0) 
                            {
                                if (col % 2 == 0)
                                {
                                    expectedArray[counter] = 0x5a5;
                                }
                                else
                                {
                                    expectedArray[counter] = 0xa5a;
                                }
                                counter++;
                            }
                            else
                            {
                                expectedArray[counter] = col; 
                                counter++;
                            }
                        }
                    }
                }
                break;

            //cout << "===== Expected array:" << endl;
            //for (auto v : expectedArray)
            //{
            //    cout << hex << v << " ";
            //}
            //cout << endl;
        
            case 4:
                // ! THIS MACHANISM IS DESIGNED FOR - TOGGLING CONSTANT TEST PATTERN
                while (counter != arraySize)
                {
                    for (int row = 0; row < rowNum; row++)
                    {
                        for (int col = 0; col < colNum; col++) 
                        {
                            if (col % 2 == 0)
                            {
                                expectedArray[counter] = 0x5a5;
                            }
                            else
                            {
                                expectedArray[counter] = 0xa5a;
                            }
                            counter++;
                        }
                    }
                }
                break;

        }


        //COMPARE THE ACTUAL VALUES WITH EXPECTED VALUES
        ofstream outdata; // outdata is like cin
        int pointer = 0;
        cout << "Comparing actual data to expected data...\n";
        outdata.open("Comparison.txt"); // opens the file

        if(!outdata ) 
        { // file couldn't be opened
            cerr << "Error: file could not be opened" << endl;
            exit(1);
        }
        for (auto i = testResult.begin(); i != testResult.end(); )
        {
            outdata << "At position: ";
            outdata << pointer << " || Act: " << hex << *i << " || Exp: " << hex << expectedArray[pointer] << "\n";
            if (*i != expectedArray[pointer])
            {
                cout << "== Fail, actual value is: " << hex << *i;
                cout << " || expected value is: " << hex << expectedArray[pointer];
                cout << " || at position: " << pointer;
                break;
            } 
            i++;
            pointer++;
            if (i == testResult.end())
            {
                cout << "== Pass, actuall values are identical to expected values";
            }
        } 

        cout << " Please see data in home/root/Comparison.txt" << endl;
        outdata.close();
    }
    
};


int main()
{
    // Windows requires that the application allocate these, not the DLL.
    //PlatformResources resources;

    // This is the data listener which will receive callbacks.  It's declared
    // before the cameraDevice so that, if this function exits with a 'return'
    // statement while the camera is still capturing, it will still be in scope
    // until the cameraDevice's destructor implicitly deregisters the listener.
    MyRawListener listener;

    // Check if we have the appropriate access level
    // (the following operations need Level 2 access)
    // if (royale::CameraManager::getAccessLevel (ROYALE_ACCESS_CODE_LEVEL2) < royale::CameraAccessLevel::L2)
    // {
    //     cerr << "Please insert the activation code for Level 2 into the define at the beginning of this program!" << endl;
    //     return 1;
    // }

    // this represents the main camera device object
    unique_ptr<royale::ICameraDevice> cameraDevice;

    // the camera manager will query for a connected camera

    CameraFactory factory;
    cameraDevice = factory.createCamera();

    // the camera device is now available and CameraManager can be deallocated here

    if(cameraDevice == nullptr)
    {
        cerr << "Cannot create the camera device" << endl;
        return 1;
        
    }
    cout << "Initialize devices end ok" << endl;
    // {
    //     //royale::CameraManager manager (ROYALE_ACCESS_CODE_LEVEL2);
    //     royale::CameraManager manager (ROYALE_ACCESS_CODE_LEVEL3);  // Running.G Edit for Level 3 Pattern Test

    //     auto camlist = manager.getConnectedCameraList();
    //     cout << "Detected " << camlist.size() << " camera(s)." << endl;
    //     if (!camlist.empty())
    //     {
    //         cout << "CamID for first device: " << camlist.at (0).c_str() << " with a length of (" << camlist.at (0).length() << ")" << endl;
    //         cameraDevice = manager.createCamera (camlist[0]);
    //     }
    // }



    // IMPORTANT: call the initialize method before working with the camera device
    if (cameraDevice->initialize() != royale::CameraStatus::SUCCESS)
    {
        cerr << "Cannot initialize the camera device" << endl;
        return 1;
    }

    if (cameraDevice->registerDataListenerExtended (&listener) != royale::CameraStatus::SUCCESS)
    {
        cerr << "Couldn't register the extended data listener" << endl;
        return 1;
    }

    // Set the callbackData you want to receive
    // (if you call cameraDevice->setCallbackData (CallbackData::Raw)
    // before initializing the camera Royale can also open cameras without
    // calibration data and return raw images)
    if (cameraDevice->setCallbackData (royale::CallbackData::Intermediate) != royale::CameraStatus::SUCCESS)
    {
        cerr << "Cannot set the callbackData" << endl;
        return 1;
    }

    // start capture mode
    if (cameraDevice->startCapture() != royale::CameraStatus::SUCCESS)
    {
        cerr << "Error starting the capturing" << endl;
        return 1;
    }

    // let the camera capture for some time
    this_thread::sleep_for (chrono::milliseconds (300)); //5 frames/s;


    // stop capture mode
    if (cameraDevice->stopCapture() != royale::CameraStatus::SUCCESS)
    {
        cerr << "Error stopping the capturing" << endl;
        return 1;
    }

    return 0;
}


