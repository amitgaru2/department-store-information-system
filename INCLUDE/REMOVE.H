 //REMOVE ITEM MODULE

struct item_remove{
char name[27];
char id[5];
float quan,rate;
char day[3], month[3];
}obj,obj2;

char remove_temp[4];

void set_remove();
int set2_remove();
void get_date();

void remove_item()
{
clrscr();
ofstream fout_remove;
fout_remove.open("removed.txt",ios::out|ios::app);				//for determining 
fout_remove.seekp(0,ios::end);
int t=fout_remove.tellp();
fout_remove.close();
int k;
set_remove();
ifstream fin_item;
ofstream fout_item;
fin_item.open("item.txt");
fout_item.open("item.txt",ios::ate);
ifstream fin_remove;
fin_remove.open("removed.txt");
fin_remove.seekg(t,ios::beg);
fin_remove.read((char *)&obj2, sizeof(obj));
fin_item.seekg(0);
fin_item.read((char *)&obj, sizeof(obj));
k=0;
// reducing the quantity in item.txt
while(fin_item)
{
	if((stricmp(obj.id, obj2.id))==0)
	{
		obj.quan = obj.quan - obj2.quan;
		fout_item.seekp(k*sizeof(obj));
		fout_item.write((char *)&obj, sizeof(obj));
		break;
	}
	k++;
	fin_item.read((char*)&obj, sizeof(obj));
}
fin_item.close();
fout_item.close();
fin_remove.close();
//display removed item
cout<<endl<<endl<<"\t\t\tItem              =  "<<obj2.name<<endl<<"\t\t\t"<<"ID                =  "<<obj.id<<endl<<"\t\t\t"<<"Quantity Removed  =  "<<obj2.quan<<"\n\t\t\tQuantity Remained =  "<<obj.quan;
cout<<endl<<endl<<endl<<endl<<endl<<"\t\t\tPress 'm' to go to Main Screen !!!";
while(getch()!='m'){}
	
fflush(stdout);
fflush(stdin);
}

void set_remove()
{
	int temp=5;
	clrscr();
	struct date d;
	getdate(&d);
	cout<<endl<<endl<<"\t\t\t\t REMOVE ITEM !!!";
	cout<<endl<<endl<<endl<<"\t Enter Item Id : ";
	gets(obj2.id);										//item before removed /to be removed
	cout<<endl<<"\tEnter Quantity : ";
	gets(remove_temp);									//item quantity to be removed					
	temp = set2_remove();											//check
	if(temp==1)
	{ 		//write
		clrscr();
		cout<<endl<<endl<<"\t\t\t\tITEM REMOVED:";
		strcpy(obj2.name, obj.name);
		get_date();
		ofstream fout_remove;
		fout_remove.open("removed.txt", ios::out|ios::app);
		fout_remove.write((char *)&obj2, sizeof(obj2));
		fout_remove.close();
	}
	else
		set_remove();

}

int set2_remove()
{
	int temp2=0; 	//for raising the count to check if the item name is available
	int i_temp=0;
	int event=0;
	while(remove_temp[i_temp]!='\0')
	{
		if(remove_temp[i_temp]<48 || remove_temp[i_temp]>57)
		{
			event=1;
			break;
		}
		i_temp++;
	}
	if(event==1 || strlen(remove_temp)>4 || strlen(remove_temp)<1)
	{
		cout<<endl<<endl<<endl<<"\t\t\tInvalid Quantity Input !!!";
		cout<<endl<<endl<<"\t\t\tPress any key to continue !!! ";
		getch();
		return 0;
	}
	else
	{
		int j_temp=0;
		obj2.quan=0;
		int length=strlen(remove_temp);
		for(i_temp=(length-1);i_temp>=0;i_temp--)
		{
			remove_temp[i_temp]=remove_temp[i_temp]-48;
			obj2.quan=obj2.quan+remove_temp[i_temp]*pow(10,j_temp);
			j_temp++;
		}
		ifstream fin_remove;
		fin_remove.open("item.txt");
		fin_remove.seekg(0);
		fin_remove.read((char *)&obj,sizeof(obj));		//check item name,quantity if available in the item list
		while(fin_remove)
		{
			if(stricmp(obj.id, obj2.id)==0)
			{
				temp2=1;
				break;
			}
			fin_remove.read((char *)&obj,sizeof(obj));
		}
		fin_remove.close();
		
			if(temp2 == 0)
			{
				cout<<endl<<endl<<endl<<"\t\tItem ID invalid or Item not available !!!";
				cout<<endl<<endl<<"\t\t\tPress any key to continue !!! ";
				getch();
				return 0;
			}

			else
			{
				if(obj.quan<obj2.quan)
				{
					cout<<endl<<endl<<endl<<"\t\t\tQuantity not sufficient in store !!!";
					cout<<endl<<endl<<"\t\t\tPress any key to continue !!! ";
					getch();
					return 0;
				}
				else if(obj2.quan<=0)
				{
					cout<<endl<<endl<<endl<<"\t\t\tInvalid Quantity Input !!!";
					cout<<endl<<endl<<"\t\t\tPress any key to continue !!! ";
					getch();
					return 0;
				}
				else return 1;
			
		    }

		}

} 


void get_date()
{
int iday, imonth;
struct date d;
getdate(&d);
iday = d.da_day;
imonth = d.da_mon;
obj2.day[1] = 48 + iday % 10;
obj2.day[0] = 48 + (iday / 10);
obj2.month[1] = 48 +(imonth % 10);
obj2.month[0] = 48 + (imonth / 10);
}

