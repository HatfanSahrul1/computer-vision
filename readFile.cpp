// #include <iostream>
// #include <fstream>
// #include <string>
// using namespace std;
// int main(){
//    fstream newfile;
//    // newfile.open("tpoint.txt",ios::out);  // open a file to perform write operation using file object
//    // if(newfile.is_open()){ //checking whether the file is open {
//    //    newfile<<"Tutorials point \n"; //inserting text
//    //    newfile.close(); //close the file object
//    // }
//    newfile.open("frame_0.xml",ios::in); //open a file to perform read operation using file object
//    if (newfile.is_open()){ //checking whether the file is open
//       string tp;
//       while(getline(newfile, tp)){ //read data from file object and put it into string.
//          cout << tp << "\n"; //print the data of the string
//       }
//       newfile.close(); //close the file object.
//    }
// }

#include <iostream>
#include <fstream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    // Read the XML file into a string
    fstream xmlFile("frame_0.xml");
    
    if (!xmlFile.is_open()) {
        cerr << "Error: Could not open the XML file." << endl;
        return -1;
    }

    string xmlContent((istreambuf_iterator<char>(xmlFile)), istreambuf_iterator<char>());

    // Close the file
    xmlFile.close();

    // Parse the XML content
    FileStorage fs(xmlContent, FileStorage::READ | FileStorage::MEMORY);

    // Extract image information
    Mat img;
    fs["annotation"]["object"]["bndbox"]["xmin"] >> img; // Assuming "xmin" contains the image data
    // You might want to load the actual image file here and assign it to 'img'

    // Extract bounding box information
    int xmin, ymin, xmax, ymax;
    fs["annotation"]["object"]["bndbox"]["xmin"] >> xmin;
    fs["annotation"]["object"]["bndbox"]["ymin"] >> ymin;
    fs["annotation"]["object"]["bndbox"]["xmax"] >> xmax;
    fs["annotation"]["object"]["bndbox"]["ymax"] >> ymax;

    // Draw bounding box on the image
    rectangle(img, Point(xmin, ymin), Point(xmax, ymax), Scalar(0, 255, 0), 2);

    // Display the image with bounding box
    imshow("Bounding Box", img);
    waitKey(0);

    return 0;
}
