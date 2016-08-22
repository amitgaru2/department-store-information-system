//calculate bill model by Amit Garu

struct cbill_item
{
char name[27];
char id[5];
float quan, rate;
char day[3], month[3];
}bll;      										 //bll object for holding bill info  f for file item.txt

cbill_item fbill_array[50];						//for storing bill items to display bill easily at last
int midpoint_x, midpoint_y;
int count=0,j,k; 							  //count = no of items added
int initial_end;  							// it represents the end of fbill file before appending data to it. used for printing bill
int array_count=0;
char quan_temp_cbill[6];					//get quantity from customer item bought list
char customer_name[26];
char username[16];

union REGS input,output;        			//for mouse pointer initialisation

void get_customername();
void set1();
int set2();
void set3();
void title();
void set();         		     //sets first value
void set_2();					// redo, bill, add screen
void bill();					//displays bill
void redo();					//do not save previous record
void mouse_set2();
void display_bill();
int initmouse();
void showmouseptr();
void detect();
void hide_mouse();
void cur_date();
void reduce_quan();
void display_array();
void combine_sameid();
void write_fbill();
void printbill();
int getbill_next_no();

void cbill(char passed_username[16])
{
strcpy(username, passed_username);
count=0;
array_count=0;
int gd=DETECT, gm;
initgraph(&gd,&gm,"..\\BGI");
midpoint_x=getmaxx()/2;
midpoint_y=getmaxy()/2;
//input customer name for outputing the name in the bill
clrscr();
title();
outtextxy(midpoint_x-80,midpoint_y-100, "Enter Customer Name");
gotoxy(33,12);
gets(customer_name);
//
set();
mouse_set2();

fflush(stdin);
fflush(stdout);

}


void set()
{
int temp;
set1();						//read
temp = set2();					//check
if(temp==1)
	set3();					//write
else
	set();
}

void set1(){
clrscr();
title();
cout<<"\n\n\tItem #"<<count+1; 	//shows the  item number of entering data
outtextxy(midpoint_x-80,midpoint_y-100,"Enter Item Id ");
gotoxy(33,11);
gets(bll.id);
outtextxy(midpoint_x-80,midpoint_y-50,"Enter Quantity ");
gotoxy(33,14);
gets(quan_temp_cbill);
}

int set2(){
int temp=0; 							//for counting to check the item name or id
cbill_item obj;
ifstream fin;
fin.open("item.txt", ios::in);
fin.seekg(0);
fin.read((char *)&obj, sizeof(bll));		//check item name,quantity if available in the item list
while(fin){
	if(stricmp(obj.id, bll.id)==0)
	{
		temp=1;
		break;
	}
	fin.read((char *)&obj,sizeof(bll));
}

fin.close();
	if(temp==0)
	{
		outtextxy(midpoint_x-120,midpoint_y+40,"Item id invalid or Item not available ");
		outtextxy(midpoint_x-80,midpoint_y+65,"Press any key to continue!!! ");
		getch();
		return 0;
	}
   else
	{
		int event=0;
		int i_temp=0;
		while(quan_temp_cbill[i_temp]!='\0')
		{
			if(quan_temp_cbill[i_temp]<48 || quan_temp_cbill[i_temp]>57)
			{
				event=1;
				break;
			}
			i_temp++;
		}
		if(event==1 || strlen(quan_temp_cbill)>5 || strlen(quan_temp_cbill)<1)
		{
			outtextxy(midpoint_x-100,midpoint_y+40,"Invalid Quantity Input !!!");
			outtextxy(midpoint_x-100,midpoint_y+65,"Press any key to continue!!! ");
			getch();
			return 0;
		}
		else
		{
			int j_temp=0;
			bll.quan=0;
			int quan_length=strlen(quan_temp_cbill);
			for(i_temp=quan_length-1;i_temp>=0;i_temp--)
			{
				quan_temp_cbill[i_temp]=quan_temp_cbill[i_temp]-48;
				bll.quan=bll.quan+quan_temp_cbill[i_temp]*pow(10,j_temp);
				j_temp++;
			}
			if(bll.quan<=0)
			{
				outtextxy(midpoint_x-100,midpoint_y+40,"Invalid Quantity Input !!!");
				outtextxy(midpoint_x-100,midpoint_y+65,"Press any key to continue!!! ");
				getch();
				return 0;
			}
			else if(obj.quan<bll.quan)
			{
				outtextxy(midpoint_x-100,midpoint_y+40,"Quantity not sufficient in store.");
				outtextxy(midpoint_x-100,midpoint_y+65,"Press any key to continue!!! ");
				getch();
				return 0;
			}
			else
			{
				return 1;
			}
		}
	}
}

void set3()
{
cur_date();
title();
count++;
gotoxy(34,11);
if(count==1)cout<<"1 item added!!!";
else cout<<count<<" items added!!!";
rectangle(midpoint_x-40,midpoint_y,midpoint_x,midpoint_y+20);
outtextxy(midpoint_x-35,midpoint_y+10,"BILL");
rectangle(midpoint_x-180,midpoint_y,midpoint_x-140,midpoint_y+20);
outtextxy(midpoint_x-175,midpoint_y+10,"UNDO");
rectangle(midpoint_x+100,midpoint_y,midpoint_x+140,midpoint_y+20);
outtextxy(midpoint_x+105,midpoint_y+10,"ADD");
}

void mouse_set2()
{
int status;
status = initmouse();
if( status == 0)
	printf("mouse not supported \n");
else
{
	showmouseptr();
	detect();
	hide_mouse();
}
}

int initmouse()
{
input.x.ax = 0;
int86(0X33, &input, &output);
return(output.x.ax);
}

void showmouseptr()
{
input.x.ax = 1;
int86(0X33, &input, &output);
}

void detect()
{
	 while (!kbhit ()|| kbhit () )
	{
		int x,y;
		input.x.ax = 3;
		int86 (0X33,&input,&output);
		if (output.x.bx == 1)
		{
			x = output.x.cx;
			y = output.x.dx;

			if(x>=139&&x<=179&&y>=239&&y<=259)  //UNDO
			{
			rectangle(midpoint_x-178,midpoint_y+2,midpoint_x-142,midpoint_y+18);
			delay(200);
			count--;
			hide_mouse();
			set();
			showmouseptr();
			}

			if(x>=279&&x<=319&&y>=239&&y<=259) //BILL
			{
			rectangle(midpoint_x-38,midpoint_y+2,midpoint_x-2,midpoint_y+18);
			delay(200);
			reduce_quan();
			combine_sameid();
			write_fbill();
			display_bill();
			break;
			//hide_mouse();
			}

			if(x>=419&&x<=458&&y>=239&&y<=259) //ADD
			{
			rectangle(midpoint_x+102,midpoint_y+2,midpoint_x+138,midpoint_y+18);
			delay(200);
			hide_mouse();
			reduce_quan();
			set();
			showmouseptr();
			}

		       //printf("X- %d , Y - %d \n",x,y);
		}
		delay (150);												 // Otherwise due to quick computer response 100s of words will get print
	}
}

void hide_mouse()
{
	input.x.ax = 2;
	int86(0X33, &input, &output);
}

void title()
{
cleardevice();
settextstyle(0,HORIZ_DIR,2);
outtextxy(midpoint_x-100,midpoint_y-160,"CALCULATE BILL");
settextstyle(0,0,0);
}

void reduce_quan()
{
k=0;
cbill_item obj; 												 //object for interacting with file item.txt
ofstream fout;
ifstream fin;
fin.open("item.txt",ios::in);									 //k = current position of file pointer
fin.seekg(0);
fin.read((char *)&obj,sizeof(bll));
while(fin)
{
	if((stricmp(obj.id,bll.id))==0)
	{
		strcpy(bll.name, obj.name);
		bll.rate = obj.rate;
		obj.quan = obj.quan - bll.quan;
		fout.open("item.txt", ios::out|ios::ate|ios::binary);
		fout.seekp(k * sizeof(bll));
		fout.write((char *)&obj,sizeof(bll));
		fout.close();
		fbill_array[array_count]=bll;				//place the item bought in the array for easier display
		array_count++;
		break;
	}
	k++;
	fin.read((char *)&obj, sizeof(bll));
}
fin.close();
}

void combine_sameid()				//combine to same item and save the total quantity
{
int temp_j;
	for(int i=0;i<array_count-1;i++)
	{
		for(int j=i+1;j<array_count;j++)
		{
			if(stricmp(fbill_array[i].id,fbill_array[j].id)==0)
			{
				fbill_array[i].quan = fbill_array[i].quan + fbill_array[j].quan;
				count--;
				temp_j=j;
				while(temp_j!=array_count-1)
				{
					fbill_array[temp_j]=fbill_array[temp_j+1];
					temp_j++;
				}
				j--;
				array_count--;
			}
		}
	}
}


void write_fbill()
{
ofstream fout;
fout.open("fbill.txt", ios::out|ios::app);
fout.seekp(0,ios::end);
initial_end=fout.tellp();
for(int i=0;i<array_count;i++)
	fout.write((char *)&fbill_array[i],sizeof(bll));
fout.close();
}


void display_bill()
{
	closegraph();
	display_bill_start:
	char ch;
	int go_down;
	clrscr();
	double gtotal=0;
	int lastbillno;
	lastbillno = getbill_next_no();
	cout<<"Customer Name : "<<setw(25)<<setiosflags(ios::left)<<customer_name<<resetiosflags(ios::left)<<"\t\t\tBill No : "<<lastbillno<<endl<<endl;
	cout<<"ID\t\tName\t\t\t\tQuan\tRate\t\tTotal";
	for(int i=0;i<array_count;i++)
	{
		if(i<=21)
		{
			gtotal = gtotal + fbill_array[i].quan * fbill_array[i].rate;
			cout<<endl<<setw(4)<<fbill_array[i].id<<"\t"<<setw(27)<<fbill_array[i].name<<"\t\t"<<setw(4)<<fbill_array[i].quan<<"\t"<<setw(4)<<fbill_array[i].rate<<"\t\t"<<setw(5)<<fbill_array[i].quan*fbill_array[i].rate;
		}
		else
		{
			go_down=25;
			ch=getch();
			if(ch == 's' || ch == 'S')
			{
				gotoxy(1,go_down);
				gtotal = gtotal + fbill_array[i].quan * fbill_array[i].rate;
				cout<<endl<<setw(4)<<fbill_array[i].id<<"\t"<<setw(27)<<fbill_array[i].name<<"\t\t"<<setw(4)<<fbill_array[i].quan<<"\t"<<setw(4)<<fbill_array[i].rate<<"\t\t"<<setw(5)<<fbill_array[i].quan*fbill_array[i].rate;
				go_down++;
			}
			else if(ch=='w' || ch=='W')
			{
				goto display_bill_start;
			}
		}

	}
cout<<"\n\n\t\tGRAND TOTAL\t\t\t\t\tRs."<<setw(10)<<gtotal;
cout<<"\n\nTotal Items : "<<count<<"\t\t\t\t\tVerified By : "<<setw(15)<<setiosflags(ios::left)<<username<<resetiosflags(ios::left);
delay(1500);
printbill();					//save bill in C:/BILLS/billno.txt

cout<<endl<<endl<<endl<<endl<<"\t\t\tPress 'm' to go Main Screen !!! ";
ch=getch();
while(ch!='m')
{
	if(ch=='w') goto display_bill_start;
	ch=getch();
}

}


void cur_date()
{
int iday, imonth;
struct date d;
getdate(&d);
iday = d.da_day;
imonth = d.da_mon;
bll.day[1] = 48 + iday % 10;
bll.day[0] = 48 + (iday / 10);
bll.month[1] = 48 +(imonth % 10);
bll.month[0] = 48 + (imonth / 10);
}

void printbill()
{
	//writing the bill to the file

	int iday, imonth;
	struct date d;
	getdate(&d);
	iday = d.da_day;
	imonth = d.da_mon;
	char day[3], month[3], folder_name[8];
	day[0] = 48 + (iday / 10);
	day[1] = 48 + iday % 10;	
	day[2] = '\0';
	month[0] = 48 + (imonth / 10);
	month[1] = 48 +(imonth % 10);
	month[2] = '\0';
	folder_name[0] = '\0';
	strcat(folder_name, month); strcat(folder_name,"_"); strcat(folder_name, day);

	char lastbillno[4] = "1";
	int nolastbill;
	int i1, temp_nolastbill = 1;
	char filename[35] = "C:\\BILLS\\";
	strcat(filename, folder_name); strcat(filename, "\\"); strcat(filename, lastbillno); strcat(filename, ".txt"); 		//concatenate to lacate the file in the disk
	ifstream fin;
	fin.open(filename, ios::in);
	while(fin)
	{
		fin.close();
		i1 = 0;
		nolastbill = 0;

		while(lastbillno[i1]!='\0')				//		convert string to integer to find last bill no
		{
		  nolastbill = nolastbill*10 + lastbillno[i1]-48;
		  i1++;
		}
		nolastbill++;									// increment filename index by 1 for searching successor file
		temp_nolastbill = nolastbill;
		i1=0;
		while(nolastbill != 0)				// convert integer to string after incrementation
		{
		  lastbillno[i1] = 48 + nolastbill%10;
		  nolastbill=nolastbill/10;
		  i1++;
		}

		strrev(lastbillno); 			//the string obtained from above is in reverse than desired

		filename[15] = '\0';
		strcat(filename, lastbillno); strcat(filename, ".txt");
		fin.open(filename, ios::in);
	}
	fin.close();
	//cout<<endl<<lastbillno;

	double gtotal=0;
	ofstream fout;
	fout.open(filename, ios::out);
	if(!fout)								//if the folder not found with today's date
	{
		char create_dir[25]="md C:\\BILLS\\";
		strcat(create_dir, folder_name);
		//strcat(create_dir, ">nul 2>&1");
		system(create_dir);
		fout.close();
		fout.open(filename, ios::out);
	}
	fout<<"Customer Name : "<<setw(25)<<setiosflags(ios::left)<<customer_name<<resetiosflags(ios::left)<<"\t\t\tBill No : "<<temp_nolastbill<<endl<<endl;
	fout<<"ID\t\tName\t\t\t\tQuan\tRate\t\tTotal";
	for(int i=0;i<array_count;i++)
	{
	gtotal = gtotal + fbill_array[i].quan * fbill_array[i].rate;
	fout<<endl<<setw(4)<<fbill_array[i].id<<"\t"<<setw(27)<<fbill_array[i].name<<"\t\t"<<setw(4)<<fbill_array[i].quan<<"\t"<<setw(4)<<fbill_array[i].rate<<"\t\t"<<setw(5)<<fbill_array[i].quan*fbill_array[i].rate;
	}
	fout<<"\n\n\t\tGRAND TOTAL\t\t\t\t\tRs."<<setw(10)<<gtotal;
	fout<<"\n\nTotal Items : "<<count<<"\t\t\t\t\tVerified By : "<<setw(15)<<setiosflags(ios::left)<<username<<resetiosflags(ios::left);
	fout.close();


}


int getbill_next_no()
{


//	fflush(stdin);
//	fflush(stdout);
	int iday, imonth;
	struct date d;
	getdate(&d);
	iday = d.da_day;
	imonth = d.da_mon;
	char day[3], month[3], folder_name[8];
	day[0] = 48 + (iday / 10);
	day[1] = 48 + iday % 10;	
	day[2] = '\0';
	month[0] = 48 + (imonth / 10);
	month[1] = 48 +(imonth % 10);
	month[2] = '\0';
	folder_name[0] = '\0';
	strcat(folder_name, month); strcat(folder_name,"_"); strcat(folder_name, day);
	char lastbillno[4] = "1";
	int nolastbill;
	int i1, temp_nolastbill = 1;
	char filename[35] = "C:/BILLS/";
	strcat(filename, folder_name); strcat(filename, "/"); strcat(filename, lastbillno); strcat(filename, ".txt"); 		//concatenate to lacate the file in the disk
	ifstream fin;
	fin.open(filename, ios::in);
	while(fin)
	{
		fin.close();
		i1 = 0;
		nolastbill = 0;

		while(lastbillno[i1]!='\0')				//		convert string to integer to find last bill no
		{
		  nolastbill = nolastbill*10 + lastbillno[i1]-48;
		  i1++;
		}
		nolastbill++;									// increment filename index by 1 for searching successor file
		temp_nolastbill = nolastbill;
		i1=0;
		while(nolastbill != 0)				// convert integer to string after incrementation
		{
		  lastbillno[i1] = 48 + nolastbill%10;
		  nolastbill=nolastbill/10;
		  i1++;
		}

		strrev(lastbillno); 			//the string obtained from above is in reverse than desired

		filename[15] = '\0';
		strcat(filename, lastbillno); strcat(filename, ".txt");
		fin.open(filename, ios::in);
	}
	fin.close();
	return temp_nolastbill;
}
