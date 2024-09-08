#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

string uppercase(string s);
  //avoid casesensitive issues
void showstock(string filename);
  //takes a file address as input and shows available models and pricing
int getprice(string filename, string choice, int& x);
  //using referencevariable to get power also

class processor{
public:
    string brand;
    string model;
    int power=0;
    int price=0;

    void set_processor(string b, string m){
        brand=b;
        model=m;
    }
};

class ram{
public:
    string generation;
    string capacity;
    int power=0;
    int price=0;

    void set_ram(string g, string c){
        generation=g;
        capacity=c;
    }
};

class gpu{
public:
    string brand;
    string model;
    int power=0;
    int price=0;

    void set_gpu(string b, string m){
        brand=b;
        model=m;
    }
};

class storage{
public:
    string type;
    string capacity;
    int power=0;
    int price=0;

    void set_storage(string t, string c){
        type=t;
        capacity=c;
    }
};

class psu{
public:
    int watt;
    int price;

    int calc_watt(int p, int r, int g, int s){
        //automatic calculation for required psu
        int psu=p+r+g+s;
        int requiredwatt=0;

        if(psu>150 && psu<=250){
            requiredwatt=350;
        }
        else if(psu>250 && psu<=350){
            requiredwatt=450;
        }
        else if(psu>350 && psu<=500){
            requiredwatt=550;
        }
        else requiredwatt=300;

        return requiredwatt;
    }

    int psu_cost(int p){
        //calculating psu cost according to requied watt
        int price=0;

        if(p==350){
            price=4500;
        }
        else if(p==450){
            price=5500;
        }
        else if(p==550){
            price=7000;
        }
        else if(p==0){
            price=0;
        }
        else price=3500;
        //for the 300w psu

        return price;
    }
};

class config{
    //Composition of Components
public:
    processor p;
    ram r;
    gpu g;
    storage s;
    psu w;

    void setcomponent(){
        cout<<"Enter Processor Brand(INTEL or AMD): ";
        cin>>p.brand;
        p.brand=uppercase(p.brand);
        cout<<endl;

        if(p.brand=="INTEL"){
            showstock("intel.txt");
            cout<<endl;
            cout<<"Enter Processor Model: ";
            cin>>p.model;
            p.model=uppercase(p.model);
            p.price=getprice("intel.txt", p.model, p.power);
        }

        else if(p.brand=="AMD"){
            showstock("ryzen.txt");
            cout<<endl;
            cout<<"Enter Processor Model: ";
            cin>>p.model;
            p.model=uppercase(p.model);
            p.price=getprice("ryzen.txt", p.model, p.power);
        }

        else {
            cout<<"This product is not available. "<<endl;
            p.model="N/A";
            p.price=0;

        }


        p.set_processor(p.brand, p.model);
        cout<<endl;

        cout<<"Enter RAM Generation(DDR4 or DDR5): ";
        cin>>r.generation;
        r.generation=uppercase(r.generation);
        cout<<endl;

        if(r.generation=="DDR4"){
            showstock("ddr4.txt");
            cout<<endl;
            cout<<"Enter RAM Capacity(GB): ";
            cin>>r.capacity;
            r.price=getprice("ddr4.txt", r.capacity, r.power);
        }

        else if(r.generation=="DDR5"){
            showstock("ddr5.txt");
            cout<<endl;
            cout<<"Enter RAM Capacity(GB): ";
            cin>>r.capacity;
            r.price=getprice("ddr5.txt", r.capacity, r.power);
        }

        else {
            cout<<"This product is not available. "<<endl;
            r.capacity="N/A";
            r.price=0;

        }

        r.set_ram(r.generation, r.capacity);
        cout<<endl;

        cout<<"Enter GPU Brand (NVIDIA or AMD): ";
        cin>>g.brand;
        g.brand=uppercase(g.brand);
        cout<<endl;

        if(g.brand=="NVIDIA"){
            showstock("nvidia.txt");
            cout<<endl;
            cout<<"Enter GPU Model: ";
            cin>>g.model;
            g.model=uppercase(g.model);
            g.price=getprice("nvidia.txt", g.model, g.power);
        }

        else if(g.brand=="AMD"){
            showstock("amd.txt");
            cout<<endl;
            cout<<"Enter GPU Model: ";
            cin>>g.model;
            g.model=uppercase(g.model);
            g.price=getprice("amd.txt",g.model, g.power);
        }

        else {
            cout<<"This product is not available. "<<endl;
            g.model="N/A";
            g.price=0;

        }

        g.set_gpu(g.brand, g.model);
        cout<<endl;

        cout<<"Enter Storage Type (NVME or SATA): ";
        cin>>s.type;
        s.type=uppercase(s.type);
        cout<<endl;

        if(s.type=="NVME"){
            showstock("nvme.txt");
            cout<<endl;
            cout<<"Enter Storage Capacity (GB): ";
            cin>>s.capacity;
            s.price=getprice("nvme.txt", s.capacity, s.power);
        }

        else if(s.type=="SATA"){
            showstock("sata.txt");
            cout<<endl;
            cout<<"Enter Storage Capacity (GB): ";
            cin>>s.capacity;
            s.price=getprice("sata.txt", s.capacity, s.power);
        }

        else {
            cout<<"This product is not available. "<<endl;
            s.capacity="N/A";
            s.price=0;
        }

        s.set_storage(s.type, s.capacity);
        cout<<endl;

        w.watt=w.calc_watt(p.power, r.power, g.power, s.power);
        //required power supply

        cout<<"Required Power supply: "<<w.watt<<" watts"<<endl;
        cout<<endl;

        w.price=w.psu_cost(w.watt);
    }


    void show_config(){
        cout<<setw(15)<<"Components"<<setw(20)<<"Details"<<setw(10)<<"Price"<<endl;
        cout<<setw(15)<<"Processor"<<setw(10)<<p.brand<<setw(10)<<p.model<<setw(10)<<p.price<<endl;
        cout<<setw(15)<<"RAM(GB)"<<setw(10)<<r.generation<<setw(10)<<r.capacity<<setw(10)<<r.price<<endl;
        cout<<setw(15)<<"GPU"<<setw(10)<<g.brand<<setw(10)<<g.model<<setw(10)<<g.price<<endl;
        cout<<setw(15)<<"Storage(GB)"<<setw(10)<<s.type<<setw(10)<<s.capacity<<setw(10)<<s.price<<endl;
        cout<<setw(15)<<"PSU(W)"<<setw(10)<<w.watt<<setw(10)<<""<<setw(10)<<w.price<<endl;
    }

    float tcost(){
        return p.price+r.price+g.price+s.price+w.price;
    }

};

class customer{
    //Customer membership verification
public:
    int id;
    int verification=0;
    config customconfig;

    void customer_membership(){
        char membership='N';

        cout<<"OUR SHOP PROVIDES SPECIAL DISCOUNT FOR OUR ACTIVE MEMBERS!"<<endl;
        cout<<"Do you have a membership ID (Press 'Y' for yes, anything else to skip): ";
        cin>>membership;
        if(membership=='Y' || membership=='y'){
            cout<<"Enter your membership ID: ";
            cin>>id;

            int memberID[5]={1005,2050,3060,4001,7405};
            //Member ID stored in server

            for(int i=0; i<5; i++){
                if(id==memberID[i]){
                    //checking if given ID is valid
                    verification=1;
                }
            }

            if(verification==1){
                cout<<"You will get 2% discount!"<<endl;}
            else cout<<"Your ID does not belong to the server."<<endl;
        }
        else cout<<"You missed out on the discount! "<<endl;
    }

    void purchase(){
        customconfig.setcomponent();
        customconfig.show_config();
        cout<<endl;

        long double totalcost=customconfig.tcost();
        cout<<"TOTAL COST: ";
        cout<<totalcost<<endl;
        cout<<endl;

        if(verification==1){
            //discount
            cout<<"Discounted Price: ";
            cout<<(totalcost-(totalcost*0.02))<<endl;
        }
    }
};

int main(){

    char input;
    customer c1;
    cout<<"WELCOME TO OUR SHOP 'POTATO PC BUILDER' "<<endl;
    cout<<"PRESS 'Y' TO SIGN UP AND BUILD YOUR POTATO PC OR ANYTHING ELSE TO SKIP"<<endl;
    cin>>input;
    cout<<endl;

    if(input=='Y' || input=='y'){
        c1.customer_membership();
        cout<<endl;

        cout<<"LET'S START BUILDING YOUR PC"<<endl;
        cout<<endl;

        c1.purchase();
        cout<<endl;
        cout<<"THANK YOU FOR YOUR PURCHASE. "<<endl;
    }

    else cout<<"HAVE A NICE DAY!"<<endl;
    return 0;
}

string uppercase(string s){

    for(int i=0; s[i]!='\0'; i++){
        s[i]=toupper(s[i]);}
    return s;
}

void showstock(string filename){

    ifstream file;

    vector<string> product;
    //storing product, prices, power seperately
    vector<int> price;
    vector<int> power;
    string line;
    file.open(filename);

    while(getline(file,line)){
        istringstream info(line);
        //creating a stream of strings

        string tempproduct;
        //using temporary variables to input string stream in vector
        int tempprice;
        int temppower;


        info>>tempproduct>>tempprice>>temppower;
        //collecting data from that stream and putting it into the temp variables

        product.push_back(tempproduct);
        price.push_back(tempprice);
        power.push_back(temppower);
    }

    cout<<"PRODUCT"<<setw(15)<<"PRICE"<<setw(20)<<"POWER"<<endl;

    for(int i=0; i<product.size(); i++){
        cout<<product[i]<<setw(15)<<price[i]<<"TAKA"<<setw(15)<<power[i]<<"W"<<endl;
    }
}

int getprice(string filename, string choice, int& x){

    int cost=0;
    int input=0;
    //ensuring the product user wants is in the list

    ifstream file;

    vector<string> product;
    vector<int> price;
    vector<int> power;
    string line;
    file.open(filename);

    while(getline(file,line)){

        istringstream info(line);

        string tempproduct;
        int tempprice;
        int temppower;

        info>>tempproduct>>tempprice>>temppower;

        product.push_back(tempproduct);
        price.push_back(tempprice);
        power.push_back(temppower);

    }
    for(int i=0; i<product.size(); i++){
        if(product[i]==choice){
            cost=price[i];
            x=power[i];
            input=1;
        }
    }
    if(input==0){
        cout<<"Your input didn't match any product."<<endl;
    }
    return cost;
    //sending the individual cost
}






