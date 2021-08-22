#ifndef LIDAR_MINI_LIB
    #define LID_MINI_LIB


#include <iostream>
#include <fstream>
#include <string>

#include <nlohmann/json.hpp>
#include <set>

using json = nlohmann::json;

size_t groundPointsFromCloud(json point_cloud, json *ground_point_cloud);

bool export_pc_json(json point_cloud, char* file_path);
bool export_pc_xyz(json point_cloud, char* file_path);


#endif