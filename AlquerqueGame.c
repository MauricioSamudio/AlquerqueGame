#include<stdio.h>
#include<gtk/gtk.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<math.h>
#include<string.h>
#include<windows.h>
#include<glib/gprintf.h>
#include<stdbool.h>

#define Negra1 101
#define Negra2 102
#define Negra3 103
#define Negra4 104
#define Negra5 105
#define Negra6 106
#define Negra7 107
#define Negra8 108
#define Negra9 109
#define Negra10  110
#define Negra11  111
#define Negra12  112

#define Blanca1 201
#define Blanca2 202
#define Blanca3 203
#define Blanca4 204
#define Blanca5 205
#define Blanca6 206
#define Blanca7 207
#define Blanca8 208
#define Blanca9 209
#define Blanca10  210
#define Blanca11  211
#define Blanca12  212
	//TABLERO DE JUEGO
	int tablero[5][5]={{1,1,1,1,1},
					   {1,1,1,1,1},
					   {1,1,0,2,2},
					   {2,2,2,2,2},
					   {2,2,2,2,2}};
GtkBuilder *builder;
GtkWidget *windowAyuda;

void generar_tablero();
int movimientos();
int juego();
int turno;
int op;
int opcion;
int movimientosCPU();
int comprobarjuego();

int fichaN=12;
int fichaB=12;

int coordenadasTableroX[5][5]; //En esta matriz se guardan las coordenadas (X) del tablero, cada lugar de la matriz representa una posición del tablero.
int coordenadasTableroY[5][5]; //En esta matriz se guardan las coordenadas (Y) del tablero, cada lugar de la matriz representa una posición del tablero.
int piezasJ1[17]; //Guarda las posiciones random tomadas para no repetirlas, se utiliza para mandar a una función una pieza aleatoria.
int piezasJ2[17]; //Guarda las posiciones random tomadas para no repetirlas, se utiliza para mandar a una función una pieza aleatoria.
int fila = 0, columna = 0; //Índices varios para iterar en loops
int i,j;
int limiteInferior = 0, limiteSuperior = 5; //Guardan los "limites superior e inferior" de los vectores de las piezas, para obtener las posiciones aleatorias.
int randomPos; //Guarda la posicion a la hora de recorrer los vectores "piezasJ1" y "piezasJ2".
int piezaRandom; //Guarda momentaneamente la posicion del vector "piezasJ1" y "Piezas J2" para recorrerlo.

void FNconfigFormJuego();
void FNcrearMenusFormJuego();
void FNmostrarPantallaCreditos();
void FNcargaCoordenadasTablero();
void FNcrearPiezas();
void FNdimensionarPiezas();
void FNrandomizarPiezas();
void FNcrearTurnos();


/// ///////////////////////////// ESTRUCTURAS DE DATOS UTILIZADAS /////////////////////////////////////////////////////////////////////////////////////////
struct Pantallas { //Guarda los objetos de las pantallas
    GtkWidget *Layout;
    GtkWidget *Frame;
    GtkWidget *Fondo;
    GtkWidget *Pantalla;
    GtkWindow *Ventana;

} formInicio, formJuego,formCreditos,formAyuda, formDialogo, table, decorado;

struct OpcionesMenus { //Guarda los objetos de las opciones de los menus de las pantallas
    GtkWidget *Boton;
    GtkWidget *Icono;
    GtkWidget *Pantalla;
    GtkWidget *Fondo;
} cerrar, randomizar, ranking, ayuda, ajustes, creditos, jugar, reiniciar, movimientoAleatorio;


struct Juego { //Guarda todos los objetos de cada pieza, el objeto pieza en sí mismo, su imagen, su menú, el peso de cada pieza y sus movimientos. (Se anida con la estrucutra de Movimientos)
    GtkWidget *Pieza;
    int Peso;
    GtkWidget *Imagen;
    GtkWidget *Menu;

} FNegra1,FNegra2,FNegra3,FNegra4,FNegra5,FNegra6,FNegra7,FNegra8,FNegra9,FNegra10,FNegra11,FNegra12,FBlanca1,FBlanca2,FBlanca3,FBlanca4,FBlanca5,FBlanca6,FBlanca7,FBlanca8,FBlanca9,FBlanca10,FBlanca11,FBlanca12;


struct Turnos { //Guarda los objetos de los turnos de los jugadores (Botón e imagen del botón)
    GtkWidget *TurnoToggle; //Boton del turno
    GtkWidget *TurnoIcono; //Icono del boton
    GtkWidget *TurnoNombre; //Label que guarda el Nombre del Jugador de cada turno
    GtkWidget *TurnoMovimientos;
    GtkWidget *TurnoCantidadMovimientos; //Label que guarda la cantidad de movimientos que va haciando cada jugador, 4 por turno.
    gint TurnoContador; //Contador que guarda los movimientos en cada turno, de cada jugador.
    char TurnoArray[5]; //Guarda lo que se convierte de entero a char para poner en el lavel TurnoCantidadMovimientos
    int TurnoEstado; //Guarda el estado actual de cada turno con constantes: ACTIVO e INACTIVO.
} Jugador1, Jugador2;

int main (int    argc,char **argv){
    GtkApplication *app;
    int status;

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (FNconfigFormJuego), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    FNcargaCoordenadasTablero(); //Se cargan las coordenadas X e Y del layout del tablero, en una matriz con posiciones analogas a la matriz que guarda las piezas.

    FNconfigFormJuego(); //Se configura todo lo que tenga que ver con la interfaz vistosa de la pantalla pricipal de juego, esta pantalla se nombro formJuego


    FNcrearTurnos();
//    FNcrearTurnos(); //Se crean los turnos de los jugadores.

 //   FNconfigMovimientoPiezas(); //Se configura el movimiento de las piezas

  //  FNimprimirMatrices(); //Se imprime en consola las matrices con que se trabajan, para el control de los datos de los movimientos.


    gtk_widget_show_all(formJuego.Pantalla); //Se muestra todo lo que hay en pantalla.
    gtk_main(); //Definición del loop del programa principal main.

    return status;

    int i,j,t;
	printf("\tBIENVENIDO AL JUEGO HALMA\n");
	printf("\n\tEliga con que color jugara\n1-Blancas\n2-Negras\nOPCION: ");
	scanf("%d", &opcion);//SELECCION DEL COLOR DE NUESTRAS PIEZAS
	printf("\nElija quien quien tiene el primer turno\n1-Fichas Blancas\n2-Fichas Negras\n3-Aleatorio");
	scanf("%d", &t);//SELECCION DE QUIEN INICIA EL JUEGO O SI SERA ALEATORIA
	switch(t){

		case 1:
			turno=0;
		break;
		case 2:
			turno=1;
		break;
		case 3:
			srand(time(NULL));
			for(i==0;i<4;i++){// USAMOS UN FOR PARA QUE HAYA MAS PROBABILIDAD DE QUE NO SE REPITAN LOS TURNOS EN CADA JUEGO
				turno=rand()%2;
				printf("\n%d", turno);
			}
		break;
	}
	system("pause");
	generar_tablero();//LLAMADO A LA FUNCION QUE IMPRIME EL TABLERO
}
int comprobarjuego(){
	if(tablero[9][5]==1 && tablero[9][6]==1 && tablero[9][7]==1 && tablero[9][8]==1 && tablero[9][9]==1 && tablero[8][6]==1 && tablero[8][7]==1 && tablero[8][8]==1 && tablero[8][9]==1 && tablero[7][7]==1 && tablero[7][8]==1 && tablero[7][9]==1 && tablero[6][8]==1 && tablero[6][9]==1 && tablero[5][9]==1)
	{//EN CASO DE QUE TODAS LAS CASILLAS EN LAS QUE EMPEZARON LAS PIEZAS NEGRAS ESTEN OCUPADAS POR PIEZAS BLANCAS SALTARA UN MENSAJE DICIENDO QUEGANARON LAS BLANCAS
		printf("\nGANAN LAS BLANCAS");
		exit(0);
	}
	if(tablero[0][0]==2 && tablero[0][1]==2 && tablero[0][2]==2 && tablero[0][3]==2 && tablero[0][4]==2 && tablero[1][0]==2 && tablero[1][1]==2 && tablero[1][2]==2 && tablero[1][3]==2 && tablero[2][0]==2 && tablero[2][1]==2 && tablero[2][2]==2 && tablero[3][0]==2 && tablero[3][1]==2 && tablero[4][0]==2){
	//EN CASO DE QUE TODAS LAS CASILLAS EN LAS QUE EMPEZARON LAS PIEZAS BLANCAS ESTEN OCUPADAS POR PIEZAS NEGRAS SALTARA UN MENSAJE DICIENDO QUEGANARON LAS NEGRAS
		printf("\nGANAN LAS NEGRAS");
		exit(0);
	}
}

void generar_tablero(){//FUNCION QUE IMPRIME EL TABLERO
	int i,j;
	comprobarjuego();

	printf("\n\tY0     1     2     3     4\n");//INDICA EL NUMERO DE COLUMNA

	for(i=0;i<5;i++){
		printf("\t");
		for(j=0;j<=4;j++){
			if(tablero[i][j]==1)
				printf(" B");
			else if(tablero[i][j]==2)
				printf(" N");
			else if(tablero[i][j]==0)
				printf("  ");
			if(j<4)
				printf("====");

		}
		printf(" %dX\t",i);
		for(j=0;j<=4;j++){
			printf("%d%d", i,j);
			if(j<4)
				printf("====");

		}

		if(i%2==0&&i<4){

			printf("\n\t||\\   ||   /||\\   ||   /||\t||\\   ||   /||\\   ||   /||");
			printf("\n\t||  \\ || /  ||  \\ || /  ||\t||  \\ || /  ||  \\ || /  ||\n");
		}else if(i%2!=0&&i<4)
		{
			printf("\n\t||   /||\\   ||   /||\\   ||\t||   /||\\   ||   /||\\   ||");
			printf("\n\t|| /  ||  \\ || /  ||  \\ ||\t|| /  ||  \\ || /  ||  \\ ||\n");
		}
	}

	if(turno==0)//ESTAS CONDICIONES NOS AYUDAN A VISUALIZAR DE QUIEN ES EL TURNO
		printf("\nTurno Ficha: BLANCA(B)");
	if(turno==1)
		printf("\nTurno Ficha: NEGRA(N)");
	printf("\n");
	juego();
}

int juego(){//COMIENZA EL JUEGO
	movimientosCPU();
}
int MoveFicha(int x,int y){
        if(x==0 && y==0 ){
			if(tablero[x+1][y+1]==0)//Movimiento en diagonal derecha hacia abajo
				printf("\ndiagonal derecha hacia abajo:%d %d",x+1,y+1);
			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
				printf("\nvertical hacia abajo:%d %d",x+1,y);
			if(tablero[x+1][y+1]==2 && tablero[x+2][y+2]==0 && turno==0||tablero[x+1][y+1]==1 && tablero[x+2][y+2]==0 && turno==1){
				printf("\ndiagonal derecha hacia abajo:%d %d",x+2,y+2);
				if(tablero[x+3][y+3]==2 && tablero[x+4][y+4]==0){
					printf("\ndiagonal derecha hacia abajo:%d %d",x+4,y+4);
				}
			}
//			if(tablero[x+1][y+1]!=0 && tablero[x][y+1]!=0 tablero[x+1][y]!=0 ){
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
		}
		else if(x==4 && y==0 ){
			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
				printf("\nvertical hacia arriba:%d %d",x-1,y);
			if(tablero[x-1][y+1]==0)//Movimiento en diagonal derecha hacia arriba
				printf("\ndiagonal  derecha hacia arriba: %d %d", x-1,y+1);
			else{
				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
				movimientos();
			}

		}
		else if(x==0 && y==4 ){
			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
				printf("\nhorizontal hacia la izquierda: %d %d", x, y+1);
			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
				printf("\nvertical hacia abajo:%d %d",x+1,y);
			if(tablero[x+1][y-1]=0)//Movimiento en diagonal izquierda hacia abajo
				printf("\ndiagonal izquierda hacia abajo: %d %d", x+1,y-1);
			else{
				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
				movimientos();
			}

		}
		else if(x==4 && y==4){
			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
				printf("\nvertical hacia arriba:%d %d",x-1,y);
			if(tablero[x-1][y-1]==0)//Movimiento en diagonal izquierda hacia arriba
				printf("\ndiagonal izquierda hacia arriba: %d %d", x-1,y-1);
			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
			else{
				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
				movimientos();
			}

		}
		else if(x==1 && y==0|| x==3 && y==0 ){
			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
				printf("\nvertical hacia abajo:%d %d",x+1,y);
			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
				printf("\nvertical hacia arriba:%d %d",x-1,y);
			else{
				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
				movimientos();
			}

		}
		else if(x==0 && y==1 ||x==0 && y==3 ){
			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
				printf("\nvertical hacia abajo:%d %d",x+1,y);
			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
			else{
				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
				movimientos();
			}

		}
		else if(x==4 && y==1 ||x==4 && y==3 ){
			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
				printf("\nvertical hacia arriba:%d %d",x-1,y);
			else{
				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
				movimientos();
			}

		}
		else if(x==1 && y==4 ||x==3&&y==4 ){
			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
				printf("\nvertical hacia arriba:%d %d",x-1,y);
			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
				printf("\nvertical hacia abajo:%d %d",x+1,y);
			else{
				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
				movimientos();
			}

		}
		else if(x==2 && y==0 ){
			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
				printf("\nvertical hacia arriba:%d %d",x-1,y);
			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
				printf("\nvertical hacia abajo:%d %d",x+1,y);
			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
			if(tablero[x+1][y+1]==0)//Movimiento en diagonal derecha hacia abajo
				printf("\ndiagonal derecha hacia abajo:%d %d",x+1,y+1);
			if(tablero[x-1][y-1]==0)//Movimiento en diagonal izquierda hacia arriba
				printf("\ndiagonal izquierda hacia arriba: %d %d", x-1,y-1);
			else{
				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
				movimientos();
			}

		}
		else if(x==2 && y==4 ){
			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
				printf("\nvertical hacia arriba:%d %d",x-1,y);
			if(tablero[x-1][y-1]==0)//Movimiento en diagonal izquierda hacia arriba
				printf("\ndiagonal izquierda hacia arriba: %d %d", x-1,y-1);
			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
				printf("\nvertical hacia abajo:%d %d",x+1,y);
			if(tablero[x+1][y-1]=0)//Movimiento en diagonal izquierda hacia abajo
				printf("\ndiagonal izquierda hacia abajo: %d %d", x+1,y-1);
			else{
				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
				movimientos();
			}

		}
		else if(x==0 && y==2 ){
			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
				printf("\nvertical hacia abajo:%d %d",x+1,y);
			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
			if(tablero[x+1][y-1]=0)//Movimiento en diagonal izquierda hacia abajo
				printf("\ndiagonal izquierda hacia abajo: %d %d", x+1,y-1);
			if(tablero[x+1][y+1]==0)//Movimiento en diagonal derecha hacia abajo
				printf("\ndiagonal derecha hacia abajo:%d %d",x+1,y+1);
			else{
				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
				movimientos();
			}

		}else if(x==4 && y==2 ){
			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
				printf("\nvertical hacia arriba:%d %d",x-1,y);
			if(tablero[x-1][y+1]==0)//Movimiento en diagonal derecha hacia arriba
				printf("\ndiagonal  derecha hacia arriba: %d %d", x-1,y+1);
			if(tablero[x-1][y-1]==0)//Movimiento en diagonal izquierda hacia arriba
				printf("\ndiagonal izquierda hacia arriba: %d %d", x-1,y-1);
			else{
				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
				movimientos();
			}

		}
		else if(x==1 && y==1 ||x==1 && y==3 ||x==3 && y==1 ||x==3 && y==3 ||x==2 && y==2 ){
			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
				printf("\nvertical hacia arriba:%d %d",x-1,y);
			if(tablero[x-1][y-1]==0)//Movimiento en diagonal izquierda hacia arriba
				printf("\ndiagonal izquierda hacia arriba: %d %d", x-1,y-1);
			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
			if(tablero[x+1][y+1]==0)//Movimiento en diagonal derecha hacia abajo
				printf("\ndiagonal derecha hacia abajo:%d %d",x+1,y+1);
			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
				printf("\nvertical hacia abajo:%d %d",x+1,y);
			if(tablero[x-1][y]!=0 && tablero[x-1][y-1]!=0 && tablero[x][y-1]!=0 && tablero[x+1][y+1]!=0 && tablero[x][y+1]!=0 &&
                tablero[x+1][y]!=0){
				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
				movimientos();
			}

		}else if(x==1 && y==2|| x==2 && y==3|| x==3 && y==2||x==2 && y==1){
			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
				printf("\nvertical hacia arriba:%d %d",x-1,y);
			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
				printf("\nvertical hacia abajo:%d %d",x+1,y);
			else{
				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
				movimientos();
			}
		}
}
int movimientos(){//EN CASO DE QUE EL MODO SEA JvJ
	int x,y,a,b;
	printf("\nIngrese la posicion de la ficha a mover(x y): ");
	scanf("%d", &x);//PARA INDICAR LA FILA DE LA FICHA
	scanf("%d", &y);//PARA INDICAR LA COLUMNA DE LA FICHA
	if(tablero[x][y]==2 && turno==0||tablero[x][y]==1 && turno==1||tablero[x][y]==0){//VERIFICA QUE LA FICHA ELEGIDA CORRESPONDA al turno
		do{
			if(tablero[x][y]==0){
                printf("\nTiene que introducir la posicion de una ficha");
			}else{
                printf("NO LE PERTENECE ESA PIEZA");//EN CASO DE QUE NO SE HAYA CUMPLIDO LA CONDICION IMPRIME ESTE MENSAJE
            }
			printf("\nFavor,reingrese la posicion de la ficha a mover(x y): ");
			scanf("%d", &x);
			scanf("%d", &y);
		}while(tablero[x][y]==2 && turno==0||tablero[x][y]==1 && turno==1||tablero[x][y]==0);//SE EJECUTA ESTE PROCESO HASTA QUE SE CUMPLA LA CONDICION
	}
    MoveFicha(x,y);
//	printf("\nPosiciones Validas:\n");
//	if(turno==0){// EN CASO DE QUE SEA EL TURNO DE LAS PIEZAS BLANCAS HAY CIERTAS CONDICIONES QUE SE DEBEN CUMPLIR PARA QUE SE MUEVA A OTRA POSICION LA PIEZA ELEGIDA
//		//CON ESTAS CONDICIONES LAS PIEZAS NO SON CAPACES DE RETROCEDER ASEGURANDONOS DE QUE TENGAN QUE LLEGAR A LAS POSICIONES INICIALES DE LAS PIEZAS NEGRAS
//
//		//Movimientos de una sola casilla sin saltos
//		if(x==0 && y==0 && tablero[x][y]==1){
//			if(tablero[x+1][y+1]==0)//Movimiento en diagonal derecha hacia abajo
//				printf("\ndiagonal derecha hacia abajo:%d %d",x+1,y+1);
//			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
//				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
//			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
//				printf("\nvertical hacia abajo:%d %d",x+1,y);
//			if(tablero[x+1][y+1]==2 && tablero[x+2][y+2]==0 ){
//				printf("\ndiagonal derecha hacia abajo:%d %d",x+2,y+2);
//				if(tablero[x+3][y+3]==2 && tablero[x+4][y+4]==0){
//					printf("\ndiagonal derecha hacia abajo:%d %d",x+4,y+4);
//				}
//			}
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//		}
//		else if(x==4 && y==0 && tablero[x][y]==1){
//			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
//				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
//			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
//				printf("\nvertical hacia arriba:%d %d",x-1,y);
//			if(tablero[x-1][y+1]==0)//Movimiento en diagonal derecha hacia arriba
//				printf("\ndiagonal  derecha hacia arriba: %d %d", x-1,y+1);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//
//		}
//		else if(x==0 && y==4 && tablero[x][y]==1){
//			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
//				printf("\nhorizontal hacia la izquierda: %d %d", x, y+1);
//			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
//				printf("\nvertical hacia abajo:%d %d",x+1,y);
//			if(tablero[x+1][y-1]=0)//Movimiento en diagonal izquierda hacia abajo
//				printf("\ndiagonal izquierda hacia abajo: %d %d", x+1,y-1);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//
//		}
//		else if(x==4 && y==4 && tablero[x][y]==1){
//			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
//				printf("\nvertical hacia arriba:%d %d",x-1,y);
//			if(tablero[x-1][y-1]==0)//Movimiento en diagonal izquierda hacia arriba
//				printf("\ndiagonal izquierda hacia arriba: %d %d", x-1,y-1);
//			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
//				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//
//		}
//		else if(x==1 && y==0 && tablero[x][y]==1|| x==3 && y==0 && tablero[x][y]==1){
//			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
//				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
//			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
//				printf("\nvertical hacia abajo:%d %d",x+1,y);
//			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
//				printf("\nvertical hacia arriba:%d %d",x-1,y);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//
//		}
//		else if(x==0 && y==1 && tablero[x][y]==1||x==0 && y==3 && tablero[x][y]==1){
//			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
//				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
//			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
//				printf("\nvertical hacia abajo:%d %d",x+1,y);
//			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
//				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//
//		}
//		else if(x==4 && y==1 && tablero[x][y]==1||x==4 && y==3 && tablero[x][y]==1){
//			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
//				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
//			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
//				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
//			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
//				printf("\nvertical hacia arriba:%d %d",x-1,y);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//
//		}
//		else if(x==1 && y==4 && tablero[x][y]==1||x==3&&y==4 && tablero[x][y]==1){
//			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
//				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
//			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
//				printf("\nvertical hacia arriba:%d %d",x-1,y);
//			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
//				printf("\nvertical hacia abajo:%d %d",x+1,y);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//
//		}
//		else if(x==2 && y==0 && tablero[x][y]==1){
//			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
//				printf("\nvertical hacia arriba:%d %d",x-1,y);
//			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
//				printf("\nvertical hacia abajo:%d %d",x+1,y);
//			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
//				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
//			if(tablero[x+1][y+1]==0)//Movimiento en diagonal derecha hacia abajo
//				printf("\ndiagonal derecha hacia abajo:%d %d",x+1,y+1);
//			if(tablero[x-1][y-1]==0)//Movimiento en diagonal izquierda hacia arriba
//				printf("\ndiagonal izquierda hacia arriba: %d %d", x-1,y-1);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//
//		}
//		else if(x==2 && y==4 && tablero[x][y]==1){
//			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
//				printf("\nvertical hacia arriba:%d %d",x-1,y);
//			if(tablero[x-1][y-1]==0)//Movimiento en diagonal izquierda hacia arriba
//				printf("\ndiagonal izquierda hacia arriba: %d %d", x-1,y-1);
//			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
//				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
//			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
//				printf("\nvertical hacia abajo:%d %d",x+1,y);
//			if(tablero[x+1][y-1]=0)//Movimiento en diagonal izquierda hacia abajo
//				printf("\ndiagonal izquierda hacia abajo: %d %d", x+1,y-1);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//
//		}
//		else if(x==0 && y==2 && tablero[x][y]==1){
//			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
//				printf("\nvertical hacia abajo:%d %d",x+1,y);
//			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
//				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
//			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
//				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
//			if(tablero[x+1][y-1]=0)//Movimiento en diagonal izquierda hacia abajo
//				printf("\ndiagonal izquierda hacia abajo: %d %d", x+1,y-1);
//			if(tablero[x+1][y+1]==0)//Movimiento en diagonal derecha hacia abajo
//				printf("\ndiagonal derecha hacia abajo:%d %d",x+1,y+1);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//
//		}else if(x==4 && y==2 && tablero[x][y]==1){
//			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
//				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
//			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
//				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
//			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
//				printf("\nvertical hacia arriba:%d %d",x-1,y);
//			if(tablero[x-1][y+1]==0)//Movimiento en diagonal derecha hacia arriba
//				printf("\ndiagonal  derecha hacia arriba: %d %d", x-1,y+1);
//			if(tablero[x-1][y-1]==0)//Movimiento en diagonal izquierda hacia arriba
//				printf("\ndiagonal izquierda hacia arriba: %d %d", x-1,y-1);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//
//		}
//		else if(x==1 && y==1 && tablero[x][y]==1||x==1 && y==3 && tablero[x][y]==1||x==3 && y==1 && tablero[x][y]==1||x==3 && y==3 && tablero[x][y]==1||x==2 && y==2 && tablero[x][y]==1){
//			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
//				printf("\nvertical hacia arriba:%d %d",x-1,y);
//			if(tablero[x-1][y-1]==0)//Movimiento en diagonal izquierda hacia arriba
//				printf("\ndiagonal izquierda hacia arriba: %d %d", x-1,y-1);
//			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
//				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
//			if(tablero[x+1][y+1]==0)//Movimiento en diagonal derecha hacia abajo
//				printf("\ndiagonal derecha hacia abajo:%d %d",x+1,y+1);
//			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
//				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
//			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
//				printf("\nvertical hacia abajo:%d %d",x+1,y);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//
//		}else if(x==1 && y==2 && tablero[x][y]==1|| x==2 && y==3 && tablero[x][y]==1|| x==3 && y==2 && tablero[x][y]==1||x==2 && y==1 && tablero[x][y]==1){
//			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
//				printf("\nvertical hacia arriba:%d %d",x-1,y);
//			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
//				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
//			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
//				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
//			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
//				printf("\nvertical hacia abajo:%d %d",x+1,y);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//		}
//
//
////		}else if(tablero[x+2][y+2]==0 && tablero[x+1][y+1]==1||tablero[x+2][y+2]==0 && tablero[x+1][y+1]==2||tablero[x+2][y]==0 && tablero[x+1][y]==1||tablero[x+2][y]==0 && tablero[x+1][y]==2|| tablero[x][y+2]==0 && tablero[x][y+1]==1)
////		{
////			printf("%d %d\n",x+1,y+1);
////			printf("%d %d\n", x+2,y);
////			printf("%d %d\n", x,y+2);
////		}else if(tablero[x+1][y+1]==0 && tablero[x+1][y]==0 && tablero[x][y+1]==0){
////				printf("%d %d\n",x+1,y+1);
////			printf("%d %d\n", x+1,y);
////0			printf("%d %d\n", x,y+1);
// 	}
//	if(turno==1){
//		//Movimientos de una sola casilla sin saltos
//		if(x==0 && y==0 && tablero[x][y]==2){
//			if(tablero[x+1][y+1]==0)//Movimiento en diagonal derecha hacia abajo
//				printf("\ndiagonal derecha hacia abajo:%d %d",x+1,y+1);
//			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
//				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
//			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
//				printf("\nvertical hacia abajo:%d %d",x+1,y);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//
//		}
//		else if(x==4 && y==0 && tablero[x][y]==2){
//			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
//				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
//			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
//				printf("\nvertical hacia arriba:%d %d",x-1,y);
//			if(tablero[x-1][y+1]==0)//Movimiento en diagonal derecha hacia arriba
//				printf("\ndiagonal  derecha hacia arriba: %d %d", x-1,y+1);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//
//		}
//		else if(x==0 && y==4 && tablero[x][y]==2){
//			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
//				printf("\nhorizontal hacia la izquierda: %d %d", x, y+1);
//			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
//				printf("\nvertical hacia abajo:%d %d",x+1,y);
//			if(tablero[x+1][y-1]=0)//Movimiento en diagonal izquierda hacia abajo
//				printf("\ndiagonal izquierda hacia abajo: %d %d", x+1,y-1);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//
//		}
//		else if(x==4 && y==4 && tablero[x][y]==2){
//			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
//				printf("\nvertical hacia arriba:%d %d",x-1,y);
//			if(tablero[x-1][y-1]==0)//Movimiento en diagonal izquierda hacia arriba
//				printf("\ndiagonal izquierda hacia arriba: %d %d", x-1,y-1);
//			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
//				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//
//		}
//		else if(x==1 && y==0 && tablero[x][y]==2|| x==3 && y==0 && tablero[x][y]==2){
//			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
//				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
//			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
//				printf("\nvertical hacia abajo:%d %d",x+1,y);
//			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
//				printf("\nvertical hacia arriba:%d %d",x-1,y);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//
//		}
//		else if(x==0 && y==1 && tablero[x][y]==2||x==0 && y==3 && tablero[x][y]==2){
//			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
//				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
//			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
//				printf("\nvertical hacia abajo:%d %d",x+1,y);
//			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
//				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//
//		}
//		else if(x==4 && y==1 && tablero[x][y]==2||x==4 && y==3 && tablero[x][y]==2){
//			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
//				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
//			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
//				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
//			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
//				printf("\nvertical hacia arriba:%d %d",x-1,y);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//
//		}
//		else if(x==1 && y==4 && tablero[x][y]==2||x==3 && y==4 && tablero[x][y]==2){
//			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
//				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
//			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
//				printf("\nvertical hacia arriba:%d %d",x-1,y);
//			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
//				printf("\nvertical hacia abajo:%d %d",x+1,y);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//
//		}
//		else if(x==2 && y==0 && tablero[x][y]==2){
//			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
//				printf("\nvertical hacia arriba:%d %d",x-1,y);
//			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
//				printf("\nvertical hacia abajo:%d %d",x+1,y);
//			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
//				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
//			if(tablero[x+1][y+1]==0)//Movimiento en diagonal derecha hacia abajo
//				printf("\ndiagonal derecha hacia abajo:%d %d",x+1,y+1);
//			if(tablero[x-1][y-1]==0)//Movimiento en diagonal izquierda hacia arriba
//				printf("\ndiagonal izquierda hacia arriba: %d %d", x-1,y-1);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//
//		}
//		else if(x==2 && y==4 && tablero[x][y]==2){
//			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
//				printf("\nvertical hacia arriba:%d %d",x-1,y);
//			if(tablero[x-1][y-1]==0)//Movimiento en diagonal izquierda hacia arriba
//				printf("\ndiagonal izquierda hacia arriba: %d %d", x-1,y-1);
//			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
//				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
//			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
//				printf("\nvertical hacia abajo:%d %d",x+1,y);
//			if(tablero[x+1][y-1]=0)//Movimiento en diagonal izquierda hacia abajo
//				printf("\ndiagonal izquierda hacia abajo: %d %d", x+1,y-1);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//
//		}
//		else if(x==0 && y==2 && tablero[x][y]==2){
//			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
//				printf("\nvertical hacia abajo:%d %d",x+1,y);
//			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
//				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
//			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
//				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
//			if(tablero[x+1][y-1]=0)//Movimiento en diagonal izquierda hacia abajo
//				printf("\ndiagonal izquierda hacia abajo: %d %d", x+1,y-1);
//			if(tablero[x+1][y+1]==0)//Movimiento en diagonal derecha hacia abajo
//				printf("\ndiagonal derecha hacia abajo:%d %d",x+1,y+1);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//
//		}else if(x==4 && y==2 && tablero[x][y]==2){
//			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
//				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
//			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
//				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
//			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
//				printf("\nvertical hacia arriba:%d %d",x-1,y);
//			if(tablero[x-1][y+1]==0)//Movimiento en diagonal derecha hacia arriba
//				printf("\ndiagonal  derecha hacia arriba: %d %d", x-1,y+1);
//			if(tablero[x-1][y-1]==0)//Movimiento en diagonal izquierda hacia arriba
//				printf("\ndiagonal izquierda hacia arriba: %d %d", x-1,y-1);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//
//		}
//		else if(x==1 && y==1 && tablero[x][y]==2||x==1 && y==3 && tablero[x][y]==2||x==3 && y==1 && tablero[x][y]==2||x==3 && y==3 && tablero[x][y]==2||x==2 && y==2 && tablero[x][y]==2){
//			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
//				printf("\nvertical hacia arriba:%d %d",x-1,y);
//			if(tablero[x-1][y-1]==0)//Movimiento en diagonal izquierda hacia arriba
//				printf("\ndiagonal izquierda hacia arriba: %d %d", x-1,y-1);
//			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
//				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
//			if(tablero[x+1][y+1]==0)//Movimiento en diagonal derecha hacia abajo
//				printf("\ndiagonal derecha hacia abajo:%d %d",x+1,y+1);
//			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
//				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
//			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
//				printf("\nvertical hacia abajo:%d %d",x+1,y);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//
//		}else if(x==1 && y==2 && tablero[x][y]==2|| x==2 && y==3 && tablero[x][y]==2|| x==3 && y==2 && tablero[x][y]==2||x==2 && y==1 && tablero[x][y]==2){
//			if(tablero[x-1][y]==0)//Movimiento en vertical hacia arriba
//				printf("\nvertical hacia arriba:%d %d",x-1,y);
//			if(tablero[x][y-1]==0)//Movimiento en horizontal hacia la izquierda
//				printf("\nhorizontal hacia la izquierda: %d %d", x, y-1);
//			if(tablero[x][y+1]==0)//Movimiento en horizontal hacia la derecha
//				printf("\nhorizontal hacia la derecha :%d %d",x,y+1);
//			if(tablero[x+1][y]==0)//Movimiento en vertical hacia abajo
//				printf("\nvertical hacia abajo:%d %d",x+1,y);
//			else{
//				printf("\nNo tiene movimientos validos");//EN CASO DE QUE LA PIEZA NO TENGA MOVIMIENTOS VALIDOS SE VOLVERA A LLAMAR A LA FUNCION generar_tablero()
//													//PARA QUE VISUALIZE QUE OTRA PIEZA PUEDE ELEGIR
//				movimientos();
//			}
//
//		}
//	}
	printf("\nIngrese la posicion a mover de la ficha(x y): ");
	scanf("%d", &a);//INDICA LA FILA A LA CUAL QUEREMOS MOVER LA FICHA
	scanf("%d", &b);//INDICA LA COLUMNA A LA CUAL QUEREMOS MOVER LA FICHA

	if(tablero[x][y]==2 && tablero[a][b]==0 && tablero[a+1][b+1]==1||tablero[x][y]==2 && tablero[a][b]==0 && tablero[a+1][b+1]==2||tablero[x][y]==2 && tablero[a][b]==0 && tablero[a][b+1]==1||tablero[x][y]==2 && tablero[a][b]==0 && tablero[a][b+1]==2||tablero[x][y]==2 && tablero[a][b]==0 && tablero[+1][b]==1||tablero[x][y]==2 && tablero[a][b]==0 && tablero[+1][b]==2||tablero[x][y]==1 && tablero[a][b]==0 && tablero[a-1][b-1]==1||tablero[x][y]==1 && tablero[a][b]==0 && tablero[a-1][b-1]==2||tablero[x][y]==1 && tablero[a][b]==0 && tablero[a][b-1]==1||tablero[x][y]==1 && tablero[a][b]==0 && tablero[a][b-1]==2||tablero[x][y]==1 && tablero[a][b]==0 && tablero[a-1][b]==1||tablero[x][y]==1 && tablero[a][b]==0 && tablero[a-1][b]==2){//CONDICION PARA ASEGURARNOS DE QUE LA POSICION A LA CUAL
		//if(  ){																	DESEAMOS MOVERNOS ESTE LIBRE
			tablero[a][b]=tablero[x][y];//LA POSICION a b TOMA LA FICHA QUE SE ENCUENTRA EN x y
			tablero[x][y]=0;//Y LA POSICION x y TOMA VALOR 0
		//}
	}
	if(tablero[x][y]==1 && tablero[a][b]==1||tablero[x][y]==1 && tablero[a][b]==2||tablero[x][y]==2 && tablero[a][b]==1||tablero[x][y]==2 && tablero[a][b]==2){
		printf("\nNo puede ubicar su pieza ahi");
		movimientos();//EN CASO DE QUE NO SE CUMPLA LAS CONDICIONES DE LA LINEA 96 VUELVE A EJECUTAR TODA LA FUNCION movimientos
	}
	turno++;//SI NO SE HA LLEGADO A CUMPLIR LA CONDICION, SUMA EL VALOR DE TURNO EN 1;
	if(turno==2)//SI TURNO LLEGA A TOMAR VALOR 2 ESTA CONDICION SE ENCARGA DE QUE VUELVA A TOMAR VALOR 0;
		turno=0;

	generar_tablero();//SE VUELVE A IMPRIMIR EL TABLERO

}
int movimientosCPU(){//EN CASO DE QUE EL MODO SEA JvCPU
	int x,y,a,b;
	switch(opcion){
		case 1:
			if(turno==0)
				movimientos();//CUANDO SEA TURNO DEL JUGADOR SOLO SERA NECESARIO EJECUTAR LA FUNCION movimientos

			if(turno==1){//CUANDO SEA TURNO DE LA CPU SE EJECUTARA CASI LOS MISMOS PASOS DE LA FUNCION movimientos, 	SOLO QUE CON UNOS POCOS
			   //CAMBIOS PARA LA ELECCION DE LAS POSICIONES
				do{
					x=rand()%5; y=rand()%5;
				//	printf("\nx%d y%d", x,y);
				}while(tablero[x][y]!=2);
			//	printf("\nx%d y%d", x,y);

				do{//problema

					a=rand()%5; b=rand()%5;
				//	printf("\na%d b%d", a,b);
				}while(tablero[a][b]!=0);
			//	printf("\na%d b%d", a,b);

/*problema*/	if(tablero[x-2][y-2]==0 && tablero[x-1][y-1]==1 && a==x-2 && b==y-2||tablero[x-2][y-2]==0 && tablero[x-1][y-1]==2 && a==x-2 && b==y-2||tablero[x+2][y+2]==0 && tablero[x+1][y+1]==1 && a==x+2 && b==y+2||tablero[x+2][y+2]==0 && tablero[x+1][y+1]==2 && a==x+2 && b==y+2||tablero[x+2][y]==0 && tablero[x+1][y]==1 && a==x+2 && b==y||tablero[x+2][y]==0 && tablero[x+1][y]==2 && a==x+2 && b==y|| tablero[x][y+2]==0 && tablero[x][y+1]==1 && a==x && b==y+2||tablero[x+1][y+1]==0 && tablero[x+1][y]==0 && tablero[x][y+1]==0 && a==x+1 && b==y+1){

					tablero[a][b]=2;
					tablero[x][y]=0;

				}
				else{
				//if(tablero[x][y]==2 && tablero[a][b]==1|| tablero[x][y]==2 && tablero[x][y]==2|| tablero[x][y]==1 && tablero[a][b]==1||tablero[x][y]==1 && tablero[a][b]==2||tablero[x][y]==2 && tablero[a+1][b+1]==0 && tablero[a-1][b-1]==0||tablero[x][y]==2 && tablero[a+1][b+1]==0 && tablero[a-1][b-1]==2||tablero[x][y]==2 && tablero[a+1][b]==0||tablero[x][y]==2 && tablero[a+1][b]==0)	{
					movimientosCPU();
				}

				turno++;
				if(turno==2)
					turno=0;
				generar_tablero();
			}
		break;
		case 2:
			if(turno==1)
				movimientos();//CUANDO SEA TURNO DEL JUGADOR SOLO SERA NECESARIO EJECUTAR LA FUNCION movimientos

			if(turno==0){//CUANDO SEA TURNO DE LA CPU SE EJECUTARA CASI LOS MISMOS PASOS DE LA FUNCION movimientos, 	SOLO QUE CON UNOS POCOS
			   //CAMBIOS PARA LA ELECCION DE LAS POSICIONES
				do{
					x=rand()%5; y=rand()%5;
				//	printf("\nx%d y%d", x,y);
				}while(tablero[x][y]!=1);
			//	printf("\nx%d y%d", x,y);

				do{

					a=rand()%5; b=rand()%5;
				//	printf("\na%d b%d", a,b);
				}while(tablero[a][b]!=0);
				//printf("\na%d b%d", a,b);

				if(tablero[x-2][y-2]==0 && tablero[x-1][y-1]==1 && a==x-2 && b==y-2||tablero[x-2][y-2]==0 && tablero[x-1][y-1]==2 && a==x-2 && b==y-2||tablero[x+2][y+2]==0 && tablero[x+1][y+1]==1 && a==x+2 && b==y+2||tablero[x+2][y+2]==0 && tablero[x+1][y+1]==2 && a==x+2 && b==y+2||tablero[x+2][y]==0 && tablero[x+1][y]==1 && a==x+2 && b==y||tablero[x+2][y]==0 && tablero[x+1][y]==2 && a==x+2 && b==y|| tablero[x][y+2]==0 && tablero[x][y+1]==1 && a==x && b==y+2||tablero[x+1][y+1]==0 && tablero[x+1][y]==0 && tablero[x][y+1]==0 && a==x+1 && b==y+1){
				//if(  ){
					tablero[a][b]=1;
					tablero[x][y]=0;
				//}
				}
				else{
				//if(tablero[x][y]==2 && tablero[a][b]==1|| tablero[x][y]==2 && tablero[x][y]==2|| tablero[x][y]==1 && tablero[a][b]==1||tablero[x][y]==1 && tablero[a][b]==2||tablero[x][y]==2 && tablero[a+1][b+1]==0 && tablero[a-1][b-1]==0||tablero[x][y]==2 && tablero[a+1][b+1]==0 && tablero[a-1][b-1]==2||tablero[x][y]==2 && tablero[a+1][b]==0||tablero[x][y]==2 && tablero[a+1][b]==0)	{
					movimientosCPU();
				}

				turno++;
				if(turno==2)
					turno=0;
				generar_tablero();
			}
		break;
	}
}

///CONFIGURACION DE LA PANTALLA DE JUEGO, DIALOGOS DE ADVERTENCIAS, ARREGLOS PARA EL CONTROL EN TERMINAL E IMPRESION EN TERMINAL.
void FNconfigFormJuego(){ //Configura la pantalla de juego

    //Creación de la pantalla de juego
    formJuego.Pantalla = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(formJuego.Pantalla), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(formJuego.Pantalla), 1324,900);
  //  gtk_window_set_resizable(GTK_WINDOW(formJuego.Pantalla), FALSE);
    gtk_window_set_title(GTK_WINDOW(formJuego.Pantalla), "Alquerque");
    gtk_container_set_border_width(GTK_CONTAINER(formJuego.Pantalla), 5);
    gtk_window_set_icon_from_file(GTK_WINDOW(formJuego.Pantalla), "tablero.jpg", NULL);

    //Creación del tablero
    table.Fondo = gtk_image_new_from_file("tablero.jpg");
    decorado.Fondo = gtk_image_new_from_file("fondoLayout.png");
    formJuego.Layout = gtk_layout_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(formJuego.Pantalla), formJuego.Layout);
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), table.Fondo, 0, 0);
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), decorado.Fondo, 900, 0);

    //Llamada a funcion para la creación de los menús de la pantalla de juego
   // FNcrearMenusFormJuego();

    FNcrearMenusFormJuego();
   gtk_widget_show_all(formJuego.Layout);

}

void FNcrearMenusFormJuego(){ //Crea los menús de opciones dentro de la pantalla de juego

    //Creacion del boton para entrar a la pantalla de ranking de jugadores ((PANTALLA EN PROCESO DE DESARROLLO PARA LA 2DA ENTREGA)
    ranking.Boton = gtk_button_new_with_label(NULL);
    ranking.Icono = gtk_image_new_from_file("ranking.png");
    gtk_button_set_always_show_image(GTK_BUTTON(ranking.Boton), TRUE);
    gtk_button_set_image(GTK_BUTTON(ranking.Boton), ranking.Icono);
    gtk_button_set_relief(GTK_BUTTON(ranking.Boton), GTK_RELIEF_NONE);
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), ranking.Boton, 1199,130);
    //g_signal_connect_swapped(G_OBJECT(ranking.Boton), "button-press-event", G_CALLBACK(gtk_main_quit),NULL);

    //Creacion del boton para entrar a la pantalla de ayuda del juego (PANTALLA EN PROCESO DE DESARROLLO PARA LA 2DA ENTREGA)
    ayuda.Boton = gtk_button_new_with_label(NULL);
    ayuda.Icono = gtk_image_new_from_file("ayuda.png");
    gtk_button_set_always_show_image(GTK_BUTTON(ayuda.Boton), TRUE);
    gtk_button_set_image(GTK_BUTTON(ayuda.Boton), ayuda.Icono);
    gtk_button_set_relief(GTK_BUTTON(ayuda.Boton), GTK_RELIEF_NONE);
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), ayuda.Boton, 1200, 8);
    //g_signal_connect_swapped(G_OBJECT(ayuda.Boton), "button-press-event", G_CALLBACK(FNmostrarPantallaAyuda),NULL);

    //Creacion del boton para entrar a la pantalla de ajustes (PANTALLA EN PROCESO DE DESARROLLO PARA LA 2DA ENTREGA)
    ajustes.Boton = gtk_button_new_with_label(NULL);
    ajustes.Icono = gtk_image_new_from_file("ajustes.png");
    gtk_button_set_always_show_image(GTK_BUTTON(ajustes.Boton), TRUE);
    gtk_button_set_image(GTK_BUTTON(ajustes.Boton), ajustes.Icono);
    gtk_button_set_relief(GTK_BUTTON(ajustes.Boton), GTK_RELIEF_NONE);
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), ajustes.Boton, 1200,515);
    //g_signal_connect_swapped(G_OBJECT(ajustes.Boton), "button-press-event", G_CALLBACK(gtk_main_quit),NULL);

    //Creacion del boton para entrar a la pantalla de creditos de desarrollo (PANTALLA EN PROCESO DE DESARROLLO PARA LA 2DA ENTREGA)
    creditos.Boton = gtk_button_new_with_label(NULL);
    creditos.Icono = gtk_image_new_from_file("creditos.png");
    gtk_button_set_always_show_image(GTK_BUTTON(creditos.Boton), TRUE);
    gtk_button_set_image(GTK_BUTTON(creditos.Boton), creditos.Icono);
    gtk_button_set_relief(GTK_BUTTON(creditos.Boton), GTK_RELIEF_NONE);
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), creditos.Boton, 1200,640 );
    g_signal_connect_swapped(G_OBJECT(creditos.Boton), "button-press-event", G_CALLBACK(FNmostrarPantallaCreditos),NULL);


    //Creacion del boton para empezar a jugar (EN PROCESO SIN TERMINAR POR TENER BUGS)
    jugar.Boton = gtk_button_new_with_label(NULL);
    jugar.Icono = gtk_image_new_from_file("jugar.png");
    gtk_button_set_always_show_image(GTK_BUTTON(jugar.Boton), TRUE);
    gtk_button_set_image(GTK_BUTTON(jugar.Boton), jugar.Icono);
    gtk_button_set_relief(GTK_BUTTON(jugar.Boton), GTK_RELIEF_NONE);
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), jugar.Boton, 1200,390);
    g_signal_connect(G_OBJECT(jugar.Boton), "clicked", G_CALLBACK(FNcrearPiezas), NULL);

    //Creacion del boton para reiniciar la partida
    reiniciar.Boton = gtk_button_new_with_label(NULL);
    reiniciar.Icono = gtk_image_new_from_file("reiniciar.png");
    gtk_button_set_always_show_image(GTK_BUTTON(reiniciar.Boton), TRUE);
    gtk_button_set_image(GTK_BUTTON(reiniciar.Boton), reiniciar.Icono);
    gtk_button_set_relief(GTK_BUTTON(reiniciar.Boton), GTK_RELIEF_NONE);
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), reiniciar.Boton, 1200,250);
    //g_signal_connect_swapped(G_OBJECT(reiniciar.Boton), "button-press-event", G_CALLBACK(FNreiniciarJuego),NULL);

    //Creacion del boton salir para cerrar la pantalla de juego
    cerrar.Boton = gtk_button_new_with_label(NULL);
    cerrar.Icono = gtk_image_new_from_file("salir.png");
    gtk_button_set_always_show_image(GTK_BUTTON(cerrar.Boton), TRUE);
    gtk_button_set_image(GTK_BUTTON(cerrar.Boton), cerrar.Icono);
    gtk_button_set_relief(GTK_BUTTON(cerrar.Boton), GTK_RELIEF_NONE);
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), cerrar.Boton, 1200,770);
    //gtk_widget_modify_bg(GTK_WIDGET(cerrar.Boton),GTK_STATE_, &colorSalir);//solucionar en futuro
    g_signal_connect_swapped(G_OBJECT(cerrar.Boton), "button-press-event", G_CALLBACK(gtk_main_quit),NULL);

    //Creacion del boton para realizar movimiento aleatorio por la computadora (EN PRUEBA CON ERRORES)
    movimientoAleatorio.Boton = gtk_button_new_with_label(NULL);
    movimientoAleatorio.Icono = gtk_image_new_from_file("movimientoAleatorio.png");
    gtk_button_set_always_show_image(GTK_BUTTON(movimientoAleatorio.Boton), TRUE);
    gtk_button_set_image(GTK_BUTTON(movimientoAleatorio.Boton), movimientoAleatorio.Icono);
    gtk_button_set_relief(GTK_BUTTON(movimientoAleatorio.Boton), GTK_RELIEF_NONE);
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), movimientoAleatorio.Boton, 1020,700);
    //g_signal_connect_swapped(G_OBJECT(movimientoAleatorio.Boton), "button-press-event", G_CALLBACK(FNmovimientoAleatorio), NULL);

}

void FNmostrarPantallaCreditos(){
    GtkWidget *dialog;
    GdkPixbuf *logo;
    GError *error=NULL;
    const gchar *authors[]={
        "Mauricio Samudio",
        "Romina Zarza",
        NULL
    };
    const gchar *documenters[]={
        "Mauricio Samudio",
        "Romina Zarza",
        NULL
    };

    dialog= gtk_about_dialog_new();
//  logo=gdk_pixbuf_new_from_file("tablero.jpg",&error);
    if(error==NULL){
        gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), logo);
    }
    gtk_window_set_icon_from_file(GTK_WINDOW(dialog), "tablero.jpg", NULL);
    gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), "Alquerque");
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), "V. 0.1");
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog),"(C) 2020 FONDDA_TEAM");

    gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(dialog), authors);
    gtk_about_dialog_set_documenters(GTK_ABOUT_DIALOG(dialog), documenters);

    gtk_dialog_run(GTK_DIALOG(dialog));

    gtk_widget_destroy(dialog);


}

void FNcargaCoordenadasTablero(){
    int pos = 0;

    for(int i=0;i<5;i++){
        pos = 10 + 113 * i;
        for(int j = 0; j<5 ;j++ ){
            coordenadasTableroX[j][i] = pos;
        }

        for(int j = 0; j<5 ;j++ ){
            coordenadasTableroY[i][j] = pos;
        }
    }
}
void FNcrearPiezas(){
//Piezas del jugador 1
//    elefanteJ1.Peso = 6;
    FNegra1.Pieza = gtk_button_new_with_label(NULL);
    FNegra1.Imagen = gtk_image_new_from_file("FichaNegra.png");
    gtk_button_set_always_show_image(GTK_BUTTON(FNegra1.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FNegra1.Pieza), FNegra1.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FNegra1.Pieza), GTK_RELIEF_NONE);

//    camelloJ1.Peso = 5;
    FNegra2.Pieza = gtk_button_new_with_label(NULL);
    FNegra2.Imagen = gtk_image_new_from_file("FichaNegra.png");
    gtk_button_set_always_show_image(GTK_BUTTON(FNegra2.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FNegra2.Pieza), FNegra2.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FNegra2.Pieza), GTK_RELIEF_NONE);

//    caballo1J1.Peso = 4;
    FNegra3.Pieza = gtk_button_new_with_label(NULL);
    FNegra3.Imagen = gtk_image_new_from_file("FichaNegra.png");
    gtk_button_set_always_show_image(GTK_BUTTON(FNegra3.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FNegra3.Pieza), FNegra3.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FNegra3.Pieza), GTK_RELIEF_NONE);

//    caballo2J1.Peso = 4;
    FNegra4.Pieza = gtk_button_new_with_label(NULL);
    FNegra4.Imagen = gtk_image_new_from_file("FichaNegra.png");
    gtk_button_set_always_show_image(GTK_BUTTON(FNegra4.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FNegra4.Pieza), FNegra4.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FNegra4.Pieza), GTK_RELIEF_NONE);

//   perro1J1.Peso = 3;
    FNegra5.Pieza = gtk_button_new_with_label(NULL);
    FNegra5.Imagen = gtk_image_new_from_file("FichaNegra.png");
    gtk_button_set_always_show_image(GTK_BUTTON(FNegra5.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FNegra5.Pieza), FNegra1.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FNegra5.Pieza), GTK_RELIEF_NONE);

//    perro2J1.Peso = 3;
//    perro2J1.Pieza = gtk_button_new_with_label(NULL);
//    perro2J1.Imagen = gtk_image_new_from_file("perroBlanco.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(perro2J1.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(perro2J1.Pieza), perro2J1.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(perro2J1.Pieza), GTK_RELIEF_NONE);
//
//    gato1J1.Peso = 2;
//    gato1J1.Pieza = gtk_button_new_with_label(NULL);
//    gato1J1.Imagen = gtk_image_new_from_file("gatoBlanco.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(gato1J1.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(gato1J1.Pieza), gato1J1.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(gato1J1.Pieza), GTK_RELIEF_NONE);
//
//    gato2J1.Peso = 2;
//    gato2J1.Pieza = gtk_button_new_with_label(NULL);
//    gato2J1.Imagen = gtk_image_new_from_file("gatoBlanco.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(gato2J1.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(gato2J1.Pieza), gato2J1.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(gato2J1.Pieza), GTK_RELIEF_NONE);
//
//    conejo1J1.Peso = 1;
//    conejo1J1.Pieza = gtk_button_new_with_label(NULL);
//    conejo1J1.Imagen = gtk_image_new_from_file("conejoBlanco.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(conejo1J1.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(conejo1J1.Pieza), conejo1J1.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(conejo1J1.Pieza), GTK_RELIEF_NONE);
//
//    conejo2J1.Peso = 1;
//    conejo2J1.Pieza = gtk_button_new_with_label(NULL);
//    conejo2J1.Imagen = gtk_image_new_from_file("conejoBlanco.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(conejo2J1.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(conejo2J1.Pieza), conejo2J1.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(conejo2J1.Pieza), GTK_RELIEF_NONE);
//
//    conejo3J1.Peso = 1;
//    conejo3J1.Pieza = gtk_button_new_with_label(NULL);
//    conejo3J1.Imagen = gtk_image_new_from_file("conejoBlanco.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(conejo3J1.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(conejo3J1.Pieza), conejo3J1.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(conejo3J1.Pieza), GTK_RELIEF_NONE);
//
//    conejo4J1.Peso = 1;
//    conejo4J1.Pieza = gtk_button_new_with_label(NULL);
//    conejo4J1.Imagen = gtk_image_new_from_file("conejoBlanco.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(conejo4J1.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(conejo4J1.Pieza), conejo4J1.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(conejo4J1.Pieza), GTK_RELIEF_NONE);
//
//    conejo5J1.Peso = 1;
//    conejo5J1.Pieza = gtk_button_new_with_label(NULL);
//    conejo5J1.Imagen = gtk_image_new_from_file("conejoBlanco.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(conejo5J1.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(conejo5J1.Pieza), conejo5J1.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(conejo5J1.Pieza), GTK_RELIEF_NONE);
//
//    conejo6J1.Peso = 1;
//    conejo6J1.Pieza = gtk_button_new_with_label(NULL);
//    conejo6J1.Imagen = gtk_image_new_from_file("conejoBlanco.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(conejo6J1.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(conejo6J1.Pieza), conejo6J1.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(conejo6J1.Pieza), GTK_RELIEF_NONE);
//
//    conejo7J1.Peso = 1;
//    conejo7J1.Pieza = gtk_button_new_with_label(NULL);
//    conejo7J1.Imagen = gtk_image_new_from_file("conejoBlanco.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(conejo7J1.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(conejo7J1.Pieza), conejo7J1.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(conejo7J1.Pieza), GTK_RELIEF_NONE);
//
//    conejo8J1.Peso = 1;
//    conejo8J1.Pieza = gtk_button_new_with_label(NULL);
//    conejo8J1.Imagen = gtk_image_new_from_file("conejoBlanco.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(conejo8J1.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(conejo8J1.Pieza), conejo8J1.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(conejo8J1.Pieza), GTK_RELIEF_NONE);
//
//    //Piezas del jugador 2
//    elefanteJ2.Peso = 6;
//    elefanteJ2.Pieza = gtk_button_new_with_label(NULL);
//    elefanteJ2.Imagen = gtk_image_new_from_file("elefanteDorado.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(elefanteJ2.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(elefanteJ2.Pieza), elefanteJ2.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(elefanteJ2.Pieza), GTK_RELIEF_NONE);
//
//    camelloJ2.Peso = 5;
//    camelloJ2.Pieza = gtk_button_new_with_label(NULL);
//    camelloJ2.Imagen = gtk_image_new_from_file("camelloDorado.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(camelloJ2.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(camelloJ2.Pieza), camelloJ2.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(camelloJ2.Pieza), GTK_RELIEF_NONE);
//
//    caballo1J2.Peso = 4;
//    caballo1J2.Pieza = gtk_button_new_with_label(NULL);
//    caballo1J2.Imagen = gtk_image_new_from_file("caballoDorado.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(caballo1J2.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(caballo1J2.Pieza), caballo1J2.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(caballo1J2.Pieza), GTK_RELIEF_NONE);
//
//    caballo2J2.Peso = 4;
//    caballo2J2.Pieza = gtk_button_new_with_label(NULL);
//    caballo2J2.Imagen = gtk_image_new_from_file("caballoDorado.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(caballo2J2.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(caballo2J2.Pieza), caballo2J2.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(caballo2J2.Pieza), GTK_RELIEF_NONE);
//
//    perro1J2.Peso = 3;
//    perro1J2.Pieza = gtk_button_new_with_label(NULL);
//    perro1J2.Imagen = gtk_image_new_from_file("perroDorado.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(perro1J2.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(perro1J2.Pieza), perro1J2.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(perro1J2.Pieza), GTK_RELIEF_NONE);
//
//    perro2J2.Peso = 3;
//    perro2J2.Pieza = gtk_button_new_with_label(NULL);
//    perro2J2.Imagen = gtk_image_new_from_file("perroDorado.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(perro2J2.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(perro2J2.Pieza), perro2J2.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(perro2J2.Pieza), GTK_RELIEF_NONE);
//
//    gato1J2.Peso = 2;
//    gato1J2.Pieza = gtk_button_new_with_label(NULL);
//    gato1J2.Imagen = gtk_image_new_from_file("gatoDorado.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(gato1J2.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(gato1J2.Pieza), gato1J2.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(gato1J2.Pieza), GTK_RELIEF_NONE);
//
//    gato2J2.Peso = 2;
//    gato2J2.Pieza = gtk_button_new_with_label(NULL);
//    gato2J2.Imagen = gtk_image_new_from_file("gatoDorado.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(gato2J2.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(gato2J2.Pieza), gato2J2.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(gato2J2.Pieza), GTK_RELIEF_NONE);
//
//    conejo1J2.Peso = 1;
//    conejo1J2.Pieza = gtk_button_new_with_label(NULL);
//    conejo1J2.Imagen = gtk_image_new_from_file("conejoDorado.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(conejo1J2.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(conejo1J2.Pieza), conejo1J2.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(conejo1J2.Pieza), GTK_RELIEF_NONE);
//
//    conejo2J2.Peso = 1;
//    conejo2J2.Pieza = gtk_button_new_with_label(NULL);
//    conejo2J2.Imagen = gtk_image_new_from_file("conejoDorado.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(conejo2J2.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(conejo2J2.Pieza), conejo2J2.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(conejo2J2.Pieza), GTK_RELIEF_NONE);
//
//    conejo3J2.Peso = 1;
//    conejo3J2.Pieza = gtk_button_new_with_label(NULL);
//    conejo3J2.Imagen = gtk_image_new_from_file("conejoDorado.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(conejo3J2.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(conejo3J2.Pieza), conejo3J2.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(conejo3J2.Pieza), GTK_RELIEF_NONE);
//
//    conejo4J2.Peso = 1;
//    conejo4J2.Pieza = gtk_button_new_with_label(NULL);
//    conejo4J2.Imagen = gtk_image_new_from_file("conejoDorado.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(conejo4J2.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(conejo4J2.Pieza), conejo4J2.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(conejo4J2.Pieza), GTK_RELIEF_NONE);
//
//    conejo5J2.Peso = 1;
//    conejo5J2.Pieza = gtk_button_new_with_label(NULL);
//    conejo5J2.Imagen = gtk_image_new_from_file("conejoDorado.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(conejo5J2.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(conejo5J2.Pieza), conejo5J2.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(conejo5J2.Pieza), GTK_RELIEF_NONE);
//
//    conejo6J2.Peso = 1;
//    conejo6J2.Pieza = gtk_button_new_with_label(NULL);
//    conejo6J2.Imagen = gtk_image_new_from_file("conejoDorado.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(conejo6J2.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(conejo6J2.Pieza), conejo6J2.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(conejo6J2.Pieza), GTK_RELIEF_NONE);
//
//    conejo7J2.Peso = 1;
//    conejo7J2.Pieza = gtk_button_new_with_label(NULL);
//    conejo7J2.Imagen = gtk_image_new_from_file("conejoDorado.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(conejo7J2.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(conejo7J2.Pieza), conejo7J2.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(conejo7J2.Pieza), GTK_RELIEF_NONE);
//
//    conejo8J2.Peso = 1;
//    conejo8J2.Pieza = gtk_button_new_with_label(NULL);
//    conejo8J2.Imagen = gtk_image_new_from_file("conejoDorado.png");
//    gtk_button_set_always_show_image(GTK_BUTTON(conejo8J2.Pieza), TRUE);
//    gtk_button_set_image(GTK_BUTTON(conejo8J2.Pieza), conejo8J2.Imagen);
//    gtk_button_set_relief(GTK_BUTTON(conejo8J2.Pieza), GTK_RELIEF_NONE);

    FNdimensionarPiezas(); //llama a la funcion que dimensiona el tamano de las piezas

    /// Se cargan dos arreglos piezasJ1 y piezasJ2 con las constantes que representan cada pieza
    //Piezas J1
    piezasJ1[0] = Negra1;
    piezasJ1[1] = Negra2;
    piezasJ1[2] = Negra3;
    piezasJ1[3] = Negra4;
    piezasJ1[4] = Negra5;
    piezasJ1[5] = Negra6;
    piezasJ1[6] = Negra7;
    piezasJ1[7] = Negra8;
    piezasJ1[8] = Negra9;
    piezasJ1[9] = Negra10;
    piezasJ1[10] = Negra11;
    piezasJ1[11] = Negra12;

    //Piezas J2
    piezasJ2[0] = Blanca1;
    piezasJ2[1] = Blanca2;
    piezasJ2[2] = Blanca3;
    piezasJ2[3] = Blanca4;
    piezasJ2[4] = Blanca5;
    piezasJ2[5] = Blanca6;
    piezasJ2[6] = Blanca7;
    piezasJ2[7] = Blanca8;
    piezasJ2[8] = Blanca9;
    piezasJ2[9] = Blanca10;
    piezasJ2[10] = Blanca11;
    piezasJ2[11] = Blanca12;
}
void FNdimensionarPiezas(){ //Dimensiona el tamaño de las piezas
    //Se da tamano a las piezas del jugador 1
    gtk_widget_set_size_request(FNegra1.Pieza, 80,80);
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FNegra1.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
    gtk_widget_set_size_request(FNegra2.Pieza, 80,80);
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FNegra2.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
    gtk_widget_set_size_request(FNegra3.Pieza, 80,80);
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FNegra3.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
    gtk_widget_set_size_request(FNegra4.Pieza, 80,80);
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FNegra4.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
    gtk_widget_set_size_request(FNegra5.Pieza, 80,80);
        gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FNegra5.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
}
// TURNOS DE LOS JUGADORES
void FNcrearTurnos(){ //Crea los turnos de los jugadores
    //Se crea un color
    GdkColor color;
    gdk_color_parse("white", &color);

    //Se crea el turno del Jugador 1
    Jugador1.TurnoIcono = gtk_image_new_from_file("jugador1.png");
    Jugador1.TurnoToggle = gtk_toggle_button_new();
    gtk_button_set_image(GTK_BUTTON(Jugador1.TurnoToggle), Jugador1.TurnoIcono);
    gtk_button_set_relief(GTK_BUTTON(Jugador1.TurnoToggle), GTK_RELIEF_NONE);
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), Jugador1.TurnoToggle, 1000, 200);
    Jugador1.TurnoNombre = gtk_label_new("Mauricio");
    gtk_label_set_text(GTK_LABEL(Jugador1.TurnoNombre), "Mauricio");
    gtk_widget_modify_fg(GTK_WIDGET(Jugador1.TurnoNombre), GTK_STATE_NORMAL, &color);
    gtk_widget_modify_font(GTK_WIDGET(Jugador1.TurnoNombre), pango_font_description_from_string("Calibri BOLD 20"));
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), Jugador1.TurnoNombre, 1000, 40);
    Jugador1.TurnoMovimientos = gtk_label_new("Movimientos: ");
    gtk_widget_modify_fg(GTK_WIDGET(Jugador1.TurnoMovimientos), GTK_STATE_NORMAL, &color);
    gtk_widget_modify_font(GTK_WIDGET(Jugador1.TurnoMovimientos), pango_font_description_from_string("Calibri 12"));
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), Jugador1.TurnoMovimientos, 1000, 80);
    Jugador1.TurnoCantidadMovimientos = gtk_label_new("0");
    gtk_widget_modify_fg(GTK_WIDGET(Jugador1.TurnoCantidadMovimientos), GTK_STATE_NORMAL, &color);
    gtk_widget_modify_font(GTK_WIDGET(Jugador1.TurnoCantidadMovimientos), pango_font_description_from_string("Calibri 12"));
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), Jugador1.TurnoCantidadMovimientos, 1120, 80);


    //Se crea el turno del Jugador 2
    Jugador2.TurnoIcono = gtk_image_new_from_file("jugador2.png");
    Jugador2.TurnoToggle = gtk_toggle_button_new();
    gtk_button_set_image(GTK_BUTTON(Jugador2.TurnoToggle), Jugador2.TurnoIcono);
    gtk_button_set_relief(GTK_BUTTON(Jugador2.TurnoToggle), GTK_RELIEF_NONE);
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), Jugador2.TurnoToggle, 1000, 600);
    Jugador2.TurnoNombre = gtk_label_new("Nombre J2");
    gtk_widget_modify_fg(GTK_WIDGET(Jugador2.TurnoNombre), GTK_STATE_NORMAL, &color);
    gtk_widget_modify_font(GTK_WIDGET(Jugador2.TurnoNombre), pango_font_description_from_string("Calibri BOLD 20"));
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), Jugador2.TurnoNombre, 1000, 810);
    Jugador2.TurnoMovimientos = gtk_label_new("Movimientos: ");
    gtk_widget_modify_fg(GTK_WIDGET(Jugador2.TurnoMovimientos), GTK_STATE_NORMAL, &color);
    gtk_widget_modify_font(GTK_WIDGET(Jugador2.TurnoMovimientos), pango_font_description_from_string("Calibri 12"));
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), Jugador2.TurnoMovimientos, 1000, 785);
    Jugador2.TurnoCantidadMovimientos = gtk_label_new("0");
    gtk_widget_modify_fg(GTK_WIDGET(Jugador2.TurnoCantidadMovimientos), GTK_STATE_NORMAL, &color);
    gtk_widget_modify_font(GTK_WIDGET(Jugador2.TurnoCantidadMovimientos), pango_font_description_from_string("Calibri 12"));
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), Jugador2.TurnoCantidadMovimientos, 1120, 785);


//    g_signal_connect(G_OBJECT(Jugador1.TurnoToggle), "toggled", G_CALLBACK(manejadorTurnoJ1), (gpointer) Jugador2.TurnoToggle);
//    g_signal_connect(G_OBJECT(Jugador2.TurnoToggle), "toggled", G_CALLBACK(manejadorTurnoJ2), (gpointer) Jugador1.TurnoToggle);

}

