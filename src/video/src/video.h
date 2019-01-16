#ifndef VIDEO
#define VIDEO
#include <iostream>
#include <string> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <opencv2/opencv.hpp> 
#include <curl/curl.h>
extern "C" {
#include <libavcodec/avcodec.h>
}

class Video {

  std::string originalFileUrl;
  std::string fileName;
  std::string videoS3Url;
  std::string thumbnailS3Url;
  std::string thumbnail;
  std::string outputPath;  
  char* thumbnailWidth;
  char* thumbnailHeight;

  const char * filePath;
  public:
    Video(std::string fl, char* tW, char* tH, std::string outputPath);
  static size_t writeFile(void * pointer, size_t size, size_t count, void * stream);

  std::string getFilenameFromUrl(std::string originalFileUrl);
  void optimizeVideo();
  void generateThumbnailFromVideo();
  void generateGIFromVideo();
  void fetch();
};
#endif