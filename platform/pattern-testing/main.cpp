#include <iostream>
#include <string>
#include <getopt.h>
#include <unistd.h>
#include <royale/ICameraDevice.hpp>
#include <CameraFactory.hpp>

using namespace std;
using namespace royale;
using namespace platform;
#include "camera.h"

std::string VERSION{"1.3"};
const bool EXIT_ON_ERROR = true;

void print_help() {
  std::cout <<
        "-v                   Show program version\n"
        "-l                   Set line counter test pattern\n"
        "-o                   Set overflow counter test pattern\n"
        "-a                   Set alternating line counter and toggling constant test pattern\n"
        "-t                   Set toggling constant test pattern\n"	
        "-h                   Show help\n";
  exit(EXIT_FAILURE);
}

#define OPTSTR "vr:m:h:loat"

typedef struct {
  string         version;
  int            numSecondsToStream;
  royale::String test_mode;
  int teston;
} options_t;

int main(int argc, char **argv)
{
  int opt;
  // Default options
  options_t options = { VERSION, 15, "MODE_9_5FPS", 1};
  // std::string ACCESS_CODE = "d79dab562f13ef8373e906d919aec323a2857388";
  std::string ACCESS_CODE = "c715e2ca31e816b1ef17ba487e2a5e9efc6bbd7b";
  // CameraFactory factory;
  Camera cam;
  int testPattern;
  Camera::CameraError error;
  
  
  // [Verification] Access Level Test
  if (!ACCESS_CODE.empty()) { error = cam.RunAccessLevelTests(3); }
  else { error = cam.RunAccessLevelTests(1); }
  if (EXIT_ON_ERROR && error != Camera::CameraError::NONE) { return error; }
  
      
  if (argc > 1) 
  {
    while ((opt = getopt(argc, argv, OPTSTR)) != -1) 
    {
      switch(opt) {
        case 'v':
          std::cout << "Version: " << options.version << std::endl;
          exit(EXIT_FAILURE);
          break;
        case 'l':
          testPattern = 1;
          break;
        case 'o':
          testPattern = 2;
          break;
        case 'a':
          testPattern = 3;
          break;
        case 't':
          testPattern = 4;
          break;
        case 'h':
        default:
          print_help();
          break;
      }
    }
  }
  else
  {
    std::cout << "Using Default Settings." << std::endl;
    std::cout << "Streaming Time [seconds]: " << options.numSecondsToStream << std::endl;
    std::cout << "Setting ToF Mode: " << options.test_mode << std::endl;
  }
  
  
  // [Setup] Camera Config Test
  error = cam.RunConfigTests(testPattern);
  if (EXIT_ON_ERROR && error != Camera::CameraError::NONE) { return error; }
  
  
  return 0;
}

