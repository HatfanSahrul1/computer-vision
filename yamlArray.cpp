#include <iostream>
#include <yaml-cpp/yaml.h>

struct init_id{
    double Xinit;
    double Yinit;
    double Zinit;
};
int main() {
        init_id kl[29];
    try {
        // Load YAML file
        YAML::Node config = YAML::LoadFile("/home/hatfan/parameters/vision/camera_calibration/world_coordinate.yaml");

        // Access the 'points' array
        const YAML::Node& points = config["points"];
        double x[29],y[29],z[29];
        // Iterate over each point object
        int j=0;
        for (const auto& point : points) {
            // if(j<29){
                kl[j].Xinit = point["Xinit"].as<double>();
                kl[j].Yinit = point["Yinit"].as<double>();
                kl[j].Zinit = point["Zinit"].as<double>();
            // }
            std::cout<<j<<"\t";
            std::cout << "Xinit: " << kl[j].Xinit << ", Yinit: " << kl[j].Yinit << ", Zinit: " << kl[j].Zinit << std::endl;
            if(j<29)
                j++;

            // Process each point (Xinit, Yinit, Zinit)
        }
    } catch (const YAML::Exception& e) {
        std::cerr << "YAML parsing error: " << e.what() << std::endl;
        return 1;
    }
    for(int i=0;i<29;i++){
            std::cout<<i<<"\t";
        std::cout << "Xinit: " << kl[i].Xinit << ",\t Yinit: " << kl[i].Yinit << ",\t Zinit: " << kl[i].Zinit << std::endl;
    }

    return 0;
}
