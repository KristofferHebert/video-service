#include "video.h"
#include <iostream>

int main(int argc, char ** argv) {
  /* 

  Arguments:
  First Argument is URL
  Second Argument is Width
  Third Argument is Height
  Fourth Argument Output Folder
  
  Example Usage:
  ./main https://sample-videos.com/video123/mp4/720/big_buck_bunny_720p_1mb.mp4 168 94 $PWD
  
  */

  if(!argv[1] || !argv[2] || !argv[3] || !argv[4]){
    std::cout << "Please provide correct arguments" << std::endl;
    std::cout << "Exiting..." << std::endl;
    return 0;
  }
  Video video(argv[1], argv[2], argv[3], argv[4]);
  video.fetch();
  video.generateThumbnailFromVideo();
  video.generateGIFromVideo();
};