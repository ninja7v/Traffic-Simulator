// Header files
#include "../headers/Map.h"

Map::Map() {
}

Road* Map::connection(Intersection* i1, Intersection* i2) {
   return connections[i1->getID()][i2->getID()];
}
// This function find the optimal path using Dijkstra algorithn
std::list<Road*> Map::track(Intersection* begin, Intersection* end) {
   std::list<Road*> path;
   float cost[constants::nbIntersections][constants::nbIntersections];
   float distance[constants::nbIntersections];
   int pred[constants::nbIntersections];
   int visited[constants::nbIntersections], count, mindistance, nextnode, i, j;
   // Fill cost matrix
   for (i = 0; i < constants::nbIntersections; i++)
      for (j = 0; j < constants::nbIntersections; j++)
         if (connections[i][j] == nullptr)
            cost[i][j] = INFINITY;
         else
            cost[i][j] = connections[i][j]->getLength();
   // Parameters initialization
   for (i = 0; i < constants::nbIntersections; i++) {
      distance[i] = cost[begin->getID()][i];
      pred[i] = begin->getID();
      visited[i] = 0;
   }
   distance[begin->getID()] = 0;
   visited[begin->getID()] = 1;
   bool exists = false;
   for (count = 1; count < constants::nbIntersections - 1; count ++) {
      exists = false;
      mindistance = INFINITY;
      for (i = 0; i < constants::nbIntersections; i++)
         if (distance[i] < mindistance && !visited[i]) {
            mindistance = distance[i];
            nextnode = i;
            exists = true;
         }
      if (exists == false)
         break;
      visited[nextnode] = 1;
      for (i = 0; i < constants::nbIntersections; i++)
         if (!visited[i])
            if (mindistance + cost[nextnode][i] < distance[i]) {
               distance[i] = mindistance + cost[nextnode][i];
               pred[i] = nextnode;
            }
   }
   i = end->getID();
   count = 0;
   do {
      count++;
      j = i;
      i = pred[i];
      path.push_front(connections[i][j]);
   } while (i != begin->getID() && count< constants::nbIntersections);
   if (count == constants::nbIntersections) {
      path.clear();
      return path;
   }
   else {
      path.push_front(connections[i][j]);
      return path;
   }
};

Road* Map::getConnection(int a, int b) {
   return connections[a][b];
}

void Map::setConnection(int a, int b, Road* r) {
   connections[a][b] = r;
}
