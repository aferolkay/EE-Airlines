#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#include "Node.h"

//THIS FILE CONTAINS TREE RELATED FUNCTIONS

void Inorder(Node* t){ //TO PRINT ALL THE FLIGHTS
    if(t!=NULL){
        Inorder(t->GetLeft());
        t->print();
        Inorder(t->GetRight());
    }
}
void InsertFlight(int v1, int v2,Node* t){ // TO INSERT NEW FLIGHTS INTO RIGHT PLACE
    Node* x=new Node(v1,v2);
    Node*temp=t;

    while( 1 ){
        if(  x->GetValue() > temp->GetValue()    ){
            if( temp->GetRight()==NULL){     temp->SetRight(x);   break; }
            else temp=temp->GetRight();

        }

      //  if(   x->GetValue() < temp->GetValue()    )
        else{
            if( temp->GetLeft()==NULL){     temp->SetLeft(x);     break; }
            else  temp=temp->GetLeft();

        }

    }

    x->print();

}
void InsertFlight(string departure,string arrival,Node* t){//TO INSERT NEW FLIGHTS INTO RIGHT PLACE OVERWRITTEN
    int v1=Converter(departure);
    int v2=Converter(arrival);
    Node* x=new Node(v1,v2);
    Node*temp=t;

    while( 1 ){
        if(  x->GetValue() > temp->GetValue()    ){

            if( temp->GetRight()==NULL){     temp->SetRight(x);    break;}
            else temp=temp->GetRight();
        }

        if(   x->GetValue() < temp->GetValue()    ){

            if( temp->GetLeft()==NULL){     temp->SetLeft(x);      break;}
            else  temp=temp->GetLeft();
        }
    }
     x->print();

}
Node* InitFlightPlan(){ //MAP ROUTES INPUTTED
    Node* t=new Node("Probia","Las Datas");
    cout<<"EE"<<Converter("Probia","Las Datas")<<endl;
    InsertFlight("Probia","Logicheim",t);
    InsertFlight("Probia","Gulf of Archi",t);
    InsertFlight("Logicheim","Probia",t);
    InsertFlight("Signale","Probia",t);
    InsertFlight("Gulf of Archi","Logicheim",t);

    return t;
}
void AddMonthlyNewFlights(int** NewRoutes,Node *t){// WHATEVER ADDED TO THE ROUTES ARE NOW ADDED TO THE FLIGHT TREE
    for(int i=0 ; i<N ; i++ ){
        InsertFlight( NewRoutes[i][0] , NewRoutes[i][1],  t); //NewRoutes carries info from Route Matrix and later is deleted
        delete [] NewRoutes[i];
    }
    delete [] NewRoutes;
}
Node* FindMin(Node*t){ // Finds the Node that has the smallest value under a given Node
    int min=9999;
    Node* out;
    if(t!=NULL){
        FindMin( t->GetLeft() );
        if ( t->GetValue()< min){  min=t->GetValue(); out=t; }
        FindMin (t->GetRight() );
    }
    return out;
}

Node* Delete(Node*t,int value){ // For some reason that i couldn't figure out,it works for some flights but not all and
                                                //when it doesn't work is stops whole program so i didn't include it in the main program.
    if(t==NULL)     return t;
    else if( value< t->GetValue() )     t->SetLeft ( Delete(t->GetLeft(),value) );
    else if( value> t->GetValue() )     t->SetRight( Delete(t->GetRight(),value) );//target is located
    else{
        //NO CHILD
        if( t->GetLeft()==NULL && t->GetRight()==NULL ){
            delete t;
            t=NULL;
        }

        //ONE CHILD
        else if( t->GetLeft() == NULL  ){
            Node* temp=t;
            t= t->GetRight();
            delete temp;
        }
        else if( t->GetRight() == NULL  ){
            Node* temp=t;
            t = t->GetLeft();
            delete temp;
        }
        //2 CHILDREN
        else{
            Node* temp = FindMin(t->GetRight());
            t->SetValue( temp->GetValue() , temp->GetData()  );
        }
    }
        return t;
}

bool Finder(Node* t,int value,Node* &m){ //FINDER & FINDFLIGHT  WORK SYNCRONOUSLY TO FIND LOC. OF GIVEN INPUT

   if(t!=NULL){
        Finder(t->GetLeft(),value,m);
        if( t->GetValue() == value) {m=t; return true;}
        Finder(t->GetRight(),value,m);
    }
}
Node* FindFlight(int v1, int v2,Node* t){  //FINDER & FINDFLIGHT  WORK SYNCRONOUSLY TO FIND LOC. OF GIVEN INPUT
    int value=100*(v1+1) + (v2+1) ;
    Node* out=NULL;
    Finder(t,value,out);
    return out;
}
void CheckNAddReturnsFlight(Node* t){ // ADD RETURN FLIGHTS
    int n=20;
    for(int i=0; i <n; i++)
        for ( int j=0; j <n ; j++ )
            if(FindFlight(i,j,t)!=NULL) //if flight exist
                if( FindFlight(j,i,t)==NULL ) // if return doesnt exist
                    InsertFlight(j,i,t);//return created
}
void DirectFlights(Graph* &Map,Node*t,string departure,string destination){
    if( Map->isEdge(departure,destination))  FindFlight(Converter(departure),Converter(destination),t)->print(); //if exist, flight is printed
    else cout<<"No direct flights!"<<endl;
}
void oneStopFlight(Graph* &Map,Node*t,string departure,string destination){
    int *arr=Map->getCityFlights(departure);
    bool count=false;
    for(int i=0; i<20 ; i++ )
        if( arr[i]!=0 )
            if( Map->isEdge( Map->List[i],destination ))  {
                count=true;
                cout<<"Flight 1:";      FindFlight(Converter(departure),Converter(Map->List[i]),t)->print();
                cout<<"Flight 2:";      FindFlight(Converter( Map->List[i]),Converter(destination),t)->print();
                cout<< "Total Cost:" << Map->weight(departure,i)+Map->weight(i,destination) <<endl<<endl;
            }
    if(!count) cout<<"No option available!"<<endl;
}
void twoStopFlight(Graph* &Map,Node*t,string departure,string destination){
    int *arr1=Map->getCityFlights(departure);
    int*arr2;
    bool count=false;
    for(int i=0; i<20 ; i++ ){
            if( arr1[i]!=0 ){
                arr2=Map->getCityFlights(Map->List[i]);
                for(int j=0; j<20; j++){
                    if( arr2[j]!=0 ){
                        if(Map->isEdge( Map->List[j],destination )){
                            count=true;
                            cout<<"Flight 1:";   FindFlight(Converter(departure),Converter( Map->List[i]),t)->print();
                            cout<<"Flight 2:";   FindFlight(Converter(Map->List[i]),Converter(Map->List[j]),t)->print();
                            cout<<"Flight 3:";   FindFlight(Converter(Map->List[j]),Converter(destination),t)->print();
                            cout<< "Total Cost:" << Map->weight(departure,i)+Map->weight(i,j)+Map->weight(j,destination) <<endl<<endl;
                        }
                    }
                }
            }
    }
    if(!count) cout<<"No option available!"<<endl;

}





#endif // TREE_H_INCLUDED
