#ifndef GLOBALFUNCTIONS_H_INCLUDED
#define GLOBALFUNCTIONS_H_INCLUDED
#include <fstream>
#include <string>
#include <sstream>
#include "Graph.h"
#include "Tree.h"
using namespace std;
//int N=5;
//int OT=70;

//*** THIS FILE CONTAINS FUNCTIONS RELATED TO ROUTES MATRIX.
string* LoadCities() {
    string line;
    string* city = new string[20] ;
    ifstream myfile ("citylist.txt");
    if (myfile.is_open())   {
        int i=0;
        while ( getline (myfile,line) ) {
        city[i]=line;
        //cout << city[i] << endl ;
        i++;
        }
        myfile.close();
    }
    else{ cout << "Unable to open file"; return nullptr;}

    return city ;
}
Graph* INITROUTEMAP(){ // INPUTS THE GIVEN MAP AND INITIALIZES MATRIX THROUGH MAP CLASS
    Graph* Map = new Graph( LoadCities() ,  20);
    //SETTING THE INITIAL MAP
    Map->setEdge("Probia","Las Datas",rand());
    Map->setEdge("Signale","Probia",rand());
    Map->setEdge("Probia","Gulf of Archi",rand());
    Map->setEdge("Gulf of Archi","Logicheim",rand());
    Map->setEdge("Logicheim","Probia",rand());
    Map->setEdge("Probia","Logicheim",rand());

    return Map;
}
int** ADDMONTHLYNEWROUTES(Graph* &Map){ // N NEW ROUTES

    int **newRoutes = new int*[N];

    for( int i=0; i<N; ){
        int departure=rand()%20; //randomly selects departure city
        int arrival=rand()%20; //randomly selects arrival city
        if(  Map->isEdge(departure,arrival) || departure==arrival )    continue;      //randomly selected route exist or both cities are same so we need to select again
        Map->setEdge(departure,arrival,rand());
        newRoutes[i]=new int[2];
        newRoutes[i][0]=departure;
        newRoutes[i][1]=arrival;  //SAVING NEW ROUTES TO ADD THEM ON THE TREE WHICH IS LATER WHERE I WILL BE DELETING THE ARRAYS
        i++;
    }

    return newRoutes;
}
void DiscardUnpopularRoutes(Graph* &Map){ //ALWAYS FIRST USE THIS SO MARKED MATRIX WILL SERVE CORRECTLY

    int n=Map->NumberofCity();
    for(int i=0; i<n ; i++)
        for(int j=0 ; j<n ; j++)
            if(   Map->isMarked(i,j) && Map->Occupation(i,j)<OT   )
                Map->delEdge(i,j);    //NOW,DOUBLE UNPOPULAR ROUTES ARE CANCELED

}
void CancelUnpopularFlights(Graph* &Map,Node*t){
    int n=Map->NumberofCity();
    for(int i=0; i<n ; i++)
        for(int j=0 ; j<n ; j++)
            if(  Map->isMarked(i,j) && Map->Occupation(i,j)<OT   ){ //NOW,DOUBLE UNPOPULAR FLIGHTS ARE CANCELED
                int value=100*(i+1) + (j+1) ;
                cout<<"Following flight is cancelled: EE"<<Converter(List[i],List[j])<<endl;
                Delete(t,value);// THE FLIGH IS DELETED VIA THIS FUNCTION
            }
}
void UpdatePrices( Graph* &Map ){
    Map->clearMarked(); // NOW MARKS ARE CLEARED SINCE THEY SERVED THEIR PURPOSE ABOVE
    int n=Map->NumberofCity();

    for(int i=0; i<n ; i++)
        for(int j=0 ; j<n ; j++)
            if( Map->isEdge(i,j) && Map->Occupation(i,j)<OT  ){// if firs time unpopular, discounted
                Map->CutPrice(i,j);
                Map->setMarked(i,j);//marked for cancellation in case of again unpopularity
            }
}
void CheckNAddReturnsRoutes(Graph* &Map){//return routes are created
    int n=Map->NumberofCity();
    for(int i=0; i <n; i++)
        for ( int j=0; j <n ; j++ )
            if(Map->isEdge(i,j)) //is route exist
                if(!Map->isEdge(j,i)) // if return doesnt exist
                    Map->setEdge(j,i,rand()); // return created

}
string Converter (string city1,string city2){ //for switching between city names and numbers
    int v1,v2;
    int leave,arrive,leave1,leave2,arrive1,arrive2;
    for( v1=0 ; v1<20 ; v1++  ){
        if( List[v1]==city1 ) break;
        if( v1 == 19) { cout<<"Departure City not found!" <<endl;  return NULL;}
    }
        for( v2=0 ; v2<20 ; v2++  ){
        if( List[v2]==city2 ) break;
        if( v2 == 19) { cout<<"Arrival City not found!" <<endl;  return NULL;}
    }

    leave=101+v1;
    leave1= (leave%100-leave%10)/10;
    leave2=leave%10;

    arrive=101+v2;
    arrive1= (arrive%100-arrive%10)/10;
    arrive2=arrive%10;

    stringstream ss;  //to get the flight name right
    ss<<leave1<<leave2<<arrive1<<arrive2;
    string output= ss.str();
    return output;
}
int Converter(string city1){//for switching between city names and numbers
     int v1;
    for( v1=0 ; v1<20 ; v1++  ){
        if( List[v1]==city1 ) break;
        if( v1 == 19) { cout<<"City not found!" <<endl;  return 21;} //21 because doesnt exist and bound to give error
    }
    return v1;
}


#endif // GLOBALFUNCTIONS_H_INCLUDED
