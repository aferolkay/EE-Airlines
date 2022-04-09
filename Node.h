#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include "GlobalFunctions.h"

//Node class to store flights
string* LoadCities();
string* List=LoadCities();
string Converter(string i , string j); //for switching between city names and numbers
int Converter(string i);  //for switching between city names and numbers

class Node
{
    private:

        Node *left;
        Node *right;
        int value;
        string data;

    public:
        //these methods are self explanatory
        Node();
        Node(int v1, int v2);
        Node(string arrival,string departure);
        void InsertLeft(Node* input);
        void InsertRight(Node* input);
        string GetData();
        int GetValue();
        Node *GetRight();
        Node *GetLeft();
        void SetRight(Node* input);
        void SetLeft(Node* input);
        void print();
        void SetValue(int input,string d);

};

Node::Node(){
    left=right=NULL;
    data="";
    value=9999; //max value
}
Node::Node(int v1,int v2){

    left=right=NULL;
    value=100*(v1+1) + (v2+1) ;
    data=Converter(List[v1],List[v2]);
}
Node::Node(string arrival,string departure){
    left=right=NULL;
    value= 100*(Converter(arrival)+1) + Converter(departure) + 1;
    data= Converter(arrival,departure);
}

int Node::GetValue(){
    return value;
}
Node* Node::GetRight(){
    return right;
}
Node* Node::GetLeft(){
    return left;
}

void Node::SetRight(Node* input){
    right=input;
}
void Node::SetLeft(Node* input){
    left=input;
}
void Node::print(){
    cout<<"EE"<<data<<endl;
}
void Node::SetValue(int input,string d){
    value=input;
    data=d;
}
string Node::GetData(){
    return data;
}


#endif // NODE_H_INCLUDED
