#include<bits/stdc++.h>
using namespace std;


struct Dist_arrivedTimeTable
{
    int interrrivalTime;
    double probability;
    double cumu_probability;
    pair<int,int>randomDigit;
};



struct Dist_serviceTimeTable
{
   int serviceTime;
   double probability;
   double cumu_probability;
   pair<int,int>randomDigit;
  
};



struct Simulation_table{
   int customer;
   int RD_IAT;
   int IAT;
   int AriivalTime;

   int RD_ST;
   int serviceTime;;
   int ST_begin;
   int waitingTime;
   int ST_end;
   int  TSS;
   int ITOS;
};




//Distribution of arrival time;
   vector<pair<int,double>>arrivedtime={{1,0.125},{2,0.125},{3,0.125},{4,0.125},{5,0.125},{6,0.125},{7,0.125},{8,0.125}}; 

  // Distribution of service time;
   vector<pair<int,double>>servicetime={{1,0.10},{2,0.20},{3,0.30},{4,0.25},{5,0.10},{6,0.05},};

   //Random digit for arrival time
   vector<int>RD_arrivaltime={0,913,727,15,948,309};
   
   //Random digit for service time
   vector<int>RD_servicetime={84,10,74,53,17,79};




vector<Dist_arrivedTimeTable> Calculate_ArrivedTimeTable(){
    
     int n=arrivedtime.size();
     vector<Dist_arrivedTimeTable> arrivedtime_table(n);

     //set interrival time and probability
     for(int i=0;i<n;i++)
     {
        arrivedtime_table[i].interrrivalTime=arrivedtime[i].first;
        arrivedtime_table[i].probability=arrivedtime[i].second;

     }


     //calculate cumulative probability;
     arrivedtime_table[0].cumu_probability=arrivedtime_table[0].probability;
     for(int i=1;i<n;i++)
     {
       arrivedtime_table[i].cumu_probability=arrivedtime_table[i].probability+arrivedtime_table[i-1].cumu_probability;
      
     }


     //calculate Random digit assingment
     int minVal=-1;
     for(int i=0;i<n;i++)
     {
       arrivedtime_table[i].randomDigit.first=++minVal;
       arrivedtime_table[i].randomDigit.second =  ((int)(arrivedtime_table[i].cumu_probability*1000)%1000);
       minVal=arrivedtime_table[i].randomDigit.second;

      
     }



     cout<<"\n       **********   Arrival Time Table  ***********************"<<endl<<endl;
     cout<<"Interrival_Time    Probability     cumulative_probability     Rangom_digit"<<endl;
     
     for(int i=0;i<arrivedtime_table.size();i++)
     {
         cout<<arrivedtime_table[i].interrrivalTime<<"                  "<<arrivedtime_table[i].probability<<"            "<<arrivedtime_table[i].cumu_probability<<"                       "<<arrivedtime_table[i].randomDigit.first<<" - "<<arrivedtime_table[i].randomDigit.second<<endl;
     }


     cout<<endl<<endl;


     return arrivedtime_table;

     
}





//calculate service time table
vector<Dist_serviceTimeTable> Calculate_ServiceTimeTable(){
    
     int n=servicetime.size();
     vector<Dist_serviceTimeTable> servicetime_table(n);

     //set service time and probability
     for(int i=0;i<n;i++)
     {
        servicetime_table[i].serviceTime=servicetime[i].first;
        servicetime_table[i].probability=servicetime[i].second;

     }


     //calculate cumulative probability;
     servicetime_table[0].cumu_probability=servicetime_table[0].probability;
     for(int i=1;i<n;i++)
     {
       servicetime_table[i].cumu_probability=servicetime_table[i].probability+servicetime_table[i-1].cumu_probability;
      
     }


     //calculate Random digit assingment
     int minVal=-1;
     for(int i=0;i<n;i++)
     {
       servicetime_table[i].randomDigit.first=++minVal;
       servicetime_table[i].randomDigit.second =  ((int)(servicetime_table[i].cumu_probability*100)%100);
       minVal=servicetime_table[i].randomDigit.second;

      
     }




     cout<<"\n       **********   Service Time Table  ***********************"<<endl<<endl;
     cout<<"Sercive_Time    Probability     cumulative_probability     Rangom_digit"<<endl;
     
     for(int i=0;i<servicetime_table.size();i++)
     {
         cout<<servicetime_table[i].serviceTime<<"                  "<<servicetime_table[i].probability<<"            "<<servicetime_table[i].cumu_probability<<"                       "<<servicetime_table[i].randomDigit.first<<" - "<<servicetime_table[i].randomDigit.second<<endl;
     }


     cout<<endl<<endl;
     


     


     return servicetime_table;

     
}






//calculate Simulation table

vector<Simulation_table> Calculate_Simulation_Table(vector<Dist_arrivedTimeTable> arrivedtime_Table,vector<Dist_serviceTimeTable> servicetime_Table)
{
      int customer=RD_servicetime.size();

      //simulation table create
      vector<Simulation_table> simulationTable(customer);

     //set Random digit to customer 
     for(int i=0;i<simulationTable.size();i++)
     {  
        simulationTable[i].customer=i+1;
        simulationTable[i].RD_IAT=RD_arrivaltime[i];
        simulationTable[i].RD_ST=RD_servicetime[i];
       
        
    }






    //*****************  calculate customer IAT;
    simulationTable[0].IAT=0;

    for(int i=1;i<simulationTable.size();i++)
    {
        for(int j=0;j<arrivedtime_Table.size();j++)
        { 
              if(simulationTable[i].RD_IAT>= arrivedtime_Table[j].randomDigit.first && (simulationTable[i].RD_IAT<= arrivedtime_Table[j].randomDigit.second || arrivedtime_Table[j].randomDigit.second==0) )
              {

                   
                   simulationTable[i].IAT=arrivedtime_Table[j].interrrivalTime;
                   
                
                   break;
              }
        }
    }




     cout<<"\n       **********   Determining time between arrival  ***********************"<<endl<<endl;
     cout<<"Customer      Random Digit       time between_arrival "<<endl;
     
     for(int i=0;i<simulationTable.size();i++)
     {
         cout<<simulationTable[i].customer<<"                  "<<simulationTable[i].RD_IAT<<"              "<<simulationTable[i].IAT<<endl;
     }


     cout<<endl<<endl;



      


     
     
    //******************  calculate customer Service time;
  

    for(int i=0;i<simulationTable.size();i++)
    {
        for(int j=0;j<servicetime.size();j++)
        { 
              if(simulationTable[i].RD_ST>= servicetime_Table[j].randomDigit.first && (simulationTable[i].RD_ST<= servicetime_Table[j].randomDigit.second || servicetime_Table[j].randomDigit.second==0) )
              {

                   
                   simulationTable[i].serviceTime=servicetime_Table[j].serviceTime;
                   
                  // cout<< simulationTable[i].customer<<"   "<<simulationTable[i].RD_ST<<"   "<<simulationTable[i].serviceTime<<endl;
                
                   break;
              }
        }
    }





    cout<<"\n       **********   Determining Service time  ***********************"<<endl<<endl;
     cout<<"Customer      Random Digit       service_time "<<endl;
     
     for(int i=0;i<simulationTable.size();i++)
     {
         cout<<simulationTable[i].customer<<"                  "<<simulationTable[i].RD_ST<<"              "<<simulationTable[i].serviceTime<<endl;
     }


     cout<<endl<<endl;






   //******* Calculate for first customer
   simulationTable[0].AriivalTime=0;
   simulationTable[0].ST_begin=0;
   simulationTable[0].waitingTime=0;
   simulationTable[0].ST_end=simulationTable[0].ST_begin+simulationTable[0].serviceTime;
   simulationTable[0].TSS=simulationTable[0].ST_end-simulationTable[0].AriivalTime;
   simulationTable[0].ITOS=0;


   //* for other customer
   for(int i=1;i<simulationTable.size();i++){
        
       simulationTable[i].AriivalTime=simulationTable[i-1].AriivalTime+simulationTable[i].IAT;
       simulationTable[i].ST_begin=max(simulationTable[i].AriivalTime,simulationTable[i-1].ST_end);
       simulationTable[i].waitingTime=max(0,simulationTable[i-1].ST_end-simulationTable[i].AriivalTime );
       simulationTable[i].ST_end=simulationTable[i].ST_begin+simulationTable[i].serviceTime;
       simulationTable[i].TSS=simulationTable[i].ST_end-simulationTable[i].AriivalTime;
       simulationTable[i].ITOS=max(0,simulationTable[i].AriivalTime -simulationTable[i-1].ST_end);



       
   }

   

   //*******  print simulation table
    cout<<"\n   ******************** Simulation table ********************* "<<endl<<endl;

   cout<<"customer      RD_IAT     IAT     RD_ST     AriivalTime     ServiceTime   ST_Begin   WaitingTime    ST_End     TSS     ITOS "<<endl<<endl;

   for(int i=0;i<simulationTable.size();i++)
   {

    
       cout<<simulationTable[i].customer<<"          ";
       cout<<simulationTable[i].RD_IAT<<"          ";
       cout<<simulationTable[i].IAT<<"          ";
       cout<<simulationTable[i].AriivalTime<<"            ";
       cout<<simulationTable[i].RD_ST<<"          ";
      
       cout<<simulationTable[i].serviceTime<<"              ";
       cout<<simulationTable[i].ST_begin<<"               ";
      cout<<simulationTable[i].waitingTime<<"          ";
       cout<<simulationTable[i].ST_end<<"          ";
       cout<<simulationTable[i].TSS<<"          ";
       cout<<simulationTable[i].ITOS<<"\n";
       
   }




      




 
  return simulationTable;
       
}

int main(){

  


  // calculate  Dist_arrivedTimetable from arrival time value;
   vector<Dist_arrivedTimeTable>arrivedtime_Table=Calculate_ArrivedTimeTable();
 
  // calculate  Dist_service Timetabl from service time value
    vector<Dist_serviceTimeTable>servicetime_Table=Calculate_ServiceTimeTable();


   //calculate simulation table
   vector<Simulation_table>simulation_Table=Calculate_Simulation_Table(arrivedtime_Table,servicetime_Table);



   //****    calculation

   double number_Customer=simulation_Table.size();
   double total_waiting_time=0;
   double total_waiting_customer=0;
   double total_idle_time=0;
   double total_service_time=0;
   double total_runtime=simulation_Table[simulation_Table.size()-1].ST_end;
   double total_IAT=simulation_Table[simulation_Table.size()-1].AriivalTime;
   double number_IAT=simulation_Table.size()-1;
   double total_TSS=0;



   for(int i=0;i<simulation_Table.size();i++)
   {  
      total_waiting_time+=simulation_Table[i].waitingTime;
      total_waiting_customer+=(simulation_Table[i].waitingTime>0);
      total_idle_time+=simulation_Table[i].ITOS;
      total_service_time+=simulation_Table[i].serviceTime;
      total_TSS+=simulation_Table[i].TSS;
      
     
   }

  


  cout<<endl<<endl;


  cout<<"Averager waiting time : " << total_waiting_time/number_Customer<< "min"<<endl;
  cout<<"Probability customer has to wait in queue : " << (total_waiting_customer/number_Customer)*100<<" %"<<endl;
  cout<<"Probability of idle Time : " <<(total_idle_time/total_runtime)*100<< " %"<<endl;
  cout<<"Average service time Time : " <<(total_service_time/number_Customer)<< ""<<endl;
  cout<<"Average time between arrival : " <<(total_IAT/number_IAT)<< " mins"<<endl;
  cout<<"Average waiting time for those who wait : " <<(total_waiting_time/total_waiting_customer)<< ""<<endl;
  cout<<"Average time customer spent in system  : " <<(total_TSS/number_Customer)<< " mins"<<endl;



   
  
  
   



return 0;
}
