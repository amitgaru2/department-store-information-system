//FOR MANAGER MODULE BY AMIT GARU

struct manager_item{
char name[27];
char id[5];
float quan,rate;
char day[3], month[3];
};

char password_array_Manager[16];
union REGS i,o;
int ma,mb; //ma = midpoint x, mb = midpoint y

void m_showmouseptr();
void manager_detect1();
int m_initmouse();
void m_hide_mouse();
void first();
//void pwd_change();
void enterpassword_Manager();
void mouse_set();
void graphics_init();
void ifinish();
void view_record();
void clear_record();
void removed_items();
void manager_title();
void daily_record();
void user_accounts();


void fmanager()
{
	graphics_init();
	manager_title();
	rectangle(108,203,230,221);
	outtextxy(ma-205,mb-30,"Items Finished");
	rectangle(263,203,368,221);
	outtextxy(ma-50,mb-30,"Daily Record");
	rectangle(403,203,517,221);
	outtextxy(ma+90,mb-30,"Removed Items");
	outtextxy(getmaxx()-80,getmaxy()-45,"Log Out");
	outtextxy(51,getmaxy()-45,"User Accounts");
	int status;
	status = m_initmouse();
	if( status == 0)
		cout<<"mouse not supported \n";
	else
	{
			m_showmouseptr();
			
			while (!kbhit () || kbhit() )
			{
			int x,y;
			i.x.ax = 3;
			int86 (0X33,&i,&o);
			if (o.x.bx == 1)
				{
				x = o.x.cx;
				y = o.x.dx;

				if(x>=110&&x<=228&&y>=205&&y<=219)  //Items Finished
				{
					rectangle(110,205,228,219);
					m_hide_mouse();
					closegraph();
					ifinish();
					break;
				}

				if(x>=265&&x<=366&&y>=205&&y<=219) //Daily Record
				{
					rectangle(265,205,366,219);
					m_hide_mouse();
					daily_record();
					break;
			 
				}
				if(x>=405&&x<=515&&y>=205&&y<=219) //Removed Items
				{
					rectangle(405,205,515,219);
					m_hide_mouse();
					closegraph();
					removed_items();
					break;
				}
				
				if(x>=558&&x<=612&&y>=432&&y<=442)
				{
					break;
						//cout<<"log out button pressed ";f
				}
				
				if(x>=49&&x<=154&&y>=432&&y<=441) 						 //User Accounts
				{
					closegraph();
					user_accounts();
					fflush(stdin);
					fflush(stdout);

					break;
				}

			//	printf("X- %d , Y - %d \n",x,y);
				}
			delay (150);											 // Otherwise due to quick computer response 100s of words will get print
			}
	}


fflush(stdin);
fflush(stdout);

}


void graphics_init()
{
int gd = DETECT, gm;
initgraph(&gd,&gm,"..\\bgi");
ma=getmaxx()/2;
mb=getmaxy()/2;
}
	

int m_initmouse()
{
	i.x.ax = 0;
	int86(0X33, &i, &o);
	return(o.x.ax);
}
void m_showmouseptr()
{
	i.x.ax = 1;
	int86(0X33, &i, &o);
}


void m_hide_mouse()
{
	i.x.ax = 2;
	int86(0X33, &i, &o);
}


void ifinish()													// item finished module
{
clrscr();
manager_item obj;
ifstream fin;
int count = 0, goDown = 0;
cout<<"\t\t\t\tFINISHED ITEMS !!!";
cout<<endl<<endl<<"\tItem ID\t\t\tItem Name";
fin.open("item.txt", ios::in);
fin.seekg(0);
fin.read((char *)&obj, sizeof(obj));
while(fin)
{
	if(obj.quan == 0)
	{
		if(count<=21)
		{
		cout<<endl<<"\t"<<setw(4)<<obj.id<<"\t\t"<<setw(27)<<obj.name;
		count++;
		}
		else
		{
			if(getch() == 's')
			{
				goDown = 25;
				gotoxy(1,goDown);
				cout<<endl<<"\t"<<setw(4)<<obj.id<<"\t\t"<<setw(27)<<obj.name;
				goDown++;
				count++;
			}
		}
	}
	fin.read((char *)&obj, sizeof(obj));
}
fin.close();
if(count==0)
{
	cout<<endl<<endl<<endl<<"\t\t\t\tNo Record Found !!!";
}
cout<<endl<<endl<<endl<<endl<<"\t\t\t    Press 'b' Key to Go Back !!! ";
while(getch()!='b'){};
fmanager();
}

void view_record()
{
manager_item obj;
char inputDay[3], inputMonth[3];
manager_item result_obj[50];
int arrayCount=0, i, event = 0;
long double gtotal= 0;
reInput:
clrscr();
cout<<endl<<endl<<"\t\t\t\tVIEW RECORD !!!";
cout<<endl<<endl<<endl<<endl<<endl<<"\t\t\t\tEnter day?"<<endl<<"\t\t\t\t    ";
gets(inputDay);
if(strlen(inputDay)!= 2)
{
	cout<<endl<<endl<<endl<<endl<<"\t\t\t\tInvalid Input !!!";
	cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!! ";
	getch();
	goto reInput;
}
else
{
	for(i=0; i<strlen(inputDay); i++)
	{
		if(inputDay[i]<48 || inputDay[i]>57)
		{
			cout<<endl<<endl<<endl<<endl<<"\t\t\t\tInvalid Input !!!";
			cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!! ";
			getch();
			goto reInput;
			break;
		}
	}
}
cout<<endl<<endl<<"\t\t\t\tEnter Month?"<<endl<<"\t\t\t\t    ";
gets(inputMonth);
if(strlen(inputMonth) != 2)
{
	cout<<endl<<endl<<endl<<endl<<"\t\t\t\tInvalid Input !!!";
	cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!!";
	getch();
	goto reInput;
}
else
{
	for(i=0; i<strlen(inputMonth); i++)
	{
		if(inputMonth[i]<48 || inputMonth[i]>57)
		{
			cout<<endl<<endl<<endl<<endl<<"\t\t\t\tInvalid Input !!!";
			cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!! ";
			getch();
			goto reInput;
			break;
		}
	}
}
ifstream fin;
fin.open("fbill.txt", ios::in);
fin.seekg(0);
fin.read((char *)&obj, sizeof(obj));
while(fin)
{
	if(strcmp(obj.day, inputDay) == 0 && strcmp(obj.month, inputMonth) == 0)
	{
		if(arrayCount == 0)								//for first condition satisfied
		{
			result_obj[0] = obj;
			arrayCount=1;
		}

		else
		{
			for(i=0;i<arrayCount; i++)
			{
				if(stricmp(obj.name, result_obj[i].name) == 0)						//adds the quantity if same name found
				{
					result_obj[i].quan = result_obj[i].quan + obj.quan;
					event =1;
					break;
				}
			}
			if(event == 0)
			{
				result_obj[arrayCount] = obj;
				arrayCount++;
			}
			else event = 0;
		}
	}

	fin.read((char *)&obj, sizeof(obj));
}
fin.close();
if(arrayCount == 0)
{
	cout<<endl<<endl<<endl<<"\t\t\t\tNo Record Found !!!";
	cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!! ";
	getch();
	goto reInput;
}
else
{
	clrscr();
	char ch;
	int go_down;
	display:
	clrscr();
	gtotal = 0;
	cout<<"ID\t\tName\t\t\t\tQuan\tRate\t\tTotal";
	for(i=0; i<arrayCount; i++)
	{
	if(i<24)
		{
			gtotal = gtotal + result_obj[i].quan * result_obj[i].rate;
			cout<<endl<<setw(4)<<result_obj[i].id<<"\t"<<setw(27)<<result_obj[i].name<<"\t\t"<<setw(4)<<result_obj[i].quan<<"\t"<<setw(4)<<result_obj[i].rate<<"\t\t"<<setw(5)<<result_obj[i].quan*result_obj[i].rate;
		}
		
		if(i>23)
		{
				go_down=25;
				ch = getch();
				if(ch =='s' || ch =='S')
				{
					gotoxy(1,go_down);
					gtotal = gtotal + result_obj[i].quan * result_obj[i].rate;
					cout<<endl<<setw(4)<<result_obj[i].id<<"\t"<<setw(27)<<result_obj[i].name<<"\t\t"<<setw(4)<<result_obj[i].quan<<"\t"<<setw(4)<<result_obj[i].rate<<"\t\t"<<setw(5)<<result_obj[i].quan*result_obj[i].rate;
					go_down++;
				}
				else if(ch=='w' || ch=='W')
				{
					goto display;
				}

		}
	}
cout<<"\n\n\t\tGrand Total\t\t\t\t\tRs."<<setw(10)<<gtotal;
delay(1500);
cout<<endl<<endl<<endl<<"\t\t\tPress 'b' To Go BACK !!! ";
ch=getch();
while(ch!='b')
{
	if(ch=='w')
		goto display;
	ch=getch();
}
fmanager();
}

}

void clear_record()
{
	manager_item obj;
	int flag = 0;
	int i;
	char inputDay[3], inputMonth[3];
	reInput:
	clrscr();
	cout<<endl<<endl<<"\t\t\t\tCLEAR RECORD !!!";
	cout<<endl<<endl<<endl<<endl<<endl<<"\t\t\t\tEnter day?"<<endl<<"\t\t\t\t    ";
	gets(inputDay);
	if(strlen(inputDay) != 2)
	{
		cout<<endl<<endl<<endl<<endl<<"\t\t\t\tInvalid Input !!!";
		cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!! ";
		getch();
		goto reInput;
	}
	else
	{
		for(i=0; i<strlen(inputDay); i++)
		{
			if(inputDay[i]<48 || inputDay[i]>57)
			{
				cout<<endl<<endl<<endl<<endl<<"\t\t\t\tInvalid Input !!!";
				cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!! ";
				getch();
				goto reInput;
				break;
			}
		}
	}
	cout<<endl<<endl<<"\t\t\t\tEnter Month?"<<endl<<"\t\t\t\t    ";
	gets(inputMonth);
	if(strlen(inputMonth) != 2)
	{
		cout<<endl<<endl<<endl<<endl<<"\t\t\t\tInvalid Input !!!";
		cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!! ";
		getch();
		goto reInput;
	}
	else
	{
		for(i=0; i<strlen(inputMonth); i++)
		{
			if(inputMonth[i]<48 || inputMonth[i]>57)
			{
				cout<<endl<<endl<<endl<<endl<<"\t\t\t\tInvalid Input !!!";
				cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!! ";
				getch();
				goto reInput;
				break;
			}
		}
	}
	
	//check if the record  is available or not in the file fbill.txt
	ifstream fin;
	fin.open("fbill.txt", ios::in);
	fin.seekg(0);
	fin.read((char *)&obj, sizeof(obj));
	while(fin)
	{
		if(strcmp(obj.day, inputDay) == 0 && strcmp(obj.month, inputMonth) == 0)
		{
			flag = 1;
			break;
		}
		fin.read((char *)&obj, sizeof(obj));
	}
	fin.close();
	if(flag == 0)
	{
		cout<<endl<<endl<<endl<<"\t\t\t\tNo Record Found !!!";
		cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!!";
		getch();
		goto reInput;
	}
	else
	{
		clrscr();
		fin.open("fbill.txt",ios::in);
		fin.seekg(0);
		ofstream fout;
		fout.open("temp.txt", ios::out);
		fin.read((char *)&obj, sizeof(obj));
		while(fin)
		{
			if(strcmp(obj.day, inputDay) == 0 && strcmp(obj.month, inputMonth) == 0)
			{}
			else
				fout.write((char *)&obj, sizeof(obj));
				
			fin.read((char *)&obj, sizeof(obj));
		}
		fout.close();
		fin.close();
		fout.open("fbill.txt", ios::trunc);
		fin.open("temp.txt");
		fin.seekg(0);
		fout.seekp(0);
		fin.read((char *)&obj, sizeof(obj));
		while(fin)
		{
			fout.write((char *)&obj, sizeof(obj));
			fin.read((char *)&obj, sizeof(obj));
		}
		fin.close();
		fout.open("temp.txt", ios::trunc);
		fout.close();
		cout<<endl<<endl<<endl<<endl<<endl<<"\t\t\t"<<inputDay<<"/"<<inputMonth<<" Record Cleared !!!";	
		cout<<endl<<endl<<endl<<"\t\t\tPress 'b' Key to Go Back !!! ";
		while(getch()!='b'){};
		fmanager();
	}
}

void removed_items()
{
char scrollch;
int count=0;
manager_item obj;
clrscr();
ifstream fin;
fin.open("removed.txt");
fin.seekg(0);
fin.read((char *)&obj, sizeof(obj));
while(fin)
{
	count++;
	break;
	//fin.read((char *)&obj, sizeof(obj));
}
fin.close();
if(count==0)
{
	cout<<endl<<endl<<endl<<endl<<endl<<"\t\t\t   No Items Found Removed !!!";
	cout<<endl<<endl<<endl<<endl<<"\t\t\tPress 'b' Key to Go Back !!! ";
	while(getch()!='b'){}
	fmanager();
}
		
else
{
	cout<<"Item Id\tRemoved Date\tRemoved Item Name\t\tRemoved Quantity"<<endl;
	count=0;
	fin.open("removed.txt");
	fin.seekg(0);
	fin.read((char *)&obj, sizeof(obj));
	while(fin)
	{
		count++;
		if(count>23)
		{
			scrollch=getch();
			if(scrollch=='s'||scrollch=='S')
				cout<<" "<<setw(4)<<obj.id<<"\t"<<setw(2)<<obj.month<<"/"<<setw(2)<<obj.day<<"\t"<<setw(27)<<obj.name<<"\t\t"<<setw(4)<<obj.quan<<endl;
		}
		else
			cout<<" "<<setw(4)<<obj.id<<"\t"<<setw(2)<<obj.month<<"/"<<setw(2)<<obj.day<<"\t"<<setw(27)<<obj.name<<"\t\t"<<setw(4)<<obj.quan<<endl;

		fin.read((char *)&obj, sizeof(obj));
	}
	delay(1000);
	cout<<endl<<endl<<"\t\tPress 'c' to Clear the Record or 'b' to go Back "<<endl<<"\t\t\t\t";
	char ch;
	getChar: ch=getch();
		if(ch == 'c')
		{
			ofstream fout;
			fout.open("removed.txt",ios::trunc);
			clrscr();
			cout<<endl<<endl<<endl<<endl<<endl<<"\t\t\t\tRECORD CLEARED!!!"<<endl<<endl<<"\t\t\t";
			cout<<endl<<endl<<endl<<endl<<"\t\t\tPress 'b' Key to Go Back !!! ";
			while(getch()!='b'){}
			fmanager();
		}
		else if(ch == 'b')
			fmanager();
		else
			goto getChar; 
	
}
	
}


void manager_title()
{
	cleardevice();
	delay(300);
	settextstyle(0,HORIZ_DIR,2);
	outtextxy(ma-100,mb-160,"FOR MANAGER");
	settextstyle(0,0,0);
}

void daily_record()
{
		manager_title();
		outtextxy(175,205,"View Record");
		outtextxy(345,205,"Clear Record");
		rectangle(167,199,267,217);
		rectangle(339,199,444,217);
		m_showmouseptr();
		while (!kbhit () || kbhit())
		{
			int x,y;
			i.x.ax = 3;
			int86 (0X33,&i,&o);
			if (o.x.bx == 1)
			{
				x = o.x.cx;
				y = o.x.dx;
				if(x>=170&&x<=264&&y>=201&&y<=215)
				{
					rectangle(170,201,264,215);
					m_hide_mouse();
					closegraph();
					view_record();
					break;
				}

				if(x>=342&&x<=441&&y>=201&&y<=215)
				{
					rectangle(342,201,441,215);
					m_hide_mouse();
					closegraph();
					clear_record(); 						//  clear_record();
					break;
				}
				
					// printf("X- %d , Y - %d \n",x,y);
			}
			delay (150);
		}
					
}


void user_accounts()
{
user_account:
struct staff_Manager
{
	char username[16];
	char password[16];
	char mgr_status;			// to determine if manager or not 1 for manager 0 for other staff
}user, temp_user;
char reentered_password[16];
char choicestr[2];
int choice;
re_choice:
clrscr();
cout<<endl<<endl<<endl<<"\t\t\t\t1.CREATE ACCOUNT\n\t\t\t\t2.UPDATE PASSWORD\n\t\t\t\t3.DEACTIVATE ACCOUNT\n\t\t\t\t4.LIST ACCOUNTS\n\t\t\t\t5.BACK\n\n\t\t\t\t";
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
	//add new user
	if(choice == 1)							
	{	
		//struct staff_Manager user, temp_user;
		start:
		clrscr();
		cout<<endl<<endl<<endl<<"\t\t      Enter Username : ";
		gets(user.username);
		if(strlen(user.username) < 6 || strlen(user.username) > 15)
		{

			cout<<endl<<endl<<"\t\t\tInvalid Username Length (6-15) !!!";
			cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!!";
			getch();
			goto start;
		}

		//check if the username already taken or not
		int found_flag=0;
		ifstream fin;
		fin.open("staff.txt", ios::in);
		fin.read((char *)&temp_user, sizeof(temp_user));
		while(fin)
		{
			if(stricmp(temp_user.username,user.username) == 0)
			{
				found_flag = 1;
				break;
			}
			
			fin.read((char *)&temp_user, sizeof(temp_user));
		}
		fin.close();
		
		//if found
		if(found_flag == 1)
		{
			cout<<endl<<endl<<endl<<"\t\t\t   Username Already Exist !!!";
			cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!!";
			getch();
			goto start;
		}

		//if not found ask for password
		cout<<endl<<"\t\t      Enter Password : ";
		enterpassword_Manager();
		strcpy(user.password, password_array_Manager);
		if(strlen(user.password) < 6 || strlen(user.password) > 15)
		{
			cout<<endl<<endl<<endl<<"\t\t\tInvalid Password Length (6-15) !!!";
			cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!!";
			getch();
			goto start;
		}

		cout<<endl<<endl<<"\t\t   Re-enter Password : ";
		enterpassword_Manager();
		strcpy(reentered_password, password_array_Manager);

		if(strcmp(user.password, reentered_password) != 0)
		{
			cout<<endl<<endl<<endl<<"\t\t\tPasswords Do Not Match !!!";
			cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!!";
			getch();
			goto start;

		}


		cout<<endl<<endl<<"\t\tManager Status (y/n) : ";
		cin>>user.mgr_status;
		if(user.mgr_status == 'y')
			user.mgr_status = 49;
		else if(user.mgr_status == 'n')
			user.mgr_status = 48;
		else
		{
			cout<<"\n\n\t\t\tInvalid Input (y/n) !!!";
			cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!!";
			getch();
			goto start;
		}
	   
	   	//write to the file
		ofstream fout;
		fout.open("staff.txt", ios::out|ios::app);
		fout.write((char *)&user, sizeof(user));
		fout.close();

	    //cout<<endl<<endl<<user.username<<endl<<user.password<<endl<<user.mgr_status;
		cout<<endl<<endl<<endl<<"\t\t\tAccount Created Successfully !!!";
		cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!!";
		getch();
		goto user_account;
	}
		


	//update password
	else if(choice == 2)		
	{
		start2:
		clrscr();
		cout<<endl<<endl<<endl<<"\t\t    Enter Username : ";
		gets(user.username);
		if(strlen(user.username) < 6 || strlen(user.username) > 15)
		{

			cout<<endl<<endl<<endl<<"\t\t\tInvalid Username Length (6-15) !!!";
			cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!!";
			getch();
			goto start2;
		}


		//check if the username is on the file or not
		int found_flag=0;
		ifstream fin;
		fin.open("staff.txt", ios::in);
		fin.read((char *)&temp_user, sizeof(temp_user));
		while(fin)
		{
			if(stricmp(temp_user.username,user.username) == 0)
			{
				found_flag = 1;
				break;
			}
			
			fin.read((char *)&temp_user, sizeof(temp_user));
		}
		fin.close();

		// if found then update password
		if(found_flag == 1)
		{
			cout<<endl<<"\t\tEnter New Password : ";
			enterpassword_Manager();
			strcpy(user.password, password_array_Manager);
			if(strlen(user.password) < 6 || strlen(user.password) > 15)
			{
				cout<<endl<<endl<<endl<<"\t\t\tInvalid Password Length (6-15) !!!";
				cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!!";
				getch();
				goto start2;
			}

			cout<<endl<<endl<<"\t\t Re-enter Password : ";
			enterpassword_Manager();
			strcpy(reentered_password, password_array_Manager);

			if(strcmp(user.password, reentered_password) != 0)
			{
				cout<<endl<<endl<<endl<<"\t\t\tPasswords Do Not Match !!!";
				cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!!";
				getch();
				goto start2;
			}

			//update password
			ofstream fout;
			fout.open("temp.txt", ios::out);
			ifstream fin;
			fin.open("staff.txt",ios::in);
			fin.read((char *)&temp_user, sizeof(temp_user));
			while(fin)
			{
				if(stricmp(user.username, temp_user.username) == 0)
				{
					strcpy(temp_user.password, user.password);
				}
				fout.write((char *)&temp_user, sizeof(user));
				fin.read((char *)&temp_user, sizeof(temp_user));
			}
			fin.close();
			fout.close();

			//copy the updated staff password list to staff.txt
			fin.open("temp.txt", ios::in);
			fout.open("staff.txt", ios::out);
			fin.read((char *)&user, sizeof(user));
			while(fin)
			{	
				fout.write((char *)&user, sizeof(user));
				fin.read((char *)&user, sizeof(user));
			}
			fout.close();
			fin.close();

			cout<<endl<<endl<<endl<<endl<<endl<<"\t\t\t   Password Updated !!!";
			cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!!";
			getch();
		}

		// else goto start2
		else
		{
			cout<<endl<<endl<<endl<<"\t\t\t   Username Not Found !!!";
			cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!!";
			getch();
			goto start2;
		}

		goto user_account;
	}

	//remove user
	else if(choice == 3)		
	{
		start3:
		clrscr();
		char mgr_status_check = '0';
		cout<<endl<<endl<<endl<<"\t\t    Enter Username : ";
		gets(user.username);
		int found_flag=0;
		ifstream fin;
		fin.open("staff.txt", ios::in);
		fin.read((char *)&temp_user, sizeof(temp_user));
		while(fin)
		{
			if(stricmp(temp_user.username,user.username) == 0)
			{
				found_flag = 1;
				break;
			}
			
			fin.read((char *)&temp_user, sizeof(temp_user));
		}
		fin.close();

		if(found_flag == 1)
		{

			//check if only one manager exist
			ifstream fin;
			fin.open("staff.txt", ios::in);
			fin.read((char *)&temp_user, sizeof(temp_user));
			while(fin)
			{
				if(stricmp(temp_user.username,user.username) == 0)
				{
					if(temp_user.mgr_status == '1') mgr_status_check = '1';
					break;
				}

			fin.read((char *)&temp_user, sizeof(temp_user));
			}
			fin.close();
			int count_manager = 0;
			if(mgr_status_check == '1')
			{
			     //	int count_manager = 0;
				ifstream fin;
				fin.open("staff.txt", ios::in);
				fin.read((char *)&temp_user, sizeof(temp_user));
				while(fin)
				{
					if(temp_user.mgr_status == '1')
						count_manager++;

					fin.read((char *)&temp_user, sizeof(temp_user));
				}
				fin.close();
			   if(count_manager == 1)
				{
					cout<<endl<<endl<<endl<<endl<<"\t\t\tAccount Deactivate Unsuccessful !!!\n\n\t\t\t     Only 1 Manager Left !!!";
					cout<<endl<<endl<<endl<<"\t\t\tPress Any Key to Continue !!!";
					getch();
					goto start3;
				}
				else
				{
					goto remove_account;
				}
			}
			else
			{
			//if more than 1 manager exist
				remove_account:
				ofstream fout;
				fout.open("temp.txt", ios::out);
				ifstream fin;
				fin.open("staff.txt",ios::in);
				fin.read((char *)&temp_user, sizeof(temp_user));
				while(fin)
				{
					if(stricmp(user.username, temp_user.username) == 0){}
					else fout.write((char *)&temp_user, sizeof(user));
					fin.read((char *)&temp_user, sizeof(temp_user));
				}	
				fin.close();
				fout.close();

					//copy the updated staff password list to staff.txt
				fin.open("temp.txt", ios::in);
				fout.open("staff.txt", ios::out);
				fin.read((char *)&user, sizeof(user));
				while(fin)
				{	
					fout.write((char *)&user, sizeof(user));
					fin.read((char *)&user, sizeof(user));
				}
				fout.close();
				fin.close();

				cout<<endl<<endl<<endl<<endl<<endl<<"\t\t\t   Account Deactivated !!!";
				cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!!";
				getch();
			}

		}

		else
		{
			cout<<endl<<endl<<endl<<"\t\t\t   Username Not Found !!!";
			cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!!";
			getch();
			goto start3;
		}

		goto user_account;

	}
		

	else if(choice == 4)					//list accounts select
	{
		int i, no_of_users;						//for looping and for counting users
		char ch;
		int go_down;
		struct staff_Manager found_users[15];
	       //	found_users[0]=NULL;
		ifstream fin;
		fin.open("staff.txt",ios::in);
		i = 0;
		//put  all the found users in array for scrollable display
		fin.read((char *)&user, sizeof(user));
		while(fin)
		{
			found_users[i] = user;
			i++;
			fin.read((char *)&user, sizeof(user));
		}
		fin.close();
		no_of_users = i;
		display_users:
		clrscr();
		//display the found users
		cout<<"\tUSERNAME\t\t\tMANAGER_STATUS"<<endl;
		for(i=0;i<no_of_users;i++)
		{
			if(i<24)
			{
				cout<<"\t"<<setw(15)<<found_users[i].username<<"\t\t\t\t"<<setw(1)<<found_users[i].mgr_status<<endl;
			}
			else
			{
				go_down=25;
				ch=getch();
				if(ch=='s' || ch=='S')
				{
					gotoxy(1,go_down);
					cout<<"\t"<<setw(15)<<found_users[i].username<<"\t\t\t\t"<<setw(1)<<found_users[i].mgr_status<<endl;
					go_down++;
				}
				else if(ch=='w' || ch=='W')
				{
					goto display_users;
				}
				
			}

		}
		cout<<endl<<endl<<"\t\t\tPress Any Key to Continue !!!";
		ch=getch();
		if(ch=='w') goto display_users;
		goto user_account;
		
	}

	else if(choice == 5)
	{

		fflush(stdout);
		fflush(stdin);
		fmanager();
	}

	else
		goto re_choice;
}
}


void enterpassword_Manager()
{
char c;
int i = 0;
c = getch();
while(c!= '\r')
{
	if(c != '\b')
	{
		cout<<"*";
		password_array_Manager[i] = c;
		i++;

	}
	else
	{
		cout<<"\b \b";
		password_array_Manager[i-1] = '\0';
		i--;
	}
	c = getch();


}
password_array_Manager[i] = '\0';

}