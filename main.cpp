#include<windows.h>
#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define pi 3.142857

/************************************/       ///changes made

int anime=1;
float edge_x=0,edge_y=0;
int done=0;

/**********************************/

/************************************************/

GLint x0=50,y00=50,yend=90,xend=150,dy,dx,swap1=0,swap2=0;
GLfloat m;
GLfloat x11=0,y11=0;
GLfloat mov[2]={0,0};
int co=0;
float path_follow[500][2];
int dnt_repeat=-1;

struct Node{
    float x;
    float y;
    struct Node* next;
};

struct Node* PathHead = NULL;
void man();

void PathInsert(float x1,float y1) {
   struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
   new_node->x = x1;
   new_node->y = y1;
   new_node->next = PathHead;
   PathHead = new_node;
}

void PathDeleteList(){
   struct Node* current = PathHead;
   struct Node* next;

   while (current != NULL)
   {
       next = current->next;
       free(current);
       current = next;
   }
   PathHead = NULL;
}

void PathPrint() {
   struct Node* ptr;
   co=0;
   ptr = PathHead;
   //float x1,y1;
   while (ptr != NULL) {

   path_follow[co][0]=ptr->x;
   path_follow[co][1]=ptr->y;
        co++;
      ptr = ptr->next;
   }

PathDeleteList();
}

void setPixel(GLint x,GLint y){
    glColor3f(1,0,0);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    x11=(GLfloat)x;
    y11=(GLfloat)y;

    PathInsert((float)x11,(float)y11);
    //mov={x,y};
    glutPostRedisplay();
}

void LinePosSlope(){
    GLint p=2*dy-dx;
    GLint twoDy=2*dy;
    GLint twoDyminusDx=2*(dy-dx);
    GLint x=x0,y=y00;
    GLint z=xend;
    if(x0>xend){
        x=xend;
        y=yend;
        xend=x0;
        swap1=1;
    }
    while(x<xend){
        x++;
        if(p<0){
            p+=twoDy;
        }
        else{
            if(x0<z && y00>yend){
                y--;
                p+=twoDyminusDx;
            }
            else{
                y++;
                p+=twoDyminusDx;
            }

        }
        printf("%d,%d   %d \n",x,y,p);
        setPixel(x,y);
    }
}

void LineNegSlope(){
    GLint p=2*dx-dy;
    GLint twoDy=2*dx;
    GLint twoDyminusDx=2*(dx-dy);
    GLint x=x0,y=y00;
    GLint z=yend;
    if(y00>yend){
        x=xend;
        y=yend;
        yend=y00;
        swap1=1;
    }
    while(y<yend){
        y++;
        if(p<0){
            p+=twoDy;
        }
        else{
            if(y00<z && x0>xend){
                x--;
                p+=twoDyminusDx;
            }
            else{
                x++;
                p+=twoDyminusDx;
            }

        }
        printf("%d,%d   %d \n",x,y,p);
        setPixel(x,y);
    }
}
void make_the_man_move(){

    //x0=
    //y00=
    //xend=
    //yend=
    if(dnt_repeat==-1)
    {
    dx=abs(xend-x0);
    dy=abs(yend-y00);
    m=(float)(dy)/(float)(dx);
    if(m>=1)
        LineNegSlope();
    else
        LinePosSlope();
    PathPrint();
    printf("%d",co);
    dnt_repeat++;
    }
    else {
    glPushMatrix();
    glTranslatef(-27.866667,-40.557500,0);
    //glTranslatef(375.66664,225.8848,0);
    //glTranslatef(377.9995,420.5399976,0);
    if(swap1==0 && swap2 ==0)
        glTranslatef((GLfloat)path_follow[co-dnt_repeat-1][0],(GLfloat)path_follow[co-dnt_repeat-1][1],0);
    else
        glTranslatef((GLfloat)path_follow[dnt_repeat][0],(GLfloat)path_follow[dnt_repeat][1],0);
    glScalef(0.25,0.25,0);
    man();
    glPopMatrix();
    if(dnt_repeat<co){
        dnt_repeat++;

        }
    else {
        done++;
        dnt_repeat=-1;
        swap1=0;
        swap2=0;
    }
    }

}
/**************************************************/


void *font;
void *currentfont;
int fontType,flag=0;
GLfloat carpos=0.0;
//float x,y,angle,angle_radians,r1=15,xx,yy,r2=80;
float p,q,angle,angle_radians,p1=25;
void display();
void start();
void circle(int p,int q,int r,int s);
void man();
void window();
void window1();
void window2();
void window3();
void window4();
void window5();
void window6();
 void window7();
 void matrix();
void values();
void drawcloud();
int slide=0;
char *e1="DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING";
char *e2="ST. JOSEPH ENGINEERING COLLEGE,MANGALURU-28";
char *e3="COMPUTER GRAPHICS PROJECT  ON";
char *e4="BELLMANFORD ALGORITHM";
char *e5="SUBMITTED BY:" ;
char *e6="PRINCY PAUL DSILVA               :  4SO16CS085";



void output(int x,int y,char *string);
void output1(int x,int y,char *string);


void drawstring(float x,float y,float z,char *string)
{
	char *c;
	glRasterPos3f(x,y,z);

	for(c=string;*c!='\0';c++)
	{	glColor3f(0.0,0.0,1.0);
		glutBitmapCharacter(currentfont,*c);
	}
}

void circle(int p,int q,int r,int s)
    {
        float theta;
        glBegin(GL_POLYGON);
        for(int i=0;i<360;i++){
            theta=i*3.142/180;
            glVertex3f(p+s*cos(theta),q+s*sin(theta),r);

        }
        glEnd();
    }



void setFont(void *font)
{
	currentfont=font;
}

void output(int x,int y,char *string)
{
  int len,i;
  glRasterPos2f(x,y);
  len=(int) strlen(string);
  for(i=0;i<len;i++)
    {
     glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,string[i]);
    }
}

void output1(int x,int y,char *string)
{
  int len,i;
  glRasterPos2f(x,y);
  len=(int) strlen(string);
  for(i=0;i<len;i++)
    {
     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
    }
}

/***********************************************************/

void keys(unsigned char key,int x,int y){
switch(key){
case 'P':
case 'p':
    if(slide>0)
        slide--;

        anime=1;
    break;
case 'N':
case 'n':
    if(slide<9)
        slide++;

        anime=1;
    break;
}
dnt_repeat=-1;
swap1=0;
glutPostRedisplay();
}
/**********************************************************/

void myMouse(int id)//when we press some key what has to happen
 {
 switch(id)
 {
     anime=1;

 case 1:slide=0;
          break;
 case 2:slide=1;


           break;
case 3:slide=2;

        /************************************************/



        /******************************************************/
       break;
case 4:slide=3;
       break;
case 5:slide=4;
       break;
case 6:slide=5;
       break;
case 7:slide=6;
       break;
case 8:slide=7;
       break;
case 9:slide=8;
       break;
case 10:slide=9;
       break;
case 11:slide=10;
        break;
case 12:slide=11;
        break;
case 13:slide=12;
         break;

 }
 glutPostRedisplay();
}

void display1()
{
glClear(GL_COLOR_BUFFER_BIT);

glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

glLoadIdentity();
gluOrtho2D(0,1000,0,1000);
switch(slide)
{
    case 0:start();
          break;
    case 1:display();
           break;
    case 2:

        window();

    /*************************************************************/

    if(anime>=2){
    glColor3f(0,0,0);
   drawstring(73,500,0.0,"node1");
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(123,500,0.0,"node2");
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
    drawstring(173,500,0.0,"node3");
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
    drawstring(225,500,0.0,"node4");
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
    drawstring(273,500,0.0,"node5");



    }
    if(anime>=3){

   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
    drawstring(138,422.5,0.0,"4");
     glColor3f(0,0,0);
     drawstring(184,422.5,0.0,"INF");
      glColor3f(0,0,0);
      drawstring(233,422.5,0.0,"-1");
       glColor3f(0,0,0);
       drawstring(280,422.5,0.0,"INF");
        glColor3f(0,0,0);
       drawstring(96,420,0.0,"0");

    }
    if(anime>=4){

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(100,350.5,0.0,"4");
    glColor3f(0,0,0);
    drawstring(133,350.5,0.0,"0");
     glColor3f(0,0,0);
    drawstring(186,350.5,0.0,"9");
     glColor3f(0,0,0);
    drawstring(240,350.5,0.0,"INF");

     glColor3f(0,0,0);
    drawstring(280,350.5,0.0,"5");

    }
    if(anime>=5){

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(90,262.5,0.0,"INF");
    glColor3f(0,0,0);
   drawstring(142,262.5,0.0,"9");
    glColor3f(0,0,0);
    drawstring(185,262.5,0.0,"0");
     glColor3f(0,0,0);
    drawstring(233,262.5,0.0,"INF");
     glColor3f(0,0,0);
    drawstring(280,262.5,0.0,"-2");
    }
    if(anime>=6){
   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
     glColor3f(0,0,0);
    drawstring(90,187.5,0.0,"-1");
     glColor3f(0,0,0);
     drawstring(133,187.5,0.0,"INF");
      glColor3f(0,0,0);
      drawstring(185,187.5,0.0,"INF");
       glColor3f(0,0,0);
   drawstring(233,187.5,0.0,"0");
    glColor3f(0,0,0);
    drawstring(290,187.5,0.0,"6");

    }
    if(anime>=7){

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
     glColor3f(0,0,0);
    drawstring(83,137.5,0.0,"INF");
     glColor3f(0,0,0);
     drawstring(143,137.5,0.0,"5");
      glColor3f(0,0,0);
      drawstring(190,137.5,0.0,"-2");
       glColor3f(0,0,0);
       drawstring(240,137.5,0.0,"6");
        glColor3f(0,0,0);
       drawstring(285,137.5,0.0,"0");
    }
    if(anime!=7)
        anime++;
    Sleep(600);


    /*************************************************************/

    /*************************************************/

glutPostRedisplay();

/***********************************************/
           break;
    case 3:window1();
           break;
    case 4:window2();
            //if(anime!=7)
            //anime++;

            Sleep(25);
            glutPostRedisplay();
           break;
     case 5:window3();
                //if(anime!=7)
           // anime++;
            Sleep(25);
            glutPostRedisplay();
           break;
     case 6:window4();
            //if(anime!=7)
            //anime++;
            Sleep(25);
            glutPostRedisplay();
           break;
     case 7:window5();
            //if(anime!=7)
            //anime++;
            Sleep(25);
            glutPostRedisplay();
           break;
    case 8:window6();
            //if(anime!=7)
            //anime++;
            Sleep(25);
            glutPostRedisplay();
           break;
   case 9:matrix();
           Sleep(25);
            glutPostRedisplay();
           break;

    case 10:exit(0);
}




glFlush();
glutSwapBuffers();

}
void start()
{

        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_POLYGON);
        glColor3ub(0.678, 0.847, 0.902);
        glVertex2d(0,0);
        glColor3ub(0.678, 0.847, 0.902);
		glVertex2d(1000,0);
		glColor3f(0.678, 0.847, 0.902);
        glVertex2d(1000,1000);
        glColor3f(0.678, 0.847, 0.902);
        glVertex2d(0,1000);
        glColor3f(0.678, 0.847, 0.902);
	glEnd();
    glColor3f(.1,.1,.1);
    output1(260,900,e1);
    output1(280,800,e2);
    output1(350,700,e3);
    glColor3f(1,1,1);
    output1(400,500,e4);
    glColor3f(1,1,1);
    output1(440,400,e5);
    output1(440,275,e6);
    //output1(440,275,e7);
    //output1(440,200,e8);
    glColor3f(1,1,1);
    output1(400,100,"UNDER THE GUIDANCE OF");
    output1(430,50,"NISHA ROCHE");
    glColor3f(0,0,0);
}

void man()
{
    glBegin(GL_POLYGON);

   for(angle=0; angle<=360; angle=angle+5)                  //neck
   {
       angle_radians = angle * (float) 3.14159 / (float)180;
       p = 99+p1* (float)cos(angle_radians);
       q = 297 + p1* (float)sin(angle_radians);
       glColor3f(0.0,0.0,0.0);
       glVertex2f(p,q);
   }

   glEnd();

   glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(0,0,0);
    glVertex2f(50,150);                //body
    glVertex2f(150,150);
    glVertex2f(150,150);
    glVertex2f(150,50);
    glVertex2f(150,50);
    glVertex2f(125,50);
    glVertex2f(125,50);
    glVertex2f(100,135);
    glVertex2f(100,135);
    glVertex2f(75,50);
    glVertex2f(75,50);
    glVertex2f(50,50);
    glVertex2f(50,50);
    glVertex2f(50,150);
    glVertex2f(50,50);
    glVertex2f(30,30);
    glVertex2f(30,30);
    glVertex2f(75,30);
     glVertex2f(75,30);
    glVertex2f(75,50);
    glVertex2f(150,50);
    glVertex2f(170,30);
    glVertex2f(170,30);
    glVertex2f(125,30);
    glVertex2f(125,30);
    glVertex2f(125,50);

    glVertex2f(50,150);             //belt   lines
    glVertex2f(50,160);
    glVertex2f(50,160);
    glVertex2f(150,160);
    glVertex2f(150,160);
    glVertex2f(150,150);

    glVertex2f(90,150);             //belt square
    glVertex2f(90,160);
    glVertex2f(110,150);
    glVertex2f(110,160);

    glVertex2f(50,160);             //body
    glVertex2f(50,250);
    glVertex2f(50,250);
    glVertex2f(75,250);
    glVertex2f(75,250);
    glVertex2f(100,210);
    glVertex2f(100,210);
    glVertex2f(125,250);
    glVertex2f(125,250);
    glVertex2f(150,250);
    glVertex2f(150,250);
    glVertex2f(150,160);

    glVertex2f(75,250);          //neck
    glVertex2f(75,270);
    glVertex2f(75,270);
    glVertex2f(125,270);
    glVertex2f(125,270);
    glVertex2f(125,250);

    glVertex2f(50,250);          //hands
    glVertex2f(30,190);
    glVertex2f(30,190);
   glVertex2f(50,150);
    glVertex2f(150,250);          //right
    glVertex2f(170,190);
    glVertex2f(170,190);
    glVertex2f(150,150);

    /*glVertex2f(75,270);         //head
    glVertex2f(75,310);
    glVertex2f(75,310);
    glVertex2f(125,310);
    glVertex2f(125,310);
    glVertex2f(125,270);*/
    glEnd();


}

void display()
{
   glClearColor(0.678, 0.847, 0.902,0);
   glClear(GL_COLOR_BUFFER_BIT);

    //glPushMatrix();
    //glScalef(0.5,0.5,0);
    man();

     glColor3f(1,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   glLineWidth(2);
    glColor3f(0,0,1);
     drawstring(110,570,0.0," Hello Friends I Am Chimpu....");
      glColor3f(0,0,1);
     drawstring(160,540,0.0,"How Do I Find ");
     glColor3f(0,0,1);
     drawstring(130,510,0.0," My Shortest Path ???? ");
     glBegin(GL_LINES);
     glColor3f(0,0,0);
    glVertex2f(300,500);
    glVertex2f(300,600);
    glVertex2f(300,600);
    glVertex2f(100,600);
    glVertex2f(100,600);
    glVertex2f(100,530);
     glVertex2f(100,530);
      glVertex2f(80,480);
      glVertex2f(80,480);
      glVertex2f(100,500);
      glVertex2f(100,500);
      glVertex2f(300,500);

glEnd();


    //glPopMatrix();

//drawstring(550,850,0.0,"TO FIND THE SHORTEST PATH");
glLineWidth(1);
glBegin(GL_POLYGON);
glVertex2f(100,200);
glVertex2f(200,300);
glVertex2f(100,200);
glEnd();

   glBegin(GL_POLYGON);              //node 2
   glColor3f(0.0,0.0,1.0);
   glVertex2d(400,400);
   glVertex2d(400,450);

   glVertex2d(450,450);
   glVertex2d(450,400);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(400,450);
   glVertex2d(425,470);
   glVertex2d(450,450);
   glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(415,500,0.0,"node2");
   glColor3f(0,0,0);
   drawstring(500,490,0.0,"9");
   glColor3f(0,0,0);
   drawstring(580,390,0.0,"5");
   glBegin(GL_POLYGON);               //node 3
   glColor3f(0.0,0.0,1.0);
   glVertex2d(600,600);
   glVertex2d(600,550);
   glVertex2d(650,550);
   glVertex2d(650,600);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(600,600);
   glVertex2d(625,630);

    glVertex2d(650,600);
    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(615,650,0.0,"node3");
   glColor3f(0,0,0);
   drawstring(680,520,0.0,"-2");
   glBegin(GL_POLYGON);               //node 1
   glColor3f(0.0,0.0,1.0);
   glVertex2d(400,200);
   glVertex2d(400,250);
   glVertex2d(450,250);
   glVertex2d(450,200);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(400,250);
    glVertex2d(425,270);

    glVertex2d(450,250);

    glEnd();
   glPopMatrix();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(415,170,0.0,"node1");
   glColor3f(0,0,0);
   drawstring(430,300,0.0,"4");
   glBegin(GL_POLYGON);                 //node 4
   glColor3f(0.0,0.0,1.0);
   glVertex2d(600,100);
   glVertex2d(600,150);
   glVertex2d(650,150);
   glVertex2d(650,100);

   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(600,150);
    glVertex2d(625,170);

    glVertex2d(650,150);

    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(615,70,0.0,"node4");
   glColor3f(0,0,0);
   drawstring(560,160,0.0,"-1");
   glBegin(GL_POLYGON);                   //node 5
   glColor3f(0.0,0.0,1.0);
   glVertex2d(800,300);
   glVertex2d(800,350);
   glVertex2d(850,350);
   glVertex2d(850,300);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(800,350);

    glVertex2d(825,370);
    glVertex2d(850,350);
    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(840,380,0.0,"node5");
   glColor3f(0,0,0);
   drawstring(700,200,0.0,"6");
   glBegin(GL_LINES);              //node 2 to node 3
   glColor3f(0.0,0.0,0.0);
   glVertex2d(450,450);
   glVertex2d(600,550);
   glEnd();

   glBegin(GL_LINES);              //node 1 to node 2
   glColor3f(0.0,0.0,0.0);
   glVertex2d(425,270);
   glVertex2d(425,400);
   glEnd();

   glBegin(GL_LINES);               //node 2 to node 5
   glColor3f(0.0,0.0,0.0);
   glVertex2d(450,400);
   glVertex2d(800,300);
   glEnd();

   glBegin(GL_LINES);                //node 1 to node 4
   glColor3f(0.0,0.0,0.0);
   glVertex2d(450,200);
   glVertex2d(600,100);
   glEnd();

   glBegin(GL_LINES);                //node 4 to node 5
   glColor3f(0.0,0.0,0.0);
   glVertex2d(650,100);
   glVertex2d(825,300);
   glEnd();

   glBegin(GL_LINES);               // node 3 to node 5
   glColor3f(0.0,0.0,0.0);
   glVertex2d(825,370);
   glVertex2d(650,550);
   glEnd();

}
void window()
{

   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0,0,0);
   drawstring(450,890,0.0,"Here it just calculates the path and if the node is not reachable it is infinity ");
   glLineWidth(1);
   glBegin(GL_POLYGON);              //node 2
   glColor3f(0.0,0.0,1.0);
   glVertex2d(400,400);
   glVertex2d(400,450);

   glVertex2d(450,450);
   glVertex2d(450,400);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(400,450);
   glVertex2d(425,470);
   glVertex2d(450,450);
   glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(415,500,0.0,"node2");
   glColor3f(0,0,0);
   drawstring(500,490,0.0,"9");
   glColor3f(0,0,0);
   drawstring(580,390,0.0,"5");
   glBegin(GL_POLYGON);               //node 3
   glColor3f(0.0,0.0,1.0);
   glVertex2d(600,600);
   glVertex2d(600,550);
   glVertex2d(650,550);
   glVertex2d(650,600);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(600,600);
   glVertex2d(625,630);

    glVertex2d(650,600);
    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(615,650,0.0,"node3");
   glColor3f(0,0,0);
   drawstring(680,520,0.0,"-2");
   glBegin(GL_POLYGON);               //node 1
   glColor3f(0.0,0.0,1.0);
   glVertex2d(400,200);
   glVertex2d(400,250);
   glVertex2d(450,250);
   glVertex2d(450,200);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(400,250);
    glVertex2d(425,270);

    glVertex2d(450,250);

    glEnd();
   glPopMatrix();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(415,170,0.0,"node1");
   glColor3f(0,0,0);
   drawstring(430,300,0.0,"4");
   glBegin(GL_POLYGON);                 //node 4
   glColor3f(0.0,0.0,1.0);
   glVertex2d(600,100);
   glVertex2d(600,150);
   glVertex2d(650,150);
   glVertex2d(650,100);

   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(600,150);
    glVertex2d(625,170);

    glVertex2d(650,150);

    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(615,70,0.0,"node4");
   glColor3f(0,0,0);
   drawstring(560,160,0.0,"-1");
   glBegin(GL_POLYGON);                   //node 5
   glColor3f(0.0,0.0,1.0);
   glVertex2d(800,300);
   glVertex2d(800,350);
   glVertex2d(850,350);
   glVertex2d(850,300);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(800,350);

    glVertex2d(825,370);
    glVertex2d(850,350);
    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(840,380,0.0,"node5");
   glColor3f(0,0,0);
   drawstring(700,200,0.0,"6");
   glBegin(GL_LINES);              //node 2 to node 3
   glColor3f(0.0,0.0,0.0);
   glVertex2d(450,450);
   glVertex2d(600,550);
   glEnd();

   glBegin(GL_LINES);              //node 1 to node 2
   glColor3f(0.0,0.0,0.0);
   glVertex2d(425,270);
   glVertex2d(425,400);
   glEnd();

   glBegin(GL_LINES);               //node 2 to node 5
   glColor3f(0.0,0.0,0.0);
   glVertex2d(450,400);
   glVertex2d(800,300);
   glEnd();

   glBegin(GL_LINES);                //node 1 to node 4
   glColor3f(0.0,0.0,0.0);
   glVertex2d(450,200);
   glVertex2d(600,100);
   glEnd();

   glBegin(GL_LINES);                //node 4 to node 5
   glColor3f(0.0,0.0,0.0);
   glVertex2d(650,100);
   glVertex2d(825,300);
   glEnd();

   glBegin(GL_LINES);               // node 3 to node 5
   glColor3f(0.0,0.0,0.0);
   glVertex2d(825,370);
   glVertex2d(650,550);
   glEnd();

   glLineWidth(3);
   glBegin(GL_LINES);
   glColor3f(0,0.0,0.0);
   glVertex2d(70,550);
   glVertex2d(70,100);
   glVertex2d(70,550);
   glVertex2d(320,550);
   glVertex2d(70,475);
   glVertex2d(320,475);
   glVertex2d(70,400);
   glVertex2d(320,400);
   glVertex2d(70,325);
   glVertex2d(320,325);
   glVertex2d(70,250);
   glVertex2d(320,250);
   glVertex2d(70,175);
   glVertex2d(320,175);
   glVertex2d(70,100);
   glVertex2d(320,100);

   glVertex2d(120,550);
   glVertex2d(120,100);
   glVertex2d(170,550);
   glVertex2d(170,100);
   glVertex2d(220,550);
   glVertex2d(220,100);
   glVertex2d(270,550);
   glVertex2d(270,100);
   glVertex2d(320,550);
   glVertex2d(320,100);
   glEnd();
    //column numbers
   /*glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(95,570,0.0,"1");
    glColor3f(0,0,0);
   drawstring(145,570,0.0,"2");
    glColor3f(0,0,0);
   drawstring(195,570,0.0,"3");
    glColor3f(0,0,0);
   drawstring(245,570,0.0,"4");
    glColor3f(0,0,0);
   drawstring(295,570,0.0,"5");*/


    glColor3f(0,0,0);
    //drawstring(50,512.5,0.0,"0");
     glColor3f(0,0,0);
    drawstring(30,437.5,0.0,"node1");
     glColor3f(0,0,0);
    drawstring(30,362.5,0.0,"node2");
     glColor3f(0,0,0);
    drawstring(30,287.5,0.0,"node3");
     glColor3f(0,0,0);
    drawstring(30,212.5,0.0,"node4");
     glColor3f(0,0,0);
    drawstring(30,137.5,0.0,"node5");
}
void window1()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,0);
    drawstring(550,890,0.0,"To Find The Shortest Path");
    glLineWidth(1);
   glBegin(GL_POLYGON);              //node 2
   glColor3f(0.0,0.0,1.0);
   glVertex2d(400,400);
   glVertex2d(400,450);

   glVertex2d(450,450);
   glVertex2d(450,400);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(400,450);
   glVertex2d(425,470);
   glVertex2d(450,450);
   glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(415,500,0.0,"node2");
   glColor3f(0,0,0);
   drawstring(500,490,0.0,"9");
   glColor3f(0,0,0);
   drawstring(580,390,0.0,"5");
   glBegin(GL_POLYGON);               //node 3
   glColor3f(0.0,0.0,1.0);
   glVertex2d(600,600);
   glVertex2d(600,550);
   glVertex2d(650,550);
   glVertex2d(650,600);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(600,600);
   glVertex2d(625,630);

    glVertex2d(650,600);
    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(615,650,0.0,"node3");
   glColor3f(0,0,0);
   drawstring(680,520,0.0,"-2");
   glBegin(GL_POLYGON);               //node 1
   glColor3f(0.0,0.0,1.0);
   glVertex2d(400,200);
   glVertex2d(400,250);
   glVertex2d(450,250);
   glVertex2d(450,200);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(400,250);
    glVertex2d(425,270);

    glVertex2d(450,250);

    glEnd();
   glPopMatrix();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(415,170,0.0,"node1");
   glColor3f(0,0,0);
   drawstring(430,300,0.0,"4");
   glBegin(GL_POLYGON);                 //node 4
   glColor3f(0.0,0.0,1.0);
   glVertex2d(600,100);
   glVertex2d(600,150);
   glVertex2d(650,150);
   glVertex2d(650,100);

   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(600,150);
    glVertex2d(625,170);

    glVertex2d(650,150);

    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(615,70,0.0,"node4");
   glColor3f(0,0,0);
   drawstring(560,160,0.0,"-1");
   glBegin(GL_POLYGON);                   //node 5
   glColor3f(0.0,0.0,1.0);
   glVertex2d(800,300);
   glVertex2d(800,350);
   glVertex2d(850,350);
   glVertex2d(850,300);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(800,350);

    glVertex2d(825,370);
    glVertex2d(850,350);
    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(840,380,0.0,"node5");
   glColor3f(0,0,0);
   drawstring(700,200,0.0,"6");
   glBegin(GL_LINES);              //node 2 to node 3
   glColor3f(0.0,0.0,0.0);
   glVertex2d(450,450);
   glVertex2d(600,550);
   glEnd();

   glBegin(GL_LINES);              //node 1 to node 2
   glColor3f(0.0,0.0,0.0);
   glVertex2d(425,270);
   glVertex2d(425,400);
   glEnd();

   glBegin(GL_LINES);               //node 2 to node 5
   glColor3f(0.0,0.0,0.0);
   glVertex2d(450,400);
   glVertex2d(800,300);
   glEnd();

   glBegin(GL_LINES);                //node 1 to node 4
   glColor3f(0.0,0.0,0.0);
   glVertex2d(450,200);
   glVertex2d(600,100);
   glEnd();

   glBegin(GL_LINES);                //node 4 to node 5
   glColor3f(0.0,0.0,0.0);
   glVertex2d(650,100);
   glVertex2d(825,300);
   glEnd();

   glBegin(GL_LINES);               // node 3 to node 5
   glColor3f(0.0,0.0,0.0);
   glVertex2d(825,370);
   glVertex2d(650,550);
   glEnd();
   glLineWidth(3);
   glBegin(GL_LINES);
   glColor3f(0,0.0,0.0);
   glVertex2d(70,550);
   glVertex2d(70,100);
   glVertex2d(70,550);
   glVertex2d(320,550);
   glVertex2d(70,475);
   glVertex2d(320,475);
   glVertex2d(70,400);
   glVertex2d(320,400);
   glVertex2d(70,325);
   glVertex2d(320,325);
   glVertex2d(70,250);
   glVertex2d(320,250);
   glVertex2d(70,175);
   glVertex2d(320,175);
   glVertex2d(70,100);
   glVertex2d(320,100);
   glVertex2d(120,550);
   glVertex2d(120,100);
   glVertex2d(170,550);
   glVertex2d(170,100);
   glVertex2d(220,550);
   glVertex2d(220,100);
   glVertex2d(270,550);
   glVertex2d(270,100);
   glVertex2d(320,550);
   glVertex2d(320,100);
   glEnd();
    //column numbers
    Sleep(500);
   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   //drawstring(95,570,0.0,"node1");
    glColor3f(0,0,0);
   drawstring(73,500,0.0,"node1");
    glColor3f(0,0,0);
   drawstring(123,500,0.0,"node2");
    glColor3f(0,0,0);
   drawstring(173,500,0.0,"node3");
    glColor3f(0,0,0);
    drawstring(225,500,0.0,"node4");
     glColor3f(0,0,0);
    drawstring(273,500,0.0,"node5");

   /*glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(145,570,0.0,"node2");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(195,570,0.0,"node3");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(245,570,0.0,"node4");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(295,570,0.0,"node5");*/

   //row numbers
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   //drawstring(50,512.5,0.0,"0");

   glColor3f(0,0,0);
    drawstring(30,437.5,0.0,"node1");
     glColor3f(0,0,0);
    drawstring(30,362.5,0.0,"node2");
     glColor3f(0,0,0);
    drawstring(30,287.5,0.0,"node3");
     glColor3f(0,0,0);
    drawstring(30,212.5,0.0,"node4");
     glColor3f(0,0,0);
    drawstring(30,137.5,0.0,"node5");


}
void window2()
{
    glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0,0,0);
   drawstring(550,890,0.0,"Here Source Node Is 1");
   glLineWidth(1);
    glBegin(GL_POLYGON);              //node 2
   glColor3f(0.0,0.0,1.0);
   glVertex2d(400,400);
   glVertex2d(400,450);

   glVertex2d(450,450);
   glVertex2d(450,400);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(400,450);
   glVertex2d(425,470);
   glVertex2d(450,450);
   glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(415,500,0.0,"node2");
   glColor3f(0,0,0);
   drawstring(500,490,0.0,"9");
   glColor3f(0,0,0);
   drawstring(580,390,0.0,"5");
   glBegin(GL_POLYGON);               //node 3
   glColor3f(0.0,0.0,1.0);
   glVertex2d(600,600);
   glVertex2d(600,550);
   glVertex2d(650,550);
   glVertex2d(650,600);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(600,600);
   glVertex2d(625,630);

    glVertex2d(650,600);
    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(615,650,0.0,"node3");
   glColor3f(0,0,0);
   drawstring(680,520,0.0,"-2");
   glBegin(GL_POLYGON);               //node 1
   glColor3f(0.0,0.0,1.0);
   glVertex2d(400,200);
   glVertex2d(400,250);
   glVertex2d(450,250);
   glVertex2d(450,200);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(400,250);
    glVertex2d(425,270);

    glVertex2d(450,250);

    glEnd();
   glPopMatrix();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(415,170,0.0,"node1");
   glColor3f(0,0,0);
   drawstring(430,300,0.0,"4");
   glBegin(GL_POLYGON);                 //node 4
   glColor3f(0.0,0.0,1.0);
   glVertex2d(600,100);
   glVertex2d(600,150);
   glVertex2d(650,150);
   glVertex2d(650,100);

   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(600,150);
    glVertex2d(625,170);

    glVertex2d(650,150);

    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(615,70,0.0,"node4");
   glColor3f(0,0,0);
   drawstring(560,160,0.0,"-1");
   glBegin(GL_POLYGON);                   //node 5
   glColor3f(0.0,0.0,1.0);
   glVertex2d(800,300);
   glVertex2d(800,350);
   glVertex2d(850,350);
   glVertex2d(850,300);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(800,350);

    glVertex2d(825,370);
    glVertex2d(850,350);
    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(840,380,0.0,"node5");
   glColor3f(0,0,0);
   drawstring(700,200,0.0,"6");
   glLineWidth(2);

   glColor3f(0,0,0);
   glBegin(GL_LINES);             //node 2 to node 3
   glColor3f(0.0,0.0,0.0);
   glVertex2d(450,450);
   glVertex2d(625,550);
   glEnd();



   if((anime==3) ){
   glColor3f(1,1,0);
    }
   else
   glColor3f(0.0,0.0,0.0);
   glBegin(GL_LINES);             //node 1 to node 2
   glVertex2d(425,400);
   glVertex2d(425,270);
   glEnd();


   glColor3f(0.0,0.0,0.0);
   glBegin(GL_LINES);                  //node 2 to node 5
   glVertex2d(450,400);
   glVertex2d(800,300);
   glEnd();


  if((anime==4)||(anime==5) ||(anime==6) ){
    glColor3f(1,1,0);
  }
   else
    glColor3f(0.0,0.0,0.0);

   glBegin(GL_LINES);                 //node 1 to node 4
   glVertex2d(450,200);
   glVertex2d(600,100);
   glEnd();

   if((anime==4)||(anime==6) ){
    glColor3f(1,1,0);
    }
   else
    glColor3f(0.0,0.0,0.0);


   glBegin(GL_LINES);             //node 4 to node 5
   glVertex2d(650,100);
   glVertex2d(825,300);
   glEnd();

   if((anime==4) ){
    glColor3f(1,1,0);
    }
   else
    glColor3f(0.0,0.0,0.0);
   glBegin(GL_LINES);                //node 3 to node 5
   glVertex2d(825,370);
   glVertex2d(650,550);
   glEnd();


   glLineWidth(3);
   glBegin(GL_LINES);
   glColor3f(0,0.0,0.0);
   glVertex2d(70,550);
   glVertex2d(70,100);
   glVertex2d(70,550);
   glVertex2d(320,550);
   glVertex2d(70,475);
   glVertex2d(320,475);
   glVertex2d(70,400);
   glVertex2d(320,400);
   glVertex2d(70,325);
   glVertex2d(320,325);
   glVertex2d(70,250);
   glVertex2d(320,250);
   glVertex2d(70,175);
   glVertex2d(320,175);
   glVertex2d(70,100);
   glVertex2d(320,100);

   glVertex2d(120,550);
   glVertex2d(120,100);
   glVertex2d(170,550);
   glVertex2d(170,100);
   glVertex2d(220,550);
   glVertex2d(220,100);
   glVertex2d(270,550);
   glVertex2d(270,100);
   glVertex2d(320,550);
   glVertex2d(320,100);
   glEnd();
    //column numbers
   // Sleep(500);
   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   //drawstring(95,570,0.0,"1");
    glColor3f(0,0,0);                //col 1
   drawstring(73,500,0.0,"node1");
    glColor3f(0,0,0);
   drawstring(123,500,0.0,"node2");
    glColor3f(0,0,0);
   drawstring(173,500,0.0,"node3");
    glColor3f(0,0,0);
   drawstring(225,500,0.0,"node4");
    glColor3f(0,0,0);
   drawstring(273,500,0.0,"node5");


   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   //drawstring(145,570,0.0,"node2");               //col 2

     glColor3f(0,0,0);
    if((anime-1)>=2)
        drawstring(90,422.5,0.0,"0");
         glColor3f(0,0,0);
    if((anime-1)>=3)
        drawstring(140,422.5,0.0,"4");
         glColor3f(0,0,0);
    if((anime-1)>=4)
        drawstring(186,422.5,0.0,"3");
         glColor3f(0,0,0);
    if((anime-1)>=5)
        drawstring(234,422.5,0.0,"-1");
         glColor3f(0,0,0);
    if((anime-1)>=6)
        drawstring(284,422.5,0.0,"5");



   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   //drawstring(195,570,0.0,"node3");

   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   //drawstring(245,570,0.0,"node4");

   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   //drawstring(295,570,0.0,"node5");

   //row numbers
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   //drawstring(50,512.5,0.0,"0");

   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(30,437.5,0.0,"node1");

   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(30,362.5,0.0,"node2");

   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(30,287.5,0.0,"node3");

   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(30,212.5,0.0,"node4");

   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(30,137.5,0.0,"node5");



   if(anime==2){
        Sleep(800);
        anime++;
        }
    else if(anime==3){
        if(done==0){
            x0=375;
            y00=225;
            xend=375;
            yend=420;
            make_the_man_move();
        }
        if(done==1){
            anime++;
            done=0;
        }
    }
    else if(anime==4){
        if(done==0){
            x0=375;
            y00=225;
            xend=624;
            yend=67;
            make_the_man_move();
        }
        if(done==1){
            x0=624;
            y00=67;
            xend=875;
            yend=332;
            make_the_man_move();
        }
        if(done==2){
            x0=875;
            y00=332;
            xend=624;
            yend=683;
            make_the_man_move();
        }
        if(done==3){
            anime++;
            done=0;
        }
    }
    else if(anime==5){
        if(done==0){
            x0=375;
            y00=225;
            xend=624;
            yend=67;
            make_the_man_move();
        }
        if(done==1){
            anime++;
            done=0;
        }
    }
    else if(anime==6){
        if(done==0){
            x0=375;
            y00=225;
            xend=624;
            yend=67;
            make_the_man_move();
        }
        if(done==1){
            x0=624;
            y00=67;
            xend=875;
            yend=332;
            make_the_man_move();
        }
        if(done==2){
            anime++;
            done=0;
        }
    }
    else {
        anime++;
        done=0;
        Sleep(800);
        }


}
void window3()
{
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0,0,0);
   drawstring(550,890,0.0,"Here Source Node Is 2");
   glLineWidth(1);
    glBegin(GL_POLYGON);              //node 2
   glColor3f(0.0,0.0,1.0);
   glVertex2d(400,400);
   glVertex2d(400,450);

   glVertex2d(450,450);
   glVertex2d(450,400);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(400,450);
   glVertex2d(425,470);
   glVertex2d(450,450);
   glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(415,500,0.0,"node2");
   glColor3f(0,0,0);
   drawstring(500,490,0.0,"9");
   glColor3f(0,0,0);
   drawstring(580,390,0.0,"5");
   glBegin(GL_POLYGON);               //node 3
   glColor3f(0.0,0.0,1.0);
   glVertex2d(600,600);
   glVertex2d(600,550);
   glVertex2d(650,550);
   glVertex2d(650,600);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(600,600);
   glVertex2d(625,630);

    glVertex2d(650,600);
    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(615,650,0.0,"node3");
   glColor3f(0,0,0);
   drawstring(680,520,0.0,"-2");
   glBegin(GL_POLYGON);               //node 1
   glColor3f(0.0,0.0,1.0);
   glVertex2d(400,200);
   glVertex2d(400,250);
   glVertex2d(450,250);
   glVertex2d(450,200);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(400,250);
    glVertex2d(425,270);

    glVertex2d(450,250);

    glEnd();
   glPopMatrix();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(415,170,0.0,"node1");
   glColor3f(0,0,0);
   drawstring(430,300,0.0,"4");
   glBegin(GL_POLYGON);                 //node 4
   glColor3f(0.0,0.0,1.0);
   glVertex2d(600,100);
   glVertex2d(600,150);
   glVertex2d(650,150);
   glVertex2d(650,100);

   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(600,150);
    glVertex2d(625,170);

    glVertex2d(650,150);

    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(615,70,0.0,"node4");
   glColor3f(0,0,0);
   drawstring(560,160,0.0,"-1");
   glBegin(GL_POLYGON);                   //node 5
   glColor3f(0.0,0.0,1.0);
   glVertex2d(800,300);
   glVertex2d(800,350);
   glVertex2d(850,350);
   glVertex2d(850,300);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(800,350);

    glVertex2d(825,370);
    glVertex2d(850,350);
    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(840,380,0.0,"node5");
   glColor3f(0,0,0);
   drawstring(700,200,0.0,"6");
  glLineWidth(2);

   glColor3f(0,0,0);
   glBegin(GL_LINES);             //node 2 to node 3
   glColor3f(0.0,0.0,0.0);
   glVertex2d(450,450);
   glVertex2d(600,550);
   glEnd();



   if((anime==5 || (anime==2)) ){
    glColor3f(1,1,0);
    }
   else
    glColor3f(0.0,0.0,0.0);
   glBegin(GL_LINES);             //node 1 to node 2
   glVertex2d(425,400);
   glVertex2d(425,270);
   glEnd();


   if((anime==6 )||(anime==4) ){
    glColor3f(1,1,0);
    }
   else
    glColor3f(0.0,0.0,0.0);
   glBegin(GL_LINES);                  //node 2 to node 5
   glVertex2d(450,400);
   glVertex2d(800,300);
   glEnd();

   if((anime==5)){
    glColor3f(1,1,0);
    }
   else
    glColor3f(0.0,0.0,0.0);
   glBegin(GL_LINES);                 //node 1 to node 4
   glVertex2d(450,200);
   glVertex2d(600,100);
   glEnd();


    glColor3f(0.0,0.0,0.0);
   glBegin(GL_LINES);             //node 4 to node 5
   glVertex2d(650,100);
   glVertex2d(825,300);
   glEnd();

   if((anime==4) ){
    glColor3f(1,1,0);
    }
   else
    glColor3f(0.0,0.0,0.0);
   glBegin(GL_LINES);                //node 3 to node 5
   glVertex2d(825,370);
   glVertex2d(650,550);
   glEnd();

   glLineWidth(3);
   glBegin(GL_LINES);
   glColor3f(0,0.0,0.0);
   glVertex2d(70,550);
   glVertex2d(70,100);
   glVertex2d(70,550);
   glVertex2d(320,550);
   glVertex2d(70,475);
   glVertex2d(320,475);
   glVertex2d(70,400);
   glVertex2d(320,400);
   glVertex2d(70,325);
   glVertex2d(320,325);
   glVertex2d(70,250);
   glVertex2d(320,250);
   glVertex2d(70,175);
   glVertex2d(320,175);
   glVertex2d(70,100);
   glVertex2d(320,100);

   glVertex2d(120,550);
   glVertex2d(120,100);
   glVertex2d(170,550);
   glVertex2d(170,100);
   glVertex2d(220,550);
   glVertex2d(220,100);
   glVertex2d(270,550);
   glVertex2d(270,100);
   glVertex2d(320,550);
   glVertex2d(320,100);
   glEnd();
    //column numbers
    //Sleep(500);
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   //drawstring(95,570,0.0,"1");
   glColor3f(0,0,0);
    drawstring(30,437.5,0.0,"node1");
     glColor3f(0,0,0);
    drawstring(30,362.5,0.0,"node2");
     glColor3f(0,0,0);
    drawstring(30,287.5,0.0,"node3");
     glColor3f(0,0,0);
    drawstring(30,212.5,0.0,"node4");
     glColor3f(0,0,0);
    drawstring(30,137.5,0.0,"node5");



   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   //drawstring(145,570,0.0,"node2");
    glColor3f(0,0,0);              //col2
    drawstring(90,422.5,0.0,"0");
     glColor3f(0,0,0);
    drawstring(140,422.5,0.0,"4");
     glColor3f(0,0,0);
     drawstring(186,422.5,0.0,"3");
      glColor3f(0,0,0);
      drawstring(234,422.5,0.0,"-1");
       glColor3f(0,0,0);
       drawstring(284,422.5,0.0,"5");


   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
 //glColor3f(0,0,0);
   //drawstring(195,570,0.0,"3");
    glColor3f(0,0,0);
    glColor3f(0,0,0);                //col 1
   drawstring(73,500,0.0,"node1");
    glColor3f(0,0,0);
   drawstring(123,500,0.0,"node2");
    glColor3f(0,0,0);
   drawstring(173,500,0.0,"node3");
    glColor3f(0,0,0);
   drawstring(225,500,0.0,"node4");
    glColor3f(0,0,0);
   drawstring(273,500,0.0,"node5");               //col3


   glColor3f(0,0,0);
   if((anime-1)>=2)
   drawstring(90,350.5,0.0,"4");
    glColor3f(0,0,0);
   if((anime-1)>=3)
    drawstring(140,350.5,0.0,"0");
     glColor3f(0,0,0);
    if((anime-1)>=4)
    drawstring(186,350.5,0.0,"3");
     glColor3f(0,0,0);
    if((anime-1)>=5)
    drawstring(234,350.5,0.0,"3");
     glColor3f(0,0,0);
    if((anime-1)>=6)
    drawstring(284,350.5,0.0,"5");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
  //drawstring(245,570,0.0,"4");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
  // drawstring(295,570,0.0,"5");

   //row numbers
   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   //drawstring(50,512.5,0.0,"0");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(30,437.5,0.0,"node1");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(30,362.5,0.0,"node2");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(30,287.5,0.0,"node3");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(30,212.5,0.0,"node4");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(30,137.5,0.0,"node5");

   if(anime==1)
        anime++;
   else if(anime==2){
        if(done==0){
            xend=375;
            yend=225;
            x0=375;
            y00=420;
            make_the_man_move();
        }
        if(done==1){
            anime++;
            done=0;
        }
    }
    else if(anime==3){
        Sleep(800);
        anime++;
    }
    else if(anime==4){
        if(done==0){
            x0=375;
            y00=420;
            xend=875;
            yend=332;
            make_the_man_move();
        }
        else if(done==1){
            x0=875;
            y00=332;
            xend=624;
            yend=683;
            make_the_man_move();
        }
        else if(done==2){
            anime++;
            done=0;
        }

    }
    else if(anime==5){
        if(done==0){
            xend=375;
            yend=225;
            x0=375;
            y00=420;
            make_the_man_move();
        }
        if(done==1){
            x0=375;
            y00=225;
            xend=624;
            yend=67;
            make_the_man_move();
        }
        if(done==2){
            anime++;
            done=0;
        }
    }
    else if(anime==6){
        if(done==0){
            x0=375;
            y00=420;
            xend=875;
            yend=332;
            make_the_man_move();
        }
        if(done==1){
            anime++;
            done=0;
        }
    }

}
void window4()
{

    glClear(GL_COLOR_BUFFER_BIT);
     glColor3f(0,0,0);
    drawstring(550,890,0.0,"Here Source Node Is 3");
    glLineWidth(1);
    glBegin(GL_POLYGON);              //node 2
   glColor3f(0.0,0.0,1.0);
   glVertex2d(400,400);
   glVertex2d(400,450);

   glVertex2d(450,450);
   glVertex2d(450,400);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(400,450);
   glVertex2d(425,470);
   glVertex2d(450,450);
   glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(415,500,0.0,"node2");
   glColor3f(0,0,0);
   drawstring(500,490,0.0,"9");
   glColor3f(0,0,0);
   drawstring(580,390,0.0,"5");
   glBegin(GL_POLYGON);               //node 3
   glColor3f(0.0,0.0,1.0);
   glVertex2d(600,600);
   glVertex2d(600,550);
   glVertex2d(650,550);
   glVertex2d(650,600);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(600,600);
   glVertex2d(625,630);

    glVertex2d(650,600);
    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(615,650,0.0,"node3");
   glColor3f(0,0,0);
   drawstring(680,520,0.0,"-2");
   glBegin(GL_POLYGON);               //node 1
   glColor3f(0.0,0.0,1.0);
   glVertex2d(400,200);
   glVertex2d(400,250);
   glVertex2d(450,250);
   glVertex2d(450,200);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(400,250);
    glVertex2d(425,270);

    glVertex2d(450,250);

    glEnd();
   glPopMatrix();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(415,170,0.0,"node1");
   glColor3f(0,0,0);
   drawstring(430,300,0.0,"4");
   glBegin(GL_POLYGON);                 //node 4
   glColor3f(0.0,0.0,1.0);
   glVertex2d(600,100);
   glVertex2d(600,150);
   glVertex2d(650,150);
   glVertex2d(650,100);

   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(600,150);
    glVertex2d(625,170);

    glVertex2d(650,150);

    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(615,70,0.0,"node4");
   glColor3f(0,0,0);
   drawstring(560,160,0.0,"-1");
   glBegin(GL_POLYGON);                   //node 5
   glColor3f(0.0,0.0,1.0);
   glVertex2d(800,300);
   glVertex2d(800,350);
   glVertex2d(850,350);
   glVertex2d(850,300);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(800,350);

    glVertex2d(825,370);
    glVertex2d(850,350);
    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(840,380,0.0,"node5");
   glColor3f(0,0,0);
   drawstring(700,200,0.0,"6");



   glLineWidth(2);

   glColor3f(0,0,0);
   glBegin(GL_LINES);             //node 2 to node 3
   glColor3f(0.0,0.0,0.0);
   glVertex2d(450,450);
   glVertex2d(600,550);
   glEnd();



    glColor3f(0.0,0.0,0.0);
   glBegin(GL_LINES);             //node 1 to node 2
   glVertex2d(425,400);
   glVertex2d(425,270);
   glEnd();

if( (anime==3)){
    glColor3f(1,1,0);
    }
   else
   glColor3f(0.0,0.0,0.0);
   glBegin(GL_LINES);                  //node 2 to node 5
   glVertex2d(450,400);
   glVertex2d(800,300);
   glEnd();

   if((anime==2)){
    glColor3f(1,1,0);
    }
   else
    glColor3f(0.0,0.0,0.0);
   glBegin(GL_LINES);                 //node 1 to node 4
   glVertex2d(450,200);
   glVertex2d(600,100);
   glEnd();

   if((anime==2)||(anime==5)){
    glColor3f(1,1,0);
    }
   else
    glColor3f(0.0,0.0,0.0);
   glBegin(GL_LINES);             //node 4 to node 5
   glVertex2d(650,100);
   glVertex2d(825,300);
   glEnd();

   if((anime==2) || (anime==3) || (anime==5) || (anime==6) ){
    glColor3f(1,1,0);
    }
   else
    glColor3f(0.0,0.0,0.0);
   glBegin(GL_LINES);                //node 3 to node 5
   glVertex2d(825,370);
   glVertex2d(650,550);
   glEnd();



   glLineWidth(3);
   glBegin(GL_LINES);
   glColor3f(0,0.0,0.0);
   glVertex2d(70,550);
   glVertex2d(70,100);
   glVertex2d(70,550);
   glVertex2d(320,550);
   glVertex2d(70,475);
   glVertex2d(320,475);
   glVertex2d(70,400);
   glVertex2d(320,400);
   glVertex2d(70,325);
   glVertex2d(320,325);
   glVertex2d(70,250);
   glVertex2d(320,250);
   glVertex2d(70,175);
   glVertex2d(320,175);
   glVertex2d(70,100);
   glVertex2d(320,100);

   glVertex2d(120,550);
   glVertex2d(120,100);
   glVertex2d(170,550);
   glVertex2d(170,100);
   glVertex2d(220,550);
   glVertex2d(220,100);
   glVertex2d(270,550);
   glVertex2d(270,100);
   glVertex2d(320,550);
   glVertex2d(320,100);
   glEnd();
    //column numbers
    //Sleep(500);
   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   //drawstring(95,570,0.0,"1");
                  //col1
   glColor3f(0,0,0);                //col 1
   drawstring(73,500,0.0,"node1");
    glColor3f(0,0,0);
   drawstring(123,500,0.0,"node2");
    glColor3f(0,0,0);
   drawstring(173,500,0.0,"node3");
    glColor3f(0,0,0);
   drawstring(225,500,0.0,"node4");
    glColor3f(0,0,0);
   drawstring(273,500,0.0,"node5");



   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
  // drawstring(145,570,0.0,"2");
    glColor3f(0,0,0);                       //col2
   drawstring(90,422.5,0.0,"0");
    glColor3f(0,0,0);
   drawstring(140,422.5,0.0,"4");
    glColor3f(0,0,0);
   drawstring(186,422.5,0.0,"3");
    glColor3f(0,0,0);
   drawstring(234,422.5,0.0,"-1");
    glColor3f(0,0,0);
   drawstring(284,422.5,0.0,"5");


   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   //drawstring(195,570,0.0,"3");                ///col3
    glColor3f(0,0,0);
   drawstring(90,350.5,0.0,"4");
     glColor3f(0,0,0);
   drawstring(140,350,0.0,"0");
    glColor3f(0,0,0);
   drawstring(180,350.5,0.0,"3");
     glColor3f(0,0,0);
   drawstring(240,350.5,0.0,"3");
    glColor3f(0,0,0);
   drawstring(280,350.5,0.0,"5");


   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   //drawstring(245,570,0.0,"4");
    glColor3f(0,0,0);                //col4
   if((anime-1)>=2)
    drawstring(90,262.5,0.0,"3");
     glColor3f(0,0,0);
    if((anime-1)>=3)
   drawstring(140,262.5,0.0,"3");
    glColor3f(0,0,0);
   if((anime-1)>=4)
    drawstring(180,262,0.0,"0");
     glColor3f(0,0,0);
    if((anime-1)>=5)
    drawstring(240,262.5,0.0,"4");
     glColor3f(0,0,0);
    if((anime-1)>=6)
    drawstring(280,262.5,0.0,"-2");
                 //col4

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   //drawstring(295,570,0.0,"5");

   //row numbers
   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   //drawstring(50,512.5,0.0,"0");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(30,437.5,0.0,"node1");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(30,362.5,0.0,"node2");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(30,287.5,0.0,"node3");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(30,212.5,0.0,"node4");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(30,137.5,0.0,"node5");

   if(anime==1)
        anime++;
   else if(anime==2){///35 54 41
        if(done==0){
            xend=624;
            yend=683;
            x0=875;
            y00=332;
            swap2=1;
            make_the_man_move();
        }
        if(done==1){
            x0=875;
            y00=332;
            xend=624;
            yend=67;
            make_the_man_move();
        }
        if(done==2){
            xend=624;
            yend=67;
            x0=375;
            y00=225;
            swap2=1;
            make_the_man_move();
        }
        if(done==3){
            anime++;
            done=0;
        }
    }
    else if(anime==3){  ///35 52
        //Sleep(800);
        //anime++;
        if(done==0){
            xend=624;
            yend=683;
            x0=875;
            y00=332;
            swap2=1;
            make_the_man_move();
        }
        if(done==1){
            xend=875;
            yend=332;
            x0=375;
            y00=420;
            swap2=1;
            make_the_man_move();
        }
        if(done==2){
            anime++;
            done=0;
        }

    }
    else if(anime==4){
        Sleep(800);
        anime++;

    }
    else if(anime==5){    ///35 54
        if(done==0){
            xend=624;
            yend=683;
            x0=875;
            y00=332;
            swap2=1;
            make_the_man_move();
        }
        if(done==1){
            x0=875;
            y00=332;
            xend=624;
            yend=67;
            make_the_man_move();
        }
        if(done==2){
            anime++;
            done=0;
        }
    }
    else if(anime==6){    ///35
        if(done==0){
            xend=624;
            yend=683;
            x0=875;
            y00=332;
            swap2=1;
            make_the_man_move();
        }
        if(done==1){
            anime++;
            done=0;
        }
    }

}

void window5()
{

    glClear(GL_COLOR_BUFFER_BIT);
     glColor3f(0,0,0);
    drawstring(550,890,0.0,"Here Source Node Is 4 ");
    glLineWidth(1);
    glBegin(GL_POLYGON);              //node 2
   glColor3f(0.0,0.0,1.0);
   glVertex2d(400,400);
   glVertex2d(400,450);

   glVertex2d(450,450);
   glVertex2d(450,400);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(400,450);
   glVertex2d(425,470);
   glVertex2d(450,450);
   glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(415,500,0.0,"node2");
   glColor3f(0,0,0);
   drawstring(500,490,0.0,"9");
   glColor3f(0,0,0);
   drawstring(580,390,0.0,"5");
   glBegin(GL_POLYGON);               //node 3
   glColor3f(0.0,0.0,1.0);
   glVertex2d(600,600);
   glVertex2d(600,550);
   glVertex2d(650,550);
   glVertex2d(650,600);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(600,600);
   glVertex2d(625,630);

    glVertex2d(650,600);
    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(615,650,0.0,"node3");
   glColor3f(0,0,0);
   drawstring(680,520,0.0,"-2");
   glBegin(GL_POLYGON);               //node 1
   glColor3f(0.0,0.0,1.0);
   glVertex2d(400,200);
   glVertex2d(400,250);
   glVertex2d(450,250);
   glVertex2d(450,200);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(400,250);
    glVertex2d(425,270);

    glVertex2d(450,250);

    glEnd();
   glPopMatrix();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(415,170,0.0,"node1");
   glColor3f(0,0,0);
   drawstring(430,300,0.0,"4");
   glBegin(GL_POLYGON);                 //node 4
   glColor3f(0.0,0.0,1.0);
   glVertex2d(600,100);
   glVertex2d(600,150);
   glVertex2d(650,150);
   glVertex2d(650,100);

   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(600,150);
    glVertex2d(625,170);

    glVertex2d(650,150);

    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(615,70,0.0,"node4");
   glColor3f(0,0,0);
   drawstring(560,160,0.0,"-1");
   glBegin(GL_POLYGON);                   //node 5
   glColor3f(0.0,0.0,1.0);
   glVertex2d(800,300);
   glVertex2d(800,350);
   glVertex2d(850,350);
   glVertex2d(850,300);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(800,350);

    glVertex2d(825,370);
    glVertex2d(850,350);
    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(840,380,0.0,"node5");
   glColor3f(0,0,0);
   drawstring(700,200,0.0,"6");
   glLineWidth(2);

   glColor3f(0,0,0);
   glBegin(GL_LINES);             //node 2 to node 3
   glColor3f(0.0,0.0,0.0);
   glVertex2d(450,450);
   glVertex2d(600,550);
   glEnd();

   if( (anime==3)){
    glColor3f(1,1,0);
    }
   else
    glColor3f(0.0,0.0,0.0);
   glBegin(GL_LINES);             //node 1 to node 2
   glVertex2d(425,400);
   glVertex2d(425,270);
   glEnd();



    glColor3f(0.0,0.0,0.0);
   glBegin(GL_LINES);                  //node 2 to node 5
   glVertex2d(450,400);
   glVertex2d(800,300);
   glEnd();

   if((anime==2)|| (anime==3)){
    glColor3f(1,1,0);
    }
   else
    glColor3f(0.0,0.0,0.0);
   glBegin(GL_LINES);                 //node 1 to node 4
   glVertex2d(450,200);
   glVertex2d(600,100);
   glEnd();


   if((anime==4) || (anime==6)){
    glColor3f(1,1,0);
    }
   else
    glColor3f(0.0,0.0,0.0);
   glBegin(GL_LINES);             //node 4 to node 5
   glVertex2d(650,100);
   glVertex2d(825,300);
   glEnd();

   if((anime==4) ){
    glColor3f(1,1,0);
    }
   else
    glColor3f(0.0,0.0,0.0);
   glBegin(GL_LINES);                //node 3 to node 5
   glVertex2d(825,370);
   glVertex2d(650,550);
   glEnd();


   glLineWidth(3);
   glBegin(GL_LINES);
   glColor3f(0,0.0,0.0);
   glVertex2d(70,550);
   glVertex2d(70,100);
   glVertex2d(70,550);
   glVertex2d(320,550);
   glVertex2d(70,475);
   glVertex2d(320,475);
   glVertex2d(70,400);
   glVertex2d(320,400);
   glVertex2d(70,325);
   glVertex2d(320,325);
   glVertex2d(70,250);
   glVertex2d(320,250);
   glVertex2d(70,175);
   glVertex2d(320,175);
   glVertex2d(70,100);
   glVertex2d(320,100);

   glVertex2d(120,550);
   glVertex2d(120,100);
   glVertex2d(170,550);
   glVertex2d(170,100);
   glVertex2d(220,550);
   glVertex2d(220,100);
   glVertex2d(270,550);
   glVertex2d(270,100);
   glVertex2d(320,550);
   glVertex2d(320,100);
   glEnd();
    //column numbers
    //Sleep(500);
   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   //drawstring(95,570,0.0,"1");        //COL1
    glColor3f(0,0,0);                //col 1
   drawstring(73,500,0.0,"node1");
    glColor3f(0,0,0);
   drawstring(123,500,0.0,"node2");
    glColor3f(0,0,0);
   drawstring(173,500,0.0,"node3");
    glColor3f(0,0,0);
   drawstring(225,500,0.0,"node4");
    glColor3f(0,0,0);
   drawstring(273,500,0.0,"node5");
   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   //drawstring(145,570,0.0,"2");
    glColor3f(0,0,0);             //COL2
   drawstring(90,422.5,0.0,"0");
    glColor3f(0,0,0);
    drawstring(140,422.5,0.0,"4");
     glColor3f(0,0,0);
    drawstring(186,422.5,0.0,"3");
     glColor3f(0,0,0);
    drawstring(234,422.5,0.0,"-1");
     glColor3f(0,0,0);
    drawstring(284,422.5,0.0,"5");
     glColor3f(0,0,0);

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   //drawstring(195,570,0.0,"3");
    glColor3f(0,0,0);              //COL3
   drawstring(90,350.5,0.0,"4");
    glColor3f(0,0,0);
    drawstring(140,350,0.0,"0");
     glColor3f(0,0,0);
    drawstring(180,350.5,0.0,"3");
     glColor3f(0,0,0);
    drawstring(240,350.5,0.0,"3");
     glColor3f(0,0,0);
    drawstring(280,350.5,0.0,"5");


   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   //drawstring(245,570,0.0,"4");            //COL4
    glColor3f(0,0,0);
    drawstring(90,262.5,0.0,"3");
    glColor3f(0,0,0);
   drawstring(140,262.5,0.0,"3");
     glColor3f(0,0,0);
    drawstring(180,262,0.0,"0");
     glColor3f(0,0,0);
    drawstring(240,262.5,0.0,"4");
     glColor3f(0,0,0);
    drawstring(280,262.5,0.0,"-2");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
   //drawstring(295,570,0.0,"5");
    glColor3f(0,0,0);          //COL5
   if((anime-1)>=2)
    drawstring(90,187.5,0.0,"-1");
     glColor3f(0,0,0);
   if((anime-1)>=3)
  drawstring(140,187.5,0.0,"3");
   glColor3f(0,0,0);
   if((anime-1)>=4)
   drawstring(180,187.5,0.0,"4");
    glColor3f(0,0,0);
   if((anime-1)>=5)
   drawstring(240,187.5,0.0,"INF");
    glColor3f(0,0,0);
   if((anime-1)>=6)
   drawstring(280,187.5,0.0,"6");

   //row numbers
   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   //drawstring(30,512.5,0.0,"0");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(30,437.5,0.0,"node1");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(30,362.5,0.0,"node2");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(30,287.5,0.0,"node3");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(30,212.5,0.0,"node4");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(30,137.5,0.0,"node5");

   if(anime==1)
        anime++;
   else if(anime==2){///41
        if(done==0){
            x0=375;
            y00=225;
            xend=624;
            yend=67;
            swap2=1;
            make_the_man_move();
        }
        if(done==1){
            anime++;
            done=0;
        }
    }
    else if(anime==3){  ///41 12
        //Sleep(800);
        //anime++;
        if(done==0){
            x0=375;
            y00=225;
            xend=624;
            yend=67;
            swap2=1;
            make_the_man_move();
        }
        if(done==1){
            xend=375;
            yend=420;
            x0=375;
            y00=225;
            //swap2=1;
            make_the_man_move();
        }
        if(done==2){
            anime++;
            done=0;
        }

    }
    else if(anime==4){ ///45 53
        if(done==0){
            xend=875;
            yend=332;
            x0=624;
            y00=67;
            //swap2=1;
            make_the_man_move();
        }
        if(done==1){
            xend=624;
            yend=683;
            x0=875;
            y00=332;
            //swap2=1;
            make_the_man_move();
        }
        if(done==2){
            anime++;
            done=0;
        }

    }
    else if(anime==5){    ///
        Sleep(800);
        anime++;
    }
    else if(anime==6){    ///45
        if(done==0){
            xend=875;
            yend=332;
            x0=624;
            y00=67;
            //swap2=1;
            make_the_man_move();
        }
        if(done==1){
            anime++;
            done=0;
        }
    }

}
void window6()
{
    glClear(GL_COLOR_BUFFER_BIT);
     glColor3f(0,0,0);
    drawstring(550,890,0.0,"Here Source Node Is 5");
    glLineWidth(1);
    glBegin(GL_POLYGON);              //node 2
   glColor3f(0.0,0.0,1.0);
   glVertex2d(400,400);
   glVertex2d(400,450);

   glVertex2d(450,450);
   glVertex2d(450,400);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(400,450);
   glVertex2d(425,470);
   glVertex2d(450,450);
   glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(415,500,0.0,"node2");
   glColor3f(0,0,0);
   drawstring(500,490,0.0,"9");
   glColor3f(0,0,0);
   drawstring(580,390,0.0,"5");
   glBegin(GL_POLYGON);               //node 3
   glColor3f(0.0,0.0,1.0);
   glVertex2d(600,600);
   glVertex2d(600,550);
   glVertex2d(650,550);
   glVertex2d(650,600);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(600,600);
   glVertex2d(625,630);

    glVertex2d(650,600);
    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(615,650,0.0,"node3");
   glColor3f(0,0,0);
   drawstring(680,520,0.0,"-2");
   glBegin(GL_POLYGON);               //node 1
   glColor3f(0.0,0.0,1.0);
   glVertex2d(400,200);
   glVertex2d(400,250);
   glVertex2d(450,250);
   glVertex2d(450,200);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(400,250);
    glVertex2d(425,270);

    glVertex2d(450,250);

    glEnd();
   glPopMatrix();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(415,170,0.0,"node1");
   glColor3f(0,0,0);
   drawstring(430,300,0.0,"4");
   glBegin(GL_POLYGON);                 //node 4
   glColor3f(0.0,0.0,1.0);
   glVertex2d(600,100);
   glVertex2d(600,150);
   glVertex2d(650,150);
   glVertex2d(650,100);

   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(600,150);
    glVertex2d(625,170);

    glVertex2d(650,150);

    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(615,70,0.0,"node4");
   glColor3f(0,0,0);
   drawstring(560,160,0.0,"-1");
   glBegin(GL_POLYGON);                   //node 5
   glColor3f(0.0,0.0,1.0);
   glVertex2d(800,300);
   glVertex2d(800,350);
   glVertex2d(850,350);
   glVertex2d(850,300);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(800,350);

    glVertex2d(825,370);
    glVertex2d(850,350);
    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(840,380,0.0,"node5");
   glColor3f(0,0,0);
   drawstring(700,200,0.0,"6");
   glLineWidth(2);

   glColor3f(0,0,0);
   glBegin(GL_LINES);             //node 2 to node 3
   glColor3f(0.0,0.0,0.0);
   glVertex2d(450,450);
   glVertex2d(600,550);
   glEnd();



    glColor3f(0.0,0.0,0.0);
   glBegin(GL_LINES);             //node 1 to node 2
   glVertex2d(425,400);
   glVertex2d(425,270);
   glEnd();


if( (anime==3)){
    glColor3f(1,1,0);
    }
   else
    glColor3f(0.0,0.0,0.0);
   glBegin(GL_LINES);                  //node 2 to node 5
   glVertex2d(450,400);
   glVertex2d(800,300);
   glEnd();

   if((anime==2)){
    glColor3f(1,1,0);
    }
   else
    glColor3f(0.0,0.0,0.0);
   glBegin(GL_LINES);                 //node 1 to node 4
   glVertex2d(450,200);
   glVertex2d(600,100);
   glEnd();

   if((anime==2)||(anime==5) ){
    glColor3f(1,1,0);
    }
   else
    glColor3f(0.0,0.0,0.0);
   glBegin(GL_LINES);             //node 4 to node 5
   glVertex2d(650,100);
   glVertex2d(825,300);
   glEnd();

   if((anime==4) ){
    glColor3f(1,1,0);
    }
   else
    glColor3f(0.0,0.0,0.0);
   glBegin(GL_LINES);                //node 3 to node 5
   glVertex2d(825,370);
   glVertex2d(650,550);
   glEnd();


   glLineWidth(3);
   glBegin(GL_LINES);
   glColor3f(0,0.0,0.0);
   glVertex2d(70,550);
   glVertex2d(70,100);
   glVertex2d(70,550);
   glVertex2d(320,550);
   glVertex2d(70,475);
   glVertex2d(320,475);
   glVertex2d(70,400);
   glVertex2d(320,400);
   glVertex2d(70,325);
   glVertex2d(320,325);
   glVertex2d(70,250);
   glVertex2d(320,250);
   glVertex2d(70,175);
   glVertex2d(320,175);
   glVertex2d(70,100);
   glVertex2d(320,100);

   glVertex2d(120,550);
   glVertex2d(120,100);
   glVertex2d(170,550);
   glVertex2d(170,100);
   glVertex2d(220,550);
   glVertex2d(220,100);
   glVertex2d(270,550);
   glVertex2d(270,100);
   glVertex2d(320,550);
   glVertex2d(320,100);
   glEnd();
    //column numbers
    //Sleep(500);
   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   //drawstring(95,570,0.0,"1");
    glColor3f(0,0,0);                //col 1
   drawstring(73,500,0.0,"node1");
    glColor3f(0,0,0);
   drawstring(123,500,0.0,"node2");
    glColor3f(0,0,0);
   drawstring(173,500,0.0,"node3");
    glColor3f(0,0,0);
   drawstring(225,500,0.0,"node4");
    glColor3f(0,0,0);
   drawstring(273,500,0.0,"node5");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   //drawstring(145,570,0.0,"2");
    glColor3f(0,0,0);
   drawstring(90,422.5,0.0,"0");
    glColor3f(0,0,0);
    drawstring(140,422.5,0.0,"4");
     glColor3f(0,0,0);
    drawstring(180,422.5,0.0,"3");
     glColor3f(0,0,0);
    drawstring(240,422.5,0.0,"-1");
     glColor3f(0,0,0);
    drawstring(280,422.5,0.0,"5");


   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   //drawstring(195,570,0.0,"3");
    glColor3f(0,0,0);
   drawstring(90,350.5,0.0,"4");
    glColor3f(0,0,0);
    drawstring(140,350,0.0,"0");
     glColor3f(0,0,0);
    drawstring(180,350.5,0.0,"3");
     glColor3f(0,0,0);
    drawstring(240,350.5,0.0,"3");
     glColor3f(0,0,0);
    drawstring(280,350.5,0.0,"5");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   //drawstring(245,570,0.0,"4");
    glColor3f(0,0,0);
   drawstring(90,262.5,0.0,"3");
    glColor3f(0,0,0);
   drawstring(140,262.5,0.0,"3");
    glColor3f(0,0,0);
    drawstring(180,262,0.0,"0");
     glColor3f(0,0,0);
    drawstring(240,262.5,0.0,"4");
     glColor3f(0,0,0);
    drawstring(280,262.5,0.0,"-2");


   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
     glColor3f(0,0,0);
    //drawstring(295,570,0.0,"5");          //COL5     //ROW5
     glColor3f(0,0,0);
   drawstring(90,187.5,0.0,"-1");
    glColor3f(0,0,0);
     drawstring(140,187.5,0.0,"3");
      glColor3f(0,0,0);
      drawstring(180,187.5,0.0,"4");
       glColor3f(0,0,0);
   drawstring(240,187.5,0.0,"0");
    glColor3f(0,0,0);
    drawstring(280,187.5,0.0,"6");


     glColor3f(0,0,0);
    if((anime-1)>=2)
    drawstring(90,137.5,0.0,"5");   //ROW6
     glColor3f(0,0,0);
    if((anime-1)>=3)
    drawstring(140,137.5,0.0,"5");
     glColor3f(0,0,0);
    if((anime-1)>=4)
     drawstring(180,137.5,0.0,"-2");
      glColor3f(0,0,0);
    if((anime-1)>=5)
    drawstring(240,137.5,0.0,"6");
     glColor3f(0,0,0);
    if((anime-1)>=6)
    drawstring(285,137.5,0.0,"0");
     glColor3f(0,0,0);




   //row numbers
   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   //drawstring(50,512.5,0.0,"0");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(30,437.5,0.0,"node1");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(30,362.5,0.0,"node2");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(30,287.5,0.0,"node3");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(30,212.5,0.0,"node4");

   glColor3f(0,0,1);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   drawstring(30,137.5,0.0,"node5");

   if(anime==1)
        anime++;
   else if(anime==2){///54 41
        if(done==0){
            x0=875;
            y00=332;
            xend=624;
            yend=67;
            //swap2=1;
            make_the_man_move();
        }
        if(done==1){
            xend=624;
            yend=67;
            x0=375;
            y00=225;
            swap2=1;
            make_the_man_move();
        }
        if(done==2){
            anime++;
            done=0;
        }
    }
    else if(anime==3){  ///52
        if(done==0){
            xend=875;
            yend=332;
            x0=375;
            y00=420;
            swap2=1;
            make_the_man_move();
        }
        if(done==1){
            anime++;
            done=0;
        }

    }
    else if(anime==4){ ///53
        if(done==0){
            x0=875;
            y00=332;
            xend=624;
            yend=683;
            //swap2=1;
            make_the_man_move();
        }
        if(done==1){
            anime++;
            done=0;
        }

    }
    else if(anime==5){    ///54
        if(done==0){
            x0=875;
            y00=332;
            xend=624;
            yend=67;
            //swap2=1;
            make_the_man_move();
        }
        if(done==1){
            anime++;
            done=0;
        }
    }
    else if(anime==6){    ///
        Sleep(800);
        anime++;
    }

}

void matrix()
{

    glClear(GL_COLOR_BUFFER_BIT);
     glColor3f(0,0,0);
    drawstring(550,890,0.0,"Solution");
    glColor3f(0,0,0);
     drawstring(480,820,0.0,"The Source Node Is Taken 1");

    glLineWidth(2);
    glColor3f(0,0,0);
     drawstring(110,670,0.0,"Yipppeee!!!!!!!!! I  Finally Found My ");
      glColor3f(0,0,0);
     drawstring(150,640,0.0,"Shortest Path");




    glLineWidth(1);
    glBegin(GL_POLYGON);              //node 2
   glColor3f(0.0,0.0,1.0);
   glVertex2d(400,400);
   glVertex2d(400,450);

   glVertex2d(450,450);
   glVertex2d(450,400);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(400,450);
   glVertex2d(425,470);
   glVertex2d(450,450);
   glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(415,500,0.0,"node2");
   glColor3f(0,0,0);
   drawstring(500,490,0.0,"9");
   glColor3f(0,0,0);
   drawstring(580,390,0.0,"5");
   glBegin(GL_POLYGON);               //node 3
   glColor3f(0.0,0.0,1.0);
   glVertex2d(600,600);
   glVertex2d(600,550);
   glVertex2d(650,550);
   glVertex2d(650,600);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(600,600);
   glVertex2d(625,630);

    glVertex2d(650,600);
    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(615,650,0.0,"node3");
   glColor3f(0,0,0);
   drawstring(680,520,0.0,"-2");
   glBegin(GL_POLYGON);               //node 1
   glColor3f(0.0,0.0,1.0);
   glVertex2d(400,200);
   glVertex2d(400,250);
   glVertex2d(450,250);
   glVertex2d(450,200);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(400,250);
    glVertex2d(425,270);

    glVertex2d(450,250);

    glEnd();
   glPopMatrix();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(415,170,0.0,"node1");
   glColor3f(0,0,0);
   drawstring(430,300,0.0,"4");
   glBegin(GL_POLYGON);                 //node 4
   glColor3f(0.0,0.0,1.0);
   glVertex2d(600,100);
   glVertex2d(600,150);
   glVertex2d(650,150);
   glVertex2d(650,100);

   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(600,150);
    glVertex2d(625,170);

    glVertex2d(650,150);

    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(615,70,0.0,"node4");
   glColor3f(0,0,0);
   drawstring(560,160,0.0,"-1");
   glBegin(GL_POLYGON);                   //node 5
   glColor3f(0.0,0.0,1.0);
   glVertex2d(800,300);
   glVertex2d(800,350);
   glVertex2d(850,350);
   glVertex2d(850,300);
   glEnd();
   glBegin(GL_TRIANGLES);
   glColor3f(0,0,0);
   glVertex2d(800,350);

    glVertex2d(825,370);
    glVertex2d(850,350);
    glEnd();
   glColor3f(0,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
   drawstring(840,380,0.0,"node5");
   glColor3f(0,0,0);
   drawstring(700,200,0.0,"6");

   glLineWidth(2);
   glColor3f(0,0,0);
   glBegin(GL_LINES);             //node 2 to node 3
   glColor3f(0.0,0.0,0.0);
   glVertex2d(450,450);
   glVertex2d(600,550);
   glEnd();



   if((anime==3) ){
    glColor3f(1,1,0);
    }
   else
    glColor3f(0.0,0.0,0.0);
   glBegin(GL_LINES);             //node 1 to node 2
   glVertex2d(425,400);
   glVertex2d(425,270);
   glEnd();





    glColor3f(0.0,0.0,0.0);
   glBegin(GL_LINES);                  //node 2 to node 5
   glVertex2d(450,400);
   glVertex2d(800,300);
   glEnd();





   if((anime==4)||(anime==5) ||(anime==6)){
    glColor3f(1,1,0);
    }
   else
    glColor3f(0.0,0.0,0.0);


   glBegin(GL_LINES);                 //node 1 to node 4
   glVertex2d(450,200);
   glVertex2d(600,100);
   glEnd();

   if((anime==4)||(anime==6) ){
    glColor3f(1,1,0);
    }
   else
    glColor3f(0.0,0.0,0.0);


   glBegin(GL_LINES);             //node 4 to node 5
   glVertex2d(650,100);
   glVertex2d(825,300);
   glEnd();

   if((anime==4) ){
    glColor3f(1,1,0);
    }
   else
    glColor3f(0.0,0.0,0.0);
   glBegin(GL_LINES);                //node 3 to node 5
   glVertex2d(825,370);
   glVertex2d(650,550);
   glEnd();



   glColor3f(1,0,0);
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   if(((anime-1)>=3))
   drawstring(20,400,0.0,"The Shortest Path From Node 1 To Node 2 -> 4");
   glColor3f(0,0,0);
                 //first iteration
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   if(((anime-1)>=4))
   drawstring(20,300,0.0,"The Shortest Path From Node 1 To Node 3 -> 3");
   glColor3f(0,0,0);
                  //first iteration
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   if(((anime-1)>=5))
   drawstring(20,200,0.0,"The Shortest Path From Node 1 To Node 4 -> -1");
   glColor3f(0,0,0);
                      //first iteration
   setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0);
   if(((anime-1)>=6))
   drawstring(20,100,0.0,"The Shortest Path From Node 1 To Node 5 -> 5");

   if(anime==2){
        Sleep(800);
        anime++;
        }
    else if(anime==3){
        if(done==0){
            x0=375;
            y00=225;
            xend=375;
            yend=420;
            make_the_man_move();
        }
        if(done==1){
            anime++;
            done=0;
        }
    }
    else if(anime==4){
        if(done==0){
            x0=375;
            y00=225;
            xend=624;
            yend=67;
            make_the_man_move();
        }
        if(done==1){
            x0=624;
            y00=67;
            xend=875;
            yend=332;
            make_the_man_move();
        }
        if(done==2){
            x0=875;
            y00=332;
            xend=624;
            yend=683;
            make_the_man_move();
        }
        if(done==3){
            anime++;
            done=0;
        }
    }
    else if(anime==5){
        if(done==0){
            x0=375;
            y00=225;
            xend=624;
            yend=67;
            make_the_man_move();
        }
        if(done==1){
            anime++;
            done=0;
        }
    }
    else if(anime==6){
        if(done==0){
            x0=375;
            y00=225;
            xend=624;
            yend=67;
            make_the_man_move();
        }
        if(done==1){
            x0=624;
            y00=67;
            xend=875;
            yend=332;
            make_the_man_move();
        }
        if(done==2){
            anime++;
            done=0;
        }
    }
    else {
        anime++;
        done=0;
        Sleep(800);
        }


}


void mouse(int btn,int state,int x,int y){
    float x1,y1;
    x1=(0.66666666667)*(float)x;
    y1=(800-(float)y)*(1.25);
    printf("%d,%d \n",x,y);
    printf("%f,%f\n",x1,y1);
    glColor3f(1,0,0);
    glBegin(GL_POINTS);
    glVertex2f((GLfloat)x1,(GLfloat)y1);
    glEnd();
    edge_x=x1;
    edge_y=y1;
}

void init(void)
{

        /*glClearColor(0.658824,0.658824,0.658824,0.8);*/
        /*glClearColor(0.372549,0.623529,0.623529,0.0);*/
        glClearColor(0.678, 0.847, 0.902,0);
        glMatrixMode(GL_PROJECTION);
        gluOrtho2D(0.0,200.0,0.0,163.0);

}
int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(10,40);
    glutInitWindowSize(1500,800);
    glutCreateWindow("BellmanFord Algorithm");
    init();
    display();
     man();


    //dot();
    glutCreateMenu(myMouse);
    glutAddMenuEntry("Home",1);
    glutAddMenuEntry("Working",2);
     glutAddMenuEntry("Window1",3);
     glutAddMenuEntry("Window2",4);
     glutAddMenuEntry("Window3",5);
     glutAddMenuEntry("Window4",6);
     glutAddMenuEntry("Window5",7);
     glutAddMenuEntry("window6",8);
     glutAddMenuEntry("window7",9);
     glutAddMenuEntry("matrix",10);




    glutAttachMenu(GLUT_RIGHT_BUTTON);
    //glutTimerFunc(20,mytimer,0);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keys);


    glutDisplayFunc(display1);

    glutMainLoop();
    glutPostRedisplay();

    return 0;
}
