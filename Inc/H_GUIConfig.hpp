#ifndef H_GUICONFIG
#define H_GUICONFIG
#include "../../include/json/json.h"
#include <iostream>
#include <bits/stdc++.h>
#include <string.h>
class H_GUIConfig
{
private:
    /* data */
public:
    H_GUIConfig(/* args */);
    ~H_GUIConfig();
    void GetDataFromFile(std::string url);
};

H_GUIConfig::H_GUIConfig(/* args */)
{
}

H_GUIConfig::~H_GUIConfig()
{
}

#endif // H_GUICONFIG
