#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/video/background_segm.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
using namespace cv;

int getIndex(vector<float>, float);

int main()
{
    bool fitToEllipse = false;
    VideoCapture cap("queda.mp4"); // in linux check $ ls /dev/video0
    if (!cap.isOpened()) {
        std::cerr << "ERROR: Could not open camera" << std::endl;
        return 1;
    }

    Ptr<BackgroundSubtractorMOG2> fgbg = createBackgroundSubtractorMOG2();
    int j = 0;
    Mat frame;
    Mat gray_image;
    vector<Mat> contours;
    Mat fgmask;
    vector<float> areas;
    Mat cnt;
    Moments M;
    Rect rect;


    while(true)
    {        
        cap >> frame;

        // Convert each frame to gray scale and subtract the background
        cvtColor(frame, gray_image, COLOR_BGR2GRAY);
        
        fgbg->apply(gray_image, fgmask);

        // imshow("gray", fgmask);
        
        // Find contours
        findContours(fgmask, contours,  RETR_TREE, CHAIN_APPROX_SIMPLE);

        if(contours.size() != 0)
        {
            // List to hold all areas
            areas = {};
            for (int j = 0; j < contours.size(); j++)
            {
                float ar = contourArea(contours[j]);
                areas.push_back(ar);
            }

            float max_area = *max_element(areas.begin(), areas.end());
            
            // cout << max_area << endl;
            int max_area_index = getIndex(areas, max_area);
            
            
            // cout << "index:" << max_area_index << endl;
            cnt = contours[max_area_index];
            M = moments(cnt);
            

            rect = boundingRect(cnt);

            drawContours(fgmask, cnt, 0, Scalar(0, 0, 0), 3, 0);
            if (rect.height < rect.width)
                j++;
                // cout << "j: " << j << endl;

            if (j > 10)
            {   
                rectangle(frame, rect, Scalar(0, 0, 225), 4);
                // cout << "should draw now" << endl;
            }

            if (rect.height > rect.width)
            {
                j = 0;
                rectangle(frame, rect, Scalar(0, 225, 0), 2);
            }

            // cout << "x: " << rect.x << endl
            //      << "y: " << rect.y << endl
            //      << "w: " << rect.width << endl
            //      << "h: " << rect.height << endl;

            imshow("video", frame);

            if (waitKey(33) == 27)
            {
                break;
            }
        }
        
    }
    return 0;
}


int getIndex(vector<float> v, float K) 
{ 
    int it = -1;
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == K)
        {
            it = i;
        }
    }
    // If element was found 
    return it;
} 