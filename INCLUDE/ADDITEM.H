//ADD ITEM MODULE

struct add_item
{
char name[27];
char id[5];
float quan, rate;
char day[3], month[3];
}file;

char get_rate[5];
char get_quan[5];

void add_cur_date();
void add_set();
int add_set1();
int add_set2();
void add_set3();
void add_quan();

void additem()
{
char choicestr[2];
int choice;
re_choice:
clrscr();
cout<<endl<<endl<<endl<<"\t\t\t\t1.ADD NEW ITEM\n\t\t\t\t2.ADD QUANTITY\n\t\t\t\t3.BACK\n\n\t\t\t\t";
gets(choicestr);
if(choicestr[0]<48 || choicestr[0]>57)
{
	cout<<endl<<endl<<endl<<endl<<"\t\t\t\tInvalid Choice !!!";
	cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!! ";
	getch();
	goto re_choice;
}
else if(strlen(choicestr)==0 || strlen(choicestr)>1)
{
	cout<<endl<<endl<<endl<<endl<<"\t\t\t\tInvalid Input !!!";
	cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!! ";
	getch();
	goto re_choice;
}
else
{
	choice = choicestr[0] - 48;
	if(choice==1)
		add_set(); 							//Add item
	else if(choice==2)
		add_quan();
	else if(choice==3)
	{
		goto end;
	}
	else
		goto re_choice;
}
end:
fflush(stdout);
fflush(stdin);
}

void add_set()
{
	int return_temp1, return_temp2;
	return_temp1 = add_set1(); 							//read and input data check
	while (return_temp1 == 0)
	{
		return_temp1 = add_set1();
	}
	return_temp2 = add_set2();							//check in the file
	if(return_temp2 == 1)
		add_set3();										 //write to the file
	else
		add_set();

}
int add_set1()
{
	int event;
	int i_temp;
	int j_temp;
	clrscr();
	cout<<endl<<"\t\t\t\tADD NEW ITEM !!!";
	cout<<endl<<endl<<endl<<"\tEnter Item Name  : ";
	gets(file.name);
	if(strlen(file.name)==0 || strlen(file.name)<3 || strlen(file.name)>26)
	{
		cout<<endl<<endl<<endl<<"\t\t\tInvalid Name Input";
		cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!!";
		getch();
		return 0;
	}
	cout<<endl<<"\tEnter Id         : ";
	gets(file.id);
	if(strlen(file.id) != 4)
	{
	cout<<endl<<endl<<endl<<"\t\t\tInvalid ID Input ( Choose 4 characters ID ) !!!";
	cout<<endl<<endl<<"\t\t\t   Press Any Key to Continue !!! ";
	getch();
	return 0;
	}
	
	
	cout<<endl<<"\tEnter Quantity   : ";
	gets(get_quan);
	i_temp=0;
	event=0;
	while(get_quan[i_temp]!='\0')
	{
		if(get_quan[i_temp]<48 || get_quan[i_temp]>57)
		{
			event=1;
			break;
		}
		i_temp++;
	}
	if(event==1 || strlen(get_quan)>4 || strlen(get_quan)<1)
	{
		cout<<endl<<endl<<endl<<endl<<"\t\t\tInvalid QUANTITY Input !!!";
		cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!! ";
		getch();
		return 0;
		
	}
	else
	{
		j_temp=0;
		file.quan=0;
		int length=strlen(get_quan);
		for(i_temp=(length-1);i_temp>=0;i_temp--)
		{
			get_quan[i_temp] = get_quan[i_temp]-48;
			file.quan = file.quan+get_quan[i_temp]*pow(10,j_temp);
			j_temp++;
		}
		if(file.quan == 0)
		{
			cout<<endl<<endl<<endl<<endl<<"\t\t\tInvalid QUANTITY Input !!!";
			cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!! ";
			getch();
			return 0;	
		}
	}

	cout<<endl<<"\tEnter Rate       : ";
	gets(get_rate);
	i_temp=0;
	event=0;
	while(get_rate[i_temp]!='\0')
	{
		if(get_rate[i_temp]<48 || get_rate[i_temp]>57)
		{
			event=1;
			break;
		}
		i_temp++;
	}
	if(event==1 || strlen(get_rate)>4 || strlen(get_rate)<1)
	{
		cout<<endl<<endl<<endl<<endl<<"\t\t\tInvalid RATE Input !!!";
		cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!! ";
		getch();
		return 0;	
	}
	else
	{
		j_temp=0;
		file.rate=0;
		int length=strlen(get_rate);
		for(i_temp=(length-1);i_temp>=0;i_temp--)
		{
			get_rate[i_temp]=get_rate[i_temp]-48;
			file.rate=file.rate+get_rate[i_temp]*pow(10,j_temp);
			j_temp++;
		}
		if(file.rate==0)
		{
			cout<<endl<<endl<<endl<<endl<<"\t\t\tInvalid RATE Input !!!";
			cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!! ";
			getch();
			return 0;
		}
	}


}

int add_set2()
{
	int temp=5;								 //for counting to check the item name or id
	add_item obj;
	ifstream fin_add;
	//compare id if already existing or not
	fin_add.open("item.txt", ios::in);
	fin_add.seekg(0);
	fin_add.read((char *)&obj, sizeof(obj));
	while(fin_add)
	{
		if(stricmp(file.id, obj.id)==0)
		{
			temp=1;
			break;
		}
		fin_add.read((char *)&obj,sizeof(obj));
	}
	fin_add.close();
	if(temp==1)
	{
		cout<<endl<<endl<<endl<<"\t\t\tId Already Exist for Item Name : "<<obj.name;
		cout<<endl<<endl<<"\t\t\t   Press Any Key to Continue !!! ";
		getch();
		return 0;
	}

	else return 1;

}

void add_set3()
{
clrscr();
char ch;
add_cur_date();
cout<<endl<<endl<<endl<<endl<<"\t\t\t\tITEM DETAILS:"<<endl<<endl<<"\t\t\tItem Name     :  "<<file.name<<"\n\t\t\tItem ID       :  "<<file.id<<"\n\t\t\tItem Quantity :  "<<file.quan<<"\n\t\t\tItem Rate     :  "<<file.rate<<"\n\t\t\tDate Added    :  "<<file.day<<"/"<<file.month;
cout<<endl<<endl<<endl<<endl<<endl<<"\t\t\tPress 'y' to Add Item to Store !!!\n\t\t\tOR Press 'n' to Discard the Item !!! ";
re_input1:
ch = getch();
if(ch == 'y')
{
	clrscr();
	ofstream fout_add;
	fout_add.open("item.txt", ios::out|ios::app|ios::binary);
	fout_add.seekp(0,ios::end);
	fout_add.write((char *)&file, sizeof(file));
	fout_add.close();
	clrscr();
	cout<<endl<<endl<<endl<<endl<<"\t\t\t\tADDED ITEM:"<<endl<<endl<<"\t\t\tItem Name     :  "<<file.name<<"\n\t\t\tItem ID       :  "<<file.id<<"\n\t\t\tItem Quantity :  "<<file.quan<<"\n\t\t\tItem Rate     :  "<<file.rate<<"\n\t\t\tDate Added    :  "<<file.day<<"/"<<file.month;
	cout<<endl<<endl<<endl<<endl<<endl<<endl<<"\t\t\tPress 'a' to Add More Items !!!\n\t\t\tOR Press 'm' to go Main Screen !!! ";
	re_input21:
	ch=getch();
	if(ch=='a')
		add_set();
	else if(ch=='m')
		goto end;
	else goto re_input21;
}
else if(ch == 'n')
{
	clrscr();
	cout<<endl<<endl<<endl<<endl<<endl<<endl<<"\t\t\t\tItem Not Added !!!";
	cout<<endl<<endl<<endl<<endl<<endl<<endl<<"\t\t\tPress 'a' to Add More Items !!!\n\t\t\tOR Press 'm' to go Main Screen !!! ";
	re_input22:
	ch=getch();
	if(ch=='a')
	add_set();
	else if(ch=='m')
	goto end;
	else goto re_input22;
}
else goto re_input1;
clrscr();

end:}

void add_quan()
{
start_add_quan:
int file_pos=0;
int temp=0;
clrscr();
cout<<endl<<"\t\t\tADD QUANTITY TO EXISTING ITEM !!!";
cout<<endl<<endl<<endl<<"\tEnter Item Id : ";
gets(file.id);
add_item obj;
ifstream fin_add;
fin_add.open("item.txt");
fin_add.seekg(0);
fin_add.read((char *)&obj,sizeof(obj));		//check item //name,quantity if available in the item list
while(fin_add)
{
	if(stricmp(obj.id,file.id)==0)
	{
		temp=1;
		break;
	}
	fin_add.read((char *)&obj, sizeof(obj));
}
fin_add.close();
if(temp==0)
{
	cout<<endl<<endl<<endl<<"\t\t\tItem Not Found !!!";
	cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!! ";
	getch();
	goto start_add_quan;
}
else if(temp==1)
{
	cout<<endl<<"\tEnter Quantity  : ";
	gets(get_quan);
	int i_temp=0;
	int event=0;
	while(get_quan[i_temp]!='\0')
	{
		if(get_quan[i_temp]<48 || get_quan[i_temp]>57)
		{
			event=1;
			break;
		}
		i_temp++;
	}
	if(event ==1 || strlen(get_quan)>4 || strlen(get_quan)<1)
	{
		cout<<endl<<endl<<endl<<"\t\t\tInvalid Quantity Input !!!";
		cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!! ";
		getch();
		goto start_add_quan;
	}
	else
	{
		int j_temp=0;
		file.quan=0;
		int length=strlen(get_quan);
		for(i_temp=(length-1);i_temp>=0;i_temp--)			//conversion of string quantity to integer
		{
			get_quan[i_temp] = get_quan[i_temp]-48;
			file.quan = file.quan+get_quan[i_temp]*pow(10,j_temp);
			j_temp++;
		}
		if(file.quan==0)
		{
		cout<<endl<<endl<<endl<<"\t\t\tInvalid Quantity Input !!!";
		cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!! ";
		getch();
		goto start_add_quan;
		}
		else
		{
			ofstream fout_add;
			ifstream fin_add;
			fout_add.open("item.txt",ios::ate);
			fin_add.open("item.txt");
			fin_add.seekg(0);
			fin_add.read((char *)&obj,sizeof(obj));							//check item
			while(fin_add)
			{
				if(stricmp(obj.id,file.id)==0)
				{
					obj.quan=obj.quan+file.quan;
					fout_add.seekp(file_pos * sizeof(obj));
					fout_add.write((char *)&obj, sizeof(obj));
					cout<<endl<<endl<<endl<<"\t\t"<<" Quantity Added to Item Name : "<<obj.name;
					cout<<endl<<endl<<"\t\t\t  Press 'm' to go Main Screen !!! ";
					while(getch()!='m'){}
					break;
				}
				file_pos++;
				fin_add.read((char *)&obj,sizeof(obj));
			}
			fout_add.close();
			fin_add.close();
		}
	}
}

}

void add_cur_date()
{
int iday, imonth;
struct date d;
getdate(&d);
iday = d.da_day;
imonth = d.da_mon;
file.day[1] = 48 + iday % 10;
file.day[0] = 48 + (iday / 10);
file.month[1] = 48 +(imonth % 10);
file.month[0] = 48 + (imonth / 10);
}