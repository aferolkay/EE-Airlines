#include <iostream>
#include <string>
#include "Graph.h"
#include "GlobalFunctions.h"

#include "Node.h"
#include "Tree.h"



int main(){
    int Month;
    string* List=LoadCities();
    Graph* Map;

    //MONTH 1
    cout<<"--------------Month 1------------------"<<endl;
    cout<<"Routes:"<<endl;
    Map=INITROUTEMAP();

    cout<<endl<<endl<<"Flights:"<<endl;
    Node * t  = InitFlightPlan();


    //MONTH 2
    cout<<"--------------Month 2------------------"<<endl;
    cout<<"Monthly New Route Offers:"<<endl;
    int**NewRoutes=ADDMONTHLYNEWROUTES(Map);

    cout<<endl<<endl<<"Monthly New Flight Offers:"<<endl;
    AddMonthlyNewFlights(NewRoutes,t);

    Map->AgencyFeedback();
//    cout<<"Cancelled Flights:"<<endl; //Cancel Flight function is faulty
//    CancelUnpopularFlights(Map,t);
    cout<<endl<<endl<<"Discarded Routes & Routes on Discount:"<<endl;
    DiscardUnpopularRoutes(Map);
    UpdatePrices(Map);



    cout<<endl<<endl<<"Routes:"<<endl;
    Map->PrintRoutes();
    cout<<endl<<endl<<"Flights:"<<endl;
    Inorder(t);

     //MONTH 3
    cout<<"--------------Month 3------------------"<<endl;


    cout<<"Monthly New Route Offers:"<<endl;
    NewRoutes=ADDMONTHLYNEWROUTES(Map);

    cout<<endl<<endl<<"Monthly New Flight Offers:"<<endl;
    AddMonthlyNewFlights(NewRoutes,t);

    Map->AgencyFeedback();
//    cout<<"Cancelled Flights:"<<endl; Cancel Flight function is faulty
//    CancelUnpopularFlights(Map,t);

    cout<<endl<<endl<<"Discarded Routes & Routes on Discount:"<<endl;
    DiscardUnpopularRoutes(Map);
    UpdatePrices(Map);



    cout<<endl<<endl<<"Routes:"<<endl;
    Map->PrintRoutes();
    cout<<endl<<endl<<"Flights:"<<endl;
    Inorder(t);


    //MONTH 4
    cout<<"--------------Month 4------------------"<<endl;
    cout<<"Monthly New Route Offers:"<<endl;
    NewRoutes=ADDMONTHLYNEWROUTES(Map);

    cout<<endl<<endl<<"Monthly New Flight Offers:"<<endl;
    AddMonthlyNewFlights(NewRoutes,t);

    Map->AgencyFeedback();
    //cout<<"Cancelled Flights:"<<endl; Cancel Flight function is faulty
    // CANCEL FUNCTION

    cout<<endl<<endl<<"Discarded Routes & Routes on Discount:"<<endl;
    DiscardUnpopularRoutes(Map);
    UpdatePrices(Map);



    cout<<endl<<endl<<"Routes:"<<endl;
    Map->PrintRoutes();
    cout<<endl<<endl<<"Flights:"<<endl;
    Inorder(t);

    //MONTH 5
    cout<<"--------------Month 5------------------"<<endl;
    cout<<"Monthly New Route Offers:"<<endl;
    NewRoutes=ADDMONTHLYNEWROUTES(Map);

    cout<<endl<<endl<<"Monthly New Flight Offers:"<<endl;
    AddMonthlyNewFlights(NewRoutes,t);

    Map->AgencyFeedback();
    //cout<<"Cancelled Flights:"<<endl; Cancel Flight function is faulty
    // CANCEL FUNCTION

    cout<<endl<<endl<<"Discarded Routes & Routes on Discount:"<<endl;
    DiscardUnpopularRoutes(Map);
    UpdatePrices(Map);



    cout<<endl<<endl<<"Routes:"<<endl;
    Map->PrintRoutes();
    cout<<endl<<endl<<"Flights:"<<endl;
    Inorder(t);


    //MONTH 6
    cout<<"--------------Month 6------------------"<<endl;
    cout<<"Monthly New Route Offers:"<<endl;
    NewRoutes=ADDMONTHLYNEWROUTES(Map);

    cout<<endl<<endl<<"Monthly New Flight Offers:"<<endl;
    AddMonthlyNewFlights(NewRoutes,t);

    Map->AgencyFeedback();
    //cout<<"Cancelled Flights:"<<endl;
    // CANCEL FUNCTION

    cout<<endl<<endl<<"Discarded Routes & Routes on Discount:"<<endl;
    DiscardUnpopularRoutes(Map);
    UpdatePrices(Map);

    cout<<endl<<endl<<"Missing Return Routes:"<<endl;
    CheckNAddReturnsRoutes(Map);

    cout<<endl<<endl<<"Missing Return Routes:"<<endl;
    CheckNAddReturnsFlight(t);



    cout<<endl<<endl<<"Routes:"<<endl;
    Map->PrintRoutes();
    cout<<endl<<endl<<"Flights:"<<endl;
    Inorder(t);

    cout<<"-------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"One-way Trip Options for Probia ---> Biomedberg :"<<endl;
    cout<<"Direct:";
    DirectFlights(Map,t,"Probia","Biomedberg");
    cout<<endl<<"1-Stop:"<<endl;
    oneStopFlight(Map,t,"Probia","Biomedberg");
    cout<<endl<<"2-Stop:"<<endl;
    twoStopFlight(Map,t,"Probia","Biomedberg");

    cout<<endl<<endl<<"One-way Trip Options for Magneta ---> Machineland :"<<endl;
    cout<<"Direct:";
    DirectFlights(Map,t,"Magneta","Machineland");
    cout<<endl<<"1-Stop:"<<endl;
    oneStopFlight(Map,t,"Magneta","Machineland");
    cout<<endl<<"2-Stop:"<<endl;
    twoStopFlight(Map,t,"Magneta","Machineland");

    cout<<endl<<endl<<"One-way Trip Options for West Circuitta ---> East Circuitta :"<<endl;
    cout<<"Direct:";
    DirectFlights(Map,t,"West Circuitta","East Circuitta");
    cout<<endl<<"1-Stop:"<<endl;
    oneStopFlight(Map,t,"West Circuitta","East Circuitta");
    cout<<endl<<"2-Stop:"<<endl;
    twoStopFlight(Map,t,"West Circuitta","East Circuitta");

    cout<<endl<<endl<<"One-way Trip Options for Las Datas ---> Island of Semicon :"<<endl;
    cout<<"Direct:";
    DirectFlights(Map,t,"Las Datas","Island of Semicon");
    cout<<endl<<"1-Stop:"<<endl;
    oneStopFlight(Map,t,"Las Datas","Island of Semicon");
    cout<<endl<<"2-Stop:"<<endl;
    twoStopFlight(Map,t,"Las Datas","Island of Semicon");

    FindMin(FindFlight(18,4,t))->print();

    return 0;
}
