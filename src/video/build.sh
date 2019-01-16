g++ src/main.cpp src/video.cpp -o ./main $(pkg-config --cflags --libs opencv libcurl)

# how to use execute
# ./main https://sample-videos.com/video123/mp4/720/big_buck_bunny_720p_1mb.mp4 168 94
# ./main http://mirrors.standaloneinstaller.com/video-sample/dolbycanyon.m4v 168 94