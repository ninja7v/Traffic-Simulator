// Libraries
//#include <list> // To use lists // alreads included in vehicle.h
#if DEBUG
#include <iostream>     // To use input/output
#endif
// Header files
#include "../headers/Map.h"

namespace {
   const double INFINTY = 999999.0;
}

Road* Map::connections[constants::nbIntersections][constants::nbIntersections];
std::vector<std::vector <double>> Map::cost = { constants::nbIntersections, std::vector<double>(constants::nbIntersections, INFINTY) };
std::vector<std::vector <double>> Map::live_cost = { constants::nbIntersections, std::vector<double>(constants::nbIntersections, INFINTY) };

Map::Map() {
}

std::list<Road*> Map::track(Intersection* begin, Intersection* end) {
   std::list<Road*> path;
   double distance[constants::nbIntersections];
   double mindistance;
   int pred[constants::nbIntersections];
   int visited[constants::nbIntersections];
   int nextnode, i, j;
   // Parameters initialization from start
   for (i = 0; i < constants::nbIntersections; i++) {
      distance[i] = live_cost[begin->getID()][i];
      pred[i] = begin->getID();
      visited[i] = 0;
   }
   distance[begin->getID()] = 0;
   visited[begin->getID()] = 1;
   // Find shortest path
   for (j = 1; j < constants::nbIntersections; j ++) {
      mindistance = INFINTY;
      for (i = 0; i < constants::nbIntersections; i++)
         if (distance[i] <= mindistance && !visited[i]) {
            mindistance = distance[i];
            nextnode = i;
         }
      visited[nextnode] = 1;
      for (i = 0; i < constants::nbIntersections; i++)
         if (!visited[i])
            if (mindistance + live_cost[nextnode][i] < distance[i]) {
               distance[i] = mindistance + live_cost[nextnode][i];
               pred[i] = nextnode;
            }
   }
   // Affect result
   i = end->getID();
   while (i != begin->getID()) {
      path.push_front(connections[pred[i]][i]);
      i = pred[i];
   };
   return path;
};

Road* Map::getConnection(const int a, const int b) const {
   return connections[a][b];
}

void Map::setConnection(const int a, const int b, Road* r) {
   connections[a][b] = r;
   cost[a][b] = r->getLength();
}

void Map::updateConnection(Road* r) {
   const double penalty = !r->containVehicle() ? 0.0 :
      cost[r->getStart()->getID()][r->getEnd()->getID()] / r->getVehicles().back()->distance(r->getStart()) - 1;
   live_cost[r->getStart()->getID()][r->getEnd()->getID()] = cost[r->getStart()->getID()][r->getEnd()->getID()] + penalty;
}
