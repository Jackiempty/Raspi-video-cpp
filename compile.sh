# image.cpp
g++ image.cpp -I/usr/local/include/opencv4 -o image -lopencv_core -lopencv_imgcodecs -lopencv_highgui -std=c++11 -Wl,-rpath,/usr/local/lib

# video.cpp
g++ video.cpp -I/usr/local/include/opencv4 -o video -lopencv_core  -lopencv_highgui -lopencv_videoio -std=c++11 -Wl,-rpath,/usr/local/lib

# face.cpp
g++ face.cpp -o face `pkg-config --cflags --libs opencv4` -std=c++11 -Wl,-rpath,/usr/local/lib

# camera.cpp
g++ camera.cpp -I/usr/local/include/opencv4 -o camera -lopencv_core  -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs  -std=c++11 -Wl,-rpath,/usr/local/lib

# fall.cpp
g++ fall.cpp -o main `pkg-config --cflags --libs opencv4` -std=c++11 -Wl,-rpath,/usr/local/lib