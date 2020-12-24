#include "route_planner.h"
#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::sort;
using std::vector;

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;
    RoutePlanner::start_node = &m_Model.FindClosestNode(start_x, start_y);
  	RoutePlanner::end_node = &m_Model.FindClosestNode(end_x, end_y);
  	start_node->g_value = 0.0;
  	start_node->h_value = CalculateHValue(start_node);
}



float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
  	RouteModel::Node *endnode = RoutePlanner::end_node;
  	float h_value = node->distance(*endnode);
	return h_value;
}



void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
  current_node->FindNeighbors();
  if (current_node->neighbors.size()>0)
  {
    for ( RouteModel::Node * nearby : current_node->neighbors)
    {
      nearby->parent = current_node;
      nearby->h_value = RoutePlanner::CalculateHValue(nearby);
      nearby->g_value = current_node->g_value + nearby->distance(*current_node); 
      nearby->visited = true;
      RoutePlanner::open_list.push_back(nearby);
    }
  }
}


bool Compare(RouteModel::Node const *a,RouteModel::Node *b)
{
  float f1 = a->h_value + a->g_value;
  float f2 = b->h_value + b->g_value;
  return (f1 < f2);
}





RouteModel::Node *RoutePlanner::NextNode() {
  sort(RoutePlanner::open_list.begin(), RoutePlanner::open_list.end(),Compare);
  RouteModel::Node *next_node = RoutePlanner::open_list.front();
  RoutePlanner::open_list.erase(RoutePlanner::open_list.begin());
  return next_node;
}



std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;
  	RouteModel::Node *parent_node = nullptr;
  	path_found.push_back(*current_node);
  	while (current_node != RoutePlanner::start_node)
    { 
      parent_node = current_node->parent;
      path_found.push_back(*parent_node);
      distance+=current_node->distance(*parent_node);
      current_node = parent_node;
    }
    std::reverse(path_found.begin(),path_found.end());  
    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;
}


void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;
	current_node = RoutePlanner::start_node;
  	current_node->visited = true;
  	RoutePlanner::open_list.push_back(current_node);
  	while (RoutePlanner::open_list.size()>0)
    {
      current_node = RoutePlanner::NextNode();
      if (current_node != RoutePlanner::end_node)
      	RoutePlanner::AddNeighbors(current_node);
      else
        break;
    }
  	m_Model.path = RoutePlanner::ConstructFinalPath(current_node);
}