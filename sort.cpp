#include <iostream>
#include <vector>
#include <algorithm>

struct objectDetect {
    int id;
    bool exist;
    float confidence;
};

// Comparator function to sort objectDetect structures by confidence in descending order
bool CompareByConfidence(const objectDetect& a, const objectDetect& b) {
    return a.confidence > b.confidence;
}

objectDetect SortByConfidence(std::vector<objectDetect>& landmarkList) {
    // Sort the vector by confidence in descending order
    std::sort(landmarkList.begin(), landmarkList.end(), CompareByConfidence);

    // Return the objectDetect with the highest confidence (first element after sorting)
    return landmarkList[0];
}

void newDNN() {
    
    std::vector<objectDetect> landmark;
    while (true) {
        // Your existing code here...

        landmark.clear();
        landmark = {
            {1, true, 0.8},
            {2, true, 0.6},
            {3, true, 0.9},
            {4, true, 0.7}
        };
        
        
        objectDetect bestLandmark = SortByConfidence(landmark);
        std::cout<<bestLandmark.id<<"\t"<<bestLandmark.confidence<<std::endl;
    }
}

int main(){
    newDNN();
    return 0;
}