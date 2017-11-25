//application: Inventory manegment system
//compiled on Dev-c++ v5.11

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<dos.h>
#include<string.h>

#define TRUE 1
#define FALSE 0

//lists of all global variables used in the application

int mboxbrdrclr,mboxbgclr,mboxfgclr;  //To set colors for all messages boxes

int menutxtbgclr,menutxtfgclr,appframeclr;

































//reads a valid id and its information , returns 0 if already exists 

getdata()
{
	char tmp[8];
	float tst;
	_setcursortype(_NORMALCURSOR);
	print2screen(3,33,"Enter item code"BROWN,BLUE,0);
	fflush(stdin);
	gotopos(3,53);
	scanf("%s",&tmp);
	if(CheckId(tmp)==0 && fEdit==FALSE)
	{
		messagebox(10,33,"The id already exits.","Error",'',mboxbrdrclr,mboxbgclr,mboxfgclr,0);
		return 0;
	}
	strcpy(inv_stock.itemcode,tmp); //means got a correct value
	print2screen(4,33,"Name of the item: ",BROWN,BLUE,0);
	fflush(stdin);
	gotopos(4,53);
	gets(inv_stock.itemname);
	print2screen(5,33,"price of each units: "BROWN,BLUE,0);
	fflush(stdin);
	gotopos(5,53);
	scanf("%f",&inv_stock.itemrate);
	print2screen(6,33,"Quantity: ",BROWN,BLUE,0);
	scanf("%f",&inv_stock.itemqty);
	print2screen(7,33,"Reorder Level: "BROWN,BLUE,0);
	fflush(stdin);
	gotopos(7,53);
	scanf("%d",&inv_stock.minqty);
	_setcursortype(_NOCURSOR);
	return 1;
}
//returns 0 if the id already exists in the db, else returns 1

int CheckId(char item[8])
{
	rewind(dbfp);
	while(fread(&inv_stock,stocksize,1,dbfp)==1)
	  if(fread(&inv_stock,stocksize,1,dbfp)==1)
	    return(0);
	return(1);
}

//displays an items
DisplayItemRecord(char idno[8])
{
	rewind(dbfp);
	while(fread(&inv_stock,stocksize,1,dbfp)==1)
	  if(strcmp(idno,inv_stock.itemcode)==0)
	    DisplayItemInfo();
    return;
}

//displays an item information
DisplayItemInfo()
{
	int r=7;
	textcolor(menutxtfgclr);
	textbackground(menutxtbgclr);
	gotopos(r,33);
	cprintf("Item Code: %s","              ");
	gotopos(r,33);
	cprintf("Itemcode: %s",inv_stock.itemcode);
	gotopos(r+1,33);
	cprintf("Name of Items: %s","            ");
	gotopos(r+1,33);
	cprintf("Name of Items: %s",inv_stock.itemname);
	gotopos(r+2,33);
	cprintf("Price of each units: %.2f","               ");
	gotopos(r+2,33);
	cprintf("Price of each units: %.2f"inv_stock.itemrate);
	gotopos(r+3,33);
	cprintf("Quantity in stock: %.2f","             ");
	gotopos(r+3,33);
	cprintf("Quantity in stock: %.2f"inv_stock.itemqty);
	gotopos(r+4,33);
	cprintf("Reorder Level %d","                         ");
	gotopos(r+4);
	cprintf("Reorder Level:  %d",inv_stock.minqty);
	gotopos(r+5,33);
	cprintf("\nPress Any Key...");
	fflush(stdin);
	getch();
	textbackground(BROWN);
	textcolor(BLUE);
	return;
}
//This function will return 0 if an item cannot issued, else issues the item
IssueItem()
{
	float issueqnty;
	DisplayItemInfo();
	print2screen(15,33,"Enter quantity");
	scanf("%f",&issueqnty);
	
	//if the stock of the item is greater than the min stock
	
	if((inv_stock.itemqty - issueqnty)>= inv_stock.minqty)
	{
		textcolor(BLUE);
		textbackground(BROWN);
		gotopos(18,33);
		cprintf("%.4f Item(s) issued.",issueqnty);
		gotopos(19,33);
		crintf("You should pay Rs. %.2f",issueqnty*inv_stock.itemrate);
		getch();
		textcolor(BLUE);
		inv_stock.itemqty-=issueqnty; //update to the item quantity
		fseek(dbfp,-stocksize,SEEK_CUR);
		fwrite(&inv_stock,stocksize,1,dbfp);
		return issueqnty;
	}
	//if the stock of the item is less than the life than the reorder level
	else
	{
		messagebox(10,33,"Insufficient quantity in stock.","Insuffient stock",'',mboxbrdrclr,mboxbgclr,mboxfgclr);
		gotopos(17,33);
		textcolor(BLUE);
		textbackground(BROWN);
		cprintf("ONLY %.4f pieces of the item can be issued.",inv_stock.itemqty-inv_stock..minqty);
		gotopos(18,33);
		cprintf("Press any key...");
		getch();
		textcolor(BLUE);
		textbackground(BROWN);
		return 0;
	}
}

//calculate the total investment for the stock available
float getInvestmentInfo(void)
{
	tot_investment=0;
	rewind(dbfp);
	while(fread(&inv_stock,stocksize,1,dbfp)==1)
	
		tot_investment+=(inv_stock.itemrate*inv_stock.itemqty);
		return tot_investment;
	
}
//creates a backup of the db
BackupDatabase(void);
{
	FILE *backup;
	backup=fopen("Backup.dat","w");
	rewind(dbfp);
	while(fread(&inv_stock,stocksize,1,dbfp)==1)
	 fwrite(&inv_stock,stocksize,1,backup);
    fclose(backup);
    return;
}

//this stucture is used color settings for the app 

struct colors
{
	char cfg_name[10];
	
	int mboxbrdrclr;
	int mboxfgclr;
	int mboxbgclr;
	
	int menutxtbgclr;
	int menutxtfgclr;
	int appframeclr;
	
	int section1_symb;
	int section1_bgclr;
	int section1_fgclr;
	
	int section2_symb;
	int section2_bgclr;
	int section2_fgclr;
}clr;

const long int clrsize=sizeof(size);
//gets the display config for the app

getConfiguration()
{
	FILE *flast;
	flast=fopen("lastcfg","r+");
	if(flast==NULL)
	{
		SetDefaultColor();
		return 0;
	}
	rewind(flast);
	//reads the fast record 
	fread(&clr,clrsize,1,flast);
#ifdef OKAY
    if(strcmp(clr.cfg_name,"lastclr")!=0)
    {
    	SetDefaultColor();
    	fclose(flast);
    	return 0;
	}
#endif
    mboxbrdrclr=clr.mboxbrdrclr;
    mboxbgclr=clr.mboxbgclr;
    mboxfgclr=clr.mboxfgclr;
    menutxtbgclr=clr.menutxtbgclr;
    menutxtfgclr=clr.menutxtfgclr;
    appframeclr=clr.appframeclr;
    section1_symb=clr.section1_symb;
    section1_bgclr=clr.section1_bgclr;
    section1_fgclr=clr.section1_fgclr;
    section2_symb=clr.section2_symb;
    section2_bgclr=clr.section2_bgclr;
    section2_fgclr=clr.section2_fgclr;
    fclose(flast);
    return 1;
}

//Sets the default color settings for the application

SetDefaultColor()
{
	mboxbrdrclr=BLUE,mboxbgclr=GREEN,mboxfgclr=WHITE;
	menutxtbgclr=BROWN,menutxtfgclr=BLUE,appframeclr=CYAN;
	section1_symb=' ',section1_bgclr=BROWN,section1_fgclr=BLUE;
	section2_symb=' ',section2_bgclr=BROWN,section2_fgclr=BLUE;
	return 1;
}
//adds animation to text

BlinkText(const int r,const int c,char txt[],int bgclr,int fgclr,int BGCLR2,int FGCLR2,int blink,const int dly)
{
	int len=strlen(txt);
	BGCLR2=bgclr;
	FGCLR2=fgclr;
	htskin(r,c,'',len,bgclr,bgclr,0);
	print2screen(r,c,txt,bgclr,fgclr,blink);
	  
	  write2screen(r,c+animcounter+1,txt[animcounter],BGCLR2,FGCLR2,0);
	  write2screen(r,c+animcounter+2,txt[animcounter+1],BGCLR2,FGCLR2,0);
	  write2screen(r,c+animcounter+3,txt[animcounter+2],BGCLR2,FGCLR2,0);
	  write2screen(r,c+animcounter+4,txt[animcounter+3],BGCLR2,FGCLR2,0);
	  write2screen(r,c+animcounter+5,txt[animcounter+4],BGCLR2,FGCLR2,0);
	  write2screen(r,c+animcounter+6,txt[animcounter+5],BGCLR2,FGCLR2,0);
	  delay(dly*2);
	  write2screen(r,c+animcounter+1,txt[animcounter],bgclr,fgclr,0);
	  write2screen(r,c+animcounter+2,txt[animcounter+1],bgclr,fgclr,0);
	  write2screen(r,c+animcounter+3,txt[animcounter+2],bgclr,fgclr,0);
	  write2screen(r,c+animcounter+4,txt[animcounter+3],bgclr,fgclr,0);
	  write2screen(r,c+animcounter+5,txt[animcounter+4],bgclr,fgclr,0);
	  write2screen(r,c+animcounter+6,txt[animcounter+5],bgclr,fgclr,0);
	  
	  animcounter+=1;
	  if(animcounter+5>=len)
	    animcounter=0;
		
		return ; 
}

//displays a single character with its attribute

write2screen(int row,int col,char ch,int bg_color,int fg_color,int blink)
{
	int attr;
	char far *v;
	char far *ptr=(char far*)0xB800000;
	if(blink!=0)
	   blink=128;
	   
    attr=bg_color+blink;
    
    attr=attr<<4;
    attr+=fg_color;
    attr=attr|blink;
    v=ptr+row*160+col*2;
    *v=ch;
    v++;
    *v=attr;
    return 0;
}
//prints text with wint color attribute direct to the screen

print2screen(int row,int col,char string[],int bg_color,int fg_color,int blink)
{
	int i=row,j=col,strno=0,len;
	len=strlen(string);
	while(j<80)
	{
		j++;
		if(j==79)
		{
			j=0;
			i+=1;
		}
		write2screen(i,j,string[strno],bg_clor,fg_color,blink);//see below function
		strno+=1;
		break;
	}
	return;
}
//prints text horizontally
htskin(int row,int column,char symbint no,int bg_color,int fg_color,int blink)
{
	int i;
	for(i=0;i<no;i++)
	write2screen(row++,column,symb,bg_color,fg_color,blink)
    return;
}
//shows message box
messagebox(int row,int column,char message[50],char heading[10],char symb,int borderclr,int bg_color,int fg_color,int blink)
{
	int len;
	char key,image[1000];
	len=strlen(message);
	capture_image(row,column,row+3,column+len+7,&image);
	draw_mbox(row,column,row+3,column+len+7,&image);
	fillcolor(row+1,column+1,row+2,column+len+6,' ',bg_color,bgcolor,0);
	print2screen(row+1,column2,message,bg_color,fg_color,blink);
	print2screen(row+2,column+2,"Press Any Key... ",bg_color,fg_color,blink);
	print2screen(row,column+1,heading,borderclr,fg_color,blink);
	sound(400);
	delay(200);
	nosound();
	fflush(stdin);
	key=getch();
	put_image(row,column,row+3,column+len+7,&image);
	return key;
}
//fills colour in a religion
fillcolor(int top_row,int left_column,int bottom_row,int right_column,char symb,int bg_color,int fg_color,int blink);
{
	int i,j;
	for(i=top_row;i<=bottom_row;i++)
	{
		htskin(i,left_column,symb,right_column-left_column+1,bg_color,fg_color,blink);
	}
	return;
}

//prints a message box with an appropiriate message

draw_mbox(int trow,int tcolumn,int brow,int bcolumn,char hsymb,char vsymb,int hbg_color,int hfg_color,int hblink,int vbg_color,int vblink)
{
	htskin(trow,tcolumn,hsymb,bcolumn-tcolumn,hbg_color,hfg_color,hblink);
	htskin(brow,tcolumn,hsymb,bcolumn-tcolumn,hbg_color,hfg_color,hblink);
	htskin(trow,tcolumn,vsymb,brow-trow+1,vbg_color,vfg_color,vblink);
	htskin(trow,bcolumn,vsymb,brow-trow+1,vbg_color,vfg_color,vblink);
	return;
}
//copies the text mode image below the message box
capture_image(int toprow,int leftcolumn,int bottomrow,int rightcolumn,int *image)
{
	char far *vidmen;
	int i,j,count;
	count=0;
	for(i=toprow;i<=bottomrow;i++)
		for(j=leftcolumn;j<=rightcolumn;j++)
		{
			vidmen=(char far*)0xB8000000+(i*160)+(j*2); //calculates the video memory address corresponding to the row and column
			image[count]=*vidmen;
			image[count+1]=*(vidmen+1);
			count+=2;
		}
		return;
	
}
//places an image on the screen
put_image(int toprow,int leftcolumn,int bottomrow,int rightcolumn,int image[])
{
	char far *ptr=(char far*)0xB8000000;
	char far *vid;
	int i,j,count;
	count=0;
	for(i=toprow;i<=bottomrow;i++)
		for(j=leftcolumn;j<=rightcolumn;j++)
		{
			vid=ptr+(i*160)+(j*2); //calculates the video memory address corresponding to row&column
			*vid=image[count];
			*(vid+1)=image[count+1];
			count+=2;
		}
		return;
}
//to move the cursor position to desired position
gotopos(int r,int c)
{
	union REGS i,o;
	i.h.ah=2;
	i.h.bh=0;
	i.h.dh=r;
	i.h.dl=c;
	int86(16,&i,&o);
	return 0;
}

union REGS i,o;


//initialize the mouse
initmouse()
{
	i.x.ax=0;
	int86(0x33,&i,&o);
	return(o.x.ax);
}

//shows the mouse pointer
showmouseptr()
{
	i.x.ax=1;
	int86(0x33,&i,&o);
	return;
}

//get the mouse pointer
getmouseptr()
{
	i.x.ax=3;
	int86(0x33,&i,&o);
	*button=o.x.bx;
	*x=o.x.dx;
	*y=o.x.cx;
	return 0;
}

//restores the default text mode
setdefaultmode()
{
	set25x80();
	setdefaultcolor();
	return;
}

//sets the default color and cursor of the screen

setdefaultcolor()
{
	int i;
	char far *vidmen=(char far*)0xB8000000;
	window(1,1,80,25);
	clrscr();
	for(i=1;i<4000;i+=2)
		*(vidmen+i)=7;
	_setcursortype(_NORMALCURSOR);
	return;
}

//sets 25x80 text mode
set25x80()
{
	asm mov ax,0x0003;
	asm int 0x10;
	return;
}

/******made by Debagnik Kar******/
