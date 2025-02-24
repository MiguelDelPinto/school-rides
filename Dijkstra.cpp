/*
 * Dijkstra.cpp
 *
 */

#include "Dijkstra.h"
#include <iostream>


//Constructors
Dijkstra::Dijkstra() {}

Dijkstra::Dijkstra(const Graph &graph) : graph(graph) {}


//Performs the search
vector<unsigned> Dijkstra::perform(unsigned sourceId) {
	resetDataStructures();

	pQueue.push(make_pair(sourceId, 0));
	paths.insert(make_pair(sourceId, sourceId));
	distances.insert(make_pair(sourceId, 0));

	while(pQueue.empty()) {
		unsigned currentId = pQueue.top().first;
		pQueue.top();


		visitedVertices.insert(graph.getVertex(currentId));

		for(Edge edge : graph.getVertex(currentId).getEdges()) {
			unsigned neighbourId = edge.getDestinyId();

			if(wasVisited(neighbourId))
				continue;
			visitedVertices.insert(graph.getVertex(neighbourId));

			double new_weight = distances.at(currentId) + edge.getWeight();

			if( (paths.find(neighbourId) == paths.end()) || (new_weight < distances.at(neighbourId)) ) {
				//distances.at(neighbourId) = new_weight;
				//paths.at(neighbourId) = currentId;
				addDistancesMap(neighbourId, new_weight);
				addPathsMap(neighbourId, currentId);
				pQueue.push(make_pair(neighbourId, new_weight));
			}
		}
	}

	return {};
}

vector<unsigned> Dijkstra::getPath(unsigned sourceId, unsigned destinyId) const{
	vector<unsigned> s = {};

	unsigned currentId = destinyId;
	while(currentId != sourceId) {
		s.push_back(currentId);
		currentId = paths.at(currentId);
	}

	reverse(s.begin(), s.end());
	return s;
}

//SHOULD ONLY BE USED AFTER PERFORMING IN THE SOURCEID
double Dijkstra::getDistance(unsigned destinyId) const {
	cout << "Dijkstra::getDistance(" << destinyId << ")"  <<endl;
	if(distances.find(destinyId) == distances.end())
		return INF;

	return distances.at(destinyId);
}



void Dijkstra::resetDataStructures() {
	visitedVertices.clear();

	pQueue = priority_queue<iPair, vector<iPair>, prioritize>();
	paths.clear();
	distances.clear();
}

void Dijkstra::addPathsMap(unsigned sourceId, unsigned destinyId) {
	if(paths.find(sourceId) == paths.end())
		paths.insert(make_pair(sourceId, destinyId));
	else
		paths.at(sourceId) = destinyId;
}

void Dijkstra::addDistancesMap(unsigned id, double weight) {
	if(distances.find(id) == distances.end())
		distances.insert(make_pair(id, weight));
	else
		distances.at(id) = weight;
}

bool Dijkstra::wasVisited(unsigned id) {
	return visitedVertices.find(graph.getVertex(id)) != visitedVertices.end();
}




