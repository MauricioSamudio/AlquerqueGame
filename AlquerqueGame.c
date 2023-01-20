#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include<gtk/gtk.h>
#include<glib/gprintf.h>
#include<stdbool.h>

#define ARRIBA     10
#define ABAJO      20
#define DERECHA    30
#define IZQUIERDA  40
#define DIAGONAL_DERECHA_ABAJO 50
#define DIAGONAL_IZQUIERDA_ABAJO 60
#define DIAGONAL_DERECHA_ARRIBA 70
#define DIAGONAL_IZQUIERDA_ARRIBA 80

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

#define J1 100
#define J2 200

#define ACTIVO 50
#define INACTIVO 60


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

GtkBuilder *builder;
GtkWidget *windowAyuda;

int coordenadasTableroX[5][5]; //En esta matriz se guardan las coordenadas (X) del tablero, cada lugar de la matriz representa una posición del tablero.
int coordenadasTableroY[5][5]; //En esta matriz se guardan las coordenadas (Y) del tablero, cada lugar de la matriz representa una posición del tablero.
int queJugador[100][100]; //Matriz analoga a posicionPiezas, en esta se guarda informacion si se trata del Jugador 1 o Jugador 2, ubicadas al mismo tiempo que se inicializaron de forma aleatoria todas las piezas.
int piezasJ1[12]; //Guarda las posiciones random tomadas para no repetirlas, se utiliza para mandar a una función una pieza aleatoria.
int piezasJ2[12]; //Guarda las posiciones random tomadas para no repetirlas, se utiliza para mandar a una función una pieza aleatoria.
int fila = 0, columna = 0; //Índices varios para iterar en loops
int sentidos[9] = {ARRIBA, ABAJO, DERECHA, IZQUIERDA, DIAGONAL_DERECHA_ABAJO,DIAGONAL_IZQUIERDA_ABAJO,DIAGONAL_DERECHA_ARRIBA,DIAGONAL_IZQUIERDA_ARRIBA}; //Se carga en un arreglo los sentidos de los movimientos
int i,j,I,J,K,L;
int limiteInferior = 0, limiteSuperior = 11; //Guardan los "limites superior e inferior" de los vectores de las piezas, para obtener las posiciones aleatorias.
int randomPos; //Guarda la posicion a la hora de recorrer los vectores "piezasJ1" y "piezasJ2".
int piezaRandom; //Guarda momentaneamente la posicion del vector "piezasJ1" y "Piezas J2" para recorrerlo.
int piezaActual; //Se utiliza en las funciones de movimientos, para guardar en que pieza se hizo click.
int jugadorActual; //Se utiliza en las funciones de movimientos, para guardar de que jugador es la pieza en que se hizo click.
int posicionPiezas[8][8]; //En esta matriz se guardan y ubican las piezas en sus respepctivas posiciones imaginando que la matriz es el tablero, luego de que las piezas fueran inicializadas en posiciones random o aleatorias.

void FNconfigFormJuego();
void FNcrearMenusFormJuego();
void FNmostrarPantallaCreditos();
void FNmostrarPantallaAyuda();
void FNcargaCoordenadasTablero();
void FNcrearPiezas();
void FNdimensionarPiezas();
void FNcrearMenusPiezas(); //Función que crea los menús de las piezas
void FNcrearTurnos();
void FNcolocarPiezas();
void FNreiniciarJuego();
void FNconfigMovimientoPiezas();
void FNconectarMenusPiezas();
void FNconectarOPMovimientosPiezas();
void FNmoverAbajo(GtkWidget *pieza);
void FNmoverArriba(GtkWidget *pieza);
void FNmoverDerecha(GtkWidget *pieza);
void FNmoverDiagonalDerecha(GtkWidget *pieza);
void FNmoverIzquierda(GtkWidget *pieza);
void FNmostrarOPmenusPiezas();
void manejadorTurnoJ1(GtkToggleButton *turno);
void manejadorTurnoJ2(GtkToggleButton *turno);
void habilitarOPmovimientosJ1();
void habilitarOPmovimientosJ2();
void deshabilitarOPmovimientosJ1();
void deshabilitarOPmovimientosJ2();
static void FNiniciarPiezasJ1();
static void FNiniciarPiezasJ2();

int desplegarMenuMovimiento(GtkWidget *widget, GdkEvent *event);

int siSobrePasaLimites (int filaOcolumna, int sentido);
int siLugarEstaOcupado(int K, int L, int sentido); //Verifica si el lugar al que se desea mover la pieza esta ocupado. Evita el intercambio sin sentido de piezas.

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

struct Movimientos { //Guarda las opciones, labels, iconos y contenedores de los movimientos de las opciones de movimientos de las piezas. (Se anida con la estructura Juego)
    GtkWidget *OPmoverArriba;
    GtkWidget *OPmoverAbajo;
    GtkWidget *OPmoverDerecha;
    GtkWidget *OPmoverDiagonalDerecha;
    GtkWidget *OPmoverIzquierda;
    GtkWidget *OPcancelar;

    GtkWidget *LBLmoverArriba;
    GtkWidget *LBLmoverAbajo;
    GtkWidget *LBLmoverDerecha;
    GtkWidget *LBLmoverDiagonalDerecha;
    GtkWidget *LBLmoverIzquierda;
    GtkWidget *LBLcancelar;

    GtkWidget *BOXmoverArriba;
    GtkWidget *BOXmoverAbajo;
    GtkWidget *BOXmoverDerecha;
    GtkWidget *BOXmoverDiagonalDerecha;
    GtkWidget *BOXmoverIzquierda;
    GtkWidget *BOXcancelar;

    GtkWidget *ICOmoverArriba;
    GtkWidget *ICOmoverAbajo;
    GtkWidget *ICOmoverDerecha;
    GtkWidget *ICOmoverDiagonalDerecha;
    GtkWidget *ICOmoverIzquierda;
    GtkWidget *ICOcancelar;

};

struct Juego { //Guarda todos los objetos de cada pieza, el objeto pieza en sí mismo, su imagen, su menú, el peso de cada pieza y sus movimientos. (Se anida con la estrucutra de Movimientos)
    GtkWidget *Pieza;
    int Peso;
    GtkWidget *Imagen;
    GtkWidget *Menu;
    struct Movimientos movimiento;
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


    app = gtk_application_new ("ALQUERQUE.exe", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (FNconfigFormJuego), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    FNcargaCoordenadasTablero(); //Se cargan las coordenadas X e Y del layout del tablero, en una matriz con posiciones analogas a la matriz que guarda las piezas.

    FNconfigFormJuego(); //Se configura todo lo que tenga que ver con la interfaz vistosa de la pantalla pricipal de juego, esta pantalla se nombro formJuego

    FNcrearPiezas();
    FNcrearTurnos(); //Se crean los turnos de los jugadores.

   FNconfigMovimientoPiezas(); //Se configura el movimiento de las piezas

  //   FNimprimirMatrices(); //Se imprime en consola las matrices con que se trabajan, para el control de los datos de los movimientos.


    gtk_widget_show_all(formJuego.Pantalla); //Se muestra todo lo que hay en pantalla.
    gtk_main(); //Definición del loop del programa principal main.

    return status;
}
void FNconfigMovimientoPiezas(){ //Llama de forma ordenada a las funciones encargadas del movimiento de las piezas.

    FNcrearMenusPiezas();
    FNconectarMenusPiezas();
    FNconectarOPMovimientosPiezas();

}

void FNcrearMenusPiezas(){ //Crea los menús de cada pieza, los cuales se despliegan al hacer distíntos clicks en ellas (MOVER Y EMPUJARESTIRAR)

/// Se crean los SubMenus de cada pieza, y se agregan a sus respectivos menus

//-------------------------------FICHA 1-------------------------------
//-------------------------------CREANDO------------------------------------
    ///Jugador1
        //Mover
    FNegra1.Menu                                 = gtk_menu_new();

    FNegra1.movimiento.OPmoverArriba             = gtk_menu_item_new();
    FNegra1.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    FNegra1.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    FNegra1.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
    FNegra1.movimiento.OPmoverDiagonalDerecha    = gtk_menu_item_new();
    FNegra1.movimiento.OPcancelar                = gtk_menu_item_new();

    FNegra2.Menu                                 = gtk_menu_new();

    FNegra2.movimiento.OPmoverArriba             = gtk_menu_item_new();
    FNegra2.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    FNegra2.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    FNegra2.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
    FNegra2.movimiento.OPmoverDiagonalDerecha    = gtk_menu_item_new();
    FNegra2.movimiento.OPcancelar                = gtk_menu_item_new();

    FNegra3.Menu                                 = gtk_menu_new();

    FNegra3.movimiento.OPmoverArriba             = gtk_menu_item_new();
    FNegra3.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    FNegra3.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    FNegra3.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
    FNegra3.movimiento.OPmoverDiagonalDerecha    = gtk_menu_item_new();
    FNegra3.movimiento.OPcancelar                = gtk_menu_item_new();

    FNegra4.Menu                                 = gtk_menu_new();

    FNegra4.movimiento.OPmoverArriba             = gtk_menu_item_new();
    FNegra4.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    FNegra4.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    FNegra4.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
    FNegra4.movimiento.OPmoverDiagonalDerecha    = gtk_menu_item_new();
    FNegra4.movimiento.OPcancelar                = gtk_menu_item_new();

    FNegra5.Menu                                 = gtk_menu_new();

    FNegra5.movimiento.OPmoverArriba             = gtk_menu_item_new();
    FNegra5.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    FNegra5.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    FNegra5.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
    FNegra5.movimiento.OPmoverDiagonalDerecha    = gtk_menu_item_new();
    FNegra5.movimiento.OPcancelar                = gtk_menu_item_new();

    FNegra6.Menu                                 = gtk_menu_new();

    FNegra6.movimiento.OPmoverArriba             = gtk_menu_item_new();
    FNegra6.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    FNegra6.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    FNegra6.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
    FNegra6.movimiento.OPmoverDiagonalDerecha    = gtk_menu_item_new();
    FNegra6.movimiento.OPcancelar                = gtk_menu_item_new();

    FNegra7.Menu                                 = gtk_menu_new();

    FNegra7.movimiento.OPmoverArriba             = gtk_menu_item_new();
    FNegra7.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    FNegra7.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    FNegra7.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
    FNegra7.movimiento.OPmoverDiagonalDerecha    = gtk_menu_item_new();
    FNegra7.movimiento.OPcancelar                = gtk_menu_item_new();

    FNegra8.Menu                                 = gtk_menu_new();

    FNegra8.movimiento.OPmoverArriba             = gtk_menu_item_new();
    FNegra8.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    FNegra8.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    FNegra8.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
    FNegra8.movimiento.OPmoverDiagonalDerecha    = gtk_menu_item_new();
    FNegra8.movimiento.OPcancelar                = gtk_menu_item_new();

    FNegra9.Menu                                 = gtk_menu_new();

    FNegra9.movimiento.OPmoverArriba             = gtk_menu_item_new();
    FNegra9.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    FNegra9.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    FNegra9.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
    FNegra9.movimiento.OPmoverDiagonalDerecha    = gtk_menu_item_new();
    FNegra9.movimiento.OPcancelar                = gtk_menu_item_new();

    FNegra10.Menu                                 = gtk_menu_new();

    FNegra10.movimiento.OPmoverArriba             = gtk_menu_item_new();
    FNegra10.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    FNegra10.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    FNegra10.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
    FNegra10.movimiento.OPmoverDiagonalDerecha    = gtk_menu_item_new();
    FNegra10.movimiento.OPcancelar                = gtk_menu_item_new();

    FNegra11.Menu                                 = gtk_menu_new();

    FNegra11.movimiento.OPmoverArriba             = gtk_menu_item_new();
    FNegra11.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    FNegra11.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    FNegra11.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
    FNegra11.movimiento.OPmoverDiagonalDerecha    = gtk_menu_item_new();
    FNegra11.movimiento.OPcancelar                = gtk_menu_item_new();

    FNegra12.Menu                                 = gtk_menu_new();

    FNegra12.movimiento.OPmoverArriba             = gtk_menu_item_new();
    FNegra12.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    FNegra12.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    FNegra12.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
    FNegra12.movimiento.OPmoverDiagonalDerecha    = gtk_menu_item_new();
    FNegra12.movimiento.OPcancelar                = gtk_menu_item_new();

    ///Jugador 2
    //Mover
    FBlanca1.Menu                                 = gtk_menu_new();

    FBlanca1.movimiento.OPmoverArriba             = gtk_menu_item_new();
    FBlanca1.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    FBlanca1.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    FBlanca1.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
    FBlanca1.movimiento.OPmoverDiagonalDerecha    = gtk_menu_item_new();
    FBlanca1.movimiento.OPcancelar                = gtk_menu_item_new();

    FBlanca2.Menu                                 = gtk_menu_new();

    FBlanca2.movimiento.OPmoverArriba             = gtk_menu_item_new();
    FBlanca2.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    FBlanca2.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    FBlanca2.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
    FBlanca2.movimiento.OPmoverDiagonalDerecha    = gtk_menu_item_new();
    FBlanca2.movimiento.OPcancelar                = gtk_menu_item_new();

    FBlanca3.Menu                                 = gtk_menu_new();

    FBlanca3.movimiento.OPmoverArriba             = gtk_menu_item_new();
    FBlanca3.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    FBlanca3.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    FBlanca3.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
    FBlanca3.movimiento.OPmoverDiagonalDerecha    = gtk_menu_item_new();
    FBlanca3.movimiento.OPcancelar                = gtk_menu_item_new();

    FBlanca4.Menu                                 = gtk_menu_new();

    FBlanca4.movimiento.OPmoverArriba             = gtk_menu_item_new();
    FBlanca4.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    FBlanca4.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    FBlanca4.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
    FBlanca4.movimiento.OPmoverDiagonalDerecha    = gtk_menu_item_new();
    FBlanca4.movimiento.OPcancelar                = gtk_menu_item_new();

    FBlanca5.Menu                                 = gtk_menu_new();

    FBlanca5.movimiento.OPmoverArriba             = gtk_menu_item_new();
    FBlanca5.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    FBlanca5.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    FBlanca5.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
    FBlanca5.movimiento.OPmoverDiagonalDerecha    = gtk_menu_item_new();
    FBlanca5.movimiento.OPcancelar                = gtk_menu_item_new();

    FBlanca6.Menu                                 = gtk_menu_new();

    FBlanca6.movimiento.OPmoverArriba             = gtk_menu_item_new();
    FBlanca6.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    FBlanca6.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    FBlanca6.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
    FBlanca6.movimiento.OPmoverDiagonalDerecha    = gtk_menu_item_new();
    FBlanca6.movimiento.OPcancelar                = gtk_menu_item_new();

    FBlanca7.Menu                                 = gtk_menu_new();

    FBlanca7.movimiento.OPmoverArriba             = gtk_menu_item_new();
    FBlanca7.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    FBlanca7.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    FBlanca7.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
    FBlanca7.movimiento.OPmoverDiagonalDerecha    = gtk_menu_item_new();
    FBlanca7.movimiento.OPcancelar                = gtk_menu_item_new();

    FBlanca8.Menu                                 = gtk_menu_new();

    FBlanca8.movimiento.OPmoverArriba             = gtk_menu_item_new();
    FBlanca8.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    FBlanca8.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    FBlanca8.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
    FBlanca8.movimiento.OPmoverDiagonalDerecha    = gtk_menu_item_new();
    FBlanca8.movimiento.OPcancelar                = gtk_menu_item_new();

    FBlanca9.Menu                                 = gtk_menu_new();

    FBlanca9.movimiento.OPmoverArriba             = gtk_menu_item_new();
    FBlanca9.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    FBlanca9.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    FBlanca9.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
    FBlanca9.movimiento.OPmoverDiagonalDerecha    = gtk_menu_item_new();
    FBlanca9.movimiento.OPcancelar                = gtk_menu_item_new();

    FBlanca10.Menu                                 = gtk_menu_new();

    FBlanca10.movimiento.OPmoverArriba             = gtk_menu_item_new();
    FBlanca10.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    FBlanca10.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    FBlanca10.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
    FBlanca10.movimiento.OPmoverDiagonalDerecha    = gtk_menu_item_new();
    FBlanca10.movimiento.OPcancelar                = gtk_menu_item_new();

    FBlanca11.Menu                                 = gtk_menu_new();

    FBlanca11.movimiento.OPmoverArriba             = gtk_menu_item_new();
    FBlanca11.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    FBlanca11.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    FBlanca11.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
    FBlanca11.movimiento.OPmoverDiagonalDerecha    = gtk_menu_item_new();
    FBlanca11.movimiento.OPcancelar                = gtk_menu_item_new();

    FBlanca12.Menu                                 = gtk_menu_new();

    FBlanca12.movimiento.OPmoverArriba             = gtk_menu_item_new();
    FBlanca12.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    FBlanca12.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    FBlanca12.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
    FBlanca12.movimiento.OPmoverDiagonalDerecha    = gtk_menu_item_new();
    FBlanca12.movimiento.OPcancelar                = gtk_menu_item_new();

//-------------------------------AGREGANDO-------------------------------
    ///Jugador1
        //Mover
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra1.Menu), FNegra1.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra1.Menu), FNegra1.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra1.Menu), FNegra1.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra1.Menu), FNegra1.movimiento.OPmoverDiagonalDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra1.Menu), FNegra1.movimiento.OPmoverIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra1.Menu), FNegra1.movimiento.OPcancelar);

    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra2.Menu), FNegra2.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra2.Menu), FNegra2.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra2.Menu), FNegra2.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra2.Menu), FNegra2.movimiento.OPmoverDiagonalDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra2.Menu), FNegra2.movimiento.OPmoverIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra2.Menu), FNegra2.movimiento.OPcancelar);

    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra3.Menu), FNegra3.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra3.Menu), FNegra3.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra3.Menu), FNegra3.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra3.Menu), FNegra3.movimiento.OPmoverDiagonalDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra3.Menu), FNegra3.movimiento.OPmoverIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra3.Menu), FNegra3.movimiento.OPcancelar);

    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra4.Menu), FNegra4.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra4.Menu), FNegra4.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra4.Menu), FNegra4.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra4.Menu), FNegra4.movimiento.OPmoverDiagonalDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra4.Menu), FNegra4.movimiento.OPmoverIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra4.Menu), FNegra4.movimiento.OPcancelar);

    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra5.Menu), FNegra5.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra5.Menu), FNegra5.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra5.Menu), FNegra5.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra5.Menu), FNegra5.movimiento.OPmoverDiagonalDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra5.Menu), FNegra5.movimiento.OPmoverIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra5.Menu), FNegra5.movimiento.OPcancelar);

    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra6.Menu), FNegra6.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra6.Menu), FNegra6.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra6.Menu), FNegra6.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra6.Menu), FNegra6.movimiento.OPmoverDiagonalDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra6.Menu), FNegra6.movimiento.OPmoverIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra6.Menu), FNegra6.movimiento.OPcancelar);

    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra7.Menu), FNegra7.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra7.Menu), FNegra7.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra7.Menu), FNegra7.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra7.Menu), FNegra7.movimiento.OPmoverDiagonalDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra7.Menu), FNegra7.movimiento.OPmoverIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra7.Menu), FNegra7.movimiento.OPcancelar);

    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra8.Menu), FNegra8.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra8.Menu), FNegra8.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra8.Menu), FNegra8.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra8.Menu), FNegra8.movimiento.OPmoverDiagonalDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra8.Menu), FNegra8.movimiento.OPmoverIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra8.Menu), FNegra8.movimiento.OPcancelar);

    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra9.Menu), FNegra9.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra9.Menu), FNegra9.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra9.Menu), FNegra9.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra9.Menu), FNegra9.movimiento.OPmoverDiagonalDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra9.Menu), FNegra9.movimiento.OPmoverIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra9.Menu), FNegra9.movimiento.OPcancelar);

    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra10.Menu), FNegra10.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra10.Menu), FNegra10.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra10.Menu), FNegra10.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra10.Menu), FNegra10.movimiento.OPmoverDiagonalDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra10.Menu), FNegra10.movimiento.OPmoverIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra10.Menu), FNegra10.movimiento.OPcancelar);

    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra11.Menu), FNegra11.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra11.Menu), FNegra11.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra11.Menu), FNegra11.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra11.Menu), FNegra11.movimiento.OPmoverDiagonalDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra11.Menu), FNegra11.movimiento.OPmoverIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra11.Menu), FNegra11.movimiento.OPcancelar);

    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra12.Menu), FNegra12.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra12.Menu), FNegra12.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra12.Menu), FNegra12.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra12.Menu), FNegra12.movimiento.OPmoverDiagonalDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra12.Menu), FNegra12.movimiento.OPmoverIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(FNegra12.Menu), FNegra12.movimiento.OPcancelar);

    ///Jugador 2
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca1.Menu), FBlanca1.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca1.Menu), FBlanca1.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca1.Menu), FBlanca1.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca1.Menu), FBlanca1.movimiento.OPmoverDiagonalDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca1.Menu), FBlanca1.movimiento.OPmoverIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca1.Menu), FBlanca1.movimiento.OPcancelar);

    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca2.Menu), FBlanca2.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca2.Menu), FBlanca2.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca2.Menu), FBlanca2.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca2.Menu), FBlanca2.movimiento.OPmoverDiagonalDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca2.Menu), FBlanca2.movimiento.OPmoverIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca2.Menu), FBlanca2.movimiento.OPcancelar);

    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca3.Menu), FBlanca3.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca3.Menu), FBlanca3.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca3.Menu), FBlanca3.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca3.Menu), FBlanca3.movimiento.OPmoverDiagonalDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca3.Menu), FBlanca3.movimiento.OPmoverIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca3.Menu), FBlanca3.movimiento.OPcancelar);

    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca4.Menu), FBlanca4.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca4.Menu), FBlanca4.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca4.Menu), FBlanca4.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca4.Menu), FBlanca4.movimiento.OPmoverDiagonalDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca4.Menu), FBlanca4.movimiento.OPmoverIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca4.Menu), FBlanca4.movimiento.OPcancelar);

    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca5.Menu), FBlanca5.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca5.Menu), FBlanca5.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca5.Menu), FBlanca5.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca5.Menu), FBlanca5.movimiento.OPmoverDiagonalDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca5.Menu), FBlanca5.movimiento.OPmoverIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca5.Menu), FBlanca5.movimiento.OPcancelar);

    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca6.Menu), FBlanca6.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca6.Menu), FBlanca6.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca6.Menu), FBlanca6.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca6.Menu), FBlanca6.movimiento.OPmoverDiagonalDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca6.Menu), FBlanca6.movimiento.OPmoverIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca6.Menu), FBlanca6.movimiento.OPcancelar);

    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca7.Menu), FBlanca7.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca7.Menu), FBlanca7.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca7.Menu), FBlanca7.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca7.Menu), FBlanca7.movimiento.OPmoverDiagonalDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca7.Menu), FBlanca7.movimiento.OPmoverIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca7.Menu), FBlanca7.movimiento.OPcancelar);

    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca8.Menu), FBlanca8.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca8.Menu), FBlanca8.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca8.Menu), FBlanca8.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca8.Menu), FBlanca8.movimiento.OPmoverDiagonalDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca8.Menu), FBlanca8.movimiento.OPmoverIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca8.Menu), FBlanca8.movimiento.OPcancelar);

    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca9.Menu), FBlanca9.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca9.Menu), FBlanca9.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca9.Menu), FBlanca9.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca9.Menu), FBlanca9.movimiento.OPmoverDiagonalDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca9.Menu), FBlanca9.movimiento.OPmoverIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca9.Menu), FBlanca9.movimiento.OPcancelar);

    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca10.Menu), FBlanca10.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca10.Menu), FBlanca10.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca10.Menu), FBlanca10.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca10.Menu), FBlanca10.movimiento.OPmoverDiagonalDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca10.Menu), FBlanca10.movimiento.OPmoverIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca10.Menu), FBlanca10.movimiento.OPcancelar);

    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca11.Menu), FBlanca11.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca11.Menu), FBlanca11.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca11.Menu), FBlanca11.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca11.Menu), FBlanca11.movimiento.OPmoverDiagonalDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca11.Menu), FBlanca11.movimiento.OPmoverIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca11.Menu), FBlanca11.movimiento.OPcancelar);

    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca12.Menu), FBlanca12.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca12.Menu), FBlanca12.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca12.Menu), FBlanca12.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca12.Menu), FBlanca12.movimiento.OPmoverDiagonalDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca12.Menu), FBlanca12.movimiento.OPmoverIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(FBlanca12.Menu), FBlanca12.movimiento.OPcancelar);

//----------------------------------MOVER ARRIBA----------------------------------//

//Cargando iconos MOVER ARRIBA para todas las piezas
    FNegra1.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    FNegra2.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    FNegra3.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    FNegra4.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    FNegra5.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    FNegra6.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    FNegra7.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    FNegra8.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    FNegra9.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    FNegra10.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    FNegra11.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    FNegra12.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");

    FBlanca1.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    FBlanca2.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    FBlanca3.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    FBlanca4.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    FBlanca5.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    FBlanca6.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    FBlanca7.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    FBlanca8.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    FBlanca9.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    FBlanca10.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    FBlanca11.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    FBlanca12.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");

//Cargando LABEL MOVER ARRIBA ARRIBA para todas las piezas
    FNegra1.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    FNegra2.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    FNegra3.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    FNegra4.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    FNegra5.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    FNegra6.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    FNegra7.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    FNegra8.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    FNegra9.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    FNegra10.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    FNegra11.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    FNegra12.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");

    FBlanca1.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    FBlanca2.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    FBlanca3.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    FBlanca4.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    FBlanca5.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    FBlanca6.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    FBlanca7.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    FBlanca8.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    FBlanca9.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    FBlanca10.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    FBlanca11.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    FBlanca12.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");

//Creando caja contenedora BOX para MOVER ARRIBA de todas las piezas
    FNegra1.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra2.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra3.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra4.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra5.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra6.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra7.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra8.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra9.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra10.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra11.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra12.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

    FBlanca1.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca2.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca3.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca4.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca5.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca6.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca7.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca8.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca9.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca10.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca11.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca12.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

//Cargando los iconos a la caja contenedora BOX
    gtk_container_add(GTK_CONTAINER(FNegra1.movimiento.BOXmoverArriba) ,  FNegra1.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra2.movimiento.BOXmoverArriba) ,  FNegra2.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra3.movimiento.BOXmoverArriba) ,  FNegra3.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra4.movimiento.BOXmoverArriba) ,  FNegra4.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra5.movimiento.BOXmoverArriba) ,  FNegra5.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra6.movimiento.BOXmoverArriba) ,  FNegra6.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra7.movimiento.BOXmoverArriba) ,  FNegra7.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra8.movimiento.BOXmoverArriba) ,  FNegra8.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra9.movimiento.BOXmoverArriba) ,  FNegra9.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra10.movimiento.BOXmoverArriba) ,  FNegra10.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra11.movimiento.BOXmoverArriba) ,  FNegra11.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra12.movimiento.BOXmoverArriba) ,  FNegra12.movimiento.ICOmoverArriba);

    gtk_container_add(GTK_CONTAINER(FBlanca1.movimiento.BOXmoverArriba) ,  FBlanca1.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca2.movimiento.BOXmoverArriba) ,  FBlanca2.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca3.movimiento.BOXmoverArriba) ,  FBlanca3.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca4.movimiento.BOXmoverArriba) ,  FBlanca4.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca5.movimiento.BOXmoverArriba) ,  FBlanca5.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca6.movimiento.BOXmoverArriba) ,  FBlanca6.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca7.movimiento.BOXmoverArriba) ,  FBlanca7.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca8.movimiento.BOXmoverArriba) ,  FBlanca8.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca9.movimiento.BOXmoverArriba) ,  FBlanca9.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca10.movimiento.BOXmoverArriba) ,  FBlanca10.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca11.movimiento.BOXmoverArriba) ,  FBlanca11.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca12.movimiento.BOXmoverArriba) ,  FBlanca12.movimiento.ICOmoverArriba);


//Cargando los Labels a la caja contenedora BOX
    gtk_container_add(GTK_CONTAINER(FNegra1.movimiento.BOXmoverArriba) ,  FNegra1.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra2.movimiento.BOXmoverArriba) ,  FNegra2.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra3.movimiento.BOXmoverArriba) ,  FNegra3.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra4.movimiento.BOXmoverArriba) ,  FNegra4.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra5.movimiento.BOXmoverArriba) ,  FNegra5.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra6.movimiento.BOXmoverArriba) ,  FNegra6.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra7.movimiento.BOXmoverArriba) ,  FNegra7.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra8.movimiento.BOXmoverArriba) ,  FNegra8.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra9.movimiento.BOXmoverArriba) ,  FNegra9.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra10.movimiento.BOXmoverArriba) ,  FNegra10.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra11.movimiento.BOXmoverArriba) ,  FNegra11.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra12.movimiento.BOXmoverArriba) ,  FNegra12.movimiento.LBLmoverArriba);

    gtk_container_add(GTK_CONTAINER(FBlanca1.movimiento.BOXmoverArriba) ,  FBlanca1.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca2.movimiento.BOXmoverArriba) ,  FBlanca2.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca3.movimiento.BOXmoverArriba) ,  FBlanca3.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca4.movimiento.BOXmoverArriba) ,  FBlanca4.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca5.movimiento.BOXmoverArriba) ,  FBlanca5.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca6.movimiento.BOXmoverArriba) ,  FBlanca6.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca7.movimiento.BOXmoverArriba) ,  FBlanca7.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca8.movimiento.BOXmoverArriba) ,  FBlanca8.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca9.movimiento.BOXmoverArriba) ,  FBlanca9.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca10.movimiento.BOXmoverArriba) ,  FBlanca10.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca11.movimiento.BOXmoverArriba) ,  FBlanca11.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca12.movimiento.BOXmoverArriba) ,  FBlanca12.movimiento.LBLmoverArriba);

//Agregando la caja contenedora BOX a cada menu
    gtk_container_add(GTK_CONTAINER(FNegra1.movimiento.OPmoverArriba) ,  FNegra1.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra2.movimiento.OPmoverArriba) ,  FNegra2.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra3.movimiento.OPmoverArriba) ,  FNegra3.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra4.movimiento.OPmoverArriba) ,  FNegra4.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra5.movimiento.OPmoverArriba) ,  FNegra5.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra6.movimiento.OPmoverArriba) ,  FNegra6.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra7.movimiento.OPmoverArriba) ,  FNegra7.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra8.movimiento.OPmoverArriba) ,  FNegra8.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra9.movimiento.OPmoverArriba) ,  FNegra9.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra10.movimiento.OPmoverArriba) ,  FNegra10.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra11.movimiento.OPmoverArriba) ,  FNegra11.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(FNegra12.movimiento.OPmoverArriba) ,  FNegra12.movimiento.BOXmoverArriba);

    gtk_container_add(GTK_CONTAINER(FBlanca1.movimiento.OPmoverArriba) ,  FBlanca1.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca2.movimiento.OPmoverArriba) ,  FBlanca2.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca3.movimiento.OPmoverArriba) ,  FBlanca3.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca4.movimiento.OPmoverArriba) ,  FBlanca4.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca5.movimiento.OPmoverArriba) ,  FBlanca5.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca6.movimiento.OPmoverArriba) ,  FBlanca6.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca7.movimiento.OPmoverArriba) ,  FBlanca7.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca8.movimiento.OPmoverArriba) ,  FBlanca8.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca9.movimiento.OPmoverArriba) ,  FBlanca9.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca10.movimiento.OPmoverArriba) ,  FBlanca10.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca11.movimiento.OPmoverArriba) ,  FBlanca11.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(FBlanca12.movimiento.OPmoverArriba) ,  FBlanca12.movimiento.BOXmoverArriba);

//----------------------------------MOVER ABAJO----------------------------------//

//Cargando iconos MOVER ABAJO para todas las piezas
    FNegra1.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    FNegra2.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    FNegra3.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    FNegra4.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    FNegra5.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    FNegra6.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    FNegra7.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    FNegra8.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    FNegra9.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    FNegra10.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    FNegra11.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    FNegra12.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");

    FBlanca1.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    FBlanca2.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    FBlanca3.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    FBlanca4.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    FBlanca5.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    FBlanca6.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    FBlanca7.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    FBlanca8.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    FBlanca9.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    FBlanca10.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    FBlanca11.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    FBlanca12.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");

//Cargando LABEL MOVER ARRIBA ABAJO para todas las piezas
    FNegra1.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    FNegra2.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    FNegra3.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    FNegra4.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    FNegra5.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    FNegra6.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    FNegra7.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    FNegra8.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    FNegra9.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    FNegra10.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    FNegra11.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    FNegra12.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");

    FBlanca1.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    FBlanca2.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    FBlanca3.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    FBlanca4.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    FBlanca5.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    FBlanca6.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    FBlanca7.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    FBlanca8.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    FBlanca9.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    FBlanca10.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    FBlanca11.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    FBlanca12.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");

//Creando caja contenedora BOX para MOVER ABAJO de todas las piezas
    FNegra1.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra2.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra3.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra4.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra5.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra6.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra7.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra8.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra9.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra10.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra11.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra12.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

    FBlanca1.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca2.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca3.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca4.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca5.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca6.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca7.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca8.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca9.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca10.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca11.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca12.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

//Cargando los iconos a la caja contenedora BOX
    gtk_container_add(GTK_CONTAINER(FNegra1.movimiento.BOXmoverAbajo) ,  FNegra1.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra2.movimiento.BOXmoverAbajo) ,  FNegra2.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra3.movimiento.BOXmoverAbajo) ,  FNegra3.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra4.movimiento.BOXmoverAbajo) ,  FNegra4.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra5.movimiento.BOXmoverAbajo) ,  FNegra5.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra6.movimiento.BOXmoverAbajo) ,  FNegra6.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra7.movimiento.BOXmoverAbajo) ,  FNegra7.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra8.movimiento.BOXmoverAbajo) ,  FNegra8.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra9.movimiento.BOXmoverAbajo) ,  FNegra9.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra10.movimiento.BOXmoverAbajo) ,  FNegra10.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra11.movimiento.BOXmoverAbajo) ,  FNegra11.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra12.movimiento.BOXmoverAbajo) ,  FNegra12.movimiento.ICOmoverAbajo);

    gtk_container_add(GTK_CONTAINER(FBlanca1.movimiento.BOXmoverAbajo) ,  FBlanca1.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca2.movimiento.BOXmoverAbajo) ,  FBlanca2.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca3.movimiento.BOXmoverAbajo) ,  FBlanca3.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca4.movimiento.BOXmoverAbajo) ,  FBlanca4.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca5.movimiento.BOXmoverAbajo) ,  FBlanca5.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca6.movimiento.BOXmoverAbajo) ,  FBlanca6.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca7.movimiento.BOXmoverAbajo) ,  FBlanca7.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca8.movimiento.BOXmoverAbajo) ,  FBlanca8.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca9.movimiento.BOXmoverAbajo) ,  FBlanca9.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca10.movimiento.BOXmoverAbajo) ,  FBlanca10.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca11.movimiento.BOXmoverAbajo) ,  FBlanca11.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca12.movimiento.BOXmoverAbajo) ,  FBlanca12.movimiento.ICOmoverAbajo);

//Cargando los Labels a la caja contenedora BOX
    gtk_container_add(GTK_CONTAINER(FNegra1.movimiento.BOXmoverAbajo) ,  FNegra1.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra2.movimiento.BOXmoverAbajo) ,  FNegra2.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra3.movimiento.BOXmoverAbajo) ,  FNegra3.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra4.movimiento.BOXmoverAbajo) ,  FNegra4.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra5.movimiento.BOXmoverAbajo) ,  FNegra5.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra6.movimiento.BOXmoverAbajo) ,  FNegra6.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra7.movimiento.BOXmoverAbajo) ,  FNegra7.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra8.movimiento.BOXmoverAbajo) ,  FNegra8.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra9.movimiento.BOXmoverAbajo) ,  FNegra9.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra10.movimiento.BOXmoverAbajo) ,  FNegra10.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra11.movimiento.BOXmoverAbajo) ,  FNegra11.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra12.movimiento.BOXmoverAbajo) ,  FNegra12.movimiento.LBLmoverAbajo);

    gtk_container_add(GTK_CONTAINER(FBlanca1.movimiento.BOXmoverAbajo) ,  FBlanca1.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca2.movimiento.BOXmoverAbajo) ,  FBlanca2.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca3.movimiento.BOXmoverAbajo) ,  FBlanca3.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca4.movimiento.BOXmoverAbajo) ,  FBlanca4.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca5.movimiento.BOXmoverAbajo) ,  FBlanca5.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca6.movimiento.BOXmoverAbajo) ,  FBlanca6.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca7.movimiento.BOXmoverAbajo) ,  FBlanca7.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca8.movimiento.BOXmoverAbajo) ,  FBlanca8.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca9.movimiento.BOXmoverAbajo) ,  FBlanca9.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca10.movimiento.BOXmoverAbajo) ,  FBlanca10.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca11.movimiento.BOXmoverAbajo) ,  FBlanca11.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca12.movimiento.BOXmoverAbajo) ,  FBlanca12.movimiento.LBLmoverAbajo);

//Agregando la caja contenedora BOX a cada menu
    gtk_container_add(GTK_CONTAINER(FNegra1.movimiento.OPmoverAbajo) ,  FNegra1.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra2.movimiento.OPmoverAbajo) ,  FNegra2.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra3.movimiento.OPmoverAbajo) ,  FNegra3.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra4.movimiento.OPmoverAbajo) ,  FNegra4.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra5.movimiento.OPmoverAbajo) ,  FNegra5.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra6.movimiento.OPmoverAbajo) ,  FNegra6.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra7.movimiento.OPmoverAbajo) ,  FNegra7.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra8.movimiento.OPmoverAbajo) ,  FNegra8.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra9.movimiento.OPmoverAbajo) ,  FNegra9.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra10.movimiento.OPmoverAbajo) ,  FNegra10.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra11.movimiento.OPmoverAbajo) ,  FNegra11.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FNegra12.movimiento.OPmoverAbajo) ,  FNegra12.movimiento.BOXmoverAbajo);

    gtk_container_add(GTK_CONTAINER(FBlanca1.movimiento.OPmoverAbajo) ,  FBlanca1.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca2.movimiento.OPmoverAbajo) ,  FBlanca2.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca3.movimiento.OPmoverAbajo) ,  FBlanca3.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca4.movimiento.OPmoverAbajo) ,  FBlanca4.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca5.movimiento.OPmoverAbajo) ,  FBlanca5.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca6.movimiento.OPmoverAbajo) ,  FBlanca6.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca7.movimiento.OPmoverAbajo) ,  FBlanca7.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca8.movimiento.OPmoverAbajo) ,  FBlanca8.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca9.movimiento.OPmoverAbajo) ,  FBlanca9.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca10.movimiento.OPmoverAbajo) ,  FBlanca10.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca11.movimiento.OPmoverAbajo) ,  FBlanca11.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(FBlanca12.movimiento.OPmoverAbajo) ,  FBlanca12.movimiento.BOXmoverAbajo);

//------------------------------DERECHA------------------------------------------------------------

//Cargando iconos MOVER DERECHA para todas las piezas
    FNegra1.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    FNegra2.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    FNegra3.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    FNegra4.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    FNegra5.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    FNegra6.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    FNegra7.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    FNegra8.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    FNegra9.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    FNegra10.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    FNegra11.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    FNegra12.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");

    FBlanca1.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    FBlanca2.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    FBlanca3.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    FBlanca4.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    FBlanca5.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    FBlanca6.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    FBlanca7.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    FBlanca8.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    FBlanca9.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    FBlanca10.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    FBlanca11.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    FBlanca12.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");

//Cargando LABEL MOVER ARRIBA ABAJO para todas las piezas
    FNegra1.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    FNegra2.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    FNegra3.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    FNegra4.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    FNegra5.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    FNegra6.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    FNegra7.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    FNegra8.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    FNegra9.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    FNegra10.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    FNegra11.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    FNegra12.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");

    FBlanca1.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    FBlanca2.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    FBlanca3.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    FBlanca4.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    FBlanca5.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    FBlanca6.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    FBlanca7.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    FBlanca8.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    FBlanca9.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    FBlanca10.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    FBlanca11.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    FBlanca12.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");

//Creando caja contenedora BOX para MOVER ABAJO de todas las piezas
    FNegra1.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra2.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra3.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra4.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra5.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra6.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra7.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra8.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra9.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra10.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra11.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra12.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

    FBlanca1.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca2.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca3.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca4.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca5.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca6.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca7.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca8.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca9.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca10.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca11.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca12.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

//Cargando los iconos a la caja contenedora BOX
    gtk_container_add(GTK_CONTAINER(FNegra1.movimiento.BOXmoverDerecha) ,  FNegra1.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra2.movimiento.BOXmoverDerecha) ,  FNegra2.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra3.movimiento.BOXmoverDerecha) ,  FNegra3.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra4.movimiento.BOXmoverDerecha) ,  FNegra4.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra5.movimiento.BOXmoverDerecha) ,  FNegra5.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra6.movimiento.BOXmoverDerecha) ,  FNegra6.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra7.movimiento.BOXmoverDerecha) ,  FNegra7.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra8.movimiento.BOXmoverDerecha) ,  FNegra8.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra9.movimiento.BOXmoverDerecha) ,  FNegra9.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra10.movimiento.BOXmoverDerecha) ,  FNegra10.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra11.movimiento.BOXmoverDerecha) ,  FNegra11.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra12.movimiento.BOXmoverDerecha) ,  FNegra12.movimiento.ICOmoverDerecha);

    gtk_container_add(GTK_CONTAINER(FBlanca1.movimiento.BOXmoverDerecha) ,  FBlanca1.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca2.movimiento.BOXmoverDerecha) ,  FBlanca2.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca3.movimiento.BOXmoverDerecha) ,  FBlanca3.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca4.movimiento.BOXmoverDerecha) ,  FBlanca4.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca5.movimiento.BOXmoverDerecha) ,  FBlanca5.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca6.movimiento.BOXmoverDerecha) ,  FBlanca6.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca7.movimiento.BOXmoverDerecha) ,  FBlanca7.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca8.movimiento.BOXmoverDerecha) ,  FBlanca8.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca9.movimiento.BOXmoverDerecha) ,  FBlanca9.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca10.movimiento.BOXmoverDerecha) ,  FBlanca10.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca11.movimiento.BOXmoverDerecha) ,  FBlanca11.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca12.movimiento.BOXmoverDerecha) ,  FBlanca12.movimiento.ICOmoverDerecha);

//Cargando los Labels a la caja contenedora BOX
    gtk_container_add(GTK_CONTAINER(FNegra1.movimiento.BOXmoverDerecha) ,  FNegra1.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra2.movimiento.BOXmoverDerecha) ,  FNegra2.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra3.movimiento.BOXmoverDerecha) ,  FNegra3.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra4.movimiento.BOXmoverDerecha) ,  FNegra4.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra5.movimiento.BOXmoverDerecha) ,  FNegra5.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra6.movimiento.BOXmoverDerecha) ,  FNegra6.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra7.movimiento.BOXmoverDerecha) ,  FNegra7.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra8.movimiento.BOXmoverDerecha) ,  FNegra8.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra9.movimiento.BOXmoverDerecha) ,  FNegra9.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra10.movimiento.BOXmoverDerecha) ,  FNegra10.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra11.movimiento.BOXmoverDerecha) ,  FNegra11.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra12.movimiento.BOXmoverDerecha) ,  FNegra12.movimiento.LBLmoverDerecha);

    gtk_container_add(GTK_CONTAINER(FBlanca1.movimiento.BOXmoverDerecha) ,  FBlanca1.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca2.movimiento.BOXmoverDerecha) ,  FBlanca2.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca3.movimiento.BOXmoverDerecha) ,  FBlanca3.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca4.movimiento.BOXmoverDerecha) ,  FBlanca4.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca5.movimiento.BOXmoverDerecha) ,  FBlanca5.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca6.movimiento.BOXmoverDerecha) ,  FBlanca6.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca7.movimiento.BOXmoverDerecha) ,  FBlanca7.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca8.movimiento.BOXmoverDerecha) ,  FBlanca8.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca9.movimiento.BOXmoverDerecha) ,  FBlanca9.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca10.movimiento.BOXmoverDerecha) ,  FBlanca10.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca11.movimiento.BOXmoverDerecha) ,  FBlanca11.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca12.movimiento.BOXmoverDerecha) ,  FBlanca12.movimiento.LBLmoverDerecha);

//Agregando la caja contenedora BOX a cada menu
    gtk_container_add(GTK_CONTAINER(FNegra1.movimiento.OPmoverDerecha) ,  FNegra1.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra2.movimiento.OPmoverDerecha) ,  FNegra2.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra3.movimiento.OPmoverDerecha) ,  FNegra3.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra4.movimiento.OPmoverDerecha) ,  FNegra4.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra5.movimiento.OPmoverDerecha) ,  FNegra5.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra6.movimiento.OPmoverDerecha) ,  FNegra6.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra7.movimiento.OPmoverDerecha) ,  FNegra7.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra8.movimiento.OPmoverDerecha) ,  FNegra8.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra9.movimiento.OPmoverDerecha) ,  FNegra9.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra10.movimiento.OPmoverDerecha) ,  FNegra10.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra11.movimiento.OPmoverDerecha) ,  FNegra11.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra12.movimiento.OPmoverDerecha) ,  FNegra12.movimiento.BOXmoverDerecha);

    gtk_container_add(GTK_CONTAINER(FBlanca1.movimiento.OPmoverDerecha) ,  FBlanca1.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca2.movimiento.OPmoverDerecha) ,  FBlanca2.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca3.movimiento.OPmoverDerecha) ,  FBlanca3.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca4.movimiento.OPmoverDerecha) ,  FBlanca4.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca5.movimiento.OPmoverDerecha) ,  FBlanca5.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca6.movimiento.OPmoverDerecha) ,  FBlanca6.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca7.movimiento.OPmoverDerecha) ,  FBlanca7.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca8.movimiento.OPmoverDerecha) ,  FBlanca8.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca9.movimiento.OPmoverDerecha) ,  FBlanca9.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca10.movimiento.OPmoverDerecha) ,  FBlanca10.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca11.movimiento.OPmoverDerecha) ,  FBlanca11.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca12.movimiento.OPmoverDerecha) ,  FBlanca12.movimiento.BOXmoverDerecha);

//------------------------------IZQUIERDA------------------------------------------------------------

//Cargando iconos MOVER DERECHA para todas las piezas
    FNegra1.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    FNegra2.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    FNegra3.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    FNegra4.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    FNegra5.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    FNegra6.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    FNegra7.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    FNegra8.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    FNegra9.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    FNegra10.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    FNegra11.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    FNegra12.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");

    FBlanca1.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    FBlanca2.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    FBlanca3.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    FBlanca4.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    FBlanca5.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    FBlanca6.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    FBlanca7.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    FBlanca8.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    FBlanca9.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    FBlanca10.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    FBlanca11.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    FBlanca12.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");

//Cargando LABEL MOVER ARRIBA ABAJO para todas las piezas
    FNegra1.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    FNegra2.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    FNegra3.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    FNegra4.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    FNegra5.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    FNegra6.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    FNegra7.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    FNegra8.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    FNegra9.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    FNegra10.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    FNegra11.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    FNegra12.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");

    FBlanca1.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    FBlanca2.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    FBlanca3.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    FBlanca4.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    FBlanca5.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    FBlanca6.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    FBlanca7.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    FBlanca8.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    FBlanca9.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    FBlanca10.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    FBlanca11.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    FBlanca12.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");

//Creando caja contenedora BOX para MOVER ABAJO de todas las piezas
    FNegra1.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra2.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra3.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra4.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra5.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra6.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra7.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra8.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra9.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra10.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra11.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra12.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

    FBlanca1.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca2.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca3.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca4.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca5.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca6.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca7.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca8.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca9.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca10.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca11.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca12.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

//Cargando los iconos a la caja contenedora BOX
    gtk_container_add(GTK_CONTAINER(FNegra1.movimiento.BOXmoverIzquierda) ,  FNegra1.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra2.movimiento.BOXmoverIzquierda) ,  FNegra2.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra3.movimiento.BOXmoverIzquierda) ,  FNegra3.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra4.movimiento.BOXmoverIzquierda) ,  FNegra4.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra5.movimiento.BOXmoverIzquierda) ,  FNegra5.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra6.movimiento.BOXmoverIzquierda) ,  FNegra6.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra7.movimiento.BOXmoverIzquierda) ,  FNegra7.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra8.movimiento.BOXmoverIzquierda) ,  FNegra8.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra9.movimiento.BOXmoverIzquierda) ,  FNegra9.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra10.movimiento.BOXmoverIzquierda) ,  FNegra10.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra11.movimiento.BOXmoverIzquierda) ,  FNegra11.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra12.movimiento.BOXmoverIzquierda) ,  FNegra12.movimiento.ICOmoverIzquierda);

    gtk_container_add(GTK_CONTAINER(FBlanca1.movimiento.BOXmoverIzquierda) ,  FBlanca1.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca2.movimiento.BOXmoverIzquierda) ,  FBlanca2.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca3.movimiento.BOXmoverIzquierda) ,  FBlanca3.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca4.movimiento.BOXmoverIzquierda) ,  FBlanca4.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca5.movimiento.BOXmoverIzquierda) ,  FBlanca5.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca6.movimiento.BOXmoverIzquierda) ,  FBlanca6.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca7.movimiento.BOXmoverIzquierda) ,  FBlanca7.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca8.movimiento.BOXmoverIzquierda) ,  FBlanca8.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca9.movimiento.BOXmoverIzquierda) ,  FBlanca9.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca10.movimiento.BOXmoverIzquierda) ,  FBlanca10.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca11.movimiento.BOXmoverIzquierda) ,  FBlanca11.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca12.movimiento.BOXmoverIzquierda) ,  FBlanca12.movimiento.ICOmoverIzquierda);

//Cargando los Labels a la caja contenedora BOX
    gtk_container_add(GTK_CONTAINER(FNegra1.movimiento.BOXmoverIzquierda) ,  FNegra1.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra2.movimiento.BOXmoverIzquierda) ,  FNegra2.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra3.movimiento.BOXmoverIzquierda) ,  FNegra3.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra4.movimiento.BOXmoverIzquierda) ,  FNegra4.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra5.movimiento.BOXmoverIzquierda) ,  FNegra5.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra6.movimiento.BOXmoverIzquierda) ,  FNegra6.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra7.movimiento.BOXmoverIzquierda) ,  FNegra7.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra8.movimiento.BOXmoverIzquierda) ,  FNegra8.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra9.movimiento.BOXmoverIzquierda) ,  FNegra9.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra10.movimiento.BOXmoverIzquierda) ,  FNegra10.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra11.movimiento.BOXmoverIzquierda) ,  FNegra11.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra12.movimiento.BOXmoverIzquierda) ,  FNegra12.movimiento.LBLmoverIzquierda);

    gtk_container_add(GTK_CONTAINER(FBlanca1.movimiento.BOXmoverIzquierda) ,  FBlanca1.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca2.movimiento.BOXmoverIzquierda) ,  FBlanca2.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca3.movimiento.BOXmoverIzquierda) ,  FBlanca3.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca4.movimiento.BOXmoverIzquierda) ,  FBlanca4.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca5.movimiento.BOXmoverIzquierda) ,  FBlanca5.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca6.movimiento.BOXmoverIzquierda) ,  FBlanca6.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca7.movimiento.BOXmoverIzquierda) ,  FBlanca7.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca8.movimiento.BOXmoverIzquierda) ,  FBlanca8.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca9.movimiento.BOXmoverIzquierda) ,  FBlanca9.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca10.movimiento.BOXmoverIzquierda) ,  FBlanca10.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca11.movimiento.BOXmoverIzquierda) ,  FBlanca11.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca12.movimiento.BOXmoverIzquierda) ,  FBlanca12.movimiento.LBLmoverIzquierda);

//Agregando la caja contenedora BOX a cada menu
    gtk_container_add(GTK_CONTAINER(FNegra1.movimiento.OPmoverIzquierda) ,  FNegra1.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra2.movimiento.OPmoverIzquierda) ,  FNegra2.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra3.movimiento.OPmoverIzquierda) ,  FNegra3.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra4.movimiento.OPmoverIzquierda) ,  FNegra4.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra5.movimiento.OPmoverIzquierda) ,  FNegra5.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra6.movimiento.OPmoverIzquierda) ,  FNegra6.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra7.movimiento.OPmoverIzquierda) ,  FNegra7.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra8.movimiento.OPmoverIzquierda) ,  FNegra8.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra9.movimiento.OPmoverIzquierda) ,  FNegra9.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra10.movimiento.OPmoverIzquierda) ,  FNegra10.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra11.movimiento.OPmoverIzquierda) ,  FNegra11.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FNegra12.movimiento.OPmoverIzquierda) ,  FNegra12.movimiento.BOXmoverIzquierda);

    gtk_container_add(GTK_CONTAINER(FBlanca1.movimiento.OPmoverIzquierda) ,  FBlanca1.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca2.movimiento.OPmoverIzquierda) ,  FBlanca2.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca3.movimiento.OPmoverIzquierda) ,  FBlanca3.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca4.movimiento.OPmoverIzquierda) ,  FBlanca4.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca5.movimiento.OPmoverIzquierda) ,  FBlanca5.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca6.movimiento.OPmoverIzquierda) ,  FBlanca6.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca7.movimiento.OPmoverIzquierda) ,  FBlanca7.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca8.movimiento.OPmoverIzquierda) ,  FBlanca8.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca9.movimiento.OPmoverIzquierda) ,  FBlanca9.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca10.movimiento.OPmoverIzquierda) ,  FBlanca10.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca11.movimiento.OPmoverIzquierda) ,  FBlanca11.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(FBlanca12.movimiento.OPmoverIzquierda) ,  FBlanca12.movimiento.BOXmoverIzquierda);

//------------------------------Diagonal Derecha------------------------------------------------------------

//Cargando iconos MOVER DERECHA para todas las piezas
    FNegra1.movimiento.ICOmoverDiagonalDerecha = gtk_image_new_from_file("moverDiagonalDerecha.png");
    FNegra2.movimiento.ICOmoverDiagonalDerecha = gtk_image_new_from_file("moverDiagonalDerecha.png");
    FNegra3.movimiento.ICOmoverDiagonalDerecha = gtk_image_new_from_file("moverDiagonalDerecha.png");
    FNegra4.movimiento.ICOmoverDiagonalDerecha = gtk_image_new_from_file("moverDiagonalDerecha.png");
    FNegra5.movimiento.ICOmoverDiagonalDerecha = gtk_image_new_from_file("moverDiagonalDerecha.png");
    FNegra6.movimiento.ICOmoverDiagonalDerecha = gtk_image_new_from_file("moverDiagonalDerecha.png");
    FNegra7.movimiento.ICOmoverDiagonalDerecha = gtk_image_new_from_file("moverDiagonalDerecha.png");
    FNegra8.movimiento.ICOmoverDiagonalDerecha = gtk_image_new_from_file("moverDiagonalDerecha.png");
    FNegra9.movimiento.ICOmoverDiagonalDerecha = gtk_image_new_from_file("moverDiagonalDerecha.png");
    FNegra10.movimiento.ICOmoverDiagonalDerecha = gtk_image_new_from_file("moverDiagonalDerecha.png");
    FNegra11.movimiento.ICOmoverDiagonalDerecha = gtk_image_new_from_file("moverDiagonalDerecha.png");
    FNegra12.movimiento.ICOmoverDiagonalDerecha = gtk_image_new_from_file("moverDiagonalDerecha.png");

    FBlanca1.movimiento.ICOmoverDiagonalDerecha = gtk_image_new_from_file("moverDiagonalDerecha.png");
    FBlanca2.movimiento.ICOmoverDiagonalDerecha = gtk_image_new_from_file("moverDiagonalDerecha.png");
    FBlanca3.movimiento.ICOmoverDiagonalDerecha = gtk_image_new_from_file("moverDiagonalDerecha.png");
    FBlanca4.movimiento.ICOmoverDiagonalDerecha = gtk_image_new_from_file("moverDiagonalDerecha.png");
    FBlanca5.movimiento.ICOmoverDiagonalDerecha = gtk_image_new_from_file("moverDiagonalDerecha.png");
    FBlanca6.movimiento.ICOmoverDiagonalDerecha = gtk_image_new_from_file("moverDiagonalDerecha.png");
    FBlanca7.movimiento.ICOmoverDiagonalDerecha = gtk_image_new_from_file("moverDiagonalDerecha.png");
    FBlanca8.movimiento.ICOmoverDiagonalDerecha = gtk_image_new_from_file("moverDiagonalDerecha.png");
    FBlanca9.movimiento.ICOmoverDiagonalDerecha = gtk_image_new_from_file("moverDiagonalDerecha.png");
    FBlanca10.movimiento.ICOmoverDiagonalDerecha = gtk_image_new_from_file("moverDiagonalDerecha.png");
    FBlanca11.movimiento.ICOmoverDiagonalDerecha = gtk_image_new_from_file("moverDiagonalDerecha.png");
    FBlanca12.movimiento.ICOmoverDiagonalDerecha = gtk_image_new_from_file("moverDiagonalDerecha.png");

//Cargando LABEL MOVER ARRIBA ABAJO para todas las piezas
    FNegra1.movimiento.LBLmoverDiagonalDerecha = gtk_label_new(" Mover Diagonal Derecha ");
    FNegra2.movimiento.LBLmoverDiagonalDerecha = gtk_label_new(" Mover Diagonal Derecha ");
    FNegra3.movimiento.LBLmoverDiagonalDerecha = gtk_label_new(" Mover Diagonal Derecha ");
    FNegra4.movimiento.LBLmoverDiagonalDerecha = gtk_label_new(" Mover Diagonal Derecha ");
    FNegra5.movimiento.LBLmoverDiagonalDerecha = gtk_label_new(" Mover Diagonal Derecha ");
    FNegra6.movimiento.LBLmoverDiagonalDerecha = gtk_label_new(" Mover Diagonal Derecha ");
    FNegra7.movimiento.LBLmoverDiagonalDerecha = gtk_label_new(" Mover Diagonal Derecha ");
    FNegra8.movimiento.LBLmoverDiagonalDerecha = gtk_label_new(" Mover Diagonal Derecha ");
    FNegra9.movimiento.LBLmoverDiagonalDerecha = gtk_label_new(" Mover Diagonal Derecha ");
    FNegra10.movimiento.LBLmoverDiagonalDerecha = gtk_label_new(" Mover Diagonal Derecha ");
    FNegra11.movimiento.LBLmoverDiagonalDerecha = gtk_label_new(" Mover Diagonal Derecha ");
    FNegra12.movimiento.LBLmoverDiagonalDerecha = gtk_label_new(" Mover Diagonal Derecha ");

    FBlanca1.movimiento.LBLmoverDiagonalDerecha = gtk_label_new(" Mover Diagonal Derecha ");
    FBlanca2.movimiento.LBLmoverDiagonalDerecha = gtk_label_new(" Mover Diagonal Derecha ");
    FBlanca3.movimiento.LBLmoverDiagonalDerecha = gtk_label_new(" Mover Diagonal Derecha ");
    FBlanca4.movimiento.LBLmoverDiagonalDerecha = gtk_label_new(" Mover Diagonal Derecha ");
    FBlanca5.movimiento.LBLmoverDiagonalDerecha = gtk_label_new(" Mover Diagonal Derecha ");
    FBlanca6.movimiento.LBLmoverDiagonalDerecha = gtk_label_new(" Mover Diagonal Derecha ");
    FBlanca7.movimiento.LBLmoverDiagonalDerecha = gtk_label_new(" Mover Diagonal Derecha ");
    FBlanca8.movimiento.LBLmoverDiagonalDerecha = gtk_label_new(" Mover Diagonal Derecha ");
    FBlanca9.movimiento.LBLmoverDiagonalDerecha = gtk_label_new(" Mover Diagonal Derecha ");
    FBlanca10.movimiento.LBLmoverDiagonalDerecha = gtk_label_new(" Mover Diagonal Derecha ");
    FBlanca11.movimiento.LBLmoverDiagonalDerecha = gtk_label_new(" Mover Diagonal Derecha ");
    FBlanca12.movimiento.LBLmoverDiagonalDerecha = gtk_label_new(" Mover Diagonal Derecha ");

//Creando caja contenedora BOX para MOVER ABAJO de todas las piezas
    FNegra1.movimiento.BOXmoverDiagonalDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra2.movimiento.BOXmoverDiagonalDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra3.movimiento.BOXmoverDiagonalDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra4.movimiento.BOXmoverDiagonalDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra5.movimiento.BOXmoverDiagonalDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra6.movimiento.BOXmoverDiagonalDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra7.movimiento.BOXmoverDiagonalDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra8.movimiento.BOXmoverDiagonalDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra9.movimiento.BOXmoverDiagonalDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra10.movimiento.BOXmoverDiagonalDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra11.movimiento.BOXmoverDiagonalDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FNegra12.movimiento.BOXmoverDiagonalDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

    FBlanca1.movimiento.BOXmoverDiagonalDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca2.movimiento.BOXmoverDiagonalDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca3.movimiento.BOXmoverDiagonalDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca4.movimiento.BOXmoverDiagonalDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca5.movimiento.BOXmoverDiagonalDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca6.movimiento.BOXmoverDiagonalDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca7.movimiento.BOXmoverDiagonalDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca8.movimiento.BOXmoverDiagonalDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca9.movimiento.BOXmoverDiagonalDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca10.movimiento.BOXmoverDiagonalDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca11.movimiento.BOXmoverDiagonalDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    FBlanca12.movimiento.BOXmoverDiagonalDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

//Cargando los iconos a la caja contenedora BOX
    gtk_container_add(GTK_CONTAINER(FNegra1.movimiento.BOXmoverDiagonalDerecha) ,  FNegra1.movimiento.ICOmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra2.movimiento.BOXmoverDiagonalDerecha) ,  FNegra2.movimiento.ICOmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra3.movimiento.BOXmoverDiagonalDerecha) ,  FNegra3.movimiento.ICOmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra4.movimiento.BOXmoverDiagonalDerecha) ,  FNegra4.movimiento.ICOmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra5.movimiento.BOXmoverDiagonalDerecha) ,  FNegra5.movimiento.ICOmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra6.movimiento.BOXmoverDiagonalDerecha) ,  FNegra6.movimiento.ICOmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra7.movimiento.BOXmoverDiagonalDerecha) ,  FNegra7.movimiento.ICOmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra8.movimiento.BOXmoverDiagonalDerecha) ,  FNegra8.movimiento.ICOmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra9.movimiento.BOXmoverDiagonalDerecha) ,  FNegra9.movimiento.ICOmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra10.movimiento.BOXmoverDiagonalDerecha) ,  FNegra10.movimiento.ICOmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra11.movimiento.BOXmoverDiagonalDerecha) ,  FNegra11.movimiento.ICOmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra12.movimiento.BOXmoverDiagonalDerecha) ,  FNegra12.movimiento.ICOmoverDiagonalDerecha);

    gtk_container_add(GTK_CONTAINER(FBlanca1.movimiento.BOXmoverDiagonalDerecha) ,  FBlanca1.movimiento.ICOmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca2.movimiento.BOXmoverDiagonalDerecha) ,  FBlanca2.movimiento.ICOmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca3.movimiento.BOXmoverDiagonalDerecha) ,  FBlanca3.movimiento.ICOmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca4.movimiento.BOXmoverDiagonalDerecha) ,  FBlanca4.movimiento.ICOmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca5.movimiento.BOXmoverDiagonalDerecha) ,  FBlanca5.movimiento.ICOmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca6.movimiento.BOXmoverDiagonalDerecha) ,  FBlanca6.movimiento.ICOmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca7.movimiento.BOXmoverDiagonalDerecha) ,  FBlanca7.movimiento.ICOmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca8.movimiento.BOXmoverDiagonalDerecha) ,  FBlanca8.movimiento.ICOmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca9.movimiento.BOXmoverDiagonalDerecha) ,  FBlanca9.movimiento.ICOmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca10.movimiento.BOXmoverDiagonalDerecha) ,  FBlanca10.movimiento.ICOmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca11.movimiento.BOXmoverDiagonalDerecha) ,  FBlanca11.movimiento.ICOmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca12.movimiento.BOXmoverDiagonalDerecha) ,  FBlanca12.movimiento.ICOmoverDiagonalDerecha);

//Cargando los Labels a la caja contenedora BOX
    gtk_container_add(GTK_CONTAINER(FNegra1.movimiento.BOXmoverDiagonalDerecha) ,  FNegra1.movimiento.LBLmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra2.movimiento.BOXmoverDiagonalDerecha) ,  FNegra2.movimiento.LBLmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra3.movimiento.BOXmoverDiagonalDerecha) ,  FNegra3.movimiento.LBLmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra4.movimiento.BOXmoverDiagonalDerecha) ,  FNegra4.movimiento.LBLmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra5.movimiento.BOXmoverDiagonalDerecha) ,  FNegra5.movimiento.LBLmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra6.movimiento.BOXmoverDiagonalDerecha) ,  FNegra6.movimiento.LBLmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra7.movimiento.BOXmoverDiagonalDerecha) ,  FNegra7.movimiento.LBLmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra8.movimiento.BOXmoverDiagonalDerecha) ,  FNegra8.movimiento.LBLmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra9.movimiento.BOXmoverDiagonalDerecha) ,  FNegra9.movimiento.LBLmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra10.movimiento.BOXmoverDiagonalDerecha) ,  FNegra10.movimiento.LBLmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra11.movimiento.BOXmoverDiagonalDerecha) ,  FNegra11.movimiento.LBLmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra12.movimiento.BOXmoverDiagonalDerecha) ,  FNegra12.movimiento.LBLmoverDiagonalDerecha);

    gtk_container_add(GTK_CONTAINER(FBlanca1.movimiento.BOXmoverDiagonalDerecha) ,  FBlanca1.movimiento.LBLmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca2.movimiento.BOXmoverDiagonalDerecha) ,  FBlanca2.movimiento.LBLmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca3.movimiento.BOXmoverDiagonalDerecha) ,  FBlanca3.movimiento.LBLmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca4.movimiento.BOXmoverDiagonalDerecha) ,  FBlanca4.movimiento.LBLmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca5.movimiento.BOXmoverDiagonalDerecha) ,  FBlanca5.movimiento.LBLmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca6.movimiento.BOXmoverDiagonalDerecha) ,  FBlanca6.movimiento.LBLmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca7.movimiento.BOXmoverDiagonalDerecha) ,  FBlanca7.movimiento.LBLmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca8.movimiento.BOXmoverDiagonalDerecha) ,  FBlanca8.movimiento.LBLmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca9.movimiento.BOXmoverDiagonalDerecha) ,  FBlanca9.movimiento.LBLmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca10.movimiento.BOXmoverDiagonalDerecha) ,  FBlanca10.movimiento.LBLmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca11.movimiento.BOXmoverDiagonalDerecha) ,  FBlanca11.movimiento.LBLmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca12.movimiento.BOXmoverDiagonalDerecha) ,  FBlanca12.movimiento.LBLmoverDiagonalDerecha);

//Agregando la caja contenedora BOX a cada menu
    gtk_container_add(GTK_CONTAINER(FNegra1.movimiento.OPmoverDiagonalDerecha) ,  FNegra1.movimiento.BOXmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra2.movimiento.OPmoverDiagonalDerecha) ,  FNegra2.movimiento.BOXmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra3.movimiento.OPmoverDiagonalDerecha) ,  FNegra3.movimiento.BOXmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra4.movimiento.OPmoverDiagonalDerecha) ,  FNegra4.movimiento.BOXmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra5.movimiento.OPmoverDiagonalDerecha) ,  FNegra5.movimiento.BOXmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra6.movimiento.OPmoverDiagonalDerecha) ,  FNegra6.movimiento.BOXmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra7.movimiento.OPmoverDiagonalDerecha) ,  FNegra7.movimiento.BOXmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra8.movimiento.OPmoverDiagonalDerecha) ,  FNegra8.movimiento.BOXmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra9.movimiento.OPmoverDiagonalDerecha) ,  FNegra9.movimiento.BOXmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra10.movimiento.OPmoverDiagonalDerecha) ,  FNegra10.movimiento.BOXmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra11.movimiento.OPmoverDiagonalDerecha) ,  FNegra11.movimiento.BOXmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FNegra12.movimiento.OPmoverDiagonalDerecha) ,  FNegra12.movimiento.BOXmoverDiagonalDerecha);

    gtk_container_add(GTK_CONTAINER(FBlanca1.movimiento.OPmoverDiagonalDerecha) ,  FBlanca1.movimiento.BOXmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca2.movimiento.OPmoverDiagonalDerecha) ,  FBlanca2.movimiento.BOXmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca3.movimiento.OPmoverDiagonalDerecha) ,  FBlanca3.movimiento.BOXmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca4.movimiento.OPmoverDiagonalDerecha) ,  FBlanca4.movimiento.BOXmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca5.movimiento.OPmoverDiagonalDerecha) ,  FBlanca5.movimiento.BOXmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca6.movimiento.OPmoverDiagonalDerecha) ,  FBlanca6.movimiento.BOXmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca7.movimiento.OPmoverDiagonalDerecha) ,  FBlanca7.movimiento.BOXmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca8.movimiento.OPmoverDiagonalDerecha) ,  FBlanca8.movimiento.BOXmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca9.movimiento.OPmoverDiagonalDerecha) ,  FBlanca9.movimiento.BOXmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca10.movimiento.OPmoverDiagonalDerecha) ,  FBlanca10.movimiento.BOXmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca11.movimiento.OPmoverDiagonalDerecha) ,  FBlanca11.movimiento.BOXmoverDiagonalDerecha);
    gtk_container_add(GTK_CONTAINER(FBlanca12.movimiento.OPmoverDiagonalDerecha) ,  FBlanca12.movimiento.BOXmoverDiagonalDerecha);

}

void FNconectarMenusPiezas(){ //Conecta los Menús creados a las piezas
    //Jugador 1
    g_signal_connect_swapped(G_OBJECT(FNegra1.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), FNegra1.Menu);
    g_signal_connect_swapped(G_OBJECT(FNegra2.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), FNegra2.Menu);
    g_signal_connect_swapped(G_OBJECT(FNegra3.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), FNegra3.Menu);
    g_signal_connect_swapped(G_OBJECT(FNegra4.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), FNegra4.Menu);
    g_signal_connect_swapped(G_OBJECT(FNegra5.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), FNegra5.Menu);
    g_signal_connect_swapped(G_OBJECT(FNegra6.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), FNegra6.Menu);
    g_signal_connect_swapped(G_OBJECT(FNegra7.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), FNegra7.Menu);
    g_signal_connect_swapped(G_OBJECT(FNegra8.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), FNegra8.Menu);
    g_signal_connect_swapped(G_OBJECT(FNegra9.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), FNegra9.Menu);
    g_signal_connect_swapped(G_OBJECT(FNegra10.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), FNegra10.Menu);
    g_signal_connect_swapped(G_OBJECT(FNegra11.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), FNegra11.Menu);
    g_signal_connect_swapped(G_OBJECT(FNegra12.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), FNegra12.Menu);

    //Jugador 2
    g_signal_connect_swapped(G_OBJECT(FBlanca1.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), FBlanca1.Menu);
    g_signal_connect_swapped(G_OBJECT(FBlanca2.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), FBlanca2.Menu);
    g_signal_connect_swapped(G_OBJECT(FBlanca3.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), FBlanca3.Menu);
    g_signal_connect_swapped(G_OBJECT(FBlanca4.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), FBlanca4.Menu);
    g_signal_connect_swapped(G_OBJECT(FBlanca5.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), FBlanca5.Menu);
    g_signal_connect_swapped(G_OBJECT(FBlanca6.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), FBlanca6.Menu);
    g_signal_connect_swapped(G_OBJECT(FBlanca7.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), FBlanca7.Menu);
    g_signal_connect_swapped(G_OBJECT(FBlanca8.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), FBlanca8.Menu);
    g_signal_connect_swapped(G_OBJECT(FBlanca9.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), FBlanca9.Menu);
    g_signal_connect_swapped(G_OBJECT(FBlanca10.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), FBlanca10.Menu);
    g_signal_connect_swapped(G_OBJECT(FBlanca11.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), FBlanca11.Menu);
    g_signal_connect_swapped(G_OBJECT(FBlanca12.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), FBlanca12.Menu);


}

void FNmostrarOPmenusPiezas(){ //(DEPRECADO) Muestra las opciones de los menús
    //Observacion: las llamadas a ciertas funciones de los conejos ("Mover arriba" y "Mover abajo") estan comentadas (pero no eliminadas para posibles pruebas) ya que el conejo no puede retroceder.

    //Jugador 1
    gtk_widget_show_all(FNegra1.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra2.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra3.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra4.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra5.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra6.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra7.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra8.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra9.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra10.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra11.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra12.movimiento.OPmoverArriba);

    gtk_widget_show_all(FNegra1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra3.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra4.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra5.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra6.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra7.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra8.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra9.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra10.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra11.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra12.movimiento.OPmoverAbajo);

    gtk_widget_show_all(FNegra1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra3.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra4.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra5.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra6.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra7.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra8.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra9.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra10.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra11.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra12.movimiento.OPmoverDerecha);

    gtk_widget_show_all(FNegra1.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FNegra2.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FNegra3.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FNegra4.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FNegra5.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FNegra6.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FNegra7.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FNegra8.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FNegra9.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FNegra10.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FNegra11.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FNegra12.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(FNegra1.movimiento.OPmoverDiagonalDerecha);
    gtk_widget_show_all(FNegra2.movimiento.OPmoverDiagonalDerecha);
    gtk_widget_show_all(FNegra3.movimiento.OPmoverDiagonalDerecha);
    gtk_widget_show_all(FNegra4.movimiento.OPmoverDiagonalDerecha);
    gtk_widget_show_all(FNegra5.movimiento.OPmoverDiagonalDerecha);
    gtk_widget_show_all(FNegra6.movimiento.OPmoverDiagonalDerecha);
    gtk_widget_show_all(FNegra7.movimiento.OPmoverDiagonalDerecha);
    gtk_widget_show_all(FNegra8.movimiento.OPmoverDiagonalDerecha);
    gtk_widget_show_all(FNegra9.movimiento.OPmoverDiagonalDerecha);
    gtk_widget_show_all(FNegra10.movimiento.OPmoverDiagonalDerecha);
    gtk_widget_show_all(FNegra11.movimiento.OPmoverDiagonalDerecha);
    gtk_widget_show_all(FNegra12.movimiento.OPmoverDiagonalDerecha);

    //Jugador 2
    gtk_widget_show_all(FBlanca1.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca2.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca3.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca4.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca5.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca6.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca7.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca8.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca9.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca10.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca11.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca12.movimiento.OPmoverArriba);

    gtk_widget_show_all(FBlanca1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca3.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca4.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca5.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca6.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca7.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca8.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca9.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca10.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca11.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca12.movimiento.OPmoverAbajo);

    gtk_widget_show_all(FBlanca1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca3.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca4.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca5.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca6.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca7.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca8.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca9.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca10.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca11.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca12.movimiento.OPmoverDerecha);

    gtk_widget_show_all(FBlanca1.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FBlanca2.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FBlanca3.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FBlanca4.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FBlanca5.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FBlanca6.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FBlanca7.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FBlanca8.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FBlanca9.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FBlanca10.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FBlanca11.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FBlanca12.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(FBlanca1.movimiento.OPmoverDiagonalDerecha);
    gtk_widget_show_all(FBlanca2.movimiento.OPmoverDiagonalDerecha);
    gtk_widget_show_all(FBlanca3.movimiento.OPmoverDiagonalDerecha);
    gtk_widget_show_all(FBlanca4.movimiento.OPmoverDiagonalDerecha);
    gtk_widget_show_all(FBlanca5.movimiento.OPmoverDiagonalDerecha);
    gtk_widget_show_all(FBlanca6.movimiento.OPmoverDiagonalDerecha);
    gtk_widget_show_all(FBlanca7.movimiento.OPmoverDiagonalDerecha);
    gtk_widget_show_all(FBlanca8.movimiento.OPmoverDiagonalDerecha);
    gtk_widget_show_all(FBlanca9.movimiento.OPmoverDiagonalDerecha);
    gtk_widget_show_all(FBlanca10.movimiento.OPmoverDiagonalDerecha);
    gtk_widget_show_all(FBlanca11.movimiento.OPmoverDiagonalDerecha);
    gtk_widget_show_all(FBlanca12.movimiento.OPmoverDiagonalDerecha);

}

void FNconectarOPMovimientosPiezas(){ //Conecta los submenús para el movimiento a los menús de cada pieza
        ///ARRIBA
        ///Mover
        //Jugador 1
        g_signal_connect_swapped(G_OBJECT(FNegra1.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), FNegra1.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra2.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), FNegra2.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra3.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), FNegra3.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra4.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), FNegra4.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra5.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), FNegra5.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra6.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), FNegra6.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra7.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), FNegra7.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra8.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), FNegra8.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra9.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), FNegra8.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra10.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), FNegra10.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra11.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), FNegra11.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra12.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), FNegra12.Pieza);

        //Jugador 2
        g_signal_connect_swapped(G_OBJECT(FBlanca1.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), FBlanca1.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca2.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), FBlanca2.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca3.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), FBlanca3.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca4.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), FBlanca4.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca5.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), FBlanca5.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca6.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), FBlanca6.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca7.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), FBlanca7.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca8.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), FBlanca8.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca9.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), FBlanca8.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca10.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), FBlanca10.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca11.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), FBlanca11.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca12.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), FBlanca12.Pieza);

        ///ABAJO
        ///Mover
        //Jugador 1
        g_signal_connect_swapped(G_OBJECT(FNegra1.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), FNegra1.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra2.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), FNegra2.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra3.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), FNegra3.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra4.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), FNegra4.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra5.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), FNegra5.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra6.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), FNegra6.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra7.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), FNegra7.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra8.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), FNegra8.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra9.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), FNegra8.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra10.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), FNegra10.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra11.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), FNegra11.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra12.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), FNegra12.Pieza);

        //Jugador 2
        g_signal_connect_swapped(G_OBJECT(FBlanca1.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), FBlanca1.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca2.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), FBlanca2.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca3.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), FBlanca3.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca4.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), FBlanca4.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca5.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), FBlanca5.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca6.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), FBlanca6.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca7.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), FBlanca7.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca8.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), FBlanca8.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca9.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), FBlanca8.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca10.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), FBlanca10.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca11.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), FBlanca11.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca12.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), FBlanca12.Pieza);

        ///DERECHA
        ///Mover
        //Jugador 1
        g_signal_connect_swapped(G_OBJECT(FNegra1.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), FNegra1.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra2.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), FNegra2.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra3.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), FNegra3.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra4.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), FNegra4.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra5.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), FNegra5.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra6.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), FNegra6.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra7.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), FNegra7.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra8.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), FNegra8.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra9.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), FNegra8.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra10.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), FNegra10.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra11.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), FNegra11.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra12.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), FNegra12.Pieza);

        //Jugador 2
        g_signal_connect_swapped(G_OBJECT(FBlanca1.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), FBlanca1.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca2.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), FBlanca2.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca3.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), FBlanca3.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca4.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), FBlanca4.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca5.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), FBlanca5.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca6.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), FBlanca6.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca7.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), FBlanca7.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca8.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), FBlanca8.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca9.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), FBlanca8.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca10.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), FBlanca10.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca11.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), FBlanca11.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca12.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), FBlanca12.Pieza);

        ///IZQUIERDA
        ///Mover
        //Jugador 1
        g_signal_connect_swapped(G_OBJECT(FNegra1.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), FNegra1.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra2.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), FNegra2.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra3.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), FNegra3.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra4.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), FNegra4.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra5.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), FNegra5.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra6.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), FNegra6.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra7.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), FNegra7.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra8.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), FNegra8.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra9.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), FNegra8.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra10.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), FNegra10.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra11.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), FNegra11.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra12.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), FNegra12.Pieza);

        //Jugador 2
        g_signal_connect_swapped(G_OBJECT(FBlanca1.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), FBlanca1.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca2.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), FBlanca2.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca3.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), FBlanca3.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca4.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), FBlanca4.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca5.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), FBlanca5.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca6.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), FBlanca6.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca7.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), FBlanca7.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca8.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), FBlanca8.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca9.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), FBlanca8.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca10.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), FBlanca10.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca11.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), FBlanca11.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca12.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), FBlanca12.Pieza);

        ///DIAGONAL DERECHA
        ///Mover
        //Jugador 1
        g_signal_connect_swapped(G_OBJECT(FNegra1.movimiento.OPmoverDiagonalDerecha), "button-press-event", G_CALLBACK(FNmoverDiagonalDerecha), FNegra1.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra2.movimiento.OPmoverDiagonalDerecha), "button-press-event", G_CALLBACK(FNmoverDiagonalDerecha), FNegra2.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra3.movimiento.OPmoverDiagonalDerecha), "button-press-event", G_CALLBACK(FNmoverDiagonalDerecha), FNegra3.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra4.movimiento.OPmoverDiagonalDerecha), "button-press-event", G_CALLBACK(FNmoverDiagonalDerecha), FNegra4.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra5.movimiento.OPmoverDiagonalDerecha), "button-press-event", G_CALLBACK(FNmoverDiagonalDerecha), FNegra5.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra6.movimiento.OPmoverDiagonalDerecha), "button-press-event", G_CALLBACK(FNmoverDiagonalDerecha), FNegra6.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra7.movimiento.OPmoverDiagonalDerecha), "button-press-event", G_CALLBACK(FNmoverDiagonalDerecha), FNegra7.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra8.movimiento.OPmoverDiagonalDerecha), "button-press-event", G_CALLBACK(FNmoverDiagonalDerecha), FNegra8.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra9.movimiento.OPmoverDiagonalDerecha), "button-press-event", G_CALLBACK(FNmoverDiagonalDerecha), FNegra8.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra10.movimiento.OPmoverDiagonalDerecha), "button-press-event", G_CALLBACK(FNmoverDiagonalDerecha), FNegra10.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra11.movimiento.OPmoverDiagonalDerecha), "button-press-event", G_CALLBACK(FNmoverDiagonalDerecha), FNegra11.Pieza);
        g_signal_connect_swapped(G_OBJECT(FNegra12.movimiento.OPmoverDiagonalDerecha), "button-press-event", G_CALLBACK(FNmoverDiagonalDerecha), FNegra12.Pieza);

        //Jugador 2
        g_signal_connect_swapped(G_OBJECT(FBlanca1.movimiento.OPmoverDiagonalDerecha), "button-press-event", G_CALLBACK(FNmoverDiagonalDerecha), FBlanca1.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca2.movimiento.OPmoverDiagonalDerecha), "button-press-event", G_CALLBACK(FNmoverDiagonalDerecha), FBlanca2.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca3.movimiento.OPmoverDiagonalDerecha), "button-press-event", G_CALLBACK(FNmoverDiagonalDerecha), FBlanca3.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca4.movimiento.OPmoverDiagonalDerecha), "button-press-event", G_CALLBACK(FNmoverDiagonalDerecha), FBlanca4.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca5.movimiento.OPmoverDiagonalDerecha), "button-press-event", G_CALLBACK(FNmoverDiagonalDerecha), FBlanca5.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca6.movimiento.OPmoverDiagonalDerecha), "button-press-event", G_CALLBACK(FNmoverDiagonalDerecha), FBlanca6.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca7.movimiento.OPmoverDiagonalDerecha), "button-press-event", G_CALLBACK(FNmoverDiagonalDerecha), FBlanca7.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca8.movimiento.OPmoverDiagonalDerecha), "button-press-event", G_CALLBACK(FNmoverDiagonalDerecha), FBlanca8.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca9.movimiento.OPmoverDiagonalDerecha), "button-press-event", G_CALLBACK(FNmoverDiagonalDerecha), FBlanca8.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca10.movimiento.OPmoverDiagonalDerecha), "button-press-event", G_CALLBACK(FNmoverDiagonalDerecha), FBlanca10.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca11.movimiento.OPmoverDiagonalDerecha), "button-press-event", G_CALLBACK(FNmoverDiagonalDerecha), FBlanca11.Pieza);
        g_signal_connect_swapped(G_OBJECT(FBlanca12.movimiento.OPmoverDiagonalDerecha), "button-press-event", G_CALLBACK(FNmoverDiagonalDerecha), FBlanca12.Pieza);


}

///CONFIGURACION DE LA PANTALLA DE JUEGO, DIALOGOS DE ADVERTENCIAS, ARREGLOS PARA EL CONTROL EN TERMINAL E IMPRESION EN TERMINAL.
void FNconfigFormJuego(){ //Configura la pantalla de juego

    //Creación de la pantalla de juego
    formJuego.Pantalla = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(formJuego.Pantalla), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(formJuego.Pantalla), 1324,900);
    gtk_window_set_resizable(GTK_WINDOW(formJuego.Pantalla), FALSE);
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
    g_signal_connect_swapped(G_OBJECT(ayuda.Boton), "button-press-event", G_CALLBACK(FNmostrarPantallaAyuda),NULL);

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
    g_signal_connect(G_OBJECT(jugar.Boton), "clicked", G_CALLBACK(FNiniciarPiezasJ1), NULL);

    //Creacion del boton para reiniciar la partida
    reiniciar.Boton = gtk_button_new_with_label(NULL);
    reiniciar.Icono = gtk_image_new_from_file("reiniciar.png");
    gtk_button_set_always_show_image(GTK_BUTTON(reiniciar.Boton), TRUE);
    gtk_button_set_image(GTK_BUTTON(reiniciar.Boton), reiniciar.Icono);
    gtk_button_set_relief(GTK_BUTTON(reiniciar.Boton), GTK_RELIEF_NONE);
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), reiniciar.Boton, 1200,250);
    g_signal_connect_swapped(G_OBJECT(reiniciar.Boton), "button-press-event", G_CALLBACK(FNreiniciarJuego),NULL);

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

static void FNiniciarPiezasJ1(){ //Inicializa aleatoriamente las piezas del Jugador 1
    fila = 0; columna = 0;
    for(i = limiteInferior; i <= limiteSuperior; i++){
        piezaRandom = piezasJ1[i];
        do{
            piezaRandom = piezasJ1[i];
        }while(piezasJ1[i] == 0);

        FNcolocarPiezas();
        columna++;
        if(columna > 4){
            columna = 0;
            fila +=1;
        }
    }
    fflush(stdin);
    FNiniciarPiezasJ2();
    gtk_widget_show_all(formJuego.Pantalla);
}

static void FNiniciarPiezasJ2(){ //Inicializa aleatoriamente las piezas del Jugador 2
    fila = 2; columna = 3;
    for(i = limiteInferior; i <= limiteSuperior; i++){
        piezaRandom = piezasJ2[i];
            do{
                piezaRandom = piezasJ2[i];
            }while(piezasJ2[i] == 0);

        FNcolocarPiezas();
        columna++;
        if(columna > 4){
            columna = 0;
            fila += 1;
        }
    }
        fflush(stdin);
}

void FNcolocarPiezas(){ //Cuando se llama a FNiniciarPiezasJ1 y FNiniciarPiezasJ2, esta función recibe una pieza aleatoria y la coloca también en una posición aleatoria del tablero.
        switch(piezaRandom){
            case Negra1:
                gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FNegra1.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
                //pesoPiezas[fila][columna] = FNegra1.Peso;
                queJugador[fila][columna] = J1;
                break;
            case Negra2:
                gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FNegra2.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
                //pesoPiezas[fila][columna] = camelloJ1.Peso;
                queJugador[fila][columna] = J1;
                break;
            case Negra3:
                gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FNegra3.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
                //pesoPiezas[fila][columna] = caballo1J1.Peso;
                queJugador[fila][columna] = J1;
                break;
            case Negra4:
                gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FNegra4.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
                //pesoPiezas[fila][columna] = caballo2J1.Peso;
                queJugador[fila][columna] = J1;
                break;
            case Negra5:
                gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FNegra5.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
                //pesoPiezas[fila][columna] = caballo2J1.Peso;
                queJugador[fila][columna] = J1;
                break;
            case Negra6:
                gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FNegra6.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
                //pesoPiezas[fila][columna] = caballo2J1.Peso;
                queJugador[fila][columna] = J1;
                break;
            case Negra7:
                gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FNegra7.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
                //pesoPiezas[fila][columna] = caballo2J1.Peso;
                queJugador[fila][columna] = J1;
                break;
            case Negra8:
                gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FNegra8.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
                //pesoPiezas[fila][columna] = caballo2J1.Peso;
                queJugador[fila][columna] = J1;
                break;
            case Negra9:
                gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FNegra9.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
                //pesoPiezas[fila][columna] = caballo2J1.Peso;
                queJugador[fila][columna] = J1;
                break;
            case Negra10:
                gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FNegra10.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
                //pesoPiezas[fila][columna] = caballo2J1.Peso;
                queJugador[fila][columna] = J1;
                break;
            case Negra11:
                gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FNegra11.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
                //pesoPiezas[fila][columna] = caballo2J1.Peso;
                queJugador[fila][columna] = J1;
                break;
            case Negra12:
                gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FNegra12.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
                //pesoPiezas[fila][columna] = caballo2J1.Peso;
                queJugador[fila][columna] = J1;
                break;
            case Blanca1:
                gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FBlanca1.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            //    pesoPiezas[fila][columna] = caballo2J1.Peso;
                queJugador[fila][columna] = J2;
                break;
            case Blanca2:
                gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FBlanca2.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
              //  pesoPiezas[fila][columna] = caballo2J1.Peso;
                queJugador[fila][columna] = J2;
                break;
            case Blanca3:
                gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FBlanca3.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
                //pesoPiezas[fila][columna] = caballo2J1.Peso;
                queJugador[fila][columna] = J2;
                break;
            case Blanca4:
                gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FBlanca4.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
                //pesoPiezas[fila][columna] = caballo2J1.Peso;
                queJugador[fila][columna] = J2;
                break;
            case Blanca5:
                gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FBlanca5.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
                //pesoPiezas[fila][columna] = caballo2J1.Peso;
                queJugador[fila][columna] = J2;
                break;
            case Blanca6:
                gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FBlanca6.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
                //pesoPiezas[fila][columna] = caballo2J1.Peso;
                queJugador[fila][columna] = J2;
                break;
            case Blanca7:
                gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FBlanca7.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
                //pesoPiezas[fila][columna] = caballo2J1.Peso;
                queJugador[fila][columna] = J2;
                break;
            case Blanca8:
                gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FBlanca8.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
                //pesoPiezas[fila][columna] = caballo2J1.Peso;
                queJugador[fila][columna] = J2;
                break;
            case Blanca9:
                gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FBlanca9.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
                //pesoPiezas[fila][columna] = caballo2J1.Peso;
                queJugador[fila][columna] = J2;
                    break;
            case Blanca10:
                gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FBlanca10.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
                //pesoPiezas[fila][columna] = caballo2J1.Peso;
                queJugador[fila][columna] = J2;
                break;
            case Blanca11:
                gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FBlanca11.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
                //pesoPiezas[fila][columna] = caballo2J1.Peso;
                queJugador[fila][columna] = J2;
                break;
            case Blanca12:
                gtk_layout_put(GTK_LAYOUT(formJuego.Layout), FBlanca12.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
                //pesoPiezas[fila][columna] = caballo2J1.Peso;
                queJugador[fila][columna] = J2;
                break;
            default:
                break;
        }

    posicionPiezas[fila][columna] = piezaRandom;
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
void FNmostrarPantallaAyuda(){
GtkWidget *dialog;
    GdkPixbuf *logo;
    GError *error=NULL;

    dialog= gtk_about_dialog_new();
//  logo=gdk_pixbuf_new_from_file("tablero.jpg",&error);
    if(error==NULL){
        gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), logo);
    }
    gtk_window_set_icon_from_file(GTK_WINDOW(dialog), "tablero.jpg", NULL);
    gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), "Alquerque");
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), "V. 0.1");
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog),"(C) 2020 FONDDA_TEAM");


    gtk_dialog_run(GTK_DIALOG(dialog));

    gtk_widget_destroy(dialog);

}


void FNreiniciarJuego(){

    //Jugador 1
    gtk_widget_destroy(FNegra1.Pieza);
    gtk_widget_destroy(FNegra2.Pieza);
    gtk_widget_destroy(FNegra3.Pieza);
    gtk_widget_destroy(FNegra4.Pieza);
    gtk_widget_destroy(FNegra5.Pieza);
    gtk_widget_destroy(FNegra6.Pieza);
    gtk_widget_destroy(FNegra7.Pieza);
    gtk_widget_destroy(FNegra8.Pieza);
    gtk_widget_destroy(FNegra9.Pieza);
    gtk_widget_destroy(FNegra10.Pieza);
    gtk_widget_destroy(FNegra11.Pieza);
    gtk_widget_destroy(FNegra12.Pieza);

    //Jugador 2
    gtk_widget_destroy(FBlanca1.Pieza);
    gtk_widget_destroy(FBlanca2.Pieza);
    gtk_widget_destroy(FBlanca3.Pieza);
    gtk_widget_destroy(FBlanca4.Pieza);
    gtk_widget_destroy(FBlanca5.Pieza);
    gtk_widget_destroy(FBlanca6.Pieza);
    gtk_widget_destroy(FBlanca7.Pieza);
    gtk_widget_destroy(FBlanca8.Pieza);
    gtk_widget_destroy(FBlanca9.Pieza);
    gtk_widget_destroy(FBlanca10.Pieza);
    gtk_widget_destroy(FBlanca11.Pieza);
    gtk_widget_destroy(FBlanca12.Pieza);

    for(int i = 0; i < 5; i ++){
        for(int j = 0; j < 5; j++){
            if(posicionPiezas[i][j] != 0){
                //if(pesoPiezas[i][j] != 0){
                    if(queJugador[i][j] != 0){
                        posicionPiezas[i][j] = 0;
                        //pesoPiezas[i][j] = 0;
                        queJugador[i][j] = 0;
                    }
                //}
            }
        }
    }

    //FNimprimirMatrices();

    Sleep(500);

    system("cls");
    printf("\n HoLa");

    FNcrearPiezas();
    FNdimensionarPiezas();
    FNiniciarPiezasJ1();
    FNconfigMovimientoPiezas();

    gtk_widget_show_all(formJuego.Pantalla);
}

void FNcargaCoordenadasTablero(){
    int pos = 0;

    for(int i=0;i<5;i++){
        pos = 30 + (185 * i);
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
    FNegra1.Pieza = gtk_button_new_with_label("F1");
    FNegra1.Imagen = gtk_image_new_from_file("FichaNegra.png");
    gtk_button_set_always_show_image(GTK_BUTTON(FNegra1.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FNegra1.Pieza), FNegra1.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FNegra1.Pieza), GTK_RELIEF_NONE);

    FNegra2.Pieza = gtk_button_new_with_label("F2");
    FNegra2.Imagen = gtk_image_new_from_file("FichaNegra.png");
    gtk_button_set_always_show_image(GTK_BUTTON(FNegra2.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FNegra2.Pieza), FNegra2.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FNegra2.Pieza), GTK_RELIEF_NONE);

    FNegra3.Pieza = gtk_button_new_with_label("F3");
    FNegra3.Imagen = gtk_image_new_from_file("FichaNegra.png");
    gtk_button_set_always_show_image(GTK_BUTTON(FNegra3.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FNegra3.Pieza), FNegra3.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FNegra3.Pieza), GTK_RELIEF_NONE);

    FNegra4.Pieza = gtk_button_new_with_label("F4");
    FNegra4.Imagen = gtk_image_new_from_file("FichaNegra.png");
    gtk_button_set_always_show_image(GTK_BUTTON(FNegra4.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FNegra4.Pieza), FNegra4.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FNegra4.Pieza), GTK_RELIEF_NONE);

    FNegra5.Pieza = gtk_button_new_with_label("F5");
    FNegra5.Imagen = gtk_image_new_from_file("FichaNegra.png");
    gtk_button_set_always_show_image(GTK_BUTTON(FNegra5.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FNegra5.Pieza), FNegra5.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FNegra5.Pieza), GTK_RELIEF_NONE);

    FNegra6.Pieza = gtk_button_new_with_label("F6");
    FNegra6.Imagen = gtk_image_new_from_file("FichaNegra.png");
    gtk_button_set_always_show_image(GTK_BUTTON(FNegra6.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FNegra6.Pieza), FNegra6.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FNegra6.Pieza), GTK_RELIEF_NONE);

    FNegra7.Pieza = gtk_button_new_with_label("F7");
    FNegra7.Imagen = gtk_image_new_from_file("FichaNegra.png");
    gtk_button_set_always_show_image(GTK_BUTTON(FNegra7.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FNegra7.Pieza), FNegra7.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FNegra7.Pieza), GTK_RELIEF_NONE);

    FNegra8.Pieza = gtk_button_new_with_label("F8");
    FNegra8.Imagen = gtk_image_new_from_file("FichaNegra.png");
    gtk_button_set_always_show_image(GTK_BUTTON(FNegra8.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FNegra8.Pieza), FNegra8.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FNegra8.Pieza), GTK_RELIEF_NONE);

    FNegra9.Pieza = gtk_button_new_with_label("F9");
    FNegra9.Imagen = gtk_image_new_from_file("FichaNegra.png");
    gtk_button_set_always_show_image(GTK_BUTTON(FNegra9.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FNegra9.Pieza), FNegra9.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FNegra9.Pieza), GTK_RELIEF_NONE);

    FNegra10.Pieza = gtk_button_new_with_label("F10");
    FNegra10.Imagen = gtk_image_new_from_file("FichaNegra.png");
    gtk_button_set_always_show_image(GTK_BUTTON(FNegra10.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FNegra10.Pieza), FNegra10.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FNegra10.Pieza), GTK_RELIEF_NONE);

    FNegra11.Pieza = gtk_button_new_with_label("F11");
    FNegra11.Imagen = gtk_image_new_from_file("FichaNegra.png");
    gtk_button_set_always_show_image(GTK_BUTTON(FNegra11.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FNegra11.Pieza), FNegra11.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FNegra11.Pieza), GTK_RELIEF_NONE);

    FNegra12.Pieza = gtk_button_new_with_label("F12");
    FNegra12.Imagen = gtk_image_new_from_file("FichaNegra.png");
    gtk_button_set_always_show_image(GTK_BUTTON(FNegra12.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FNegra12.Pieza), FNegra12.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FNegra12.Pieza), GTK_RELIEF_NONE);

//Piezas del Jugador 2
    FBlanca1.Pieza = gtk_button_new_with_label("F1");
    FBlanca1.Imagen = gtk_image_new_from_file("FichaBlanca.jpg");
    gtk_button_set_always_show_image(GTK_BUTTON(FBlanca1.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FBlanca1.Pieza), FBlanca1.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FBlanca1.Pieza), GTK_RELIEF_NONE);

    FBlanca2.Pieza = gtk_button_new_with_label("F2");
    FBlanca2.Imagen = gtk_image_new_from_file("FichaBlanca.jpg");
    gtk_button_set_always_show_image(GTK_BUTTON(FBlanca2.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FBlanca2.Pieza), FBlanca2.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FBlanca2.Pieza), GTK_RELIEF_NONE);

    FBlanca3.Pieza = gtk_button_new_with_label("F3");
    FBlanca3.Imagen = gtk_image_new_from_file("FichaBlanca.jpg");
    gtk_button_set_always_show_image(GTK_BUTTON(FBlanca3.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FBlanca3.Pieza), FBlanca3.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FBlanca3.Pieza), GTK_RELIEF_NONE);

    FBlanca4.Pieza = gtk_button_new_with_label("F4");
    FBlanca4.Imagen = gtk_image_new_from_file("FichaBlanca.jpg");
    gtk_button_set_always_show_image(GTK_BUTTON(FBlanca4.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FBlanca4.Pieza), FBlanca4.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FBlanca4.Pieza), GTK_RELIEF_NONE);

    FBlanca5.Pieza = gtk_button_new_with_label("F5");
    FBlanca5.Imagen = gtk_image_new_from_file("FichaBlanca.jpg");
    gtk_button_set_always_show_image(GTK_BUTTON(FBlanca5.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FBlanca5.Pieza), FBlanca5.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FBlanca5.Pieza), GTK_RELIEF_NONE);

    FBlanca6.Pieza = gtk_button_new_with_label("F6");
    FBlanca6.Imagen = gtk_image_new_from_file("FichaBlanca.jpg");
    gtk_button_set_always_show_image(GTK_BUTTON(FBlanca6.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FBlanca6.Pieza), FBlanca6.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FBlanca6.Pieza), GTK_RELIEF_NONE);

    FBlanca7.Pieza = gtk_button_new_with_label("F7");
    FBlanca7.Imagen = gtk_image_new_from_file("FichaBlanca.jpg");
    gtk_button_set_always_show_image(GTK_BUTTON(FBlanca7.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FBlanca7.Pieza), FBlanca7.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FBlanca7.Pieza), GTK_RELIEF_NONE);

    FBlanca8.Pieza = gtk_button_new_with_label("F8");
    FBlanca8.Imagen = gtk_image_new_from_file("FichaBlanca.jpg");
    gtk_button_set_always_show_image(GTK_BUTTON(FBlanca8.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FBlanca8.Pieza), FBlanca8.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FBlanca8.Pieza), GTK_RELIEF_NONE);

    FBlanca9.Pieza = gtk_button_new_with_label("F9");
    FBlanca9.Imagen = gtk_image_new_from_file("FichaBlanca.jpg");
    gtk_button_set_always_show_image(GTK_BUTTON(FBlanca9.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FBlanca9.Pieza), FBlanca9.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FBlanca9.Pieza), GTK_RELIEF_NONE);

    FBlanca10.Pieza = gtk_button_new_with_label("F10");
    FBlanca10.Imagen = gtk_image_new_from_file("FichaBlanca.jpg");
    gtk_button_set_always_show_image(GTK_BUTTON(FBlanca10.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FBlanca10.Pieza), FBlanca10.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FBlanca10.Pieza), GTK_RELIEF_NONE);

    FBlanca11.Pieza = gtk_button_new_with_label("F11");
    FBlanca11.Imagen = gtk_image_new_from_file("FichaBlanca.jpg");
    gtk_button_set_always_show_image(GTK_BUTTON(FBlanca11.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FBlanca11.Pieza), FBlanca11.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FBlanca11.Pieza), GTK_RELIEF_NONE);

    FBlanca12.Pieza = gtk_button_new_with_label("F12");
    FBlanca12.Imagen = gtk_image_new_from_file("FichaBlanca.jpg");
    gtk_button_set_always_show_image(GTK_BUTTON(FBlanca12.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(FBlanca12.Pieza), FBlanca12.Imagen);
    gtk_button_set_relief(GTK_BUTTON(FBlanca12.Pieza), GTK_RELIEF_NONE);


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

    FNdimensionarPiezas(); //llama a la funcion que dimensiona el tamano de las piezas

}
void FNdimensionarPiezas(){ //Dimensiona el tamaño de las piezas
    //Se da tamano a las piezas del jugador 1
    gtk_widget_set_size_request(FNegra1.Pieza, 100,100);
    gtk_widget_set_size_request(FNegra2.Pieza, 100,100);
    gtk_widget_set_size_request(FNegra3.Pieza, 100,100);
    gtk_widget_set_size_request(FNegra4.Pieza, 100,100);
    gtk_widget_set_size_request(FNegra5.Pieza, 100,100);
    gtk_widget_set_size_request(FNegra6.Pieza, 100,100);
    gtk_widget_set_size_request(FNegra7.Pieza, 100,100);
    gtk_widget_set_size_request(FNegra8.Pieza, 100,100);
    gtk_widget_set_size_request(FNegra9.Pieza, 100,100);
    gtk_widget_set_size_request(FNegra10.Pieza, 100,100);
    gtk_widget_set_size_request(FNegra11.Pieza, 100,100);
    gtk_widget_set_size_request(FNegra12.Pieza, 100,100);

    //Se da tamano a las piezas del jugador 2
    gtk_widget_set_size_request(FBlanca1.Pieza, 100,100);
    gtk_widget_set_size_request(FBlanca2.Pieza, 100,100);
    gtk_widget_set_size_request(FBlanca3.Pieza, 100,100);
    gtk_widget_set_size_request(FBlanca4.Pieza, 100,100);
    gtk_widget_set_size_request(FBlanca5.Pieza, 100,100);
    gtk_widget_set_size_request(FBlanca6.Pieza, 100,100);
    gtk_widget_set_size_request(FBlanca7.Pieza, 100,100);
    gtk_widget_set_size_request(FBlanca8.Pieza, 100,100);
    gtk_widget_set_size_request(FBlanca9.Pieza, 100,100);
    gtk_widget_set_size_request(FBlanca10.Pieza, 100,100);
    gtk_widget_set_size_request(FBlanca11.Pieza, 100,100);
    gtk_widget_set_size_request(FBlanca12.Pieza, 100,100);

}


void FNmensajeDialogo(GtkWindow *padre, gchar *mensaje){ //Despliega una ventana de dialogo para advertencias y/o errores (recibe una ventana padre y el mensaje)
        GtkWidget *dialogo, *label, *contenedorDialogo;
        GtkDialogFlags bandera;

        //Se crean los objetos necesarios para el dialogo
        bandera = GTK_DIALOG_DESTROY_WITH_PARENT;
        dialogo = gtk_dialog_new();

        dialogo = gtk_dialog_new_with_buttons("Advertencia!", padre, bandera, ("OK"), GTK_RESPONSE_OK /*GTK_RESPONSE_NONE*/ , NULL);
        gtk_window_set_default_size(GTK_WINDOW(dialogo), 300,100);
        gtk_window_set_position(GTK_WINDOW(dialogo), GTK_WIN_POS_CENTER);
        contenedorDialogo = gtk_dialog_get_content_area(GTK_DIALOG(dialogo));
        label = gtk_label_new(mensaje);

        //Se manda la senal de cierre del dialogo cuando se da ok "response"
        g_signal_connect_swapped(dialogo, "response", G_CALLBACK(gtk_widget_destroy), dialogo);

        // Se agrega el label al contenedor del dialogo y se muestra todo.
        gtk_container_add(GTK_CONTAINER(contenedorDialogo), label);
        gtk_widget_show_all(dialogo);
}

// TURNOS DE LOS JUGADORES
void FNcrearTurnos(){ //Crea los turnos de los jugadores
    //Se crea un color
    GdkColor color;
//    gdk_color_parse("white", &color);

    //Se crea el turno del Jugador 1
    Jugador1.TurnoIcono = gtk_image_new_from_file("jugador1.png");
    Jugador1.TurnoToggle = gtk_toggle_button_new();
    gtk_button_set_image(GTK_BUTTON(Jugador1.TurnoToggle), Jugador1.TurnoIcono);
    gtk_button_set_relief(GTK_BUTTON(Jugador1.TurnoToggle), GTK_RELIEF_NONE);
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), Jugador1.TurnoToggle, 1000, 200);
    Jugador1.TurnoNombre = gtk_label_new("Jugador 1");
    gtk_label_set_text(GTK_LABEL(Jugador1.TurnoNombre), "Juagdor 1");
 //   gtk_widget_modify_fg(GTK_WIDGET(Jugador1.TurnoNombre), GTK_STATE_NORMAL, &color);
  //  gtk_widget_modify_font(GTK_WIDGET(Jugador1.TurnoNombre), pango_font_description_from_string("Calibri BOLD 20"));
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), Jugador1.TurnoNombre, 1000, 40);
    Jugador1.TurnoMovimientos = gtk_label_new("Movimientos: ");
 //   gtk_widget_modify_fg(GTK_WIDGET(Jugador1.TurnoMovimientos), GTK_STATE_NORMAL, &color);
  //  gtk_widget_modify_font(GTK_WIDGET(Jugador1.TurnoMovimientos), pango_font_description_from_string("Calibri 12"));
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), Jugador1.TurnoMovimientos, 1000, 80);
    Jugador1.TurnoCantidadMovimientos = gtk_label_new("0");
  //  gtk_widget_modify_fg(GTK_WIDGET(Jugador1.TurnoCantidadMovimientos), GTK_STATE_NORMAL, &color);
  //  gtk_widget_modify_font(GTK_WIDGET(Jugador1.TurnoCantidadMovimientos), pango_font_description_from_string("Calibri 12"));
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), Jugador1.TurnoCantidadMovimientos, 1120, 80);


    //Se crea el turno del Jugador 2
    Jugador2.TurnoIcono = gtk_image_new_from_file("jugador2.png");
    Jugador2.TurnoToggle = gtk_toggle_button_new();
    gtk_button_set_image(GTK_BUTTON(Jugador2.TurnoToggle), Jugador2.TurnoIcono);
    gtk_button_set_relief(GTK_BUTTON(Jugador2.TurnoToggle), GTK_RELIEF_NONE);
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), Jugador2.TurnoToggle, 1000, 600);
    Jugador2.TurnoNombre = gtk_label_new("Nombre J2");
 //   gtk_widget_modify_fg(GTK_WIDGET(Jugador2.TurnoNombre), GTK_STATE_NORMAL, &color);
//    gtk_widget_modify_font(GTK_WIDGET(Jugador2.TurnoNombre), pango_font_description_from_string("Calibri BOLD 20"));
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), Jugador2.TurnoNombre, 1000, 810);
    Jugador2.TurnoMovimientos = gtk_label_new("Movimientos: ");
 //   gtk_widget_modify_fg(GTK_WIDGET(Jugador2.TurnoMovimientos), GTK_STATE_NORMAL, &color);
 //   gtk_widget_modify_font(GTK_WIDGET(Jugador2.TurnoMovimientos), pango_font_description_from_string("Calibri 12"));
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), Jugador2.TurnoMovimientos, 1000, 785);
    Jugador2.TurnoCantidadMovimientos = gtk_label_new(" 0");
 //   gtk_widget_modify_fg(GTK_WIDGET(Jugador2.TurnoCantidadMovimientos), GTK_STATE_NORMAL, &color);
 //   gtk_widget_modify_font(GTK_WIDGET(Jugador2.TurnoCantidadMovimientos), pango_font_description_from_string("Calibri 12"));
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), Jugador2.TurnoCantidadMovimientos, 1120, 785);

    g_signal_connect(G_OBJECT(Jugador1.TurnoToggle), "toggled", G_CALLBACK(manejadorTurnoJ1), (gpointer) Jugador2.TurnoToggle);
    g_signal_connect(G_OBJECT(Jugador2.TurnoToggle), "toggled", G_CALLBACK(manejadorTurnoJ2), (gpointer) Jugador1.TurnoToggle);

}

void manejadorTurnoJ1(GtkToggleButton *turno){ //Maneja el turno del Jugador 1 cuando se presiona el boton de tipo ToggleButton, dicho botón tiene dos estados (Presionado y No presionado)
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(Jugador1.TurnoToggle))){ //Si el estado del boton esta activo
        printf("\n TURNO J1 ACTIVO");
        habilitarOPmovimientosJ1(); //Se habilitan las opciones de movimiento para el J1
        gtk_widget_set_sensitive(GTK_WIDGET(Jugador2.TurnoToggle), FALSE); //Se desactiva el boton toggle de turno del J2
    }
    else{ //Sino, cuando el boton toggle se desactiva, todo lo mencionado en las sentencias de arriba, se revierten.
        printf("\n TURNO J1 INACTIVO");
        Jugador1.TurnoContador = 0;
        gtk_label_set_text(GTK_LABEL(Jugador1.TurnoCantidadMovimientos), "0");
        deshabilitarOPmovimientosJ1();
        gtk_widget_set_sensitive(GTK_WIDGET(Jugador2.TurnoToggle), TRUE);
    }
}

void manejadorTurnoJ2(GtkToggleButton *turno){ //Maneja el turno del Jugador 2 cuando se presiona el boton de tipo ToggleButton, dicho botón tiene dos estados (Presionado y No presionado)
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(Jugador2.TurnoToggle))){ //Si el estado del boton esta activo
        printf("\n TURNO J2 ACTIVO");
        habilitarOPmovimientosJ2(); //Se habilitan las opciones de movimiento para el J2
        gtk_widget_set_sensitive(GTK_WIDGET(Jugador1.TurnoToggle), FALSE); //Se desactiva el boton toggle de turno del J1
    }
    else{ //Sino, cuando el boton toggle se desactiva, todo lo mencionado en las sentencias de arriba, se revierten.
        printf("\n TURNO J2 INACTIVO");
        Jugador2.TurnoContador = 0;
        gtk_label_set_text(GTK_LABEL(Jugador2.TurnoCantidadMovimientos), "0");
        deshabilitarOPmovimientosJ2();
        gtk_widget_set_sensitive(GTK_WIDGET(Jugador1.TurnoToggle), TRUE);
    }
}
int desplegarMenuMovimiento(GtkWidget *widget, GdkEvent *event){ //Despliega los menus creados como PoPuPs, controlado por un evento de click.

    const int RIGHT_BUTTON = 3;
    const int LEFT_BUTTON = 1;

    if(event->type == GDK_BUTTON_PRESS){
        GdkEventButton *bevent = (GdkEventButton *) event;
        if(bevent->button == LEFT_BUTTON){
            gtk_menu_popup(GTK_MENU(widget), NULL, NULL, NULL, NULL, bevent->button, bevent->time);
        }
        return TRUE;
    }
    return FALSE;
}
void FNpiezaClickeada(GtkWidget *pieza){ //Recibe un OBJETO PIEZA y guarda en una variable la constante de la pieza que representa el OBJETO PIEZA presionado.
    if(pieza == FNegra1.Pieza){
        piezaActual = Negra1;
        jugadorActual = J1;
    }
    else{
        if(pieza == FNegra2.Pieza){
            piezaActual = Negra2;
            jugadorActual = J1;
        }
        else{
            if(pieza == FNegra3.Pieza){
                piezaActual = Negra3;
                jugadorActual = J1;
            }
            else{
                if(pieza == FNegra4.Pieza){
                    piezaActual = Negra4;
                    jugadorActual = J1;
                }
                else{
                    if(pieza == FNegra5.Pieza){
                        piezaActual = Negra5;
                        jugadorActual = J1;
                    }
                    else{
                        if(pieza == FNegra6.Pieza){
                            piezaActual = Negra6;
                            jugadorActual = J1;
                        }
                        else{
                            if(pieza == FNegra7.Pieza){
                                piezaActual = Negra7;
                                jugadorActual = J1;
                            }
                            else{
                                if(pieza == FNegra8.Pieza){
                                    piezaActual = Negra8;
                                    jugadorActual = J1;
                                }
                                else{
                                    if(pieza == FNegra9.Pieza){
                                       piezaActual = Negra9;
                                       jugadorActual = J1;
                                    }
                                    else{
                                        if(pieza == FNegra10.Pieza){
                                            piezaActual = Negra10;
                                            jugadorActual = J1;
                                        }
                                        else{
                                            if(pieza == FNegra11.Pieza){
                                                piezaActual = Negra11;
                                                jugadorActual = J1;
                                            }
                                            else{
                                                if(pieza == FNegra12.Pieza){
                                                    piezaActual = Negra12;
                                                    jugadorActual = J1;
                                                }
                                                else{
                                                    if(pieza == FBlanca1.Pieza){
                                                        piezaActual = Blanca1;
                                                        jugadorActual = J2;
                                                    }
                                                    else{
                                                        if(pieza == FBlanca2.Pieza){
                                                            piezaActual = Blanca2;
                                                            jugadorActual = J2;
                                                        }
                                                        else{
                                                            if(pieza == FBlanca3.Pieza){
                                                                piezaActual = Blanca3;
                                                                jugadorActual = J2;
                                                            }
                                                            else{
                                                                if(pieza == FBlanca4.Pieza){
                                                                   piezaActual = Blanca4;
                                                                   jugadorActual = J2;
                                                                }
                                                                else{
                                                                    if(pieza == FBlanca5.Pieza){
                                                                        piezaActual = Blanca5;
                                                                        jugadorActual = J2;
                                                                    }
                                                                    else{
                                                                        if(pieza == FBlanca6.Pieza){
                                                                            piezaActual = Blanca6;
                                                                            jugadorActual = J2;
                                                                        }
                                                                        else{
                                                                            if(pieza == FBlanca7.Pieza){
                                                                                piezaActual = Blanca7;
                                                                                jugadorActual = J2;
                                                                            }
                                                                            else{
                                                                                if(pieza == FBlanca8.Pieza){
                                                                                    piezaActual = Blanca8;
                                                                                    jugadorActual = J2;
                                                                                }
                                                                                else{
                                                                                    if(pieza == FBlanca9.Pieza){
                                                                                        piezaActual = Blanca9;
                                                                                        jugadorActual = J2;
                                                                                    }
                                                                                    else{
                                                                                        if(pieza == FBlanca10.Pieza){
                                                                                            piezaActual = Blanca10;
                                                                                            jugadorActual = J2;
                                                                                        }
                                                                                        else{
                                                                                            if(pieza == FBlanca11.Pieza){
                                                                                                piezaActual = Blanca11;
                                                                                                jugadorActual = J2;
                                                                                            }
                                                                                            else{
                                                                                                if(pieza == FBlanca12.Pieza){
                                                                                                    piezaActual = Blanca12;
                                                                                                    jugadorActual = J2;
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int siLugarEstaOcupado(int K, int L, int sentido){ //Si retorna true es porque se intenta mover una pieza donde ya esta otra, y este intercambio solo se permite antes de iniciar la partida; tambi�n se manda una advertencia.
    if(sentido == ABAJO){
        if(posicionPiezas[K + 1][L] != 0){//verificando abajo
            return true;
        }
    }

    if(sentido == ARRIBA){
        if(posicionPiezas[K - 1][L] != 0){//verificando arriba
            return true;
        }
    }

    if(sentido == DERECHA){
        if(posicionPiezas[K][L + 1] != 0){//verificando derecha
            return true;
        }
    }

    if(sentido == IZQUIERDA){
        if(posicionPiezas[K][L - 1] != 0){//verificando izquierda
            return true;
        }
    }
    if(sentido == DIAGONAL_DERECHA_ABAJO){//verificando diagonal derecha hacia abajo
        if(posicionPiezas[K+1][L+1] !=0){
            return true;
        }
    }

    if(sentido == DIAGONAL_DERECHA_ARRIBA){//verificando diagonal derecha hacia arriba
        if(posicionPiezas[K+1][L-1] !=0){
            return true;
        }
    }
    if(sentido == DIAGONAL_IZQUIERDA_ABAJO){//verificando diagonal izquierda hacia abajo
        if(posicionPiezas[K-1][L+1] !=0){
            return true;
        }
    }

    if(sentido == DIAGONAL_IZQUIERDA_ARRIBA){//verificando diagonal derecha hacia arriba
        if(posicionPiezas[K-1][L-1] !=0){
            return true;
        }
    }
    return false;
}

int siSobrePasaLimites (int filaOcolumna, int sentido){ //Si retorna true, se intenta mover la pieza fuera del tablero y se env�a una advertencia, si retorna false, se mueve la pieza
    if(sentido == ABAJO){//verificando abajo
        if(filaOcolumna > 5){
            return true;
        }
    }

    if(sentido == ARRIBA){//verificando arriba
        if(filaOcolumna < 0){
            return true;
        }
    }

    if(sentido == DERECHA){//verificando derecha
        if(filaOcolumna > 5){
            return true;
        }
    }

    if(sentido == IZQUIERDA){//verificando izquierda
        if(filaOcolumna < 0){
            return true;
        }
    }

    if(sentido == DIAGONAL_DERECHA_ABAJO){//verificando derecha
        if(filaOcolumna > 5){
            return true;
        }
    }

    if(sentido == DIAGONAL_DERECHA_ARRIBA){//verificando izquierda
        if(filaOcolumna < 0){
            return true;
        }
    }

    if(sentido == DIAGONAL_IZQUIERDA_ABAJO){//verificando derecha
        if(filaOcolumna < 0){
            return true;
        }
    }

    if(sentido == DIAGONAL_IZQUIERDA_ARRIBA){//verificando izquierda
        if(filaOcolumna < 0){
            return true;
        }
    }
    return false;
}

void FNmoverArriba(GtkWidget *pieza){ //Mueve la pieza que recibe una posición arriba

    FNpiezaClickeada(pieza);

    for(I = 0; I < 5; I++){
        for(J = 0; J < 5; J++){
            if(piezaActual == posicionPiezas[I][J]){
                for(K = 0; K < 5; K++){
                    for(L = 0; L < 5; L++){
                        if((I == K) && (J == L)){
                            if(siSobrePasaLimites(K-1, ARRIBA)){
                                FNmensajeDialogo(formDialogo.Ventana, "\n\n No intentes mover la pieza fuera del trablero!\n"); printf("\a");
                            }
                            else{
                                if(siLugarEstaOcupado(K, L, ARRIBA)){
                                    FNmensajeDialogo(formDialogo.Ventana, "\n\n NO PUEDES COLOCAR EN ESA POSICION LA FICHA\n");
                                    printf("\a");
                                }
                                else{
                                    if(Jugador1.TurnoContador >=1 || Jugador2.TurnoContador >= 1){
                                        FNmensajeDialogo(formDialogo.Ventana, "\n\n Has llegado al limite de movimientos posibles \n\n");
//                                                goto salirFNmoverArriba;
                                    }
                                    else{
                                        switch(jugadorActual){
                                            case J1:
                                                Jugador1.TurnoContador++;
                                                sprintf(Jugador1.TurnoArray, "%d", Jugador1.TurnoContador);
                                                gtk_label_set_text(GTK_LABEL(Jugador1.TurnoCantidadMovimientos), Jugador1.TurnoArray);
                                                break;
                                            case J2:
                                                Jugador2.TurnoContador++;
                                                sprintf(Jugador2.TurnoArray, "%d", Jugador2.TurnoContador);
                                                gtk_label_set_text(GTK_LABEL(Jugador2.TurnoCantidadMovimientos), Jugador2.TurnoArray);
                                                break;
                                        }
                                        gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[K-1][L], coordenadasTableroY[K-1][L]);
//                                             FNimprimirMatrices();
                                        goto actualizarPosicionPiezas;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    actualizarPosicionPiezas:
        posicionPiezas[I-1][J] = piezaActual;
        posicionPiezas[I][J] = 0;
    //    pesoPiezas[I-1][J] = pesoActual;
      //  pesoPiezas[I][J] = 0;
        queJugador[I-1][J] = jugadorActual;
        queJugador[I][J] = 0;
    //    FNimprimirMatrices();

}
void FNmoverAbajo(GtkWidget *pieza){ //Mueve la pieza que recibe una posición abajo

    FNpiezaClickeada(pieza); //trae que pieza fue clickeada y la guarda en piezaActual

    for(I = 0; I < 5; I++){
        for(J = 0; J < 5; J++){
            if(piezaActual == posicionPiezas[I][J]){
                for(K = 0; K < 5; K++){
                    for(L = 0; L < 5; L++){
                        if((I == K) && (J == L)){
                            if(siSobrePasaLimites(K+1, ABAJO)){
                                FNmensajeDialogo(formDialogo.Ventana, "\n\n No intentes mover la pieza fuera del trablero!\n");
                                printf("\a");
                            }
                            else{
                                if(siLugarEstaOcupado(K, L, ABAJO)){
                                    FNmensajeDialogo(formDialogo.Ventana, "\nn NO PUEDES COLOCAR EN ESA POSICION LA FICHA\n");
                                    printf("\a");
                                }
                                else{
                                    if(Jugador1.TurnoContador >= 1 || Jugador2.TurnoContador >= 1){
                                        FNmensajeDialogo(formDialogo.Ventana, "\n\n Has llegado al limite de movimientos posibles \n\n");
                                        goto salirFNmoverAbajo;
                                    }
                                    else{
                                        switch(jugadorActual){
                                            case J1:
                                                Jugador1.TurnoContador++;
                                                sprintf(Jugador1.TurnoArray, "%d", Jugador1.TurnoContador);
                                                gtk_label_set_text(GTK_LABEL(Jugador1.TurnoCantidadMovimientos), Jugador1.TurnoArray);
                                                break;
                                            case J2:
                                                Jugador2.TurnoContador++;
                                                sprintf(Jugador2.TurnoArray, "%d", Jugador2.TurnoContador);
                                                gtk_label_set_text(GTK_LABEL(Jugador2.TurnoCantidadMovimientos), Jugador2.TurnoArray);
                                                break;
                                        }
                                        gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[K+1][L], coordenadasTableroY[K+1][L]);
                                        //FNimprimirMatrices();
                                        goto actualizarPosicionPiezas;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }


    actualizarPosicionPiezas:
        posicionPiezas[I+1][J] = piezaActual;
        posicionPiezas[I][J] = 0;
  //      pesoPiezas[I+1][J] = pesoActual;
//        pesoPiezas[I][J] = 0;
        queJugador[I+1][J] = jugadorActual;
        queJugador[I][J] = 0;

    salirFNmoverAbajo:
        printf(" ");

}


void FNmoverDerecha(GtkWidget *pieza){ //Mueve la pieza que recibe una posición a la derecha
    FNpiezaClickeada(pieza);

    for(I = 0; I < 5; I++){
        for(J = 0; J < 5; J++){
            if(piezaActual == posicionPiezas[I][J]){
                for(K = 0; K < 5; K++){
                    for(L = 0; L < 5; L++){
                        if((I != K) && (J == L)){
                            if(siSobrePasaLimites(L+1, DERECHA)){
                                FNmensajeDialogo(formDialogo.Ventana, "\n\n No intentes mover la pieza fuera del trablero!\n");
                                printf("\a");
                            }
                            else{
                                if(siLugarEstaOcupado(K, L, DERECHA)){
                                    FNmensajeDialogo(formDialogo.Ventana, "\nn NO PUEDES COLOCAR EN ESA POSICION LA FICHA\n");
                                    printf("\a");
                                }
                                else{
                                    if(Jugador1.TurnoContador >= 1 || Jugador2.TurnoContador >= 1){
                                        FNmensajeDialogo(formDialogo.Ventana, "\n\n Has llegado al limite de movimientos posibles \n\n");
                                        goto salirFNmoverDerecha;
                                    }
                                    else{
                                        switch(jugadorActual){
                                            case J1:
                                                Jugador1.TurnoContador++;
                                                sprintf(Jugador1.TurnoArray, "%d", Jugador1.TurnoContador);
                                                gtk_label_set_text(GTK_LABEL(Jugador1.TurnoCantidadMovimientos), Jugador1.TurnoArray);
                                            break;
                                            case J2:
                                                Jugador2.TurnoContador++;
                                                sprintf(Jugador2.TurnoArray, "%d", Jugador2.TurnoContador);
                                                gtk_label_set_text(GTK_LABEL(Jugador2.TurnoCantidadMovimientos), Jugador2.TurnoArray);
                                            break;
                                        }
                                        gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[K][L+1], coordenadasTableroY[K][L+1]);
                                        goto actualizarPosicionPiezas;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    actualizarPosicionPiezas:
        posicionPiezas[I][J+1] = piezaActual;
        posicionPiezas[I][J] = 0;
//        pesoPiezas[I][J+1] = pesoActual;
  //      pesoPiezas[I][J] = 0;
        queJugador[I][J+1] = jugadorActual;
        queJugador[I][J] = 0;
    //    FNimprimirMatrices();
    salirFNmoverDerecha:
        printf(" ");

}

void FNmoverDiagonalDerecha(GtkWidget *pieza){ //Mueve la pieza que recibe una posición a la diagonal derecha
    FNpiezaClickeada(pieza);

    for(I = 0; I < 5; I++){
        for(J = 0; J < 5; J++){
            if(piezaActual == posicionPiezas[I][J]){
                for(K = 0; K < 5; K++){
                    for(L = 0; L < 5; L++){
                        if((I != K) && (J == L)){
                            if(siSobrePasaLimites(L+1, DERECHA)){
                                FNmensajeDialogo(formDialogo.Ventana, "\n\n No intentes mover la pieza fuera del trablero!\n");
                                printf("\a");
                            }
                            else{
                                if(siLugarEstaOcupado(K, L, DERECHA)){
                                    FNmensajeDialogo(formDialogo.Ventana, "\nn NO PUEDES COLOCAR EN ESA POSICION LA FICHA\n");
                                    printf("\a");
                                }
                                else{
                                    if(Jugador1.TurnoContador >= 1 || Jugador2.TurnoContador >= 1){
                                        FNmensajeDialogo(formDialogo.Ventana, "\n\n Has llegado al limite de movimientos posibles \n\n");
                                        goto salirFNmoverDerecha;
                                    }
                                    else{
                                        switch(jugadorActual){
                                            case J1:
                                                Jugador1.TurnoContador++;
                                                sprintf(Jugador1.TurnoArray, "%d", Jugador1.TurnoContador);
                                                gtk_label_set_text(GTK_LABEL(Jugador1.TurnoCantidadMovimientos), Jugador1.TurnoArray);
                                            break;
                                            case J2:
                                                Jugador2.TurnoContador++;
                                                sprintf(Jugador2.TurnoArray, "%d", Jugador2.TurnoContador);
                                                gtk_label_set_text(GTK_LABEL(Jugador2.TurnoCantidadMovimientos), Jugador2.TurnoArray);
                                            break;
                                        }
                                        gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[K][L+1], coordenadasTableroY[K][L]);
                                        goto actualizarPosicionPiezas;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    actualizarPosicionPiezas:
        posicionPiezas[I+1][J+1] = piezaActual;
        posicionPiezas[I][J] = 0;
//        pesoPiezas[I][J+1] = pesoActual;
  //      pesoPiezas[I][J] = 0;
        queJugador[I+1][J+1] = jugadorActual;
        queJugador[I][J] = 0;
    //    FNimprimirMatrices();
    salirFNmoverDerecha:
        printf(" ");

}
void FNmoverIzquierda(GtkWidget *pieza){ //Mueve la pieza que recibe una posición a la izquierda

    FNpiezaClickeada(pieza);

    for(I = 0; I < 5; I++){
        for(J = 0; J < 5; J++){
            if(piezaActual == posicionPiezas[I][J]){
                for(K = 0; K < 5; K++){
                    for(L = 0; L < 5; L++){
                        if((I == K) && (J == L)){
                            if(siSobrePasaLimites(L-1, IZQUIERDA)){
                                FNmensajeDialogo(formDialogo.Ventana, "\n\n No intentes mover la pieza fuera del trablero!\n");
                                printf("\a");
                            }
                            else{
                                if(siLugarEstaOcupado(K, L, IZQUIERDA)){
                                    FNmensajeDialogo(formDialogo.Ventana, "\nn NO PUEDES COLOCAR EN ESA POSICION LA FICHA\n");
                                    printf("\a");
                                }
                                else{
                                    if(Jugador1.TurnoContador >= 1 || Jugador2.TurnoContador >= 1){
                                        FNmensajeDialogo(formDialogo.Ventana, "\n\n Has llegado al limite de movimientos posibles \n\n");
                                        goto salirFNmoverIzquierda;
                                    }
                                    else{
                                        switch(jugadorActual){
                                            case J1:
                                                Jugador1.TurnoContador++;
                                                sprintf(Jugador1.TurnoArray, "%d", Jugador1.TurnoContador);
                                                gtk_label_set_text(GTK_LABEL(Jugador1.TurnoCantidadMovimientos), Jugador1.TurnoArray);
                                            break;
                                            case J2:
                                                Jugador2.TurnoContador++;
                                                sprintf(Jugador2.TurnoArray, "%d", Jugador2.TurnoContador);
                                                gtk_label_set_text(GTK_LABEL(Jugador2.TurnoCantidadMovimientos), Jugador2.TurnoArray);
                                            break;
                                        }
                                        gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[K][L-1], coordenadasTableroY[K][L-1]);
                                        goto actualizarPosicionPiezas;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    actualizarPosicionPiezas:
        posicionPiezas[I][J-1] = piezaActual;
        posicionPiezas[I][J] = 0;
    //    pesoPiezas[I][J-1] = pesoActual;
      //  pesoPiezas[I][J] = 0;
        queJugador[I][J-1] = jugadorActual;
        queJugador[I][J] = 0;

    salirFNmoverIzquierda:
        printf(" ");

}


void habilitarOPmovimientosJ1(){ //Habilita las opciones de movimiento del Jugador 1
    //Jugador 1
    gtk_widget_show_all(FNegra1.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra1.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FNegra1.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_show_all(FNegra2.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra2.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FNegra2.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_show_all(FNegra3.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra3.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra3.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra3.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FNegra3.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_show_all(FNegra4.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra4.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra4.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra4.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FNegra4.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_show_all(FNegra5.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra5.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra5.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra5.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FNegra5.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_show_all(FNegra6.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra6.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra6.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra6.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FNegra6.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_show_all(FNegra7.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra7.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra7.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra7.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FNegra7.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_show_all(FNegra8.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra8.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra8.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra8.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FNegra8.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_show_all(FNegra9.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra9.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra9.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra9.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FNegra9.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_show_all(FNegra10.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra10.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra10.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra10.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FNegra10.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_show_all(FNegra11.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra11.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra11.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra11.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FNegra11.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_show_all(FNegra12.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra12.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra12.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra12.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FNegra12.movimiento.OPmoverDiagonalDerecha);
}

void deshabilitarOPmovimientosJ1(){ //Deshabilita las opciones de movimiento del Jugador 1

    //Jugador 1
    gtk_widget_hide(FNegra1.movimiento.OPmoverArriba);
    gtk_widget_hide(FNegra1.movimiento.OPmoverAbajo);
    gtk_widget_hide(FNegra1.movimiento.OPmoverDerecha);
    gtk_widget_hide(FNegra1.movimiento.OPmoverIzquierda);
    gtk_widget_hide(FNegra1.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_hide(FNegra2.movimiento.OPmoverArriba);
    gtk_widget_hide(FNegra2.movimiento.OPmoverAbajo);
    gtk_widget_hide(FNegra2.movimiento.OPmoverDerecha);
    gtk_widget_hide(FNegra2.movimiento.OPmoverIzquierda);
    gtk_widget_hide(FNegra2.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_hide(FNegra3.movimiento.OPmoverArriba);
    gtk_widget_hide(FNegra3.movimiento.OPmoverAbajo);
    gtk_widget_hide(FNegra3.movimiento.OPmoverDerecha);
    gtk_widget_hide(FNegra3.movimiento.OPmoverIzquierda);
    gtk_widget_hide(FNegra3.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_hide(FNegra4.movimiento.OPmoverArriba);
    gtk_widget_hide(FNegra4.movimiento.OPmoverAbajo);
    gtk_widget_hide(FNegra4.movimiento.OPmoverDerecha);
    gtk_widget_hide(FNegra4.movimiento.OPmoverIzquierda);
    gtk_widget_hide(FNegra4.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_hide(FNegra5.movimiento.OPmoverArriba);
    gtk_widget_hide(FNegra5.movimiento.OPmoverAbajo);
    gtk_widget_hide(FNegra5.movimiento.OPmoverDerecha);
    gtk_widget_hide(FNegra5.movimiento.OPmoverIzquierda);
    gtk_widget_hide(FNegra5.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_hide(FNegra6.movimiento.OPmoverArriba);
    gtk_widget_hide(FNegra6.movimiento.OPmoverAbajo);
    gtk_widget_hide(FNegra6.movimiento.OPmoverDerecha);
    gtk_widget_hide(FNegra6.movimiento.OPmoverIzquierda);
    gtk_widget_hide(FNegra6.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_hide(FNegra7.movimiento.OPmoverArriba);
    gtk_widget_hide(FNegra7.movimiento.OPmoverAbajo);
    gtk_widget_hide(FNegra7.movimiento.OPmoverDerecha);
    gtk_widget_hide(FNegra7.movimiento.OPmoverIzquierda);
    gtk_widget_hide(FNegra7.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_hide(FNegra8.movimiento.OPmoverArriba);
    gtk_widget_hide(FNegra8.movimiento.OPmoverAbajo);
    gtk_widget_hide(FNegra8.movimiento.OPmoverDerecha);
    gtk_widget_hide(FNegra8.movimiento.OPmoverIzquierda);
    gtk_widget_hide(FNegra8.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_hide(FNegra9.movimiento.OPmoverArriba);
    gtk_widget_hide(FNegra9.movimiento.OPmoverAbajo);
    gtk_widget_hide(FNegra9.movimiento.OPmoverDerecha);
    gtk_widget_hide(FNegra9.movimiento.OPmoverIzquierda);
    gtk_widget_hide(FNegra9.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_hide(FNegra10.movimiento.OPmoverArriba);
    gtk_widget_hide(FNegra10.movimiento.OPmoverAbajo);
    gtk_widget_hide(FNegra10.movimiento.OPmoverDerecha);
    gtk_widget_hide(FNegra10.movimiento.OPmoverIzquierda);
    gtk_widget_hide(FNegra10.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_hide(FNegra11.movimiento.OPmoverArriba);
    gtk_widget_hide(FNegra11.movimiento.OPmoverAbajo);
    gtk_widget_hide(FNegra11.movimiento.OPmoverDerecha);
    gtk_widget_hide(FNegra11.movimiento.OPmoverIzquierda);
    gtk_widget_hide(FNegra11.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_hide(FNegra12.movimiento.OPmoverArriba);
    gtk_widget_hide(FNegra12.movimiento.OPmoverAbajo);
    gtk_widget_hide(FNegra12.movimiento.OPmoverDerecha);
    gtk_widget_hide(FNegra12.movimiento.OPmoverIzquierda);
    gtk_widget_hide(FNegra12.movimiento.OPmoverDiagonalDerecha);
}

void habilitarOPmovimientosJ2(){ //Habilita las opciones de movimiento del Jugador 1
    //Jugador 1
    gtk_widget_show_all(FBlanca1.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca1.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FBlanca1.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_show_all(FBlanca2.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca2.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FBlanca2.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_show_all(FBlanca3.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca3.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca3.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca3.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FBlanca3.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_show_all(FBlanca4.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca4.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca4.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca4.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FBlanca4.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_show_all(FBlanca5.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca5.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca5.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca5.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FBlanca5.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_show_all(FBlanca6.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca6.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca6.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca6.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FBlanca6.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_show_all(FBlanca7.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca7.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca7.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca7.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FBlanca7.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_show_all(FBlanca8.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca8.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca8.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca8.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FBlanca8.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_show_all(FBlanca9.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca9.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca9.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca9.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FBlanca9.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_show_all(FBlanca10.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca10.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca10.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca10.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FBlanca10.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_show_all(FBlanca11.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca11.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca11.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca11.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FBlanca11.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_show_all(FBlanca12.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca12.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca12.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca12.movimiento.OPmoverIzquierda);
    gtk_widget_show_all(FBlanca12.movimiento.OPmoverDiagonalDerecha);
}

void deshabilitarOPmovimientosJ2(){ //Deshabilita las opciones de movimiento del Jugador 1

    //Jugador 1
    gtk_widget_hide(FBlanca1.movimiento.OPmoverArriba);
    gtk_widget_hide(FBlanca1.movimiento.OPmoverAbajo);
    gtk_widget_hide(FBlanca1.movimiento.OPmoverDerecha);
    gtk_widget_hide(FBlanca1.movimiento.OPmoverIzquierda);
    gtk_widget_hide(FBlanca1.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_hide(FBlanca2.movimiento.OPmoverArriba);
    gtk_widget_hide(FBlanca2.movimiento.OPmoverAbajo);
    gtk_widget_hide(FBlanca2.movimiento.OPmoverDerecha);
    gtk_widget_hide(FBlanca2.movimiento.OPmoverIzquierda);
    gtk_widget_hide(FBlanca2.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_hide(FBlanca3.movimiento.OPmoverArriba);
    gtk_widget_hide(FBlanca3.movimiento.OPmoverAbajo);
    gtk_widget_hide(FBlanca3.movimiento.OPmoverDerecha);
    gtk_widget_hide(FBlanca3.movimiento.OPmoverIzquierda);
    gtk_widget_hide(FBlanca3.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_hide(FBlanca4.movimiento.OPmoverArriba);
    gtk_widget_hide(FBlanca4.movimiento.OPmoverAbajo);
    gtk_widget_hide(FBlanca4.movimiento.OPmoverDerecha);
    gtk_widget_hide(FBlanca4.movimiento.OPmoverIzquierda);
    gtk_widget_hide(FBlanca4.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_hide(FBlanca5.movimiento.OPmoverArriba);
    gtk_widget_hide(FBlanca5.movimiento.OPmoverAbajo);
    gtk_widget_hide(FBlanca5.movimiento.OPmoverDerecha);
    gtk_widget_hide(FBlanca5.movimiento.OPmoverIzquierda);
    gtk_widget_hide(FBlanca5.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_hide(FBlanca6.movimiento.OPmoverArriba);
    gtk_widget_hide(FBlanca6.movimiento.OPmoverAbajo);
    gtk_widget_hide(FBlanca6.movimiento.OPmoverDerecha);
    gtk_widget_hide(FBlanca6.movimiento.OPmoverIzquierda);
    gtk_widget_hide(FBlanca6.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_hide(FBlanca7.movimiento.OPmoverArriba);
    gtk_widget_hide(FBlanca7.movimiento.OPmoverAbajo);
    gtk_widget_hide(FBlanca7.movimiento.OPmoverDerecha);
    gtk_widget_hide(FBlanca7.movimiento.OPmoverIzquierda);
    gtk_widget_hide(FBlanca7.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_hide(FBlanca8.movimiento.OPmoverArriba);
    gtk_widget_hide(FBlanca8.movimiento.OPmoverAbajo);
    gtk_widget_hide(FBlanca8.movimiento.OPmoverDerecha);
    gtk_widget_hide(FBlanca8.movimiento.OPmoverIzquierda);
    gtk_widget_hide(FBlanca8.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_hide(FBlanca9.movimiento.OPmoverArriba);
    gtk_widget_hide(FBlanca9.movimiento.OPmoverAbajo);
    gtk_widget_hide(FBlanca9.movimiento.OPmoverDerecha);
    gtk_widget_hide(FBlanca9.movimiento.OPmoverIzquierda);
    gtk_widget_hide(FBlanca9.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_hide(FBlanca10.movimiento.OPmoverArriba);
    gtk_widget_hide(FBlanca10.movimiento.OPmoverAbajo);
    gtk_widget_hide(FBlanca10.movimiento.OPmoverDerecha);
    gtk_widget_hide(FBlanca10.movimiento.OPmoverIzquierda);
    gtk_widget_hide(FBlanca10.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_hide(FBlanca11.movimiento.OPmoverArriba);
    gtk_widget_hide(FBlanca11.movimiento.OPmoverAbajo);
    gtk_widget_hide(FBlanca11.movimiento.OPmoverDerecha);
    gtk_widget_hide(FBlanca11.movimiento.OPmoverIzquierda);
    gtk_widget_hide(FBlanca11.movimiento.OPmoverDiagonalDerecha);

    gtk_widget_hide(FBlanca12.movimiento.OPmoverArriba);
    gtk_widget_hide(FBlanca12.movimiento.OPmoverAbajo);
    gtk_widget_hide(FBlanca12.movimiento.OPmoverDerecha);
    gtk_widget_hide(FBlanca12.movimiento.OPmoverIzquierda);
    gtk_widget_hide(FBlanca12.movimiento.OPmoverDiagonalDerecha);
}
