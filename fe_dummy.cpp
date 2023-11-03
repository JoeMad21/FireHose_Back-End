#include<fstream>
#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include<unistd.h>

int main() {

    std::ifstream myFile0("results.txt");
    std::string file_status;
    int done = 1;
    std::cout << "Waiting on Back-End...\n";
    while(done) {
        std::getline(myFile0, file_status);
        if (file_status == "F") {
            myFile0.clear();
            myFile0.seekg(0);
        }
        else {
            done = 0;
        }
        sleep(2);
        std::cout << "Waiting on Back-End...\n";
    }

    myFile0.close();

    std::vector<float> results;
    std::vector<float> anomalies;

    std::ifstream myFile("results.txt");

    std::string temp;
    while(myFile.good()) {
        std::getline(myFile, temp);

        if (temp != "") {
            results.push_back(std::stof(temp));
        }
    }

    myFile.close();

    std::ifstream myFile2("anomalies.txt");

    while(myFile2.good()) {
        std::getline(myFile2, temp);

        if (temp != "") {
            anomalies.push_back(std::stof(temp));
        }
    }

    myFile2.close();


    std::cout << "Results\n";
    int root = std::sqrt(results.size());
    for(int i = 0; i < results.size(); i++) {
        std::cout << std::fixed << results[i] << "\t";
        if ( (i+1)%root == 0) {
            std::cout << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Anomalies\n";
    root = std::sqrt(anomalies.size());
    for(int i = 0; i < anomalies.size(); i++) {
        std::cout << std::fixed << anomalies[i] << "\t";
        if ( (i+1)%root == 0) {
            std::cout << std::endl;
        }
    }

    std::ofstream myFile3 ("results.txt");

    myFile3 << "F";

    myFile3.close();

    std::ofstream myFile4 ("anomalies.txt");

    myFile4 << "F";

    myFile4.close();
}