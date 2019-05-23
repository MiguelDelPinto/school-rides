/*
 * Network.cpp
 *
 */

#include "Network.h"
#include <cmath>

Network::Network() {
	numberOfBus = 0;
};

void Network::loadMap(const Graph& newMap) {
	map = newMap;
}

Graph Network::getMap() {
	return map;
}

vector<Vertex> Network::getSchools() {
	return schools;
}

Vertex Network::getSchool(){
	return school;
}

Vertex Network::getGarage(){
	return garage;
}

void Network::setSchool(unsigned id){
	school = map.getVertexSet().at(id);
}

void Network::setGarage(unsigned id){
	garage = map.getVertexSet().at(id);
}

void Network::insertAddress(unsigned id){
	childrenVertices.push_back(map.getVertexSet().at(id));
}

void Network::removeAddress(unsigned id){
	vector<Vertex> newVector = {};
	for (size_t i = 0; i < childrenVertices.size(); i++){
		if (childrenVertices[i].getId() != id)
			newVector.push_back(childrenVertices[i]);
	}

	childrenVertices = newVector;
}


void Network::calculatePathMatrix(){
	unsigned v = map.getNumVertex();
	unsigned e = map.getNumEdges();
	distances = {};
	paths = {};
	if ((v+e)*log2((double)v)*childrenVertices.size() > pow(v, 3)){
		//Neste caso calcular FloydWarshall
		FloydWarshall FW = FloydWarshall(map);
		FW.perform();
		//O ciclo abaixo aloca os resultados em duas matrizes (distances e paths)
		for (size_t i = 0; i < childrenVertices.size(); i++){
			distances.push_back({});
			paths.push_back({});
			for (size_t j = 0; j < childrenVertices.size(); j++){
				FW.getDistance(childrenVertices[i].getId(), childrenVertices[j].getId());
				paths[i].push_back(FW.getPath(childrenVertices[i].getId(), childrenVertices[j].getId()));
			}
		}
		for (size_t i = 0; i < childrenVertices.size(); i++){
			//as informacoes sobre a escola e a garagem sao postas em vetores separados
			distancesFromSchool.push_back(FW.getDistance(school.getId(), childrenVertices[i].getId()));
			distancesToGarage.push_back(FW.getDistance(childrenVertices[i].getId(), garage.getId()));

			pathsFromSchool.push_back(FW.getPath(school.getId(), childrenVertices[i].getId()));
			pathsToGarage.push_back(FW.getPath(childrenVertices[i].getId(), garage.getId()));

		}
	}
	else {
		//Neste caso calcular Dijkstra para cada v�rtice
		/*
		 * Algo assim (quando o Dijkstra estiver pronto):
		for (size_t i = 0; i < childrenVertices.size(); i++){
			Dijkstra Dij = Dijkstra(map, childrenVertices[i]);
			Dij.perform();
		}*/
	}
}



Matrix Network::getDistances(){
	return distances;
}

vector<vector<vector<unsigned>>> Network::getPaths(){
	return paths;
}

vector<double> Network::getDistancesFromSchool(){
	return distancesFromSchool;
}

vector<double> Network::getDistancesToGarage(){
	return distancesToGarage;
}

vector<vector<unsigned>> Network::getPathsFromSchool(){
	return pathsFromSchool;
}

vector<vector<unsigned>> Network::getPathsToGarage(){
	return pathsToGarage;
}







