#include<iostream>
#include<cstdlib>
using namespace std;
int main(int argc,char *argv[]){
    if(argc<=1){
        cout<<"Please input numbers to find average.";
        return 0;
    }
    double sum=0;
    cout<<"---------------------------------\n";
    for(int i=1;i<argc;i++){
        
      sum=sum+atof(argv[i]);
        
    }
    double avg=sum/(argc-1);
    cout<<"Average of " <<argc-1<<" numbers = "<<avg;
     cout<<"\n---------------------------------";
    

    
    
}
