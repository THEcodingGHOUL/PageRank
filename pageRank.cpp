/*  Assignment 
 *	Name - Robin Saxena
 *	Roll No - 17075049
 */


#include<bits/stdc++.h>
using namespace std;

//page Rank algorithm 
//Reference : https://courses.cs.washington.edu/courses/cse373/17au/project3/project3-3.html
// Graph is custom designed ...5 nodes only....


/*******************All Data Structures and Variables Definition*******************/

vector<int>adj[6]; // To store the nodes..which it links to..
unordered_map<int,double> PageRankValues,UpdatedValues;
double totalLinks;
double decayFactor; //  it's a parameter that represents the rate at which your surfers are willing to "continue clicking" a link.
double epsilon; // will be used to check if the algorithm has converged or not




/********************Implementation of Functions************************************/

void createGraphofWebpages(){
	/* 
		graph is :

		1 -->3
		2 -->1,3
		3 -->5
		4 -->2,3,5
		5 -->3
	*/
	adj[1].push_back(3);
	adj[2].push_back(1);
	adj[2].push_back(3);
	adj[3].push_back(5);
	adj[4].push_back(2);
	adj[4].push_back(3);
	adj[4].push_back(5);
	adj[5].push_back(3);

}

void initialize(){
	totalLinks=8; // from the design of the graph

	for(int i=1;i<=5;++i){
		PageRankValues[i] = 1/totalLinks;
		// initially page Rank values of all the nodes are kept identical and eual to 1/totallinks...
		UpdatedValues[i] =0; // will temporary store the page rank of each node for each iteration
	}

	decayFactor =0.85;
	//0.025
	epsilon =0.03;

}

void pageRank(){

	bool flag =true;
	while(flag){
		for(int j=1;j<=5;++j){   					// for each node
			double uniqueLinks = adj[j].size();		// total no of outgoing edges
			if(uniqueLinks==0){
				for(int k=1;k<=5;++k){
					UpdatedValues[k] += decayFactor * (PageRankValues[j]/totalLinks);
				}
			}
			else{
				for(auto k : adj[j]){
					UpdatedValues[k] += decayFactor * (PageRankValues[j]/uniqueLinks);
				}
			}
		}

		for(int k=1;k<=5;++k){
			UpdatedValues[k] += (1 - decayFactor)/totalLinks;
		}

		int count=0;    			// stores the no of nodes where the difference between current and previous rank values is less than epsilon
		for(int k=1;k<=5;++k){
			if(abs(UpdatedValues[k] - PageRankValues[k]) < epsilon) count +=1;
		}

		for(int k=1;k<=5;++k){ 					// updates the values after each iteration
			PageRankValues[k]=UpdatedValues[k];
			UpdatedValues[k]=0;
		}

		if(count==5) flag = false;

	}
}

void printfinalPageRankValues(){
	for(int k=1;k<=5;++k){
		cout << "page rank value of node " << k << "is :" << PageRankValues[k] << endl;
	}
}

int main(){

	createGraphofWebpages();
	initialize();
	pageRank();
	printfinalPageRankValues();
	return 0;
}