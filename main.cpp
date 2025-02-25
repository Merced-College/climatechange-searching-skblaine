// main.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <string>
//#include "StateClimate.h"

using namespace std;

// StateClimate.h
class StateClimate {
private:
    int fips;
    int year;
    double temp;
    double tempc;

public:
    // Constructor
    StateClimate(int f, int y, double t, double tc);

    // Getters
    int getFips() const;
    int getYear() const;
    double getTemp() const;
    double getTempC() const;

    // Setters
    void setFips(int f);
    void setYear(int y);
    void setTemp(double t);
    void setTempC(double tc);

    // Display function
    void display() const;
};

// StateClimate.cpp
// Constructor
StateClimate::StateClimate(int f, int y, double t, double tc) : fips(f), year(y), temp(t), tempc(tc) {}

// Getters
int StateClimate::getFips() const { return fips; }
int StateClimate::getYear() const { return year; }
double StateClimate::getTemp() const { return temp; }
double StateClimate::getTempC() const { return tempc; }


//Setters
void StateClimate::setFips(int f) { fips = f; }
void StateClimate::setYear(int y) { year = y; }
void StateClimate::setTemp(double t) { temp = t; }
void StateClimate::setTempC(double tc) { tempc = tc; }


// Display function
void StateClimate::display() const {
    cout << "FIPS: " << fips << ", Year: " << year 
              << ", Temp (F): " << temp << ", Temp (C): " << tempc << endl;
}

//binary search here
int binarySearch (const vector<StateClimate> &data, int fips){
    int high = data.size() - 1;
    int low = 0;
    int mid;

    while (low <= high){
        mid = (low + high) / 2;
        if (data[mid].getFips() == fips){ 
            return mid; // if mid matched user fips, return mid
        }
        else if (data[mid].getFips() < fips){
            low = mid + 1;
        }
        else{
            high = mid - 1;
        }
    }
    return -1;
}


int main() {
    vector<StateClimate> climateData;
    ifstream file("climdiv_state_year.csv");
    
    if (!file) {
        cerr << "Error opening file!" << std::endl;
        return 1;
    }

    string line;
    getline(file, line); // Skip header line
    while (getline(file, line)) {
        stringstream ss(line);
        int fips, year;
        double temp, tempc;
        char comma;

        ss >> fips >> comma >> year >> comma >> temp >> comma >> tempc;
        climateData.emplace_back(fips, year, temp, tempc);
    }

    file.close();

    // search loop here
    string userinput;
    while(true){
        cout << "Enter a state FIPS to search (or 'exit' to quit): ";
        cin >> userinput;

        if (userinput == "exit"){ // while loop will break if user enters 'exit'
            break;
        }

        int fips = stoi(userinput); // 'stoi' converts the user fips to an integer 
        int index = binarySearch(climateData, fips); // start the binary search using the user fips
       
        if (index != -1) {
            climateData[index].display(); // will display data using the display function
        } else {
            cout << "State not found. Please try again." << endl;
        }
    }

/*
    // Display data
    for (const auto &entry : climateData) {
        entry.display();
    }

*/

    return 0;
}
