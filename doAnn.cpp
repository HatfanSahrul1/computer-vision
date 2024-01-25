#include "pugixml.hpp"
#include <iostream>

using namespace std;

int main() {
    int a, b;
    int xmin,ymin,xmax,ymax;

    std::cout << "Enter start value for name: ";
    std::cin >> a;

    std::cout << "Enter end value for name: ";
    std::cin >> b;

    cout<<"enter the coordinates : ";
    cin>>xmin>>ymin>>xmax>>ymax;

    for (int nameValue = a; nameValue <= b; ++nameValue) {
        // Create a new XML document
        pugi::xml_document doc;

        // Add the root node
        pugi::xml_node annotation = doc.append_child("annotation");

        // Add child nodes to the root
        annotation.append_child("folder").text().set("normal");
        annotation.append_child("filename").text().set("cap_Normal_0.jpg");
        annotation.append_child("path").text().set(("/home/hatfan/fokusL/normal/cap_Normal_" + to_string(nameValue) + ".jpg").c_str());

        // Add source node
        pugi::xml_node source = annotation.append_child("source");
        source.append_child("database").text().set("Unknown");

        // Add size node
        pugi::xml_node size = annotation.append_child("size");
        size.append_child("width").text().set("640");
        size.append_child("height").text().set("480");
        size.append_child("depth").text().set("3");

        annotation.append_child("segmented").text().set("0");

        // Add object node
        pugi::xml_node object = annotation.append_child("object");
        object.append_child("name").text().set("L");
        object.append_child("pose").text().set("Unspecified");
        object.append_child("truncated").text().set("0");
        object.append_child("difficult").text().set("0");

        // Add bndbox node
        pugi::xml_node bndbox = object.append_child("bndbox");
        bndbox.append_child("xmin").text().set(to_string(xmin).c_str());
        bndbox.append_child("ymin").text().set(to_string(ymin).c_str());
        bndbox.append_child("xmax").text().set(to_string(xmax).c_str());
        bndbox.append_child("ymax").text().set(to_string(ymax).c_str());

        // Save the XML document to a file
        string filename = "/home/hatfan/fokusL/normal/cap_Normal_" + to_string(nameValue) + ".xml";
        doc.save_file(filename.c_str());

        cout << "XML file " << filename << " created.\n";
    }

    return 0;
}
