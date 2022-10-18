#include <iostream>
#include <string>
#include <getopt.h>
#include <unistd.h>
#include <royale/ICameraDevice.hpp>
#include <CameraFactory.hpp>
#include <royale.hpp>
#include "camera.h"

using namespace std;
using namespace royale;
using namespace platform;

std::string VERSION{"1.3"};
const bool EXIT_ON_ERROR = true;

void print_help() {
  cout <<
        "-v                   Show program version.\n"
        "-r <n>               Set number of seconds to record: -r 60\n"
        "-m <str>             Set ToF mode: -m MODE_9_5FPS\n"
        "-h                   Show help\n";
  exit(EXIT_FAILURE);
}

#define OPTSTR "vr:m:h"

typedef struct {
  string         version;
  int            numSecondsToStream;
  royale::String test_mode;
} options_t;

int main(int argc, char **argv)
{
  int opt;
  // Default options
  options_t options = { VERSION, 15, "MODE_9_5FPS" };
  // std::string ACCESS_CODE = "d79dab562f13ef8373e906d919aec323a2857388";
  std::string ACCESS_CODE = "c715e2ca31e816b1ef17ba487e2a5e9efc6bbd7b";
  // CameraFactory factory;
  Camera cam;

  if (argc > 1) {
    while ((opt = getopt(argc, argv, OPTSTR)) != -1) {
      switch(opt) {
        case 'v':
          cout << "Version: " << options.version << endl;
          exit(EXIT_FAILURE);
          break;
        case 'r':
          options.numSecondsToStream = std::stoi(optarg);
          if (options.numSecondsToStream < 10) {
            options.numSecondsToStream = 10;
            cout << "Minimum Streaming Time is 10 Seconds." << endl;
          }
          cout << "Streaming Time [seconds]: " << options.numSecondsToStream << endl;
          if (options.numSecondsToStream > 300) {
            cout << "USING STREAM TEST-MODE : Output will be stream to /dev/null" << endl;
          }
          break;
        case 'm':
          options.test_mode = royale::String(optarg);
          cout << "Setting ToF Mode: " << options.test_mode << endl;
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
    // std::cout << "Using Default Settings." << std::endl;
    cout << "== ToF Cam Pattern Test Start" << endl;
    cout << "== Streaming Time [seconds]: " << options.numSecondsToStream << endl;
    cout << "== Setting ToF Mode: " << options.test_mode << endl;
  }

  // [Setup] Camera Initialization Test
  //Camera::CameraError error = cam.RunInitializeTests(options.test_mode);
  //if (EXIT_ON_ERROR && error != Camera::CameraError::NONE) { return error; }

  Camera::CameraError error;
  // [Setup] Access Level Test
  //if (!ACCESS_CODE.empty()) { error = cam.RunAccessLevelTests(3); }
  //else { error = cam.RunAccessLevelTests(1); }
  //if (EXIT_ON_ERROR && error != Camera::CameraError::NONE) { return error; }

  // [Streaming] Pattern Tests
  error = cam.RunPatternTest(1);
  if (EXIT_ON_ERROR && error != Camera::CameraError::NONE) { return error; }

  return 0;
}
