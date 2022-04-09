#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <assert.h>
#include <string>
using namespace std;
int N=5;
int OT=70; // recommended values


//HOCA COPY PASTE
enum visited {UNVISITED, VISITED}; // enum for marking vertices

// Graph class definition with adjacency matrix

class Graph{
private:
    int numVertex, numEdge; // mumber of edges and vertices
    int **matrix; // pointer for adjacency matrix
    int Marked[20][20];
    int count;
    int **occupancy;

public:
    string* List;
    Graph(int n); // Constructor
    void delEdge(int v1, int v2); // delete route
    int weight(int v1, int v2); // get the price of (v1,v2)

//MY MODIFICATIONS
    void setEdge(string departure, string arrival, int fare);//override - string input version
    Graph(string*List, int n); // Constructor
    void setEdge(int v1, int v2, int wt); // set route with price wt
    bool isEdge(int v1, int v2); // is (v1,vj) an edge? is tehre a route
    bool isEdge(string in, string out);//is there a route overwritten
    void AgencyFeedback();// agency supplies occupancy info
    ~Graph(); // Destructor
    bool  isMarked(int i, int j); // has i to j has been discounted in former month?
    void setMarked(int v, int val); // set the mark for discounted
    void clearMarked(); // clear all marks
    int NumberofCity();
    int Occupation(int i, int j);//route occupaciton
    int* getOccupancyLoc(int i,int j); // for route occ. location
    void print_route(string departure,string destination); //print single route
    int* getCityFlights(string departure);//learn where can you fly to from departure city
    int weight(string departure, int v2); //overwritten learn price method
    int weight(int v1, string destination);//overwritten learn price method
    void CutPrice(int i, int j);//50% discount apply
    void PrintRoutes();//print all routes
};
Graph::Graph(int n){
    int i;
    numVertex = n;
    numEdge = 0;
//    mark = new int[numVertex]; // Initialize mark array
//    for (i=0; i < numVertex; i++)
//        mark[i] = UNVISITED;
    // Make matrix, it is not possible to create 2D array with a single new operation. Size is numVertex*numVertex

    matrix = new int*[numVertex];
    for(i=0; i < numVertex; i++)
        matrix[i] = new int[numVertex];
    for(i=0; i < numVertex; i++) // Initialize to 0
        for (int j=0; j < numVertex; j++)
            matrix[i][j] = 0;
}
void Graph::delEdge(int v1, int v2) { // Delete edge (v1, v2)
    if (matrix[v1][v2] != 0)
        numEdge--;
    matrix[v1][v2] = 0;
    cout<<List[v1]<<"-x->"<<List[v2]<<endl;
}
int Graph::weight(int v1, int v2){ // Return weight of (v1,v2)
return matrix[v1][v2];
}

//MY MODIFICATIONS
Graph::Graph(string*input, int n){
    int i;
    numVertex = n;
    numEdge = 0;
    count=0;
    //Marked=nullptr;
    //    mark = new int[numVertex]; // Initialize mark array
    //    for (i=0; i < numVertex; i++)
    //        mark[i] = UNVISITED;
    // Make matrix, it is not possible to create 2D array with a single new operation. Size is numVertex*numVertex

    matrix = new int*[numVertex];
    occupancy=new int*[numVertex];
    for(i=0; i < numVertex; i++){
        matrix[i] = new int[numVertex];
        occupancy[i]=new int[numVertex];
        }
    for(i=0; i < numVertex; i++) // Initialize to 0
        for (int j=0; j < numVertex; j++){
            matrix[i][j] = 0;
            occupancy[i][j] = 0;
            Marked[i][j]=0;
        }

    List=input;


}
Graph::~Graph(){// Destructor, Return dynamically allocated memory
    for (int i=0; i < numVertex; i++){
        delete[] matrix[i];  delete[] occupancy[i];}
    delete [] matrix;
    delete[] occupancy;
}
void Graph::setEdge(string departure, string arrival, int fare ){
    int in, out;
    assert(fare>0);
    for( out=0 ; out<20 ; out++  ){
        if( List[out]==departure ) break;
        if( out == 19) { cout<<"Departure City not found!" <<endl; return;}
    }
      for( in=0 ; in<20 ; in++  ){
        if( List[in]==arrival ) break;
        if( in == 19) { cout<<"Arrival City not found!" <<endl; return;}
    }
    matrix[out][in]=fare;
    cout<<departure<<"--->"<<arrival<<" "<<in<<"     Ticket Price="<<matrix[out][in]<<endl;


}
void Graph::setEdge(int v1, int v2, int wt) {// Set edge (v1, v2) to "wt"

    assert(wt > 0);
    if (matrix[v1][v2] == 0)//http://www.cplusplus.com/reference/cassert/assert/

    numEdge++;
    matrix[v1][v2] = wt;
    cout<<List[v1]<<"--->"<<List[v2]<<"     Ticket Price="<<matrix[v1][v2]<<endl;
}
bool Graph::isEdge(int i, int j){ // Is (v1,v2) an edge?
return matrix[i][j] != 0;
}
void Graph::AgencyFeedback(){
    for(int i=0; i < numVertex; i++)
        for (int j=0; j < numVertex; j++)
            if(matrix[i][j] != 0)   occupancy[i][j]=rand()%100;
}
bool Graph::isMarked(int i, int j){
    return Marked[i][j];
}
void Graph::setMarked(int v, int val){
    Marked[v][val] = 1 ;
}
void  Graph::clearMarked(){
  for(int i=0; i < numVertex; i++)
        for (int j=0; j < numVertex; j++)
            Marked[i][j] = 0;
}
int Graph::NumberofCity(){
    return numVertex;
}
int Graph::Occupation(int i, int j){
    return occupancy[i][j];
}
int* Graph::getOccupancyLoc(int i,int j){
    return &(occupancy[i][j]);

}
bool Graph::isEdge(string in, string out){
    int i, o;
    for( o=0 ; o<20 ; o++  ){
        if( List[o]==in ) break;
        if( o == 19) { cout<<"Departure City not found!" <<endl;  return false;}
    }
      for( i=0 ; i<20 ; i++  ){
        if( List[i]==out ) break;
        if( i == 19) { cout<<"Arrival City not found!" <<endl; return false;}
    }
    return matrix[o][i] != 0;

}
void Graph::print_route(string departure,string destination){
    int i, o;
    for( o=0 ; o<20 ; o++  ){
        if( List[o]==departure ) break;
        if( o == 19) { cout<<"Departure City not found!" <<endl; return;}
    }
      for( i=0 ; i<20 ; i++  ){
        if( List[i]==destination ) break;
        if( i == 19) { cout<<"Arrival City not found!" <<endl; return;}
    }

cout<<departure<<"--->"<<destination<<"     Ticket Price="<<matrix[o][i]<<endl;

}
int* Graph::getCityFlights(string departure){
        int o;
    for( o=0 ; o<20 ; o++  ){
        if( List[o]==departure ) break;
        if( o == 19) { cout<<"Departure City not found!" <<endl; return nullptr;}
    }
    return matrix[o];
}
int Graph::weight(string departure, int v2){
    int o;
    for( o=0 ; o<20 ; o++  ){
        if( List[o]==departure ) break;
        if( o == 19) { cout<<"Departure City not found!" <<endl; return 0;}
    }
    return weight(o,v2);
}
int Graph::weight(int v1, string destination){
    int i;
    for( i=0 ; i<20 ; i++  ){
        if( List[i]==destination ) break;
        if( i == 19) { cout<<"Departure City not found!" <<endl; return 0;}
    }
    return weight(v1,i);
}
void Graph::CutPrice(int i, int j){

    cout<<List[i]<<"--->"<<List[j]<<"|"<<"Price Change:"<<matrix[i][j]<<"--->";
    matrix[i][j]= matrix[i][j] / 2;
    cout<<matrix[i][j]<<endl;

}
void Graph::PrintRoutes(){
    for(int i=0; i < numVertex; i++)
        for (int j=0; j < numVertex; j++)
            if(isEdge(i,j))
                cout<<List[i]<<"--->"<<List[j]<<"     Ticket Price="<<matrix[i][j]<<endl;

}




#endif // GRAPH_H_INCLUDED
