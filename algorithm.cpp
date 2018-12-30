#include "algorithm.h"

int main(int argc, char* argv[]){
	int alg;
	//select Node Source
	cout<<"Enter Source Node: ";
	cin>>sourceNode;

	//read files
	if (readFiles() == 2){
		//ask for the algorithm to use
		if(sourceNode > 0 && sourceNode < nNodes){
			cout<<"Available algortihm"<<endl<<"Enter 1 for Dijkstra"<<endl<<"Enter 2 for Dial"<<endl<<"Enter option:";
			cin>>alg;
			//run the algorithm
			if(alg == 1)dijkstra();
			else if (alg == 2) dial();
			else cout  << "Something goes wrong with the algorithm selected. Please retry." << endl;
			writeFile();
		}
		else cout  << "Something goes wrong with the source node selected. Please check." << endl;
	}
	else cout  << "Something goes wrong with the files. Please check." << endl;
	return 0;
}

int readFiles(){
/************************************/
/*Description:			    */
/*This function read the files 	    */
/*nodos.txt and arcos.txt           */
/*and set the number of nodes and   */
/*the topology			    */
/*Returns:			    */
/*0 Can not read files		    */
/*1 Read 1 file			    */
/*2 Read both files	            */  		
/************************************/
	int output = 0;
	string line;
	ifstream nodos("nodos.txt");
	ifstream arcos("arcos.txt");
	int sNode;
	int dNode;
	int cost;

	//get amount of nodes in var nNodes
	if(nodos.is_open())
	{
		getline(nodos,line);
		nNodes=atoi(line.c_str());
		nodos.close();
		output++;
	}	
	else cout << "nodos.txt not found"<<endl;
	
	//initial global vars
	initValue();
	
	///////////////////////////////////////////////////////////
	//set the topology                                       //
	//usage:                                                 //
	//	topology[sourceNode][destNode]=cost or distance  //
	//if cost = -1 means that there is not connection between//
	//sourceNode and destNode				 //
	///////////////////////////////////////////////////////////
	maxWeight = 0;
	if(arcos.is_open())
	{
		while (getline(arcos,line))
			if (line != "EOF"){
				stringstream buffer(line);
				buffer >> sNode;				
				buffer >> dNode;
				buffer >> cost;
				topology[sNode][dNode] = cost;
				//if link are bidirectional
				//topology[dNode][sNode] = cost;
				if(cost > maxWeight) maxWeight = cost;
			}
		arcos.close();
		output++;
	}	
	else cout << "arcos.txt not found"<<endl;
	return output;
}

void writeFile(){
/************************************/
/*Description:			    */
/*Write file salida.txt with the    */
/*result			    */
/*Return none			    */
/************************************/
	ofstream salida;
	salida.open("salida.txt");

	salida << sourceNode<<endl;
	for(int i = 1; i <= nNodes; i++)
		salida << i <<" "<<solution[i].prevNode<<" "<<solution[i].cost<<endl;

	salida.close();
}

void initValue(){
/************************************/
/*Description:			    */
/*This function set up the initial  */
/*solution without algorithm        */
/* Return none			    */
/************************************/
	pairsNode temp1;
	int temp2 = -1;
	vector < int > temp3;
	
	//populate topology and solution vectors
        	
	for(int i = 0 ; i <= nNodes; i++){
		temp3.push_back(temp2);
		solution.push_back(temp1);
		if(i == sourceNode)
			S.push_back(i);
		else
			nonS.push_back(i);
	}
	
	solution[sourceNode].cost = 0;
	solution[sourceNode].prevNode=sourceNode;	

	for(int i = 0 ; i <= nNodes; i++){
		topology.push_back(temp3);
	}
}

/*************************Algorithm section*************************************/
void dijkstra(){
/****************************************/
/*Description:                      	*/
/*Dijkstra algorithm	            	*/
/*Return none			    	*/
/*Vars:				    	*/
/*S(n) vector with nodes with path  	*/
/*topology(x)(y) direct path from x to y*/
/*nonS(n) vector with nodes without path*/
/*nNodes amoung of nodes in the topology*/	
/*solution(n) result of algorithm       */
/****************************************/

	int sNode; 		//node in S and Source Node
	int nonsNode;		//node in nonS
	int dNode;		//Dest Node
	int cost;		//distance

	//until S is not full
	while(S.size() < nNodes){

		//iteration for every node in S
		for(int spos=0; spos < S.size(); spos++){
			sNode = S[spos];
			//iteration for every node in nonS with node S as source
			for(int nonspos = 0; nonspos < nonS.size() ; nonspos++){
				nonsNode = nonS[nonspos];
				cost = topology[sNode][nonsNode];
				if(cost != -1){
					if(solution[nonsNode].cost == -1 || solution[nonsNode].cost > (solution[sNode].cost+cost) ){
						solution[nonsNode].cost = solution[sNode].cost+cost;
						solution[nonsNode].prevNode = sNode;
					}
				}
			}//end for nonspos
		}//end for spos

		//remove nodes with solution from nonS and add to S
		for(int i = 0 ; i < nonS.size(); i++){
			nonsNode = nonS[i];
			if(solution[nonsNode].cost != -1){
				nonS.erase(nonS.begin()+i);
				S.push_back(nonsNode);
				i--;
			}
		}//end for i
			
		//recalculation with new nodes
		dijkstra_recalDist();		
	}//end while
	dijkstra_recalDist();		
}

void dijkstra_recalDist(){
/************************************/
/*Description:                      */
/*Recalculation of min routes       */
/*with new nodes		    */
/*Return none			    */
/************************************/
	int sNode; 		
	int dNode;		
	int cost;		
	for(int spos=0; spos < S.size(); spos++){
		sNode = S[spos];
		for(int dpos = 0; dpos < S.size(); dpos++){
			dNode = S[dpos];
			if(sNode != dNode){
				cost = topology[sNode][dNode];
				if(cost != -1 && (solution[dNode].cost > (solution[sNode].cost + cost) ) ) {
					solution[dNode].cost = solution[sNode].cost + cost;
					solution[dNode].prevNode=sNode;
				}
			}
		}//end for dpos  
	}//end for spos	
}

void dial(){
/****************************************/
/*Description:                      	*/
/*Dial algorithm	            	*/
/*Return none			    	*/
/*Vars:				    	*/
/*S(n) vector with nodes with path  	*/
/*topology(x)(y) direct path from x to y*/
/*nonS(n) vector with nodes without path*/
/*nNodes amoung of nodes in the topology*/	
/*solution(n) result of algorithm       */
/****************************************/

	vector < vector < bucketNode > > vBucket;
	vector < bucketNode > temp;
	bucketNode tBucketNode;
	int vBucketSize = nNodes * (maxWeight - 1 );
	int selectedNode, prevNode, tempNode;
	int tempCost, selectedCost;
	for(int i = 0 ; i < vBucketSize ; i++)	
		vBucket.push_back(temp);

	//first bucket fill
	selectedNode = S[0];
	for(int i = 1 ; i <= nNodes ; i++)
		if(i != selectedNode){
			tempCost = topology[selectedNode][i];
			if(tempCost != -1 && tempCost < vBucketSize){
			//enter to the bucket
				tBucketNode.node=i;
				tBucketNode.prevNode=selectedNode;
				vBucket[tempCost].push_back(tBucketNode);
			}
				
		}
	//loop
	while(S.size() < nNodes){
		//looking the buckets for next node
		selectedNode = -1;
		for(int i = 0 ; i < vBucketSize ; i++)
			if(vBucket[i].size() > 0){
				selectedNode = vBucket[i][0].node;
				prevNode = vBucket[i][0].prevNode;
				selectedCost = i;
				vBucket[i].erase(vBucket[i].begin());
				i=vBucketSize+1;
			}
		//there is not item in the buckets
		if(selectedNode == -1) break;

		//add node to S and solution and delete from nonS
		S.push_back(selectedNode);
		solution[selectedNode].cost = selectedCost;
		solution[selectedNode].prevNode = prevNode;
		for(int i = 0; i < nonS.size() ; i++)
			if(nonS[i] == selectedNode){
				nonS.erase(nonS.begin()+i);
				i=nonS.size()+2;
			}
		//delete all the bucketNode with selectedNode
		for(int i = selectedCost; i < vBucketSize ; i++)
			for(int j = 0; j < vBucket[i].size() ; j++){
				if(vBucket[i][j].node == selectedNode){
					vBucket[i].erase(vBucket[i].begin()+j);
					j--;
				}

			}
		//refill the bucket with distance to selectedNode
 		for(int i = 0; i < nonS.size() ; i++){
			tempNode = nonS[i];
			tempCost = topology[selectedNode][tempNode];
			if(tempCost != -1 && (tempCost+selectedCost) < vBucketSize){
				tempCost += selectedCost;
				tBucketNode.node= tempNode;
				tBucketNode.prevNode = selectedNode;
				vBucket[tempCost].push_back(tBucketNode);
			}	
		}
	}
}
