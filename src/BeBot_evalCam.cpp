#include <string>

#include <boost/shared_ptr.hpp>

#include <rsb/Event.h>
#include <rsb/Factory.h>
#include <rsb/Handler.h>
#include <rsb/filter/OriginFilter.h>

using namespace std;

using namespace boost;

void printMessage(rsb::EventPtr event) {
    shared_ptr<string> message
        = static_pointer_cast<string>(event->getData());

    string sender = event->getScope().getComponents().back();

    cout << "\r" << sender << ": " << *message  << endl
         << "> ";
    cout.flush();
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "usage: " << argv[0] << " NICKNAME" << endl;
        return EXIT_FAILURE;
    }
    string nick = argv[1];

    rsb::Factory &factory = rsb::Factory::getInstance();

    rsb::Informer<string>::Ptr informer
        = factory.createInformer<string>("/chat/text/" + nick);
    rsb::ListenerPtr listener = factory.createListener("/chat/text");
    listener->addFilter(rsb::filter::FilterPtr(new rsb::filter::OriginFilter(informer->getId(), true)));
    listener->addHandler(rsb::HandlerPtr(new rsb::EventFunctionHandler(&printMessage)));

    while (true) {
        cout << "> ";
        cout.flush();
        shared_ptr<string> message(new string());
        getline(cin, *message);
        if (*message == "/quit") {
            break;
        }
        informer->publish(message);
    }

    return EXIT_SUCCESS;
}


////
//#include <iostream>
////
//#include "opencv2/core/core.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include <boost/shared_ptr.hpp>
//#include <ctime>
//
//
////
////
////using namespace boost;
////using namespace cv;
//using namespace std;
//
////const string WIN_NAME = "Camera View";
//
////// Print out the recieved octree
////void getMessage(rsb::EventPtr event);
//
//int main() {
//
//
//  // Creating the cam object
//  cv::VideoCapture cam;
//  // Open the device /dev/video0
//  cam.open(3);
//  // Allocate a frame object to store the picture
////  cv::Mat frame;
//  boost::shared_ptr<cv::Mat> frame(new cv::Mat(240,320,CV_8UC3));
//
//
////  cv::Mat(240,320,cv::CV_8UC3)
//  //(320,240,cv::CV_8UC3)
//
//  // Read the key
////  int key = cv::waitKey(DELAY);
//
//  // Process the cam as long as it is open
////  cam.isOpened()
//
//  unsigned int start = clock();
//
//  for (int i = 0; i < 100 ; i++) {
//std::cout << i << std::endl;
//    // Save the actual picture to the frame object
//    cam >> *frame;
//
//
//    //    cv::waitKey(1000);
////    // Show the picture
////    cv::imwrite(cv::format("%d.ppm", i), frame);
////    cv::imshow(WIN_NAME, frame);
//    // Send the data.
////          informer->publish(frame);
//
////    // Read a keystroke
////    key = cv::waitKey(DELAY);
////
////    // If the keystroke was ESC, then break
////    if (KEY_ESC == key)
////      break;
//  }
//
//
//  std::cout << "time in sec.:" << ((float)clock() - start)/CLOCKS_PER_SEC << std::endl;
//  // Free the cam
//  cam.release();
//
//  return 0;
//
//}
//
//
////void getMessage(rsb::EventPtr event) {
////
////        // Get the data
////    shared_ptr<cv::Mat> message_rec = static_pointer_cast<cv::Mat>(event->getData());
////
//////    std::cout << "blah" << std::endl;
////    // Write OcTree to file
//////    cv::imshow("Show It", *message_rec);
//////    cv::imwrite( "Image.jpg", *message_rec );
////}
