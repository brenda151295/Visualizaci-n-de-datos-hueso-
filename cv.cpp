#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <utility>
#include <vector>
#include <stdio.h>


int main( int argc, char** argv ) {
  cv::Mat image = cv::imread(
    "data/LV_60_FEM_R.labels000.png",
    CV_LOAD_IMAGE_GRAYSCALE
  );

  if(! image.data ) {                             // Check for invalid input
    std::cout <<  "Could not open or find the image" << std::endl ;
    return -1;
  }


  std::vector< std::pair<uchar, uchar> > tmp;

  int sum = 0;
  int black = 0;
  for (int row = 0; row < image.rows; ++row)
  {
    const uchar *ptr = image.ptr(row);
    for (int col = 0; col < image.cols; ++col)
    {
      const uchar* uc_pixel = ptr;
      cv::Vec3b& color = image.at<cv::Vec3b>(row, col);
      int a = uc_pixel[0];
      int b = uc_pixel[1];
      int c = uc_pixel[2];           
      if (a && b && c) {
        tmp.push_back(std::make_pair(row, col));
        color[0] = 255;
        color[1] = 255;
        color[2] = 255;
        printf("a %d (%d, %d)\n", a, row, col);
        printf("b %d (%d, %d)\n", b, row, col);
        printf("c %d (%d, %d)\n", c, row, col);
        ++sum;
      } else {
        ++black;
      }
      ptr += 3;
    }
  }
  printf("\nSUM = %d\n", sum);
  printf("\nBLACK = %d\n", black);

  cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);    // Create a window for display.
  cv::imshow("Display window", image );                   // Show our image inside it.

  cv::waitKey(0);                                          // Wait for a keystroke in the window
  return 0;
}
