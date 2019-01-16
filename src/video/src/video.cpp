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

#include "video.h"
    Video::Video(std::string fl, char* tW, char* tH,  std::string oP) {
      originalFileUrl = fl;
      fileName = Video::getFilenameFromUrl(originalFileUrl);
      thumbnailWidth = tW;
      thumbnailHeight = tH;

      // Add trailing slash if it does not exist
      if(oP.back() != '/'){
        oP = oP + '/';
      }
      outputPath = oP;
    }

  size_t Video::writeFile(void * pointer, size_t size, size_t count, void * stream) {
    return fwrite(pointer, size, count, (FILE * ) stream);
  }

  std::string Video::getFilenameFromUrl(std::string originalFileUrl) {
    const size_t lastSlash = originalFileUrl.find_last_of("/");
    std::string fileName;
    if (std::string::npos != lastSlash) {
      fileName = originalFileUrl.erase(0, lastSlash + 1);
    }
    return fileName;
  }
  void Video::optimizeVideo() {
    // read video
    // print video fileSize
    // optimize video
    // print new video fileSize
    // save video
    // upload to S3*
  }
  void Video::generateThumbnailFromVideo() {
    // read video
    cv::VideoCapture video;
    video.open(filePath);

    if (!video.isOpened()) {
      std::cout << "Video not found" << std::endl;
      return;
    }

    std::cout << "Reading Video opened from " << filePath << std::endl;
    
    int sec = 0;

    // Capture first frame
    cv::Mat frame;
    cv::Mat resized;
    video >> frame;
    thumbnail = fileName.substr(0,fileName.find_last_of('.')) + ".jpg";
    cv::resize(frame, frame, cv::Size(atoi(thumbnailWidth), atoi(thumbnailHeight)));
    cv::imwrite(outputPath + thumbnail, frame);

    while (true) {

      // Capture frame-by-frame
      video >> frame;

      // If the frame is empty, break immediately
      if (frame.empty())
        break;

      // Capture 50th frame
      if(sec == 10){
        cv::resize(frame, frame, cv::Size(atoi(thumbnailWidth), atoi(thumbnailHeight)));
        std::cout << "Generating Thumbnail " << std::endl;
        cv::imwrite(outputPath + thumbnail, frame);
        break;
      }
      sec++;
    }

    // // When everything done, release the video capture object
    // video.release();

    // // Closes all the frames
    // cv::destroyAllWindows();

    // generate thumbnail from video
    // save thumbnail to /tmp
    // handle thumbnail error
    // upload to S3*
    // return thumbnail path

  }
  void Video::generateGIFromVideo(){
    std::cout << "Generating GIF from Video to " << outputPath << " ..." << std::endl;

    std::string name = fileName.substr(0,fileName.find_last_of('.'));
    std::string command = "src/videotogif.sh " + outputPath + fileName + " " + outputPath + name + ".gif " + thumbnailWidth + " " + thumbnailHeight;
    
    // Use C++ to execute bash script with arguments
    system(command.c_str());
  }
  void Video::fetch() {

    CURL * curl;
    FILE * videoFile;
    CURLcode response;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    std::string tmpFilePath = outputPath + fileName;
    filePath = tmpFilePath.c_str();
    videoFile = fopen(filePath, "wb");

    if (curl && videoFile) {
      // Set CURL URL
      curl_easy_setopt(curl, CURLOPT_URL, originalFileUrl.c_str());

      // Save Video file to temp folder
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFile);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, videoFile);

      std::cout << "Fetching " << fileName << " from " << originalFileUrl << std::endl;

      // Perform CURL Request
      response = curl_easy_perform(curl);

      if (response != CURLE_OK) {
        std::cout << "Geting Video failed" << std::endl;
        std::cout << curl_easy_strerror(response) << std::endl;
      }

      curl_easy_cleanup(curl);
      fclose(videoFile);
    }

  curl_global_cleanup();

    std::cout << "Video fetch completed " << std::endl;

  }
