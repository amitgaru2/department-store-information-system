// DEPARTMENT INFORMATION SYSTEM
// DESIGNED AND DEVELOPED BY AMIT GARU AND HIS GROUP,
// KHWOPA ENGINEERING COLLEGE '070 COMPUTER
#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<time.h>
#include<graphics.h>
#include<fstream.h>
#include<string.h>
#include<process.h>
#include<math.h>
#include<iomanip.h>
#include<cbill.h>
#include<update.h>
#include<remove.h>
#include<psearch.h>
#include<manager.h>
#include<additem.h>


int login();
int menu_page();
int initmouse1();
void showmouseptr1();
int detect1();
void hide_mouse1();
void enterpassword();

int m,n;				//dividing the main menu screen in rows and columns
union REGS in,out;
char password_array[16];
char pass_username[16];				//for passing to cbill module to determine the one who verified bill

struct staff
{
	char username[16];
	char password[16];
	char mgr_status;			// to determine if manager or not 1 for manager 0 for other staff


};


void main()
{
clrscr();
int midx,midy;
int gd=DETECT, gm;
initgraph(&gd,&gm,"C:\\TC\\BGI");
midx = getmaxx()/2;
midy = getmaxy()/2;
outtextxy((getmaxx()/2)-160,getmaxy()/2,"DEPARTMENT STORE INFORMATION SYSTEM");
outtextxy(midx-125,midy+70,"Press Any key to Continue !!!");
getch();
cleardevice();
closegraph();
delay(350);

//verifying staff access or manager access

cout<<endl<<endl<<"\t\t\t\t    LOGIN !!!";
int stemp=0;
stemp=login();
while(stemp == 0)							//1 for other staff 2 for manager
{
	clrscr();
	cout<<endl<<endl<<"\t\t\t\t    LOGIN !!!";
	cout<<endl<<endl<<"\t\t\tWrong Username or Password !!! ";
	stemp=login();
}

if(stemp == 2)
{
	clrscr();
	fmanager();
	main();
}
else
{
	int rtemp=menu_page();				//rtemp = return temp temp var for storing returned values
	while (rtemp==1)
	{
		rtemp = menu_page();					//displaying all the menu
	}

	if (rtemp == 2)
	{
		main();
	}
}

}

int login()
{
int flag = 0;
struct staff user_login, user_registered;
cout<<endl<<endl<<endl<<endl<<"\t\t      Enter Username : ";
gets(user_login.username);

cout<<endl<<"\t\t      Enter Password : ";
enterpassword();
strcpy(user_login.password, password_array);

ifstream fin;
fin.open("staff.txt",ios::in);
fin.read((char *)&user_registered, sizeof(user_registered));
while(fin)
{
	if(stricmp(user_registered.username, user_login.username)==0 && strcmp(user_registered.password, user_login.password)==0)
	{
		fin.close();
		if(user_registered.mgr_status == 49)
		flag = 2;
		else flag = 1;
		break;
	}
	fin.read((char *)&user_registered, sizeof(user_registered));
}
fin.close();

if(flag == 1) { strcpy(pass_username, user_registered.username); return 1;}
else if (flag == 2) return 2;
else return 0;

}




int menu_page()
{

	int status, gd = DETECT, gm;
	initgraph(&gd,&gm,"C:\\TC\\BGI");
	m = getmaxx()/5;  //divide in 5 columns
	n = getmaxy()/13;  //divide in 13 rows
	outtextxy(m,5*n,"1.Calculate the Bill");
	outtextxy(m,6*n,"2.Add New Item");
	outtextxy(m,7*n,"3.Update Item");
	outtextxy(m,8*n,"4.Remove Item");
	outtextxy(m,9*n,"5.Search Item");							//search if the items exist or not if exist how much by quantity
	//outtextxy(m,10*n,"6.For Manager");
	rectangle(4*m,12*n,4*m+45,12*n+15);
	outtextxy(1*m, 12*n+5, "Log Out");
	outtextxy(4*m+5,12*n+5,"Exit");


	status = initmouse1();

	if( status == 0)
		printf("mouse not supported \n");
	else
	{
		showmouseptr1();
		int rtemp=detect1();
		if(rtemp==2) return 2;
		else return 1;
		hide_mouse1();
	}
	clrscr();
	closegraph();
	return 0;
}

int initmouse1()
{
	in.x.ax = 0;
	int86(0X33, &in, &out);
	return(out.x.ax);
}

void showmouseptr1()
{
	in.x.ax = 1;
	int86(0X33, &in, &out);
}

int detect1()
{
	 while (!kbhit ()||kbhit() )
	{
		int x,y;
		in.x.ax = 3;
		int86 (0X33,&in,&out);
		if (out.x.bx == 1)
		{
			x = out.x.cx;
			y = out.x.dx;
			if((x>=m&&x<=m+160)&&(y>=(5*n)&&y<=(6*n-n/2)))
			{
				delay(150);
			    cbill(pass_username);
				return 1;
			}
			if((x>=m&&x<=m+110)&&(y>=(6*n)&&y<=(7*n-n/2)))
			{
				closegraph();
				additem();
				return 1;
			}
			//printf("2nd selected");
			if(x>=m&&x<=m+100&&y>=(7*n)&&y<=(8*n-n/2))
			{
			//printf("3rd selected");
				closegraph();
				update_item();
				return 1;
			}
			if(x>=m&&x<=m+112&&y>=(8*n)&&y<=(9*n-n/2))
			{
				closegraph();
				remove_item();
				return 1;
			}
			if(x>=m&&x<=m+100&&y>=(9*n)&&y<=(10*n-n/2))
			{
			//printf("5th selected");
				closegraph();
				search();
				return 1;
			}
			/*if(x>=m&&x<=m+110&&y>=(10*n)&&y<=(11*n-n/2))
			{
				//printf("6th selected");
				closegraph();
				fmanager();
				return 1;
			}*/
			if(x>=125&&x<=180&&y>=435&&y<=445)		//logout
			{
				return 2;
			}
			if(x>=4*m&&x<=4*m+45&&y>=(n*12)&&y<=(n*12+15))  //EXIT
			{
				rectangle(4*m+2,n*12+2,4*m+43,n*12+13);
				hide_mouse1();
				delay(500);
				closegraph();
				clrscr();
				exit(0);
			}
		    // printf("X- %d , Y - %d \n",x,y);
		}
		delay (150); // Otherwise due to quick computer response 100s of words will get print
	}
}

void hide_mouse1()
{
	in.x.ax = 2;
	int86(0X33, &in, &out);
}


void enterpassword()
{
char c;
int i = 0;
c = getch();
while(c!= '\r')
{
	if(c != '\b')
	{
		cout<<"*";
		password_array[i] = c;
		i++;

	}
	else
	{
		cout<<"\b \b";
		password_array[i-1] = '\0';
		i--;
	}
	c = getch();


}
password_array[i] = '\0';

}
