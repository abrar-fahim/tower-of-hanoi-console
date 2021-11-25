#include <stdio.h>
#include <windows.h>

int n;
int ns, nh , nd;
int so[100],he[100],de[100];

void gotoxy(int x,int y)
{
  COORD coord={x,y};
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void printPoles(int n)
{
    int x,y,i,j;
    for(y=5;y<=n+10;y++)
    {
        for(x=20;x<=120;x=x+50)
        {
            gotoxy(x,y);
            printf("|");
        }

    }

    for(j=5;j<=135;j=j+50)
    {
        gotoxy(j,n+10);
        for(x=j;x<=(j+30);x++)
        printf("_");
    }

}

void printCurrentDisks(void)
{
    int i;
    for(i=0;i<n;i++)  //prints source disks
    {
        printDisk(so[i],20,n+10-i);
    }
    for(i=0;i<n;i++)
    {
        printDisk(he[i],70,n+10-i);
    }
    for(i=0;i<n;i++)
    {
        printDisk(de[i],120,n+10-i);
    }
}

void printDisk(int diskNum,int x,int y) //x coordinate here is the centre of the disk.
{
    int sizeFactor,j;
    sizeFactor=30/n;
    //diskNum is 1 for the smallest disk and n for the largest.
      for(j=x-((sizeFactor*diskNum)/2);j<=x+(sizeFactor*diskNum)/2;j++)
        {
            gotoxy(j,y);
            printf("|");
        }
}

void moveDisk(int diskNum,int s,int d)
{

    int numSource; //numSource tells us the num of disks in the CURRENT source.
    int numDest;   //numDest tells us the num of disks in the CURRENT destination.
    int i,j;

    printPoles(n);

      switch(s)
    {
    case 20:
        numSource=ns;
        so[numSource-1]=0;
        ns--;
        break;
    case 70:
        numSource=nh;
        he[numSource-1]=0;
        nh--;
        break;
    case 120:
        numSource=nd;
        de[numSource-1]=0;
        nd--;
        break;
    }

    switch(d)
    {
    case 20:
        numDest=ns;
        ns++;
        break;
    case 70:
        numDest=nh;
        nh++;
        break;
    case 120:
        numDest=nd;
        nd++;
        break;
    }

    for(i=(n-numSource)+10;i>=3;i--)  //n-ns+10 gives us the y coordinate of the top disk at source.
    {
        system("cls");
        printPoles(n);
        printCurrentDisks();
        printDisk(diskNum,s,i); //n-ns+1 gives us the disk number of the top disk at source.
    }
    if(d>s)
    {
         for(i=s;i<=d;i++)
         {
             system("cls");
             printPoles(n);
             printCurrentDisks();
             printDisk(diskNum,i,3);
         }
    }
    else
    {
        for(i=s;i>=d;i--)
        {
            system("cls");
            printPoles(n);
            printCurrentDisks();
            printDisk(diskNum,i,3);
        }

    }
    for(i=3;i<=((n+10)-numDest);i++)
    {
        system("cls");
        printPoles(n);
        printCurrentDisks();
        printDisk(diskNum,d,i);
    }
    switch(d)
    {
    case 20:
        so[numDest]=diskNum;
        break;
    case 70:
        he[numDest]=diskNum;
        break;
    case 120:
        de[numDest]=diskNum;
        break;
    }
}

void hanoi(int n,int s,int h,int d)
{
    if(n==1) moveDisk(1,s,d);

    else
    {
        hanoi(n-1,s,d,h);
        moveDisk(n,s,d);
        hanoi(n-1,h,s,d);
    }
}

int main()
{
    int i;
    printf("Enter number of disks: ");
    scanf("%d",&n);
    ns=n;
    nh=0;
    nd=0;
    for(i=0;i<n;i++)     //initializes all the arrays. value of 0 means no disk is present in the position.
    {
        so[i]=n-i;
        he[i]=0;
        de[i]=0;
    }
    for(i=0;i<100;i++)
    {
        printCurrentDisks();
        printPoles(n);
    }
    hanoi(n,20,70,120);  //the numbers are central x coordinates of the poles
    printPoles(n);
    printCurrentDisks();
}
