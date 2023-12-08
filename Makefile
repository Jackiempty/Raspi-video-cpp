CC:=g++
obj:=image.cpp video.cpp face.cpp camera.cpp
exe:= image video face camera
lib:=-I/usr/local/include/opencv4 -lopencv_video -lopencv_core  -lopencv_highgui -lopencv_videoio -lopencv_objdetect -lopencv_imgproc -lopencv_imgcodecs -std=c++11 -Wl,-rpath,/usr/local/lib

all:$(obj)
	$(CC) -o image image.cpp $(lib)
	$(CC) -o video video.cpp $(lib)
	$(CC) -o face face.cpp $(lib)
	$(CC) -o camera camera.cpp $(lib)

.PHONY:image
image:image.cpp
	$(CC) -o image image.cpp $(lib)

.PHONY:video
video:video.cpp
	$(CC) -o video video.cpp $(lib)

.PHONY:face
face:face.cpp
	$(CC) -o face face.cpp $(lib)

.PHONY:camera
camera:camera.cpp
	$(CC) -o camera camera.cpp $(lib)

.PHONY:fall
fall:fall.cpp	
	$(CC) -o fall fall.cpp $(lib)

.PHONY:clean
clean:
	rm -rf $(exe)