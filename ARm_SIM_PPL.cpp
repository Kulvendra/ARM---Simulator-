#include <iostream>
#include <string>
#include <fstream>
#include<map>
#include<vector>

using namespace std;

ifstream myReadFile;
string a[100];
int i=0,totalLines;
int reg[16];
int memory[100];
char ck;

int add(int ,int ,int,int );
int sub(int ,int ,int,int );
int mul(int ,int ,int,int );
int mov(int ,int ,int,int );
int str(int ,int ,int,int );
int ldr(int ,int ,int,int );
int mov(int ,int);

int operandValues(string);
int instExecution();
int check(string);
int instFetch(int l);
int instDecode();
int instMemory();
int instWriteBack();

//........................................................................................

class pipeline{

    public:
    string instruction = "";
    int op1,op2,op3;
    int alu;
    int checkOp;
    int writeBackValue;
    int writeBackRegister;  

    int writeMemory;
    int strMemoryValue;

    int movCheck;

    int writeMemoryBkRegister;
};
pipeline IF_ID[5];

//............................................................................................
/*
        alu value:    alu();                        For hashvalues of Operand3:     checkOp();
        add:1                                           m=1
        sub:2                                       For Register value of Operand3:
        mul:3                                           m=2
        ldr:4                                       For non hash value:
        str:5                                           m=0
        mov:6
        bne:7
        cmp:8
*/

//.......................................IF................................................

int instFetch(int l){
IF_ID[4].instruction = a[l];
//cout<<a[l]<<endl;
    if(IF_ID[4].instruction != ""){
cout<<"IF :=> "+IF_ID[4].instruction<<endl;
    }
    else{
       cout<<"ID :=>blank "<<endl;
       }
instDecode();
IF_ID[3].instruction=IF_ID[4].instruction;
IF_ID[3].alu=IF_ID[4].alu;
return 0;
}
//........................................ID.................................................
int instDecode(){  
if(IF_ID[3].instruction != ""){    
int x= check(IF_ID[3].instruction);
////cout<<x<<endl;
operandValues(IF_ID[3].instruction);
IF_ID[3].alu=x;
cout<<"ID :=> "+IF_ID[3].instruction<<endl;
}else{
cout<<"ID :=>blank "<<endl;    
}

instExecution();
IF_ID[2].instruction=IF_ID[3].instruction;
IF_ID[2].op1=IF_ID[3].op1;
IF_ID[2].op2=IF_ID[3].op2;
IF_ID[2].op3=IF_ID[3].op3;
IF_ID[2].checkOp=IF_ID[3].checkOp;
IF_ID[2].alu=IF_ID[3].alu;
IF_ID[2].movCheck=IF_ID[3].movCheck;
    return 0;
}
//........................................EXE...................................................

int instExecution(){
    if(IF_ID[2].instruction != ""){
    int ROp1,ROp2,ROp3;
    int check;
    int alu;
    ROp1=IF_ID[2].op1;
    ROp2=IF_ID[2].op2;
    ROp3 = IF_ID[2].op3;
    check=IF_ID[2].checkOp;
    alu=IF_ID[2].alu;  
    int writeBack;
    switch(alu){
        case 1 :        
            //cout<<"ADD Found..(Switch)!!";
            writeBack = add(ROp1,ROp2,ROp3,check);                   
            break;
        case 2 :        
            ////cout<<"SUB Found..!!";
            writeBack = sub(ROp1,ROp2,ROp3,check);              
            break;
        case 3 :        
            ////cout<<"MUL Found..!!";
            writeBack = mul(ROp1,ROp2,ROp3,check);              
            break;        
        case 4 :        
            ////cout<<"LDR Found..!!";
            writeBack = ldr(ROp1,ROp2,ROp3,check);               
            break;
         case 5 :        
           // //cout<<"STR Found..!!";
            writeBack = str(ROp1,ROp2,ROp3,check);             
            break;   
        case 6 :        
            ////cout<<"MOV Found..!!";
            writeBack = mov(ROp1,ROp2);             
            break;
        case 7 :        
           // //cout<<"BNE Found..!!";
           // writeBack = add(ROp1,ROp2,ROp3,check);   
            //cout<<"WriteBack Value:"<<writeBack<<endl; 
            break;
        case 8 :        
            ////cout<<"CMP Found..!!";
           // writeBack = add(ROp1,ROp2,ROp3,check);   
            //cout<<"WriteBack Value:"<<writeBack<<endl; 
            break;
    }  
    IF_ID[2].writeBackRegister=ROp1;
    IF_ID[2].writeBackValue=writeBack;
cout<<"IE :=> "+IF_ID[2].instruction<<endl;    
    }else{
cout<<"IE :=>blank "<<endl;    
} 
    instMemory();
    IF_ID[1].instruction=IF_ID[2].instruction;
    IF_ID[1].writeBackRegister=IF_ID[2].writeBackRegister;
    IF_ID[1].writeBackValue=IF_ID[2].writeBackValue;
    IF_ID[1].writeMemory=IF_ID[2].writeMemory;
    IF_ID[1].strMemoryValue=IF_ID[2].strMemoryValue;
    IF_ID[1].writeMemoryBkRegister=IF_ID[2].writeMemoryBkRegister;
    IF_ID[1].alu=IF_ID[2].alu;  
}
//....................................MEM....................................................

int instMemory(){
        if(IF_ID[1].instruction!=""){
            memory[IF_ID[1].writeMemory]=IF_ID[1].strMemoryValue;
            cout<<"MEM :=> "+IF_ID[1].instruction<<endl;            
        }else{
        cout<<"MEM :=>blank "<<endl;
        }
        instWriteBack();   
    if(IF_ID[1].alu!=5){
    IF_ID[0].instruction=IF_ID[1].instruction;
    IF_ID[0].writeBackRegister=IF_ID[1].writeBackRegister;
    IF_ID[0].writeBackValue=IF_ID[1].writeBackValue;
    IF_ID[0].writeMemoryBkRegister=IF_ID[1].writeMemoryBkRegister;
    IF_ID[0].alu=IF_ID[1].alu;
    }
}
//....................................WB..........................................................

int instWriteBack(){
    if(IF_ID[0].instruction != ""){
        int temp=IF_ID[0].alu;
        if(temp==4){
            reg[IF_ID[0].writeMemoryBkRegister]=memory[IF_ID[0].writeBackValue];
            cout<<"WB :=> "+IF_ID[0].instruction<<endl;
        }else{        
        //cout<<"ALU Number:=> "<<temp<<endl;            
    int regNumber=IF_ID[0].writeBackRegister;
    int regValue=IF_ID[0].writeBackValue;
    reg[regNumber]=regValue;
    cout<<"WB :=> "+IF_ID[0].instruction<<endl;
    //cout<<"Register"<<regNumber<<"="<<regValue<<endl<<endl;
    }
    }
    else{
cout<<"WB :=>blank "<<endl;
}
cout<<endl;
}
//.......................................Value Extraction....................................................

int operandValues(string s){
        int op[3],m=0;
    for(int j=0;j<s.length();j++)
            {   
                std::size_t found = s.find("r");

                if(found==std::string::npos)
                {
                    //cout<<"error"<<endl;                    
                    break;
                }
                for(int k=found;k<s.length();k++)
                {
                    if(s[k]>='0' && s[k]<='9')
                    {
                        op[0]=(int)s[k]-48;   
                        break;
                    }
                }

                std::size_t found2=s.find("#",found+1);
                found=s.find("r",found+1);
                if(found!=std::string::npos || found2!=std::string::npos)
                {
                     if(found!=std::string::npos || found2==std::string::npos)
                    {                
                for(int k=found;k<s.length();k++)
                {
                    if(s[k]>='0' && s[k]<='9')
                    {
                        op[1]=(int)s[k]-48;    
                         IF_ID[3].movCheck=2;                  
                        break;
                    }
                }
                    }
                    else{
                        string hashvalue="";
                        for(int k=found2;k<s.length();k++)
                        {
                            if(s[k]>='0' && s[k]<='9')
                            {
                                hashvalue+=s[k];
                            }
                        }
                        if(hashvalue=="")
                            {                                
                                break;
                            }
                            op[1]=stoi(hashvalue);  

                            IF_ID[3].movCheck=1;                                   
                    }
                }

                std::size_t found1=s.find("#",found+1);
                found=s.find("r",found+1);

                if(found!=std::string::npos || found1!=std::string::npos)
                {
                    if(found==std::string::npos || found1!=std::string::npos)
                    {
                        string hashvalue="";
                        for(int k=found1;k<s.length();k++)
                        {
                            if(s[k]>='0' && s[k]<='9')
                            {
                                hashvalue+=s[k];
                            }
                        }
                        if(hashvalue=="")
                            {                                
                                break;
                            }
                            op[2]=stoi(hashvalue);                         
                            m=1;
                    }
                    else
                    {
                        for(int k=found;k<s.length();k++)
                        {
                            if(s[k]>='0' && s[k]<='9')
                            {
                                op[2]=(int)s[k]-48;                            
                                break;
                            }
                        }           
                            m=2;
                    }
                }
                else
                {                    
                    break;
                }
        }
    IF_ID[3].op1=op[0];
    IF_ID[3].op2=op[1];
    IF_ID[3].op3=op[2];
    IF_ID[3].checkOp=m;
}
//.................................Funtion Checking.........................................................

int check(string instruction){    
    int alu;
     for(int j=0;j<instruction.length()-2;j++){
        if((instruction.substr(j,4)).compare("ADD ")==0)
            {
                //cout<<"ADD Found"<<endl;
                alu=1;            
            }
            else  if((instruction.substr(j,4)).compare("SUB ")==0)
            {
                //cout<<"SUB Found"<<endl;
                alu=2;            
            }else  if((instruction.substr(j,4)).compare("MUL ")==0)
            {
                //cout<<"MUL Found"<<endl;
                alu=3;            
            }else  if((instruction.substr(j,4)).compare("LDR ")==0)
            {                
                alu=4;
                //cout<<"LDR Found:=> "+alu<<endl;            
            }else  if((instruction.substr(j,4)).compare("STR ")==0)
            {
                //cout<<"STR Found"<<endl;
                alu=5;            
            }else  if((instruction.substr(j,4)).compare("MOV ")==0)
            {
                //cout<<"MOV Found"<<endl;
                alu=6;            
            }else  if((instruction.substr(j,4)).compare("BNE ")==0)
            {
                //cout<<"BNE Found"<<endl;
                alu=7;            
            }else  if((instruction.substr(j,4)).compare("CMP ")==0)
            {
                //cout<<"CMP Found"<<endl;
                alu=8;            
            }
        }   
    return alu;
}
//.....................................ALL Functions.................................................

int add(int r1,int r2,int r,int temp){
    int writeBK;
   // //cout<<"Temp :="<<temp<<endl;
    if(temp==1){
        writeBK=reg[r2]+r;
    }
    else if(temp==2){
        writeBK=reg[r2]+reg[r];
        //cout<<"Write Back Value in ADD Function:=>"<<writeBK<<"   "<<"Reg2:=>"<<reg[r2]<<"   "<<"Reg3:=>"<<reg[r];
    }
return writeBK;
}

int sub(int r1,int r2,int r,int temp){

    int writeBK;
    if(temp==1){
        writeBK=reg[r2]-r;
    }
    else if(temp==2){
        writeBK=reg[r2]-reg[r];
    }
return writeBK;
}

int mul(int r1,int r2,int r,int temp){
    int writeBK;
    if(temp==1){
        writeBK=reg[r2]*r; 
    }
    else if(temp==2){
        writeBK=reg[r2]*reg[r];
    }
return writeBK;
}

int str(int r1,int r2,int r , int temp){
    int writeBK;
   if(temp==1){
        IF_ID[2].strMemoryValue=reg[r1];
       // cout<<"                       WriteBackValue:=> "<<reg[r1]<<endl;
        IF_ID[2].writeMemory=reg[r2]+r/4;          
   }else{     
       IF_ID[2].strMemoryValue=reg[r1];
       IF_ID[2].writeMemory=reg[r2];
   }
return writeBK;
}

int ldr(int r1,int r2,int r , int temp){
    int writeBK;
   if(temp==1){
        writeBK=reg[r2]+r/4;
        IF_ID[2].writeMemoryBkRegister=r1;                 
   }else{     
       writeBK=reg[r2];
       IF_ID[2].writeMemoryBkRegister=r1;       
   }       
return writeBK;
}

int mov(int r1,int r2){

    int writeBK;
   if(IF_ID[2].movCheck==1){
       writeBK=r2;                 
   }else{            
       writeBK=reg[r2];       
   }       
return writeBK;

}
//......................................Main..........................................................

int main(){    

    for(int d=0;d<16;d++){
        reg[d]=0;
    }

    myReadFile.open("in.txt");

    
    int k=0;

    if (myReadFile.is_open()) 
    {
        while (getline(myReadFile,a[k])){
            
            k++;

        }

        totalLines=k;
        ////cout<<"Total Lines:=>"<<totalLines<<endl;
    }
    else{

        //cout<<"Unable to open file";
        //cout<<endl;
    }
    
    ////cout<<"Total Lines:"<<k<<endl;    
    for(i=0;i<totalLines+4;i++)
    {
    instFetch(i);   
    }

    for(i=1;i<=10;i++){
        cout<<"                                    Register"<<i<<" :=>"<<reg[i]<<endl;
    }
    // for(i=1;i<=20;i++){
    //     cout<<"                                    Memory"<<i<<" :=>"<<memory[i]<<endl;
    // }
    return 0 ;        
}


