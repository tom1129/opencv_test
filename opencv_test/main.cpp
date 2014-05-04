//
//  main.cpp
//  opencv_test
//
//  Created by Watson on 5/3/14.
//  Copyright (c) 2014 Watson. All rights reserved.
//

// Example showing how to read and write images
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cvaux.hpp>
#include <stdlib.h>


using namespace cv;
int main(int argc, char** argv)
{
    IplImage * pInpImg = 0;
    Mat image = imread("my_image_copy.png");
    int x = 0, y = 0;
    Vec3b intensity;
    Mat gray_image;
    long random_number;

    //get the random number with the seed based on the time when i request a random number
    srand((unsigned)time(NULL));
    random_number = random();


    Mat img1 = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE); Mat img2 = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE); if(img1.empty() || img2.empty())
    {
        printf("Can’t read one of the images\n");
        return -1; }
    // detecting keypoints
    OrbFeatureDetector detector(400);
    vector<KeyPoint> keypoints1, keypoints2;
    detector.detect(img1, keypoints1);
    detector.detect(img2, keypoints2);
    // computing descriptors
    OrbDescriptorExtractor extractor;
    Mat descriptors1, descriptors2;
    extractor.compute(img1, keypoints1, descriptors1);
    extractor.compute(img2, keypoints2, descriptors2);
    // matching descriptors
    BruteForceMatcher<L2<float> > matcher; vector<DMatch> matches;
    matcher.match(descriptors1, descriptors2, matches);
    // drawing the results
    namedWindow("matches", 1);
    Mat img_matches;
    drawMatches(img1, keypoints1, img2, keypoints2, matches, img_matches);
    imshow("matches", img_matches);
    waitKey(0);


    return 0;
}