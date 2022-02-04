#include<iostream>
#include<string.h>
#include<conio.h>
#include<fstream>
using namespace std;
int i,n;
ifstream fin; /* it is used to read the file fin is a object using this fin variable we can open and close the file */
ofstream fout; // it is used to write the file using fout object we can open and close the file
fstream fio;
void disp();
class stock
{
		char name[20];
	float pr; int quant;

public:
	void get();
	void show();
    int stockcheck(char nm[30]);    
    void withd(int qty);
    void refil(int qty);
}st;
void stock::withd(int qty)
{
	if(quant>=qty)
	{
		quant-=qty;   // if quantity is greater or equal to qty then we should subtract 
		cout<<"\n\nStock updated.\n";
		cout<<"\n\nTotal price to be paid:"<<pr*qty;
    }
	else 
	   cout<<"\n\nInsufficient stock";
	    getch();	
}
void stock::refil(int qty)
{
		quant+=qty;    // here we should add the quantity of required stock
		cout<<"\n\nStock updated.";
	    getch();	
}
int stock::stockcheck(char nm[30])
{
	/* here we are comparing the strings entered 
		if the both strings(the item present in the stock and the item u entered ) are equal
		then it returns 0 otherwise it will return exit the program (that means both strings are not equal) */
	if(strcmp(nm,name)==0)
	 return 0;
	else 
	return 1;
}
void stock::get()
{
	cout<<"\nEnter the Name , the price and then the quantity\n"; 	
	cin>>name>>pr>>quant;
}

void stock::show()
{
	cout<<"\n"<<name<<"\t\t\t"<<quant<<"\t\t\t"<<pr;
}
void addnew()
{
    system("cls"); // this command is used to clear the command prompt(terminal)
		
	disp();
	getch();
	/*getch is used to hold the output screen and waits until user gives any type of input */
	system("cls");
	
	cout<<"\nEnter the No. of Products that you wish to add: ";
    cin>>n;
  if (n!=0)			// if no of products is not equal to zero ,now u can proceed to add the items
    {
	fout.open("shop.dat",ios::binary|ios::app); 
	/* ios::app is used for append the text to existing file
		ios::binary causes file to be open in binary mode
	*/
	/* here we used .dat extension because we are gonna create a data base of stocks */
	for(i=0;i<n;i++)
	{   
		cout<<"\n\nInput the name, price and the quantity of item respectively\n\n";
	    st.get();
	    fout.write((char*)&st,sizeof(st));
        cout<<"\n\nitem updated";
		cin.get();
    }
    cout<<"\n\nStock Updated!!";
    fout.close(); // after updating the stock we should close the file 
    cin.get();
    system("cls");
    disp();
}
	else
{

	fout.close();
	cin.get();
	system("cls");
	cout<<"\n\nNo items to be added";
}
}
void withdraw()
{
	system("cls");
	char temp[100];int qty;
	int i=0;
	long pos=0;
	disp();
	cout<<"\n\nEnter the product's name \n"<<endl;
	cin>>temp;
	cout<<"\n\nEnter quantity: \n"<<endl;
	cin>>qty;
	fio.open("shop.dat",ios::binary|ios::out|ios::in);
	/*ios::out -> used to write the text in a file
		ios::in -> used to read the text in a file
	*/
     while(fio)
     {
	    pos=fio.tellp(); // tellp() (used in o/p stream) points the position of pointer in stream  
	    fio.read((char*)&st,sizeof(st));
	    if(st.stockcheck(temp)==0)
	    {
		  /* check wheather the stock entered by the user and stock already present in stock items
		  	if both are equal then u can proceed to withdraw the required stock */
		  st.withd(qty);
		  fio.seekp(pos);
		  fio.write((char*)&st,sizeof(st));
		  i++;break;
	    }
     }
     
    
     if(i!=1)
       cout<<"\n\n!!Item not found!!";
       getch();
     fio.close();
    cin.get();
    system("cls");
	 disp(); 
	getch();
}
void disp()
{
	int i=1;
	cout<<"\n==================================================================";
	cout<<"\n\n=================\tTHE STOCK ITEMS ARE\t==================";
	cout<<"\n\n==================================================================\n";
	cout<<"\n\nPARTICULARS\tSTOCK AVAILABLE\t\t\t PRICE";
	cout<<"\n\n============================================================\n";	
	 fin.open("shop.dat",ios::binary);
     while(!fin.eof())
     {	// read the file till it reach the end
	  fin.read((char*)&st,sizeof(st));
	  if(!fin.eof())
	  {
	     if(fin.tellg()<0) //tellg() is o/p stream used to get the position in i/p sequence
	     {	i=0; break;}
	     st.show();
	  }
     }
     if(i==0)
     {	cout<<"\n\n\t\t\t!!Empty record room!!";
	getch();
     }
     fin.close();
    
}
void refill()
{
	system("cls");
	char temp[100];int qty;
	int i=0;
	long pos=0;
	disp();
	cout<<"\n\nEnter the products name \n"<<endl;
	cin>>temp;
	cout<<"\n\nEnter quantity: \n"<<endl;
	cin>>qty;
	fio.open("shop.dat",ios::binary|ios::out|ios::in);
     while(fio)
     {
	    pos=fio.tellp();
	    fio.read((char*)&st,sizeof(st));
	    if(st.stockcheck(temp)==0)
	    {
		  st.refil(qty);
		  fio.seekp(pos);
		  fio.write((char*)&st,sizeof(st));
		  i++;break;
	    }
     }
     if(i!=1)
       cout<<"\n\n!!Record not found!!";
     fio.close();
    system("cls");
    cin.get();
	 disp(); cin.get();	
}
void remove()
{
	system("cls");	
	 int i=0;
     char temp[30];
     cout<<"\n\t\t\t\tDelete Record";
     cout<<"\n\nEnter the name of the product:";
     cin>>temp;
     fout.open("temp.dat",ios::binary);
     fin.open("shop.dat",ios::binary);
     while(!fin.eof())
     {
	  fin.read((char*)&st,sizeof(st));
	  if(!fin.eof())
	    if(st.stockcheck(temp)==0)
	    {
	/* check if the stock is present in the record to delete */
		  st.show();
		  cout<<"\n\n\t\tRecord deleted";
		  i++;
	    }
	    else
		  fout.write((char*)&st,sizeof(st));
     }
     if(i==0)
       cout<<"\n\n!!Record not found!!";
     fin.close();
     fout.close();
     remove("shop.dat");
     rename("temp.dat","shop.dat");
}
int main()
{
	char pass[10];
	int i,j;
	cout<<"\n\t\tINVENTORY MANAGEMENT SYSTEM\n";	
	cout<<"=============================================================";
	cout<<"\n\n\t\t 1.Employee Menu\n\n\t\t 2.Customer Menu\n\n\t\t";
	cout<<"\n\n==========================================================\n";
	cout<<"\n\nEnter Your Choice:";
	cin>>j;
	if(j==1)
	{
	system("cls");
    cout<<"\n\n\nt\t\tPlease enter the password: ";
	
	for(int z=0;z<3;z++)
	{
		pass[z]=getch();
		system("cls");
		cout<<"\n\n\n\n\n\n\n\t\t\t\t\tPlease enter the password: ";
		for(i=1;i<=(z+1);i++)
		{
			cout<<"*";
		}
	}
	if(strcmp(pass,"abc")==0)
	{
    system("cls");
	empmenu:
	system("cls");
	cout<<"=================================================================";
	cout<<"\n\n\t\t\t    EMPLOYEE MENU\n1. Add new product\n2. Display stock\n3. Refill\n4. Remove an item\n5. Exit:";
	cout<<"\n\n\n=======+===================END OF MENU=============================";
	cout<<"\n\n Enter your Choice :\t";
	cin>>i;
	if(i==1)
	{
		addnew();getch();
	goto empmenu;
	}

	else if(i==2)
	{
		system("cls");
	disp();getch();goto empmenu;
	}
	else if(i==3)
	{
		refill();goto empmenu;
	}
	else if(i==4)
	{
		remove();getch();goto empmenu;
	}
	else 
	{
		system("cls");
	getch();
	exit(0);
}
}
else
{
	cout<<"\n\n\nINPUT CORRECT PASSWORD!!!\n\n";
	getch();

	exit(0);
}
	}
	if(j==2)
	{
		custmenu:
	system("cls");
	cout<<"=================================================================";
	cout<<"\n\n\t\t\t CUSTOMER MENU\n1. Purchase\n2. Display stock\n3. Exit:";
	cout<<"\n\n\n==========================END OF MENU=============================";
	cout<<"\n\n Enter your Choice :\t";
	cin>>i;	
	if (i==1)
	{
	withdraw();getch();goto custmenu;
	}
	else if(i==2)
	{
		system("cls");
	disp();getch();goto custmenu;
	}	
	else 
	{
		system("cls");
	getch();
	exit(0);
}	
}
	getch();
}
