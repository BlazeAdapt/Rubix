#include <stdio.h>
//yellow top,blue front, yellow 0, blue 1,red2,green3,oranhge4,white5
// the numbers in the array signify the position of the block, the blocks are numbered in the usual method
//convention is clockwise
// RUfl uRRRdFDdLDULLLdBD = testcase
//small alphabet r means R'
#define CIRC(arr, i) ((arr)[((i)%(4)+(4))%(4)])

char crossP[]={'B','R','F','L'};
char crossN[]={'b','r','f','l'};
int solvedpermvert[]={0,1,2,3,4,5,6,7};
int solvedpermedge[]={0,1,2,3,4,5,6,7,8,9,10,11};
//solved all orients 0
int current_edge[]={0,1,2,3,4,5,6,7,8,9,10,11};
 int current_vert[]={0,1,2,3,4,5,6,7};
 int orientvert[]={0,0,0,0,0,0,0,0};
 int orientedge[]={0,0,0,0,0,0,0,0,0,0,0,0};
char longmoves[200];
int number_moves=0;
char temp[200];
int nmove=0;
int downs=0;
char moveset[]={'U','u','R','r','D','d','L','l','F','f','B','b'};



int find(int arr[],int x){
    int i=0;
    while(1){
        if(arr[i]==x) return i;
        i++;
    }}
int findchar(char arr[],char x){
    int i=0;
    while(1){
        if(arr[i]==x) return i;
        i++;
    }
}
void cyclenum(int arr[],int a,int b,int c,int d){
    a=find(arr,a);
    b=find(arr,b);
    c=find(arr,c);
    d=find(arr,d);
int temp= arr[a];
arr[a]=arr[b];
arr[b]=arr[c];
arr[c]=arr[d];
arr[d]=temp;
}

void orient(int arr[],int brr[],int a,int b,int c,int d,int e){
     a=find(arr,a);
    b=find(arr,b);
    c=find(arr,c);
    d=find(arr,d);
    if(e==2){
        brr[a]=(brr[a]+1)%2;
        brr[b]=(brr[b]+1)%2;
        brr[c]=(brr[c]+1)%2;
        brr[d]=(brr[d]+1)%2;
    }
    else{
        brr[a]=(brr[a]+2)%3;
        brr[b]=(brr[b]+1)%3;
        brr[c]=(brr[c]+2)%3;
        brr[d]=(brr[d]+1)%3;
    }
}



void cubemove(char x)
{
    if(x=='R'){
    orient(current_vert,orientvert,1,5,6,2,3);
    cyclenum(current_vert,1,5,6,2);
    cyclenum(current_edge,1,5,9,6);

    }
    if(x=='r'){
        orient(current_vert,orientvert,1,5,6,2,3);
        cyclenum(current_vert,2,6,5,1);
        cyclenum(current_edge,6,9,5,1);

    }
    if(x=='U'){
        cyclenum(current_vert,0,1,2,3);
        cyclenum(current_edge,0,1,2,3);
    }
    if(x=='u'){
        cyclenum(current_vert,3,2,1,0);
        cyclenum(current_edge,3,2,1,0);
    }
    if(x=='L'){
        orient(current_vert,orientvert,3,7,4,0,3);
        cyclenum(current_vert,3,7,4,0);
        cyclenum(current_edge,3,7,11,4);

    }
    if(x=='l'){
        orient(current_vert,orientvert,3,7,4,0,3);
        cyclenum(current_vert,0,4,7,3);
        cyclenum(current_edge,4,11,7,3);

    }
    if(x=='D'){
        cyclenum(current_vert,7,6,5,4);
        cyclenum(current_edge,11,10,9,8);
    }
    if(x=='d'){
        cyclenum(current_vert,4,5,6,7);
        cyclenum(current_edge,8,9,10,11);
    }
    if(x=='F'){
        orient(current_vert,orientvert,2,6,7,3,3);
        orient(current_edge,orientedge,2,6,10,7,2);
        cyclenum(current_vert,2,6,7,3);
        cyclenum(current_edge,2,6,10,7);
    }
    if(x=='f'){
        orient(current_vert,orientvert,2,6,7,3,3);
        orient(current_edge,orientedge,2,6,10,7,2);
        cyclenum(current_vert,3,7,6,2);
        cyclenum(current_edge,7,10,6,2);
    }
    if(x=='B'){
        orient(current_vert,orientvert,0,4,5,1,3);
        orient(current_edge,orientedge,0,4,8,5,2);
        cyclenum(current_vert,0,4,5,1);
        cyclenum(current_edge,0,4,8,5);
    }
      if(x=='b'){
        orient(current_vert,orientvert,0,4,5,1,3);
        orient(current_edge,orientedge,0,4,8,5,2);
        cyclenum(current_vert,1,5,4,0);
        cyclenum(current_edge,5,8,4,0);
        }
    }

void move(char x){
    printf("%c",x);
        longmoves[nmove]=(x);
        longmoves[nmove+1]='\0';
        cubemove(x);
        nmove++;
        number_moves++;
        }


void cross(int a){

    //solving blue,a=10
    if(current_edge[a]==a && !orientedge[a]){ return;};

    if(current_edge[a]==0 || current_edge[a]==1 || current_edge[a]==2 || current_edge[a]==3 ){
        printf("P");
            if(current_edge[a]!=(a-8))
                        {   int j=(a-8-current_edge[a]);
                            for(int i=0;i<((j>0)?j:-j);i++){
                            move((j>0)?'U':'u');
                           }


        }
        printf("%d",orientedge[a]);
         if(!orientedge[a]){
                printf("K");

            move(crossP[a-8]);
            move(crossP[a-8]);
            return;}
        else{
            printf("E");
            move(CIRC(crossP,a-8-1));
            move('u');
            move(CIRC(crossN,a-8-1));
            move(crossP[a-8]);
            return;
        }
    }
    if(current_edge[a]==4||current_edge[a]==5||current_edge[a]==6||current_edge[a]==7){
            //4,7 means bring to left one

        if(!orientedge[a]){
            if(current_edge[a]==4||current_edge[a]==7){
               downs=3-(a-8);//number of D'

               for(int i=0;i<downs;i++) move('d');
                if(current_edge[a]==4) move('l');
                else move('L');
               }
               else{
                downs=((1-(a-8))>=0)?(1-(a-8)):4+(1-(a-8));
                for(int i=0;i<downs;i++) move('d');
                if(current_edge[a]==6) move('r');
                else move('R');
               }
               for(int i=0;i<downs;i++) move('D');
               return;
        }
        else{
            if(current_edge[a]==4||current_edge[a]==5){
                downs=(4-(a-8))%4;
                for(int i=0;i<downs;i++) move('d');
                if(current_edge[a]==4) move('B');
                else move('b');
            }
            else{
                downs=((2-(a-8))>=0)?(2-(a-8)):4+(2-(a-8));
                for(int i=0;i<downs;i++) move('d');
                if(current_edge[a]==6) move('F');
                else move('f');
            }
            for(int i=0;i<downs;i++) move('D');
            return;

        }
    }
    else{

        move(crossP[current_edge[a]-8]);
        cross(a);
        return;
    }

return;
}

void f2lori1(int a){
    move(CIRC(crossP,current_edge[a]+1));
    move('U');
    move(crossN[current_edge[a]]);
    return;
}
void f2lori2(int a){
move(CIRC(crossN,current_edge[a]-1));
move('u');
move(crossP[current_edge[a]]);
return;
}

void f2l(int a){
    // a is the color, 6=blue+red+white;
    // corrosponding edge is also a
    if(current_vert[a]==a && orientvert[a]==0) return;

    if(current_vert[a]==0||current_vert[a]==1||current_vert[a]==2||current_vert[a]==3){

            int ups=((a-4)-current_vert[a])>=0?((a-4)-current_vert[a]):4+((a-4)-current_vert[a]);
        for(int i=0;i<ups;i++) move('U');
            if(orientvert[a]!=0){
                    printf("1");

        if(orientvert[a]==1){
            if(current_edge[a]<4){
                    printf("2");
            if(current_edge[a]==current_vert[a]){
                if((orientedge[a]==1 && a%2==0)||(orientedge[a]==0 && a%2==1)){
                    move('u');
                    move(CIRC(crossN,current_edge[a]+1));
                    move('U');
                    move(crossP[current_edge[a]]);
                    return;
                }
                else{
                        printf("koko");
                    move('U');
                    move(CIRC(crossN,current_edge[a]-1));
                    move('U');
                    move('U');
                    move(CIRC(crossP,current_edge[a]+1));
                    move('u');
                    f2lori1(a);
                    return;
                }
            }
            if((current_edge[a]==current_vert[a]+1)||current_edge[a]+3==current_vert[a]){
                if((orientedge[a]==1 && a%2==0)||(orientedge[a]==0 && a%2==1 )){
                    move('U');
                    move(CIRC(crossN,current_edge[a]+2));
                    move('u');
                    move(CIRC(crossP,current_edge[a]-1));
                    f2l(a);
                    return;
                }
                else{
                    move('u');
                    move(CIRC(crossP,current_edge[a]-1));
                    move('U');
                    move(CIRC(crossN,current_edge[a]+2));
                    move('U');
                    f2lori1(a);
                    return;

                }
            }
            if((current_edge[a]+2==current_vert[a])||(current_edge[a]==current_vert[a]+2)){
                if((orientedge[a]==0 && a%2==0)||(orientedge[a]==1 && a%2==1)){
                    f2lori1(a);
                    printf("dodo");
                    return;
                }
                else{
                        printf("momo");
                    move('U');
                    move(CIRC(crossN,current_edge[a]+1));
                    move('U');
                    move('U');
                    move(CIRC(crossP,current_edge[a]-1));
                    move('u');
                    f2l(a);
                    return;
                }
            }
            if((current_edge[a]==current_vert[a]-1)||(current_edge[a]==current_vert[a]+3)){
                if((orientedge[a]==0 && a%2==1)||(orientedge[a]==1 && a%2==0)){
                     move(crossP[current_edge[a]]);
                    move('u');
                    move(CIRC(crossN,current_edge[a]-4));
                    move('U');
                    move('U');
                    f2lori2(a);
                    return;
                }
                else{

                    move('u');
                    move(CIRC(crossP,current_edge[a]+1));
                    move('u');
                    move(CIRC(crossN,current_edge[a]+2));
                    move('U');
                    f2lori1(a);
                    return;
                }
            }
                }
                else{
                        printf("3");
            if(current_edge[a]==current_vert[a]+4){
                    printf("4");
                move(CIRC(crossP,current_vert[a]-1));
                move('u');
                move(CIRC(crossN,current_edge[a]+1));
                f2l(a);
                return;
            }
            if((current_edge[a]==current_vert[a]+5)||(current_edge[a]==current_vert[a]+1)){
                printf("5");
                move(CIRC(crossN,current_vert[a]+1));
                move('u');
                move(CIRC(crossP,current_edge[a]+1));
                f2l(a);
                return;
            }
            if((current_edge[a]==current_vert[a]+2)||current_edge[a]==current_vert[a]+6){
                printf("6");
                move(CIRC(crossP,current_vert[a]+1));
                move('u');
                move(CIRC(crossN,current_edge[a]+1));
                f2l(a);
                return;
            }
            if((current_edge[a]==current_vert[a]+3)||current_edge[a]==current_vert[a]+7){
                printf("7");
                move(CIRC(crossP,current_vert[a]+2));
                move('U');
                move(CIRC(crossN,current_edge[a]-1));
                f2l(a);
                return;
            }
        }
      }
      else if(orientvert[a]==2){
            printf("9");
            if(current_edge[a]<4){
                    printf("**");
            if((current_edge[a]==current_vert[a]-1)||(current_edge[a]==current_vert[a]+3)){
                if((orientedge[a]==0 && a%2==0)||(orientedge[a]==1 && a%2==1)){
                        printf("X");
                        // old was u,N[a]+1,U,P[a]
                        //new is U,P[a]-1,u,N[a]
                    move('U');
                    move(CIRC(crossP,current_edge[a]-1));
                    move('u');
                    move(crossN[current_edge[a]]);
                    return;
                }
                else{
                    //expected = u, P[a]+1 u u N[a]-1 U f2lori2 BOMBOCLAT
                    move('u');
                    move(CIRC(crossP,current_edge[a]+1));
                    move('u');
                    move('u');
                    move(CIRC(crossN,current_edge[a]-1));
                    move('U');
                    f2lori2(a);
                    return;
                }//fixed
            }
            if((current_edge[a]+2==current_vert[a])||(current_edge[a]==current_vert[a]+2)){
                    printf("Y");
                if((orientedge[a]==0 && a%2==0)||(orientedge[a]==1 && a%2==1 )){
                    move('u');
                    move(CIRC(crossP,current_edge[a]+2));
                    move('U');
                    move(CIRC(crossN,current_edge[a]+1));
                    f2l(a);//fixed
                    return;
                }
                else{
                    move('U');
                    move(CIRC(crossN,current_edge[a]+1));
                    move('u');
                    move(CIRC(crossP,current_edge[a]+2));
                    move('u');
                    f2lori2(a);//fixed
                    return;

                }
            }
            if((current_edge[a]+3==current_vert[a])||(current_edge[a]==current_vert[a]+1)){
                    printf("Z");
                if((orientedge[a]==1 && a%2==0)||(orientedge[a]==0 && a%2==1)){
                        printf("!");
                    f2lori2(a);
                    return;
                }
                else{
                    printf("@");
                    move('u');
                    move(CIRC(crossP,current_edge[a]-1));
                    move('u');
                    move('u');
                    move(CIRC(crossN,current_edge[a]+1));
                    move('U');
                    f2l(a);//fixwed
                    return;
                }
            }
            if(current_edge[a]==current_vert[a]){
                printf("O%d",a);
                if((orientedge[a]==0 && a%2==0)||(orientedge[a]==0 && a%2==0)){

                    move(crossN[current_edge[a]]);
                    move('U');
                    move(CIRC(crossP,current_vert[a]-2));
                    move('u');
                    move('u');
                    f2lori1(a);//fixed
                    return;
                }
                else{

                     move('U');
                    move(CIRC(crossN,current_edge[a]-1));
                    move('U');
                    move(CIRC(crossP,current_edge[a]+2));
                    move('u');
                    f2lori2(a);//fixed
                    return;
                }
            }
                }
                else{
                        printf("##");
            if(current_edge[a]==current_vert[a]+4){
                move(CIRC(crossP,current_vert[a]-1));
                move('u');
                move(CIRC(crossN,current_edge[a]+1));
                f2l(a);
                return;
            }
            if((current_edge[a]==current_vert[a]+5)||(current_edge[a]==current_vert[a]+1)){
                move(CIRC(crossN,current_vert[a]+1));
                move('u');
                move(CIRC(crossP,current_edge[a]+1));
                f2l(a);
                return;
            }
            if((current_edge[a]==current_vert[a]+2)||current_edge[a]==current_vert[a]+6){
                move(CIRC(crossP,current_vert[a]+1));
                move('u');
                move(CIRC(crossN,current_edge[a]+1));
                f2l(a);
                return;
            }
            if((current_edge[a]==current_vert[a]+3)||current_edge[a]==current_vert[a]+7){
                move(CIRC(crossP,current_vert[a]+2));
                move('U');
                move(CIRC(crossN,current_edge[a]-1));
                f2l(a);
                return;
            }
        }
      }
    }
    else{
        move(CIRC(crossP,current_vert[a]-1));
        move('u');
        move(CIRC(crossN,current_vert[a]+1));
        f2l(a);
        return;
    }
}
else{
    if(orientvert[a]==0||orientvert[a]==2){
        move(CIRC(crossN,current_vert[a]-4));
        move('U');
        move(CIRC(crossP,current_vert[a]-1));
        f2l(a);
        return;
    }
    else{
        move(CIRC(crossP,current_vert[a]-5));
        move('u');
        move(CIRC(crossN,current_vert[a]));
        f2l(a);
        return;
    }
}
}

void f2edge(int a){
    printf("A ");
    if(current_edge[a]==a && orientedge[a]==0) return;
    if(current_edge[a]==0||current_edge[a]==1||current_edge[a]==2||current_edge[a]==3){
        if((a%2==0 && orientedge[a]==1)||(a%2==1 && orientedge[a]==0)){
            while(current_edge[a]!=a-4) move('U');
            move('U');
            move(CIRC(crossP,current_edge[a]+2));
            move('u');
            move(CIRC(crossN,current_edge[a]-1));
            f2l(a);
            return;
        }
        else{
            while(current_edge[a]!=((a-5>=0)?(a-5):(a-1))) move('U');
            move('u');
            move(CIRC(crossN,current_edge[a]+2));
            move('U');
            move(CIRC(crossP,current_edge[a]+1));
            f2l(a);
            return;
        }

    }
    else{
        move(crossN[current_edge[a]-4]);
        move('U');
        move(CIRC(crossP,current_edge[a]-1));
        f2l(a);
        return;
    }
}
void oll(){
    if(orientedge[0]==1 && orientedge[1]==1 && orientedge[2]==1 && orientedge[3]==1){
        move('F');move('R');move('U');move('r');move('u');move('f');
    }
    for(int i=0;i<4;i++){
            printf("M");
        if(orientedge[find(current_edge,i)]==0 && orientedge[find(current_edge,(i+1)%4)]==1 && orientedge[find(current_edge,(i+2)%4)]==0){
                printf("aa");
            move(CIRC(crossP,i+1));
            move(crossP[i]);
            move('U');
            move(crossN[i]);
            move('u');
            move(CIRC(crossN,i+1));
            break;
        }
        else if(orientedge[find(current_edge,i)]==0 && orientedge[find(current_edge,(i+1)%4)]==0 && orientedge[find(current_edge,(i+2)%4)]==1){
            printf("mm");
            move(CIRC(crossP,i-1));
            move('U');
            move(CIRC(crossP,i+2));
            move('u');
            move(CIRC(crossN,i+2));
            move(CIRC(crossN,i-1));
            break;
        }
    }

    printf("ollcross");
    for(int i=0;i<8;i++) printf("%d  ",orientvert[i]);
     for(int i=0;i<4;i++){
        if(orientvert[find(current_vert,i)]==2 && orientvert[find(current_vert,(i+1)%4)]==2 && orientvert[find(current_vert,(i+2)%4)]==1){
            move(CIRC(crossP,i-1));
            move('U');
            move('U');
            move(CIRC(crossP,i-1));
            move(CIRC(crossP,i-1));
            move('u');
            move(CIRC(crossP,i-1));
            move(CIRC(crossP,i-1));
            move('u');
            move(CIRC(crossP,i-1));
            move(CIRC(crossP,i-1));
            move('U');
            move('U');
            move(CIRC(crossP,i-1));
            break;
        }
        else if(orientvert[find(current_vert,i)]==1 && orientvert[find(current_vert,(i+1)%4)]==2 && orientvert[find(current_vert,(i+2)%4)]==1){
            move(CIRC(crossP,i-1));
            move('U');
            move(CIRC(crossN,i-1));
            move('U');
            move(CIRC(crossP,i-1));
            move('u');
            move(CIRC(crossN,i-1));
            move('U');
            move(CIRC(crossP,i-1));
            move('U');
            move('U');
            move(CIRC(crossN,i-1));
            break;
            }
        else if(orientvert[find(current_vert,i)]==1 && orientvert[find(current_vert,(i+1)%4)]==1 && orientvert[find(current_vert,(i+2)%4)]==1){
            move(CIRC(crossP,i-1));
            move('U');
            move('U');
            move(CIRC(crossN,i-1));
            move('u');
            move(CIRC(crossP,i-1));
            move('u');
            move(CIRC(crossN,i-1));
            break;
                }
        else if(orientvert[find(current_vert,i)]==2 && orientvert[find(current_vert,(i+1)%4)]==0 && orientvert[find(current_vert,(i+2)%4)]==2){
            move(CIRC(crossP,i-1));
            move('U');
            move(CIRC(crossN,i-1));
            move('U');
            move(CIRC(crossP,i-1));
            move('U');
            move('U');
            move(CIRC(crossN,i-1));
            break;
                }
        else if(orientvert[find(current_vert,i)]==0 && orientvert[find(current_vert,(i+1)%4)]==1 && orientvert[find(current_vert,(i+2)%4)]==0){
            move(crossP[i]);
            move(CIRC(crossN,i-1));
            move(crossN[i]);
            move(CIRC(crossP,i+1));
            move(crossP[i]);
            move(CIRC(crossP,i-1));
            move(crossN[i]);
            move(CIRC(crossN,i+1));
            break;
        }
        else if(orientvert[find(current_vert,i)]==0 && orientvert[find(current_vert,(i+1)%4)]==1 && orientvert[find(current_vert,(i+2)%4)]==2){
            move(CIRC(crossP,i+1));
            move(crossP[i]);
            move(CIRC(crossN,i-1));
            move(crossN[i]);
            move(CIRC(crossN,i+1));
            move(crossP[i]);
            move(CIRC(crossP,i-1));
            move(crossN[i]);
            break;
        }
        else if(orientvert[find(current_vert,i)]==2 && orientvert[find(current_vert,(i+1)%4)]==1 && orientvert[find(current_vert,(i+2)%4)]==0){
            move(CIRC(crossP,i-1));
            move(CIRC(crossP,i-1));
            move('D');
            move(CIRC(crossN,i-1));
            move('U');
            move('U');
            move(CIRC(crossP,i-1));
            move('d');
            move(CIRC(crossN,i-1));
            move('U');
            move('U');
            move(CIRC(crossN,i-1));
            break;
        }
    printf("%d ",i);

    }
}

void pll(){
    printf("start");
    if((current_vert[0]+1)%4==current_vert[1] && (current_vert[0]+2)%4==current_vert[2]) printf("A");
    else if((current_vert[0]+2)%4==current_vert[2]){
        printf("B");
        move('F');
        move('R');
        move('u');
        move('r');
        move('u');
        move('R');
        move('U');
        move('r');
        move('f');
        move('R');
        move('U');
        move('r');
        move('u');
        move('r');
        move('F');
        move('R');
        move('f');
    }
    else{
            printf("C");
        for(int i=0;i<4;i++){
            if(current_vert[(find(current_vert,i)+1)%4]==(i+1)%4){
                    printf("i =%d",i);
                move(CIRC(crossP,i-2));
                move('U');
                move(CIRC(crossN,i-2));
                move('u');
                move(CIRC(crossN,i-2));
                move(CIRC(crossP,i-1));
                move(CIRC(crossP,i-2));
                move(CIRC(crossP,i-2));
                move('u');
                move(CIRC(crossN,i-2));
                move('u');
                move(CIRC(crossP,i-2));
                move('U');
                move(CIRC(crossN,i-2));
                move(CIRC(crossN,i-1));
                break;
            }
        }
    }
    while(current_vert[0]!=0) move('U');
    printf("pt2 ");

    if(current_edge[0]==0 && current_edge[1]==1);
    else if(current_edge[0]==2 && current_edge[1]==3){
        move('R');
        move('R');
        move('l');
        move('l');
        move('D');
        move('R');
        move('R');
        move('l');
        move('l');
        move('U');
        move('U');
        move('R');
        move('R');
        move('l');
        move('l');
        move('D');
        move('R');
        move('R');
        move('l');
        move('l');
    }
    else{
        for(int i=0;i<4;i++){
            if (current_edge[i]==i){
                if(CIRC(current_edge,i+1)==(i+2)%4){
                    move(CIRC(crossP,i+1));
                    move('u');
                    move(CIRC(crossP,i+1));
                    move('U');
                    move(CIRC(crossP,i+1));
                    move('U');
                    move(CIRC(crossP,i+1));
                    move('u');
                    move(CIRC(crossN,i+1));
                    move('u');
                    move(CIRC(crossP,i+1));
                    move(CIRC(crossP,i+1));
                    return;
                }
                else{
                    move(CIRC(crossP,i+1));
                    move(CIRC(crossP,i+1));
                    move('U');
                    move(CIRC(crossP,i+1));
                    move('U');
                    move(CIRC(crossN,i+1));
                    move('u');
                    move(CIRC(crossN,i+1));
                    move('u');
                    move(CIRC(crossN,i+1));
                    move('U');
                    move(CIRC(crossN,i+1));
                    return;
                }
            }
        }
        if(current_edge[0]==1){
            move('r');
            move('L');
            move('F');
            move('r');
            move('r');
            move('L');
            move('L');
            move('B');
            move('r');
            move('r');
            move('L');
            move('L');
            move('F');
            move('r');
            move('L');
            move('D');
            move('D');
            move('r');
            move('r');
            move('L');
            move('L');
            move('u');
        }
        else{
            move('r');
            move('L');
            move('f');
            move('r');
            move('r');
            move('L');
            move('L');
            move('b');
            move('r');
            move('r');
            move('L');
            move('L');
            move('f');
            move('r');
            move('L');
            move('D');
            move('D');
            move('r');
            move('r');
            move('L');
            move('L');
            move('U');
        }

    }



}


void solvecross(){
cross(8);
printf("onedone");
cross(9);printf("2done");
cross(10);printf("3done");
cross(11);
}
void solvef2l(){
    while((current_vert[4]!=4||current_vert[5]!=5||current_vert[6]!=6||current_vert[7]!=7)||(orientvert[4]!=0 || orientvert[5]!=0 || orientvert[6]!=0 ||orientvert[7]!=0)){
        f2l(4);printf("first done");
        f2l(5);printf("second done");
        f2l(6);printf("third done");
        f2l(7);
         printf("check");

    }
    while((current_edge[4]!=4||current_edge[5]!=5||current_edge[6]!=6||current_edge[7]!=7)||(orientedge[4]!=0 || orientedge[5]!=0 || orientedge[6]!=0 ||orientedge[7]!=0)){
        f2edge(4);
        f2edge(5);
        f2edge(6);
        f2edge(7);
        printf("problemo");
    }
}

void reducemoves(){
    int i=0;
    int k=0;
    int changes=0;
    do{
            changes=0;
    while(longmoves[i]!='\0'){
        if((i<number_moves-3) &&(longmoves[i]==longmoves[i+1] && longmoves[i+1]==longmoves[i+2] && longmoves[i+2]==longmoves[i+3])){ i+=4; changes+=4;}
        if((i<number_moves-2)&&(longmoves[i]==longmoves[i+1] && longmoves[i+1]==longmoves[i+2])){
            longmoves[k]=(findchar(moveset,longmoves[i])%2==0)? moveset[findchar(moveset,longmoves[i])+1]:moveset[findchar(moveset,longmoves[i])-1];
            i+=3;
            k++;
            changes+=2;
        }
        if((i<number_moves-1)&&(findchar(moveset,longmoves[i])%2==0)?(findchar(moveset,longmoves[i+1])==findchar(moveset,longmoves[i])+1):(findchar(moveset,longmoves[i+1])==findchar(moveset,longmoves[i])-1)){
            i+=2;
            changes++;}
        else{
            longmoves[k]=longmoves[i];
            i++;
            k++;
        }
    }
    number_moves-=changes;
    longmoves[k]='\0';
    i=0;
    k=0;
    }while(changes);
    return;
}


    int main(){
    move('F');
    move('r');move('L');move('f');move('u');move('F');move('L');
   // for(int i=0;i<12;i++) printf("%d ",current_edge[i]);
    // printf(" ");

    solvecross();
    printf("crossdone ");
    solvef2l();
    oll();
    pll();
for(int i=0;i<8;i++) printf("%d  ",current_vert[i]);
printf("\n");
    printf("%s\n",longmoves);
    reducemoves();
    printf("%s\n",longmoves);

    }

