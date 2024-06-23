#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <ctime>
#include <curl/curl.h>
#include <algorithm>

using std::cout;
using std::cin;
using std::string;
using std::vector;

//Struct to hold activity info
struct Info {
    std::string activity;
    std::string city;
    vector<int> weatherCategories;
    vector<int> timeCategories;
};

// Callbackfunction for cURL to store the response in a string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Function to get real-time weather for a given city using OpenWeather API
float getWeather(const string& city) {
    const string API_KEY = "025250f2b8a9de9718741669ceaa7297"; // Our API key from OpenWeather
    const string API_ENDPOINT = "http://api.openweathermap.org/data/2.5/weather?q=";
    string url = API_ENDPOINT + city + "&units=metric&appid=" + API_KEY;

    CURL* curl;
    CURLcode res;
    string readBuffer;

//initializing cURL
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

//Checking for errors
        if (res != CURLE_OK) {
            std::cerr << "cURL request failed: " << curl_easy_strerror(res) << std::endl;
            return -1; // Return an error value
        }

        // Parse JSON response so as to get the temperature
        auto tempPos = readBuffer.find("\"temp\":");
        if (tempPos != string::npos) {
            size_t endPos = readBuffer.find(",", tempPos);
            if (endPos != string::npos) {
                return std::stof(readBuffer.substr(tempPos + 7, endPos - tempPos - 7));
            }
        }
    }
    return -1; // Return an error value if parsing fails
}

// Function to categorize time based on the hour of the day
int determineTimeCategory(int hour) {
    if (hour >= 6 && hour < 12) return 6; // Morning
    if (hour >= 12 && hour < 17) return 7; // Afternoon
    if (hour >= 17 && hour < 21) return 8; // Evening
    return 9; // Night
}


// Function to categorize weather based on temperature
int determineWeatherCategory(float temperature) {
    if (temperature < 0) return 4;
    else if (temperature < 18) return 3;
    else if (temperature < 29) return 2;
    else return 1;
}



int main() {
    // Hardcoded activities data (I did it like that because i had problems with reading the file)
    vector<Info> activities = {
        {"Acropolis", "Athens", {2, 3}, {6, 7, 8}},
        {"shopping_in_the_city_center", "Athens", {2, 3}, {6, 7, 8}},
        {"Get_coffee_in_Kolonaki", "Athens", {1, 2, 3}, {6, 7, 8}},
        {"Go_swim_in_Vouliagmeni", "Athens", {1, 2}, {6, 7}},
        {"Movie_theater", "Athens", {1, 2, 3, 4, 5}, {8, 9}},
        {"Visit_chora", "Mykonos", {1, 2, 3}, {7, 8, 9}},
        {"Day_parting", "Mykonos", {1, 2}, {6, 7}},
        {"Night_partying", "Mykonos", {1, 2}, {6, 7}},
        {"Go_to_a_Nammos", "Mykonos", {1, 2}, {6, 7, 8}},
        {"Daily_trip_to_Delos", "Mykonos", {1, 2}, {6, 7}},
        {"Shopping_in_Center_Jakarta", "Jakarta", {1, 2, 4}, {7, 8}},
        {"Tour_the_National_Monument_Monas", "Jakarta", {1, 2}, {6, 7, 8}},
        {"Chinatown_Jakarta", "Jakarta", {1, 2}, {8, 9}},
        {"Rooftop_Bar", "Jakarta", {2}, {8, 9}},
        {"Asia's_Largest_Nightclub", "Jakarta", {1, 2, 4}, {9}},
        {"ATV_Cave_Tour", "Bali", {1, 2, 4}, {6, 7}},
        {"Nusa_Penida_Privat_island_tour", "Bali", {1, 2}, {6, 7, 8}},
        {"Day_Beach_Club", "Bali", {1, 2}, {6, 7}},
        {"Night_beach_Club", "Bali", {1, 2}, {8, 9}},
        {"Atlas_Beach_Club", "Bali", {1, 2}, {8, 9}}
    };

    // Display loaded activities for debugging purposes
    cout << "Loaded activities:\n";
    for (const auto& activity : activities) {
        cout << "Activity: " << activity.activity << ", City: " << activity.city 
             << ", Weather Categories: ";
        for (int w : activity.weatherCategories) cout << w << " ";
        cout << ", Time Categories: ";
        for (int t : activity.timeCategories) cout << t << " ";
        cout << "\n";
    }

    // Get user input for the city and time 
    cout << "Select a City: (Jakarta, Bali, Athens, Mykonos)\n";
    string city;
    cin >> city;

    cout << "Input the time (24 Hr Clock but just the hour):\n";
    int hour;
    cin >> hour;

    // Determine time category based on the hour input
    int timeCategory = determineTimeCategory(hour);
    cout << "Determined time category: " << timeCategory << "\n";

//Get the weather for the selected city
    float temperature = getWeather(city);
    if (temperature == -1) {
        cout << "Failed to get weather data. Please check your network or API key.\n";
        return 1;
    }
    cout << "Current weather in " << city << " is " << temperature << "°C\n";

    //determine weather cat based on the current temp of the city
    int weatherCategory = determineWeatherCategory(temperature);
    cout << "Determined weather category: " << weatherCategory << "\n";

    // Find matching activities based on all the criteria
    bool found = false;
    for (const auto& activity : activities) {
        if (activity.city == city) {
            //checking if the act matches the current time category
            bool timeMatch = std::find(activity.timeCategories.begin(), activity.timeCategories.end(), timeCategory) != activity.timeCategories.end();
            //checking if the act matches the current weather category
            bool weatherMatch = std::find(activity.weatherCategories.begin(), activity.weatherCategories.end(), weatherCategory) != activity.weatherCategories.end();

            //if both time and weather matcg suggest activity
            if (timeMatch && weatherMatch) {
                string suggestedActivity = activity.activity;
                std::replace(suggestedActivity.begin(), suggestedActivity.end(), '_', ' ');
                cout << "Suggested activity: " << suggestedActivity << "\n";
                found = true;
            }
        }
    }
    //if no matching activity is found
    if (!found) {
        cout << "We are sorry, we don't have any recommendations but we are working to get more soon!\n";
    }

    return 0;
}
