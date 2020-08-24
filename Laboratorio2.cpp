/*
Universidad del Valle de Guatemala
Laboratorio 2 - Calculo de la sumatoria utilizando pthread
Bryann Alfaro 19372
Referencia: Material de clase
*/

//Librerias necesarias
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

//Almacenaje del valor total

float result; //variable global para sumatoria

//Funcion para realizar impresion de cada sumatoria
void *calculo_hilo(void *numeroHilo) {
  
  //Variables locales de la funcion
  long identificadorHilo; 
  double operacion;
  identificadorHilo = (long)numeroHilo;
 
  operacion = 1.0/(((double) identificadorHilo+1)*((double) identificadorHilo+1));
  
  printf("El ciclo i numero: %d\n",(identificadorHilo+1),"esta ejecutandose");
  printf("El resultado de la operacion en este hilo es: %f\n",operacion);
  result+=operacion; //se guarda el resultado de la sumatoria
  pthread_exit(NULL);
}                      

main() {
  //Se crean las variables necesarias
  int createHilo, i, j, detachstate;
  pthread_t thread_id;
  pthread_attr_t atributo;
  int ingreso;

  pthread_attr_init(&atributo);
  pthread_attr_setdetachstate(&atributo, PTHREAD_CREATE_JOINABLE);
  
    cout<<"-----------Bienvenido al programa de sumatoria--------\n";
	cout<<"Ingrese el numero maximo de la sumatoria: ";
	cin>>ingreso;

  for (j=0; j<(ingreso); j++) {
    createHilo = pthread_create(&thread_id, &atributo, calculo_hilo, (void *)j);
    if (createHilo) {              
      printf("Error al momento de crear el hilo");
      exit(-1);
    }

    createHilo = pthread_join(thread_id, NULL);
    if (createHilo) {
      printf("Error al realizar el join del hilo");
      exit(-1);
    }
  }

  pthread_attr_destroy(&atributo);
  printf("------------EXTRA----------------\n");
  printf("La sumatoria total es : %f",result);
  pthread_exit(NULL);

}


