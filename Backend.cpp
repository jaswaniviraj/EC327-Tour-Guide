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
    vector <Info> v;
    while (true) {
        myd >> activity >> city >> weather >> time; 
        if (!myd) break;
        v.push_back(Info(activity, city, weather, time));
    }
    myd.close();
    for (auto e: v){
    cout << e.a << "\n";
    }
    
    //GUI SFML @YOUSEF @SOUD
    cout<<"Enter time or choose the current time: \n";
    cout<<"Type: Morning Afternoon Evening Night\n";
    /*YOUSEF SOUD, this needs to be two boxes they click on the screen
    for the purpose rn the input will manual*/ 
    string choice_time;
    cin >> choice_time;
    if (choice_time == "Morning") {choice_time = 6;}
    else if (choice_time == "Afternoon") {choice_time = 7;}
    else if (choice_time == "Evening") {choice_time = 8;}
    else if (choice_time == "Night") {choice_time = 9;}

    for (auto e: v){
        if (e.t.find('6') != std::string::npos){
            cout << e.a << "\n";
        }
    
    }

}
