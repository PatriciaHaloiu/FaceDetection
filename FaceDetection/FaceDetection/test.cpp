#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>
#include<iostream>

using namespace std;
using namespace cv;

/*void main() {
	string path = "IMG_0139.JPG";
	Mat	img = imread(path);
	imshow("Frame", img);
	waitKey(0);
}

void main() {
	VideoCapture video(0);
	Mat img;
	while (true) {
		video.read(img);
		imshow("Frame", img);
		waitKey(0);
	}
}*/


void applySepia(Mat& img) {
    Mat kernel = (Mat_<float>(3, 3) <<
        0.272, 0.534, 0.131,
        0.349, 0.686, 0.168,
        0.393, 0.769, 0.189);
    transform(img, img, kernel);
}

void applyNegative(Mat& img) {
    bitwise_not(img, img);
}

void applyBlur(Mat& img) {
    GaussianBlur(img, img, Size(15, 15), 0);
}

void applyEdgeDetection(Mat& img) {
    Canny(img, img, 50, 150);
}


void overlayImage(const Mat& background, const Mat& foreground, Mat& output, Point2i location)
{
    background.copyTo(output);

    for (int y = max(location.y, 0); y < background.rows; ++y) {
        int fY = y - location.y; 

        if (fY >= foreground.rows)
            break;

        for (int x = max(location.x, 0); x < background.cols; ++x) {
            int fX = x - location.x; 

            if (fX >= foreground.cols)
                break;

            double opacity = ((double)foreground.data[fY * foreground.step + fX * foreground.channels() + 3]) / 255;

            for (int c = 0; opacity > 0 && c < output.channels(); ++c) {
                unsigned char foregroundPx = foreground.data[fY * foreground.step + fX * foreground.channels() + c];
                unsigned char backgroundPx = background.data[y * background.step + x * background.channels() + c];
                output.data[y * output.step + output.channels() * x + c] =
                    backgroundPx * (1. - opacity) + foregroundPx * opacity;
            }
        }
    }
}

int main() {
    VideoCapture video(0);
    CascadeClassifier facedetect;
    Mat img;
    facedetect.load("haarcascade_frontalface_default.xml");


    if (!video.isOpened()) {
        cerr << "Error: Could not open the camera." << endl;
        return -1;
    }

    Mat hat = imread("heart.png", IMREAD_UNCHANGED);
    if (hat.empty()) {
        cerr << "Error: Could not load hat image." << endl;
        return -1;
    }

    Mat hat1 = imread("bird.png", IMREAD_UNCHANGED);
    if (hat1.empty()) {
        cerr << "Error: Could not load hat image." << endl;
        return -1;
    }

    namedWindow("Frame", WINDOW_AUTOSIZE);
    int  effect = 0;
    int hatEffect = 0;

    while (true) {
        video.read(img);

        switch (effect) {
        case 1:
            cvtColor(img, img, COLOR_BGR2GRAY);  // Efect alb-negru
            break;
        case 2:
            applySepia(img);  // Efect sepia
            break;
        case 3:
            applyNegative(img);  // Efect negativ
            break;
        case 4:
            applyBlur(img);  // Efect blur
            break;
        case 5:
            applyEdgeDetection(img);  // Efect detectie margini
            break;
        default:
            break;  // Niciun efect
        }

        vector<Rect> faces;
        facedetect.detectMultiScale(img, faces, 1.3, 5);

        cout << faces.size() << endl;

        for (int i = 0; i < faces.size(); i++) {
            Rect face = faces[i];

            int hatWidth = face.width;
            int hatHeight = hatWidth * hat.rows / hat.cols;
            Point hatPosition(face.x, face.y - hatHeight);

            if (hatPosition.y < 0) {
                hatPosition.y = 0;
            }

            Mat resizedHat;

            if (hatEffect == 1) {
                resize(hat, resizedHat, Size(hatWidth, hatHeight));
                overlayImage(img, resizedHat, img, hatPosition);
            }
            else if (hatEffect == 2) {
                resize(hat1, resizedHat, Size(hatWidth, hatHeight));
                overlayImage(img, resizedHat, img, hatPosition);
            }

            rectangle(img, face.tl(), face.br(), Scalar(50, 50, 255), 1);
        }

        if (img.empty()) {
            cerr << "Error: Captured frame is empty." << endl;
            break;
        }

        imshow("Frame", img);

        char key = (char)waitKey(30);
        if (key == 27) break;  // Tasta 'Esc' pentru a iesi
        if (key == '1') effect = 1;  // Alb-negru
        if (key == '2') effect = 2;  // Sepia
        if (key == '3') effect = 3;  // Negativ
        if (key == '4') effect = 4;  // Blur
        if (key == '5') effect = 5;  // Detectie margini
        if (key == '0') effect = 0;  // Niciun efect
        if (key == 'h') hatEffect = 1; // Afiseaza imaginea 'heart'
        if (key == 'b') hatEffect = 2; // Afiseaza imaginea 'bird'
        if (key == 'n') hatEffect = 0; // Nici o imagine
    }
    video.release();
    //destroyAllWindows();

    return 0;
}