#include <iostream>
#include <fstream>
#include <string>

#include <nlohmann/json.hpp>
#include <set>

using namespace std;
using json = nlohmann::json;


#define DENSITY_PROBE_Z ((float)0.5)
struct point_3d {
    size_t number;
    float x;
    float y;
    float z;
};

bool comp_by_z(point_3d a, point_3d b){
    return a.z < b.z;
}

size_t groundPointsFromCloud(json point_cloud, json *ground_point_cloud){
    // converting json to set, where points are sorted by z
    set<point_3d, decltype(&comp_by_z)> point_cloud_set(&comp_by_z);
    for(json::iterator itr = point_cloud.begin(); itr != point_cloud.end(); itr++){
        point_3d point = {stoull(itr.key()), (*itr)["x"], (*itr)["y"], (*itr)["z"]};
        point_cloud_set.insert(point);
    }    

    // structues holds range of the most dense point cloud slice along z axis
    struct {
        size_t length = 0;
        set<point_3d>::iterator group_begin;
        set<point_3d>::iterator group_end;
    } ground_point_cloud_trim;

    // single pass to find dense point cloud
    size_t length = 0;
    set<point_3d>::iterator itr_begin = point_cloud_set.begin();
    set<point_3d>::iterator itr_end = point_cloud_set.begin();
    while(itr_end != point_cloud_set.end()){

        if(length > ground_point_cloud_trim.length){
            ground_point_cloud_trim.length = length;
            ground_point_cloud_trim.group_begin = itr_begin;
            ground_point_cloud_trim.group_end   = itr_end;
        }

        while(itr_begin->z  + DENSITY_PROBE_Z < itr_end->z){
            length--;
            itr_begin++;
        }     
        length++;
        itr_end++;
    }
    
    // additionaly return everything below ground points
    json ground_point_cloud_buffer = {};
    for(set<point_3d>::iterator itr = ground_point_cloud_trim.group_begin; itr != ground_point_cloud_trim.group_end; itr++){
        ground_point_cloud_buffer[to_string(itr->number)] = {
            {"x", itr->x},
            {"y", itr->y},
            {"z", itr->z}
        };
    }

    *ground_point_cloud = ground_point_cloud_buffer;
    return ground_point_cloud_trim.length;
}


bool export_pc_json(json point_cloud, char* file_path){
    
    // init output file stream
    ofstream file_output(file_path);

    // write json
    file_output << point_cloud;

    // close file stream
    file_output.close();

    return true;
}

bool export_pc_xyz(json point_cloud, char* file_path){

    // init output file stream
    ofstream file_output(file_path);
    file_output << endl;                // empty first line required for .xyz files

    // "flattening" every point into single line
    for(json::iterator itr = point_cloud.begin(); itr != point_cloud.end(); itr++){
        file_output << (*itr)["x"] << " ";
        file_output << (*itr)["y"] << " ";
        file_output << (*itr)["z"] << endl;
    }    

    // closing file stream
    file_output.close();
    
    return true;
}