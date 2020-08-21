#include <iostream>
#include <string.h>
#include <cstring>
#include <stdio.h>
#include <fstream>
#include "H_GUIConfig.hpp"
#include <bits/stdc++.h>
using namespace std;

void H_GUIConfig::GetDataFromFile(std::string url)
{
    fstream json_file;
    json_file.open(url,ios::in);
    string data; 
    string line;
}
