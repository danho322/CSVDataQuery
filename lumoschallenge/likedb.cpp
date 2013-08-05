//
//  likedb.cpp
//  lumoschallenge
//
//  Created by Daniel Ho on 8/2/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <math.h>

using namespace std;

enum queryType { TARGETED_LIKES, NEARBY_GENDER, UNKNOWN_QUERY };
enum genderType { MALE, FEMALE, UNKNOWN_GENDER };

struct user{
    string name;
    string phone;
    int x;
    int y;
    string gender;
};

map<string, user> users;
vector<user> males;
vector<user> females;
map<string, vector<string> > likes;

static string trimString(string stringToTrim, bool removePunct)
{
    stringToTrim.erase(remove_if(stringToTrim.begin(), stringToTrim.end(), ::isspace), 
               stringToTrim.end() );
    if (removePunct)
    {
        stringToTrim.erase(remove_if(stringToTrim.begin(), stringToTrim.end(), ::ispunct),
                           stringToTrim.end() );
    }
    return stringToTrim;
}

static void storeUserData(ifstream &data, string &line, bool isGenderQuery)
{
    if (line.length() == 0)
    {
        return;
    }
    
    user thisUser;
    stringstream lineStream(line);
    string cell;
    
    getline(lineStream,cell,',');
    thisUser.name = cell;
    
    getline(lineStream,cell,',');
    cell = trimString(cell, false);
    thisUser.phone = cell;
    
    getline(lineStream,cell,',');
    thisUser.x = atoi(cell.c_str());
    
    getline(lineStream,cell,',');
    thisUser.y = atoi(cell.c_str());

    getline(lineStream,cell,',');
    cell = trimString(cell, true);
    thisUser.gender = cell;
    
    if (isGenderQuery)
    {
        if (thisUser.gender.compare("male") == 0)
        {
            males.push_back(thisUser);
        }
        else
        {
            females.push_back(thisUser);
        }
    }
    else
    {
        users[thisUser.name] = thisUser;
    }
}

static void storeLikeData(ifstream &data, string &line)
{
    if (line.length() == 0)
    {
        return;
    }
    
    stringstream lineStream(line);
    string name;
    string like;
    
    getline(lineStream,name,',');
    
    getline(lineStream,like,',');
    like = trimString(like, true);
    
    vector<string> likeVector;
    if (likes.find(like) != likes.end())
    {
        likeVector = likes[like];
    }
    likeVector.push_back(name);
    likes[like] = likeVector;
}

static float distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
    float xDiff = x2 - x1;
    float yDiff = y2 - y1;
    return sqrt( xDiff * xDiff + yDiff * yDiff );
}

static void likesQuery(string likeString, float distance, float x, float y)
{
    // Show me all users within DISTANCE radius of (X, Y) that like LIKE
    // Output:
    // "Cory Virok", "555-223-2121", 37, 122, "male
    // "Alice Cooper", "123-666-0101", 21, 102, "female"
    vector<string> names = likes[likeString];
    for(vector<int>::size_type i = 0; i != names.size(); i++) {
        user thisUser = users[names[i]];
        float userDistance = distanceBetweenPoints(x, y, thisUser.x, thisUser.y);
        if (userDistance <= distance)
        {
            cout << thisUser.name << ", " << thisUser.phone << ", " << thisUser.x << ", " <<
                    thisUser.y << ", \"" << thisUser.gender << "\"" << endl;
        }
    }
}


static void genderQuery(bool isMale, float distance)
{
    // Get all GENDER users that are within DISTANCE of each other
    // Output:
    // "Cory Virok", "Nikola Tesla", 19.8
    // "Steve Jobs", "Cory Virok", 11.9
    // "Steve Jobs", "Joel Spolsky", 15.0
    vector<user> genderUsers = (isMale) ? males : females;
    vector<int>::size_type vectorSize = genderUsers.size();
    for(vector<int>::size_type i = 0; i < vectorSize - 1; i++) {
        user thisUser = genderUsers[i];
        
        for(vector<int>::size_type j = i + 1; j != vectorSize; j++) {
            user compareUser = genderUsers[j];
            float userDistance = distanceBetweenPoints(thisUser.x, thisUser.y, compareUser.x, compareUser.y);
            if (userDistance <= distance)
            {
                cout << thisUser.name << ", " << compareUser.name << ", " << userDistance << endl;
            }
        }
    }
}

int main (int argc, const char * argv[])
{
    float distance = -1;
    float x = 0;
    float y = 0;
    queryType queryArg = UNKNOWN_QUERY;
    genderType genderArg = UNKNOWN_GENDER;
    string likeString = "";
    
    // $>./likedb -q targeted_likes distance=5 x=27 y=127 like="pizza"
    // $>./likedb -q nearby_gender distance=20 gender=male
    for (int i = 1; i < argc; ++i)
    {
        if (string(argv[i]) == "-q")
        {
            if (i + 1 < argc)
            {
                string queryString = argv[++i];
                if (queryString == "targeted_likes")
                {
                    queryArg = TARGETED_LIKES;
                }
                else if (queryString == "nearby_gender")
                {
                    queryArg = NEARBY_GENDER;
                }
            }
            else
            {
                cerr << "Include query type" << endl;
            }
        }
        else
        {
            string s = string(argv[i]);
            string delimiter = "=";
            size_t pos = 0;
            string argToken;
            if ((pos = s.find(delimiter)) != string::npos) {
                argToken = s.substr(0, pos);
                s.erase(0, pos + delimiter.length());
                
                if (argToken == "distance")
                {
                    distance = atoi(s.c_str());
                }
                else if (argToken == "x")
                {
                    x = atoi(s.c_str());
                }
                else if (argToken == "y")
                {
                    y = atoi(s.c_str());
                }
                else if (argToken == "like")
                {
                    likeString = s;
                }
                else if (argToken == "gender")
                {
                    s = trimString(s, true);
                    if (s == "male")
                    {
                        genderArg = MALE;
                    }
                    else if (s == "female")
                    {
                        genderArg = FEMALE;
                    }
                }
            }
        }
        
    }
    
    ifstream  userData("users.csv");
    string line;
    while(getline(userData,line))
    {
        storeUserData(userData, line, (queryArg == NEARBY_GENDER) );
    }
    
    if ( queryArg == TARGETED_LIKES )
    {
        ifstream  likeData("likes.csv");
        while(getline(likeData,line))
        {
            storeLikeData(likeData, line);
        }
    }
    
    if (queryArg == UNKNOWN_QUERY)
    {
        cerr << "Unknown query type" << endl;
    }
    else
    {
        if (distance == -1)
        {
            cerr << "Enter a valid distance" << endl;
        }
        else
        {
            if (queryArg == NEARBY_GENDER)
            {
                if (genderArg == UNKNOWN_GENDER)
                {
                    cerr << "Enter a valid gender" << endl;
                }
                else
                {
                    genderQuery( (genderArg == MALE), distance);
                }
            }
            else if (queryArg == TARGETED_LIKES)
            {
                likesQuery(likeString, distance, x, y);
            }
        }
    }
    
    return 0;
}

