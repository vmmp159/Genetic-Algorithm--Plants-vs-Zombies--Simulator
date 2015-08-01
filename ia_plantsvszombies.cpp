#include "ia_plantsvszombies.h"
#include "ui_ia_plantsvszombies.h"
#include "rand.cpp"
#include <string.h>
#include <qdebug.h>
#include <map>
#include <vector>
#include <utility>
using namespace std;

IA_PlantsvsZombies::IA_PlantsvsZombies(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IA_PlantsvsZombies)
{
    ui->setupUi(this);
}

IA_PlantsvsZombies::~IA_PlantsvsZombies()
{
    delete ui;
}

void IA_PlantsvsZombies::on_pushButton_clicked()
{
    int tam =ui->spinBox->value();//Número de individuos por generación
    map<int,vector<int> >::iterator it;
    map<int,vector<int> > arr[tam];//Tablero con los N individuos por generación
    int arr_res[tam];
    QString str5 =ui->plainTextEdit->toPlainText();//Posición de los Zombies
    int str6 =ui->w->value();
    int str7 =ui->h->value();
    int str8 =ui->z->value();
    int maxim=0;
    QStringList list=str5.split(" ", QString::SkipEmptyParts);//Guardas una lista de las posiciones donde salen los Zombies
    int aux=0;//Valor utilizado para verificar que lo introducido por el usuario es valido
    if(list.size()<=10000 && list.size()>0){
        for(int i=0;i<list.size();i++){
            int pos=list[i].toInt();
            if((pos<=str7 || pos<=10000) && pos>0){
                if(pos>str7){
                    str7=pos;
                    ui->h->setValue(pos);
                }
                maxim=max(pos,maxim);
                for(int j=0;j<tam;j++){
                    if(arr[j].find(pos)==arr[j].end()){
                        vector<int> new_vec;
                        int rnd1 =((float)(rand()%4));
                        new_vec.push_back(rnd1);
                        rnd1 =((float)(rand()%4));
                        new_vec.push_back(rnd1);
                        rnd1 =((float)(rand()%4));
                        new_vec.push_back(rnd1);
                        rnd1 =((float)(rand()%4));
                        new_vec.push_back(rnd1);
                        arr[j][pos]=new_vec;
                    }else
                        break;
                }
            }else{
                aux=1;
                ui->Error->setText("Introdujo una posición que no es numérica o superior a 10000.");
                ui->Error->setStyleSheet("QLabel {  color : red; }");
                break;
            }
        }
    }else{
        aux=1;
        ui->Error->setText("Superas el número máximo de Zombies permitido que es 10000.");
        ui->Error->setStyleSheet("QLabel {  color : red; }");
    }
    if(aux==0){
        ui->Error->setText("");
        ui->Error->setStyleSheet("QLabel { }");
        ui->z->setValue(list.size());
        int gener=ui->generacion->value();
        int ciclo=(str7*4);
        map<int,int> arr_zom[str7+1];//Tablero con los Z Zombies
        vector<int> arr_pos[str7+1];//Posicion de los zombies
        for(int i=0;i<list.size();i++){
            int pos=list[i].toInt();
            arr_zom[pos][(str6+i)]=8;
            arr_pos[pos].push_back(str6+i);
        }
        for(int j=0;j<tam;j++){

            for(int i=0;i<=str7;i++){
            if(arr_pos[i].size()==0){
                vector<int> new_vec;
                new_vec.push_back(0);
                new_vec.push_back(0);
                new_vec.push_back(0);
                new_vec.push_back(0);
                arr[j][i]=new_vec;
            }
            }
        }
        for(int z=0;z<=str7;z++){
                vector<int> new_vec;
                new_vec.push_back(0);
                new_vec.push_back(0);
                new_vec.push_back(0);
                new_vec.push_back(0);
                arr_def[z]=new_vec;
        }
        minimo=10000000;
        posminimo=0;
        int rep=0;
        for(int i=0;i<gener;i++){
            map<int,vector<int> > arr2[tam];
            for(int j=0;j<tam;j++){
                int max1=0;
                for(int i=0;i<str7;i++){
                    if(max1!=-1){
                        int val_neg=0;
                        if((action_plants[arr[j][i+1][0]]==2&&action_plants[arr[j][i+1][1]]==2&&action_plants[arr[j][i+1][2]]==2&&action_plants[arr[j][i+1][3]]==2))
                            val_neg=str8;
                        else
                            val_neg=fila(arr[j][i+1],arr_zom[i+1],arr_pos[i+1],str6);
                        if(val_neg==-1){
                            max1=-1;
                        }else{
                            max1=max(max1,val_neg);
                        }
                    }
                }
                if(max1>0)
                    minimo=min(minimo,max1);
                if( max1==minimo){
                    arr_def=arr[j];
                    posminimo=j;
                }
                arr_res[j]=max1;
            }


            for(int j=0;j<tam;j++){
                int rnd1 =((float)(rand()%tam));
                int rnd2 =((float)(rand()%tam));
                if(arr_res[rnd1]<arr_res[rnd2]){
                    arr2[j]=arr[rnd1];
                }else{
                    arr2[j]=arr[rnd2];
                }
            }
            for(int j=0;j<tam;j++){
                double cambio =(double)rand()/(double)RAND_MAX;
                if(cambio<=Pc){
                    int rnd1 =((float)(rand()%tam));
                    int rnd2 =((float)(rand()%tam));
                    int rndpos =((float)(rand()%ciclo));
                    for(int z=rndpos;z<ciclo;z++){
                        int fila=(z/4)+1;
                        int columna=z%4;
                        int aux1=arr2[rnd1][fila][columna];
                        arr2[rnd1][fila][columna]=arr2[rnd2][fila][columna];
                        arr2[rnd2][fila][columna]=aux1;
                    }
                }
            }
            for(int j=0;j<tam;j++){
                for(int z=0;z<ciclo;z++){
                    double cambio =(double)rand()/(double)RAND_MAX;
                    if(cambio<=Pm){
                        int rndpos =((float)(rand()%4));
                        int fila=(z/4)+1;
                        int columna=(z%4);
                        arr2[j][fila][columna]=rndpos;
                    }
                }
                arr[j]=arr2[j];
            }

            if(i+1>=gener){
                if(minimo==10000000 && rep!=10000){
                    rep++;
                    i--;
                }
            }
        }
        qDebug()<<minimo;
        qDebug()<<posminimo;
        QString cad="";
        for(int z=1;z<=str7;z++){
            qDebug()<<arr_def[z][0]<<" "<<arr_def[z][1]<<" "<<arr_def[z][2]<<" "<<arr_def[z][3];
            cad+=QString::number(arr_def[z][0])+" "+QString::number(arr_def[z][1])+" "+QString::number(arr_def[z][2])+" "+QString::number(arr_def[z][3])+"\n";
        }
        ui->plainTextEdit_2->setPlainText(cad);
        if(rep>0 &&rep!=10000){
            ui->Error->setText("Se itero "+QString::number(rep)+" generaciones más para conseguir una solución.");
            ui->Error->setStyleSheet("QLabel {  color : blue; }");
        }
        if(rep==10000 && posminimo==0){
            ui->Error->setText("Se itero "+QString::number(rep)+" generaciones y no se consiguio una solución.");
            ui->Error->setStyleSheet("QLabel {  color : red; }");
        }
    }
}

