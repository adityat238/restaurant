#include<iostream>
#include<fstream>
#include<string.h>
#include<conio.h>
using namespace std;
class menu
{
    public:
    int itemcode;
    char itemname[100];
    int itemprice;
    public:
        void accept()
        {
            cout<<"enter item code: ";
            cin>>itemcode;
            cout<<"enter item name: ";
            cin>>itemname;
            cout<<"enter item price: ";
            cin>>itemprice;
        }
        void display()
        {
            cout<<itemcode<<"\t\t"<<itemname<<"\t\t"<<itemprice<<endl;

        }


};
menu obj;//global object
void additem()//adding items to file
{
    obj.accept();
    fstream outfile;
    outfile.open("c:\\vmm_programms\\menu.txt",ios::app);
    outfile.write((char*)&obj,sizeof(obj));
    cout<<"item added successfully"<<endl;
}
void viewmenu()
{
  fstream infile;
  infile.open("c:\\vmm_programms\\menu.txt",ios::in);
  infile.seekg(0,ios::end);
  int n=infile.tellg()/sizeof(obj);
  infile.seekg(0,ios::beg);
  cout<<"code"<<"\t\t"<<"name"<<"\t\t"<<"price"<<endl;
  for(int i=1;i<=n;i++)
  {
      infile.read((char*)&obj,sizeof(obj));
      obj.display();
  }
}
void removeitem()
{
    fstream infile,outfile;
    infile.open("c:\\vmm_programms\\menu.txt",ios::in);
    outfile.open("c:\\vmm_programms\\temp.txt",ios::out);
    infile.seekg(0,ios::end);
    int x=infile.tellg()/sizeof(obj);
    infile.seekg(0,ios::beg);
    int sr;
    cout<<"enter itemcode to remove: ";
    cin>>sr;
    for(int i=1;i<=x;i++)
    {
        infile.read((char*)&obj,sizeof(obj));

    if(obj.itemcode==sr)
    {
        cout<<"item removed successfully"<<endl;
    }
    else
    {
        outfile.write((char*)&obj,sizeof(obj));
    }}
infile.close();
outfile.close();
remove("c:\\vmm_programms\\menu.txt");
    rename("c:\\vmm_programms\\temp.txt","c:\\vmm_programms\\menu.txt");
}
void updateitem()
{
  fstream rd,wr;
  rd.open("c:\\vmm_programms\\menu.txt",ios::in);
  wr.open("c:\\vmm_programms\\temp.txt",ios::out);
  rd.seekg(0,ios::end);
  int n=rd.tellg()/sizeof(obj);
  rd.seekg(0,ios::beg);
  int sr;
  cout<<"enter itemcode to update item: ";
  cin>>sr;
  for(int i=1;i<=n;i++)
  {
      rd.read((char*)&obj,sizeof(obj));
      if(obj.itemcode==sr)
      {
          obj.accept();
          wr.write((char*)&obj,sizeof(obj));
      }
      else
      {
          wr.write((char*)&obj,sizeof(obj));
      }
  }
  rd.close();
  wr.close();
  remove("c:\\vmm_programms\\menu.txt");
  rename("c:\\vmm_programms\\temp.txt","c:\\vmm_programms\\menu.txt");
}
class bill
{
public:
    int dd,mm,yy,pr,qty,billid,total,icode;
    char iname[100];
public:
    void accept(int bid,int d,int m,int y,int ic,int q)
    {
        billid=bid;
        dd=d;
        mm=m;
        yy=y;
        icode=ic;
        qty=q;
        fstream rd;
        rd.open("c:\\vmm_programms\\menu.txt");
        rd.seekg(0,ios::end);
        int n=rd.tellg()/sizeof(obj);
        rd.seekg(0,ios::beg);
        for(int i=1;i<=n;i++)
        {
            rd.read((char*)&obj,sizeof(obj));
            if(icode==obj.itemcode)
            {
                strcpy(iname,obj.itemname);
                pr=obj.itemprice;
                total=pr*qty;
            }
        }
    }
};
bill bobj;//global object of class bill
void preparebill()
{
    int bill_number;
    cout<<"enter bill number: ";
    cin>>bill_number;
    int date,month,year;
    cout<<"enter date in dd mm yy format: ";
    cin>>date>>month>>year;
    int choice=0;//because we have to remove garbage value,if any
    while(1)
    {
        int itemcode;
        cout<<"enter item code: ";
        cin>>itemcode;
        int quantity;
        cout<<"enter quantity: ";
        cin>>quantity;
        bobj.accept(bill_number,date,month,year,itemcode,quantity);
        fstream wr;
        wr.open("c:\\vmm_programms\\bill.txt",ios::app);
        wr.write((char*)&bobj,sizeof(bobj));
        wr.close();
        cout<<endl<<endl<<"press 1 to add new item ";
        cout<<endl<<"press 2 to prepare bill ";
        cin>>choice;
        if(choice==2)
        {
            break;
        }
    }
    cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
    cout<<"bill number: "<<bill_number<<"\t\t"<<"dated: "<<date<<" "<<month<<" "<<year<<endl<<endl;
    cout<<endl<<endl;
    cout<<"*******************************************"<<endl;
    cout<<"star oriented catering"<<endl;
    cout<<"*******************************************"<<endl;
    fstream wr,rd;
    rd.open("c:\\vmm_programms\\bill.txt",ios::in);
    rd.seekg(0,ios::end);
    int x=rd.tellg()/sizeof(bobj);
    rd.seekg(0,ios::beg);
    cout<<"code"<<"\t"<<"name"<<"\t"<<"quant"<<"\t"<<"price"<<"\t"<<"total"<<endl<<endl;
    int ftotal=0;
    for(int i=1;i<=x;i++)
    {
        rd.read((char*)&bobj,sizeof(bobj));
        if(bobj.billid==bill_number&&bobj.dd==date&&bobj.mm==month&&bobj.yy==year)
        {
            cout<<bobj.icode<<"\t"<<bobj.iname<<"\t"<<bobj.qty<<"\t"<<bobj.pr<<"\t"<<bobj.total<<endl;
            ftotal=ftotal+bobj.total;

        }

    }
    cout<<endl<<endl<<endl;
    cout<<"******************************************"<<endl;
    cout<<"total amount is: "<<ftotal<<endl;
    cout<<"******************************************"<<endl;

}
void viewsales()
{
    int date,month,year;
    cout<<"enter date in dd mm yyyy format: ";
    cin>>date>>month>>year;
    cout<<endl;
    fstream rd;
    rd.open("c:\\vmm_programms\\bill.txt",ios::in);
    rd.seekg(0,ios::end);
    int n=rd.tellg()/sizeof(bobj);
    rd.seekg(0,ios::beg);
    int stotal=0;
    cout<<"id"<<"\t"<<"code"<<"\t"<<"name"<<"\t"<<"quant"<<"\t"<<"price"<<"\t"<<"total"<<endl<<endl;
    for( int i=1;i<=n;i++)
    {
        rd.read((char*)&bobj,sizeof(bobj));
        if(date==bobj.dd&&month==bobj.mm&&year==bobj.yy)
        {
            cout<<bobj.billid<<"\t"<<bobj.icode<<"\t"<<bobj.iname<<"\t"<<bobj.qty<<"\t"<<bobj.pr<<"\t"<<bobj.total<<endl;
            stotal=stotal+bobj.total;
        }
    }
    cout<<"*************************************"<<endl;
    cout<<"total sales are: "<<stotal<<endl;
    cout<<"*************************************"<<endl;

}
main()
{
    int choice;
    do
    {
       cout<<"1) to prepare bill"<<endl
           <<"2) to view sales"<<endl
           <<"3) to add new item"<<endl
           <<"4) to view menu"<<endl
           <<"5) to remove item from menu"<<endl
           <<"6) to update menu"<<endl
           <<"7) exit"<<endl;
           cout<<"enter your choice: ";
           cin>>choice;
           switch(choice)
           {
               case 1: preparebill();break;
               case 2: viewsales();break;
               case 3: additem();break;
               case 4: viewmenu();break;
               case 5: removeitem();break;
               case 6: updateitem();break;
               case 7: exit(0);
               default:
                cout<<"invalid choice"<<endl;
           }
    }while(1);
}


