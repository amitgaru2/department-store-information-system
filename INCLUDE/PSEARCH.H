//SEARCH ITEM MODULE BY AMIT GARU

struct search_item
{
char name[27];
char id[5];
float quan,rate;
char day[3], month[3];
};

void search()
{
clrscr();
search_item found_array[110];
search_item file_obj, in_obj, temp_obj;
ifstream fin;
char ch;
int array_size=0;
int go_down;
int diffn_name, diffn_id;
gotoxy(36,10);
cout<<"SEARCH !!!";
cout<<endl<<endl<<"\t\t\t---------------------------------";
cout<<endl<<endl<<"\t\t\t---------------------------------";
gotoxy(26,13);
gets(in_obj.name);
int length=strlen(in_obj.name);
fin.open("item.txt", ios::in);
fin.seekg(0);
fin.read((char *)&file_obj, sizeof(file_obj));
while(fin)
{
	diffn_name = stricmp(file_obj.name,in_obj.name);
	diffn_id = stricmp(file_obj.id, in_obj.name);
	if(diffn_name == int(file_obj.name[length]) || (diffn_name+32) == int(file_obj.name[length]) || diffn_id==int(file_obj.id[length]) || (diffn_id+32)==int(file_obj.id[length]) )
	{
		found_array[array_size]=file_obj;
		array_size++;
	}
	fin.read((char *)&file_obj, sizeof(file_obj));
}
fin.close();
clrscr();
if(array_size==0)
{
	cout<<endl<<endl<<endl<<"\t\t\t\tNo Items Found !!!";
	cout<<endl<<endl<<"\t\t\tPress Any key to Search Again !!! ";
	getch();
	search();
}
else
{
	found_items:
	clrscr();
	cout<<setiosflags(ios::left)<<setw(27)<<"ITEM NAMES FOUND"<<setiosflags(ios::right)<<"\tDATE-ADDED\tID\tQUANTITY-LEFT\tRATE";
	for(int i=0;i<array_size;i++)
	{
		if(i<24)
		{
			cout<<endl<<setiosflags(ios::left)<<setw(27)<<found_array[i].name;
			cout<<setiosflags(ios::right)<<"\t"<<found_array[i].day<<"/"<<found_array[i].month<<"\t\t"<<setw(4)<<found_array[i].id<<"\t "<<setiosflags(ios::left)<<setw(4)<<found_array[i].quan<<"\t\t"<<setw(4)<<found_array[i].rate;
		}
		if(i>23)
		{
			go_down=25;
			ch=getch();
			if(ch=='s' || ch=='S')
			{
				gotoxy(1,go_down);
				cout<<endl<<setiosflags(ios::left)<<setw(27)<<found_array[i].name;
				cout<<setiosflags(ios::right)<<"\t"<<found_array[i].day<<"/"<<found_array[i].month<<"\t\t"<<setw(4)<<found_array[i].id<<"\t "<<setiosflags(ios::left)<<setw(4)<<found_array[i].quan<<"\t\t"<<setw(4)<<found_array[i].rate;
				go_down++;
			}
			else if(ch=='w' || ch=='W')
			{
				goto found_items;
			}
		}

	}
}

delay(1000);
cout<<endl<<endl<<endl<<"\t\t\tPress 'm' to go Main Screen !!! ";
ch=getch();
while(ch!='m')
{
	if(ch=='w') goto found_items;
	ch=getch();
}

fflush(stdout);
fflush(stdin);
}