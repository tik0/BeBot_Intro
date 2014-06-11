/*
 * image.c - Camera image demo
 *
 * This file is part of openrobotix-utils.
 *
 * Copyright(C) 2013
 * Stefan Herbrechtsmeier <sherbrec@cit-ec.uni-bielefeld.de>
 * http://opensource.cit-ec.de/projects/openrobotix-utils
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * The development of this software was supported by the
 * Excellence Cluster EXC 277 Cognitive Interaction Technology.
 * The Excellence Cluster EXC 277 is a grant of the Deutsche
 * Forschungsgemeinschaft (DFG) in the context of the German
 * Excellence Initiative.
 *
 */

//
#include <iostream>
//
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "MatConverter.hpp"

#include <boost/shared_ptr.hpp>
#include <rsb/filter/OriginFilter.h>

#include <rsb/Factory.h>

#include <rsb/converter/Repository.h>
#include <rsb/converter/ProtocolBufferConverter.h>


//
//
using namespace std;
using namespace cv;
using namespace rsb;
using namespace converter_Mat;
using namespace rsb::converter;

//const int KEY_ESC = 27;
//const int DELAY = 30;

//const string WIN_NAME = "Camera View";

int main() {

  // Creating the cam object
  cv::VideoCapture cam;
  // Open the device /dev/video0
//  try
//    {
//      cam.open(0);
//    }
//  catch (int e) {
//  std::cout << "DEVICE NOT OPENED\n";
//
//  }
  cam.open(0);
  cam.release();

//  cam.open(1);
//  if (!cam.isOpened())
//    std::cout << "DEVICE NOT OPENED\n";
//  cam.release();
//  cam.open(2);
//  if (!cam.isOpened())
//    std::cout << "DEVICE NOT OPENED\n";
//  cam.release();
  cam.open(3);
  if (!cam.isOpened())
    std::cout << "DEVICE NOT OPENED\n";

//  cam.open("/dev/video3");
  // Allocate a frame object to store the picture
//  cv::Mat frame(320, 240, CV_8UC3);
  shared_ptr<cv::Mat> frame(new cv::Mat(320, 240, CV_8UC3));

  //  fmt.fmt.pix.width       = 320;
  //  fmt.fmt.pix.height      = 240;
  //  fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_RGB24;
  //  fmt.fmt.pix.field       = V4L2_FIELD_ANY;

//  // Read the key
//  int key = cv::waitKey(DELAY);

  int i = 0;
  vector<int> compression_params;
  compression_params.push_back(CV_IMWRITE_PXM_BINARY);
  compression_params.push_back(1);


  ////////////////////////////////////////////////////////////////////////////////////////////////////
  // Register our converter within the collection of converters for
  // the string wire-type (which is used for arrays of octets in
  // C++).
//  shared_ptr<MatConverter> converter(new MatConverter());
//  converterRepository<std::string>()->registerConverter(converter);
//
//
//  rsb::Factory &factory = rsb::Factory::getInstance();
//
//  // Create the informer
//  Informer<Mat>::Ptr informer =
//          getFactory().createInformer<Mat> (Scope("/image"));


  boost::shared_ptr< rsb::converter::ProtocolBufferConverter<MatConverter> > converter(new rsb::converter::ProtocolBufferConverter<MatConverter>());
  rsb::converter::converterRepository<std::string>()->registerConverter(converter);

  // After the converter has been registered, the default
  // configuration used by the Factory includes the converter.
  Factory& factory = Factory::getInstance();
  // Create the informer
  Informer<MatConverter>::Ptr informer = factory.createInformer<MatConverter> ("/image");
  ////////////////////////////////////////////////////////////////////////////////////////////////////

  // Process the cam as long as it is open
  for (; cam.isOpened();) {

    // Save the actual picture to the frame object
    cam >> *frame;
    cv::imwrite(cv::format("%d.ppm", i), *frame, compression_params);

//    // Show the picture
//    cv::imshow(WIN_NAME, frame);
//

//    // If the keystroke was ESC, then break
//    if (KEY_ESC == key)
//      break;

    // Send the data.
      informer->publish(frame);

    i++;
    if (i == 10)
      break;
  }

  // Free the cam
  cam.release();

  return 0;

}
