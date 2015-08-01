#include <float.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <qdebug.h>
#include <map>
#include <vector>
#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1 + (IM - 1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0 - EPS)
#define MASK 123459876
#define Pc 0.7
#define Pm 0.01
long *idum;
int action_plants[]={0,1,2,-1};
int minimo=1000000;
int posminimo=0;

using namespace std;

map<int,vector<int> > arr_def;


int fila(vector<int>  arr,map<int,int> arr_zom2,vector<int>  arr_pos,int w){
    int acum=0;
    int win=1;
    while(arr_zom2.size()!=0){
        int aux1;
        for(int i=0;i<(int)arr.size();i++){
            aux1=action_plants[arr[i]];
            if(aux1>0){
                int atq=aux1;
                for(int i=0;i<(int)arr_pos.size();i++){
                    int j=arr_pos[i];
                    if(j>w)
                        break;
                    if(arr_zom2[j]>0){
                        arr_zom2[j]=arr_zom2[j]-1;
                        atq--;
                        if(atq!=0 && arr_zom2[j]>0){
                            arr_zom2[j]=arr_zom2[j]-1;
                            atq--;
                        }
                        if(arr_zom2[j]==0)
                            arr_pos.erase(arr_pos.begin()+i);
                    }
                    if(atq==0)
                        break;
                }

            }

        }
        int cont=0;
        for(int j=0;j<(int)arr_pos.size();j++){
            int i=arr_pos[j];
            if(arr_zom2[i]>0){
                cont++;
                arr_zom2[i-1]=arr_zom2[i];
                arr_pos[j]-=1;
                arr_zom2[i]=0;
                if(i-1<=4){
                    if(i-1!=1){
                        if(action_plants[arr[i-2]]!=-1){
                            arr[i-2]=0;
                        }else{
                            arr_zom2[i-1]=0;
                            arr_pos.erase(arr_pos.begin()+j);
                            j--;
                            arr[i-2]=0;
                        }
                    }else{
                        win=0;
                        break;
                    }
                }
            }
        }
        int cont1=0;
        int cont2=0;
        for(int i=0;i<(int)arr.size();i++){
            aux1=action_plants[arr[i]];
            if(aux1>0)
                cont1+=aux1;
            else
                cont2+=aux1;
        }
        if(win==0||(cont1==0&&(cont2+cont)>0)){
            acum= -1;
            break;
        }
        acum++;
        if(cont==0)
            break;
    }
    return acum;
}

int simulacion(int rnd1,int rnd2,map<int,vector<int> > arr[],map<int,int> arr_zom[],vector<int> arr_pos[],int w,int h){
    int max1=0;
    int max2=0;
    for(int i=0;i<h;i++){
        if(max1!=-1){
            int val_neg=0;
            if((action_plants[arr[rnd1][i+1][0]]==2&&action_plants[arr[rnd1][i+1][1]]==2))
                val_neg=w;
            else
                val_neg=fila(arr[rnd1][i+1],arr_zom[i+1],arr_pos[i+1],w);
            if(val_neg==-1){
                max1=-1;
            }else{
                max1=max(max1,val_neg);
            }
        }
        if(max2!=-1){
            int val_neg=0;
            if((action_plants[arr[rnd2][i+1][0]]==2&&action_plants[arr[rnd2][i+1][1]]==2))
                val_neg=w;
            else
                val_neg=fila(arr[rnd2][i+1],arr_zom[i+1],arr_pos[i+1],w);
            if(val_neg==-1){
                max2=-1;
            }else{
                max2=max(max1,val_neg);
            }
        }
    }
    if(max2>max1||max2==0){
            if(max1>0)
                minimo=min(minimo,max1);
            if( max1==minimo){
                arr_def=arr[rnd1];
                posminimo=rnd1;
            }
        return 0;
    }else{
            if(max2>0)
                minimo=min(minimo,max2);
            if(max2==minimo){
                arr_def=arr[rnd2];
                posminimo=rnd2;
            }
        return 1;
    }
}


