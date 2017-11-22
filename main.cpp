//Universidad del Valle de Guatemala
//Programaci'on de microprocesadores
//Proyecto final
//------------------------
//Ana Lucia Diaz Leppe
//Byron Mota Hernandez
//
//------------------------------------------------------------------------------------------------
//|  compilar con: g++ main.cpp bme280.cpp bme280.h sensores.cpp sensores.h -lwiringPi -o main   |
//|  ejecutar con ./main                                                                         |
//------------------------------------------------------------------------------------------------

#include <string>

#include <iostream>

#include <cstdlib>

#include "sensores.h"

//dev added

#include <stdlib.h>

#include <unistd.h>

#include <pthread.h>



#define DATASIZE 30	//data height/ display size

#define GRAPHWIDTH 20	//data width/ display size

#define GRAPHSTEP 3 //yaxis data scale

#define GREFRESH 1  //global refresh rate

#define CREFRESH 3 	//chart refresh rate


bool end = false;
float temp = 0;
float hume = 0;
float pres = 0;

pthread_mutex_t lock;

using namespace std;

int time_ticks = 0;

int avg_temp, avg_moist, avg_pres;

char chartdata [GRAPHWIDTH][DATASIZE];

const char block = 'x';


//print current temp, humidiry and pressure

void get_current_stats(){

	

	cout<<"| Temperatura | Humedad | Presion |"<<endl;

	cout<<"|";
	cout.width(8);
	cout<< getTemperatura();
	cout.width(6);
	cout<<"|";
	cout.width(6);
	cout<< getHumedad();
	cout.width(4);
	cout<<"|";
	cout.width(6);
	cout<< getPresion();
	cout.width(5);
	cout<<"|";
}



//set column height value

void set_column_height(int col, int key){

	for (int i=0; i<DATASIZE; i++){
		chartdata[i][key]='.';
	}

	for (int i=DATASIZE-col; i<DATASIZE; i++){
		chartdata[i][key]=block;
	}

}





void get_graph(int time, int value){
	set_column_height(GRAPHSTEP,0);
	set_column_height(value/GRAPHSTEP, time%DATASIZE+1);

	

	for(int i=0; i<DATASIZE; i++){

		for(int j=0; j<DATASIZE; j++){

		cout<<chartdata[i][j]<<" ";

		}

		cout<<"\n";

	}
}



int main(int argc, char* argv[]) {

	//set array to 0
  pthread_mutex_init(&lock, NULL);
  
	for(int i=0; i< DATASIZE; i++){

		for(int j=0; j<DATASIZE; j++){

			chartdata[i][j]=0;

		}

	}



  int N = 100;

	
	int i=0;
  while(true){

    // compute percentage

    cout<<"Datos Actuales :"<<endl;

	get_current_stats();

	cout<<"\nDatos Historicos:"<<endl;

	//print graph

	get_graph(i%DATASIZE,(int) floor(getTemperatura())%1000+1);

	sleep(GREFRESH);

    system("clear");

    //cout << p << endl;
	i++;
    

  }
}
/*
  void *thread_function_print(void* argument){



  while (!end) {

  



	pthread_mutex_lock(&lock);

	float tempToPrint = temp;

	float presToPrint = pres;

	float humeToPrint = hume;

	pthread_mutex_unlock(&lock);



  return 0;

}

*/

// print progress
