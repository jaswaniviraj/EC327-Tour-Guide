#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using std::ifstream;
using std::cout;
using std::cin;
using std::string;
using std::vector;

struct Info{
    string a,c,w,t;
    Info(string aa, string cc,string ww,string tt){
    a = aa;
    c = cc;
    w = ww;
    t = tt;
    }
};

int main () {
    ifstream myd;
    myd.open("activities.csv");
    string activity, city, weather, time;
    string choice_city,choice_time,choice_weather,suggested_activity;
    vector <Info> v;
    while (true) {
        myd >> activity >> city >> weather >> time; 
        if (!myd) break;
        v.push_back(Info(activity, city, weather, time));
    }
    myd.close();
    /*for (auto e: v){
    cout << e.a << "\n";
    }*/
    
    //MAIN INPUTS
    cout<<"Select a City: (Jakarta, Bali, Athens, Mykonos) \n";
    cin >> choice_city;
    cout<<"Input the time (24 Hr Clock but just the hour): \n";
    int time_entry;
    cin >> time_entry;
        /*YOUSEF SOUD, this needs to be two boxes they click on the screen
        for the purpose rn the input will manual*/
        if (time_entry<12){choice_time = '6';}
        else if (time_entry >=12 && time_entry <17) {choice_time = '7';}
        else if (time_entry >=17 && time_entry <21) {choice_time = '8';}
        else if (time_entry >=21 && time_entry <24) {choice_time = '9';}
    //cout << choice_time;

    cout<<"Input the weather: \n";
    float weather_entry;
    cin >> weather_entry;
        /*YOUSEF SOUD, this needs to be two boxes they click on the screen
        for the purpose rn the input will manual*/
        if (weather_entry>29){choice_weather = '1';}
        else if (weather_entry <=29 && weather_entry >18) {choice_weather = '2';}
        else if (weather_entry <=18 && weather_entry >0) {choice_weather = '3';}
        else if (weather_entry <=0) {choice_weather = '4';}
    //cout << choice_weather;
 
    int checker = 0;
    for (auto e: v){
        if (e.c.find(choice_city) != std::string::npos){
            if (e.t.find(choice_time) != std::string::npos){
                 if (e.w.find(choice_weather) != std::string::npos){
                        suggested_activity = e.a;
                    for (int i = 0;i<suggested_activity.size();i++){
                        if (suggested_activity[i] == '_'){
                            suggested_activity[i] = ' ';
                        }
                    }
                    cout << suggested_activity << "\n";//ADD A IF NOTHING FOUND
                    checker = 1;
                 }
            }
        }
    }
    if (checker == 0) {cout<<"We are sorry, we don't have any recomendations but we are working to get more soon! ";}
}
