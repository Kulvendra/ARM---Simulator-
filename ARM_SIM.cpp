#include <iostream>
#include <string>
#include <fstream>
#include<map>
#include<vector>

using namespace std;
    ifstream myReadFile;

    string a[100];
    int reg[16];
    int memory[100]={516};
    int i=0,total_lat;
    fstream lat;
    string lat_name[15];
    int lat_val[15],total_instructions = 0;
    vector<string> loop_lines;

    map<string, int> lats;
    int i_new = 0;
    char ck;
    bool loop = true,isloop = false;


bool working(){
            total_instructions++;
    
       cout<<a[i]<<endl;
        int flag=0;

        // ADDITION CODE IS STARTING HERE

        for(int j=0;j<a[i].length()-2;j++)
        {   //cout<<a[i].substr(j,3)<<endl;
            if((a[i].substr(j,3)).compare("add")==0)
            {   
                total_lat += lats.at("add");

                flag=1;
                cout<<"add function found"<<endl;
                int op[3];

                
                std::size_t found = a[i].find("r");
                if(found==std::string::npos)
                {
                    cout<<"error"<<endl;
                    flag=0;
                    break;
                }
                for(int k=found;k<a[i].length();k++)
                {
                    if(a[i][k]>='0' && a[i][k]<='9')
                    {
                        op[0]=(int)a[i][k]-48;
                        cout<<op[0]<<endl;
                        break;
                    }
                }
                found=a[i].find("r",found+1);
                if(found==std::string::npos)
                {
                    flag=0;
                    break;
                }
                for(int k=found;k<a[i].length();k++)
                {
                    if(a[i][k]>='0' && a[i][k]<='9')
                    {
                        op[1]=(int)a[i][k]-48;
                        cout<<op[1]<<endl;
                        break;
                    }
                }

                std::size_t found1=a[i].find("#",found+1);
                found=a[i].find("r",found+1);

                if(found!=std::string::npos || found1!=std::string::npos)
                {
                    if(found==std::string::npos || found1!=std::string::npos)
                    {
                        string hashvalue="";
                        for(int k=found1;k<a[i].length();k++)
                        {
                            if(a[i][k]>='0' && a[i][k]<='9')
                            {
                                hashvalue+=a[i][k];
                            }
                        }
                        if(hashvalue=="")
                            {
                                flag=0;
                                break;
                            }
                            op[2]=stoi(hashvalue);
                            cout<<op[2]<<endl;
                            reg[op[0]]=reg[op[1]]+op[2];
                            cout<<"Register value="<<reg[op[0]]<<endl;
                    }
                    else
                    {
                        for(int k=found;k<a[i].length();k++)
                        {
                            if(a[i][k]>='0' && a[i][k]<='9')
                            {
                                op[2]=(int)a[i][k]-48;
                                cout<<op[2]<<endl;
                                break;
                            }
                        }
                            //cout<<op[2]<<endl;
                            reg[op[0]]=reg[op[1]]+reg[op[2]];
                            cout<<"Register value="<<reg[op[0]]<<endl;
                    }
                }
                else
                {
                    flag=0;
                    break;
                }              
            }
        }

        // ADDITION CODE IS ENDING HERE

        // SUBATRACTION CODE 


         for(int j=0;j<a[i].length()-2;j++)
        {   //cout<<a[i].substr(j,3)<<endl;
            if((a[i].substr(j,3)).compare("sub")==0)
            {   
                total_lat += lats.at("sub");

                flag=1;
                cout<<"sub function found"<<endl;
                int op[3];
                std::size_t found = a[i].find("r");
                if(found==std::string::npos)
                {
                    cout<<"error"<<endl;
                    flag=0;
                    break;
                }
                for(int k=found;k<a[i].length();k++)
                {
                    if(a[i][k]>='0' && a[i][k]<='9')
                    {
                        op[0]=(int)a[i][k]-48;
                        cout<<op[0]<<endl;
                        break;
                    }
                }
                found=a[i].find("r",found+1);
                if(found==std::string::npos)
                {
                    flag=0;
                    break;
                }
                for(int k=found;k<a[i].length();k++)
                {
                    if(a[i][k]>='0' && a[i][k]<='9')
                    {
                        op[1]=(int)a[i][k]-48;
                        cout<<op[1]<<endl;
                        break;
                    }
                }
                
                std::size_t found1=a[i].find("#",found+1);
                found=a[i].find("r",found+1);

                if(found!=std::string::npos || found1!=std::string::npos)
                {
                    if(found==std::string::npos || found1!=std::string::npos)
                    {
                        string hashvalue="";
                        for(int k=found1;k<a[i].length();k++)
                        {
                            if(a[i][k]>='0' && a[i][k]<='9')
                            {
                                hashvalue+=a[i][k];
                            }
                        }
                        if(hashvalue=="")
                            {
                                flag=0;
                                break;
                            }
                            op[2]=stoi(hashvalue);
                            cout<<op[2]<<endl;
                            reg[op[0]]=reg[op[1]]-op[2];
                            cout<<"Register value="<<reg[op[0]]<<endl;
                    }
                    else
                    {
                        for(int k=found;k<a[i].length();k++)
                        {
                            if(a[i][k]>='0' && a[i][k]<='9')
                            {
                                op[2]=(int)a[i][k]-48;
                                cout<<op[2]<<endl;
                                break;
                            }
                        }
                            //cout<<op[2]<<endl;
                            reg[op[0]]=reg[op[1]]-reg[op[2]];
                            cout<<"Register value="<<reg[op[0]]<<endl;
                    }
                }
                else
                {
                    flag=0;
                    break;
                }              
            }
        }

// MOV FUNCTION CODE STARTS HERE 
        for(int j=0;j<a[i].length()-2;j++)
        {   //cout<<a[i].substr(j,3)<<endl;
            if((a[i].substr(j,3)).compare("mov")==0)
            {   
                total_lat += lats.at("mov");

                flag=1;
                cout<<"mov function found"<<endl;
                int op[3];
                std::size_t found = a[i].find("r");
                if(found==std::string::npos)
                {
                    cout<<"error"<<endl;
                    flag=0;
                    break;
                }
                for(int k=found;k<a[i].length();k++)
                {
                    if(a[i][k]>='0' && a[i][k]<='9')
                    {
                        op[0]=(int)a[i][k]-48;
                        cout<<op[0]<<endl;
                        break;
                    }
                }

            std::size_t found1=a[i].find("#",found+1);
            found=a[i].find("r",found+1);

        if(found!=std::string::npos || found1!=std::string::npos)
                {
                    if(found==std::string::npos || found1!=std::string::npos)
                    {
                        string hashvalue="";
                        for(int k=found1;k<a[i].length();k++)
                        {
                            if(a[i][k]>='0' && a[i][k]<='9')
                            {
                                hashvalue+=a[i][k];
                            }
                        }
                        if(hashvalue=="")
                            {
                                flag=0;
                                break;
                            }
                            op[1]=stoi(hashvalue);
                            cout<<op[1]<<endl;
                            reg[op[0]]=op[1];
                            cout<<"Register value="<<reg[op[0]]<<endl;
                    }
                    else
                    {
                        for(int k=found;k<a[i].length();k++)
                        {
                            if(a[i][k]>='0' && a[i][k]<='9')
                            {
                                op[1]=(int)a[i][k]-48;
                                cout<<op[1]<<endl;
                                break;
                            }
                        }
                            //cout<<op[2]<<endl;
                            reg[op[0]]=reg[op[1]];
                            cout<<"Register value="<<reg[op[0]]<<endl;
                    }
                }
                else
                {
                    flag=0;
                    break;
                }              
            }
        }
        // MOV FUNCTION CODE ENDS HERE 

        // MUTLIPLICATION CODE STARTING HERE 


                for(int j=0;j<a[i].length()-2;j++)
        {   //cout<<a[i].substr(j,3)<<endl;
            if((a[i].substr(j,3)).compare("mul")==0)
            {   
                total_lat += lats.at("mul");

                flag=1;
                cout<<"mul function found"<<endl;
                int op[3];
                std::size_t found = a[i].find("r");
                if(found==std::string::npos)
                {
                    cout<<"error"<<endl;
                    flag=0;
                    break;
                }
                for(int k=found;k<a[i].length();k++)
                {
                    if(a[i][k]>='0' && a[i][k]<='9')
                    {
                        op[0]=(int)a[i][k]-48;
                        cout<<op[0]<<endl;
                        break;
                    }
                }
                found=a[i].find("r",found+1);
                if(found==std::string::npos)
                {
                    flag=0;
                    break;
                }
                for(int k=found;k<a[i].length();k++)
                {
                    if(a[i][k]>='0' && a[i][k]<='9')
                    {
                        op[1]=(int)a[i][k]-48;
                        cout<<op[1]<<endl;
                        break;
                    }
                }
                
                std::size_t found1=a[i].find("#",found+1);
                found=a[i].find("r",found+1);

                if(found!=std::string::npos || found1!=std::string::npos)
                {
                    if(found==std::string::npos || found1!=std::string::npos)
                    {
                        string hashvalue="";
                        for(int k=found1;k<a[i].length();k++)
                        {
                            if(a[i][k]>='0' && a[i][k]<='9')
                            {
                                hashvalue+=a[i][k];
                            }
                        }
                        if(hashvalue=="")
                            {
                                flag=0;
                                break;
                            }
                            op[2]=stoi(hashvalue);
                            cout<<op[2]<<endl;
                            reg[op[0]]=reg[op[1]]*op[2];
                            cout<<"Register value="<<reg[op[0]]<<endl;
                    }
                    else
                    {
                        for(int k=found;k<a[i].length();k++)
                        {
                            if(a[i][k]>='0' && a[i][k]<='9')
                            {
                                op[2]=(int)a[i][k]-48;
                                cout<<op[2]<<endl;
                                break;
                            }
                        }
                            //cout<<op[2]<<endl;
                            reg[op[0]]=reg[op[1]]*reg[op[2]];
                            cout<<"Register value="<<reg[op[0]]<<endl;
                    }
                }
                else
                {
                    flag=0;
                    break;
                }              
            }
        }
        // MUTLIPLICATION CODE ending HERE 

        string label;
        if(a[i][a[i].length()-1] == ':'){
            flag =1;
            cout<<a[i][a[i].length()-1];
            label = a[i].substr(a[i].length()-2);
            total_instructions--;
        }

        int size;
        if(a[i].substr(0,6) == ".space" ){
            flag =1;
            total_instructions--;
            
            
            size = stoi(a[i].substr(7,a[i].length()-1));
        }

        //cout<<a[i].substr(j,3)<<endl;
            if((a[i].substr(0,3))=="ldr")
            {
                total_lat += lats.at("ldr");

            flag =1;
            if(stoi(a[i].substr(13,2)) < size){
reg[stoi(a[i].substr(5,1))] = memory[stoi(a[i].substr(13,2))];
                cout<<"Register value ="<<reg[stoi(a[i].substr(5,1))]<<endl;
            }else{
                cout<<endl<<"Out of memory"<<endl;
                exit(0);
            }
                
            }


            // str  
        if((a[i].substr(0,3))=="str")
            {
                total_lat += lats.at("str");

            flag =1;
            if(stoi(a[i].substr(13,2)) < size){
                 memory[stoi(a[i].substr(13,2))]  = reg[stoi(a[i].substr(5,1))];
                cout<<"Memory value ="<<memory[stoi(a[i].substr(13,2))]<<endl;
            }else{
                cout<<endl<<"Out of memory"<<endl;
                exit(0);
            }
                
            }

// cmp
        if((a[i].substr(0,3))=="cmp"){
            flag =1;
            total_lat += lats.at("cmp");
            
            cout<<"first: "<<reg[stoi(a[i].substr(5,1))]<<endl;
            cout<<"second: "<<reg[stoi(a[i].substr(8,1))]<<endl;
            if(reg[stoi(a[i].substr(5,1))] == reg[stoi(a[i].substr(8,1))])
                cout<<"equal"<<endl;
            else
                cout<<"not equal"<<endl;
        }
        

        // STORE FUNCTION IS ENDING HERE 

        if(flag==0)
        {
            cout<<"Error in line number="<<i+1<<endl;
            return false;
        }
        i++;

        return true;
}



int main()
{   


       //          ==============================latency=======================
    myReadFile.open("in.txt");
    lat.open("latency.txt",ios::in);


    while(!lat.eof()){
        lat>>lat_name[i_new];
        
        lat>>ck;
        lat>>lat_val[i_new];
        lats.insert(pair<string, int>(lat_name[i_new],lat_val[i_new]));
        
        lat>>ck;
    }
    // =====================end===================
    
    int g = -1;

    if (myReadFile.is_open()) 
    {
        while (getline(myReadFile,a[i]) && loop) 
        {

            if(a[i].substr(0,3)  == "bne"){
                cout<<"bne found"<<endl;

                int backup = i + 1 ;
                cout<<backup<<endl;

                for(int u = g;u<i;u++){
                    cout<<u<<endl;
                    i=u;
                    cout<<a[i]<<endl;
                    if(a[i].substr(0,3) != "cmp" ){
                        cout<<"loop running :"<<u<<endl;
                        loop = working();
                        i = backup-1;
                    }
                    else {
                        cout<<"cmp found"<<endl;
                        total_instructions++;

                        cout<<a[i].substr(5,1)<<endl;

                        if(reg[stoi(a[i].substr(5,1))] != stoi(a[i].substr(8,a[i].length() - 8 ) ) ){
                            u = g-1;
                        }else{
                            break;
                        }
                    }
                }

                for(int rege = 0 ;rege <15;rege++){
                    cout<<"r["<<rege<<"]: "<<reg[rege]<<"   ";
                }
                cout<<endl;
                i=backup+1;
            }
            else if(a[i][a[i].length()-1 ] == ':' && a[i] != "load:"){
                g = i;
            }else if(a[i].substr(0,3) != "cmp" ){
                loop = working();
            }else {
                i++;
            }


        }
    }
    else 
    cout<<"Unable to open file";
    cout<<endl;

    for(int rege = 0 ;rege <15;rege++){
        cout<<"r["<<rege<<"]: "<<reg[rege]<<"   ";
    }

    cout<<endl;

    cout<<endl<<"Total latency: "<<total_lat<<endl;
    cout<<endl<<"Total instructions: "<<total_instructions<<endl;
    cout<<endl<<"Total instructions per cycle: "<<(float)total_instructions/total_lat<<endl;

    myReadFile.close();
    return 0;
}