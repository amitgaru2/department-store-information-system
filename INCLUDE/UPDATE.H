// UPDATE ITEM MODULE BY AMIT GARU

struct up_item{
char name[27];
char id[5];
float quan,rate;
char day[3], month[3];
};

char update_temp[4]; 
char temp_name[27];


void update_item(){
start:
clrscr();
ofstream fout;
ifstream fin;
up_item in_obj, file_obj,temp_obj;
int event = 0;
int choice;
char choicestr[2];
cout<<endl<<endl<<"\t\t\t\tUPDATE ITEM !!!";
cout<<endl<<endl<<endl<<"\tEnter Item Id: ";
gets(in_obj.id);
fin.open("item.txt");
fin.seekg(0);
fin.read((char *)&file_obj, sizeof(file_obj));
while(fin)
{
	if(stricmp(in_obj.id,file_obj.id)==0)
	{
		event = 1;
		break;
	}
	fin.read((char *)&file_obj, sizeof(file_obj));
}
fin.close();
if(event==0)
{
	cout<<endl<<endl<<"\t\t\tItem Not Found !!!";
	cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!!";
	getch();
	goto start;
}
else if(event==1)
	{
		up:
		clrscr();
		cout<<endl<<"\t\t\t1. Update Name\n\t\t\t2. Update ID\n\t\t\t3. Update Rate\n\t\t\t4. Go Back"<<endl<<endl<<"\t\t\t";
		gets(choicestr);
		if(choicestr[0]<48 || choicestr[0]>57)
		{
			cout<<endl<<endl<<endl<<endl<<"\t\t\t\tInvalid Choice !!!";
			cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!! ";
			getch();
			goto up;
		}
		else if(strlen(choicestr)==0 || strlen(choicestr)>1)
		{
			cout<<endl<<endl<<endl<<endl<<"\t\t\t\tInvalid Input !!!";
			cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!! ";
			getch();
			goto up;
		}
		else
		{
			choice = choicestr[0] - 48;
			switch(choice)
			{
				case 1:
				up_name:
				clrscr();
				cout<<endl<<endl<<"\tEnter New Name to Item : "<<in_obj.id<<endl<<"\t";
				gets(temp_obj.name);
				if(strlen(temp_obj.name)==0||strlen(temp_obj.name)<6 || strlen(temp_obj.name)>26)
				{
					cout<<endl<<endl<<endl<<"\t\t\tInvalid Name Input";
					cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!!";
					getch();
					goto up_name;
				}	

				int count_pos=0;
				fout.open("item.txt",ios::out|ios::ate);
				fin.open("item.txt");
				fin.seekg(0);
				fin.read((char *)&file_obj,sizeof(file_obj));
				while(fin)
				{
					if(stricmp(in_obj.id, file_obj.id)==0)					//destn,source
					{
						strcpy(temp_name, file_obj.name);
						strcpy(file_obj.name,temp_obj.name);
						fout.seekp(count_pos*sizeof(file_obj));
						fout.write((char *)&file_obj,sizeof(file_obj));
						clrscr();
						cout<<endl<<endl<<"\t\t\tItem Name Updated !!!\n\n\t\t\tOld Name : "<<temp_name<<"\n\t\t\tNew Name : "<<temp_obj.name<<"\n\t\t\t Item ID : "<<file_obj.id;
						cout<<endl<<endl<<"\t\t\tPress 'm' to go Main Screen !!!";
						while(getch()!='m'){}
						break;
					}
				count_pos++;
				fin.read((char *)&file_obj, sizeof(file_obj));
				}
				fin.close();
				fout.close();
				//}
				break;

				case 2:
				up_id:
				clrscr();
				cout<<endl<<"\tEnter New Id to the Item : "<<in_obj.id<<endl<<"\t";
				gets(temp_obj.id);	
				if( strlen(temp_obj.id) != 4 )
				{
					cout<<endl<<endl<<"\t\t\tInvalid ID Input ( enter 4 characters ) !!!";
					cout<<endl<<endl<<"\t\t\tPress Any key to Continue !!!";
					getch();
					goto up_id;
				}
				
				else
				{
					event=0;
					fin.open("item.txt");
					fin.seekg(0);
					fin.read((char *)&file_obj, sizeof(file_obj));
					while(fin)
					{
						if(strcmp(temp_obj.id, file_obj.id) == 0)
						{
							event=1;
							break;
						}
						fin.read((char *)&file_obj, sizeof(file_obj));
					}
					fin.close();
					if(event==1)
					{
						cout<<endl<<endl<<"\t\tID already exist for the Item Name: "<<file_obj.name;
						cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!!";
						getch();
						goto up_id;
					}
					else
					{
						int count_pos=0;
						fout.open("item.txt",ios::out|ios::ate);
						fin.open("item.txt");
						fin.seekg(0);
						fin.read((char *)&file_obj,sizeof(file_obj));
						while(fin)
						{
							if(stricmp(in_obj.id, file_obj.id)==0)					
							{	
								strcpy(in_obj.id, file_obj.id);						//	in_obj.id stores old id , temp_obj.id stores new id
								strcpy(file_obj.id, temp_obj.id);
								fout.seekp(count_pos * sizeof(file_obj));
								fout.write((char *)&file_obj, sizeof(file_obj));
								clrscr();
								cout<<endl<<endl<<"\t\t\tItem ID Updated !!!"<<"\n\n\t\t\tItem Name : "<<file_obj.name<<"\n\t\t\t   Old ID : "<<in_obj.id<<"\n\t\t\t   New ID : "<<temp_obj.id;
								cout<<endl<<endl<<"\t\t\tPress 'm' to go Main Screen !!!";
								while(getch()!='m'){}
								break;
							}
						count_pos++;
						fin.read((char *)&file_obj, sizeof(file_obj));
						}
						fin.close();
						fout.close();
					}

					
				}	
				break;

				case 3:
				int i_temp, flag;
				up_rate:
				clrscr();
				cout<<endl<<"\tEnter New Rate to the Item : "<<in_obj.id<<endl<<"\t";
				gets(update_temp);
				i_temp=0;
				flag=0;
				while(update_temp[i_temp]!='\0')
				{
					if(update_temp[i_temp]<48 || update_temp[i_temp]>57)
					{
						flag=1;
						break;
					}
					i_temp++;
				}
				if(flag == 1 || strlen(update_temp)>4 || strlen(update_temp)<1)
				{
					cout<<endl<<endl<<"\t\t\tInvalid RATE Input !!!";
					cout<<endl<<endl<<"\t\t\tPress Any key to Continue !!!";
					getch();
					goto up_rate;
				}
				
				else
				{
					int j_temp=0;
					temp_obj.rate=0;
					int length=strlen(update_temp);
					for(i_temp=(length-1);i_temp>=0;i_temp--)
					{
						update_temp[i_temp]=update_temp[i_temp]-48;
						temp_obj.rate=temp_obj.rate+update_temp[i_temp]*pow(10,j_temp);
						j_temp++;
					}
					if(temp_obj.rate == 0)
					{
						cout<<endl<<endl<<"\t\t\tInvalid RATE Input !!!";
						cout<<endl<<endl<<"\t\t\tPress Any key to Continue !!!";
						getch();
						goto up_rate;
					}
					else
					{
						int count_pos=0;
						fout.open("item.txt",ios::out|ios::ate);
						fin.open("item.txt");
						fin.seekg(0);
						fin.read((char *)&file_obj, sizeof(file_obj));
						while(fin)
						{
							if(stricmp(in_obj.id, file_obj.id)==0)
							{
								in_obj.rate = file_obj.rate;
								file_obj.rate = temp_obj.rate;
								fout.seekp(count_pos * sizeof(file_obj));
								fout.write((char *)&file_obj, sizeof(file_obj));
								clrscr();
								cout<<endl<<"\t\t\tItem RATE Updated !!!"<<"\n\n\t\t\tItem Name : "<<file_obj.name<<"\n\t\t\t Old RATE : "<<in_obj.rate<<"\n\t\t\t New RATE : "<<temp_obj.rate;
								cout<<endl<<endl<<"\t\t\tPress 'm' to go Main Screen !!!";
								while(getch()!='m'){}
								break;
							}
							count_pos++;
							fin.read((char *)&file_obj, sizeof(file_obj));
						}
						fin.close();
						fout.close();
					}
				}
				break;

				case 4:
				break;
				
				default:
				cout<<endl<<endl<<"\t\t\tWrong Input !!!";
				cout<<endl<<endl<<"\t\t\tPress Any key to Input Again !!!";
				getch();
				goto up;
			}
		}
	}
	
fflush(stdout);
fflush(stdin);
}