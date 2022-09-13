
  /////////////////////////////////////////
 //				LIBRERÍAS				//
/////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROJO_T     	   	"\x1b[31m"
#define VERDE_T        	"\x1b[32m"
#define AMARILLO_T 	   	"\x1b[33m"
#define AZUL_T     		"\x1b[34m"
#define MAGENTA_T  		"\x1b[35m"
#define CYAN_T     		"\x1b[36m"
#define RESET_COLOR    	"\x1b[0m"
#define TAM 99


  /////////////////////////////////////////
 //		 DECLARACIÓN DE FUNCIONES		//
/////////////////////////////////////////

int menu (void);
int comprueba_num_en_carton(int *vector, int tam, int num);
void pone_blancos_carton(int* matriz, int f, int c, int b);
void pone_blancos_carton_manual(int* matriz, int f, int c, int b);
void pone_nums_carton(int* matriz, int f, int c, int b);
void pone_nums_carton_manual(int* matriz, int f, int c, int b);
void ordena_vector(int *vector, int tam);
void imprime_carton(int* matriz, int f, int c);
void juego_bingo(int eleccion);
void jugar_ordenador(int f, int c, int b);
void jugar_usuarios(int f, int c, int b);
void generarTablero(int* matriz, int f, int c, int b);
void generarTableroAutomatico(int* matriz, int f, int c, int b);
void inicializa_vector(int *vector, int tam);
void inicializar_carton(int* matriz, int f, int c);
void jugar(int *carton1,int *carton2, int f, int c);
int	comprobar_ganador(int* carton, int f, int c);
int	comprobar_fila(int* carton, int f, int c);
void comprueba_carton(int* carton, int f, int c, int num, int numCarton);
int comprueba_si_ha_salido_bola(int num, int *vector);
void ordena_carton(int *carton, int f, int c);



  /////////////////////////////////////////
 //		 FUNCIÓN PRINCIPAL MAIN			//
/////////////////////////////////////////

int main (){

	//Declaración de variables
	int opcion;

	//Inicializo la semilla
	srand(time(NULL));

	//Imprimo mensaje

	printf(CYAN_T "\n\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");	
	printf("\n\t~ ¡¡Bienvenido al programa Juego Bingo!! ~");
	printf("\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" RESET_COLOR);

	//Repito si la opcion es distinta de 3
	do{
		//Llamo a la función menú
		opcion = menu();

		//Llamo a la función juego bingo
		if(opcion == 1 || opcion == 2)
			juego_bingo(opcion);

	}while(opcion != 3);

	printf("\n----------------------------------------------------------------\n");
	//Imprimo mensaje de despedida
	printf(CYAN_T "\n\n\t¡Hasta la próxima!\n\n"RESET_COLOR);

	//Fin del programa
	return 0;
}


  /////////////////////////////////////////
 //	  FUNCIÓN COMPRUEBA NUM EN CARTON	//
/////////////////////////////////////////

int comprueba_num_en_carton(int *vector, int tam, int num){

	//Declaración de variables
	int cont = 0;

	while(cont < TAM){
		if(*(vector + cont) == num){
			return 1;
		}
		else if(*(vector + cont) == 0){
			return 0;
		}
		cont++;
	}

	return 0;
}


  /////////////////////////////////////////
 //			   FUNCIÓN MENÚ				//
/////////////////////////////////////////

int menu (void){

	//Declaración de variables
	int opcion;

	//Imprimo el mensaje
	printf("\n---------------------------------------------------------\n");
	printf("\nPor favor, seleccione una opción de juego: ");
	printf("\n\t1. Jugar contra el ordenador.");
	printf("\n\t2. Jugar contra otro usuario.");
	printf("\n\t3. Salir del programa.");
	printf("\n\tLa opción seleccionada es: ");

	//Leo el número introducido
	scanf("%d", &opcion);

	while(getchar() != '\n'){
		printf(ROJO_T "\n\nError." RESET_COLOR " La opción seleccionada debe ser un número.\n");
		opcion = 0;
	}

	//Si no es correcto imprimo un error
	if(opcion < 1 || opcion > 3){
		printf(ROJO_T "\n\nError." RESET_COLOR " La opción seleccionada debe estar entre 1 y 3.\n");
	}

	//Devuelvo el valor
	return opcion;
}


  /////////////////////////////////////////
 //	   FUNCIÓN PON BLANCOS EN CARTON    //
/////////////////////////////////////////

void pone_blancos_carton(int* matriz, int f, int c, int b){

	//Declaración de variables
	int i, j, aleatorio;

	//Recorremos el cartón para poner los blancos
	for(i = 0; i < f; i++){
		for(j = 0; j < b; j++){
			aleatorio = 0;
			aleatorio = (rand() % c);

			if(*(matriz + i * c + aleatorio) != -1){

				*(matriz + i * c + aleatorio) = -1;
			}
			else{
				j--;
			}
		}
	}
}


  //////////////////////////////////////////
 // FUNCIÓN PON BLANCOS EN CARTON MANUAL //
//////////////////////////////////////////

void pone_blancos_carton_manual(int* matriz, int f, int c, int b){

	//Declaración de variables
	int pos, i, j;

	printf("\n\nVamos a introducir las posiciones de los blancos en el cartón. \n\tLas posiciones deben ir de la 1 a la %d.\n\tRecuerda que no puedes introducir 2 blancos en la misma posición. \nEmpezamos a introducir las posiciones: \n", c);
	
	for(i = 0; i < f; i++){
		for(j = 0; j < b; j++){
			printf("\n\tIntroduce la posicion del blanco de la fila %d: ", i + 1);
			scanf("%d", &pos);

			pos--;

			if((pos >= 0) && (pos < c)){
			
				if(*(matriz + i * c + pos) != -1){
					*(matriz + i * c + pos) = -1;
				}
				else{
					printf(ROJO_T "\n\nError." RESET_COLOR " No se pueden introducir dos blancos en la misma posición.\n");
					j--;
				}
			}
			else{
				printf(ROJO_T "\n\nError." RESET_COLOR " La posicion de los blancos debe existir.\n");
				j--;
			}
		}
	}
}


  /////////////////////////////////////////
 //	  	FUNCIÓN PON NUMS EN CARTON		//
/////////////////////////////////////////

void pone_nums_carton(int* matriz, int f, int c, int b){

	//Declaración de variables
	int i, j, k, l, aleatorio, existe;

	//Recorremos el cartón para poner los blancos
	for(i = 0; i < f; i++){
		for(j = 0; j < c; j++){

			aleatorio = 0;

			//Si la posición tiene un 0
			if(*(matriz + i * c + j) == 0){

				aleatorio = (rand() % 99) + 1;
				existe = 0;

				//Comprobamos si ya existe ese número en el cartón
				for(k = 0; k <= i; k++){
					for(l = 0; l < c; l++){
						if(*(matriz + k * c + l) == aleatorio){
							existe = 1;
							k = f + 1;
							l = c + 1;
						}
					}
				}

				if(existe == 0){
					*(matriz + i * c + j) = aleatorio;
				}
				else{
					j--;
					if(j < 0){
						i--;
					}
				}
			}
			
		}
	}
}


  /////////////////////////////////////////
 //	 FUNCIÓN PON NUMS EN CARTON MANUAL	//
/////////////////////////////////////////

void pone_nums_carton_manual(int* matriz, int f, int c, int b){

	//Declaración de variables
	int numero, i, j, *vector, tam, cont;

	cont = 0;

	tam = ((f * c) - (f * b));

	vector = (int *)malloc(tam * sizeof(int));

	inicializa_vector(vector, tam);

	//Inserto números de forma manual
	printf("\n\nVamos a introducir los números en el cartón. \n\tLos números deben ir del 1 al 99.\n\tRecuerda que da igual el orden, luego los ordenaremos.\nEmpezamos a introducir los números: \n");
	for(i = 0; i < c; i++){ 
		for(j = 0; j < f; j++){
			if(*(matriz + j * c + i) != -1){
				printf("\n\tIntroduzce un número: ");
				scanf("%d", &numero);

				if((numero > 99) || (numero <= 0)){
					printf(ROJO_T "\n\nError." RESET_COLOR " El número introducido no es válido.\n");
					j--;
				}
				else if(comprueba_num_en_carton(vector, tam, numero) == 0){
					*(matriz + j * c + i) = numero;
					*(vector + cont) = numero;
					cont++;
				}
				else{
					printf(ROJO_T "\n\nError." RESET_COLOR " El número introducido ya se encuentra en el cartón.\n");
					j--;
				}
			}
		}
	}
	//Liberamos memoria
	free(vector);
}


  /////////////////////////////////////////
 //	  	   FUNCIÓN ORDENA VECTOR		//
/////////////////////////////////////////

void ordena_vector(int *vector, int tam){

	//Declaración de variables
	int i, j, tmp;

	for (i = 0; i < tam; i++) {
        for (j = 0; j < tam - i - 1; j++) {
        	tmp = 0;
            if(vector[j] > vector[j + 1]){
                tmp = vector[j + 1];
                vector[j + 1] = vector[j];
                vector[j] = tmp;
            }
        }
    }
}


  /////////////////////////////////////////
 //	  	  FUNCIÓN IMPRIME CARTON		//
/////////////////////////////////////////

void imprime_carton(int* matriz, int f, int c){

	//Declaración de variables
	int i, j;

	//Recorro la matriz para imprimirla
	for (i = 0; i < f; i++){
		printf("\n");
	    for (j = 0; j < c; j++){
	    	if(((i % 2 == 0) && (j % 2 != 0)) || ((i % 2 != 0) && (j % 2 == 0))){
				if(*(matriz + i * c + j) == -1){
		            printf(MAGENTA_T "|  X |" RESET_COLOR);
		        }
		        else if(*(matriz + i * c + j) == -2){
		            printf(MAGENTA_T "|  $ |" RESET_COLOR);
		        }
		        else if(*(matriz + i * c + j) < 10 ){
		            printf(MAGENTA_T "|  %d |" RESET_COLOR, *(matriz + i * c + j));
		        }
		        else{
		            printf(MAGENTA_T "| %d |" RESET_COLOR, *(matriz + i * c + j));
		        }
	    	}
	    	else{
	    		if(*(matriz + i * c + j) == -1){
		            printf("|  X |");
		        }
		        else if(*(matriz + i * c + j) == -2){
		            printf("|  $ |");
		        }
		        else if(*(matriz + i * c + j) < 10 ){
		            printf("|  %d |", *(matriz + i * c + j));
		        }
		        else{
		            printf("| %d |", *(matriz + i * c + j));
		        }
	    	}        
	    }
	}

	printf("\n");
}


  /////////////////////////////////////////
 //	  		FUNCIÓN JUEGO BINGO 		//
/////////////////////////////////////////

void juego_bingo(int eleccion){

	//Declaración de variables
	int jugar, filas, columnas, blancos, numsCarton;

	numsCarton = 99;

	do{
		printf("\n----------------------------------------------------------------\n");
		printf("\nIntroduce el número de filas del carton: ");
		scanf("%d", &filas);

		if(filas <= 0){
			printf(ROJO_T "\nError." RESET_COLOR " El número de filas introducido no es válido.\n");
		}
		else{
			printf("\nIntroduce el número de columnas del cartón: ");
			scanf("%d", &columnas);

			if(columnas <= 0){
				printf(ROJO_T "\nError." RESET_COLOR " El número de columnas introducido no es válido.\n");
			}
			else{
				printf("\nIntroduce el número de blancos por fila: ");
				scanf("%d", &blancos);

				if(blancos < 0 || blancos > columnas){
					printf(ROJO_T "\nError." RESET_COLOR " El número de blancos debe ser positivo y menor que el número de columnas.\n");
				}
				else {

					numsCarton = (columnas * filas) - (filas * blancos);

					if(numsCarton >= 99){
						printf(ROJO_T "\nError." RESET_COLOR " El cartón tiene demasiados números.\n");
					}
					else{
						printf("\nEl cartón tendrá %d filas, %d columnas y %d blancos por fila.\n", filas, columnas, blancos);
					}
				}
			}
		}
	}while(numsCarton >= 99);
	
	printf("\n----------------------------------------------------------------\n");	

	if(eleccion == 1){

		printf(CYAN_T "\nComienza el Juego Automático (ordenador vs ordenador)." RESET_COLOR);
		printf("\n----------------------------------------------------------------\n");	
		jugar_ordenador(filas, columnas, blancos);
	}
	else{

		printf(CYAN_T "\nComienza el Juego Manual (usuario vs usuario)." RESET_COLOR);
		
		jugar_usuarios(filas, columnas, blancos);
	}
}


  /////////////////////////////////////////
 //	  	  FUNCIÓN JUGAR ORDENADOR		//
/////////////////////////////////////////

void jugar_ordenador(int f, int c, int b){

	//Declaración de variables
	int *carton1, *carton2, i;

	//CARTON 1
	carton1 = (int *)malloc(f * c * sizeof(int));

	//CARTON 2
	carton2 = (int *)malloc(f * c * sizeof(int));

	printf("\n**************************************************************");
	printf("\n\nLos cartones con los que vamos a jugar son: \n");
	//Genero el tablero de forma automática
	printf(VERDE_T "\nCartón 1: \n" RESET_COLOR);
	generarTableroAutomatico(carton1, f, c, b);
	printf(AMARILLO_T "\nCartón 2: \n" RESET_COLOR);
	generarTableroAutomatico(carton2, f, c, b);

	//Jugamos al bingo
	printf("\n**************************************************************");
	printf("\n\nEmpezamos a jugar:");
	jugar(carton1, carton2, f, c);
}


  /////////////////////////////////////////
 //	  	  FUNCIÓN JUGAR USUARIOS		//
/////////////////////////////////////////

void jugar_usuarios(int f, int c, int b){

	//Declaración de variables
	int *carton1, *carton2, i;

	//CARTON 1
	carton1 = (int *)malloc(f * c * sizeof(int));

	//CARTON 2
	carton2 = (int *)malloc(f * c * sizeof(int));

	printf("\n**************************************************************");
	printf("\n\nLos cartones con los que vamos a jugar son: \n");
	//Genero el tablero de forma automática
	printf(VERDE_T "\\nCartón 1: \n" RESET_COLOR);
	generarTablero(carton1, f, c, b);
	printf(AMARILLO_T "\n\nCartón 2: \n" RESET_COLOR);
	generarTablero(carton2, f, c, b);

	//Jugamos al bingo
	printf("\n**************************************************************");
	printf("\n\nEmpezamos a jugar:");
	jugar(carton1, carton2, f, c);
}


  /////////////////////////////////////////
 //	  	  FUNCIÓN GENERAR TABLERO		//
/////////////////////////////////////////

void generarTablero(int* matriz, int f, int c, int b){

	//Declaración de variables
	int i, j;

	//Inicializo la matriz a 0.
	inicializar_carton(matriz, f, c);

    //Pongo los blancos
    pone_blancos_carton_manual(matriz, f, c, b);

    //Pongo los números en el cartón
    pone_nums_carton_manual(matriz, f, c, b);

    //Ordeno el cartón de menor a mayor
    ordena_carton(matriz, f, c);

    //Imprimo el cartón
    imprime_carton(matriz, f, c);
}


  /////////////////////////////////////////
 //	FUNCIÓN GENERAR TABLERO AUTOMATICO	//
/////////////////////////////////////////

void generarTableroAutomatico(int* matriz, int f, int c, int b){

	//Declaración de variables
	int i, j;

	//Inicializo la matriz a 0.
	inicializar_carton(matriz, f, c);

    //Pongo los blancos
    pone_blancos_carton(matriz, f, c, b);

    //Pongo los números en el cartón
    pone_nums_carton(matriz, f, c, b);

    //Ordeno el cartón de menor a mayor
    ordena_carton(matriz, f, c);

    //Imprimo el cartón
    imprime_carton(matriz, f, c);
}


  /////////////////////////////////////////
 //	  	 FUNCIÓN INICIALIZA VECTOR		//
/////////////////////////////////////////

void inicializa_vector(int *vector, int tam){

	//Declaración de variables
	int i;

	//Recorro el vector para inicializarlo
	for(i = 0; i < tam; i++){
		*(vector + i) = 0;
	}
}


  /////////////////////////////////////////
 //	  	 FUNCIÓN INICIALIZA CARTON		//
/////////////////////////////////////////

void inicializar_carton(int* matriz, int f, int c){

	//Declaración de variables
	int i, j;

	//Inicializo la matriz a 0.
	for (i = 0; i < f; i++)
        for(j = 0; j < c; j++)
            *(matriz + i * c + j) = 0;
}


  /////////////////////////////////////////
 //	  		   FUNCIÓN JUGAR			//
/////////////////////////////////////////

void jugar(int *carton1,int *carton2, int f, int c){

	//Declaración de variables
	int *vector, i, k, aleatorio, existe, linea1, linea2, bingo1, bingo2;
	int linea = 0;
	int ganador = 0;

	vector = (int *)malloc(TAM * sizeof(int));

	//Inicializo el vector a 0
	inicializa_vector(vector, TAM);

	for(i = 0; i < TAM && ganador == 0; i++){
		existe = 0;
		aleatorio = 0;
		aleatorio = (rand() % TAM) + 1;	//Los números van del 1 al 99

		existe = comprueba_si_ha_salido_bola(aleatorio, vector);

		//Si no existe el número en el vector
		if(existe == 0){	

			//printf("\n\tHA SALIDO EL NÚMERO %d.\n", aleatorio);
			*(vector + i) = aleatorio;

			ordena_vector(vector, i);

			//Compruebo los cartones
			comprueba_carton(carton1, f, c, aleatorio, 1);
			comprueba_carton(carton2, f, c, aleatorio, 2);

			//Si aún no han cantado linea
			if(linea == 0){

				linea1 = comprobar_fila(carton1, f, c);
				linea2 = comprobar_fila(carton2, f, c);

				//Tenemos 3 opciones:
				if(linea1 == 1){
					//Cantan los 2 a la vez
					if(linea2 == 1){
						printf("\n\nHan cantado " AZUL_T "LINEA" RESET_COLOR " en ambos cartones cuándo llevamos %d bolas.\n", i + 1);
						linea = 3;
					}
					else{	//Sólo el cartón 1
						printf("\n\nHan cantado " AZUL_T "LINEA" RESET_COLOR " en el " VERDE_T "cartón 1" RESET_COLOR " cuándo llevamos %d bolas.\n", i + 1);
						linea = 3;
					}
					linea = 3;
				}	//Sólo el cartón 2
				else if(linea2 == 1){
					printf("\n\nHan cantado " AZUL_T "LINEA" RESET_COLOR " en el " AMARILLO_T "cartón 2" RESET_COLOR " cuándo llevamos %d bolas.\n", i + 1);
					linea = 3;
				}
			}
			else{	//Comprobamos si cantan bingo
				bingo1 = comprobar_ganador(carton1, f, c);
				bingo2 = comprobar_ganador(carton2, f, c);
			}
		}
		else{
			i--;
		}

		//Si cantan bingo
		if(bingo1 == 1 && bingo2 == 0){
			printf("\n\nHan cantado " AZUL_T "BINGO" RESET_COLOR " en el " VERDE_T "cartón nº 1" RESET_COLOR " cuándo llevamos %d bolas.\n", i + 1);
			ganador = 1;
		}
		else if(bingo1 == 0 && bingo2 == 1){
			printf("\n\nHan cantado " AZUL_T "BINGO" RESET_COLOR " en el " AMARILLO_T "cartón nº 2" RESET_COLOR " cuándo llevamos %d bolas.\n", i + 1);
			ganador = 1;
		}
		else if(bingo1 == 1 && bingo2 == 1){
			printf("\n\nHan cantado " AZUL_T "BINGO" RESET_COLOR " en ambos cartones cuándo llevamos %d bolas.\n", i + 1);
			ganador = 1;
		}
	}

	printf("\nLos cartones han quedado de esta forma:\n");
	printf(VERDE_T "\nCartón 1: " RESET_COLOR);
	imprime_carton(carton1, f, c);
	printf(AMARILLO_T "\nCartón 2: " RESET_COLOR);
	imprime_carton(carton2, f, c);

	//Liberamos memoria
	free(carton1);
	free(carton2);
	free(vector);
}


  /////////////////////////////////////////
 //	  	 FUNCIÓN COMPROBAR GANADOR		//
/////////////////////////////////////////

int	comprobar_ganador(int* carton, int f, int c){

	//Declaración de variables
	int i, j;

	for(i = 0; i < f; i++){
		for(j = 0; j < c; j++){
			if(*(carton + i * c + j) > 0)
				return 0;
		}
	}

	//Fin de la función
	return 1;
}


  /////////////////////////////////////////
 //	  	  FUNCIÓN COMPROBAR FILA		//
/////////////////////////////////////////

int	comprobar_fila(int* carton, int f, int c){

	//Declaración de variables
	int i, j, encontrado = 0;

	for(i = 0; i < f; i++){
		for(j = 0; j < c; j++){
			if(*(carton + i * c + j) > 0)
				encontrado = 1;
		}

		if(encontrado == 0)
			return 1;
	}

	//Fin de la función
	return 0;
}


  /////////////////////////////////////////
 //	  	 FUNCIÓN COMPRUEBA CARTON		//
/////////////////////////////////////////

void comprueba_carton(int* carton, int f, int c, int num, int numCarton){

	//Declaración de variables
	int i, j;

	//Recorro el cartón para ver si aparece el número
	for(i = 0; i < f; i++){
		for(j = 0; j < c; j++){
			if(*(carton + i * c + j) == num){
				*(carton + i * c + j) = -2;

				//Imprimimos mensaje
				printf("\n**************************************************************");
				if(numCarton == 1){
					printf("\n\nEl número %d se encuentra en el " VERDE_T "primer cartón"  RESET_COLOR ". Tachamos: \n", num);
					printf(VERDE_T "\nCarton %d: " RESET_COLOR, numCarton);
				}
				else{
					printf("\n\nEl número %d se encuentra en el " AMARILLO_T "segundo cartón"  RESET_COLOR ". Tachamos: \n", num);
					printf(AMARILLO_T "\nCarton %d: " RESET_COLOR, numCarton);
				}
				
				imprime_carton(carton, f, c);
			}
		}
	}
}


  /////////////////////////////////////////
 //	  FUNCIÓN COMPRUEBA SI SALIÓ BOLA	//
/////////////////////////////////////////

int comprueba_si_ha_salido_bola(int num, int *vector){

	//Declaración de variables
	int cont = 0;

	while(cont < TAM){
		if(*(vector + cont) == num){
			return 1;
		}
		else if(*(vector + cont) == 0){
			return 0;
		}
		cont++;
	}

	return 0;
}

  /////////////////////////////////////////
 //	  	   FUNCIÓN ORDENA CARTON		//
/////////////////////////////////////////

void ordena_carton(int *carton, int f, int c){

	//Declaración de variables
	int i, j, k, l, menor;

	//Ordeno la matriz
	for(i = 0; i < c; i++){
		for(j = 0; j < f; j++){
			if(*(carton + j * c + i) != -1){
				for(k = 0; k < c; k++){
					for(l = 0; l < f; l++){
						if(*(carton + j * c + i) < *(carton + l * c + k)){
							menor = *(carton + j * c + i);
							*(carton + j * c + i) = *(carton + l * c + k);
							*(carton + l * c + k) = menor;
						}
					}
				}
			}
		}
	}
}



