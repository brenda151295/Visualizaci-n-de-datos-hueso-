#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(){

    cv::Mat image= cv::imread("LV_60_FEM_R.labels366.png", CV_LOAD_IMAGE_GRAYSCALE);
    cv::Mat contours;
    cv::Mat gray_image;

    std::vector<cv::Mat> channels;
    cv::Canny(image,contours,10,350);


    cv::namedWindow("Canny");
    cv::imshow("Canny",contours);
    cv::waitKey(0);
}