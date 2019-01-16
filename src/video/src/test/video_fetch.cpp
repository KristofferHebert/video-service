#include <string>
#include "gtest/gtest.h"
#include "video.h"

// Test video fetch functionality

TEST(video, fetch){

  https://sample-videos.com/video123/mp4/720/big_buck_bunny_720p_1mb.mp4 168 94

    std::string fl = "https://sample-videos.com/video123/mp4/720/big_buck_bunny_720p_1mb.mp4";
    char* tW = "168";
    char* tH = "94";
    std::string oP = "/tmp";

    // Initialize video
    Video video(fl, tW, tH, oP);
    
    // Fetch video from URL
    video.fetch();

    // Test existance of video file
    FILE * f = fopen("/tmp/big_buck_bunny_720p_1mb.mp4", "r");
    ASSERT_TRUE(f != NULL);
    fclose(f);
}