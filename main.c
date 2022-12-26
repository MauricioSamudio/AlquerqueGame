#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include<gtk/gtk.h>
#include<glib/gprintf.h>
#include<stdbool.h>

/// /////////////////////////////////// INICIO DECLARACIÓN DE CONSTANTES //////////////////////////////////////////////////////////////////
#define ARRIBA     10
#define ABAJO      20
#define DERECHA    30
#define IZQUIERDA  40

#define J1 100
#define J2 200

#define ACTIVO 50
#define INACTIVO 60

//Constantes de piezas del JUGADOR 1: utilizadas para cargar las piezas en una matriz 8x8 analoga al tablero del juego.
#define ELEFANTEJ1 101
#define CAMELLOJ1  102
#define CABALLO1J1 103
#define CABALLO2J1 104
#define PERRO1J1   105
#define PERRO2J1   106
#define GATO1J1    107
#define GATO2J1    108
#define CONEJO1J1  109
#define CONEJO2J1  110
#define CONEJO3J1  111
#define CONEJO4J1  112
#define CONEJO5J1  113
#define CONEJO6J1  114
#define CONEJO7J1  115
#define CONEJO8J1  116
//Constantes de piezas del JUGADOR 2: utilizadas para cargar las piezas en una matriz 8x8 analoga al tablero del juego.
#define ELEFANTEJ2 201
#define CAMELLOJ2  202
#define CABALLO1J2 203
#define CABALLO2J2 204
#define PERRO1J2   205
#define PERRO2J2   206
#define GATO1J2    207
#define GATO2J2    208
#define CONEJO1J2  209
#define CONEJO2J2  210
#define CONEJO3J2  211
#define CONEJO4J2  212
#define CONEJO5J2  213
#define CONEJO6J2  214
#define CONEJO7J2  215
#define CONEJO8J2  216
/// /////////////////////////////////// FIN DECLARACIÓN DE CONSTANTES //////////////////////////////////////////////////////////////////////////

/// ///////////// DECLARACION DE CONSTRUCTOR ///////////////////////////////////////////////////////////////////////////////////////////////////
GtkBuilder *builder;
GtkWidget *windowAyuda;
/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/// ///////////////////////////////// INICIO DECLARACION DE VARIABLES GLOBALES Y ARREGLOS ////////////////////////////////////////////////////////////
int coordenadasTableroX[5][5]; //En esta matriz se guardan las coordenadas (X) del tablero, cada lugar de la matriz representa una posición del tablero.
int coordenadasTableroY[5][5]; //En esta matriz se guardan las coordenadas (Y) del tablero, cada lugar de la matriz representa una posición del tablero.
int posicionPiezas[5][5]; //En esta matriz se guardan y ubican las piezas en sus respepctivas posiciones imaginando que la matriz es el tablero, luego de que las piezas fueran inicializadas en posiciones random o aleatorias.
int pesoPiezas[100][100]; //Matriz analoga a posicionPiezas, en esta se guardan el peso(prioridad de piezas), ubicadas al mismo tiempo que se inicializaron de forma aleatoria todas las piezas.
int queJugador[100][100]; //Matriz analoga a posicionPiezas, en esta se guarda informacion si se trata del Jugador 1 o Jugador 2, ubicadas al mismo tiempo que se inicializaron de forma aleatoria todas las piezas.
int piezasJ1[17]; //Guarda las posiciones random tomadas para no repetirlas, se utiliza para mandar a una función una pieza aleatoria.
int piezasJ2[17]; //Guarda las posiciones random tomadas para no repetirlas, se utiliza para mandar a una función una pieza aleatoria.
int piezaRandom; //Guarda momentaneamente la posicion del vector "piezasJ1" y "Piezas J2" para recorrerlo.
int limiteInferior = 0, limiteSuperior = 15; //Guardan los "limites superior e inferior" de los vectores de las piezas, para obtener las posiciones aleatorias.
int randomPos; //Guarda la posicion a la hora de recorrer los vectores "piezasJ1" y "piezasJ2".
int piezaActual; //Se utiliza en las funciones de movimientos, para guardar en que pieza se hizo click.
int pesoActual; //Se utiliza en las funciones de movimientos, para guardar el peso de la pieza en que se hizo click.
int jugadorActual; //Se utiliza en las funciones de movimientos, para guardar de que jugador es la pieza en que se hizo click.
int sentidos[5] = {ARRIBA, ABAJO, DERECHA, IZQUIERDA}; //Se carga en un arreglo los sentidos de los movimientos
int i = 0, j = 0; //Índices varios para iterar en loops
int fila = 0, columna = 0; //Índices varios para iterar en loops
int I = 0, J = 0, K = 0, L = 0; //Índices varios para iterar en loops
bool seEliminoPieza = false; //Bandera para saber si se elimino o no una pieza al caer a una posicion trampa
int P, Q; //Indices varios
//Variables que constantemente se sobreescriben para guardar la info de las piezas que se van a mover(empujar o estirar)
int piezaEmpujada, pesoPiezaEmpujada, queJugadorPiezaEmpujada;
int piezaQueEmpuja, pesoPiezaQueEmpuja, queJugadorPiezaQueEmpuja;
int pieza_A_EmpujarEstirar; //pieza QUE SE VA a empujar o estirar
int pieza_que_empujaOestira; //pieza QUE EMPUJA o ESTIRA
int coorXempEst; //Coordenada X de pieza a empujar o estirar
int coorYempEst; //Coordenada Y de pieza a empujar o estitrar
bool entra = false; //Bandera para verificar entrada en loops
/// ///////////////////////////////// FIN DECLARACION DE VARIABLES GLOBALES Y ARREGLOS ////////////////////////////////////////////////////////////////////////


/// /////////////////////////////// INICIO DECLARACION DE FUNCIONES ///////////////////////////////////////////////////////////////////////////////////////////
void FNcargaCoordenadasTablero(); //Carga las coordenadas del tablero en dos matrices: coordenadasTableroX; coordenadasTableroY, para X e Y respectivamente.
void FNcrearPiezas();//Crea las piezas
void FNrecargarPiezas(); //Recarga las constantes de las piezas en los vectores piezasJ1 y piezasJ2
void FNdimensionarPiezas();//Define el tamaño de las piezas
void FNconfigFormJuego();//Crea la pantalla del juego y el layout del mismo, en dicho layout van colocadas las piezas y el trablero de juego, además otros botones y menus.
void FNcrearMenusFormJuego(); //Crea los menus de opciones de la pantalla  de juego
void FNcolocarPiezas(int PiezaAletoria, int Fila, int Columna); //Coloca las piezas en el tablero, recibe tres parametros: una pieza random, una fila y una columna.
void FNrandomizarPiezas(); //EN PRUEBA Función que vuelve a randomizar las posiciones iniciales de las piezas de cada jugador.
static void FNiniciarPiezasJ1(); //Coloca de forma aleatoria las piezas en las posiciones de inicio del Jugador 1
static void FNiniciarPiezasJ2(); //Coloca de forma aleatoria las piezas en las posiciones de inicio del Jugador 1
void FNconfigMovimientoPiezas(); //Funcion que configura el Menú de Movimientos de las piezas
void FNcrearMenusPiezas(); //Función que crea los menús de las piezas
void FNconectarMenusPiezas(); //Función que conecta los menús a las respectivas piezas
void FNconectarOPMovimientosPiezas(); //Conecta las opciones de movimiento a los menus de cada pieza
void FNconectarOPempujarOestirarPiezas(); //Conecta las opciones de empuje a los menus de cada pieza
void FNconectarOPestirarPiezas(); //Conecta las opciones de estirar a los menus de cada pieza
void FNmostrarOPmenusPiezas(); //Función particular de la librería que hace visible los submenús para los movimientos.
int  desplegarMenuMovimiento(GtkWidget *widget, GdkEvent *event); //Funcion que despliega el menú PoPup de cada puiza para moverla
void FNmoverAbajo(GtkWidget *pieza); //Mueve la pieza Abajo
void FNmoverArriba(GtkWidget *pieza); //Mueve la pieza Arriba
void FNmoverDerecha(GtkWidget *pieza); //Mueve la pieza a la Derecha
void FNmoverIzquierda(GtkWidget *pieza); //Mueve la pieza a la Izquierda
void FNempujarArribaJ1(GtkWidget *pieza); //Empuja hacia arriba la pieza del J1
void FNestirarDerechaJ1(GtkWidget *pieza);
void FNestirarIzquierdaJ1(GtkWidget *pieza);
void FNestirarDerechaJ2(GtkWidget *pieza);
void FNestirarIzquierdaJ2(GtkWidget *pieza);
void FNestirarAbajoJ1(GtkWidget *pieza); //Estira hacia abajo la pieza del J2
void FNempujarDerechaJ1(GtkWidget *pieza); //Empuja a la derecha la pieza del J1
void FNempujarIzquierdaJ1(GtkWidget *pieza); //Empuja a la izquierda la pieza del J2
void FNempujarAbajoJ2(GtkWidget *pieza); //Empuja hacia abajo la pieza del J2
void FNestirarArribaJ2(GtkWidget *pieza); //Estura hacia arriba la pieza del J2
void FNempujarDerechaJ2(GtkWidget *pieza); //Empuja a la derecha la pieza del J2
void FNempujarIzquierdaJ2(GtkWidget *pieza); //Empuja a la izquierda la pieza del J2
void FNimprimirMatrices(); //Imprime en la consola las matrices con las que se esta trabajando
void FNmensajeDialogo(GtkWindow *padre, gchar *mensaje); //Funcion para desplegar dialogos de errores o advertencias
int siCongela(int I, int J); //Verifica si la pieza que se desea mover esta congelada
int siSobrePasaLimites(int filaOcolumna, int sentido); //Verifica si la pieza que se desea mover esta intentando moverse fuera de los limites del tablero.
int siLugarEstaOcupado(int K, int L, int sentido); //Verifica si el lugar al que se desea mover la pieza esta ocupado. Evita el intercambio sin sentido de piezas.
int siCaeEnTrampa(int fil, int col); //Verifica si el lugar al que se movió la pieza era una trampa, y si está a salvo o no de la eliminación de la pieza
int siPuedeEmpujarOestirar(int); //Verifica si se puede empujar o estirar
int siGana(int I, int J, int sentido, int jugador, int pieza);
void FNpiezaClickeada(GtkWidget *pieza); //Función que recibe la pieza en que se hizo click e identifica de que pieza se trata, para luego trabajar con las funciones de movimientos.
void manejadorTurnoJ1(GtkToggleButton *turno); //Maneja el turno del Jugador 1
void manejadorTurnoJ2(GtkToggleButton *turno); //Maneja el turno del Jugador 2
void FNcrearTurnos(); //Crea los turnos de los Jugadores
void habilitarOPmovimientosJ1(); //Habilita o deshabilita opciones de movimientos, empuje o estire de las piezas, dependiendo del turno.
void habilitarOPmovimientosJ2(); //Habilita o deshabilita opciones de movimientos, empuje o estire de las piezas, dependiendo del turno.
void deshabilitarOPmovimientosJ1(); //Habilita o deshabilita opciones de movimientos, empuje o estire de las piezas, dependiendo del turno.
void deshabilitarOPmovimientosJ2(); //Habilita o deshabilita opciones de movimientos, empuje o estire de las piezas, dependiendo del turno.
void habilitarOPempujarOestirarJ1(); //Habilita o deshabilita opciones de movimientos, empuje o estire de las piezas, dependiendo del turno.
void habilitarOPempujarOestirarJ2(); //Habilita o deshabilita opciones de movimientos, empuje o estire de las piezas, dependiendo del turno.
void deshabilitarOPempujarOestirarJ1(); //Habilita o deshabilita opciones de movimientos, empuje o estire de las piezas, dependiendo del turno.
void deshabilitarOPempujarOestirarJ2(); //Habilita o deshabilita opciones de movimientos, empuje o estire de las piezas, dependiendo del turno.
void empujaOestiraJ1(int posicionPieza, GtkWidget *pieza, int sentido); //Realiza el empuje o estire de J1
void empujaOestiraJ2(int posicionPieza, GtkWidget *pieza, int sentido); //Realiza el empuje o estire del J2
void FNmovimientoAleatorio(); //(EN PRUEBA) Dispara la funcion para mover aleatoriamente las piezas del J2
void FNmoverAleatoriamente(int constPieza); //(EN PRUEBA) mueve aleatoriamente las piezas
void FNreiniciarJuego();
void FNmostrarPantallaCreditos();
void FNmostrarPantallaAyuda();
/// /////////////////////////////// FIN DECLARACION DE FUNCIONES ///////////////////////////////////////////////////////////////////////////////////////////


/// ///////////////////////////// ESTRUCTURAS DE DATOS UTILIZADAS /////////////////////////////////////////////////////////////////////////////////////////
struct Pantallas { //Guarda los objetos de las pantallas
    GtkWidget *Layout;
    GtkWidget *Frame;
    GtkWidget *Fondo;
    GtkWidget *Pantalla;
    GtkWindow *Ventana;

} formInicio, formJuego,formCreditos,formAyuda, formDialogo, tablero, decorado;

struct OpcionesMenus { //Guarda los objetos de las opciones de los menus de las pantallas
    GtkWidget *Boton;
    GtkWidget *Icono;
    GtkWidget *Pantalla;
    GtkWidget *Fondo;
} cerrar, randomizar, ranking, ayuda, ajustes, creditos, jugar, reiniciar, movimientoAleatorio;

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

struct MovimientosGUI{ //(DEPRECADO)
    GtkWidget *Imagen;
    GtkWidget *Label;
    GtkWidget *Box;
};

struct Movimientos { //Guarda las opciones, labels, iconos y contenedores de los movimientos de las opciones de movimientos de las piezas. (Se anida con la estructura Juego)
    GtkWidget *OPmoverArriba;
    GtkWidget *OPmoverAbajo;
    GtkWidget *OPmoverDerecha;
    GtkWidget *OPmoverIzquierda;
    GtkWidget *OPempujarArriba;
    GtkWidget *OPempujarAbajo;
    GtkWidget *OPempujarDerecha;
    GtkWidget *OPempujarIzquierda;
    GtkWidget *OPestirarArriba;
    GtkWidget *OPestirarAbajo;
    GtkWidget *OPestirarDerecha;
    GtkWidget *OPestirarIzquierda;
    GtkWidget *OPcancelar;

    GtkWidget *LBLmoverArriba;
    GtkWidget *LBLmoverAbajo;
    GtkWidget *LBLmoverDerecha;
    GtkWidget *LBLmoverIzquierda;
    GtkWidget *LBLempujarArriba;
    GtkWidget *LBLempujarAbajo;
    GtkWidget *LBLempujarDerecha;
    GtkWidget *LBLempujarIzquierda;
    GtkWidget *LBLestirarArriba;
    GtkWidget *LBLestirarAbajo;
    GtkWidget *LBLestirarDerecha;
    GtkWidget *LBLestirarIzquierda;
    GtkWidget *LBLcancelar;

    GtkWidget *BOXmoverArriba;
    GtkWidget *BOXmoverAbajo;
    GtkWidget *BOXmoverDerecha;
    GtkWidget *BOXmoverIzquierda;
    GtkWidget *BOXempujarArriba;
    GtkWidget *BOXempujarAbajo;
    GtkWidget *BOXempujarDerecha;
    GtkWidget *BOXempujarIzquierda;
    GtkWidget *BOXestirarArriba;
    GtkWidget *BOXestirarAbajo;
    GtkWidget *BOXestirarDerecha;
    GtkWidget *BOXestirarIzquierda;
    GtkWidget *BOXcancelar;

    GtkWidget *ICOmoverArriba;
    GtkWidget *ICOmoverAbajo;
    GtkWidget *ICOmoverDerecha;
    GtkWidget *ICOmoverIzquierda;
    GtkWidget *ICOempujarArriba;
    GtkWidget *ICOempujarAbajo;
    GtkWidget *ICOempujarDerecha;
    GtkWidget *ICOempujarIzquierda;
    GtkWidget *ICOestirarArriba;
    GtkWidget *ICOestirarAbajo;
    GtkWidget *ICOestirarDerecha;
    GtkWidget *ICOestirarIzquierda;
    GtkWidget *ICOcancelar;

};

struct Juego { //Guarda todos los objetos de cada pieza, el objeto pieza en sí mismo, su imagen, su menú, el peso de cada pieza y sus movimientos. (Se anida con la estrucutra de Movimientos)
    GtkWidget *Pieza;
    int Peso;
    GtkWidget *Imagen;
    GtkWidget *Menu;
    struct Movimientos movimiento;
} elefanteJ1, elefanteJ2, camelloJ1, camelloJ2, caballo1J1, caballo1J2, caballo2J1, caballo2J2, perro1J1, perro1J2, perro2J1, perro2J2, gato1J1, gato1J2, gato2J1, gato2J2, conejo1J1, conejo1J2, conejo2J1, conejo2J2, conejo3J1, conejo3J2, conejo4J1, conejo4J2, conejo5J1, conejo5J2, conejo6J1, conejo6J2,conejo7J1, conejo7J2,conejo8J1, conejo8J2;
/// ///////////////////////////// FIN DECLARACIÓN DE ESTRUCTURAS DE DATOS UTILIZADAS /////////////////////////////////////////////////////////////////////////////////////////

/// /////////////////////////////////// INICIO FUNCIÓN PRINCIPAL MAIN /////////////////////////////////////////////////////////////////////////////////////////////////////////////
 int main(int argc, char *argv[]){


    srand(time(NULL)); //Se inicializan numeros aleatorios
    system("color 1F"); //Da color a la consola
    gtk_init(&argc, &argv); //Se inicializa la librería
    GtkSettings *default_settings = gtk_settings_get_default(); //Configuración de la libraría
    g_object_set(default_settings, "gtk-button-images", TRUE, NULL); //Configuración de la libraría
    builder = gtk_builder_new(); //Se construye al constructor
    gtk_builder_add_from_file(builder, "ArimaaFtGLD.glade", NULL);



    FNcargaCoordenadasTablero(); //Se cargan las coordenadas X e Y del layout del tablero, en una matriz con posiciones analogas a la matriz que guarda las piezas.

    FNconfigFormJuego(); //Se configura todo lo que tenga que ver con la interfaz vistosa de la pantalla pricipal de juego, esta pantalla se nombro formJuego


    FNcrearPiezas(); //Se crean las piezas

    FNcrearTurnos(); //Se crean los turnos de los jugadores.

    FNconfigMovimientoPiezas(); //Se configura el movimiento de las piezas

    FNimprimirMatrices(); //Se imprime en consola las matrices con que se trabajan, para el control de los datos de los movimientos.


    gtk_widget_show_all(formJuego.Pantalla); //Se muestra todo lo que hay en pantalla.
    gtk_main(); //Definición del loop del programa principal main.

    return 0;
 }
/// /////////////////////////////////// FIN FUNCION PRINCIPAL MAIN /////////////////////////////////////////////////////////////////////////////////////////////////////////////


/// A PARTIR DE ESTA LINEA COMIENZA EL DESARROLLO DE LAS FUNCIONES ///


///CONFIGURACION DE LA PANTALLA DE JUEGO, DIALOGOS DE ADVERTENCIAS, ARREGLOS PARA EL CONTROL EN TERMINAL E IMPRESION EN TERMINAL.
void FNconfigFormJuego(){ //Configura la pantalla de juego

    //Creación de la pantalla de juego
    formJuego.Pantalla = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(formJuego.Pantalla), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(formJuego.Pantalla), 1324,900);
  //  gtk_window_set_resizable(GTK_WINDOW(formJuego.Pantalla), FALSE);
    gtk_window_set_title(GTK_WINDOW(formJuego.Pantalla), "Fonda Team");
    gtk_container_set_border_width(GTK_CONTAINER(formJuego.Pantalla), 5);
    gtk_window_set_icon_from_file(GTK_WINDOW(formJuego.Pantalla), "ArimaaF.png", NULL);

    //Creación del tablero
    tablero.Fondo = gtk_image_new_from_file("tableroFinal.png");
    decorado.Fondo = gtk_image_new_from_file("fondoLayout.png");
    formJuego.Layout = gtk_layout_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(formJuego.Pantalla), formJuego.Layout);
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), tablero.Fondo, 0, 0);
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), decorado.Fondo, 900, 0);

    //Llamada a funcion para la creación de los menús de la pantalla de juego
    FNcrearMenusFormJuego();

    gtk_widget_show_all(formJuego.Layout); //Se muestra todo lo que hay en dicha pantalla.
 }

void FNcrearMenusFormJuego(){ //Crea los menús de opciones dentro de la pantalla de juego

    //Creacion del boton para entrar a la pantalla de ranking de jugadores ((PANTALLA EN PROCESO DE DESARROLLO PARA LA 2DA ENTREGA)
    ranking.Boton = gtk_button_new_with_label(NULL);
    ranking.Icono = gtk_image_new_from_file("ranking.png");
    gtk_button_set_always_show_image(GTK_BUTTON(ranking.Boton), TRUE);
    gtk_button_set_image(GTK_BUTTON(ranking.Boton), ranking.Icono);
    gtk_button_set_relief(GTK_BUTTON(ranking.Boton), GTK_RELIEF_NONE);
    gtk_layout_put(GTK_LAYOUT(formJuego.Layout), ranking.Boton, 1199,130);
    g_signal_connect_swapped(G_OBJECT(ranking.Boton), "button-press-event", G_CALLBACK(gtk_main_quit),NULL);

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
    g_signal_connect_swapped(G_OBJECT(ajustes.Boton), "button-press-event", G_CALLBACK(gtk_main_quit),NULL);

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
    g_signal_connect(G_OBJECT(jugar.Boton), "clicked", G_CALLBACK(FNrandomizarPiezas), NULL);

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
    g_signal_connect_swapped(G_OBJECT(movimientoAleatorio.Boton), "button-press-event", G_CALLBACK(FNmovimientoAleatorio), NULL);

}
void FNmostrarPantallaCreditos(){
    GtkWidget *dialog;
    GdkPixbuf *logo;
    GError *error=NULL;
    const gchar *authors[]={
        "Mauricio Samudio",
        "R.I.P. Tobias Nill",
        NULL
    };
    const gchar *documenters[]={
        "Mauricio Samudio",NULL
    };

    dialog= gtk_about_dialog_new();
    logo=gdk_pixbuf_new_from_file("ArimaaF.png",&error);
        if(error==NULL){
        gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), logo);
    }
    gtk_window_set_icon_from_file(GTK_WINDOW(dialog), "ArimaaF.png", NULL);
    gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), "ARIMAAA BY FONDA_TEAM");
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), "V. 0.1");
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog),"(C) 2020 FONDDA_TEAM");

    gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(dialog), authors);
    gtk_about_dialog_set_documenters(GTK_ABOUT_DIALOG(dialog), documenters);

    gtk_dialog_run(GTK_DIALOG(dialog));

    gtk_widget_destroy(dialog);


}
void FNmostrarPantallaAyuda(){

    formAyuda.Pantalla = GTK_WIDGET(gtk_builder_get_object(builder,"FormAyudaGLD"));
    gtk_widget_show_all(formAyuda.Pantalla);

}

void FNcargaCoordenadasTablero(){ //Carga las coordenadas X e Y del layout en una matriz para manejar la colocación gráfica de las piezas
    /*int i,j,Xactual,Yactual;
    int Xinicial=10,Yinicial=10,Xdif=113,Ydif=113;

    Xactual=Xinicial;

    for(i=0;i<8;i++){
        Xactual=Xinicial;
        for(j=0;j<8;j++){
            coordenadasTableroX[i][j]=Xactual;
            coordenadasTableroY[i][j]=Yactual;
            Xactual=Xactual+Xdif;
        }
        Yinicial+=Ydif;
    }*/

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


//    //Fila 0 del tablero
//    coordenadasTableroX[0][0] = 10;
//    coordenadasTableroY[0][0] = 10;
//
//    coordenadasTableroX[0][1] = 122;
//    coordenadasTableroY[0][1] = 10;
//
//    coordenadasTableroX[0][2] = 235;
//    coordenadasTableroY[0][2] = 10;
//
//    coordenadasTableroX[0][3] = 348;
//    coordenadasTableroY[0][3] = 10;
//
//    coordenadasTableroX[0][4] = 460;
//    coordenadasTableroY[0][4] = 10;
//
//    coordenadasTableroX[0][5] = 572;
//    coordenadasTableroY[0][5] = 10;
//
//    coordenadasTableroX[0][6] = 683;
//    coordenadasTableroY[0][6] = 10;
//
//    coordenadasTableroX[0][7] = 793;
//    coordenadasTableroY[0][7] = 10;
//
//    //Fila 1 del tablero
//    coordenadasTableroX[1][0] = 10;
//    coordenadasTableroY[1][0] = 123;
//
//    coordenadasTableroX[1][1] = 122;
//    coordenadasTableroY[1][1] = 123;
//
//    coordenadasTableroX[1][2] = 235;
//    coordenadasTableroY[1][2] = 123;
//
//    coordenadasTableroX[1][3] = 348;
//    coordenadasTableroY[1][3] = 123;
//
//    coordenadasTableroX[1][4] = 460;
//    coordenadasTableroY[1][4] = 123;
//
//    coordenadasTableroX[1][5] = 572;
//    coordenadasTableroY[1][5] = 123;
//
//    coordenadasTableroX[1][6] = 683;
//    coordenadasTableroY[1][6] = 123;
//
//    coordenadasTableroX[1][7] = 793;
//    coordenadasTableroY[1][7] = 123;
//
//    //Fila 2 del tablero
//    coordenadasTableroX[2][0] = 10;
//    coordenadasTableroY[2][0] = 234;
//
//    coordenadasTableroX[2][1] = 122;
//    coordenadasTableroY[2][1] = 234;
//
//    coordenadasTableroX[2][2] = 235;
//    coordenadasTableroY[2][2] = 234;
//
//    coordenadasTableroX[2][3] = 348;
//    coordenadasTableroY[2][3] = 234;
//
//    coordenadasTableroX[2][4] = 460;
//    coordenadasTableroY[2][4] = 234;
//
//    coordenadasTableroX[2][5] = 572;
//    coordenadasTableroY[2][5] = 234;
//
//    coordenadasTableroX[2][6] = 683;
//    coordenadasTableroY[2][6] = 234;
//
//    coordenadasTableroX[2][7] = 793;
//    coordenadasTableroY[2][7] = 234;
//
//    //Fila 3 del tablero
//    coordenadasTableroX[3][0] = 10;
//    coordenadasTableroY[3][0] = 345;
//
//    coordenadasTableroX[3][1] = 122;
//    coordenadasTableroY[3][1] = 345;
//
//    coordenadasTableroX[3][2] = 235;
//    coordenadasTableroY[3][2] = 345;
//
//    coordenadasTableroX[3][3] = 348;
//    coordenadasTableroY[3][3] = 345;
//
//    coordenadasTableroX[3][4] = 460;
//    coordenadasTableroY[3][4] = 345;
//
//    coordenadasTableroX[3][5] = 572;
//    coordenadasTableroY[3][5] = 345;
//
//    coordenadasTableroX[3][6] = 683;
//    coordenadasTableroY[3][6] = 345;
//
//    coordenadasTableroX[3][7] = 793;
//    coordenadasTableroY[3][7] = 345;
//
//    //Fila 4 del tablero
//    coordenadasTableroX[4][0] = 10;
//    coordenadasTableroY[4][0] = 458;
//
//    coordenadasTableroX[4][1] = 122;
//    coordenadasTableroY[4][1] = 458;
//
//    coordenadasTableroX[4][2] = 235;
//    coordenadasTableroY[4][2] = 458;
//
//    coordenadasTableroX[4][3] = 348;
//    coordenadasTableroY[4][3] = 458;
//
//    coordenadasTableroX[4][4] = 460;
//    coordenadasTableroY[4][4] = 458;
//
//    coordenadasTableroX[4][5] = 572;
//    coordenadasTableroY[4][5] = 458;
//
//    coordenadasTableroX[4][6] = 683;
//    coordenadasTableroY[4][6] = 458;
//
//    coordenadasTableroX[4][7] = 793;
//    coordenadasTableroY[4][7] = 458;
//
//    //Fila 5 del tablero
//    coordenadasTableroX[5][0] = 10;
//    coordenadasTableroY[5][0] = 572;
//
//    coordenadasTableroX[5][1] = 122;
//    coordenadasTableroY[5][1] = 572;
//
//    coordenadasTableroX[5][2] = 235;
//    coordenadasTableroY[5][2] = 572;
//
//    coordenadasTableroX[5][3] = 348;
//    coordenadasTableroY[5][3] = 572;
//
//    coordenadasTableroX[5][4] = 460;
//    coordenadasTableroY[5][4] = 572;
//
//    coordenadasTableroX[5][5] = 572;
//    coordenadasTableroY[5][5] = 572;
//
//    coordenadasTableroX[5][6] = 683;
//    coordenadasTableroY[5][6] = 572;
//
//    coordenadasTableroX[5][7] = 793;
//    coordenadasTableroY[5][7] = 572;
//
//    //Fila 6 del tablero
//    coordenadasTableroX[6][0] = 10;
//    coordenadasTableroY[6][0] = 685;
//
//    coordenadasTableroX[6][1] = 122;
//    coordenadasTableroY[6][1] = 685;
//
//    coordenadasTableroX[6][2] = 235;
//    coordenadasTableroY[6][2] = 685;
//
//    coordenadasTableroX[6][3] = 348;
//    coordenadasTableroY[6][3] = 685;
//
//    coordenadasTableroX[6][4] = 460;
//    coordenadasTableroY[6][4] = 685;
//
//    coordenadasTableroX[6][5] = 572;
//    coordenadasTableroY[6][5] = 685;
//
//    coordenadasTableroX[6][6] = 683;
//    coordenadasTableroY[6][6] = 685;
//
//    coordenadasTableroX[6][7] = 793;
//    coordenadasTableroY[6][7] = 685;
//
//    //Fila 7 del tablero
//    coordenadasTableroX[7][0] = 10;
//    coordenadasTableroY[7][0] = 795;
//
//    coordenadasTableroX[7][1] = 122;
//    coordenadasTableroY[7][1] = 795;
//
//    coordenadasTableroX[7][2] = 235;
//    coordenadasTableroY[7][2] = 795;
//
//    coordenadasTableroX[7][3] = 348;
//    coordenadasTableroY[7][3] = 795;
//
//    coordenadasTableroX[7][4] = 460;
//    coordenadasTableroY[7][4] = 795;
//
//    coordenadasTableroX[7][5] = 572;
//    coordenadasTableroY[7][5] = 795;
//
//    coordenadasTableroX[7][6] = 683;
//    coordenadasTableroY[7][6] = 795;
//
//    coordenadasTableroX[7][7] = 793;
//    coordenadasTableroY[7][7] = 795;

}

void FNimprimirMatrices(){ //Imprime todas las matrices con que se trabajan en la consola, y se actualiza con cada movimiento de juego
    //system("cls");
    printf("\n");

    for(int p = 0; p < 8; p++){
        for(int q = 0; q < 8; q++){
            if(posicionPiezas[p][q] == 0){
                printf("00|", posicionPiezas[p][q]);
            }
            else{
                printf("    ",posicionPiezas[p][q]);
            }
        }
        printf("   \n");
    }

    printf("\n");

    for(int p = 0; p < 8; p++){
        for(int q = 0; q < 8; q++){
            if(posicionPiezas[p][q] == 0){
                printf("00|", queJugador[p][q]);
            }
            else{
                printf("    ", queJugador[p][q]);
            }
        }
        printf("   \n");
    }

    printf("\n");

        for(int p = 0; p < 8; p++){
            for(int q = 0; q < 8; q++){
                if(pesoPiezas[p][q] == 0){
                    printf("    ", pesoPiezas[p][q]);
                }
                else{
                    printf("    ", pesoPiezas[p][q]);
                }
        }
        printf("    \n");
    }

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


    g_signal_connect(G_OBJECT(Jugador1.TurnoToggle), "toggled", G_CALLBACK(manejadorTurnoJ1), (gpointer) Jugador2.TurnoToggle);
    g_signal_connect(G_OBJECT(Jugador2.TurnoToggle), "toggled", G_CALLBACK(manejadorTurnoJ2), (gpointer) Jugador1.TurnoToggle);

}

void manejadorTurnoJ1(GtkToggleButton *turno){ //Maneja el turno del Jugador 1 cuando se presiona el boton de tipo ToggleButton, dicho botón tiene dos estados (Presionado y No presionado)
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(Jugador1.TurnoToggle))){ //Si el estado del boton esta activo
        printf("\n TURNO J1 ACTIVO");
        habilitarOPmovimientosJ1(); //Se habilitan las opciones de movimiento para el J1
        habilitarOPempujarOestirarJ2(); //Se habilitan las opciones de empuje o estire del J2, las cuales el J1 puede manejar
        gtk_widget_set_sensitive(GTK_WIDGET(Jugador2.TurnoToggle), FALSE); //Se desactiva el boton toggle de turno del J2
    }
    else{ //Sino, cuando el boton toggle se desactiva, todo lo mencionado en las sentencias de arriba, se revierten.
        printf("\n TURNO J1 INACTIVO");
        Jugador1.TurnoContador = 0;
        gtk_label_set_text(GTK_LABEL(Jugador1.TurnoCantidadMovimientos), "0");
        deshabilitarOPmovimientosJ1();
        deshabilitarOPempujarOestirarJ2();
        gtk_widget_set_sensitive(GTK_WIDGET(Jugador2.TurnoToggle), TRUE);
    }
}

void manejadorTurnoJ2(GtkToggleButton *turno){ //Maneja el turno del Jugador 2 cuando se presiona el boton de tipo ToggleButton, dicho botón tiene dos estados (Presionado y No presionado)
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(Jugador2.TurnoToggle))){ //Si el estado del boton esta activo
        printf("\n TURNO J2 ACTIVO");
        habilitarOPmovimientosJ2(); //Se habilitan las opciones de movimiento para el J2
        habilitarOPempujarOestirarJ1(); //Se habilitan las opciones de empuje o estire del J1, las cuales el J2 puede manejar
        gtk_widget_set_sensitive(GTK_WIDGET(Jugador1.TurnoToggle), FALSE); //Se desactiva el boton toggle de turno del J1
    }
    else{ //Sino, cuando el boton toggle se desactiva, todo lo mencionado en las sentencias de arriba, se revierten.
        printf("\n TURNO J2 INACTIVO");
        Jugador2.TurnoContador = 0;
        gtk_label_set_text(GTK_LABEL(Jugador2.TurnoCantidadMovimientos), "0");
        deshabilitarOPmovimientosJ2();
        deshabilitarOPempujarOestirarJ1();
        gtk_widget_set_sensitive(GTK_WIDGET(Jugador1.TurnoToggle), TRUE);
    }
}


//CREACION, CONFIGURACION, COLOCACION E INICIALIZACION DE PIEZAS
void FNcrearPiezas(){ //Crea las piezas
    //Piezas del jugador 1
    elefanteJ1.Peso = 6;
    elefanteJ1.Pieza = gtk_button_new_with_label(NULL);
    elefanteJ1.Imagen = gtk_image_new_from_file("elefanteBlanco.png");
    gtk_button_set_always_show_image(GTK_BUTTON(elefanteJ1.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(elefanteJ1.Pieza), elefanteJ1.Imagen);
    gtk_button_set_relief(GTK_BUTTON(elefanteJ1.Pieza), GTK_RELIEF_NONE);

    camelloJ1.Peso = 5;
    camelloJ1.Pieza = gtk_button_new_with_label(NULL);
    camelloJ1.Imagen = gtk_image_new_from_file("camelloBlanco.png");
    gtk_button_set_always_show_image(GTK_BUTTON(camelloJ1.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(camelloJ1.Pieza), camelloJ1.Imagen);
    gtk_button_set_relief(GTK_BUTTON(camelloJ1.Pieza), GTK_RELIEF_NONE);

    caballo1J1.Peso = 4;
    caballo1J1.Pieza = gtk_button_new_with_label(NULL);
    caballo1J1.Imagen = gtk_image_new_from_file("caballoBlanco.png");
    gtk_button_set_always_show_image(GTK_BUTTON(caballo1J1.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(caballo1J1.Pieza), caballo1J1.Imagen);
    gtk_button_set_relief(GTK_BUTTON(caballo1J1.Pieza), GTK_RELIEF_NONE);

    caballo2J1.Peso = 4;
    caballo2J1.Pieza = gtk_button_new_with_label(NULL);
    caballo2J1.Imagen = gtk_image_new_from_file("caballoBlanco.png");
    gtk_button_set_always_show_image(GTK_BUTTON(caballo2J1.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(caballo2J1.Pieza), caballo2J1.Imagen);
    gtk_button_set_relief(GTK_BUTTON(caballo2J1.Pieza), GTK_RELIEF_NONE);

    perro1J1.Peso = 3;
    perro1J1.Pieza = gtk_button_new_with_label(NULL);
    perro1J1.Imagen = gtk_image_new_from_file("perroBlanco.png");
    gtk_button_set_always_show_image(GTK_BUTTON(perro1J1.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(perro1J1.Pieza), perro1J1.Imagen);
    gtk_button_set_relief(GTK_BUTTON(perro1J1.Pieza), GTK_RELIEF_NONE);

    perro2J1.Peso = 3;
    perro2J1.Pieza = gtk_button_new_with_label(NULL);
    perro2J1.Imagen = gtk_image_new_from_file("perroBlanco.png");
    gtk_button_set_always_show_image(GTK_BUTTON(perro2J1.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(perro2J1.Pieza), perro2J1.Imagen);
    gtk_button_set_relief(GTK_BUTTON(perro2J1.Pieza), GTK_RELIEF_NONE);

    gato1J1.Peso = 2;
    gato1J1.Pieza = gtk_button_new_with_label(NULL);
    gato1J1.Imagen = gtk_image_new_from_file("gatoBlanco.png");
    gtk_button_set_always_show_image(GTK_BUTTON(gato1J1.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(gato1J1.Pieza), gato1J1.Imagen);
    gtk_button_set_relief(GTK_BUTTON(gato1J1.Pieza), GTK_RELIEF_NONE);

    gato2J1.Peso = 2;
    gato2J1.Pieza = gtk_button_new_with_label(NULL);
    gato2J1.Imagen = gtk_image_new_from_file("gatoBlanco.png");
    gtk_button_set_always_show_image(GTK_BUTTON(gato2J1.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(gato2J1.Pieza), gato2J1.Imagen);
    gtk_button_set_relief(GTK_BUTTON(gato2J1.Pieza), GTK_RELIEF_NONE);

    conejo1J1.Peso = 1;
    conejo1J1.Pieza = gtk_button_new_with_label(NULL);
    conejo1J1.Imagen = gtk_image_new_from_file("conejoBlanco.png");
    gtk_button_set_always_show_image(GTK_BUTTON(conejo1J1.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(conejo1J1.Pieza), conejo1J1.Imagen);
    gtk_button_set_relief(GTK_BUTTON(conejo1J1.Pieza), GTK_RELIEF_NONE);

    conejo2J1.Peso = 1;
    conejo2J1.Pieza = gtk_button_new_with_label(NULL);
    conejo2J1.Imagen = gtk_image_new_from_file("conejoBlanco.png");
    gtk_button_set_always_show_image(GTK_BUTTON(conejo2J1.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(conejo2J1.Pieza), conejo2J1.Imagen);
    gtk_button_set_relief(GTK_BUTTON(conejo2J1.Pieza), GTK_RELIEF_NONE);

    conejo3J1.Peso = 1;
    conejo3J1.Pieza = gtk_button_new_with_label(NULL);
    conejo3J1.Imagen = gtk_image_new_from_file("conejoBlanco.png");
    gtk_button_set_always_show_image(GTK_BUTTON(conejo3J1.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(conejo3J1.Pieza), conejo3J1.Imagen);
    gtk_button_set_relief(GTK_BUTTON(conejo3J1.Pieza), GTK_RELIEF_NONE);

    conejo4J1.Peso = 1;
    conejo4J1.Pieza = gtk_button_new_with_label(NULL);
    conejo4J1.Imagen = gtk_image_new_from_file("conejoBlanco.png");
    gtk_button_set_always_show_image(GTK_BUTTON(conejo4J1.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(conejo4J1.Pieza), conejo4J1.Imagen);
    gtk_button_set_relief(GTK_BUTTON(conejo4J1.Pieza), GTK_RELIEF_NONE);

    conejo5J1.Peso = 1;
    conejo5J1.Pieza = gtk_button_new_with_label(NULL);
    conejo5J1.Imagen = gtk_image_new_from_file("conejoBlanco.png");
    gtk_button_set_always_show_image(GTK_BUTTON(conejo5J1.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(conejo5J1.Pieza), conejo5J1.Imagen);
    gtk_button_set_relief(GTK_BUTTON(conejo5J1.Pieza), GTK_RELIEF_NONE);

    conejo6J1.Peso = 1;
    conejo6J1.Pieza = gtk_button_new_with_label(NULL);
    conejo6J1.Imagen = gtk_image_new_from_file("conejoBlanco.png");
    gtk_button_set_always_show_image(GTK_BUTTON(conejo6J1.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(conejo6J1.Pieza), conejo6J1.Imagen);
    gtk_button_set_relief(GTK_BUTTON(conejo6J1.Pieza), GTK_RELIEF_NONE);

    conejo7J1.Peso = 1;
    conejo7J1.Pieza = gtk_button_new_with_label(NULL);
    conejo7J1.Imagen = gtk_image_new_from_file("conejoBlanco.png");
    gtk_button_set_always_show_image(GTK_BUTTON(conejo7J1.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(conejo7J1.Pieza), conejo7J1.Imagen);
    gtk_button_set_relief(GTK_BUTTON(conejo7J1.Pieza), GTK_RELIEF_NONE);

    conejo8J1.Peso = 1;
    conejo8J1.Pieza = gtk_button_new_with_label(NULL);
    conejo8J1.Imagen = gtk_image_new_from_file("conejoBlanco.png");
    gtk_button_set_always_show_image(GTK_BUTTON(conejo8J1.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(conejo8J1.Pieza), conejo8J1.Imagen);
    gtk_button_set_relief(GTK_BUTTON(conejo8J1.Pieza), GTK_RELIEF_NONE);

    //Piezas del jugador 2
    elefanteJ2.Peso = 6;
    elefanteJ2.Pieza = gtk_button_new_with_label(NULL);
    elefanteJ2.Imagen = gtk_image_new_from_file("elefanteDorado.png");
    gtk_button_set_always_show_image(GTK_BUTTON(elefanteJ2.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(elefanteJ2.Pieza), elefanteJ2.Imagen);
    gtk_button_set_relief(GTK_BUTTON(elefanteJ2.Pieza), GTK_RELIEF_NONE);

    camelloJ2.Peso = 5;
    camelloJ2.Pieza = gtk_button_new_with_label(NULL);
    camelloJ2.Imagen = gtk_image_new_from_file("camelloDorado.png");
    gtk_button_set_always_show_image(GTK_BUTTON(camelloJ2.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(camelloJ2.Pieza), camelloJ2.Imagen);
    gtk_button_set_relief(GTK_BUTTON(camelloJ2.Pieza), GTK_RELIEF_NONE);

    caballo1J2.Peso = 4;
    caballo1J2.Pieza = gtk_button_new_with_label(NULL);
    caballo1J2.Imagen = gtk_image_new_from_file("caballoDorado.png");
    gtk_button_set_always_show_image(GTK_BUTTON(caballo1J2.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(caballo1J2.Pieza), caballo1J2.Imagen);
    gtk_button_set_relief(GTK_BUTTON(caballo1J2.Pieza), GTK_RELIEF_NONE);

    caballo2J2.Peso = 4;
    caballo2J2.Pieza = gtk_button_new_with_label(NULL);
    caballo2J2.Imagen = gtk_image_new_from_file("caballoDorado.png");
    gtk_button_set_always_show_image(GTK_BUTTON(caballo2J2.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(caballo2J2.Pieza), caballo2J2.Imagen);
    gtk_button_set_relief(GTK_BUTTON(caballo2J2.Pieza), GTK_RELIEF_NONE);

    perro1J2.Peso = 3;
    perro1J2.Pieza = gtk_button_new_with_label(NULL);
    perro1J2.Imagen = gtk_image_new_from_file("perroDorado.png");
    gtk_button_set_always_show_image(GTK_BUTTON(perro1J2.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(perro1J2.Pieza), perro1J2.Imagen);
    gtk_button_set_relief(GTK_BUTTON(perro1J2.Pieza), GTK_RELIEF_NONE);

    perro2J2.Peso = 3;
    perro2J2.Pieza = gtk_button_new_with_label(NULL);
    perro2J2.Imagen = gtk_image_new_from_file("perroDorado.png");
    gtk_button_set_always_show_image(GTK_BUTTON(perro2J2.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(perro2J2.Pieza), perro2J2.Imagen);
    gtk_button_set_relief(GTK_BUTTON(perro2J2.Pieza), GTK_RELIEF_NONE);

    gato1J2.Peso = 2;
    gato1J2.Pieza = gtk_button_new_with_label(NULL);
    gato1J2.Imagen = gtk_image_new_from_file("gatoDorado.png");
    gtk_button_set_always_show_image(GTK_BUTTON(gato1J2.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(gato1J2.Pieza), gato1J2.Imagen);
    gtk_button_set_relief(GTK_BUTTON(gato1J2.Pieza), GTK_RELIEF_NONE);

    gato2J2.Peso = 2;
    gato2J2.Pieza = gtk_button_new_with_label(NULL);
    gato2J2.Imagen = gtk_image_new_from_file("gatoDorado.png");
    gtk_button_set_always_show_image(GTK_BUTTON(gato2J2.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(gato2J2.Pieza), gato2J2.Imagen);
    gtk_button_set_relief(GTK_BUTTON(gato2J2.Pieza), GTK_RELIEF_NONE);

    conejo1J2.Peso = 1;
    conejo1J2.Pieza = gtk_button_new_with_label(NULL);
    conejo1J2.Imagen = gtk_image_new_from_file("conejoDorado.png");
    gtk_button_set_always_show_image(GTK_BUTTON(conejo1J2.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(conejo1J2.Pieza), conejo1J2.Imagen);
    gtk_button_set_relief(GTK_BUTTON(conejo1J2.Pieza), GTK_RELIEF_NONE);

    conejo2J2.Peso = 1;
    conejo2J2.Pieza = gtk_button_new_with_label(NULL);
    conejo2J2.Imagen = gtk_image_new_from_file("conejoDorado.png");
    gtk_button_set_always_show_image(GTK_BUTTON(conejo2J2.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(conejo2J2.Pieza), conejo2J2.Imagen);
    gtk_button_set_relief(GTK_BUTTON(conejo2J2.Pieza), GTK_RELIEF_NONE);

    conejo3J2.Peso = 1;
    conejo3J2.Pieza = gtk_button_new_with_label(NULL);
    conejo3J2.Imagen = gtk_image_new_from_file("conejoDorado.png");
    gtk_button_set_always_show_image(GTK_BUTTON(conejo3J2.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(conejo3J2.Pieza), conejo3J2.Imagen);
    gtk_button_set_relief(GTK_BUTTON(conejo3J2.Pieza), GTK_RELIEF_NONE);

    conejo4J2.Peso = 1;
    conejo4J2.Pieza = gtk_button_new_with_label(NULL);
    conejo4J2.Imagen = gtk_image_new_from_file("conejoDorado.png");
    gtk_button_set_always_show_image(GTK_BUTTON(conejo4J2.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(conejo4J2.Pieza), conejo4J2.Imagen);
    gtk_button_set_relief(GTK_BUTTON(conejo4J2.Pieza), GTK_RELIEF_NONE);

    conejo5J2.Peso = 1;
    conejo5J2.Pieza = gtk_button_new_with_label(NULL);
    conejo5J2.Imagen = gtk_image_new_from_file("conejoDorado.png");
    gtk_button_set_always_show_image(GTK_BUTTON(conejo5J2.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(conejo5J2.Pieza), conejo5J2.Imagen);
    gtk_button_set_relief(GTK_BUTTON(conejo5J2.Pieza), GTK_RELIEF_NONE);

    conejo6J2.Peso = 1;
    conejo6J2.Pieza = gtk_button_new_with_label(NULL);
    conejo6J2.Imagen = gtk_image_new_from_file("conejoDorado.png");
    gtk_button_set_always_show_image(GTK_BUTTON(conejo6J2.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(conejo6J2.Pieza), conejo6J2.Imagen);
    gtk_button_set_relief(GTK_BUTTON(conejo6J2.Pieza), GTK_RELIEF_NONE);

    conejo7J2.Peso = 1;
    conejo7J2.Pieza = gtk_button_new_with_label(NULL);
    conejo7J2.Imagen = gtk_image_new_from_file("conejoDorado.png");
    gtk_button_set_always_show_image(GTK_BUTTON(conejo7J2.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(conejo7J2.Pieza), conejo7J2.Imagen);
    gtk_button_set_relief(GTK_BUTTON(conejo7J2.Pieza), GTK_RELIEF_NONE);

    conejo8J2.Peso = 1;
    conejo8J2.Pieza = gtk_button_new_with_label(NULL);
    conejo8J2.Imagen = gtk_image_new_from_file("conejoDorado.png");
    gtk_button_set_always_show_image(GTK_BUTTON(conejo8J2.Pieza), TRUE);
    gtk_button_set_image(GTK_BUTTON(conejo8J2.Pieza), conejo8J2.Imagen);
    gtk_button_set_relief(GTK_BUTTON(conejo8J2.Pieza), GTK_RELIEF_NONE);

    FNdimensionarPiezas(); //llama a la funcion que dimensiona el tamano de las piezas

    /// Se cargan dos arreglos piezasJ1 y piezasJ2 con las constantes que representan cada pieza
    //Piezas J1
    piezasJ1[0] = ELEFANTEJ1;
    piezasJ1[1] = CAMELLOJ1;
    piezasJ1[2] = CABALLO1J1;
    piezasJ1[3] = CABALLO2J1;
    piezasJ1[4] = PERRO1J1;
    piezasJ1[5] = PERRO2J1;
    piezasJ1[6] = GATO1J1;
    piezasJ1[7] = GATO2J1;
    piezasJ1[8] = CONEJO1J1;
    piezasJ1[9] = CONEJO2J1;
    piezasJ1[10] = CONEJO3J1;
    piezasJ1[11] = CONEJO4J1;
    piezasJ1[12] = CONEJO5J1;
    piezasJ1[13] = CONEJO6J1;
    piezasJ1[14] = CONEJO7J1;
    piezasJ1[15] = CONEJO8J1;
    //Piezas J2
    piezasJ2[0] = ELEFANTEJ2;
    piezasJ2[1] = CAMELLOJ2;
    piezasJ2[2] = CABALLO1J2;
    piezasJ2[3] = CABALLO2J2;
    piezasJ2[4] = PERRO1J2;
    piezasJ2[5] = PERRO2J2;
    piezasJ2[6] = GATO1J2;
    piezasJ2[7] = GATO2J2;
    piezasJ2[8] = CONEJO1J2;
    piezasJ2[9] = CONEJO2J2;
    piezasJ2[10] = CONEJO3J2;
    piezasJ2[11] = CONEJO4J2;
    piezasJ2[12] = CONEJO5J2;
    piezasJ2[13] = CONEJO6J2;
    piezasJ2[14] = CONEJO7J2;
    piezasJ2[15] = CONEJO8J2;
 }

void FNdimensionarPiezas(){ //Dimensiona el tamaño de las piezas
    //Se da tamano a las piezas del jugador 1
    gtk_widget_set_size_request(elefanteJ1.Pieza, 80,80);
    gtk_widget_set_size_request(camelloJ1.Pieza, 80,80);
    gtk_widget_set_size_request(caballo1J1.Pieza, 80,80);
    gtk_widget_set_size_request(caballo2J1.Pieza, 80,80);
    gtk_widget_set_size_request(perro1J1.Pieza, 80,80);
    gtk_widget_set_size_request(perro2J1.Pieza, 80,80);
    gtk_widget_set_size_request(gato1J1.Pieza, 80,80);
    gtk_widget_set_size_request(gato2J1.Pieza, 80,80);
    gtk_widget_set_size_request(conejo1J1.Pieza, 80,80);
    gtk_widget_set_size_request(conejo2J1.Pieza, 80,80);
    gtk_widget_set_size_request(conejo3J1.Pieza, 80,80);
    gtk_widget_set_size_request(conejo4J1.Pieza, 80,80);
    gtk_widget_set_size_request(conejo5J1.Pieza, 80,80);
    gtk_widget_set_size_request(conejo6J1.Pieza, 80,80);
    gtk_widget_set_size_request(conejo7J1.Pieza, 80,80);
    gtk_widget_set_size_request(conejo8J1.Pieza, 80,80);
    //Se da tamano a las piezas del jugador 2
    gtk_widget_set_size_request(elefanteJ2.Pieza, 80,80);
    gtk_widget_set_size_request(camelloJ2.Pieza, 80,80);
    gtk_widget_set_size_request(caballo1J2.Pieza, 80,80);
    gtk_widget_set_size_request(caballo2J2.Pieza, 80,80);
    gtk_widget_set_size_request(perro1J2.Pieza, 80, 80);
    gtk_widget_set_size_request(perro2J2.Pieza, 80,80);
    gtk_widget_set_size_request(gato1J2.Pieza, 80,80);
    gtk_widget_set_size_request(gato2J2.Pieza, 80,80);
    gtk_widget_set_size_request(conejo1J2.Pieza, 80,80);
    gtk_widget_set_size_request(conejo2J2.Pieza, 80,80);
    gtk_widget_set_size_request(conejo3J2.Pieza, 80,80);
    gtk_widget_set_size_request(conejo4J2.Pieza, 80,80);
    gtk_widget_set_size_request(conejo5J2.Pieza, 80,80);
    gtk_widget_set_size_request(conejo6J2.Pieza, 80,80);
    gtk_widget_set_size_request(conejo7J2.Pieza, 80,80);
    gtk_widget_set_size_request(conejo8J2.Pieza, 80,80);
}

void FNrandomizarPiezas(){ //(EN PRUEBA) vuelve a ranzomizar las piezas ya ubicadas en el tablero
    FNiniciarPiezasJ1();
    FNiniciarPiezasJ2();
}

static void FNiniciarPiezasJ1(){ //Inicializa aleatoriamente las piezas del Jugador 1
        fila = 0; columna = 0;
        for(i = limiteInferior; i <= limiteSuperior; i++){
            randomPos = limiteInferior + rand()%(limiteSuperior+1 - limiteInferior);
            piezaRandom = piezasJ1[randomPos];
            if(piezasJ1[randomPos] == 0){
                do{
                    randomPos = limiteInferior + rand()%(limiteSuperior+1 - limiteInferior);
                    piezaRandom = piezasJ1[randomPos];
                }while(piezasJ1[randomPos] == 0);
            }
            piezasJ1[randomPos] = 0;
            FNcolocarPiezas(piezaRandom, columna, fila);
            columna++;
            if(columna > 7){
                columna = 0;
                fila = 1;
            }
        }
        fflush(stdin);
}

static void FNiniciarPiezasJ2(){ //Inicializa aleatoriamente las piezas del Jugador 2

    fila = 6; columna = 0;
    for(i = limiteInferior; i <= limiteSuperior; i++){
        randomPos = limiteInferior + rand()%(limiteSuperior+1 - limiteInferior);
        piezaRandom = piezasJ2[randomPos];
        if(piezasJ2[randomPos] == 0){
            do{
                randomPos = limiteInferior + rand()%(limiteSuperior+1 - limiteInferior);
                piezaRandom = piezasJ2[randomPos];
            }while(piezasJ2[randomPos] == 0);
        }
        piezasJ2[randomPos] = 0;
        FNcolocarPiezas(piezaRandom, columna, fila);
        columna++;
        if(columna > 7){
            columna = 0;
            fila = 7;
        }
    }
    fflush(stdin);
}

void FNcolocarPiezas(int PiezaAletoria, int Fila, int Columna){ //Cuando se llama a FNiniciarPiezasJ1 y FNiniciarPiezasJ2, esta función recibe una pieza aleatoria y la coloca también en una posición aleatoria del tablero.
    switch(piezaRandom){
        case ELEFANTEJ1:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), elefanteJ1.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = elefanteJ1.Peso;
            queJugador[fila][columna] = J1;
            break;
        case CAMELLOJ1:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), camelloJ1.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = camelloJ1.Peso;
            queJugador[fila][columna] = J1;
            break;
        case CABALLO1J1:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), caballo1J1.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = caballo1J1.Peso;
            queJugador[fila][columna] = J1;
            break;
        case CABALLO2J1:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), caballo2J1.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = caballo2J1.Peso;
            queJugador[fila][columna] = J1;
            break;
        case PERRO1J1:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), perro1J1.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = perro1J1.Peso;
            queJugador[fila][columna] = J1;
            break;
        case PERRO2J1:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), perro2J1.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = perro2J1.Peso;
            queJugador[fila][columna] = J1;
            break;
        case GATO1J1:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), gato1J1.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = gato1J1.Peso;
            queJugador[fila][columna] = J1;
            break;
        case GATO2J1:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), gato2J1.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = gato2J1.Peso;
            queJugador[fila][columna] = J1;
            break;
        case CONEJO1J1:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), conejo1J1.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = conejo1J1.Peso;
            queJugador[fila][columna] = J1;
            break;
        case CONEJO2J1:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), conejo2J1.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = conejo2J1.Peso;
            queJugador[fila][columna] = J1;
            break;
        case CONEJO3J1:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), conejo3J1.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = conejo3J1.Peso;
            queJugador[fila][columna] = J1;
            break;
        case CONEJO4J1:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), conejo4J1.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = conejo4J1.Peso;
            queJugador[fila][columna] = J1;
            break;
        case CONEJO5J1:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), conejo5J1.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = conejo5J1.Peso;
            queJugador[fila][columna] = J1;
            break;
        case CONEJO6J1:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), conejo6J1.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = conejo6J1.Peso;
            queJugador[fila][columna] = J1;
            break;
        case CONEJO7J1:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), conejo7J1.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = conejo7J1.Peso;
            queJugador[fila][columna] = J1;
            break;
        case CONEJO8J1:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), conejo8J1.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = conejo8J1.Peso;
            queJugador[fila][columna] = J1;
            break;
        case ELEFANTEJ2:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), elefanteJ2.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = elefanteJ2.Peso;
            queJugador[fila][columna] = J2;
            break;
        case CAMELLOJ2:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), camelloJ2.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = camelloJ2.Peso;
            queJugador[fila][columna] = J2;
            break;
        case CABALLO1J2:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), caballo1J2.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = caballo1J2.Peso;
            queJugador[fila][columna] = J2;
            break;
        case CABALLO2J2:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), caballo2J2.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = caballo2J2.Peso;
            queJugador[fila][columna] = J2;
            break;
        case PERRO1J2:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), perro1J2.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = perro1J2.Peso;
            queJugador[fila][columna] = J2;
            break;
        case PERRO2J2:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), perro2J2.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = perro2J2.Peso;
            queJugador[fila][columna] = J2;
            break;
        case GATO1J2:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), gato1J2.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = gato1J2.Peso;
            queJugador[fila][columna] = J2;
            break;
        case GATO2J2:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), gato2J2.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = gato2J2.Peso;
            queJugador[fila][columna] = J2;
            break;
        case CONEJO1J2:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), conejo1J2.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = conejo1J2.Peso;
            queJugador[fila][columna] = J2;
            break;
        case CONEJO2J2:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), conejo2J2.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = conejo2J2.Peso;
            queJugador[fila][columna] = J2;
            break;
        case CONEJO3J2:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), conejo3J2.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = conejo3J2.Peso;
            queJugador[fila][columna] = J2;
            break;
        case CONEJO4J2:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), conejo4J2.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = conejo4J2.Peso;
            queJugador[fila][columna] = J2;
            break;
        case CONEJO5J2:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), conejo5J2.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = conejo5J2.Peso;
            queJugador[fila][columna] = J2;
            break;
        case CONEJO6J2:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), conejo6J2.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = conejo6J2.Peso;
            queJugador[fila][columna] = J2;
            break;
        case CONEJO7J2:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), conejo7J2.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = conejo7J2.Peso;
            queJugador[fila][columna] = J2;
            break;
        case CONEJO8J2:
            gtk_layout_put(GTK_LAYOUT(formJuego.Layout), conejo8J2.Pieza, coordenadasTableroX[fila][columna], coordenadasTableroY[fila][columna]);
            pesoPiezas[fila][columna] = conejo8J2.Peso;
            queJugador[fila][columna] = J2;
            break;
        default:
            break;
    }
    posicionPiezas[fila][columna] = piezaRandom;
    gtk_widget_show_all(formJuego.Pantalla);
 }

void FNrecargarPiezas(){ //Recarga las constantes de las piezas en los vectores piezasJ1 y piezasJ2
    /// Se cargan dos arreglos piezasJ1 y piezasJ2 con las constantes que representan cada pieza
    //Piezas J1
    piezasJ1[0] = ELEFANTEJ1;
    piezasJ1[1] = CAMELLOJ1;
    piezasJ1[2] = CABALLO1J1;
    piezasJ1[3] = CABALLO2J1;
    piezasJ1[4] = PERRO1J1;
    piezasJ1[5] = PERRO2J1;
    piezasJ1[6] = GATO1J1;
    piezasJ1[7] = GATO2J1;
    piezasJ1[8] = CONEJO1J1;
    piezasJ1[9] = CONEJO2J1;
    piezasJ1[10] = CONEJO3J1;
    piezasJ1[11] = CONEJO4J1;
    piezasJ1[12] = CONEJO5J1;
    piezasJ1[13] = CONEJO6J1;
    piezasJ1[14] = CONEJO7J1;
    piezasJ1[15] = CONEJO8J1;
    //Piezas J2
    piezasJ2[0] = ELEFANTEJ2;
    piezasJ2[1] = CAMELLOJ2;
    piezasJ2[2] = CABALLO1J2;
    piezasJ2[3] = CABALLO2J2;
    piezasJ2[4] = PERRO1J2;
    piezasJ2[5] = PERRO2J2;
    piezasJ2[6] = GATO1J2;
    piezasJ2[7] = GATO2J2;
    piezasJ2[8] = CONEJO1J2;
    piezasJ2[9] = CONEJO2J2;
    piezasJ2[10] = CONEJO3J2;
    piezasJ2[11] = CONEJO4J2;
    piezasJ2[12] = CONEJO5J2;
    piezasJ2[13] = CONEJO6J2;
    piezasJ2[14] = CONEJO7J2;
    piezasJ2[15] = CONEJO8J2;

}

void FNcrearMenusPiezas(){ //Crea los menús de cada pieza, los cuales se despliegan al hacer distíntos clicks en ellas (MOVER Y EMPUJARESTIRAR)

/// Se crean los SubMenus de cada pieza, y se agregan a sus respectivos menus

//-------------------------------ELEFANTE-------------------------------
//-------------------------------CREANDO------------------------------------
    ///Jugador1
        //Mover
    elefanteJ1.Menu                                 = gtk_menu_new();
    elefanteJ1.movimiento.OPmoverArriba             = gtk_menu_item_new();
    elefanteJ1.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    elefanteJ1.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    elefanteJ1.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    elefanteJ1.movimiento.OPempujarArriba           = gtk_menu_item_new();
    elefanteJ1.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    elefanteJ1.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    elefanteJ1.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    elefanteJ1.movimiento.OPestirarArriba           = gtk_menu_item_new();
    elefanteJ1.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    elefanteJ1.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    elefanteJ1.movimiento.OPestirarAbajo            = gtk_menu_item_new();

    elefanteJ1.movimiento.OPcancelar                = gtk_menu_item_new();
    ///Jugador 2
        //Mover
    elefanteJ2.Menu                                 = gtk_menu_new();
    elefanteJ2.movimiento.OPmoverArriba             = gtk_menu_item_new();
    elefanteJ2.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    elefanteJ2.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    elefanteJ2.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    elefanteJ2.movimiento.OPempujarArriba           = gtk_menu_item_new();
    elefanteJ2.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    elefanteJ2.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    elefanteJ2.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    elefanteJ2.movimiento.OPestirarArriba           = gtk_menu_item_new();
    elefanteJ2.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    elefanteJ2.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    elefanteJ2.movimiento.OPestirarAbajo            = gtk_menu_item_new();

    elefanteJ2.movimiento.OPcancelar                = gtk_menu_item_new();
//-------------------------------AGREGANDO-------------------------------
    ///Jugador1
        //Mover
    gtk_menu_shell_append(GTK_MENU_SHELL(elefanteJ1.Menu), elefanteJ1.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(elefanteJ1.Menu), elefanteJ1.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(elefanteJ1.Menu), elefanteJ1.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(elefanteJ1.Menu), elefanteJ1.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(elefanteJ1.Menu), elefanteJ1.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(elefanteJ1.Menu), elefanteJ1.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(elefanteJ1.Menu), elefanteJ1.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(elefanteJ1.Menu), elefanteJ1.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(elefanteJ1.Menu), elefanteJ1.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(elefanteJ1.Menu), elefanteJ1.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(elefanteJ1.Menu), elefanteJ1.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(elefanteJ1.Menu), elefanteJ1.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(elefanteJ1.Menu), elefanteJ1.movimiento.OPcancelar);
    ///Jugador 2
    gtk_menu_shell_append(GTK_MENU_SHELL(elefanteJ2.Menu), elefanteJ2.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(elefanteJ2.Menu), elefanteJ2.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(elefanteJ2.Menu), elefanteJ2.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(elefanteJ2.Menu), elefanteJ2.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(elefanteJ2.Menu), elefanteJ2.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(elefanteJ2.Menu), elefanteJ2.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(elefanteJ2.Menu), elefanteJ2.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(elefanteJ2.Menu), elefanteJ2.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(elefanteJ2.Menu), elefanteJ2.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(elefanteJ2.Menu), elefanteJ2.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(elefanteJ2.Menu), elefanteJ2.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(elefanteJ2.Menu), elefanteJ2.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(elefanteJ2.Menu), elefanteJ2.movimiento.OPcancelar);

//-------------------------------CAMELLO-------------------------------
//-------------------------------CREANDO-------------------------------
    ///Jugador 1
        //Mover
    camelloJ1.Menu                                 = gtk_menu_new();
    camelloJ1.movimiento.OPmoverArriba             = gtk_menu_item_new();
    camelloJ1.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    camelloJ1.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    camelloJ1.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    camelloJ1.movimiento.OPempujarArriba           = gtk_menu_item_new();
    camelloJ1.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    camelloJ1.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    camelloJ1.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    camelloJ1.movimiento.OPestirarArriba           = gtk_menu_item_new();
    camelloJ1.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    camelloJ1.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    camelloJ1.movimiento.OPestirarAbajo            = gtk_menu_item_new();

    camelloJ1.movimiento.OPcancelar                = gtk_menu_item_new();
    ///Jugador 2
        //Mover
    camelloJ2.Menu                                 = gtk_menu_new();
    camelloJ2.movimiento.OPmoverArriba             = gtk_menu_item_new();
    camelloJ2.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    camelloJ2.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    camelloJ2.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    camelloJ2.movimiento.OPempujarArriba           = gtk_menu_item_new();
    camelloJ2.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    camelloJ2.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    camelloJ2.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    camelloJ2.movimiento.OPestirarArriba           = gtk_menu_item_new();
    camelloJ2.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    camelloJ2.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    camelloJ2.movimiento.OPestirarAbajo            = gtk_menu_item_new();
    //-------------------------------AGREGANDO--------------------------------------------------------------
  ///Jugador1
        //Mover
    gtk_menu_shell_append(GTK_MENU_SHELL(camelloJ1.Menu), camelloJ1.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(camelloJ1.Menu), camelloJ1.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(camelloJ1.Menu), camelloJ1.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(camelloJ1.Menu), camelloJ1.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(camelloJ1.Menu), camelloJ1.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(camelloJ1.Menu), camelloJ1.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(camelloJ1.Menu), camelloJ1.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(camelloJ1.Menu), camelloJ1.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(camelloJ1.Menu), camelloJ1.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(camelloJ1.Menu), camelloJ1.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(camelloJ1.Menu), camelloJ1.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(camelloJ1.Menu), camelloJ1.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(camelloJ1.Menu), camelloJ1.movimiento.OPcancelar);
    ///Jugador 2
    gtk_menu_shell_append(GTK_MENU_SHELL(camelloJ2.Menu), camelloJ2.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(camelloJ2.Menu), camelloJ2.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(camelloJ2.Menu), camelloJ2.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(camelloJ2.Menu), camelloJ2.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(camelloJ2.Menu), camelloJ2.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(camelloJ2.Menu), camelloJ2.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(camelloJ2.Menu), camelloJ2.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(camelloJ2.Menu), camelloJ2.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(camelloJ2.Menu), camelloJ2.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(camelloJ2.Menu), camelloJ2.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(camelloJ2.Menu), camelloJ2.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(camelloJ2.Menu), camelloJ2.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(camelloJ2.Menu), camelloJ2.movimiento.OPcancelar);

//-------------------------------CABALLO 1-------------------------------
/// -------------------------------CREANDO-------------------------------
      ///Jugador 1
        //Mover
    caballo1J1.Menu                                 = gtk_menu_new();
    caballo1J1.movimiento.OPmoverArriba             = gtk_menu_item_new();
    caballo1J1.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    caballo1J1.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    caballo1J1.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    caballo1J1.movimiento.OPempujarArriba           = gtk_menu_item_new();
    caballo1J1.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    caballo1J1.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    caballo1J1.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    caballo1J1.movimiento.OPestirarArriba           = gtk_menu_item_new();
    caballo1J1.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    caballo1J1.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    caballo1J1.movimiento.OPestirarAbajo            = gtk_menu_item_new();

    caballo1J1.movimiento.OPcancelar                = gtk_menu_item_new();
    ///Jugador 2
        //Mover
    caballo1J2.Menu                                 = gtk_menu_new();
    caballo1J2.movimiento.OPmoverArriba             = gtk_menu_item_new();
    caballo1J2.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    caballo1J2.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    caballo1J2.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    caballo1J2.movimiento.OPempujarArriba           = gtk_menu_item_new();
    caballo1J2.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    caballo1J2.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    caballo1J2.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    caballo1J2.movimiento.OPestirarArriba           = gtk_menu_item_new();
    caballo1J2.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    caballo1J2.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    caballo1J2.movimiento.OPestirarAbajo            = gtk_menu_item_new();
    //-------------------------------AGREGANDO-------------------------------
  ///Jugador1
        //Mover
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo1J1.Menu), caballo1J1.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo1J1.Menu), caballo1J1.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo1J1.Menu), caballo1J1.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo1J1.Menu), caballo1J1.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo1J1.Menu), caballo1J1.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo1J1.Menu), caballo1J1.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo1J1.Menu), caballo1J1.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo1J1.Menu), caballo1J1.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo1J1.Menu), caballo1J1.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo1J1.Menu), caballo1J1.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo1J1.Menu), caballo1J1.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo1J1.Menu), caballo1J1.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo1J1.Menu), caballo1J1.movimiento.OPcancelar);
    ///Jugador 2
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo1J2.Menu), caballo1J2.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo1J2.Menu), caballo1J2.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo1J2.Menu), caballo1J2.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo1J2.Menu), caballo1J2.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo1J2.Menu), caballo1J2.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo1J2.Menu), caballo1J2.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo1J2.Menu), caballo1J2.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo1J2.Menu), caballo1J2.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo1J2.Menu), caballo1J2.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo1J2.Menu), caballo1J2.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo1J2.Menu), caballo1J2.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo1J2.Menu), caballo1J2.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo1J2.Menu), caballo1J2.movimiento.OPcancelar);
//-------------------------------CABALLO 2-------------------------------
//-------------------------------CREANDO-------------------------------
    ///Jugador 1
        //Mover
    caballo2J1.Menu                                 = gtk_menu_new();
    caballo2J1.movimiento.OPmoverArriba             = gtk_menu_item_new();
    caballo2J1.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    caballo2J1.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    caballo2J1.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    caballo2J1.movimiento.OPempujarArriba           = gtk_menu_item_new();
    caballo2J1.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    caballo2J1.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    caballo2J1.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    caballo2J1.movimiento.OPestirarArriba           = gtk_menu_item_new();
    caballo2J1.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    caballo2J1.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    caballo2J1.movimiento.OPestirarAbajo            = gtk_menu_item_new();

    caballo2J1.movimiento.OPcancelar                = gtk_menu_item_new();
    ///Jugador 2
        //Mover
    caballo2J2.Menu                                 = gtk_menu_new();
    caballo2J2.movimiento.OPmoverArriba             = gtk_menu_item_new();
    caballo2J2.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    caballo2J2.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    caballo2J2.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    caballo2J2.movimiento.OPempujarArriba           = gtk_menu_item_new();
    caballo2J2.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    caballo2J2.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    caballo2J2.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    caballo2J2.movimiento.OPestirarArriba           = gtk_menu_item_new();
    caballo2J2.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    caballo2J2.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    caballo2J2.movimiento.OPestirarAbajo            = gtk_menu_item_new();
    //-------------------------------AGREGANDO-------------------------------
  ///Jugador1
        //Mover
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo2J1.Menu), caballo2J1.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo2J1.Menu), caballo2J1.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo2J1.Menu), caballo2J1.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo2J1.Menu), caballo2J1.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo2J1.Menu), caballo2J1.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo2J1.Menu), caballo2J1.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo2J1.Menu), caballo2J1.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo2J1.Menu), caballo2J1.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo2J1.Menu), caballo2J1.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo2J1.Menu), caballo2J1.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo2J1.Menu), caballo2J1.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo2J1.Menu), caballo2J1.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo2J1.Menu), caballo2J1.movimiento.OPcancelar);
    ///Jugador 2
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo2J2.Menu), caballo2J2.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo2J2.Menu), caballo2J2.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo2J2.Menu), caballo2J2.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo2J2.Menu), caballo2J2.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo2J2.Menu), caballo2J2.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo2J2.Menu), caballo2J2.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo2J2.Menu), caballo2J2.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo2J2.Menu), caballo2J2.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo2J2.Menu), caballo2J2.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo2J2.Menu), caballo2J2.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo2J2.Menu), caballo2J2.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo2J2.Menu), caballo2J2.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(caballo2J2.Menu), caballo2J2.movimiento.OPcancelar);
//-------------------------------PERRO 1-------------------------------
//-------------------------------CREANDO-------------------------------
    ///Jugador 1
        //Mover
    perro1J1.Menu                                 = gtk_menu_new();
    perro1J1.movimiento.OPmoverArriba             = gtk_menu_item_new();
    perro1J1.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    perro1J1.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    perro1J1.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    perro1J1.movimiento.OPempujarArriba           = gtk_menu_item_new();
    perro1J1.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    perro1J1.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    perro1J1.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    perro1J1.movimiento.OPestirarArriba           = gtk_menu_item_new();
    perro1J1.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    perro1J1.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    perro1J1.movimiento.OPestirarAbajo            = gtk_menu_item_new();

    perro1J1.movimiento.OPcancelar                = gtk_menu_item_new();
    ///Jugador 2
        //Mover
    perro1J2.Menu                                 = gtk_menu_new();
    perro1J2.movimiento.OPmoverArriba             = gtk_menu_item_new();
    perro1J2.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    perro1J2.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    perro1J2.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    perro1J2.movimiento.OPempujarArriba           = gtk_menu_item_new();
    perro1J2.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    perro1J2.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    perro1J2.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    perro1J2.movimiento.OPestirarArriba           = gtk_menu_item_new();
    perro1J2.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    perro1J2.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    perro1J2.movimiento.OPestirarAbajo            = gtk_menu_item_new();
    //-------------------------------AGREGANDO-------------------------------
  ///Jugador1
        //Mover
    gtk_menu_shell_append(GTK_MENU_SHELL(perro1J1.Menu), perro1J1.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro1J1.Menu), perro1J1.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro1J1.Menu), perro1J1.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro1J1.Menu), perro1J1.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(perro1J1.Menu), perro1J1.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro1J1.Menu), perro1J1.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro1J1.Menu), perro1J1.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro1J1.Menu), perro1J1.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(perro1J1.Menu), perro1J1.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro1J1.Menu), perro1J1.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro1J1.Menu), perro1J1.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro1J1.Menu), perro1J1.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro1J1.Menu), perro1J1.movimiento.OPcancelar);
    ///Jugador 2
    gtk_menu_shell_append(GTK_MENU_SHELL(perro1J2.Menu), perro1J2.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro1J2.Menu), perro1J2.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro1J2.Menu), perro1J2.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro1J2.Menu), perro1J2.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(perro1J2.Menu), perro1J2.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro1J2.Menu), perro1J2.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro1J2.Menu), perro1J2.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro1J2.Menu), perro1J2.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(perro1J2.Menu), perro1J2.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro1J2.Menu), perro1J2.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro1J2.Menu), perro1J2.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro1J2.Menu), perro1J2.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro1J2.Menu), perro1J2.movimiento.OPcancelar);
//-------------------------------PERRO 2-------------------------------
//-------------------------------CREANDO-------------------------------
    ///Jugador 1
        //Mover
    perro2J1.Menu                                 = gtk_menu_new();
    perro2J1.movimiento.OPmoverArriba             = gtk_menu_item_new();
    perro2J1.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    perro2J1.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    perro2J1.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    perro2J1.movimiento.OPempujarArriba           = gtk_menu_item_new();
    perro2J1.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    perro2J1.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    perro2J1.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    perro2J1.movimiento.OPestirarArriba           = gtk_menu_item_new();
    perro2J1.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    perro2J1.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    perro2J1.movimiento.OPestirarAbajo            = gtk_menu_item_new();

    perro2J1.movimiento.OPcancelar                = gtk_menu_item_new();
    ///Jugador 2
        //Mover
    perro2J2.Menu                                 = gtk_menu_new();
    perro2J2.movimiento.OPmoverArriba             = gtk_menu_item_new();
    perro2J2.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    perro2J2.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    perro2J2.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    perro2J2.movimiento.OPempujarArriba           = gtk_menu_item_new();
    perro2J2.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    perro2J2.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    perro2J2.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    perro2J2.movimiento.OPestirarArriba           = gtk_menu_item_new();
    perro2J2.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    perro2J2.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    perro2J2.movimiento.OPestirarAbajo            = gtk_menu_item_new();
    //-------------------------------AGREGANDO-------------------------------
  ///Jugador1
        //Mover
    gtk_menu_shell_append(GTK_MENU_SHELL(perro2J1.Menu), perro2J1.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro2J1.Menu), perro2J1.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro2J1.Menu), perro2J1.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro2J1.Menu), perro2J1.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(perro2J1.Menu), perro2J1.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro2J1.Menu), perro2J1.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro2J1.Menu), perro2J1.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro2J1.Menu), perro2J1.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(perro2J1.Menu), perro2J1.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro2J1.Menu), perro2J1.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro2J1.Menu), perro2J1.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro2J1.Menu), perro2J1.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro2J1.Menu), perro2J1.movimiento.OPcancelar);
    ///Jugador 2
    gtk_menu_shell_append(GTK_MENU_SHELL(perro2J2.Menu), perro2J2.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro2J2.Menu), perro2J2.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro2J2.Menu), perro2J2.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro2J2.Menu), perro2J2.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(perro2J2.Menu), perro2J2.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro2J2.Menu), perro2J2.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro2J2.Menu), perro2J2.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro2J2.Menu), perro2J2.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(perro2J2.Menu), perro2J2.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro2J2.Menu), perro2J2.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro2J2.Menu), perro2J2.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro2J2.Menu), perro2J2.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(perro2J2.Menu), perro2J2.movimiento.OPcancelar);

//-------------------------------GATO 1-------------------------------
//-------------------------------CREANDO-------------------------------
   ///Jugador 1
        //Mover
    gato1J1.Menu                                 = gtk_menu_new();
    gato1J1.movimiento.OPmoverArriba             = gtk_menu_item_new();
    gato1J1.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    gato1J1.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    gato1J1.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    gato1J1.movimiento.OPempujarArriba           = gtk_menu_item_new();
    gato1J1.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    gato1J1.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    gato1J1.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    gato1J1.movimiento.OPestirarArriba           = gtk_menu_item_new();
    gato1J1.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    gato1J1.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    gato1J1.movimiento.OPestirarAbajo            = gtk_menu_item_new();

    gato1J1.movimiento.OPcancelar                = gtk_menu_item_new();
    ///Jugador 2
        //Mover
    gato1J2.Menu                                 = gtk_menu_new();
    gato1J2.movimiento.OPmoverArriba             = gtk_menu_item_new();
    gato1J2.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    gato1J2.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    gato1J2.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    gato1J2.movimiento.OPempujarArriba           = gtk_menu_item_new();
    gato1J2.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    gato1J2.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    gato1J2.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    gato1J2.movimiento.OPestirarArriba           = gtk_menu_item_new();
    gato1J2.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    gato1J2.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    gato1J2.movimiento.OPestirarAbajo            = gtk_menu_item_new();
    //-------------------------------AGREGANDO-------------------------------
  ///Jugador1
        //Mover
    gtk_menu_shell_append(GTK_MENU_SHELL(gato1J1.Menu), gato1J1.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato1J1.Menu), gato1J1.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato1J1.Menu), gato1J1.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato1J1.Menu), gato1J1.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(gato1J1.Menu), gato1J1.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato1J1.Menu), gato1J1.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato1J1.Menu), gato1J1.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato1J1.Menu), gato1J1.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(gato1J1.Menu), gato1J1.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato1J1.Menu), gato1J1.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato1J1.Menu), gato1J1.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato1J1.Menu), gato1J1.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato1J1.Menu), gato1J1.movimiento.OPcancelar);
    ///Jugador 2
    gtk_menu_shell_append(GTK_MENU_SHELL(gato1J2.Menu), gato1J2.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato1J2.Menu), gato1J2.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato1J2.Menu), gato1J2.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato1J2.Menu), gato1J2.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(gato1J2.Menu), gato1J2.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato1J2.Menu), gato1J2.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato1J2.Menu), gato1J2.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato1J2.Menu), gato1J2.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(gato1J2.Menu), gato1J2.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato1J2.Menu), gato1J2.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato1J2.Menu), gato1J2.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato1J2.Menu), gato1J2.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato1J2.Menu), gato1J2.movimiento.OPcancelar);
/// ////////////////////////GATO 2//////////////////////////////////////
/// ///////////////////////CREANDO///////////////////////////////////////
    ///Jugador 1
        //Mover
    gato2J1.Menu                                 = gtk_menu_new();
    gato2J1.movimiento.OPmoverArriba             = gtk_menu_item_new();
    gato2J1.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    gato2J1.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    gato2J1.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    gato2J1.movimiento.OPempujarArriba           = gtk_menu_item_new();
    gato2J1.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    gato2J1.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    gato2J1.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    gato2J1.movimiento.OPestirarArriba           = gtk_menu_item_new();
    gato2J1.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    gato2J1.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    gato2J1.movimiento.OPestirarAbajo            = gtk_menu_item_new();

    gato2J1.movimiento.OPcancelar                = gtk_menu_item_new();
    ///Jugador 2
        //Mover
    gato2J2.Menu                                 = gtk_menu_new();
    gato2J2.movimiento.OPmoverArriba             = gtk_menu_item_new();
    gato2J2.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    gato2J2.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    gato2J2.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    gato2J2.movimiento.OPempujarArriba           = gtk_menu_item_new();
    gato2J2.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    gato2J2.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    gato2J2.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    gato2J2.movimiento.OPestirarArriba           = gtk_menu_item_new();
    gato2J2.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    gato2J2.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    gato2J2.movimiento.OPestirarAbajo            = gtk_menu_item_new();
    //-------------------------------AGREGANDO-------------------------------
  ///Jugador1
        //Mover
    gtk_menu_shell_append(GTK_MENU_SHELL(gato2J1.Menu), gato2J1.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato2J1.Menu), gato2J1.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato2J1.Menu), gato2J1.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato2J1.Menu), gato2J1.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(gato2J1.Menu), gato2J1.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato2J1.Menu), gato2J1.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato2J1.Menu), gato2J1.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato2J1.Menu), gato2J1.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(gato2J1.Menu), gato2J1.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato2J1.Menu), gato2J1.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato2J1.Menu), gato2J1.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato2J1.Menu), gato2J1.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato2J1.Menu), gato2J1.movimiento.OPcancelar);
    ///Jugador 2
    gtk_menu_shell_append(GTK_MENU_SHELL(gato2J2.Menu), gato2J2.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato2J2.Menu), gato2J2.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato2J2.Menu), gato2J2.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato2J2.Menu), gato2J2.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(gato2J2.Menu), gato2J2.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato2J2.Menu), gato2J2.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato2J2.Menu), gato2J2.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato2J2.Menu), gato2J2.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(gato2J2.Menu), gato2J2.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato2J2.Menu), gato2J2.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato2J2.Menu), gato2J2.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato2J2.Menu), gato2J2.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(gato2J2.Menu), gato2J2.movimiento.OPcancelar);
//-------------------------------CONEJO 1-------------------------------
//-------------------------------CREANDO-------------------------------
      ///Jugador 1
        //Mover
    conejo1J1.Menu                                 = gtk_menu_new();
    conejo1J1.movimiento.OPmoverArriba             = gtk_menu_item_new();
    conejo1J1.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    conejo1J1.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    conejo1J1.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    conejo1J1.movimiento.OPempujarArriba           = gtk_menu_item_new();
    conejo1J1.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    conejo1J1.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    conejo1J1.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    conejo1J1.movimiento.OPestirarArriba           = gtk_menu_item_new();
    conejo1J1.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    conejo1J1.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    conejo1J1.movimiento.OPestirarAbajo            = gtk_menu_item_new();

    conejo1J1.movimiento.OPcancelar                = gtk_menu_item_new();
    ///Jugador 2
        //Mover
    conejo1J2.Menu                                 = gtk_menu_new();
    conejo1J2.movimiento.OPmoverArriba             = gtk_menu_item_new();
    conejo1J2.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    conejo1J2.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    conejo1J2.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    conejo1J2.movimiento.OPempujarArriba           = gtk_menu_item_new();
    conejo1J2.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    conejo1J2.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    conejo1J2.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    conejo1J2.movimiento.OPestirarArriba           = gtk_menu_item_new();
    conejo1J2.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    conejo1J2.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    conejo1J2.movimiento.OPestirarAbajo            = gtk_menu_item_new();
    //-------------------------------AGREGANDO-------------------------------
  ///Jugador1
        //Mover
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo1J1.Menu), conejo1J1.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo1J1.Menu), conejo1J1.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo1J1.Menu), conejo1J1.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo1J1.Menu), conejo1J1.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo1J1.Menu), conejo1J1.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo1J1.Menu), conejo1J1.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo1J1.Menu), conejo1J1.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo1J1.Menu), conejo1J1.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo1J1.Menu), conejo1J1.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo1J1.Menu), conejo1J1.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo1J1.Menu), conejo1J1.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo1J1.Menu), conejo1J1.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo1J1.Menu), conejo1J1.movimiento.OPcancelar);
    ///Jugador 2
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo1J2.Menu), conejo1J2.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo1J2.Menu), conejo1J2.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo1J2.Menu), conejo1J2.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo1J2.Menu), conejo1J2.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo1J2.Menu), conejo1J2.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo1J2.Menu), conejo1J2.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo1J2.Menu), conejo1J2.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo1J2.Menu), conejo1J2.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo1J2.Menu), conejo1J2.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo1J2.Menu), conejo1J2.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo1J2.Menu), conejo1J2.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo1J2.Menu), conejo1J2.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo1J2.Menu), conejo1J2.movimiento.OPcancelar);
//-------------------------------CONEJO 2-------------------------------
//-------------------------------CREANDO-------------------------------
    ///Jugador 1
        //Mover
    conejo2J1.Menu                                 = gtk_menu_new();
    conejo2J1.movimiento.OPmoverArriba             = gtk_menu_item_new();
    conejo2J1.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    conejo2J1.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    conejo2J1.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    conejo2J1.movimiento.OPempujarArriba           = gtk_menu_item_new();
    conejo2J1.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    conejo2J1.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    conejo2J1.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    conejo2J1.movimiento.OPestirarArriba           = gtk_menu_item_new();
    conejo2J1.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    conejo2J1.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    conejo2J1.movimiento.OPestirarAbajo            = gtk_menu_item_new();

    conejo2J1.movimiento.OPcancelar                = gtk_menu_item_new();
    ///Jugador 2
        //Mover
    conejo2J2.Menu                                 = gtk_menu_new();
    conejo2J2.movimiento.OPmoverArriba             = gtk_menu_item_new();
    conejo2J2.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    conejo2J2.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    conejo2J2.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    conejo2J2.movimiento.OPempujarArriba           = gtk_menu_item_new();
    conejo2J2.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    conejo2J2.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    conejo2J2.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    conejo2J2.movimiento.OPestirarArriba           = gtk_menu_item_new();
    conejo2J2.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    conejo2J2.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    conejo2J2.movimiento.OPestirarAbajo            = gtk_menu_item_new();
    //-------------------------------AGREGANDO-------------------------------
  ///Jugador1
        //Mover
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo2J1.Menu), conejo2J1.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo2J1.Menu), conejo2J1.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo2J1.Menu), conejo2J1.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo2J1.Menu), conejo2J1.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo2J1.Menu), conejo2J1.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo2J1.Menu), conejo2J1.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo2J1.Menu), conejo2J1.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo2J1.Menu), conejo2J1.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo2J1.Menu), conejo2J1.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo2J1.Menu), conejo2J1.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo2J1.Menu), conejo2J1.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo2J1.Menu), conejo2J1.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo2J1.Menu), conejo2J1.movimiento.OPcancelar);
    ///Jugador 2
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo2J2.Menu), conejo2J2.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo2J2.Menu), conejo2J2.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo2J2.Menu), conejo2J2.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo2J2.Menu), conejo2J2.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo2J2.Menu), conejo2J2.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo2J2.Menu), conejo2J2.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo2J2.Menu), conejo2J2.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo2J2.Menu), conejo2J2.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo2J2.Menu), conejo2J2.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo2J2.Menu), conejo2J2.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo2J2.Menu), conejo2J2.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo2J2.Menu), conejo2J2.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo2J2.Menu), conejo2J2.movimiento.OPcancelar);
//-------------------------------CONEJO 3-------------------------------
//-------------------------------CREANDO-------------------------------
  ///Jugador 1
        //Mover
    conejo3J1.Menu                                 = gtk_menu_new();
    conejo3J1.movimiento.OPmoverArriba             = gtk_menu_item_new();
    conejo3J1.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    conejo3J1.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    conejo3J1.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    conejo3J1.movimiento.OPempujarArriba           = gtk_menu_item_new();
    conejo3J1.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    conejo3J1.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    conejo3J1.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    conejo3J1.movimiento.OPestirarArriba           = gtk_menu_item_new();
    conejo3J1.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    conejo3J1.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    conejo3J1.movimiento.OPestirarAbajo            = gtk_menu_item_new();

    conejo3J1.movimiento.OPcancelar                = gtk_menu_item_new();
    ///Jugador 2
        //Mover
    conejo3J2.Menu                                 = gtk_menu_new();
    conejo3J2.movimiento.OPmoverArriba             = gtk_menu_item_new();
    conejo3J2.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    conejo3J2.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    conejo3J2.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    conejo3J2.movimiento.OPempujarArriba           = gtk_menu_item_new();
    conejo3J2.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    conejo3J2.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    conejo3J2.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    conejo3J2.movimiento.OPestirarArriba           = gtk_menu_item_new();
    conejo3J2.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    conejo3J2.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    conejo3J2.movimiento.OPestirarAbajo            = gtk_menu_item_new();
    //-------------------------------AGREGANDO-------------------------------
  ///Jugador1
        //Mover
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo3J1.Menu), conejo3J1.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo3J1.Menu), conejo3J1.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo3J1.Menu), conejo3J1.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo3J1.Menu), conejo3J1.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo3J1.Menu), conejo3J1.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo3J1.Menu), conejo3J1.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo3J1.Menu), conejo3J1.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo3J1.Menu), conejo3J1.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo3J1.Menu), conejo3J1.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo3J1.Menu), conejo3J1.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo3J1.Menu), conejo3J1.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo3J1.Menu), conejo3J1.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo3J1.Menu), conejo3J1.movimiento.OPcancelar);
    ///Jugador 2
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo3J2.Menu), conejo3J2.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo3J2.Menu), conejo3J2.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo3J2.Menu), conejo3J2.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo3J2.Menu), conejo3J2.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo3J2.Menu), conejo3J2.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo3J2.Menu), conejo3J2.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo3J2.Menu), conejo3J2.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo3J2.Menu), conejo3J2.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo3J2.Menu), conejo3J2.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo3J2.Menu), conejo3J2.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo3J2.Menu), conejo3J2.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo3J2.Menu), conejo3J2.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo3J2.Menu), conejo3J2.movimiento.OPcancelar);
/// ////////////////////////CONEJO 4//////////////////////////////////////
/// ///////////////////////CREANDO///////////////////////////////////////
    ///Jugador 1
        //Mover
    conejo4J1.Menu                                 = gtk_menu_new();
    conejo4J1.movimiento.OPmoverArriba             = gtk_menu_item_new();
    conejo4J1.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    conejo4J1.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    conejo4J1.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    conejo4J1.movimiento.OPempujarArriba           = gtk_menu_item_new();
    conejo4J1.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    conejo4J1.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    conejo4J1.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    conejo4J1.movimiento.OPestirarArriba           = gtk_menu_item_new();
    conejo4J1.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    conejo4J1.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    conejo4J1.movimiento.OPestirarAbajo            = gtk_menu_item_new();

    conejo4J1.movimiento.OPcancelar                = gtk_menu_item_new();
    ///Jugador 2
        //Mover
    conejo4J2.Menu                                 = gtk_menu_new();
    conejo4J2.movimiento.OPmoverArriba             = gtk_menu_item_new();
    conejo4J2.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    conejo4J2.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    conejo4J2.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    conejo4J2.movimiento.OPempujarArriba           = gtk_menu_item_new();
    conejo4J2.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    conejo4J2.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    conejo4J2.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    conejo4J2.movimiento.OPestirarArriba           = gtk_menu_item_new();
    conejo4J2.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    conejo4J2.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    conejo4J2.movimiento.OPestirarAbajo            = gtk_menu_item_new();
    /// -------------------------------AGREGANDO-------------------------------
  ///Jugador1
        //Mover
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo4J1.Menu), conejo4J1.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo4J1.Menu), conejo4J1.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo4J1.Menu), conejo4J1.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo4J1.Menu), conejo4J1.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo4J1.Menu), conejo4J1.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo4J1.Menu), conejo4J1.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo4J1.Menu), conejo4J1.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo4J1.Menu), conejo4J1.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo4J1.Menu), conejo4J1.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo4J1.Menu), conejo4J1.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo4J1.Menu), conejo4J1.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo4J1.Menu), conejo4J1.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo4J1.Menu), conejo4J1.movimiento.OPcancelar);
    ///Jugador 2
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo4J2.Menu), conejo4J2.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo4J2.Menu), conejo4J2.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo4J2.Menu), conejo4J2.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo4J2.Menu), conejo4J2.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo4J2.Menu), conejo4J2.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo4J2.Menu), conejo4J2.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo4J2.Menu), conejo4J2.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo4J2.Menu), conejo4J2.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo4J2.Menu), conejo4J2.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo4J2.Menu), conejo4J2.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo4J2.Menu), conejo4J2.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo4J2.Menu), conejo4J2.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo4J2.Menu), conejo4J2.movimiento.OPcancelar);
// -------------------------------CONEJO 5-------------------------------
//-------------------------------CREANDO-------------------------------
    ///Jugador 1
        //Mover
    conejo5J1.Menu                                 = gtk_menu_new();
    conejo5J1.movimiento.OPmoverArriba             = gtk_menu_item_new();
    conejo5J1.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    conejo5J1.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    conejo5J1.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    conejo5J1.movimiento.OPempujarArriba           = gtk_menu_item_new();
    conejo5J1.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    conejo5J1.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    conejo5J1.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    conejo5J1.movimiento.OPestirarArriba           = gtk_menu_item_new();
    conejo5J1.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    conejo5J1.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    conejo5J1.movimiento.OPestirarAbajo            = gtk_menu_item_new();

    conejo5J1.movimiento.OPcancelar                = gtk_menu_item_new();
    ///Jugador 2
        //Mover
    conejo5J2.Menu                                 = gtk_menu_new();
    conejo5J2.movimiento.OPmoverArriba             = gtk_menu_item_new();
    conejo5J2.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    conejo5J2.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    conejo5J2.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    conejo5J2.movimiento.OPempujarArriba           = gtk_menu_item_new();
    conejo5J2.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    conejo5J2.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    conejo5J2.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    conejo5J2.movimiento.OPestirarArriba           = gtk_menu_item_new();
    conejo5J2.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    conejo5J2.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    conejo5J2.movimiento.OPestirarAbajo            = gtk_menu_item_new();
    //-------------------------------AGREGANDO-------------------------------
  ///Jugador1
        //Mover
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo5J1.Menu), conejo5J1.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo5J1.Menu), conejo5J1.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo5J1.Menu), conejo5J1.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo5J1.Menu), conejo5J1.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo5J1.Menu), conejo5J1.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo5J1.Menu), conejo5J1.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo5J1.Menu), conejo5J1.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo5J1.Menu), conejo5J1.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo5J1.Menu), conejo5J1.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo5J1.Menu), conejo5J1.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo5J1.Menu), conejo5J1.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo5J1.Menu), conejo5J1.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo5J1.Menu), conejo5J1.movimiento.OPcancelar);
    ///Jugador 2
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo5J2.Menu), conejo5J2.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo5J2.Menu), conejo5J2.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo5J2.Menu), conejo5J2.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo5J2.Menu), conejo5J2.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo5J2.Menu), conejo5J2.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo5J2.Menu), conejo5J2.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo5J2.Menu), conejo5J2.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo5J2.Menu), conejo5J2.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo5J2.Menu), conejo5J2.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo5J2.Menu), conejo5J2.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo5J2.Menu), conejo5J2.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo5J2.Menu), conejo5J2.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo5J2.Menu), conejo5J2.movimiento.OPcancelar);
 //-------------------------------CONEJO 6-------------------------------
//-------------------------------CREANDO-------------------------------
    ///Jugador 1
        //Mover
    conejo6J1.Menu                                 = gtk_menu_new();
    conejo6J1.movimiento.OPmoverArriba             = gtk_menu_item_new();
    conejo6J1.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    conejo6J1.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    conejo6J1.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    conejo6J1.movimiento.OPempujarArriba           = gtk_menu_item_new();
    conejo6J1.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    conejo6J1.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    conejo6J1.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    conejo6J1.movimiento.OPestirarArriba           = gtk_menu_item_new();
    conejo6J1.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    conejo6J1.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    conejo6J1.movimiento.OPestirarAbajo            = gtk_menu_item_new();

    conejo6J1.movimiento.OPcancelar                = gtk_menu_item_new();
    ///Jugador 2
        //Mover
    conejo6J2.Menu                                 = gtk_menu_new();
    conejo6J2.movimiento.OPmoverArriba             = gtk_menu_item_new();
    conejo6J2.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    conejo6J2.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    conejo6J2.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    conejo6J2.movimiento.OPempujarArriba           = gtk_menu_item_new();
    conejo6J2.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    conejo6J2.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    conejo6J2.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    conejo6J2.movimiento.OPestirarArriba           = gtk_menu_item_new();
    conejo6J2.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    conejo6J2.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    conejo6J2.movimiento.OPestirarAbajo            = gtk_menu_item_new();
    //-------------------------------AGREGANDO-------------------------------
  ///Jugador1
        //Mover
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo6J1.Menu), conejo6J1.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo6J1.Menu), conejo6J1.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo6J1.Menu), conejo6J1.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo6J1.Menu), conejo6J1.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo6J1.Menu), conejo6J1.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo6J1.Menu), conejo6J1.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo6J1.Menu), conejo6J1.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo6J1.Menu), conejo6J1.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo6J1.Menu), conejo6J1.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo6J1.Menu), conejo6J1.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo6J1.Menu), conejo6J1.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo6J1.Menu), conejo6J1.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo6J1.Menu), conejo6J1.movimiento.OPcancelar);
    ///Jugador 2
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo6J2.Menu), conejo6J2.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo6J2.Menu), conejo6J2.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo6J2.Menu), conejo6J2.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo6J2.Menu), conejo6J2.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo6J2.Menu), conejo6J2.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo6J2.Menu), conejo6J2.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo6J2.Menu), conejo6J2.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo6J2.Menu), conejo6J2.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo6J2.Menu), conejo6J2.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo6J2.Menu), conejo6J2.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo6J2.Menu), conejo6J2.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo6J2.Menu), conejo6J2.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo6J2.Menu), conejo6J2.movimiento.OPcancelar);

//-------------------------------CONEJO 7-------------------------------
//-------------------------------CREANDO-------------------------------
    ///Jugador 1
        //Mover
    conejo7J1.Menu                                 = gtk_menu_new();
    conejo7J1.movimiento.OPmoverArriba             = gtk_menu_item_new();
    conejo7J1.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    conejo7J1.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    conejo7J1.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    conejo7J1.movimiento.OPempujarArriba           = gtk_menu_item_new();
    conejo7J1.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    conejo7J1.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    conejo7J1.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    conejo7J1.movimiento.OPestirarArriba           = gtk_menu_item_new();
    conejo7J1.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    conejo7J1.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    conejo7J1.movimiento.OPestirarAbajo            = gtk_menu_item_new();

    conejo7J1.movimiento.OPcancelar                = gtk_menu_item_new();
    ///Jugador 2
        //Mover
    conejo7J2.Menu                                 = gtk_menu_new();
    conejo7J2.movimiento.OPmoverArriba             = gtk_menu_item_new();
    conejo7J2.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    conejo7J2.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    conejo7J2.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    conejo7J2.movimiento.OPempujarArriba           = gtk_menu_item_new();
    conejo7J2.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    conejo7J2.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    conejo7J2.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    conejo7J2.movimiento.OPestirarArriba           = gtk_menu_item_new();
    conejo7J2.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    conejo7J2.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    conejo7J2.movimiento.OPestirarAbajo            = gtk_menu_item_new();
    /// ///////////////////////AGREGANDO///////////////////////////////////////
  ///Jugador1
        //Mover
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo7J1.Menu), conejo7J1.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo7J1.Menu), conejo7J1.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo7J1.Menu), conejo7J1.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo7J1.Menu), conejo7J1.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo7J1.Menu), conejo7J1.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo7J1.Menu), conejo7J1.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo7J1.Menu), conejo7J1.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo7J1.Menu), conejo7J1.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo7J1.Menu), conejo7J1.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo7J1.Menu), conejo7J1.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo7J1.Menu), conejo7J1.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo7J1.Menu), conejo7J1.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo7J1.Menu), conejo7J1.movimiento.OPcancelar);
    ///Jugador 2
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo7J2.Menu), conejo7J2.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo7J2.Menu), conejo7J2.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo7J2.Menu), conejo7J2.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo7J2.Menu), conejo7J2.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo7J2.Menu), conejo7J2.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo7J2.Menu), conejo7J2.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo7J2.Menu), conejo7J2.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo7J2.Menu), conejo7J2.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo7J2.Menu), conejo7J2.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo7J2.Menu), conejo7J2.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo7J2.Menu), conejo7J2.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo7J2.Menu), conejo7J2.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo7J2.Menu), conejo7J2.movimiento.OPcancelar);
 /// ////////////////////////CONEJO 8//////////////////////////////////////
/// ///////////////////////CREANDO///////////////////////////////////////
    ///Jugador 1
        //Mover
    conejo8J1.Menu                                 = gtk_menu_new();
    conejo8J1.movimiento.OPmoverArriba             = gtk_menu_item_new();
    conejo8J1.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    conejo8J1.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    conejo8J1.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    conejo8J1.movimiento.OPempujarArriba           = gtk_menu_item_new();
    conejo8J1.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    conejo8J1.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    conejo8J1.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    conejo8J1.movimiento.OPestirarArriba           = gtk_menu_item_new();
    conejo8J1.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    conejo8J1.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    conejo8J1.movimiento.OPestirarAbajo            = gtk_menu_item_new();

    conejo8J1.movimiento.OPcancelar                = gtk_menu_item_new();
    ///Jugador 2
        //Mover
    conejo8J2.Menu                                 = gtk_menu_new();
    conejo8J2.movimiento.OPmoverArriba             = gtk_menu_item_new();
    conejo8J2.movimiento.OPmoverAbajo              = gtk_menu_item_new();
    conejo8J2.movimiento.OPmoverDerecha            = gtk_menu_item_new();
    conejo8J2.movimiento.OPmoverIzquierda          = gtk_menu_item_new();
        //Empujar
    conejo8J2.movimiento.OPempujarArriba           = gtk_menu_item_new();
    conejo8J2.movimiento.OPempujarDerecha          = gtk_menu_item_new();
    conejo8J2.movimiento.OPempujarIzquierda        = gtk_menu_item_new();
    conejo8J2.movimiento.OPempujarAbajo            = gtk_menu_item_new();
        //Estirar
    conejo8J2.movimiento.OPestirarArriba           = gtk_menu_item_new();
    conejo8J2.movimiento.OPestirarDerecha          = gtk_menu_item_new();
    conejo8J2.movimiento.OPestirarIzquierda        = gtk_menu_item_new();
    conejo8J2.movimiento.OPestirarAbajo            = gtk_menu_item_new();
    /// ///////////////////////AGREGANDO///////////////////////////////////////
  ///Jugador1
        //Mover
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo8J1.Menu), conejo8J1.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo8J1.Menu), conejo8J1.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo8J1.Menu), conejo8J1.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo8J1.Menu), conejo8J1.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo8J1.Menu), conejo8J1.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo8J1.Menu), conejo8J1.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo8J1.Menu), conejo8J1.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo8J1.Menu), conejo8J1.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo8J1.Menu), conejo8J1.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo8J1.Menu), conejo8J1.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo8J1.Menu), conejo8J1.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo8J1.Menu), conejo8J1.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo8J1.Menu), conejo8J1.movimiento.OPcancelar);
    ///Jugador 2
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo8J2.Menu), conejo8J2.movimiento.OPmoverArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo8J2.Menu), conejo8J2.movimiento.OPmoverAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo8J2.Menu), conejo8J2.movimiento.OPmoverDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo8J2.Menu), conejo8J2.movimiento.OPmoverIzquierda);
        //Empujar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo8J2.Menu), conejo8J2.movimiento.OPempujarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo8J2.Menu), conejo8J2.movimiento.OPempujarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo8J2.Menu), conejo8J2.movimiento.OPempujarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo8J2.Menu), conejo8J2.movimiento.OPempujarIzquierda);
        //Estirar
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo8J2.Menu), conejo8J2.movimiento.OPestirarArriba);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo8J2.Menu), conejo8J2.movimiento.OPestirarAbajo);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo8J2.Menu), conejo8J2.movimiento.OPestirarDerecha);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo8J2.Menu), conejo8J2.movimiento.OPestirarIzquierda);
    gtk_menu_shell_append(GTK_MENU_SHELL(conejo8J2.Menu), conejo8J2.movimiento.OPcancelar);


//Cargando iconos MOVER ARRIBA y EMPUJAR ARRIBA para todas las piezas
    elefanteJ1.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    elefanteJ2.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    camelloJ1.movimiento.ICOmoverArriba  = gtk_image_new_from_file("moverArriba.png");
    camelloJ2.movimiento.ICOmoverArriba  = gtk_image_new_from_file("moverArriba.png");
    caballo1J1.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    caballo1J2.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    caballo2J1.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    caballo2J2.movimiento.ICOmoverArriba = gtk_image_new_from_file("moverArriba.png");
    perro1J1.movimiento.ICOmoverArriba   = gtk_image_new_from_file("moverArriba.png");
    perro1J2.movimiento.ICOmoverArriba   = gtk_image_new_from_file("moverArriba.png");
    perro2J1.movimiento.ICOmoverArriba   = gtk_image_new_from_file("moverArriba.png");
    perro2J2.movimiento.ICOmoverArriba   = gtk_image_new_from_file("moverArriba.png");
    gato1J1.movimiento.ICOmoverArriba    = gtk_image_new_from_file("moverArriba.png");
    gato1J2.movimiento.ICOmoverArriba    = gtk_image_new_from_file("moverArriba.png");
    gato2J1.movimiento.ICOmoverArriba    = gtk_image_new_from_file("moverArriba.png");
    gato2J2.movimiento.ICOmoverArriba    = gtk_image_new_from_file("moverArriba.png");
    conejo1J1.movimiento.ICOmoverArriba  = gtk_image_new_from_file("moverArriba.png");
    conejo1J2.movimiento.ICOmoverArriba  = gtk_image_new_from_file("moverArriba.png");
    conejo2J1.movimiento.ICOmoverArriba  = gtk_image_new_from_file("moverArriba.png");
    conejo2J2.movimiento.ICOmoverArriba  = gtk_image_new_from_file("moverArriba.png");
    conejo3J1.movimiento.ICOmoverArriba  = gtk_image_new_from_file("moverArriba.png");
    conejo3J2.movimiento.ICOmoverArriba  = gtk_image_new_from_file("moverArriba.png");
    conejo4J1.movimiento.ICOmoverArriba  = gtk_image_new_from_file("moverArriba.png");
    conejo4J2.movimiento.ICOmoverArriba  = gtk_image_new_from_file("moverArriba.png");
    conejo5J1.movimiento.ICOmoverArriba  = gtk_image_new_from_file("moverArriba.png");
    conejo5J2.movimiento.ICOmoverArriba  = gtk_image_new_from_file("moverArriba.png");
    conejo6J1.movimiento.ICOmoverArriba  = gtk_image_new_from_file("moverArriba.png");
    conejo6J2.movimiento.ICOmoverArriba  = gtk_image_new_from_file("moverArriba.png");
    conejo7J1.movimiento.ICOmoverArriba  = gtk_image_new_from_file("moverArriba.png");
    conejo7J2.movimiento.ICOmoverArriba  = gtk_image_new_from_file("moverArriba.png");
    conejo8J1.movimiento.ICOmoverArriba  = gtk_image_new_from_file("moverArriba.png");
    conejo8J2.movimiento.ICOmoverArriba  = gtk_image_new_from_file("moverArriba.png");
    elefanteJ1.movimiento.ICOempujarArriba = gtk_image_new_from_file("empujarArriba.png");
    camelloJ1.movimiento.ICOempujarArriba  = gtk_image_new_from_file("empujarArriba.png");
    caballo1J1.movimiento.ICOempujarArriba = gtk_image_new_from_file("empujarArriba.png");
    caballo2J1.movimiento.ICOempujarArriba = gtk_image_new_from_file("empujarArriba.png");
    perro1J1.movimiento.ICOempujarArriba   = gtk_image_new_from_file("empujarArriba.png");
    perro2J1.movimiento.ICOempujarArriba   = gtk_image_new_from_file("empujarArriba.png");
    gato1J1.movimiento.ICOempujarArriba    = gtk_image_new_from_file("empujarArriba.png");
    gato2J1.movimiento.ICOempujarArriba    = gtk_image_new_from_file("empujarArriba.png");
    conejo1J1.movimiento.ICOempujarArriba  = gtk_image_new_from_file("empujarArriba.png");
    conejo2J1.movimiento.ICOempujarArriba  = gtk_image_new_from_file("empujarArriba.png");
    conejo3J1.movimiento.ICOempujarArriba  = gtk_image_new_from_file("empujarArriba.png");
    conejo4J1.movimiento.ICOempujarArriba  = gtk_image_new_from_file("empujarArriba.png");
    conejo5J1.movimiento.ICOempujarArriba  = gtk_image_new_from_file("empujarArriba.png");
    conejo6J1.movimiento.ICOempujarArriba  = gtk_image_new_from_file("empujarArriba.png");
    conejo7J1.movimiento.ICOempujarArriba  = gtk_image_new_from_file("empujarArriba.png");
    conejo8J1.movimiento.ICOempujarArriba  = gtk_image_new_from_file("empujarArriba.png");
    elefanteJ2.movimiento.ICOestirarArriba = gtk_image_new_from_file("estirarArriba.png");
    camelloJ2.movimiento.ICOestirarArriba  = gtk_image_new_from_file("estirarArriba.png");
    caballo1J2.movimiento.ICOestirarArriba = gtk_image_new_from_file("estirarArriba.png");
    caballo2J2.movimiento.ICOestirarArriba = gtk_image_new_from_file("estirarArriba.png");
    perro1J2.movimiento.ICOestirarArriba   = gtk_image_new_from_file("estirarArriba.png");
    perro2J2.movimiento.ICOestirarArriba   = gtk_image_new_from_file("estirarArriba.png");
    gato1J2.movimiento.ICOestirarArriba    = gtk_image_new_from_file("estirarArriba.png");
    gato2J2.movimiento.ICOestirarArriba    = gtk_image_new_from_file("estirarArriba.png");
    conejo1J2.movimiento.ICOestirarArriba  = gtk_image_new_from_file("estirarArriba.png");
    conejo2J2.movimiento.ICOestirarArriba  = gtk_image_new_from_file("estirarArriba.png");
    conejo3J2.movimiento.ICOestirarArriba  = gtk_image_new_from_file("estirarArriba.png");
    conejo4J2.movimiento.ICOestirarArriba  = gtk_image_new_from_file("estirarArriba.png");
    conejo5J2.movimiento.ICOestirarArriba  = gtk_image_new_from_file("estirarArriba.png");
    conejo6J2.movimiento.ICOestirarArriba  = gtk_image_new_from_file("estirarArriba.png");
    conejo7J2.movimiento.ICOestirarArriba  = gtk_image_new_from_file("estirarArriba.png");
    conejo8J2.movimiento.ICOestirarArriba  = gtk_image_new_from_file("estirarArriba.png");


//Cargando LABEL MOVER ARRIBA y EMPUJAR ARRIBA para todas las piezas
    elefanteJ1.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    elefanteJ2.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    camelloJ1.movimiento.LBLmoverArriba  = gtk_label_new(" Mover Arriba ");
    camelloJ2.movimiento.LBLmoverArriba  = gtk_label_new(" Mover Arriba ");
    caballo1J1.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    caballo1J2.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    caballo2J1.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    caballo2J2.movimiento.LBLmoverArriba = gtk_label_new(" Mover Arriba ");
    perro1J1.movimiento.LBLmoverArriba   = gtk_label_new(" Mover Arriba ");
    perro1J2.movimiento.LBLmoverArriba   = gtk_label_new(" Mover Arriba ");
    perro2J1.movimiento.LBLmoverArriba   = gtk_label_new(" Mover Arriba ");
    perro2J2.movimiento.LBLmoverArriba   = gtk_label_new(" Mover Arriba ");
    gato1J1.movimiento.LBLmoverArriba    = gtk_label_new(" Mover Arriba ");
    gato1J2.movimiento.LBLmoverArriba    = gtk_label_new(" Mover Arriba ");
    gato2J1.movimiento.LBLmoverArriba    = gtk_label_new(" Mover Arriba ");
    gato2J2.movimiento.LBLmoverArriba    = gtk_label_new(" Mover Arriba ");
    conejo1J1.movimiento.LBLmoverArriba  = gtk_label_new(" Mover Arriba ");
    conejo1J2.movimiento.LBLmoverArriba  = gtk_label_new(" Mover Arriba ");
    conejo2J1.movimiento.LBLmoverArriba  = gtk_label_new(" Mover Arriba ");
    conejo2J2.movimiento.LBLmoverArriba  = gtk_label_new(" Mover Arriba ");
    conejo3J1.movimiento.LBLmoverArriba  = gtk_label_new(" Mover Arriba ");
    conejo3J2.movimiento.LBLmoverArriba  = gtk_label_new(" Mover Arriba ");
    conejo4J1.movimiento.LBLmoverArriba  = gtk_label_new(" Mover Arriba ");
    conejo4J2.movimiento.LBLmoverArriba  = gtk_label_new(" Mover Arriba ");
    conejo5J1.movimiento.LBLmoverArriba  = gtk_label_new(" Mover Arriba ");
    conejo5J2.movimiento.LBLmoverArriba  = gtk_label_new(" Mover Arriba ");
    conejo6J1.movimiento.LBLmoverArriba  = gtk_label_new(" Mover Arriba ");
    conejo6J2.movimiento.LBLmoverArriba  = gtk_label_new(" Mover Arriba ");
    conejo7J1.movimiento.LBLmoverArriba  = gtk_label_new(" Mover Arriba ");
    conejo7J2.movimiento.LBLmoverArriba  = gtk_label_new(" Mover Arriba ");
    conejo8J1.movimiento.LBLmoverArriba  = gtk_label_new(" Mover Arriba ");
    conejo8J2.movimiento.LBLmoverArriba  = gtk_label_new(" Mover Arriba ");
    elefanteJ1.movimiento.LBLempujarArriba = gtk_label_new(" empujar Arriba ");
    camelloJ1.movimiento.LBLempujarArriba  = gtk_label_new(" empujar Arriba ");
    caballo1J1.movimiento.LBLempujarArriba = gtk_label_new(" empujar Arriba ");
    caballo2J1.movimiento.LBLempujarArriba = gtk_label_new(" empujar Arriba ");
    perro1J1.movimiento.LBLempujarArriba   = gtk_label_new(" empujar Arriba ");
    perro2J1.movimiento.LBLempujarArriba   = gtk_label_new(" empujar Arriba ");
    gato1J1.movimiento.LBLempujarArriba    = gtk_label_new(" empujar Arriba ");
    gato2J1.movimiento.LBLempujarArriba    = gtk_label_new(" empujar Arriba ");
    conejo1J1.movimiento.LBLempujarArriba  = gtk_label_new(" empujar Arriba ");
    conejo2J1.movimiento.LBLempujarArriba  = gtk_label_new(" empujar Arriba ");
    conejo3J1.movimiento.LBLempujarArriba  = gtk_label_new(" empujar Arriba ");
    conejo4J1.movimiento.LBLempujarArriba  = gtk_label_new(" empujar Arriba ");
    conejo5J1.movimiento.LBLempujarArriba  = gtk_label_new(" empujar Arriba ");
    conejo6J1.movimiento.LBLempujarArriba  = gtk_label_new(" empujar Arriba ");
    conejo7J1.movimiento.LBLempujarArriba  = gtk_label_new(" empujar Arriba ");
    conejo8J1.movimiento.LBLempujarArriba  = gtk_label_new(" empujar Arriba ");
    elefanteJ2.movimiento.LBLestirarArriba = gtk_label_new(" estirar Arriba ");
    camelloJ2.movimiento.LBLestirarArriba  = gtk_label_new(" estirar Arriba ");
    caballo1J2.movimiento.LBLestirarArriba = gtk_label_new(" estirar Arriba ");
    caballo2J2.movimiento.LBLestirarArriba = gtk_label_new(" estirar Arriba ");
    perro1J2.movimiento.LBLestirarArriba   = gtk_label_new(" estirar Arriba ");
    perro2J2.movimiento.LBLestirarArriba   = gtk_label_new(" estirar Arriba ");
    gato1J2.movimiento.LBLestirarArriba    = gtk_label_new(" estirar Arriba ");
    gato2J2.movimiento.LBLestirarArriba    = gtk_label_new(" estirar Arriba ");
    conejo1J2.movimiento.LBLestirarArriba  = gtk_label_new(" estirar Arriba ");
    conejo2J2.movimiento.LBLestirarArriba  = gtk_label_new(" estirar Arriba ");
    conejo3J2.movimiento.LBLestirarArriba  = gtk_label_new(" estirar Arriba ");
    conejo4J2.movimiento.LBLestirarArriba  = gtk_label_new(" estirar Arriba ");
    conejo5J2.movimiento.LBLestirarArriba  = gtk_label_new(" estirar Arriba ");
    conejo6J2.movimiento.LBLestirarArriba  = gtk_label_new(" estirar Arriba ");
    conejo7J2.movimiento.LBLestirarArriba  = gtk_label_new(" estirar Arriba ");
    conejo8J2.movimiento.LBLestirarArriba  = gtk_label_new(" estirar Arriba ");

//Creando caja contenedora BOX para MOVER ARRIBA y EMPUJAR ARRIBA de todas las piezas
    elefanteJ1.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    elefanteJ2.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    camelloJ1.movimiento.BOXmoverArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    camelloJ2.movimiento.BOXmoverArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo1J1.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo1J2.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo2J1.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo2J2.movimiento.BOXmoverArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro1J1.movimiento.BOXmoverArriba   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro1J2.movimiento.BOXmoverArriba   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro2J1.movimiento.BOXmoverArriba   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro2J2.movimiento.BOXmoverArriba   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato1J1.movimiento.BOXmoverArriba    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato1J2.movimiento.BOXmoverArriba    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato2J1.movimiento.BOXmoverArriba    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato2J2.movimiento.BOXmoverArriba    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo1J1.movimiento.BOXmoverArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo1J2.movimiento.BOXmoverArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo2J1.movimiento.BOXmoverArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo2J2.movimiento.BOXmoverArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo3J1.movimiento.BOXmoverArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo3J2.movimiento.BOXmoverArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo4J1.movimiento.BOXmoverArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo4J2.movimiento.BOXmoverArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo5J1.movimiento.BOXmoverArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo5J2.movimiento.BOXmoverArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo6J1.movimiento.BOXmoverArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo6J2.movimiento.BOXmoverArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo7J1.movimiento.BOXmoverArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo7J2.movimiento.BOXmoverArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo8J1.movimiento.BOXmoverArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo8J2.movimiento.BOXmoverArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    elefanteJ1.movimiento.BOXempujarArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    camelloJ1.movimiento.BOXempujarArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo1J1.movimiento.BOXempujarArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo2J1.movimiento.BOXempujarArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro1J1.movimiento.BOXempujarArriba   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro2J1.movimiento.BOXempujarArriba   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato1J1.movimiento.BOXempujarArriba    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato2J1.movimiento.BOXempujarArriba    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo1J1.movimiento.BOXempujarArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo2J1.movimiento.BOXempujarArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo3J1.movimiento.BOXempujarArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo4J1.movimiento.BOXempujarArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo5J1.movimiento.BOXempujarArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo6J1.movimiento.BOXempujarArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo7J1.movimiento.BOXempujarArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo8J1.movimiento.BOXempujarArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    elefanteJ2.movimiento.BOXestirarArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    camelloJ2.movimiento.BOXestirarArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo1J2.movimiento.BOXestirarArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo2J2.movimiento.BOXestirarArriba = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro1J2.movimiento.BOXestirarArriba   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro2J2.movimiento.BOXestirarArriba   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato1J2.movimiento.BOXestirarArriba    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato2J2.movimiento.BOXestirarArriba    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo1J2.movimiento.BOXestirarArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo2J2.movimiento.BOXestirarArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo3J2.movimiento.BOXestirarArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo4J2.movimiento.BOXestirarArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo5J2.movimiento.BOXestirarArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo6J2.movimiento.BOXestirarArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo7J2.movimiento.BOXestirarArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo8J2.movimiento.BOXestirarArriba  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

//Cargando los iconos a la caja contenedora BOX
    gtk_container_add(GTK_CONTAINER(elefanteJ1.movimiento.BOXmoverArriba) ,  elefanteJ1.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(elefanteJ2.movimiento.BOXmoverArriba) ,  elefanteJ2.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(camelloJ1.movimiento.BOXmoverArriba)  ,  camelloJ1.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(camelloJ2.movimiento.BOXmoverArriba)  ,  camelloJ2.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(caballo1J1.movimiento.BOXmoverArriba) ,  caballo1J1.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(caballo1J2.movimiento.BOXmoverArriba) ,  caballo1J2.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(caballo2J1.movimiento.BOXmoverArriba) ,  caballo2J1.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(caballo2J2.movimiento.BOXmoverArriba) ,  caballo2J2.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(perro1J1.movimiento.BOXmoverArriba)   ,  perro1J1.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(perro1J2.movimiento.BOXmoverArriba)   ,  perro1J2.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(perro2J1.movimiento.BOXmoverArriba)   ,  perro2J1.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(perro2J2.movimiento.BOXmoverArriba)   ,  perro2J2.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(gato1J1.movimiento.BOXmoverArriba)    ,  gato1J1.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(gato1J2.movimiento.BOXmoverArriba)    ,  gato1J2.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(gato2J1.movimiento.BOXmoverArriba)    ,  gato2J1.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(gato2J2.movimiento.BOXmoverArriba)    ,  gato2J2.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo1J1.movimiento.BOXmoverArriba)  ,  conejo1J1.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo1J2.movimiento.BOXmoverArriba)  ,  conejo1J2.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo2J1.movimiento.BOXmoverArriba)  ,  conejo2J1.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo2J2.movimiento.BOXmoverArriba)  ,  conejo2J2.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo3J1.movimiento.BOXmoverArriba)  ,  conejo3J1.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo3J2.movimiento.BOXmoverArriba)  ,  conejo3J2.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo4J1.movimiento.BOXmoverArriba)  ,  conejo4J1.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo4J2.movimiento.BOXmoverArriba)  ,  conejo4J2.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo5J1.movimiento.BOXmoverArriba)  ,  conejo5J1.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo5J2.movimiento.BOXmoverArriba)  ,  conejo5J2.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo6J1.movimiento.BOXmoverArriba)  ,  conejo6J1.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo6J2.movimiento.BOXmoverArriba)  ,  conejo6J2.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo7J1.movimiento.BOXmoverArriba)  ,  conejo7J1.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo7J2.movimiento.BOXmoverArriba)  ,  conejo7J2.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo8J1.movimiento.BOXmoverArriba)  ,  conejo8J1.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo8J2.movimiento.BOXmoverArriba)  ,  conejo8J2.movimiento.ICOmoverArriba);
    gtk_container_add(GTK_CONTAINER(elefanteJ1.movimiento.BOXempujarArriba) ,  elefanteJ1.movimiento.ICOempujarArriba);
    gtk_container_add(GTK_CONTAINER(camelloJ1.movimiento.BOXempujarArriba)  ,  camelloJ1.movimiento.ICOempujarArriba);
    gtk_container_add(GTK_CONTAINER(caballo1J1.movimiento.BOXempujarArriba) ,  caballo1J1.movimiento.ICOempujarArriba);
    gtk_container_add(GTK_CONTAINER(caballo2J1.movimiento.BOXempujarArriba) ,  caballo2J1.movimiento.ICOempujarArriba);
    gtk_container_add(GTK_CONTAINER(perro1J1.movimiento.BOXempujarArriba)   ,  perro1J1.movimiento.ICOempujarArriba);
    gtk_container_add(GTK_CONTAINER(perro2J1.movimiento.BOXempujarArriba)   ,  perro2J1.movimiento.ICOempujarArriba);
    gtk_container_add(GTK_CONTAINER(gato1J1.movimiento.BOXempujarArriba)    ,  gato1J1.movimiento.ICOempujarArriba);
    gtk_container_add(GTK_CONTAINER(gato2J1.movimiento.BOXempujarArriba)    ,  gato2J1.movimiento.ICOempujarArriba);
    gtk_container_add(GTK_CONTAINER(conejo1J1.movimiento.BOXempujarArriba)  ,  conejo1J1.movimiento.ICOempujarArriba);
    gtk_container_add(GTK_CONTAINER(conejo2J1.movimiento.BOXempujarArriba)  ,  conejo2J1.movimiento.ICOempujarArriba);
    gtk_container_add(GTK_CONTAINER(conejo3J1.movimiento.BOXempujarArriba)  ,  conejo3J1.movimiento.ICOempujarArriba);
    gtk_container_add(GTK_CONTAINER(conejo4J1.movimiento.BOXempujarArriba)  ,  conejo4J1.movimiento.ICOempujarArriba);
    gtk_container_add(GTK_CONTAINER(conejo5J1.movimiento.BOXempujarArriba)  ,  conejo5J1.movimiento.ICOempujarArriba);
    gtk_container_add(GTK_CONTAINER(conejo6J1.movimiento.BOXempujarArriba)  ,  conejo6J1.movimiento.ICOempujarArriba);
    gtk_container_add(GTK_CONTAINER(conejo7J1.movimiento.BOXempujarArriba)  ,  conejo7J1.movimiento.ICOempujarArriba);
    gtk_container_add(GTK_CONTAINER(conejo8J1.movimiento.BOXempujarArriba)  ,  conejo8J1.movimiento.ICOempujarArriba);
    gtk_container_add(GTK_CONTAINER(elefanteJ2.movimiento.BOXestirarArriba) ,  elefanteJ2.movimiento.ICOestirarArriba);
    gtk_container_add(GTK_CONTAINER(camelloJ2.movimiento.BOXestirarArriba)  ,  camelloJ2.movimiento.ICOestirarArriba);
    gtk_container_add(GTK_CONTAINER(caballo1J2.movimiento.BOXestirarArriba) ,  caballo1J2.movimiento.ICOestirarArriba);
    gtk_container_add(GTK_CONTAINER(caballo2J2.movimiento.BOXestirarArriba) ,  caballo2J2.movimiento.ICOestirarArriba);
    gtk_container_add(GTK_CONTAINER(perro1J2.movimiento.BOXestirarArriba)   ,  perro1J2.movimiento.ICOestirarArriba);
    gtk_container_add(GTK_CONTAINER(perro2J2.movimiento.BOXestirarArriba)   ,  perro2J2.movimiento.ICOestirarArriba);
    gtk_container_add(GTK_CONTAINER(gato1J2.movimiento.BOXestirarArriba)    ,  gato1J2.movimiento.ICOestirarArriba);
    gtk_container_add(GTK_CONTAINER(gato2J2.movimiento.BOXestirarArriba)    ,  gato2J2.movimiento.ICOestirarArriba);
    gtk_container_add(GTK_CONTAINER(conejo1J2.movimiento.BOXestirarArriba)  ,  conejo1J2.movimiento.ICOestirarArriba);
    gtk_container_add(GTK_CONTAINER(conejo2J2.movimiento.BOXestirarArriba)  ,  conejo2J2.movimiento.ICOestirarArriba);
    gtk_container_add(GTK_CONTAINER(conejo3J2.movimiento.BOXestirarArriba)  ,  conejo3J2.movimiento.ICOestirarArriba);
    gtk_container_add(GTK_CONTAINER(conejo4J2.movimiento.BOXestirarArriba)  ,  conejo4J2.movimiento.ICOestirarArriba);
    gtk_container_add(GTK_CONTAINER(conejo5J2.movimiento.BOXestirarArriba)  ,  conejo5J2.movimiento.ICOestirarArriba);
    gtk_container_add(GTK_CONTAINER(conejo6J2.movimiento.BOXestirarArriba)  ,  conejo6J2.movimiento.ICOestirarArriba);
    gtk_container_add(GTK_CONTAINER(conejo7J2.movimiento.BOXestirarArriba)  ,  conejo7J2.movimiento.ICOestirarArriba);
    gtk_container_add(GTK_CONTAINER(conejo8J2.movimiento.BOXestirarArriba)  ,  conejo8J2.movimiento.ICOestirarArriba);

//Cargando los Labels a la caja contenedora BOX
    gtk_container_add(GTK_CONTAINER(elefanteJ1.movimiento.BOXmoverArriba) ,  elefanteJ1.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(elefanteJ2.movimiento.BOXmoverArriba) ,  elefanteJ2.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(camelloJ1.movimiento.BOXmoverArriba)  ,  camelloJ1.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(camelloJ2.movimiento.BOXmoverArriba)  ,  camelloJ2.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(caballo1J1.movimiento.BOXmoverArriba) ,  caballo1J1.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(caballo1J2.movimiento.BOXmoverArriba) ,  caballo1J2.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(caballo2J1.movimiento.BOXmoverArriba) ,  caballo2J1.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(caballo2J2.movimiento.BOXmoverArriba) ,  caballo2J2.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(perro1J1.movimiento.BOXmoverArriba)   ,  perro1J1.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(perro1J2.movimiento.BOXmoverArriba)   ,  perro1J2.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(perro2J1.movimiento.BOXmoverArriba)   ,  perro2J1.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(perro2J2.movimiento.BOXmoverArriba)   ,  perro2J2.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(gato1J1.movimiento.BOXmoverArriba)    ,  gato1J1.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(gato1J2.movimiento.BOXmoverArriba)    ,  gato1J2.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(gato2J1.movimiento.BOXmoverArriba)    ,  gato2J1.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(gato2J2.movimiento.BOXmoverArriba)    ,  gato2J2.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo1J1.movimiento.BOXmoverArriba)  ,  conejo1J1.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo1J2.movimiento.BOXmoverArriba)  ,  conejo1J2.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo2J1.movimiento.BOXmoverArriba)  ,  conejo2J1.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo2J2.movimiento.BOXmoverArriba)  ,  conejo2J2.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo3J1.movimiento.BOXmoverArriba)  ,  conejo3J1.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo3J2.movimiento.BOXmoverArriba)  ,  conejo3J2.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo4J1.movimiento.BOXmoverArriba)  ,  conejo4J1.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo4J2.movimiento.BOXmoverArriba)  ,  conejo4J2.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo5J1.movimiento.BOXmoverArriba)  ,  conejo5J1.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo5J2.movimiento.BOXmoverArriba)  ,  conejo5J2.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo6J1.movimiento.BOXmoverArriba)  ,  conejo6J1.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo6J2.movimiento.BOXmoverArriba)  ,  conejo6J2.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo7J1.movimiento.BOXmoverArriba)  ,  conejo7J1.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo7J2.movimiento.BOXmoverArriba)  ,  conejo7J2.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo8J1.movimiento.BOXmoverArriba)  ,  conejo8J1.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo8J2.movimiento.BOXmoverArriba)  ,  conejo8J2.movimiento.LBLmoverArriba);
    gtk_container_add(GTK_CONTAINER(elefanteJ1.movimiento.BOXempujarArriba) ,  elefanteJ1.movimiento.LBLempujarArriba);
    gtk_container_add(GTK_CONTAINER(camelloJ1.movimiento.BOXempujarArriba)  ,  camelloJ1.movimiento.LBLempujarArriba);
    gtk_container_add(GTK_CONTAINER(caballo1J1.movimiento.BOXempujarArriba) ,  caballo1J1.movimiento.LBLempujarArriba);
    gtk_container_add(GTK_CONTAINER(caballo2J1.movimiento.BOXempujarArriba) ,  caballo2J1.movimiento.LBLempujarArriba);
    gtk_container_add(GTK_CONTAINER(perro1J1.movimiento.BOXempujarArriba)   ,  perro1J1.movimiento.LBLempujarArriba);
    gtk_container_add(GTK_CONTAINER(perro2J1.movimiento.BOXempujarArriba)   ,  perro2J1.movimiento.LBLempujarArriba);
    gtk_container_add(GTK_CONTAINER(gato1J1.movimiento.BOXempujarArriba)    ,  gato1J1.movimiento.LBLempujarArriba);
    gtk_container_add(GTK_CONTAINER(gato2J1.movimiento.BOXempujarArriba)    ,  gato2J1.movimiento.LBLempujarArriba);
    gtk_container_add(GTK_CONTAINER(conejo1J1.movimiento.BOXempujarArriba)  ,  conejo1J1.movimiento.LBLempujarArriba);
    gtk_container_add(GTK_CONTAINER(conejo2J1.movimiento.BOXempujarArriba)  ,  conejo2J1.movimiento.LBLempujarArriba);
    gtk_container_add(GTK_CONTAINER(conejo3J1.movimiento.BOXempujarArriba)  ,  conejo3J1.movimiento.LBLempujarArriba);
    gtk_container_add(GTK_CONTAINER(conejo4J1.movimiento.BOXempujarArriba)  ,  conejo4J1.movimiento.LBLempujarArriba);
    gtk_container_add(GTK_CONTAINER(conejo5J1.movimiento.BOXempujarArriba)  ,  conejo5J1.movimiento.LBLempujarArriba);
    gtk_container_add(GTK_CONTAINER(conejo6J1.movimiento.BOXempujarArriba)  ,  conejo6J1.movimiento.LBLempujarArriba);
    gtk_container_add(GTK_CONTAINER(conejo7J1.movimiento.BOXempujarArriba)  ,  conejo7J1.movimiento.LBLempujarArriba);
    gtk_container_add(GTK_CONTAINER(conejo8J1.movimiento.BOXempujarArriba)  ,  conejo8J1.movimiento.LBLempujarArriba);
    gtk_container_add(GTK_CONTAINER(elefanteJ2.movimiento.BOXestirarArriba) ,  elefanteJ2.movimiento.LBLestirarArriba);
    gtk_container_add(GTK_CONTAINER(camelloJ2.movimiento.BOXestirarArriba)  ,  camelloJ2.movimiento.LBLestirarArriba);
    gtk_container_add(GTK_CONTAINER(caballo1J2.movimiento.BOXestirarArriba) ,  caballo1J2.movimiento.LBLestirarArriba);
    gtk_container_add(GTK_CONTAINER(caballo2J2.movimiento.BOXestirarArriba) ,  caballo2J2.movimiento.LBLestirarArriba);
    gtk_container_add(GTK_CONTAINER(perro1J2.movimiento.BOXestirarArriba)   ,  perro1J2.movimiento.LBLestirarArriba);
    gtk_container_add(GTK_CONTAINER(perro2J2.movimiento.BOXestirarArriba)   ,  perro2J2.movimiento.LBLestirarArriba);
    gtk_container_add(GTK_CONTAINER(gato1J2.movimiento.BOXestirarArriba)    ,  gato1J2.movimiento.LBLestirarArriba);
    gtk_container_add(GTK_CONTAINER(gato2J2.movimiento.BOXestirarArriba)    ,  gato2J2.movimiento.LBLestirarArriba);
    gtk_container_add(GTK_CONTAINER(conejo1J2.movimiento.BOXestirarArriba)  ,  conejo1J2.movimiento.LBLestirarArriba);
    gtk_container_add(GTK_CONTAINER(conejo2J2.movimiento.BOXestirarArriba)  ,  conejo2J2.movimiento.LBLestirarArriba);
    gtk_container_add(GTK_CONTAINER(conejo3J2.movimiento.BOXestirarArriba)  ,  conejo3J2.movimiento.LBLestirarArriba);
    gtk_container_add(GTK_CONTAINER(conejo4J2.movimiento.BOXestirarArriba)  ,  conejo4J2.movimiento.LBLestirarArriba);
    gtk_container_add(GTK_CONTAINER(conejo5J2.movimiento.BOXestirarArriba)  ,  conejo5J2.movimiento.LBLestirarArriba);
    gtk_container_add(GTK_CONTAINER(conejo6J2.movimiento.BOXestirarArriba)  ,  conejo6J2.movimiento.LBLestirarArriba);
    gtk_container_add(GTK_CONTAINER(conejo7J2.movimiento.BOXestirarArriba)  ,  conejo7J2.movimiento.LBLestirarArriba);
    gtk_container_add(GTK_CONTAINER(conejo8J2.movimiento.BOXestirarArriba)  ,  conejo8J2.movimiento.LBLestirarArriba);

//Agragando la caja contenedora BOX a cada menu
    gtk_container_add(GTK_CONTAINER(elefanteJ1.movimiento.OPmoverArriba) ,  elefanteJ1.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(elefanteJ2.movimiento.OPmoverArriba) ,  elefanteJ2.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(camelloJ1.movimiento.OPmoverArriba)  ,  camelloJ1.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(camelloJ2.movimiento.OPmoverArriba)  ,  camelloJ2.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(caballo1J1.movimiento.OPmoverArriba) ,  caballo1J1.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(caballo1J2.movimiento.OPmoverArriba) ,  caballo1J2.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(caballo2J1.movimiento.OPmoverArriba) ,  caballo2J1.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(caballo2J2.movimiento.OPmoverArriba) ,  caballo2J2.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(perro1J1.movimiento.OPmoverArriba)   ,  perro1J1.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(perro1J2.movimiento.OPmoverArriba)   ,  perro1J2.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(perro2J1.movimiento.OPmoverArriba)   ,  perro2J1.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(perro2J2.movimiento.OPmoverArriba)   ,  perro2J2.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(gato1J1.movimiento.OPmoverArriba)    ,  gato1J1.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(gato1J2.movimiento.OPmoverArriba)    ,  gato1J2.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(gato2J1.movimiento.OPmoverArriba)    ,  gato2J1.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(gato2J2.movimiento.OPmoverArriba)    ,  gato2J2.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo1J1.movimiento.OPmoverArriba)  ,  conejo1J1.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo1J2.movimiento.OPmoverArriba)  ,  conejo1J2.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo2J1.movimiento.OPmoverArriba)  ,  conejo2J1.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo2J2.movimiento.OPmoverArriba)  ,  conejo2J2.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo3J1.movimiento.OPmoverArriba)  ,  conejo3J1.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo3J2.movimiento.OPmoverArriba)  ,  conejo3J2.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo4J1.movimiento.OPmoverArriba)  ,  conejo4J1.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo4J2.movimiento.OPmoverArriba)  ,  conejo4J2.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo5J1.movimiento.OPmoverArriba)  ,  conejo5J1.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo5J2.movimiento.OPmoverArriba)  ,  conejo5J2.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo6J1.movimiento.OPmoverArriba)  ,  conejo6J1.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo6J2.movimiento.OPmoverArriba)  ,  conejo6J2.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo7J1.movimiento.OPmoverArriba)  ,  conejo7J1.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo7J2.movimiento.OPmoverArriba)  ,  conejo7J2.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo8J1.movimiento.OPmoverArriba)  ,  conejo8J1.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(conejo8J2.movimiento.OPmoverArriba)  ,  conejo8J2.movimiento.BOXmoverArriba);
    gtk_container_add(GTK_CONTAINER(elefanteJ1.movimiento.OPempujarArriba) ,  elefanteJ1.movimiento.BOXempujarArriba);
    gtk_container_add(GTK_CONTAINER(camelloJ1.movimiento.OPempujarArriba)  ,  camelloJ1.movimiento.BOXempujarArriba);
    gtk_container_add(GTK_CONTAINER(caballo1J1.movimiento.OPempujarArriba) ,  caballo1J1.movimiento.BOXempujarArriba);
    gtk_container_add(GTK_CONTAINER(caballo2J1.movimiento.OPempujarArriba) ,  caballo2J1.movimiento.BOXempujarArriba);
    gtk_container_add(GTK_CONTAINER(perro1J1.movimiento.OPempujarArriba)   ,  perro1J1.movimiento.BOXempujarArriba);
    gtk_container_add(GTK_CONTAINER(perro2J1.movimiento.OPempujarArriba)   ,  perro2J1.movimiento.BOXempujarArriba);
    gtk_container_add(GTK_CONTAINER(gato1J1.movimiento.OPempujarArriba)    ,  gato1J1.movimiento.BOXempujarArriba);
    gtk_container_add(GTK_CONTAINER(gato2J1.movimiento.OPempujarArriba)    ,  gato2J1.movimiento.BOXempujarArriba);
    gtk_container_add(GTK_CONTAINER(conejo1J1.movimiento.OPempujarArriba)  ,  conejo1J1.movimiento.BOXempujarArriba);
    gtk_container_add(GTK_CONTAINER(conejo2J1.movimiento.OPempujarArriba)  ,  conejo2J1.movimiento.BOXempujarArriba);
    gtk_container_add(GTK_CONTAINER(conejo3J1.movimiento.OPempujarArriba)  ,  conejo3J1.movimiento.BOXempujarArriba);
    gtk_container_add(GTK_CONTAINER(conejo4J1.movimiento.OPempujarArriba)  ,  conejo4J1.movimiento.BOXempujarArriba);
    gtk_container_add(GTK_CONTAINER(conejo5J1.movimiento.OPempujarArriba)  ,  conejo5J1.movimiento.BOXempujarArriba);
    gtk_container_add(GTK_CONTAINER(conejo6J1.movimiento.OPempujarArriba)  ,  conejo6J1.movimiento.BOXempujarArriba);
    gtk_container_add(GTK_CONTAINER(conejo7J1.movimiento.OPempujarArriba)  ,  conejo7J1.movimiento.BOXempujarArriba);
    gtk_container_add(GTK_CONTAINER(conejo8J1.movimiento.OPempujarArriba)  ,  conejo8J1.movimiento.BOXempujarArriba);
    gtk_container_add(GTK_CONTAINER(elefanteJ2.movimiento.OPestirarArriba) ,  elefanteJ2.movimiento.BOXestirarArriba);
    gtk_container_add(GTK_CONTAINER(camelloJ2.movimiento.OPestirarArriba)  ,  camelloJ2.movimiento.BOXestirarArriba);
    gtk_container_add(GTK_CONTAINER(caballo1J2.movimiento.OPestirarArriba) ,  caballo1J2.movimiento.BOXestirarArriba);
    gtk_container_add(GTK_CONTAINER(caballo2J2.movimiento.OPestirarArriba) ,  caballo2J2.movimiento.BOXestirarArriba);
    gtk_container_add(GTK_CONTAINER(perro1J2.movimiento.OPestirarArriba)   ,  perro1J2.movimiento.BOXestirarArriba);
    gtk_container_add(GTK_CONTAINER(perro2J2.movimiento.OPestirarArriba)   ,  perro2J2.movimiento.BOXestirarArriba);
    gtk_container_add(GTK_CONTAINER(gato1J2.movimiento.OPestirarArriba)    ,  gato1J2.movimiento.BOXestirarArriba);
    gtk_container_add(GTK_CONTAINER(gato2J2.movimiento.OPestirarArriba)    ,  gato2J2.movimiento.BOXestirarArriba);
    gtk_container_add(GTK_CONTAINER(conejo1J2.movimiento.OPestirarArriba)  ,  conejo1J2.movimiento.BOXestirarArriba);
    gtk_container_add(GTK_CONTAINER(conejo2J2.movimiento.OPestirarArriba)  ,  conejo2J2.movimiento.BOXestirarArriba);
    gtk_container_add(GTK_CONTAINER(conejo3J2.movimiento.OPestirarArriba)  ,  conejo3J2.movimiento.BOXestirarArriba);
    gtk_container_add(GTK_CONTAINER(conejo4J2.movimiento.OPestirarArriba)  ,  conejo4J2.movimiento.BOXestirarArriba);
    gtk_container_add(GTK_CONTAINER(conejo5J2.movimiento.OPestirarArriba)  ,  conejo5J2.movimiento.BOXestirarArriba);
    gtk_container_add(GTK_CONTAINER(conejo6J2.movimiento.OPestirarArriba)  ,  conejo6J2.movimiento.BOXestirarArriba);
    gtk_container_add(GTK_CONTAINER(conejo7J2.movimiento.OPestirarArriba)  ,  conejo7J2.movimiento.BOXestirarArriba);
    gtk_container_add(GTK_CONTAINER(conejo8J2.movimiento.OPestirarArriba)  ,  conejo8J2.movimiento.BOXestirarArriba);

//Cargando iconos MOVER Abajo y EMPUJAR Abajo para todas las piezas
    elefanteJ1.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    elefanteJ2.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    camelloJ1.movimiento.ICOmoverAbajo  = gtk_image_new_from_file("moverAbajo.png");
    camelloJ2.movimiento.ICOmoverAbajo  = gtk_image_new_from_file("moverAbajo.png");
    caballo1J1.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    caballo1J2.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    caballo2J1.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    caballo2J2.movimiento.ICOmoverAbajo = gtk_image_new_from_file("moverAbajo.png");
    perro1J1.movimiento.ICOmoverAbajo   = gtk_image_new_from_file("moverAbajo.png");
    perro1J2.movimiento.ICOmoverAbajo   = gtk_image_new_from_file("moverAbajo.png");
    perro2J1.movimiento.ICOmoverAbajo   = gtk_image_new_from_file("moverAbajo.png");
    perro2J2.movimiento.ICOmoverAbajo   = gtk_image_new_from_file("moverAbajo.png");
    gato1J1.movimiento.ICOmoverAbajo    = gtk_image_new_from_file("moverAbajo.png");
    gato1J2.movimiento.ICOmoverAbajo    = gtk_image_new_from_file("moverAbajo.png");
    gato2J1.movimiento.ICOmoverAbajo    = gtk_image_new_from_file("moverAbajo.png");
    gato2J2.movimiento.ICOmoverAbajo    = gtk_image_new_from_file("moverAbajo.png");
    conejo1J1.movimiento.ICOmoverAbajo  = gtk_image_new_from_file("moverAbajo.png");
    conejo1J2.movimiento.ICOmoverAbajo  = gtk_image_new_from_file("moverAbajo.png");
    conejo2J1.movimiento.ICOmoverAbajo  = gtk_image_new_from_file("moverAbajo.png");
    conejo2J2.movimiento.ICOmoverAbajo  = gtk_image_new_from_file("moverAbajo.png");
    conejo3J1.movimiento.ICOmoverAbajo  = gtk_image_new_from_file("moverAbajo.png");
    conejo3J2.movimiento.ICOmoverAbajo  = gtk_image_new_from_file("moverAbajo.png");
    conejo4J1.movimiento.ICOmoverAbajo  = gtk_image_new_from_file("moverAbajo.png");
    conejo4J2.movimiento.ICOmoverAbajo  = gtk_image_new_from_file("moverAbajo.png");
    conejo5J1.movimiento.ICOmoverAbajo  = gtk_image_new_from_file("moverAbajo.png");
    conejo5J2.movimiento.ICOmoverAbajo  = gtk_image_new_from_file("moverAbajo.png");
    conejo6J1.movimiento.ICOmoverAbajo  = gtk_image_new_from_file("moverAbajo.png");
    conejo6J2.movimiento.ICOmoverAbajo  = gtk_image_new_from_file("moverAbajo.png");
    conejo7J1.movimiento.ICOmoverAbajo  = gtk_image_new_from_file("moverAbajo.png");
    conejo7J2.movimiento.ICOmoverAbajo  = gtk_image_new_from_file("moverAbajo.png");
    conejo8J1.movimiento.ICOmoverAbajo  = gtk_image_new_from_file("moverAbajo.png");
    conejo8J2.movimiento.ICOmoverAbajo  = gtk_image_new_from_file("moverAbajo.png");
    elefanteJ1.movimiento.ICOestirarAbajo = gtk_image_new_from_file("estirarAbajo.png");
    camelloJ1.movimiento.ICOestirarAbajo  = gtk_image_new_from_file("estirarAbajo.png");
    caballo1J1.movimiento.ICOestirarAbajo = gtk_image_new_from_file("estirarAbajo.png");
    caballo2J1.movimiento.ICOestirarAbajo = gtk_image_new_from_file("estirarAbajo.png");
    perro1J1.movimiento.ICOestirarAbajo   = gtk_image_new_from_file("estirarAbajo.png");
    perro2J1.movimiento.ICOestirarAbajo   = gtk_image_new_from_file("estirarAbajo.png");
    gato1J1.movimiento.ICOestirarAbajo    = gtk_image_new_from_file("estirarAbajo.png");
    gato2J1.movimiento.ICOestirarAbajo    = gtk_image_new_from_file("estirarAbajo.png");
    conejo1J1.movimiento.ICOestirarAbajo  = gtk_image_new_from_file("estirarAbajo.png");
    conejo2J1.movimiento.ICOestirarAbajo  = gtk_image_new_from_file("estirarAbajo.png");
    conejo3J1.movimiento.ICOestirarAbajo  = gtk_image_new_from_file("estirarAbajo.png");
    conejo4J1.movimiento.ICOestirarAbajo  = gtk_image_new_from_file("estirarAbajo.png");
    conejo5J1.movimiento.ICOestirarAbajo  = gtk_image_new_from_file("estirarAbajo.png");
    conejo6J1.movimiento.ICOestirarAbajo  = gtk_image_new_from_file("estirarAbajo.png");
    conejo7J1.movimiento.ICOestirarAbajo  = gtk_image_new_from_file("estirarAbajo.png");
    conejo8J1.movimiento.ICOestirarAbajo  = gtk_image_new_from_file("estirarAbajo.png");
    elefanteJ2.movimiento.ICOempujarAbajo = gtk_image_new_from_file("empujarAbajo.png");
    camelloJ2.movimiento.ICOempujarAbajo  = gtk_image_new_from_file("empujarAbajo.png");
    caballo1J2.movimiento.ICOempujarAbajo = gtk_image_new_from_file("empujarAbajo.png");
    caballo2J2.movimiento.ICOempujarAbajo = gtk_image_new_from_file("empujarAbajo.png");
    perro1J2.movimiento.ICOempujarAbajo   = gtk_image_new_from_file("empujarAbajo.png");
    perro2J2.movimiento.ICOempujarAbajo   = gtk_image_new_from_file("empujarAbajo.png");
    gato1J2.movimiento.ICOempujarAbajo    = gtk_image_new_from_file("empujarAbajo.png");
    gato2J2.movimiento.ICOempujarAbajo    = gtk_image_new_from_file("empujarAbajo.png");
    conejo1J2.movimiento.ICOempujarAbajo  = gtk_image_new_from_file("empujarAbajo.png");
    conejo2J2.movimiento.ICOempujarAbajo  = gtk_image_new_from_file("empujarAbajo.png");
    conejo3J2.movimiento.ICOempujarAbajo  = gtk_image_new_from_file("empujarAbajo.png");
    conejo4J2.movimiento.ICOempujarAbajo  = gtk_image_new_from_file("empujarAbajo.png");
    conejo5J2.movimiento.ICOempujarAbajo  = gtk_image_new_from_file("empujarAbajo.png");
    conejo6J2.movimiento.ICOempujarAbajo  = gtk_image_new_from_file("empujarAbajo.png");
    conejo7J2.movimiento.ICOempujarAbajo  = gtk_image_new_from_file("empujarAbajo.png");
    conejo8J2.movimiento.ICOempujarAbajo  = gtk_image_new_from_file("empujarAbajo.png");

//Cargando LABEL MOVER Abajo y EMPUJAR  Abajo para todas las piezas
    elefanteJ1.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    elefanteJ2.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    camelloJ1.movimiento.LBLmoverAbajo  = gtk_label_new(" Mover Abajo ");
    camelloJ2.movimiento.LBLmoverAbajo  = gtk_label_new(" Mover Abajo ");
    caballo1J1.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    caballo1J2.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    caballo2J1.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    caballo2J2.movimiento.LBLmoverAbajo = gtk_label_new(" Mover Abajo ");
    perro1J1.movimiento.LBLmoverAbajo   = gtk_label_new(" Mover Abajo ");
    perro1J2.movimiento.LBLmoverAbajo   = gtk_label_new(" Mover Abajo ");
    perro2J1.movimiento.LBLmoverAbajo   = gtk_label_new(" Mover Abajo ");
    perro2J2.movimiento.LBLmoverAbajo   = gtk_label_new(" Mover Abajo ");
    gato1J1.movimiento.LBLmoverAbajo    = gtk_label_new(" Mover Abajo ");
    gato1J2.movimiento.LBLmoverAbajo    = gtk_label_new(" Mover Abajo ");
    gato2J1.movimiento.LBLmoverAbajo    = gtk_label_new(" Mover Abajo ");
    gato2J2.movimiento.LBLmoverAbajo    = gtk_label_new(" Mover Abajo ");
    conejo1J1.movimiento.LBLmoverAbajo  = gtk_label_new(" Mover Abajo ");
    conejo1J2.movimiento.LBLmoverAbajo  = gtk_label_new(" Mover Abajo ");
    conejo2J1.movimiento.LBLmoverAbajo  = gtk_label_new(" Mover Abajo ");
    conejo2J2.movimiento.LBLmoverAbajo  = gtk_label_new(" Mover Abajo ");
    conejo3J1.movimiento.LBLmoverAbajo  = gtk_label_new(" Mover Abajo ");
    conejo3J2.movimiento.LBLmoverAbajo  = gtk_label_new(" Mover Abajo ");
    conejo4J1.movimiento.LBLmoverAbajo  = gtk_label_new(" Mover Abajo ");
    conejo4J2.movimiento.LBLmoverAbajo  = gtk_label_new(" Mover Abajo ");
    conejo5J1.movimiento.LBLmoverAbajo  = gtk_label_new(" Mover Abajo ");
    conejo5J2.movimiento.LBLmoverAbajo  = gtk_label_new(" Mover Abajo ");
    conejo6J1.movimiento.LBLmoverAbajo  = gtk_label_new(" Mover Abajo ");
    conejo6J2.movimiento.LBLmoverAbajo  = gtk_label_new(" Mover Abajo ");
    conejo7J1.movimiento.LBLmoverAbajo  = gtk_label_new(" Mover Abajo ");
    conejo7J2.movimiento.LBLmoverAbajo  = gtk_label_new(" Mover Abajo ");
    conejo8J1.movimiento.LBLmoverAbajo  = gtk_label_new(" Mover Abajo ");
    conejo8J2.movimiento.LBLmoverAbajo  = gtk_label_new(" Mover Abajo ");
    elefanteJ1.movimiento.LBLestirarAbajo = gtk_label_new(" estirar Abajo ");
    camelloJ1.movimiento.LBLestirarAbajo  = gtk_label_new(" estirar Abajo ");
    caballo1J1.movimiento.LBLestirarAbajo = gtk_label_new(" estirar Abajo ");
    caballo2J1.movimiento.LBLestirarAbajo = gtk_label_new(" estirar Abajo ");
    perro1J1.movimiento.LBLestirarAbajo   = gtk_label_new(" estirar Abajo ");
    perro2J1.movimiento.LBLestirarAbajo   = gtk_label_new(" estirar Abajo ");
    gato1J1.movimiento.LBLestirarAbajo    = gtk_label_new(" estirar Abajo ");
    gato2J1.movimiento.LBLestirarAbajo    = gtk_label_new(" estirar Abajo ");
    conejo1J1.movimiento.LBLestirarAbajo  = gtk_label_new(" estirar Abajo ");
    conejo2J1.movimiento.LBLestirarAbajo  = gtk_label_new(" estirar Abajo ");
    conejo3J1.movimiento.LBLestirarAbajo  = gtk_label_new(" estirar Abajo ");
    conejo4J1.movimiento.LBLestirarAbajo  = gtk_label_new(" estirar Abajo ");
    conejo5J1.movimiento.LBLestirarAbajo  = gtk_label_new(" estirar Abajo ");
    conejo6J1.movimiento.LBLestirarAbajo  = gtk_label_new(" estirar Abajo ");
    conejo7J1.movimiento.LBLestirarAbajo  = gtk_label_new(" estirar Abajo ");
    conejo8J1.movimiento.LBLestirarAbajo  = gtk_label_new(" estirar Abajo ");
    elefanteJ2.movimiento.LBLempujarAbajo = gtk_label_new(" empujar Abajo ");
    camelloJ2.movimiento.LBLempujarAbajo  = gtk_label_new(" empujar Abajo ");
    caballo1J2.movimiento.LBLempujarAbajo = gtk_label_new(" empujar Abajo ");
    caballo2J2.movimiento.LBLempujarAbajo = gtk_label_new(" empujar Abajo ");
    perro1J2.movimiento.LBLempujarAbajo   = gtk_label_new(" empujar Abajo ");
    perro2J2.movimiento.LBLempujarAbajo   = gtk_label_new(" empujar Abajo ");
    gato1J2.movimiento.LBLempujarAbajo    = gtk_label_new(" empujar Abajo ");
    gato2J2.movimiento.LBLempujarAbajo    = gtk_label_new(" empujar Abajo ");
    conejo1J2.movimiento.LBLempujarAbajo  = gtk_label_new(" empujar Abajo ");
    conejo2J2.movimiento.LBLempujarAbajo  = gtk_label_new(" empujar Abajo ");
    conejo3J2.movimiento.LBLempujarAbajo  = gtk_label_new(" empujar Abajo ");
    conejo4J2.movimiento.LBLempujarAbajo  = gtk_label_new(" empujar Abajo ");
    conejo5J2.movimiento.LBLempujarAbajo  = gtk_label_new(" empujar Abajo ");
    conejo6J2.movimiento.LBLempujarAbajo  = gtk_label_new(" empujar Abajo ");
    conejo7J2.movimiento.LBLempujarAbajo  = gtk_label_new(" empujar Abajo ");
    conejo8J2.movimiento.LBLempujarAbajo  = gtk_label_new(" empujar Abajo ");

//Creando caja contenedora BOX para MOVER Abajo y EMPUJAR  abajo de todas las piezas
    elefanteJ1.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    elefanteJ2.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    camelloJ1.movimiento.BOXmoverAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    camelloJ2.movimiento.BOXmoverAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo1J1.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo1J2.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo2J1.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo2J2.movimiento.BOXmoverAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro1J1.movimiento.BOXmoverAbajo   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro1J2.movimiento.BOXmoverAbajo   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro2J1.movimiento.BOXmoverAbajo   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro2J2.movimiento.BOXmoverAbajo   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato1J1.movimiento.BOXmoverAbajo    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato1J2.movimiento.BOXmoverAbajo    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato2J1.movimiento.BOXmoverAbajo    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato2J2.movimiento.BOXmoverAbajo    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo1J1.movimiento.BOXmoverAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo1J2.movimiento.BOXmoverAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo2J1.movimiento.BOXmoverAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo2J2.movimiento.BOXmoverAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo3J1.movimiento.BOXmoverAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo3J2.movimiento.BOXmoverAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo4J1.movimiento.BOXmoverAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo4J2.movimiento.BOXmoverAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo5J1.movimiento.BOXmoverAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo5J2.movimiento.BOXmoverAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo6J1.movimiento.BOXmoverAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo6J2.movimiento.BOXmoverAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo7J1.movimiento.BOXmoverAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo7J2.movimiento.BOXmoverAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo8J1.movimiento.BOXmoverAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo8J2.movimiento.BOXmoverAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    elefanteJ1.movimiento.BOXestirarAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    camelloJ1.movimiento.BOXestirarAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo1J1.movimiento.BOXestirarAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo2J1.movimiento.BOXestirarAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro1J1.movimiento.BOXestirarAbajo   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro2J1.movimiento.BOXestirarAbajo   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato1J1.movimiento.BOXestirarAbajo    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato2J1.movimiento.BOXestirarAbajo    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo1J1.movimiento.BOXestirarAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo2J1.movimiento.BOXestirarAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo3J1.movimiento.BOXestirarAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo4J1.movimiento.BOXestirarAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo5J1.movimiento.BOXestirarAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo6J1.movimiento.BOXestirarAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo7J1.movimiento.BOXestirarAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo8J1.movimiento.BOXestirarAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    elefanteJ2.movimiento.BOXempujarAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    camelloJ2.movimiento.BOXempujarAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo1J2.movimiento.BOXempujarAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo2J2.movimiento.BOXempujarAbajo = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro1J2.movimiento.BOXempujarAbajo   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro2J2.movimiento.BOXempujarAbajo   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato1J2.movimiento.BOXempujarAbajo    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato2J2.movimiento.BOXempujarAbajo    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo1J2.movimiento.BOXempujarAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo2J2.movimiento.BOXempujarAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo3J2.movimiento.BOXempujarAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo4J2.movimiento.BOXempujarAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo5J2.movimiento.BOXempujarAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo6J2.movimiento.BOXempujarAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo7J2.movimiento.BOXempujarAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo8J2.movimiento.BOXempujarAbajo  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

//Cargando los iconos a la caja contenedora BOX
    gtk_container_add(GTK_CONTAINER(elefanteJ1.movimiento.BOXmoverAbajo) ,  elefanteJ1.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(elefanteJ2.movimiento.BOXmoverAbajo) ,  elefanteJ2.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(camelloJ1.movimiento.BOXmoverAbajo)  ,  camelloJ1.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(camelloJ2.movimiento.BOXmoverAbajo)  ,  camelloJ2.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(caballo1J1.movimiento.BOXmoverAbajo) ,  caballo1J1.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(caballo1J2.movimiento.BOXmoverAbajo) ,  caballo1J2.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(caballo2J1.movimiento.BOXmoverAbajo) ,  caballo2J1.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(caballo2J2.movimiento.BOXmoverAbajo) ,  caballo2J2.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(perro1J1.movimiento.BOXmoverAbajo)   ,  perro1J1.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(perro1J2.movimiento.BOXmoverAbajo)   ,  perro1J2.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(perro2J1.movimiento.BOXmoverAbajo)   ,  perro2J1.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(perro2J2.movimiento.BOXmoverAbajo)   ,  perro2J2.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(gato1J1.movimiento.BOXmoverAbajo)    ,  gato1J1.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(gato1J2.movimiento.BOXmoverAbajo)    ,  gato1J2.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(gato2J1.movimiento.BOXmoverAbajo)    ,  gato2J1.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(gato2J2.movimiento.BOXmoverAbajo)    ,  gato2J2.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo1J1.movimiento.BOXmoverAbajo)  ,  conejo1J1.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo1J2.movimiento.BOXmoverAbajo)  ,  conejo1J2.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo2J1.movimiento.BOXmoverAbajo)  ,  conejo2J1.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo2J2.movimiento.BOXmoverAbajo)  ,  conejo2J2.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo3J1.movimiento.BOXmoverAbajo)  ,  conejo3J1.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo3J2.movimiento.BOXmoverAbajo)  ,  conejo3J2.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo4J1.movimiento.BOXmoverAbajo)  ,  conejo4J1.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo4J2.movimiento.BOXmoverAbajo)  ,  conejo4J2.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo5J1.movimiento.BOXmoverAbajo)  ,  conejo5J1.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo5J2.movimiento.BOXmoverAbajo)  ,  conejo5J2.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo6J1.movimiento.BOXmoverAbajo)  ,  conejo6J1.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo6J2.movimiento.BOXmoverAbajo)  ,  conejo6J2.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo7J1.movimiento.BOXmoverAbajo)  ,  conejo7J1.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo7J2.movimiento.BOXmoverAbajo)  ,  conejo7J2.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo8J1.movimiento.BOXmoverAbajo)  ,  conejo8J1.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo8J2.movimiento.BOXmoverAbajo)  ,  conejo8J2.movimiento.ICOmoverAbajo);
    gtk_container_add(GTK_CONTAINER(elefanteJ1.movimiento.BOXestirarAbajo) ,  elefanteJ1.movimiento.ICOestirarAbajo);
    gtk_container_add(GTK_CONTAINER(camelloJ1.movimiento.BOXestirarAbajo)  ,  camelloJ1.movimiento.ICOestirarAbajo);
    gtk_container_add(GTK_CONTAINER(caballo1J1.movimiento.BOXestirarAbajo) ,  caballo1J1.movimiento.ICOestirarAbajo);
    gtk_container_add(GTK_CONTAINER(caballo2J1.movimiento.BOXestirarAbajo) ,  caballo2J1.movimiento.ICOestirarAbajo);
    gtk_container_add(GTK_CONTAINER(perro1J1.movimiento.BOXestirarAbajo)   ,  perro1J1.movimiento.ICOestirarAbajo);
    gtk_container_add(GTK_CONTAINER(perro2J1.movimiento.BOXestirarAbajo)   ,  perro2J1.movimiento.ICOestirarAbajo);
    gtk_container_add(GTK_CONTAINER(gato1J1.movimiento.BOXestirarAbajo)    ,  gato1J1.movimiento.ICOestirarAbajo);
    gtk_container_add(GTK_CONTAINER(gato2J1.movimiento.BOXestirarAbajo)    ,  gato2J1.movimiento.ICOestirarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo1J1.movimiento.BOXestirarAbajo)  ,  conejo1J1.movimiento.ICOestirarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo2J1.movimiento.BOXestirarAbajo)  ,  conejo2J1.movimiento.ICOestirarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo3J1.movimiento.BOXestirarAbajo)  ,  conejo3J1.movimiento.ICOestirarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo4J1.movimiento.BOXestirarAbajo)  ,  conejo4J1.movimiento.ICOestirarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo5J1.movimiento.BOXestirarAbajo)  ,  conejo5J1.movimiento.ICOestirarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo6J1.movimiento.BOXestirarAbajo)  ,  conejo6J1.movimiento.ICOestirarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo7J1.movimiento.BOXestirarAbajo)  ,  conejo7J1.movimiento.ICOestirarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo8J1.movimiento.BOXestirarAbajo)  ,  conejo8J1.movimiento.ICOestirarAbajo);
    gtk_container_add(GTK_CONTAINER(elefanteJ2.movimiento.BOXempujarAbajo) ,  elefanteJ2.movimiento.ICOempujarAbajo);
    gtk_container_add(GTK_CONTAINER(camelloJ2.movimiento.BOXempujarAbajo)  ,  camelloJ2.movimiento.ICOempujarAbajo);
    gtk_container_add(GTK_CONTAINER(caballo1J2.movimiento.BOXempujarAbajo) ,  caballo1J2.movimiento.ICOempujarAbajo);
    gtk_container_add(GTK_CONTAINER(caballo2J2.movimiento.BOXempujarAbajo) ,  caballo2J2.movimiento.ICOempujarAbajo);
    gtk_container_add(GTK_CONTAINER(perro1J2.movimiento.BOXempujarAbajo)   ,  perro1J2.movimiento.ICOempujarAbajo);
    gtk_container_add(GTK_CONTAINER(perro2J2.movimiento.BOXempujarAbajo)   ,  perro2J2.movimiento.ICOempujarAbajo);
    gtk_container_add(GTK_CONTAINER(gato1J2.movimiento.BOXempujarAbajo)    ,  gato1J2.movimiento.ICOempujarAbajo);
    gtk_container_add(GTK_CONTAINER(gato2J2.movimiento.BOXempujarAbajo)    ,  gato2J2.movimiento.ICOempujarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo1J2.movimiento.BOXempujarAbajo)  ,  conejo1J2.movimiento.ICOempujarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo2J2.movimiento.BOXempujarAbajo)  ,  conejo2J2.movimiento.ICOempujarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo3J2.movimiento.BOXempujarAbajo)  ,  conejo3J2.movimiento.ICOempujarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo4J2.movimiento.BOXempujarAbajo)  ,  conejo4J2.movimiento.ICOempujarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo5J2.movimiento.BOXempujarAbajo)  ,  conejo5J2.movimiento.ICOempujarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo6J2.movimiento.BOXempujarAbajo)  ,  conejo6J2.movimiento.ICOempujarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo7J2.movimiento.BOXempujarAbajo)  ,  conejo7J2.movimiento.ICOempujarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo8J2.movimiento.BOXempujarAbajo)  ,  conejo8J2.movimiento.ICOempujarAbajo);

//Cargando los Labels a la caja contenedora BOX
    gtk_container_add(GTK_CONTAINER(elefanteJ1.movimiento.BOXmoverAbajo) ,  elefanteJ1.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(elefanteJ2.movimiento.BOXmoverAbajo) ,  elefanteJ2.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(camelloJ1.movimiento.BOXmoverAbajo)  ,  camelloJ1.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(camelloJ2.movimiento.BOXmoverAbajo)  ,  camelloJ2.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(caballo1J1.movimiento.BOXmoverAbajo) ,  caballo1J1.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(caballo1J2.movimiento.BOXmoverAbajo) ,  caballo1J2.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(caballo2J1.movimiento.BOXmoverAbajo) ,  caballo2J1.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(caballo2J2.movimiento.BOXmoverAbajo) ,  caballo2J2.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(perro1J1.movimiento.BOXmoverAbajo)   ,  perro1J1.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(perro1J2.movimiento.BOXmoverAbajo)   ,  perro1J2.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(perro2J1.movimiento.BOXmoverAbajo)   ,  perro2J1.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(perro2J2.movimiento.BOXmoverAbajo)   ,  perro2J2.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(gato1J1.movimiento.BOXmoverAbajo)    ,  gato1J1.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(gato1J2.movimiento.BOXmoverAbajo)    ,  gato1J2.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(gato2J1.movimiento.BOXmoverAbajo)    ,  gato2J1.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(gato2J2.movimiento.BOXmoverAbajo)    ,  gato2J2.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo1J1.movimiento.BOXmoverAbajo)  ,  conejo1J1.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo1J2.movimiento.BOXmoverAbajo)  ,  conejo1J2.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo2J1.movimiento.BOXmoverAbajo)  ,  conejo2J1.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo2J2.movimiento.BOXmoverAbajo)  ,  conejo2J2.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo3J1.movimiento.BOXmoverAbajo)  ,  conejo3J1.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo3J2.movimiento.BOXmoverAbajo)  ,  conejo3J2.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo4J1.movimiento.BOXmoverAbajo)  ,  conejo4J1.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo4J2.movimiento.BOXmoverAbajo)  ,  conejo4J2.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo5J1.movimiento.BOXmoverAbajo)  ,  conejo5J1.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo5J2.movimiento.BOXmoverAbajo)  ,  conejo5J2.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo6J1.movimiento.BOXmoverAbajo)  ,  conejo6J1.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo6J2.movimiento.BOXmoverAbajo)  ,  conejo6J2.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo7J1.movimiento.BOXmoverAbajo)  ,  conejo7J1.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo7J2.movimiento.BOXmoverAbajo)  ,  conejo7J2.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo8J1.movimiento.BOXmoverAbajo)  ,  conejo8J1.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo8J2.movimiento.BOXmoverAbajo)  ,  conejo8J2.movimiento.LBLmoverAbajo);
    gtk_container_add(GTK_CONTAINER(elefanteJ1.movimiento.BOXestirarAbajo) ,  elefanteJ1.movimiento.LBLestirarAbajo);
    gtk_container_add(GTK_CONTAINER(camelloJ1.movimiento.BOXestirarAbajo)  ,  camelloJ1.movimiento.LBLestirarAbajo);
    gtk_container_add(GTK_CONTAINER(caballo1J1.movimiento.BOXestirarAbajo) ,  caballo1J1.movimiento.LBLestirarAbajo);
    gtk_container_add(GTK_CONTAINER(caballo2J1.movimiento.BOXestirarAbajo) ,  caballo2J1.movimiento.LBLestirarAbajo);
    gtk_container_add(GTK_CONTAINER(perro1J1.movimiento.BOXestirarAbajo)   ,  perro1J1.movimiento.LBLestirarAbajo);
    gtk_container_add(GTK_CONTAINER(perro2J1.movimiento.BOXestirarAbajo)   ,  perro2J1.movimiento.LBLestirarAbajo);
    gtk_container_add(GTK_CONTAINER(gato1J1.movimiento.BOXestirarAbajo)    ,  gato1J1.movimiento.LBLestirarAbajo);
    gtk_container_add(GTK_CONTAINER(gato2J1.movimiento.BOXestirarAbajo)    ,  gato2J1.movimiento.LBLestirarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo1J1.movimiento.BOXestirarAbajo)  ,  conejo1J1.movimiento.LBLestirarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo2J1.movimiento.BOXestirarAbajo)  ,  conejo2J1.movimiento.LBLestirarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo3J1.movimiento.BOXestirarAbajo)  ,  conejo3J1.movimiento.LBLestirarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo4J1.movimiento.BOXestirarAbajo)  ,  conejo4J1.movimiento.LBLestirarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo5J1.movimiento.BOXestirarAbajo)  ,  conejo5J1.movimiento.LBLestirarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo6J1.movimiento.BOXestirarAbajo)  ,  conejo6J1.movimiento.LBLestirarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo7J1.movimiento.BOXestirarAbajo)  ,  conejo7J1.movimiento.LBLestirarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo8J1.movimiento.BOXestirarAbajo)  ,  conejo8J1.movimiento.LBLestirarAbajo);
    gtk_container_add(GTK_CONTAINER(elefanteJ2.movimiento.BOXempujarAbajo) ,  elefanteJ2.movimiento.LBLempujarAbajo);
    gtk_container_add(GTK_CONTAINER(camelloJ2.movimiento.BOXempujarAbajo)  ,  camelloJ2.movimiento.LBLempujarAbajo);
    gtk_container_add(GTK_CONTAINER(caballo1J2.movimiento.BOXempujarAbajo) ,  caballo1J2.movimiento.LBLempujarAbajo);
    gtk_container_add(GTK_CONTAINER(caballo2J2.movimiento.BOXempujarAbajo) ,  caballo2J2.movimiento.LBLempujarAbajo);
    gtk_container_add(GTK_CONTAINER(perro1J2.movimiento.BOXempujarAbajo)   ,  perro1J2.movimiento.LBLempujarAbajo);
    gtk_container_add(GTK_CONTAINER(perro2J2.movimiento.BOXempujarAbajo)   ,  perro2J2.movimiento.LBLempujarAbajo);
    gtk_container_add(GTK_CONTAINER(gato1J2.movimiento.BOXempujarAbajo)    ,  gato1J2.movimiento.LBLempujarAbajo);
    gtk_container_add(GTK_CONTAINER(gato2J2.movimiento.BOXempujarAbajo)    ,  gato2J2.movimiento.LBLempujarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo1J2.movimiento.BOXempujarAbajo)  ,  conejo1J2.movimiento.LBLempujarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo2J2.movimiento.BOXempujarAbajo)  ,  conejo2J2.movimiento.LBLempujarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo3J2.movimiento.BOXempujarAbajo)  ,  conejo3J2.movimiento.LBLempujarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo4J2.movimiento.BOXempujarAbajo)  ,  conejo4J2.movimiento.LBLempujarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo5J2.movimiento.BOXempujarAbajo)  ,  conejo5J2.movimiento.LBLempujarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo6J2.movimiento.BOXempujarAbajo)  ,  conejo6J2.movimiento.LBLempujarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo7J2.movimiento.BOXempujarAbajo)  ,  conejo7J2.movimiento.LBLempujarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo8J2.movimiento.BOXempujarAbajo)  ,  conejo8J2.movimiento.LBLempujarAbajo);

//Agragando la caja contenedora BOX a cada menu
    gtk_container_add(GTK_CONTAINER(elefanteJ1.movimiento.OPmoverAbajo) ,  elefanteJ1.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(elefanteJ2.movimiento.OPmoverAbajo) ,  elefanteJ2.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(camelloJ1.movimiento.OPmoverAbajo)  ,  camelloJ1.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(camelloJ2.movimiento.OPmoverAbajo)  ,  camelloJ2.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(caballo1J1.movimiento.OPmoverAbajo) ,  caballo1J1.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(caballo1J2.movimiento.OPmoverAbajo) ,  caballo1J2.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(caballo2J1.movimiento.OPmoverAbajo) ,  caballo2J1.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(caballo2J2.movimiento.OPmoverAbajo) ,  caballo2J2.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(perro1J1.movimiento.OPmoverAbajo)   ,  perro1J1.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(perro1J2.movimiento.OPmoverAbajo)   ,  perro1J2.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(perro2J1.movimiento.OPmoverAbajo)   ,  perro2J1.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(perro2J2.movimiento.OPmoverAbajo)   ,  perro2J2.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(gato1J1.movimiento.OPmoverAbajo)    ,  gato1J1.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(gato1J2.movimiento.OPmoverAbajo)    ,  gato1J2.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(gato2J1.movimiento.OPmoverAbajo)    ,  gato2J1.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(gato2J2.movimiento.OPmoverAbajo)    ,  gato2J2.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo1J1.movimiento.OPmoverAbajo)  ,  conejo1J1.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo1J2.movimiento.OPmoverAbajo)  ,  conejo1J2.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo2J1.movimiento.OPmoverAbajo)  ,  conejo2J1.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo2J2.movimiento.OPmoverAbajo)  ,  conejo2J2.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo3J1.movimiento.OPmoverAbajo)  ,  conejo3J1.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo3J2.movimiento.OPmoverAbajo)  ,  conejo3J2.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo4J1.movimiento.OPmoverAbajo)  ,  conejo4J1.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo4J2.movimiento.OPmoverAbajo)  ,  conejo4J2.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo5J1.movimiento.OPmoverAbajo)  ,  conejo5J1.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo5J2.movimiento.OPmoverAbajo)  ,  conejo5J2.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo6J1.movimiento.OPmoverAbajo)  ,  conejo6J1.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo6J2.movimiento.OPmoverAbajo)  ,  conejo6J2.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo7J1.movimiento.OPmoverAbajo)  ,  conejo7J1.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo7J2.movimiento.OPmoverAbajo)  ,  conejo7J2.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo8J1.movimiento.OPmoverAbajo)  ,  conejo8J1.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(conejo8J2.movimiento.OPmoverAbajo)  ,  conejo8J2.movimiento.BOXmoverAbajo);
    gtk_container_add(GTK_CONTAINER(elefanteJ1.movimiento.OPestirarAbajo) ,  elefanteJ1.movimiento.BOXestirarAbajo);
    gtk_container_add(GTK_CONTAINER(camelloJ1.movimiento.OPestirarAbajo)  ,  camelloJ1.movimiento.BOXestirarAbajo);
    gtk_container_add(GTK_CONTAINER(caballo1J1.movimiento.OPestirarAbajo) ,  caballo1J1.movimiento.BOXestirarAbajo);
    gtk_container_add(GTK_CONTAINER(caballo2J1.movimiento.OPestirarAbajo) ,  caballo2J1.movimiento.BOXestirarAbajo);
    gtk_container_add(GTK_CONTAINER(perro1J1.movimiento.OPestirarAbajo)   ,  perro1J1.movimiento.BOXestirarAbajo);
    gtk_container_add(GTK_CONTAINER(perro2J1.movimiento.OPestirarAbajo)   ,  perro2J1.movimiento.BOXestirarAbajo);
    gtk_container_add(GTK_CONTAINER(gato1J1.movimiento.OPestirarAbajo)    ,  gato1J1.movimiento.BOXestirarAbajo);
    gtk_container_add(GTK_CONTAINER(gato2J1.movimiento.OPestirarAbajo)    ,  gato2J1.movimiento.BOXestirarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo1J1.movimiento.OPestirarAbajo)  ,  conejo1J1.movimiento.BOXestirarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo2J1.movimiento.OPestirarAbajo)  ,  conejo2J1.movimiento.BOXestirarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo3J1.movimiento.OPestirarAbajo)  ,  conejo3J1.movimiento.BOXestirarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo4J1.movimiento.OPestirarAbajo)  ,  conejo4J1.movimiento.BOXestirarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo5J1.movimiento.OPestirarAbajo)  ,  conejo5J1.movimiento.BOXestirarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo6J1.movimiento.OPestirarAbajo)  ,  conejo6J1.movimiento.BOXestirarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo7J1.movimiento.OPestirarAbajo)  ,  conejo7J1.movimiento.BOXestirarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo8J1.movimiento.OPestirarAbajo)  ,  conejo8J1.movimiento.BOXestirarAbajo);
    gtk_container_add(GTK_CONTAINER(elefanteJ2.movimiento.OPempujarAbajo) ,  elefanteJ2.movimiento.BOXempujarAbajo);
    gtk_container_add(GTK_CONTAINER(camelloJ2.movimiento.OPempujarAbajo)  ,  camelloJ2.movimiento.BOXempujarAbajo);
    gtk_container_add(GTK_CONTAINER(caballo1J2.movimiento.OPempujarAbajo) ,  caballo1J2.movimiento.BOXempujarAbajo);
    gtk_container_add(GTK_CONTAINER(caballo2J2.movimiento.OPempujarAbajo) ,  caballo2J2.movimiento.BOXempujarAbajo);
    gtk_container_add(GTK_CONTAINER(perro1J2.movimiento.OPempujarAbajo)   ,  perro1J2.movimiento.BOXempujarAbajo);
    gtk_container_add(GTK_CONTAINER(perro2J2.movimiento.OPempujarAbajo)   ,  perro2J2.movimiento.BOXempujarAbajo);
    gtk_container_add(GTK_CONTAINER(gato1J2.movimiento.OPempujarAbajo)    ,  gato1J2.movimiento.BOXempujarAbajo);
    gtk_container_add(GTK_CONTAINER(gato2J2.movimiento.OPempujarAbajo)    ,  gato2J2.movimiento.BOXempujarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo1J2.movimiento.OPempujarAbajo)  ,  conejo1J2.movimiento.BOXempujarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo2J2.movimiento.OPempujarAbajo)  ,  conejo2J2.movimiento.BOXempujarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo3J2.movimiento.OPempujarAbajo)  ,  conejo3J2.movimiento.BOXempujarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo4J2.movimiento.OPempujarAbajo)  ,  conejo4J2.movimiento.BOXempujarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo5J2.movimiento.OPempujarAbajo)  ,  conejo5J2.movimiento.BOXempujarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo6J2.movimiento.OPempujarAbajo)  ,  conejo6J2.movimiento.BOXempujarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo7J2.movimiento.OPempujarAbajo)  ,  conejo7J2.movimiento.BOXempujarAbajo);
    gtk_container_add(GTK_CONTAINER(conejo8J2.movimiento.OPempujarAbajo)  ,  conejo8J2.movimiento.BOXempujarAbajo);


//Cargando iconos MOVER Derecha y EMPUJAR Derecha para todas las piezas
    elefanteJ1.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    elefanteJ2.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    camelloJ1.movimiento.ICOmoverDerecha  = gtk_image_new_from_file("moverDerecha.png");
    camelloJ2.movimiento.ICOmoverDerecha  = gtk_image_new_from_file("moverDerecha.png");
    caballo1J1.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    caballo1J2.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    caballo2J1.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    caballo2J2.movimiento.ICOmoverDerecha = gtk_image_new_from_file("moverDerecha.png");
    perro1J1.movimiento.ICOmoverDerecha   = gtk_image_new_from_file("moverDerecha.png");
    perro1J2.movimiento.ICOmoverDerecha   = gtk_image_new_from_file("moverDerecha.png");
    perro2J1.movimiento.ICOmoverDerecha   = gtk_image_new_from_file("moverDerecha.png");
    perro2J2.movimiento.ICOmoverDerecha   = gtk_image_new_from_file("moverDerecha.png");
    gato1J1.movimiento.ICOmoverDerecha    = gtk_image_new_from_file("moverDerecha.png");
    gato1J2.movimiento.ICOmoverDerecha    = gtk_image_new_from_file("moverDerecha.png");
    gato2J1.movimiento.ICOmoverDerecha    = gtk_image_new_from_file("moverDerecha.png");
    gato2J2.movimiento.ICOmoverDerecha    = gtk_image_new_from_file("moverDerecha.png");
    conejo1J1.movimiento.ICOmoverDerecha  = gtk_image_new_from_file("moverDerecha.png");
    conejo1J2.movimiento.ICOmoverDerecha  = gtk_image_new_from_file("moverDerecha.png");
    conejo2J1.movimiento.ICOmoverDerecha  = gtk_image_new_from_file("moverDerecha.png");
    conejo2J2.movimiento.ICOmoverDerecha  = gtk_image_new_from_file("moverDerecha.png");
    conejo3J1.movimiento.ICOmoverDerecha  = gtk_image_new_from_file("moverDerecha.png");
    conejo3J2.movimiento.ICOmoverDerecha  = gtk_image_new_from_file("moverDerecha.png");
    conejo4J1.movimiento.ICOmoverDerecha  = gtk_image_new_from_file("moverDerecha.png");
    conejo4J2.movimiento.ICOmoverDerecha  = gtk_image_new_from_file("moverDerecha.png");
    conejo5J1.movimiento.ICOmoverDerecha  = gtk_image_new_from_file("moverDerecha.png");
    conejo5J2.movimiento.ICOmoverDerecha  = gtk_image_new_from_file("moverDerecha.png");
    conejo6J1.movimiento.ICOmoverDerecha  = gtk_image_new_from_file("moverDerecha.png");
    conejo6J2.movimiento.ICOmoverDerecha  = gtk_image_new_from_file("moverDerecha.png");
    conejo7J1.movimiento.ICOmoverDerecha  = gtk_image_new_from_file("moverDerecha.png");
    conejo7J2.movimiento.ICOmoverDerecha  = gtk_image_new_from_file("moverDerecha.png");
    conejo8J1.movimiento.ICOmoverDerecha  = gtk_image_new_from_file("moverDerecha.png");
    conejo8J2.movimiento.ICOmoverDerecha  = gtk_image_new_from_file("moverDerecha.png");
    elefanteJ1.movimiento.ICOempujarDerecha = gtk_image_new_from_file("empujarDerecha.png");
    elefanteJ2.movimiento.ICOempujarDerecha = gtk_image_new_from_file("empujarDerecha.png");
    camelloJ1.movimiento.ICOempujarDerecha  = gtk_image_new_from_file("empujarDerecha.png");
    camelloJ2.movimiento.ICOempujarDerecha  = gtk_image_new_from_file("empujarDerecha.png");
    caballo1J1.movimiento.ICOempujarDerecha = gtk_image_new_from_file("empujarDerecha.png");
    caballo1J2.movimiento.ICOempujarDerecha = gtk_image_new_from_file("empujarDerecha.png");
    caballo2J1.movimiento.ICOempujarDerecha = gtk_image_new_from_file("empujarDerecha.png");
    caballo2J2.movimiento.ICOempujarDerecha = gtk_image_new_from_file("empujarDerecha.png");
    perro1J1.movimiento.ICOempujarDerecha   = gtk_image_new_from_file("empujarDerecha.png");
    perro1J2.movimiento.ICOempujarDerecha   = gtk_image_new_from_file("empujarDerecha.png");
    perro2J1.movimiento.ICOempujarDerecha   = gtk_image_new_from_file("empujarDerecha.png");
    perro2J2.movimiento.ICOempujarDerecha   = gtk_image_new_from_file("empujarDerecha.png");
    gato1J1.movimiento.ICOempujarDerecha    = gtk_image_new_from_file("empujarDerecha.png");
    gato1J2.movimiento.ICOempujarDerecha    = gtk_image_new_from_file("empujarDerecha.png");
    gato2J1.movimiento.ICOempujarDerecha    = gtk_image_new_from_file("empujarDerecha.png");
    gato2J2.movimiento.ICOempujarDerecha    = gtk_image_new_from_file("empujarDerecha.png");
    conejo1J1.movimiento.ICOempujarDerecha  = gtk_image_new_from_file("empujarDerecha.png");
    conejo1J2.movimiento.ICOempujarDerecha  = gtk_image_new_from_file("empujarDerecha.png");
    conejo2J1.movimiento.ICOempujarDerecha  = gtk_image_new_from_file("empujarDerecha.png");
    conejo2J2.movimiento.ICOempujarDerecha  = gtk_image_new_from_file("empujarDerecha.png");
    conejo3J1.movimiento.ICOempujarDerecha  = gtk_image_new_from_file("empujarDerecha.png");
    conejo3J2.movimiento.ICOempujarDerecha  = gtk_image_new_from_file("empujarDerecha.png");
    conejo4J1.movimiento.ICOempujarDerecha  = gtk_image_new_from_file("empujarDerecha.png");
    conejo4J2.movimiento.ICOempujarDerecha  = gtk_image_new_from_file("empujarDerecha.png");
    conejo5J1.movimiento.ICOempujarDerecha  = gtk_image_new_from_file("empujarDerecha.png");
    conejo5J2.movimiento.ICOempujarDerecha  = gtk_image_new_from_file("empujarDerecha.png");
    conejo6J1.movimiento.ICOempujarDerecha  = gtk_image_new_from_file("empujarDerecha.png");
    conejo6J2.movimiento.ICOempujarDerecha  = gtk_image_new_from_file("empujarDerecha.png");
    conejo7J1.movimiento.ICOempujarDerecha  = gtk_image_new_from_file("empujarDerecha.png");
    conejo7J2.movimiento.ICOempujarDerecha  = gtk_image_new_from_file("empujarDerecha.png");
    conejo8J1.movimiento.ICOempujarDerecha  = gtk_image_new_from_file("empujarDerecha.png");
    conejo8J2.movimiento.ICOempujarDerecha  = gtk_image_new_from_file("empujarDerecha.png");

//Cargando LABEL MOVER Derecha y EMPUJAR Derecha para todas las piezas
    elefanteJ1.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    elefanteJ2.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    camelloJ1.movimiento.LBLmoverDerecha  = gtk_label_new(" Mover Derecha ");
    camelloJ2.movimiento.LBLmoverDerecha  = gtk_label_new(" Mover Derecha ");
    caballo1J1.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    caballo1J2.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    caballo2J1.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    caballo2J2.movimiento.LBLmoverDerecha = gtk_label_new(" Mover Derecha ");
    perro1J1.movimiento.LBLmoverDerecha   = gtk_label_new(" Mover Derecha ");
    perro1J2.movimiento.LBLmoverDerecha   = gtk_label_new(" Mover Derecha ");
    perro2J1.movimiento.LBLmoverDerecha   = gtk_label_new(" Mover Derecha ");
    perro2J2.movimiento.LBLmoverDerecha   = gtk_label_new(" Mover Derecha ");
    gato1J1.movimiento.LBLmoverDerecha    = gtk_label_new(" Mover Derecha ");
    gato1J2.movimiento.LBLmoverDerecha    = gtk_label_new(" Mover Derecha ");
    gato2J1.movimiento.LBLmoverDerecha    = gtk_label_new(" Mover Derecha ");
    gato2J2.movimiento.LBLmoverDerecha    = gtk_label_new(" Mover Derecha ");
    conejo1J1.movimiento.LBLmoverDerecha  = gtk_label_new(" Mover Derecha ");
    conejo1J2.movimiento.LBLmoverDerecha  = gtk_label_new(" Mover Derecha ");
    conejo2J1.movimiento.LBLmoverDerecha  = gtk_label_new(" Mover Derecha ");
    conejo2J2.movimiento.LBLmoverDerecha  = gtk_label_new(" Mover Derecha ");
    conejo3J1.movimiento.LBLmoverDerecha  = gtk_label_new(" Mover Derecha ");
    conejo3J2.movimiento.LBLmoverDerecha  = gtk_label_new(" Mover Derecha ");
    conejo4J1.movimiento.LBLmoverDerecha  = gtk_label_new(" Mover Derecha ");
    conejo4J2.movimiento.LBLmoverDerecha  = gtk_label_new(" Mover Derecha ");
    conejo5J1.movimiento.LBLmoverDerecha  = gtk_label_new(" Mover Derecha ");
    conejo5J2.movimiento.LBLmoverDerecha  = gtk_label_new(" Mover Derecha ");
    conejo6J1.movimiento.LBLmoverDerecha  = gtk_label_new(" Mover Derecha ");
    conejo6J2.movimiento.LBLmoverDerecha  = gtk_label_new(" Mover Derecha ");
    conejo7J1.movimiento.LBLmoverDerecha  = gtk_label_new(" Mover Derecha ");
    conejo7J2.movimiento.LBLmoverDerecha  = gtk_label_new(" Mover Derecha ");
    conejo8J1.movimiento.LBLmoverDerecha  = gtk_label_new(" Mover Derecha ");
    conejo8J2.movimiento.LBLmoverDerecha  = gtk_label_new(" Mover Derecha ");
    elefanteJ1.movimiento.LBLempujarDerecha = gtk_label_new(" empujar Derecha ");
    elefanteJ2.movimiento.LBLempujarDerecha = gtk_label_new(" empujar Derecha ");
    camelloJ1.movimiento.LBLempujarDerecha  = gtk_label_new(" empujar Derecha ");
    camelloJ2.movimiento.LBLempujarDerecha  = gtk_label_new(" empujar Derecha ");
    caballo1J1.movimiento.LBLempujarDerecha = gtk_label_new(" empujar Derecha ");
    caballo1J2.movimiento.LBLempujarDerecha = gtk_label_new(" empujar Derecha ");
    caballo2J1.movimiento.LBLempujarDerecha = gtk_label_new(" empujar Derecha ");
    caballo2J2.movimiento.LBLempujarDerecha = gtk_label_new(" empujar Derecha ");
    perro1J1.movimiento.LBLempujarDerecha   = gtk_label_new(" empujar Derecha ");
    perro1J2.movimiento.LBLempujarDerecha   = gtk_label_new(" empujar Derecha ");
    perro2J1.movimiento.LBLempujarDerecha   = gtk_label_new(" empujar Derecha ");
    perro2J2.movimiento.LBLempujarDerecha   = gtk_label_new(" empujar Derecha ");
    gato1J1.movimiento.LBLempujarDerecha    = gtk_label_new(" empujar Derecha ");
    gato1J2.movimiento.LBLempujarDerecha    = gtk_label_new(" empujar Derecha ");
    gato2J1.movimiento.LBLempujarDerecha    = gtk_label_new(" empujar Derecha ");
    gato2J2.movimiento.LBLempujarDerecha    = gtk_label_new(" empujar Derecha ");
    conejo1J1.movimiento.LBLempujarDerecha  = gtk_label_new(" empujar Derecha ");
    conejo1J2.movimiento.LBLempujarDerecha  = gtk_label_new(" empujar Derecha ");
    conejo2J1.movimiento.LBLempujarDerecha  = gtk_label_new(" empujar Derecha ");
    conejo2J2.movimiento.LBLempujarDerecha  = gtk_label_new(" empujar Derecha ");
    conejo3J1.movimiento.LBLempujarDerecha  = gtk_label_new(" empujar Derecha ");
    conejo3J2.movimiento.LBLempujarDerecha  = gtk_label_new(" empujar Derecha ");
    conejo4J1.movimiento.LBLempujarDerecha  = gtk_label_new(" empujar Derecha ");
    conejo4J2.movimiento.LBLempujarDerecha  = gtk_label_new(" empujar Derecha ");
    conejo5J1.movimiento.LBLempujarDerecha  = gtk_label_new(" empujar Derecha ");
    conejo5J2.movimiento.LBLempujarDerecha  = gtk_label_new(" empujar Derecha ");
    conejo6J1.movimiento.LBLempujarDerecha  = gtk_label_new(" empujar Derecha ");
    conejo6J2.movimiento.LBLempujarDerecha  = gtk_label_new(" empujar Derecha ");
    conejo7J1.movimiento.LBLempujarDerecha  = gtk_label_new(" empujar Derecha ");
    conejo7J2.movimiento.LBLempujarDerecha  = gtk_label_new(" empujar Derecha ");
    conejo8J1.movimiento.LBLempujarDerecha  = gtk_label_new(" empujar Derecha ");
    conejo8J2.movimiento.LBLempujarDerecha  = gtk_label_new(" empujar Derecha ");

//Creando caja contenedora BOX para MOVER Derecha y EMPUJAR Derecha de todas las piezas
    elefanteJ1.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    elefanteJ2.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    camelloJ1.movimiento.BOXmoverDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    camelloJ2.movimiento.BOXmoverDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo1J1.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo1J2.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo2J1.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo2J2.movimiento.BOXmoverDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro1J1.movimiento.BOXmoverDerecha   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro1J2.movimiento.BOXmoverDerecha   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro2J1.movimiento.BOXmoverDerecha   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro2J2.movimiento.BOXmoverDerecha   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato1J1.movimiento.BOXmoverDerecha    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato1J2.movimiento.BOXmoverDerecha    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato2J1.movimiento.BOXmoverDerecha    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato2J2.movimiento.BOXmoverDerecha    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo1J1.movimiento.BOXmoverDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo1J2.movimiento.BOXmoverDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo2J1.movimiento.BOXmoverDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo2J2.movimiento.BOXmoverDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo3J1.movimiento.BOXmoverDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo3J2.movimiento.BOXmoverDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo4J1.movimiento.BOXmoverDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo4J2.movimiento.BOXmoverDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo5J1.movimiento.BOXmoverDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo5J2.movimiento.BOXmoverDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo6J1.movimiento.BOXmoverDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo6J2.movimiento.BOXmoverDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo7J1.movimiento.BOXmoverDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo7J2.movimiento.BOXmoverDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo8J1.movimiento.BOXmoverDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo8J2.movimiento.BOXmoverDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    elefanteJ1.movimiento.BOXempujarDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    elefanteJ2.movimiento.BOXempujarDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    camelloJ1.movimiento.BOXempujarDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    camelloJ2.movimiento.BOXempujarDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo1J1.movimiento.BOXempujarDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo1J2.movimiento.BOXempujarDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo2J1.movimiento.BOXempujarDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo2J2.movimiento.BOXempujarDerecha = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro1J1.movimiento.BOXempujarDerecha   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro1J2.movimiento.BOXempujarDerecha   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro2J1.movimiento.BOXempujarDerecha   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro2J2.movimiento.BOXempujarDerecha   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato1J1.movimiento.BOXempujarDerecha    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato1J2.movimiento.BOXempujarDerecha    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato2J1.movimiento.BOXempujarDerecha    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato2J2.movimiento.BOXempujarDerecha    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo1J1.movimiento.BOXempujarDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo1J2.movimiento.BOXempujarDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo2J1.movimiento.BOXempujarDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo2J2.movimiento.BOXempujarDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo3J1.movimiento.BOXempujarDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo3J2.movimiento.BOXempujarDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo4J1.movimiento.BOXempujarDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo4J2.movimiento.BOXempujarDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo5J1.movimiento.BOXempujarDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo5J2.movimiento.BOXempujarDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo6J1.movimiento.BOXempujarDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo6J2.movimiento.BOXempujarDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo7J1.movimiento.BOXempujarDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo7J2.movimiento.BOXempujarDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo8J1.movimiento.BOXempujarDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo8J2.movimiento.BOXempujarDerecha  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

//Cargando los iconos a la caja contenedora BOX
    gtk_container_add(GTK_CONTAINER(elefanteJ1.movimiento.BOXmoverDerecha) ,  elefanteJ1.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(elefanteJ2.movimiento.BOXmoverDerecha) ,  elefanteJ2.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(camelloJ1.movimiento.BOXmoverDerecha)  ,  camelloJ1.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(camelloJ2.movimiento.BOXmoverDerecha)  ,  camelloJ2.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(caballo1J1.movimiento.BOXmoverDerecha) ,  caballo1J1.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(caballo1J2.movimiento.BOXmoverDerecha) ,  caballo1J2.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(caballo2J1.movimiento.BOXmoverDerecha) ,  caballo2J1.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(caballo2J2.movimiento.BOXmoverDerecha) ,  caballo2J2.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(perro1J1.movimiento.BOXmoverDerecha)   ,  perro1J1.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(perro1J2.movimiento.BOXmoverDerecha)   ,  perro1J2.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(perro2J1.movimiento.BOXmoverDerecha)   ,  perro2J1.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(perro2J2.movimiento.BOXmoverDerecha)   ,  perro2J2.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(gato1J1.movimiento.BOXmoverDerecha)    ,  gato1J1.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(gato1J2.movimiento.BOXmoverDerecha)    ,  gato1J2.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(gato2J1.movimiento.BOXmoverDerecha)    ,  gato2J1.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(gato2J2.movimiento.BOXmoverDerecha)    ,  gato2J2.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo1J1.movimiento.BOXmoverDerecha)  ,  conejo1J1.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo1J2.movimiento.BOXmoverDerecha)  ,  conejo1J2.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo2J1.movimiento.BOXmoverDerecha)  ,  conejo2J1.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo2J2.movimiento.BOXmoverDerecha)  ,  conejo2J2.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo3J1.movimiento.BOXmoverDerecha)  ,  conejo3J1.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo3J2.movimiento.BOXmoverDerecha)  ,  conejo3J2.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo4J1.movimiento.BOXmoverDerecha)  ,  conejo4J1.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo4J2.movimiento.BOXmoverDerecha)  ,  conejo4J2.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo5J1.movimiento.BOXmoverDerecha)  ,  conejo5J1.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo5J2.movimiento.BOXmoverDerecha)  ,  conejo5J2.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo6J1.movimiento.BOXmoverDerecha)  ,  conejo6J1.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo6J2.movimiento.BOXmoverDerecha)  ,  conejo6J2.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo7J1.movimiento.BOXmoverDerecha)  ,  conejo7J1.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo7J2.movimiento.BOXmoverDerecha)  ,  conejo7J2.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo8J1.movimiento.BOXmoverDerecha)  ,  conejo8J1.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo8J2.movimiento.BOXmoverDerecha)  ,  conejo8J2.movimiento.ICOmoverDerecha);
    gtk_container_add(GTK_CONTAINER(elefanteJ1.movimiento.BOXempujarDerecha) ,  elefanteJ1.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(elefanteJ2.movimiento.BOXempujarDerecha) ,  elefanteJ2.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(camelloJ1.movimiento.BOXempujarDerecha)  ,  camelloJ1.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(camelloJ2.movimiento.BOXempujarDerecha)  ,  camelloJ2.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(caballo1J1.movimiento.BOXempujarDerecha) ,  caballo1J1.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(caballo1J2.movimiento.BOXempujarDerecha) ,  caballo1J2.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(caballo2J1.movimiento.BOXempujarDerecha) ,  caballo2J1.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(caballo2J2.movimiento.BOXempujarDerecha) ,  caballo2J2.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(perro1J1.movimiento.BOXempujarDerecha)   ,  perro1J1.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(perro1J2.movimiento.BOXempujarDerecha)   ,  perro1J2.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(perro2J1.movimiento.BOXempujarDerecha)   ,  perro2J1.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(perro2J2.movimiento.BOXempujarDerecha)   ,  perro2J2.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(gato1J1.movimiento.BOXempujarDerecha)    ,  gato1J1.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(gato1J2.movimiento.BOXempujarDerecha)    ,  gato1J2.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(gato2J1.movimiento.BOXempujarDerecha)    ,  gato2J1.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(gato2J2.movimiento.BOXempujarDerecha)    ,  gato2J2.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo1J1.movimiento.BOXempujarDerecha)  ,  conejo1J1.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo1J2.movimiento.BOXempujarDerecha)  ,  conejo1J2.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo2J1.movimiento.BOXempujarDerecha)  ,  conejo2J1.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo2J2.movimiento.BOXempujarDerecha)  ,  conejo2J2.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo3J1.movimiento.BOXempujarDerecha)  ,  conejo3J1.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo3J2.movimiento.BOXempujarDerecha)  ,  conejo3J2.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo4J1.movimiento.BOXempujarDerecha)  ,  conejo4J1.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo4J2.movimiento.BOXempujarDerecha)  ,  conejo4J2.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo5J1.movimiento.BOXempujarDerecha)  ,  conejo5J1.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo5J2.movimiento.BOXempujarDerecha)  ,  conejo5J2.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo6J1.movimiento.BOXempujarDerecha)  ,  conejo6J1.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo6J2.movimiento.BOXempujarDerecha)  ,  conejo6J2.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo7J1.movimiento.BOXempujarDerecha)  ,  conejo7J1.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo7J2.movimiento.BOXempujarDerecha)  ,  conejo7J2.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo8J1.movimiento.BOXempujarDerecha)  ,  conejo8J1.movimiento.ICOempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo8J2.movimiento.BOXempujarDerecha)  ,  conejo8J2.movimiento.ICOempujarDerecha);

//Cargando los Labels a la caja contenedora BOX
    gtk_container_add(GTK_CONTAINER(elefanteJ1.movimiento.BOXmoverDerecha) ,  elefanteJ1.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(elefanteJ2.movimiento.BOXmoverDerecha) ,  elefanteJ2.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(camelloJ1.movimiento.BOXmoverDerecha)  ,  camelloJ1.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(camelloJ2.movimiento.BOXmoverDerecha)  ,  camelloJ2.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(caballo1J1.movimiento.BOXmoverDerecha) ,  caballo1J1.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(caballo1J2.movimiento.BOXmoverDerecha) ,  caballo1J2.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(caballo2J1.movimiento.BOXmoverDerecha) ,  caballo2J1.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(caballo2J2.movimiento.BOXmoverDerecha) ,  caballo2J2.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(perro1J1.movimiento.BOXmoverDerecha)   ,  perro1J1.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(perro1J2.movimiento.BOXmoverDerecha)   ,  perro1J2.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(perro2J1.movimiento.BOXmoverDerecha)   ,  perro2J1.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(perro2J2.movimiento.BOXmoverDerecha)   ,  perro2J2.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(gato1J1.movimiento.BOXmoverDerecha)    ,  gato1J1.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(gato1J2.movimiento.BOXmoverDerecha)    ,  gato1J2.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(gato2J1.movimiento.BOXmoverDerecha)    ,  gato2J1.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(gato2J2.movimiento.BOXmoverDerecha)    ,  gato2J2.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo1J1.movimiento.BOXmoverDerecha)  ,  conejo1J1.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo1J2.movimiento.BOXmoverDerecha)  ,  conejo1J2.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo2J1.movimiento.BOXmoverDerecha)  ,  conejo2J1.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo2J2.movimiento.BOXmoverDerecha)  ,  conejo2J2.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo3J1.movimiento.BOXmoverDerecha)  ,  conejo3J1.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo3J2.movimiento.BOXmoverDerecha)  ,  conejo3J2.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo4J1.movimiento.BOXmoverDerecha)  ,  conejo4J1.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo4J2.movimiento.BOXmoverDerecha)  ,  conejo4J2.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo5J1.movimiento.BOXmoverDerecha)  ,  conejo5J1.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo5J2.movimiento.BOXmoverDerecha)  ,  conejo5J2.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo6J1.movimiento.BOXmoverDerecha)  ,  conejo6J1.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo6J2.movimiento.BOXmoverDerecha)  ,  conejo6J2.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo7J1.movimiento.BOXmoverDerecha)  ,  conejo7J1.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo7J2.movimiento.BOXmoverDerecha)  ,  conejo7J2.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo8J1.movimiento.BOXmoverDerecha)  ,  conejo8J1.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo8J2.movimiento.BOXmoverDerecha)  ,  conejo8J2.movimiento.LBLmoverDerecha);
    gtk_container_add(GTK_CONTAINER(elefanteJ1.movimiento.BOXempujarDerecha) ,  elefanteJ1.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(elefanteJ2.movimiento.BOXempujarDerecha) ,  elefanteJ2.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(camelloJ1.movimiento.BOXempujarDerecha)  ,  camelloJ1.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(camelloJ2.movimiento.BOXempujarDerecha)  ,  camelloJ2.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(caballo1J1.movimiento.BOXempujarDerecha) ,  caballo1J1.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(caballo1J2.movimiento.BOXempujarDerecha) ,  caballo1J2.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(caballo2J1.movimiento.BOXempujarDerecha) ,  caballo2J1.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(caballo2J2.movimiento.BOXempujarDerecha) ,  caballo2J2.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(perro1J1.movimiento.BOXempujarDerecha)   ,  perro1J1.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(perro1J2.movimiento.BOXempujarDerecha)   ,  perro1J2.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(perro2J1.movimiento.BOXempujarDerecha)   ,  perro2J1.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(perro2J2.movimiento.BOXempujarDerecha)   ,  perro2J2.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(gato1J1.movimiento.BOXempujarDerecha)    ,  gato1J1.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(gato1J2.movimiento.BOXempujarDerecha)    ,  gato1J2.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(gato2J1.movimiento.BOXempujarDerecha)    ,  gato2J1.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(gato2J2.movimiento.BOXempujarDerecha)    ,  gato2J2.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo1J1.movimiento.BOXempujarDerecha)  ,  conejo1J1.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo1J2.movimiento.BOXempujarDerecha)  ,  conejo1J2.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo2J1.movimiento.BOXempujarDerecha)  ,  conejo2J1.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo2J2.movimiento.BOXempujarDerecha)  ,  conejo2J2.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo3J1.movimiento.BOXempujarDerecha)  ,  conejo3J1.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo3J2.movimiento.BOXempujarDerecha)  ,  conejo3J2.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo4J1.movimiento.BOXempujarDerecha)  ,  conejo4J1.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo4J2.movimiento.BOXempujarDerecha)  ,  conejo4J2.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo5J1.movimiento.BOXempujarDerecha)  ,  conejo5J1.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo5J2.movimiento.BOXempujarDerecha)  ,  conejo5J2.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo6J1.movimiento.BOXempujarDerecha)  ,  conejo6J1.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo6J2.movimiento.BOXempujarDerecha)  ,  conejo6J2.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo7J1.movimiento.BOXempujarDerecha)  ,  conejo7J1.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo7J2.movimiento.BOXempujarDerecha)  ,  conejo7J2.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo8J1.movimiento.BOXempujarDerecha)  ,  conejo8J1.movimiento.LBLempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo8J2.movimiento.BOXempujarDerecha)  ,  conejo8J2.movimiento.LBLempujarDerecha);

//Agragando la caja contenedora BOX a cada menu
    gtk_container_add(GTK_CONTAINER(elefanteJ1.movimiento.OPmoverDerecha) ,  elefanteJ1.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(elefanteJ2.movimiento.OPmoverDerecha) ,  elefanteJ2.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(camelloJ1.movimiento.OPmoverDerecha)  ,  camelloJ1.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(camelloJ2.movimiento.OPmoverDerecha)  ,  camelloJ2.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(caballo1J1.movimiento.OPmoverDerecha) ,  caballo1J1.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(caballo1J2.movimiento.OPmoverDerecha) ,  caballo1J2.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(caballo2J1.movimiento.OPmoverDerecha) ,  caballo2J1.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(caballo2J2.movimiento.OPmoverDerecha) ,  caballo2J2.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(perro1J1.movimiento.OPmoverDerecha)   ,  perro1J1.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(perro1J2.movimiento.OPmoverDerecha)   ,  perro1J2.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(perro2J1.movimiento.OPmoverDerecha)   ,  perro2J1.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(perro2J2.movimiento.OPmoverDerecha)   ,  perro2J2.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(gato1J1.movimiento.OPmoverDerecha)    ,  gato1J1.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(gato1J2.movimiento.OPmoverDerecha)    ,  gato1J2.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(gato2J1.movimiento.OPmoverDerecha)    ,  gato2J1.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(gato2J2.movimiento.OPmoverDerecha)    ,  gato2J2.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo1J1.movimiento.OPmoverDerecha)  ,  conejo1J1.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo1J2.movimiento.OPmoverDerecha)  ,  conejo1J2.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo2J1.movimiento.OPmoverDerecha)  ,  conejo2J1.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo2J2.movimiento.OPmoverDerecha)  ,  conejo2J2.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo3J1.movimiento.OPmoverDerecha)  ,  conejo3J1.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo3J2.movimiento.OPmoverDerecha)  ,  conejo3J2.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo4J1.movimiento.OPmoverDerecha)  ,  conejo4J1.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo4J2.movimiento.OPmoverDerecha)  ,  conejo4J2.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo5J1.movimiento.OPmoverDerecha)  ,  conejo5J1.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo5J2.movimiento.OPmoverDerecha)  ,  conejo5J2.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo6J1.movimiento.OPmoverDerecha)  ,  conejo6J1.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo6J2.movimiento.OPmoverDerecha)  ,  conejo6J2.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo7J1.movimiento.OPmoverDerecha)  ,  conejo7J1.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo7J2.movimiento.OPmoverDerecha)  ,  conejo7J2.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo8J1.movimiento.OPmoverDerecha)  ,  conejo8J1.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(conejo8J2.movimiento.OPmoverDerecha)  ,  conejo8J2.movimiento.BOXmoverDerecha);
    gtk_container_add(GTK_CONTAINER(elefanteJ1.movimiento.OPempujarDerecha) ,  elefanteJ1.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(elefanteJ2.movimiento.OPempujarDerecha) ,  elefanteJ2.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(camelloJ1.movimiento.OPempujarDerecha)  ,  camelloJ1.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(camelloJ2.movimiento.OPempujarDerecha)  ,  camelloJ2.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(caballo1J1.movimiento.OPempujarDerecha) ,  caballo1J1.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(caballo1J2.movimiento.OPempujarDerecha) ,  caballo1J2.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(caballo2J1.movimiento.OPempujarDerecha) ,  caballo2J1.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(caballo2J2.movimiento.OPempujarDerecha) ,  caballo2J2.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(perro1J1.movimiento.OPempujarDerecha)   ,  perro1J1.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(perro1J2.movimiento.OPempujarDerecha)   ,  perro1J2.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(perro2J1.movimiento.OPempujarDerecha)   ,  perro2J1.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(perro2J2.movimiento.OPempujarDerecha)   ,  perro2J2.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(gato1J1.movimiento.OPempujarDerecha)    ,  gato1J1.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(gato1J2.movimiento.OPempujarDerecha)    ,  gato1J2.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(gato2J1.movimiento.OPempujarDerecha)    ,  gato2J1.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(gato2J2.movimiento.OPempujarDerecha)    ,  gato2J2.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo1J1.movimiento.OPempujarDerecha)  ,  conejo1J1.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo1J2.movimiento.OPempujarDerecha)  ,  conejo1J2.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo2J1.movimiento.OPempujarDerecha)  ,  conejo2J1.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo2J2.movimiento.OPempujarDerecha)  ,  conejo2J2.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo3J1.movimiento.OPempujarDerecha)  ,  conejo3J1.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo3J2.movimiento.OPempujarDerecha)  ,  conejo3J2.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo4J1.movimiento.OPempujarDerecha)  ,  conejo4J1.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo4J2.movimiento.OPempujarDerecha)  ,  conejo4J2.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo5J1.movimiento.OPempujarDerecha)  ,  conejo5J1.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo5J2.movimiento.OPempujarDerecha)  ,  conejo5J2.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo6J1.movimiento.OPempujarDerecha)  ,  conejo6J1.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo6J2.movimiento.OPempujarDerecha)  ,  conejo6J2.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo7J1.movimiento.OPempujarDerecha)  ,  conejo7J1.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo7J2.movimiento.OPempujarDerecha)  ,  conejo7J2.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo8J1.movimiento.OPempujarDerecha)  ,  conejo8J1.movimiento.BOXempujarDerecha);
    gtk_container_add(GTK_CONTAINER(conejo8J2.movimiento.OPempujarDerecha)  ,  conejo8J2.movimiento.BOXempujarDerecha);

//Cargando iconos MOVER Izquierda y EMPUJAR  Izquierda para todas las piezas
    elefanteJ1.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    elefanteJ2.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    camelloJ1.movimiento.ICOmoverIzquierda  = gtk_image_new_from_file("moverIzquierda.png");
    camelloJ2.movimiento.ICOmoverIzquierda  = gtk_image_new_from_file("moverIzquierda.png");
    caballo1J1.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    caballo1J2.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    caballo2J1.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    caballo2J2.movimiento.ICOmoverIzquierda = gtk_image_new_from_file("moverIzquierda.png");
    perro1J1.movimiento.ICOmoverIzquierda   = gtk_image_new_from_file("moverIzquierda.png");
    perro1J2.movimiento.ICOmoverIzquierda   = gtk_image_new_from_file("moverIzquierda.png");
    perro2J1.movimiento.ICOmoverIzquierda   = gtk_image_new_from_file("moverIzquierda.png");
    perro2J2.movimiento.ICOmoverIzquierda   = gtk_image_new_from_file("moverIzquierda.png");
    gato1J1.movimiento.ICOmoverIzquierda    = gtk_image_new_from_file("moverIzquierda.png");
    gato1J2.movimiento.ICOmoverIzquierda    = gtk_image_new_from_file("moverIzquierda.png");
    gato2J1.movimiento.ICOmoverIzquierda    = gtk_image_new_from_file("moverIzquierda.png");
    gato2J2.movimiento.ICOmoverIzquierda    = gtk_image_new_from_file("moverIzquierda.png");
    conejo1J1.movimiento.ICOmoverIzquierda  = gtk_image_new_from_file("moverIzquierda.png");
    conejo1J2.movimiento.ICOmoverIzquierda  = gtk_image_new_from_file("moverIzquierda.png");
    conejo2J1.movimiento.ICOmoverIzquierda  = gtk_image_new_from_file("moverIzquierda.png");
    conejo2J2.movimiento.ICOmoverIzquierda  = gtk_image_new_from_file("moverIzquierda.png");
    conejo3J1.movimiento.ICOmoverIzquierda  = gtk_image_new_from_file("moverIzquierda.png");
    conejo3J2.movimiento.ICOmoverIzquierda  = gtk_image_new_from_file("moverIzquierda.png");
    conejo4J1.movimiento.ICOmoverIzquierda  = gtk_image_new_from_file("moverIzquierda.png");
    conejo4J2.movimiento.ICOmoverIzquierda  = gtk_image_new_from_file("moverIzquierda.png");
    conejo5J1.movimiento.ICOmoverIzquierda  = gtk_image_new_from_file("moverIzquierda.png");
    conejo5J2.movimiento.ICOmoverIzquierda  = gtk_image_new_from_file("moverIzquierda.png");
    conejo6J1.movimiento.ICOmoverIzquierda  = gtk_image_new_from_file("moverIzquierda.png");
    conejo6J2.movimiento.ICOmoverIzquierda  = gtk_image_new_from_file("moverIzquierda.png");
    conejo7J1.movimiento.ICOmoverIzquierda  = gtk_image_new_from_file("moverIzquierda.png");
    conejo7J2.movimiento.ICOmoverIzquierda  = gtk_image_new_from_file("moverIzquierda.png");
    conejo8J1.movimiento.ICOmoverIzquierda  = gtk_image_new_from_file("moverIzquierda.png");
    conejo8J2.movimiento.ICOmoverIzquierda  = gtk_image_new_from_file("moverIzquierda.png");
    elefanteJ1.movimiento.ICOempujarIzquierda = gtk_image_new_from_file("empujarIzquierda.png");
    elefanteJ2.movimiento.ICOempujarIzquierda = gtk_image_new_from_file("empujarIzquierda.png");
    camelloJ1.movimiento.ICOempujarIzquierda  = gtk_image_new_from_file("empujarIzquierda.png");
    camelloJ2.movimiento.ICOempujarIzquierda  = gtk_image_new_from_file("empujarIzquierda.png");
    caballo1J1.movimiento.ICOempujarIzquierda = gtk_image_new_from_file("empujarIzquierda.png");
    caballo1J2.movimiento.ICOempujarIzquierda = gtk_image_new_from_file("empujarIzquierda.png");
    caballo2J1.movimiento.ICOempujarIzquierda = gtk_image_new_from_file("empujarIzquierda.png");
    caballo2J2.movimiento.ICOempujarIzquierda = gtk_image_new_from_file("empujarIzquierda.png");
    perro1J1.movimiento.ICOempujarIzquierda   = gtk_image_new_from_file("empujarIzquierda.png");
    perro1J2.movimiento.ICOempujarIzquierda   = gtk_image_new_from_file("empujarIzquierda.png");
    perro2J1.movimiento.ICOempujarIzquierda   = gtk_image_new_from_file("empujarIzquierda.png");
    perro2J2.movimiento.ICOempujarIzquierda   = gtk_image_new_from_file("empujarIzquierda.png");
    gato1J1.movimiento.ICOempujarIzquierda    = gtk_image_new_from_file("empujarIzquierda.png");
    gato1J2.movimiento.ICOempujarIzquierda    = gtk_image_new_from_file("empujarIzquierda.png");
    gato2J1.movimiento.ICOempujarIzquierda    = gtk_image_new_from_file("empujarIzquierda.png");
    gato2J2.movimiento.ICOempujarIzquierda    = gtk_image_new_from_file("empujarIzquierda.png");
    conejo1J1.movimiento.ICOempujarIzquierda  = gtk_image_new_from_file("empujarIzquierda.png");
    conejo1J2.movimiento.ICOempujarIzquierda  = gtk_image_new_from_file("empujarIzquierda.png");
    conejo2J1.movimiento.ICOempujarIzquierda  = gtk_image_new_from_file("empujarIzquierda.png");
    conejo2J2.movimiento.ICOempujarIzquierda  = gtk_image_new_from_file("empujarIzquierda.png");
    conejo3J1.movimiento.ICOempujarIzquierda  = gtk_image_new_from_file("empujarIzquierda.png");
    conejo3J2.movimiento.ICOempujarIzquierda  = gtk_image_new_from_file("empujarIzquierda.png");
    conejo4J1.movimiento.ICOempujarIzquierda  = gtk_image_new_from_file("empujarIzquierda.png");
    conejo4J2.movimiento.ICOempujarIzquierda  = gtk_image_new_from_file("empujarIzquierda.png");
    conejo5J1.movimiento.ICOempujarIzquierda  = gtk_image_new_from_file("empujarIzquierda.png");
    conejo5J2.movimiento.ICOempujarIzquierda  = gtk_image_new_from_file("empujarIzquierda.png");
    conejo6J1.movimiento.ICOempujarIzquierda  = gtk_image_new_from_file("empujarIzquierda.png");
    conejo6J2.movimiento.ICOempujarIzquierda  = gtk_image_new_from_file("empujarIzquierda.png");
    conejo7J1.movimiento.ICOempujarIzquierda  = gtk_image_new_from_file("empujarIzquierda.png");
    conejo7J2.movimiento.ICOempujarIzquierda  = gtk_image_new_from_file("empujarIzquierda.png");
    conejo8J1.movimiento.ICOempujarIzquierda  = gtk_image_new_from_file("empujarIzquierda.png");
    conejo8J2.movimiento.ICOempujarIzquierda  = gtk_image_new_from_file("empujarIzquierda.png");

//Cargando LABEL MOVER Izquierda y EMPUJAR  Izquierda para todas las piezas
    elefanteJ1.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    elefanteJ2.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    camelloJ1.movimiento.LBLmoverIzquierda  = gtk_label_new(" Mover Izquierda ");
    camelloJ2.movimiento.LBLmoverIzquierda  = gtk_label_new(" Mover Izquierda ");
    caballo1J1.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    caballo1J2.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    caballo2J1.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    caballo2J2.movimiento.LBLmoverIzquierda = gtk_label_new(" Mover Izquierda ");
    perro1J1.movimiento.LBLmoverIzquierda   = gtk_label_new(" Mover Izquierda ");
    perro1J2.movimiento.LBLmoverIzquierda   = gtk_label_new(" Mover Izquierda ");
    perro2J1.movimiento.LBLmoverIzquierda   = gtk_label_new(" Mover Izquierda ");
    perro2J2.movimiento.LBLmoverIzquierda   = gtk_label_new(" Mover Izquierda ");
    gato1J1.movimiento.LBLmoverIzquierda    = gtk_label_new(" Mover Izquierda ");
    gato1J2.movimiento.LBLmoverIzquierda    = gtk_label_new(" Mover Izquierda ");
    gato2J1.movimiento.LBLmoverIzquierda    = gtk_label_new(" Mover Izquierda ");
    gato2J2.movimiento.LBLmoverIzquierda    = gtk_label_new(" Mover Izquierda ");
    conejo1J1.movimiento.LBLmoverIzquierda  = gtk_label_new(" Mover Izquierda ");
    conejo1J2.movimiento.LBLmoverIzquierda  = gtk_label_new(" Mover Izquierda ");
    conejo2J1.movimiento.LBLmoverIzquierda  = gtk_label_new(" Mover Izquierda ");
    conejo2J2.movimiento.LBLmoverIzquierda  = gtk_label_new(" Mover Izquierda ");
    conejo3J1.movimiento.LBLmoverIzquierda  = gtk_label_new(" Mover Izquierda ");
    conejo3J2.movimiento.LBLmoverIzquierda  = gtk_label_new(" Mover Izquierda ");
    conejo4J1.movimiento.LBLmoverIzquierda  = gtk_label_new(" Mover Izquierda ");
    conejo4J2.movimiento.LBLmoverIzquierda  = gtk_label_new(" Mover Izquierda ");
    conejo5J1.movimiento.LBLmoverIzquierda  = gtk_label_new(" Mover Izquierda ");
    conejo5J2.movimiento.LBLmoverIzquierda  = gtk_label_new(" Mover Izquierda ");
    conejo6J1.movimiento.LBLmoverIzquierda  = gtk_label_new(" Mover Izquierda ");
    conejo6J2.movimiento.LBLmoverIzquierda  = gtk_label_new(" Mover Izquierda ");
    conejo7J1.movimiento.LBLmoverIzquierda  = gtk_label_new(" Mover Izquierda ");
    conejo7J2.movimiento.LBLmoverIzquierda  = gtk_label_new(" Mover Izquierda ");
    conejo8J1.movimiento.LBLmoverIzquierda  = gtk_label_new(" Mover Izquierda ");
    conejo8J2.movimiento.LBLmoverIzquierda  = gtk_label_new(" Mover Izquierda ");
    elefanteJ1.movimiento.LBLempujarIzquierda = gtk_label_new(" empujar Izquierda ");
    elefanteJ2.movimiento.LBLempujarIzquierda = gtk_label_new(" empujar Izquierda ");
    camelloJ1.movimiento.LBLempujarIzquierda  = gtk_label_new(" empujar Izquierda ");
    camelloJ2.movimiento.LBLempujarIzquierda  = gtk_label_new(" empujar Izquierda ");
    caballo1J1.movimiento.LBLempujarIzquierda = gtk_label_new(" empujar Izquierda ");
    caballo1J2.movimiento.LBLempujarIzquierda = gtk_label_new(" empujar Izquierda ");
    caballo2J1.movimiento.LBLempujarIzquierda = gtk_label_new(" empujar Izquierda ");
    caballo2J2.movimiento.LBLempujarIzquierda = gtk_label_new(" empujar Izquierda ");
    perro1J1.movimiento.LBLempujarIzquierda   = gtk_label_new(" empujar Izquierda ");
    perro1J2.movimiento.LBLempujarIzquierda   = gtk_label_new(" empujar Izquierda ");
    perro2J1.movimiento.LBLempujarIzquierda   = gtk_label_new(" empujar Izquierda ");
    perro2J2.movimiento.LBLempujarIzquierda   = gtk_label_new(" empujar Izquierda ");
    gato1J1.movimiento.LBLempujarIzquierda    = gtk_label_new(" empujar Izquierda ");
    gato1J2.movimiento.LBLempujarIzquierda    = gtk_label_new(" empujar Izquierda ");
    gato2J1.movimiento.LBLempujarIzquierda    = gtk_label_new(" empujar Izquierda ");
    gato2J2.movimiento.LBLempujarIzquierda    = gtk_label_new(" empujar Izquierda ");
    conejo1J1.movimiento.LBLempujarIzquierda  = gtk_label_new(" empujar Izquierda ");
    conejo1J2.movimiento.LBLempujarIzquierda  = gtk_label_new(" empujar Izquierda ");
    conejo2J1.movimiento.LBLempujarIzquierda  = gtk_label_new(" empujar Izquierda ");
    conejo2J2.movimiento.LBLempujarIzquierda  = gtk_label_new(" empujar Izquierda ");
    conejo3J1.movimiento.LBLempujarIzquierda  = gtk_label_new(" empujar Izquierda ");
    conejo3J2.movimiento.LBLempujarIzquierda  = gtk_label_new(" empujar Izquierda ");
    conejo4J1.movimiento.LBLempujarIzquierda  = gtk_label_new(" empujar Izquierda ");
    conejo4J2.movimiento.LBLempujarIzquierda  = gtk_label_new(" empujar Izquierda ");
    conejo5J1.movimiento.LBLempujarIzquierda  = gtk_label_new(" empujar Izquierda ");
    conejo5J2.movimiento.LBLempujarIzquierda  = gtk_label_new(" empujar Izquierda ");
    conejo6J1.movimiento.LBLempujarIzquierda  = gtk_label_new(" empujar Izquierda ");
    conejo6J2.movimiento.LBLempujarIzquierda  = gtk_label_new(" empujar Izquierda ");
    conejo7J1.movimiento.LBLempujarIzquierda  = gtk_label_new(" empujar Izquierda ");
    conejo7J2.movimiento.LBLempujarIzquierda  = gtk_label_new(" empujar Izquierda ");
    conejo8J1.movimiento.LBLempujarIzquierda  = gtk_label_new(" empujar Izquierda ");
    conejo8J2.movimiento.LBLempujarIzquierda  = gtk_label_new(" empujar Izquierda ");

//Creando caja contenedora BOX para MOVER Izquierda y EMPUJAR  Izquierda de todas las piezas
    elefanteJ1.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    elefanteJ2.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    camelloJ1.movimiento.BOXmoverIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    camelloJ2.movimiento.BOXmoverIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo1J1.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo1J2.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo2J1.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo2J2.movimiento.BOXmoverIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro1J1.movimiento.BOXmoverIzquierda   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro1J2.movimiento.BOXmoverIzquierda   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro2J1.movimiento.BOXmoverIzquierda   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro2J2.movimiento.BOXmoverIzquierda   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato1J1.movimiento.BOXmoverIzquierda    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato1J2.movimiento.BOXmoverIzquierda    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato2J1.movimiento.BOXmoverIzquierda    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato2J2.movimiento.BOXmoverIzquierda    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo1J1.movimiento.BOXmoverIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo1J2.movimiento.BOXmoverIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo2J1.movimiento.BOXmoverIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo2J2.movimiento.BOXmoverIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo3J1.movimiento.BOXmoverIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo3J2.movimiento.BOXmoverIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo4J1.movimiento.BOXmoverIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo4J2.movimiento.BOXmoverIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo5J1.movimiento.BOXmoverIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo5J2.movimiento.BOXmoverIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo6J1.movimiento.BOXmoverIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo6J2.movimiento.BOXmoverIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo7J1.movimiento.BOXmoverIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo7J2.movimiento.BOXmoverIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo8J1.movimiento.BOXmoverIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo8J2.movimiento.BOXmoverIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    elefanteJ1.movimiento.BOXempujarIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    elefanteJ2.movimiento.BOXempujarIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    camelloJ1.movimiento.BOXempujarIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    camelloJ2.movimiento.BOXempujarIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo1J1.movimiento.BOXempujarIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo1J2.movimiento.BOXempujarIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo2J1.movimiento.BOXempujarIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    caballo2J2.movimiento.BOXempujarIzquierda = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro1J1.movimiento.BOXempujarIzquierda   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro1J2.movimiento.BOXempujarIzquierda   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro2J1.movimiento.BOXempujarIzquierda   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    perro2J2.movimiento.BOXempujarIzquierda   = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato1J1.movimiento.BOXempujarIzquierda    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato1J2.movimiento.BOXempujarIzquierda    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato2J1.movimiento.BOXempujarIzquierda    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    gato2J2.movimiento.BOXempujarIzquierda    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo1J1.movimiento.BOXempujarIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo1J2.movimiento.BOXempujarIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo2J1.movimiento.BOXempujarIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo2J2.movimiento.BOXempujarIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo3J1.movimiento.BOXempujarIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo3J2.movimiento.BOXempujarIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo4J1.movimiento.BOXempujarIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo4J2.movimiento.BOXempujarIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo5J1.movimiento.BOXempujarIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo5J2.movimiento.BOXempujarIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo6J1.movimiento.BOXempujarIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo6J2.movimiento.BOXempujarIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo7J1.movimiento.BOXempujarIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo7J2.movimiento.BOXempujarIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo8J1.movimiento.BOXempujarIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    conejo8J2.movimiento.BOXempujarIzquierda  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

//Cargando los iconos a la caja contenedora BOX
    gtk_container_add(GTK_CONTAINER(elefanteJ1.movimiento.BOXmoverIzquierda) ,  elefanteJ1.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(elefanteJ2.movimiento.BOXmoverIzquierda) ,  elefanteJ2.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(camelloJ1.movimiento.BOXmoverIzquierda)  ,  camelloJ1.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(camelloJ2.movimiento.BOXmoverIzquierda)  ,  camelloJ2.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(caballo1J1.movimiento.BOXmoverIzquierda) ,  caballo1J1.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(caballo1J2.movimiento.BOXmoverIzquierda) ,  caballo1J2.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(caballo2J1.movimiento.BOXmoverIzquierda) ,  caballo2J1.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(caballo2J2.movimiento.BOXmoverIzquierda) ,  caballo2J2.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(perro1J1.movimiento.BOXmoverIzquierda)   ,  perro1J1.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(perro1J2.movimiento.BOXmoverIzquierda)   ,  perro1J2.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(perro2J1.movimiento.BOXmoverIzquierda)   ,  perro2J1.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(perro2J2.movimiento.BOXmoverIzquierda)   ,  perro2J2.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(gato1J1.movimiento.BOXmoverIzquierda)    ,  gato1J1.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(gato1J2.movimiento.BOXmoverIzquierda)    ,  gato1J2.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(gato2J1.movimiento.BOXmoverIzquierda)    ,  gato2J1.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(gato2J2.movimiento.BOXmoverIzquierda)    ,  gato2J2.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo1J1.movimiento.BOXmoverIzquierda)  ,  conejo1J1.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo1J2.movimiento.BOXmoverIzquierda)  ,  conejo1J2.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo2J1.movimiento.BOXmoverIzquierda)  ,  conejo2J1.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo2J2.movimiento.BOXmoverIzquierda)  ,  conejo2J2.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo3J1.movimiento.BOXmoverIzquierda)  ,  conejo3J1.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo3J2.movimiento.BOXmoverIzquierda)  ,  conejo3J2.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo4J1.movimiento.BOXmoverIzquierda)  ,  conejo4J1.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo4J2.movimiento.BOXmoverIzquierda)  ,  conejo4J2.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo5J1.movimiento.BOXmoverIzquierda)  ,  conejo5J1.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo5J2.movimiento.BOXmoverIzquierda)  ,  conejo5J2.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo6J1.movimiento.BOXmoverIzquierda)  ,  conejo6J1.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo6J2.movimiento.BOXmoverIzquierda)  ,  conejo6J2.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo7J1.movimiento.BOXmoverIzquierda)  ,  conejo7J1.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo7J2.movimiento.BOXmoverIzquierda)  ,  conejo7J2.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo8J1.movimiento.BOXmoverIzquierda)  ,  conejo8J1.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo8J2.movimiento.BOXmoverIzquierda)  ,  conejo8J2.movimiento.ICOmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(elefanteJ1.movimiento.BOXempujarIzquierda) ,  elefanteJ1.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(elefanteJ2.movimiento.BOXempujarIzquierda) ,  elefanteJ2.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(camelloJ1.movimiento.BOXempujarIzquierda)  ,  camelloJ1.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(camelloJ2.movimiento.BOXempujarIzquierda)  ,  camelloJ2.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(caballo1J1.movimiento.BOXempujarIzquierda) ,  caballo1J1.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(caballo1J2.movimiento.BOXempujarIzquierda) ,  caballo1J2.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(caballo2J1.movimiento.BOXempujarIzquierda) ,  caballo2J1.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(caballo2J2.movimiento.BOXempujarIzquierda) ,  caballo2J2.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(perro1J1.movimiento.BOXempujarIzquierda)   ,  perro1J1.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(perro1J2.movimiento.BOXempujarIzquierda)   ,  perro1J2.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(perro2J1.movimiento.BOXempujarIzquierda)   ,  perro2J1.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(perro2J2.movimiento.BOXempujarIzquierda)   ,  perro2J2.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(gato1J1.movimiento.BOXempujarIzquierda)    ,  gato1J1.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(gato1J2.movimiento.BOXempujarIzquierda)    ,  gato1J2.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(gato2J1.movimiento.BOXempujarIzquierda)    ,  gato2J1.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(gato2J2.movimiento.BOXempujarIzquierda)    ,  gato2J2.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo1J1.movimiento.BOXempujarIzquierda)  ,  conejo1J1.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo1J2.movimiento.BOXempujarIzquierda)  ,  conejo1J2.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo2J1.movimiento.BOXempujarIzquierda)  ,  conejo2J1.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo2J2.movimiento.BOXempujarIzquierda)  ,  conejo2J2.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo3J1.movimiento.BOXempujarIzquierda)  ,  conejo3J1.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo3J2.movimiento.BOXempujarIzquierda)  ,  conejo3J2.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo4J1.movimiento.BOXempujarIzquierda)  ,  conejo4J1.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo4J2.movimiento.BOXempujarIzquierda)  ,  conejo4J2.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo5J1.movimiento.BOXempujarIzquierda)  ,  conejo5J1.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo5J2.movimiento.BOXempujarIzquierda)  ,  conejo5J2.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo6J1.movimiento.BOXempujarIzquierda)  ,  conejo6J1.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo6J2.movimiento.BOXempujarIzquierda)  ,  conejo6J2.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo7J1.movimiento.BOXempujarIzquierda)  ,  conejo7J1.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo7J2.movimiento.BOXempujarIzquierda)  ,  conejo7J2.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo8J1.movimiento.BOXempujarIzquierda)  ,  conejo8J1.movimiento.ICOempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo8J2.movimiento.BOXempujarIzquierda)  ,  conejo8J2.movimiento.ICOempujarIzquierda);

//Cargando los Labels a la caja contenedora BOX
    gtk_container_add(GTK_CONTAINER(elefanteJ1.movimiento.BOXmoverIzquierda) ,  elefanteJ1.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(elefanteJ2.movimiento.BOXmoverIzquierda) ,  elefanteJ2.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(camelloJ1.movimiento.BOXmoverIzquierda)  ,  camelloJ1.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(camelloJ2.movimiento.BOXmoverIzquierda)  ,  camelloJ2.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(caballo1J1.movimiento.BOXmoverIzquierda) ,  caballo1J1.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(caballo1J2.movimiento.BOXmoverIzquierda) ,  caballo1J2.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(caballo2J1.movimiento.BOXmoverIzquierda) ,  caballo2J1.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(caballo2J2.movimiento.BOXmoverIzquierda) ,  caballo2J2.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(perro1J1.movimiento.BOXmoverIzquierda)   ,  perro1J1.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(perro1J2.movimiento.BOXmoverIzquierda)   ,  perro1J2.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(perro2J1.movimiento.BOXmoverIzquierda)   ,  perro2J1.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(perro2J2.movimiento.BOXmoverIzquierda)   ,  perro2J2.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(gato1J1.movimiento.BOXmoverIzquierda)    ,  gato1J1.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(gato1J2.movimiento.BOXmoverIzquierda)    ,  gato1J2.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(gato2J1.movimiento.BOXmoverIzquierda)    ,  gato2J1.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(gato2J2.movimiento.BOXmoverIzquierda)    ,  gato2J2.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo1J1.movimiento.BOXmoverIzquierda)  ,  conejo1J1.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo1J2.movimiento.BOXmoverIzquierda)  ,  conejo1J2.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo2J1.movimiento.BOXmoverIzquierda)  ,  conejo2J1.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo2J2.movimiento.BOXmoverIzquierda)  ,  conejo2J2.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo3J1.movimiento.BOXmoverIzquierda)  ,  conejo3J1.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo3J2.movimiento.BOXmoverIzquierda)  ,  conejo3J2.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo4J1.movimiento.BOXmoverIzquierda)  ,  conejo4J1.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo4J2.movimiento.BOXmoverIzquierda)  ,  conejo4J2.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo5J1.movimiento.BOXmoverIzquierda)  ,  conejo5J1.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo5J2.movimiento.BOXmoverIzquierda)  ,  conejo5J2.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo6J1.movimiento.BOXmoverIzquierda)  ,  conejo6J1.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo6J2.movimiento.BOXmoverIzquierda)  ,  conejo6J2.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo7J1.movimiento.BOXmoverIzquierda)  ,  conejo7J1.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo7J2.movimiento.BOXmoverIzquierda)  ,  conejo7J2.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo8J1.movimiento.BOXmoverIzquierda)  ,  conejo8J1.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo8J2.movimiento.BOXmoverIzquierda)  ,  conejo8J2.movimiento.LBLmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(elefanteJ1.movimiento.BOXempujarIzquierda) ,  elefanteJ1.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(elefanteJ2.movimiento.BOXempujarIzquierda) ,  elefanteJ2.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(camelloJ1.movimiento.BOXempujarIzquierda)  ,  camelloJ1.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(camelloJ2.movimiento.BOXempujarIzquierda)  ,  camelloJ2.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(caballo1J1.movimiento.BOXempujarIzquierda) ,  caballo1J1.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(caballo1J2.movimiento.BOXempujarIzquierda) ,  caballo1J2.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(caballo2J1.movimiento.BOXempujarIzquierda) ,  caballo2J1.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(caballo2J2.movimiento.BOXempujarIzquierda) ,  caballo2J2.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(perro1J1.movimiento.BOXempujarIzquierda)   ,  perro1J1.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(perro1J2.movimiento.BOXempujarIzquierda)   ,  perro1J2.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(perro2J1.movimiento.BOXempujarIzquierda)   ,  perro2J1.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(perro2J2.movimiento.BOXempujarIzquierda)   ,  perro2J2.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(gato1J1.movimiento.BOXempujarIzquierda)    ,  gato1J1.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(gato1J2.movimiento.BOXempujarIzquierda)    ,  gato1J2.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(gato2J1.movimiento.BOXempujarIzquierda)    ,  gato2J1.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(gato2J2.movimiento.BOXempujarIzquierda)    ,  gato2J2.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo1J1.movimiento.BOXempujarIzquierda)  ,  conejo1J1.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo1J2.movimiento.BOXempujarIzquierda)  ,  conejo1J2.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo2J1.movimiento.BOXempujarIzquierda)  ,  conejo2J1.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo2J2.movimiento.BOXempujarIzquierda)  ,  conejo2J2.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo3J1.movimiento.BOXempujarIzquierda)  ,  conejo3J1.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo3J2.movimiento.BOXempujarIzquierda)  ,  conejo3J2.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo4J1.movimiento.BOXempujarIzquierda)  ,  conejo4J1.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo4J2.movimiento.BOXempujarIzquierda)  ,  conejo4J2.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo5J1.movimiento.BOXempujarIzquierda)  ,  conejo5J1.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo5J2.movimiento.BOXempujarIzquierda)  ,  conejo5J2.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo6J1.movimiento.BOXempujarIzquierda)  ,  conejo6J1.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo6J2.movimiento.BOXempujarIzquierda)  ,  conejo6J2.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo7J1.movimiento.BOXempujarIzquierda)  ,  conejo7J1.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo7J2.movimiento.BOXempujarIzquierda)  ,  conejo7J2.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo8J1.movimiento.BOXempujarIzquierda)  ,  conejo8J1.movimiento.LBLempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo8J2.movimiento.BOXempujarIzquierda)  ,  conejo8J2.movimiento.LBLempujarIzquierda);

//Agragando la caja contenedora BOX a cada menu
    gtk_container_add(GTK_CONTAINER(elefanteJ1.movimiento.OPmoverIzquierda) ,  elefanteJ1.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(elefanteJ2.movimiento.OPmoverIzquierda) ,  elefanteJ2.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(camelloJ1.movimiento.OPmoverIzquierda)  ,  camelloJ1.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(camelloJ2.movimiento.OPmoverIzquierda)  ,  camelloJ2.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(caballo1J1.movimiento.OPmoverIzquierda) ,  caballo1J1.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(caballo1J2.movimiento.OPmoverIzquierda) ,  caballo1J2.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(caballo2J1.movimiento.OPmoverIzquierda) ,  caballo2J1.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(caballo2J2.movimiento.OPmoverIzquierda) ,  caballo2J2.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(perro1J1.movimiento.OPmoverIzquierda)   ,  perro1J1.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(perro1J2.movimiento.OPmoverIzquierda)   ,  perro1J2.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(perro2J1.movimiento.OPmoverIzquierda)   ,  perro2J1.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(perro2J2.movimiento.OPmoverIzquierda)   ,  perro2J2.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(gato1J1.movimiento.OPmoverIzquierda)    ,  gato1J1.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(gato1J2.movimiento.OPmoverIzquierda)    ,  gato1J2.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(gato2J1.movimiento.OPmoverIzquierda)    ,  gato2J1.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(gato2J2.movimiento.OPmoverIzquierda)    ,  gato2J2.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo1J1.movimiento.OPmoverIzquierda)  ,  conejo1J1.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo1J2.movimiento.OPmoverIzquierda)  ,  conejo1J2.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo2J1.movimiento.OPmoverIzquierda)  ,  conejo2J1.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo2J2.movimiento.OPmoverIzquierda)  ,  conejo2J2.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo3J1.movimiento.OPmoverIzquierda)  ,  conejo3J1.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo3J2.movimiento.OPmoverIzquierda)  ,  conejo3J2.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo4J1.movimiento.OPmoverIzquierda)  ,  conejo4J1.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo4J2.movimiento.OPmoverIzquierda)  ,  conejo4J2.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo5J1.movimiento.OPmoverIzquierda)  ,  conejo5J1.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo5J2.movimiento.OPmoverIzquierda)  ,  conejo5J2.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo6J1.movimiento.OPmoverIzquierda)  ,  conejo6J1.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo6J2.movimiento.OPmoverIzquierda)  ,  conejo6J2.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo7J1.movimiento.OPmoverIzquierda)  ,  conejo7J1.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo7J2.movimiento.OPmoverIzquierda)  ,  conejo7J2.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo8J1.movimiento.OPmoverIzquierda)  ,  conejo8J1.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo8J2.movimiento.OPmoverIzquierda)  ,  conejo8J2.movimiento.BOXmoverIzquierda);
    gtk_container_add(GTK_CONTAINER(elefanteJ1.movimiento.OPempujarIzquierda) ,  elefanteJ1.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(elefanteJ2.movimiento.OPempujarIzquierda) ,  elefanteJ2.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(camelloJ1.movimiento.OPempujarIzquierda)  ,  camelloJ1.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(camelloJ2.movimiento.OPempujarIzquierda)  ,  camelloJ2.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(caballo1J1.movimiento.OPempujarIzquierda) ,  caballo1J1.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(caballo1J2.movimiento.OPempujarIzquierda) ,  caballo1J2.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(caballo2J1.movimiento.OPempujarIzquierda) ,  caballo2J1.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(caballo2J2.movimiento.OPempujarIzquierda) ,  caballo2J2.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(perro1J1.movimiento.OPempujarIzquierda)   ,  perro1J1.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(perro1J2.movimiento.OPempujarIzquierda)   ,  perro1J2.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(perro2J1.movimiento.OPempujarIzquierda)   ,  perro2J1.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(perro2J2.movimiento.OPempujarIzquierda)   ,  perro2J2.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(gato1J1.movimiento.OPempujarIzquierda)    ,  gato1J1.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(gato1J2.movimiento.OPempujarIzquierda)    ,  gato1J2.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(gato2J1.movimiento.OPempujarIzquierda)    ,  gato2J1.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(gato2J2.movimiento.OPempujarIzquierda)    ,  gato2J2.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo1J1.movimiento.OPempujarIzquierda)  ,  conejo1J1.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo1J2.movimiento.OPempujarIzquierda)  ,  conejo1J2.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo2J1.movimiento.OPempujarIzquierda)  ,  conejo2J1.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo2J2.movimiento.OPempujarIzquierda)  ,  conejo2J2.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo3J1.movimiento.OPempujarIzquierda)  ,  conejo3J1.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo3J2.movimiento.OPempujarIzquierda)  ,  conejo3J2.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo4J1.movimiento.OPempujarIzquierda)  ,  conejo4J1.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo4J2.movimiento.OPempujarIzquierda)  ,  conejo4J2.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo5J1.movimiento.OPempujarIzquierda)  ,  conejo5J1.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo5J2.movimiento.OPempujarIzquierda)  ,  conejo5J2.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo6J1.movimiento.OPempujarIzquierda)  ,  conejo6J1.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo6J2.movimiento.OPempujarIzquierda)  ,  conejo6J2.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo7J1.movimiento.OPempujarIzquierda)  ,  conejo7J1.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo7J2.movimiento.OPempujarIzquierda)  ,  conejo7J2.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo8J1.movimiento.OPempujarIzquierda)  ,  conejo8J1.movimiento.BOXempujarIzquierda);
    gtk_container_add(GTK_CONTAINER(conejo8J2.movimiento.OPempujarIzquierda)  ,  conejo8J2.movimiento.BOXempujarIzquierda);

}

void FNconectarMenusPiezas(){ //Conecta los Menús creados a las piezas
    //Jugador 1
    g_signal_connect_swapped(G_OBJECT(elefanteJ1.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), elefanteJ1.Menu);
    g_signal_connect_swapped(G_OBJECT(camelloJ1.Pieza),  "button-press-event", G_CALLBACK(desplegarMenuMovimiento), camelloJ1.Menu);
    g_signal_connect_swapped(G_OBJECT(caballo1J1.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), caballo1J1.Menu);
    g_signal_connect_swapped(G_OBJECT(caballo2J1.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), caballo2J1.Menu);
    g_signal_connect_swapped(G_OBJECT(perro1J1.Pieza),   "button-press-event", G_CALLBACK(desplegarMenuMovimiento), perro1J1.Menu);
    g_signal_connect_swapped(G_OBJECT(perro2J1.Pieza),   "button-press-event", G_CALLBACK(desplegarMenuMovimiento), perro2J1.Menu);
    g_signal_connect_swapped(G_OBJECT(gato1J1.Pieza),    "button-press-event", G_CALLBACK(desplegarMenuMovimiento), gato1J1.Menu);
    g_signal_connect_swapped(G_OBJECT(gato2J1.Pieza),    "button-press-event", G_CALLBACK(desplegarMenuMovimiento), gato2J1.Menu);
    g_signal_connect_swapped(G_OBJECT(conejo1J1.Pieza),  "button-press-event", G_CALLBACK(desplegarMenuMovimiento), conejo1J1.Menu);
    g_signal_connect_swapped(G_OBJECT(conejo2J1.Pieza),  "button-press-event", G_CALLBACK(desplegarMenuMovimiento), conejo2J1.Menu);
    g_signal_connect_swapped(G_OBJECT(conejo3J1.Pieza),  "button-press-event", G_CALLBACK(desplegarMenuMovimiento), conejo3J1.Menu);
    g_signal_connect_swapped(G_OBJECT(conejo4J1.Pieza),  "button-press-event", G_CALLBACK(desplegarMenuMovimiento), conejo4J1.Menu);
    g_signal_connect_swapped(G_OBJECT(conejo5J1.Pieza),  "button-press-event", G_CALLBACK(desplegarMenuMovimiento), conejo5J1.Menu);
    g_signal_connect_swapped(G_OBJECT(conejo6J1.Pieza),  "button-press-event", G_CALLBACK(desplegarMenuMovimiento), conejo6J1.Menu);
    g_signal_connect_swapped(G_OBJECT(conejo7J1.Pieza),  "button-press-event", G_CALLBACK(desplegarMenuMovimiento), conejo7J1.Menu);
    g_signal_connect_swapped(G_OBJECT(conejo8J1.Pieza),  "button-press-event", G_CALLBACK(desplegarMenuMovimiento), conejo8J1.Menu);
    //Jugador 2
    g_signal_connect_swapped(G_OBJECT(elefanteJ2.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), elefanteJ2.Menu);
    g_signal_connect_swapped(G_OBJECT(camelloJ2.Pieza),  "button-press-event", G_CALLBACK(desplegarMenuMovimiento), camelloJ2.Menu);
    g_signal_connect_swapped(G_OBJECT(caballo1J2.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), caballo1J2.Menu);
    g_signal_connect_swapped(G_OBJECT(caballo2J2.Pieza), "button-press-event", G_CALLBACK(desplegarMenuMovimiento), caballo2J2.Menu);
    g_signal_connect_swapped(G_OBJECT(perro1J2.Pieza),   "button-press-event", G_CALLBACK(desplegarMenuMovimiento), perro1J2.Menu);
    g_signal_connect_swapped(G_OBJECT(perro2J2.Pieza),   "button-press-event", G_CALLBACK(desplegarMenuMovimiento), perro2J2.Menu);
    g_signal_connect_swapped(G_OBJECT(gato1J2.Pieza),    "button-press-event", G_CALLBACK(desplegarMenuMovimiento), gato1J2.Menu);
    g_signal_connect_swapped(G_OBJECT(gato2J2.Pieza),    "button-press-event", G_CALLBACK(desplegarMenuMovimiento), gato2J2.Menu);
    g_signal_connect_swapped(G_OBJECT(conejo1J2.Pieza),  "button-press-event", G_CALLBACK(desplegarMenuMovimiento), conejo1J2.Menu);
    g_signal_connect_swapped(G_OBJECT(conejo2J2.Pieza),  "button-press-event", G_CALLBACK(desplegarMenuMovimiento), conejo2J2.Menu);
    g_signal_connect_swapped(G_OBJECT(conejo3J2.Pieza),  "button-press-event", G_CALLBACK(desplegarMenuMovimiento), conejo3J2.Menu);
    g_signal_connect_swapped(G_OBJECT(conejo4J2.Pieza),  "button-press-event", G_CALLBACK(desplegarMenuMovimiento), conejo4J2.Menu);
    g_signal_connect_swapped(G_OBJECT(conejo5J2.Pieza),  "button-press-event", G_CALLBACK(desplegarMenuMovimiento), conejo5J2.Menu);
    g_signal_connect_swapped(G_OBJECT(conejo6J2.Pieza),  "button-press-event", G_CALLBACK(desplegarMenuMovimiento), conejo6J2.Menu);
    g_signal_connect_swapped(G_OBJECT(conejo7J2.Pieza),  "button-press-event", G_CALLBACK(desplegarMenuMovimiento), conejo7J2.Menu);
    g_signal_connect_swapped(G_OBJECT(conejo8J2.Pieza),  "button-press-event", G_CALLBACK(desplegarMenuMovimiento), conejo8J2.Menu);

}

void FNmostrarOPmenusPiezas(){ //(DEPRECADO) Muestra las opciones de los menús
    //Observacion: las llamadas a ciertas funciones de los conejos ("Mover arriba" y "Mover abajo") estan comentadas (pero no eliminadas para posibles pruebas) ya que el conejo no puede retroceder.

    //Jugador 1
    gtk_widget_show_all(elefanteJ1.movimiento.OPmoverArriba);
    gtk_widget_show_all(elefanteJ1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(elefanteJ1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(elefanteJ1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(camelloJ1.movimiento.OPmoverArriba);
    gtk_widget_show_all(camelloJ1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(camelloJ1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(camelloJ1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(caballo1J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(caballo1J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(caballo1J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(caballo1J1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(caballo2J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(caballo2J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(caballo2J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(caballo2J1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(perro1J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(perro1J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(perro1J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(perro1J1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(perro2J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(perro2J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(perro2J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(perro2J1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(gato1J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(gato1J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(gato1J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(gato1J1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(gato2J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(gato2J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(gato2J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(gato2J1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo1J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo1J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo1J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo1J1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo2J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo2J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo2J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo2J1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo3J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo3J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo3J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo3J1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo4J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo4J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo4J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo4J1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo5J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo5J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo5J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo5J1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo6J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo6J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo6J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo6J1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo7J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo7J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo7J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo7J1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo8J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo8J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo8J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo8J1.movimiento.OPmoverIzquierda);

    //Jugador 2
    gtk_widget_show_all(elefanteJ2.movimiento.OPmoverArriba);
    gtk_widget_show_all(elefanteJ2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(elefanteJ2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(elefanteJ2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(camelloJ2.movimiento.OPmoverArriba);
    gtk_widget_show_all(camelloJ2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(camelloJ2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(camelloJ2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(caballo1J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(caballo1J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(caballo1J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(caballo1J2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(caballo2J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(caballo2J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(caballo2J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(caballo2J2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(perro1J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(perro1J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(perro1J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(perro1J2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(perro2J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(perro2J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(perro2J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(perro2J2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(gato1J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(gato1J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(gato1J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(gato1J2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(gato2J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(gato2J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(gato2J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(gato2J2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo1J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo1J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo1J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo1J2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo2J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo2J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo2J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo2J2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo3J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo3J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo3J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo3J2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo4J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo4J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo4J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo4J2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo5J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo5J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo5J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo5J2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo6J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo6J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo6J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo6J2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo7J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo7J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo7J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo7J2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo8J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo8J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo8J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo8J2.movimiento.OPmoverIzquierda);
}

void FNconectarOPMovimientosPiezas(){ //Conecta los submenús para el movimiento a los menús de cada pieza
        ///ABAJO
        ///Mover
        //Jugador 1
        g_signal_connect_swapped(G_OBJECT(elefanteJ1.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), elefanteJ1.Pieza);
        g_signal_connect_swapped(G_OBJECT(camelloJ1.movimiento.OPmoverAbajo),  "button-press-event", G_CALLBACK(FNmoverAbajo), camelloJ1.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo1J1.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), caballo1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo2J1.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), caballo2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro1J1.movimiento.OPmoverAbajo),   "button-press-event", G_CALLBACK(FNmoverAbajo), perro1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro2J1.movimiento.OPmoverAbajo),   "button-press-event", G_CALLBACK(FNmoverAbajo), perro2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato1J1.movimiento.OPmoverAbajo),    "button-press-event", G_CALLBACK(FNmoverAbajo), gato1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato2J1.movimiento.OPmoverAbajo),    "button-press-event", G_CALLBACK(FNmoverAbajo), gato2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo1J1.movimiento.OPmoverAbajo),  "button-press-event", G_CALLBACK(FNmoverAbajo), conejo1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo2J1.movimiento.OPmoverAbajo),  "button-press-event", G_CALLBACK(FNmoverAbajo), conejo2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo3J1.movimiento.OPmoverAbajo),  "button-press-event", G_CALLBACK(FNmoverAbajo), conejo3J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo4J1.movimiento.OPmoverAbajo),  "button-press-event", G_CALLBACK(FNmoverAbajo), conejo4J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo5J1.movimiento.OPmoverAbajo),  "button-press-event", G_CALLBACK(FNmoverAbajo), conejo5J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo6J1.movimiento.OPmoverAbajo),  "button-press-event", G_CALLBACK(FNmoverAbajo), conejo6J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo7J1.movimiento.OPmoverAbajo),  "button-press-event", G_CALLBACK(FNmoverAbajo), conejo7J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo8J1.movimiento.OPmoverAbajo),  "button-press-event", G_CALLBACK(FNmoverAbajo), conejo8J1.Pieza);
        //Jugador 2
        g_signal_connect_swapped(G_OBJECT(elefanteJ2.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), elefanteJ2.Pieza);
        g_signal_connect_swapped(G_OBJECT(camelloJ2.movimiento.OPmoverAbajo),  "button-press-event", G_CALLBACK(FNmoverAbajo), camelloJ2.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo1J2.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), caballo1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo2J2.movimiento.OPmoverAbajo), "button-press-event", G_CALLBACK(FNmoverAbajo), caballo2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro1J2.movimiento.OPmoverAbajo),   "button-press-event", G_CALLBACK(FNmoverAbajo), perro1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro2J2.movimiento.OPmoverAbajo),   "button-press-event", G_CALLBACK(FNmoverAbajo), perro2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato1J2.movimiento.OPmoverAbajo),    "button-press-event", G_CALLBACK(FNmoverAbajo), gato1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato2J2.movimiento.OPmoverAbajo),    "button-press-event", G_CALLBACK(FNmoverAbajo), gato2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo1J2.movimiento.OPmoverAbajo),  "button-press-event", G_CALLBACK(FNmoverAbajo), conejo1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo2J2.movimiento.OPmoverAbajo),  "button-press-event", G_CALLBACK(FNmoverAbajo), conejo2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo3J2.movimiento.OPmoverAbajo),  "button-press-event", G_CALLBACK(FNmoverAbajo), conejo3J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo4J2.movimiento.OPmoverAbajo),  "button-press-event", G_CALLBACK(FNmoverAbajo), conejo4J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo5J2.movimiento.OPmoverAbajo),  "button-press-event", G_CALLBACK(FNmoverAbajo), conejo5J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo6J2.movimiento.OPmoverAbajo),  "button-press-event", G_CALLBACK(FNmoverAbajo), conejo6J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo7J2.movimiento.OPmoverAbajo),  "button-press-event", G_CALLBACK(FNmoverAbajo), conejo7J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo8J2.movimiento.OPmoverAbajo),  "button-press-event", G_CALLBACK(FNmoverAbajo), conejo8J2.Pieza);

        ///ARRIBA
        ///Mover
        //Jugador 1
        g_signal_connect_swapped(G_OBJECT(elefanteJ1.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), elefanteJ1.Pieza);
        g_signal_connect_swapped(G_OBJECT(camelloJ1.movimiento.OPmoverArriba),  "button-press-event", G_CALLBACK(FNmoverArriba), camelloJ1.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo1J1.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), caballo1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo2J1.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), caballo2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro1J1.movimiento.OPmoverArriba),   "button-press-event", G_CALLBACK(FNmoverArriba), perro1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro2J1.movimiento.OPmoverArriba),   "button-press-event", G_CALLBACK(FNmoverArriba), perro2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato1J1.movimiento.OPmoverArriba),    "button-press-event", G_CALLBACK(FNmoverArriba), gato1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato2J1.movimiento.OPmoverArriba),    "button-press-event", G_CALLBACK(FNmoverArriba), gato2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo1J1.movimiento.OPmoverArriba),  "button-press-event", G_CALLBACK(FNmoverArriba), conejo1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo2J1.movimiento.OPmoverArriba),  "button-press-event", G_CALLBACK(FNmoverArriba), conejo2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo3J1.movimiento.OPmoverArriba),  "button-press-event", G_CALLBACK(FNmoverArriba), conejo3J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo4J1.movimiento.OPmoverArriba),  "button-press-event", G_CALLBACK(FNmoverArriba), conejo4J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo5J1.movimiento.OPmoverArriba),  "button-press-event", G_CALLBACK(FNmoverArriba), conejo5J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo6J1.movimiento.OPmoverArriba),  "button-press-event", G_CALLBACK(FNmoverArriba), conejo6J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo7J1.movimiento.OPmoverArriba),  "button-press-event", G_CALLBACK(FNmoverArriba), conejo7J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo8J1.movimiento.OPmoverArriba),  "button-press-event", G_CALLBACK(FNmoverArriba), conejo8J1.Pieza);
        //Jugador2
        g_signal_connect_swapped(G_OBJECT(elefanteJ2.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), elefanteJ2.Pieza);
        g_signal_connect_swapped(G_OBJECT(camelloJ2.movimiento.OPmoverArriba),  "button-press-event", G_CALLBACK(FNmoverArriba), camelloJ2.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo1J2.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), caballo1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo2J2.movimiento.OPmoverArriba), "button-press-event", G_CALLBACK(FNmoverArriba), caballo2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro1J2.movimiento.OPmoverArriba),   "button-press-event", G_CALLBACK(FNmoverArriba), perro1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro2J2.movimiento.OPmoverArriba),   "button-press-event", G_CALLBACK(FNmoverArriba), perro2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato1J2.movimiento.OPmoverArriba),    "button-press-event", G_CALLBACK(FNmoverArriba), gato1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato2J2.movimiento.OPmoverArriba),    "button-press-event", G_CALLBACK(FNmoverArriba), gato2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo1J2.movimiento.OPmoverArriba),  "button-press-event", G_CALLBACK(FNmoverArriba), conejo1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo2J2.movimiento.OPmoverArriba),  "button-press-event", G_CALLBACK(FNmoverArriba), conejo2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo3J2.movimiento.OPmoverArriba),  "button-press-event", G_CALLBACK(FNmoverArriba), conejo3J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo4J2.movimiento.OPmoverArriba),  "button-press-event", G_CALLBACK(FNmoverArriba), conejo4J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo5J2.movimiento.OPmoverArriba),  "button-press-event", G_CALLBACK(FNmoverArriba), conejo5J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo6J2.movimiento.OPmoverArriba),  "button-press-event", G_CALLBACK(FNmoverArriba), conejo6J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo7J2.movimiento.OPmoverArriba),  "button-press-event", G_CALLBACK(FNmoverArriba), conejo7J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo8J2.movimiento.OPmoverArriba),  "button-press-event", G_CALLBACK(FNmoverArriba), conejo8J2.Pieza);


        ///Derecha
        ///Derecha
        //Jugador 1
        g_signal_connect_swapped(G_OBJECT(elefanteJ1.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), elefanteJ1.Pieza);
        g_signal_connect_swapped(G_OBJECT(camelloJ1.movimiento.OPmoverDerecha),  "button-press-event", G_CALLBACK(FNmoverDerecha), camelloJ1.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo1J1.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), caballo1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo2J1.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), caballo2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro1J1.movimiento.OPmoverDerecha),   "button-press-event", G_CALLBACK(FNmoverDerecha), perro1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro2J1.movimiento.OPmoverDerecha),   "button-press-event", G_CALLBACK(FNmoverDerecha), perro2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato1J1.movimiento.OPmoverDerecha),    "button-press-event", G_CALLBACK(FNmoverDerecha), gato1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato2J1.movimiento.OPmoverDerecha),    "button-press-event", G_CALLBACK(FNmoverDerecha), gato2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo1J1.movimiento.OPmoverDerecha),  "button-press-event", G_CALLBACK(FNmoverDerecha), conejo1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo2J1.movimiento.OPmoverDerecha),  "button-press-event", G_CALLBACK(FNmoverDerecha), conejo2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo3J1.movimiento.OPmoverDerecha),  "button-press-event", G_CALLBACK(FNmoverDerecha), conejo3J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo4J1.movimiento.OPmoverDerecha),  "button-press-event", G_CALLBACK(FNmoverDerecha), conejo4J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo5J1.movimiento.OPmoverDerecha),  "button-press-event", G_CALLBACK(FNmoverDerecha), conejo5J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo6J1.movimiento.OPmoverDerecha),  "button-press-event", G_CALLBACK(FNmoverDerecha), conejo6J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo7J1.movimiento.OPmoverDerecha),  "button-press-event", G_CALLBACK(FNmoverDerecha), conejo7J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo8J1.movimiento.OPmoverDerecha),  "button-press-event", G_CALLBACK(FNmoverDerecha), conejo8J1.Pieza);
        // Jugador 2
        g_signal_connect_swapped(G_OBJECT(elefanteJ2.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), elefanteJ2.Pieza);
        g_signal_connect_swapped(G_OBJECT(camelloJ2.movimiento.OPmoverDerecha),  "button-press-event", G_CALLBACK(FNmoverDerecha), camelloJ2.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo1J2.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), caballo1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo2J2.movimiento.OPmoverDerecha), "button-press-event", G_CALLBACK(FNmoverDerecha), caballo2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro1J2.movimiento.OPmoverDerecha),   "button-press-event", G_CALLBACK(FNmoverDerecha), perro1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro2J2.movimiento.OPmoverDerecha),   "button-press-event", G_CALLBACK(FNmoverDerecha), perro2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato1J2.movimiento.OPmoverDerecha),    "button-press-event", G_CALLBACK(FNmoverDerecha), gato1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato2J2.movimiento.OPmoverDerecha),    "button-press-event", G_CALLBACK(FNmoverDerecha), gato2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo1J2.movimiento.OPmoverDerecha),  "button-press-event", G_CALLBACK(FNmoverDerecha), conejo1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo2J2.movimiento.OPmoverDerecha),  "button-press-event", G_CALLBACK(FNmoverDerecha), conejo2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo3J2.movimiento.OPmoverDerecha),  "button-press-event", G_CALLBACK(FNmoverDerecha), conejo3J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo4J2.movimiento.OPmoverDerecha),  "button-press-event", G_CALLBACK(FNmoverDerecha), conejo4J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo5J2.movimiento.OPmoverDerecha),  "button-press-event", G_CALLBACK(FNmoverDerecha), conejo5J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo6J2.movimiento.OPmoverDerecha),  "button-press-event", G_CALLBACK(FNmoverDerecha), conejo6J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo7J2.movimiento.OPmoverDerecha),  "button-press-event", G_CALLBACK(FNmoverDerecha), conejo7J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo8J2.movimiento.OPmoverDerecha),  "button-press-event", G_CALLBACK(FNmoverDerecha), conejo8J2.Pieza);


        ///Izquierda
        ///Mover
        //Jugador 1
        g_signal_connect_swapped(G_OBJECT(elefanteJ1.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), elefanteJ1.Pieza);
        g_signal_connect_swapped(G_OBJECT(camelloJ1.movimiento.OPmoverIzquierda),  "button-press-event", G_CALLBACK(FNmoverIzquierda), camelloJ1.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo1J1.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), caballo1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo2J1.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), caballo2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro1J1.movimiento.OPmoverIzquierda),   "button-press-event", G_CALLBACK(FNmoverIzquierda), perro1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro2J1.movimiento.OPmoverIzquierda),   "button-press-event", G_CALLBACK(FNmoverIzquierda), perro2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato1J1.movimiento.OPmoverIzquierda),    "button-press-event", G_CALLBACK(FNmoverIzquierda), gato1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato2J1.movimiento.OPmoverIzquierda),    "button-press-event", G_CALLBACK(FNmoverIzquierda), gato2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo1J1.movimiento.OPmoverIzquierda),  "button-press-event", G_CALLBACK(FNmoverIzquierda), conejo1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo2J1.movimiento.OPmoverIzquierda),  "button-press-event", G_CALLBACK(FNmoverIzquierda), conejo2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo3J1.movimiento.OPmoverIzquierda),  "button-press-event", G_CALLBACK(FNmoverIzquierda), conejo3J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo4J1.movimiento.OPmoverIzquierda),  "button-press-event", G_CALLBACK(FNmoverIzquierda), conejo4J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo5J1.movimiento.OPmoverIzquierda),  "button-press-event", G_CALLBACK(FNmoverIzquierda), conejo5J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo6J1.movimiento.OPmoverIzquierda),  "button-press-event", G_CALLBACK(FNmoverIzquierda), conejo6J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo7J1.movimiento.OPmoverIzquierda),  "button-press-event", G_CALLBACK(FNmoverIzquierda), conejo7J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo8J1.movimiento.OPmoverIzquierda),  "button-press-event", G_CALLBACK(FNmoverIzquierda), conejo8J1.Pieza);
        //Jugador 2
        g_signal_connect_swapped(G_OBJECT(elefanteJ2.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), elefanteJ2.Pieza);
        g_signal_connect_swapped(G_OBJECT(camelloJ2.movimiento.OPmoverIzquierda),  "button-press-event", G_CALLBACK(FNmoverIzquierda), camelloJ2.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo1J2.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), caballo1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo2J2.movimiento.OPmoverIzquierda), "button-press-event", G_CALLBACK(FNmoverIzquierda), caballo2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro1J2.movimiento.OPmoverIzquierda),   "button-press-event", G_CALLBACK(FNmoverIzquierda), perro1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro2J2.movimiento.OPmoverIzquierda),   "button-press-event", G_CALLBACK(FNmoverIzquierda), perro2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato1J2.movimiento.OPmoverIzquierda),    "button-press-event", G_CALLBACK(FNmoverIzquierda), gato1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato2J2.movimiento.OPmoverIzquierda),    "button-press-event", G_CALLBACK(FNmoverIzquierda), gato2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo1J2.movimiento.OPmoverIzquierda),  "button-press-event", G_CALLBACK(FNmoverIzquierda), conejo1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo2J2.movimiento.OPmoverIzquierda),  "button-press-event", G_CALLBACK(FNmoverIzquierda), conejo2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo3J2.movimiento.OPmoverIzquierda),  "button-press-event", G_CALLBACK(FNmoverIzquierda), conejo3J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo4J2.movimiento.OPmoverIzquierda),  "button-press-event", G_CALLBACK(FNmoverIzquierda), conejo4J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo5J2.movimiento.OPmoverIzquierda),  "button-press-event", G_CALLBACK(FNmoverIzquierda), conejo5J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo6J2.movimiento.OPmoverIzquierda),  "button-press-event", G_CALLBACK(FNmoverIzquierda), conejo6J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo7J2.movimiento.OPmoverIzquierda),  "button-press-event", G_CALLBACK(FNmoverIzquierda), conejo7J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo8J2.movimiento.OPmoverIzquierda),  "button-press-event", G_CALLBACK(FNmoverIzquierda), conejo8J2.Pieza);

}

void FNconectarOPempujarOestirarPiezas(){
     /// ABAJO
    ///Estirar
       // Jugador 1
        g_signal_connect_swapped(G_OBJECT(elefanteJ1.movimiento.OPestirarAbajo), "button-press-event", G_CALLBACK(FNestirarAbajoJ1), elefanteJ1.Pieza);
        g_signal_connect_swapped(G_OBJECT(camelloJ1.movimiento.OPestirarAbajo),  "button-press-event", G_CALLBACK(FNestirarAbajoJ1), camelloJ1.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo1J1.movimiento.OPestirarAbajo), "button-press-event", G_CALLBACK(FNestirarAbajoJ1), caballo1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo2J1.movimiento.OPestirarAbajo), "button-press-event", G_CALLBACK(FNestirarAbajoJ1), caballo2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro1J1.movimiento.OPestirarAbajo),   "button-press-event", G_CALLBACK(FNestirarAbajoJ1), perro1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro2J1.movimiento.OPestirarAbajo),   "button-press-event", G_CALLBACK(FNestirarAbajoJ1), perro2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato1J1.movimiento.OPestirarAbajo),    "button-press-event", G_CALLBACK(FNestirarAbajoJ1), gato1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato2J1.movimiento.OPestirarAbajo),    "button-press-event", G_CALLBACK(FNestirarAbajoJ1), gato2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo1J1.movimiento.OPestirarAbajo),  "button-press-event", G_CALLBACK(FNestirarAbajoJ1), conejo1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo2J1.movimiento.OPestirarAbajo),  "button-press-event", G_CALLBACK(FNestirarAbajoJ1), conejo2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo3J1.movimiento.OPestirarAbajo),  "button-press-event", G_CALLBACK(FNestirarAbajoJ1), conejo3J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo4J1.movimiento.OPestirarAbajo),  "button-press-event", G_CALLBACK(FNestirarAbajoJ1), conejo4J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo5J1.movimiento.OPestirarAbajo),  "button-press-event", G_CALLBACK(FNestirarAbajoJ1), conejo5J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo6J1.movimiento.OPestirarAbajo),  "button-press-event", G_CALLBACK(FNestirarAbajoJ1), conejo6J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo7J1.movimiento.OPestirarAbajo),  "button-press-event", G_CALLBACK(FNestirarAbajoJ1), conejo7J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo8J1.movimiento.OPestirarAbajo),  "button-press-event", G_CALLBACK(FNestirarAbajoJ1), conejo8J1.Pieza);
        ///Empujar
        //Jugador 2
        g_signal_connect_swapped(G_OBJECT(elefanteJ2.movimiento.OPempujarAbajo), "button-press-event", G_CALLBACK(FNempujarAbajoJ2), elefanteJ2.Pieza);
        g_signal_connect_swapped(G_OBJECT(camelloJ2.movimiento.OPempujarAbajo),  "button-press-event", G_CALLBACK(FNempujarAbajoJ2), camelloJ2.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo1J2.movimiento.OPempujarAbajo), "button-press-event", G_CALLBACK(FNempujarAbajoJ2), caballo1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo2J2.movimiento.OPempujarAbajo), "button-press-event", G_CALLBACK(FNempujarAbajoJ2), caballo2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro1J2.movimiento.OPempujarAbajo),   "button-press-event", G_CALLBACK(FNempujarAbajoJ2), perro1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro2J2.movimiento.OPempujarAbajo),   "button-press-event", G_CALLBACK(FNempujarAbajoJ2), perro2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato1J2.movimiento.OPempujarAbajo),    "button-press-event", G_CALLBACK(FNempujarAbajoJ2), gato1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato2J2.movimiento.OPempujarAbajo),    "button-press-event", G_CALLBACK(FNempujarAbajoJ2), gato2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo1J2.movimiento.OPempujarAbajo),  "button-press-event", G_CALLBACK(FNempujarAbajoJ2), conejo1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo2J2.movimiento.OPempujarAbajo),  "button-press-event", G_CALLBACK(FNempujarAbajoJ2), conejo2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo3J2.movimiento.OPempujarAbajo),  "button-press-event", G_CALLBACK(FNempujarAbajoJ2), conejo3J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo4J2.movimiento.OPempujarAbajo),  "button-press-event", G_CALLBACK(FNempujarAbajoJ2), conejo4J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo5J2.movimiento.OPempujarAbajo),  "button-press-event", G_CALLBACK(FNempujarAbajoJ2), conejo5J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo6J2.movimiento.OPempujarAbajo),  "button-press-event", G_CALLBACK(FNempujarAbajoJ2), conejo6J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo7J2.movimiento.OPempujarAbajo),  "button-press-event", G_CALLBACK(FNempujarAbajoJ2), conejo7J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo8J2.movimiento.OPempujarAbajo),  "button-press-event", G_CALLBACK(FNempujarAbajoJ2), conejo8J2.Pieza);

        //ARRIBA
        //Empujar
        //Jugador 1
        g_signal_connect_swapped(G_OBJECT(elefanteJ1.movimiento.OPempujarArriba), "button-press-event", G_CALLBACK(FNempujarArribaJ1), elefanteJ1.Pieza);
        g_signal_connect_swapped(G_OBJECT(camelloJ1.movimiento.OPempujarArriba),  "button-press-event", G_CALLBACK(FNempujarArribaJ1), camelloJ1.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo1J1.movimiento.OPempujarArriba), "button-press-event", G_CALLBACK(FNempujarArribaJ1), caballo1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo2J1.movimiento.OPempujarArriba), "button-press-event", G_CALLBACK(FNempujarArribaJ1), caballo2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro1J1.movimiento.OPempujarArriba),   "button-press-event", G_CALLBACK(FNempujarArribaJ1), perro1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro2J1.movimiento.OPempujarArriba),   "button-press-event", G_CALLBACK(FNempujarArribaJ1), perro2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato1J1.movimiento.OPempujarArriba),    "button-press-event", G_CALLBACK(FNempujarArribaJ1), gato1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato2J1.movimiento.OPempujarArriba),    "button-press-event", G_CALLBACK(FNempujarArribaJ1), gato2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo1J1.movimiento.OPempujarArriba),  "button-press-event", G_CALLBACK(FNempujarArribaJ1), conejo1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo2J1.movimiento.OPempujarArriba),  "button-press-event", G_CALLBACK(FNempujarArribaJ1), conejo2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo3J1.movimiento.OPempujarArriba),  "button-press-event", G_CALLBACK(FNempujarArribaJ1), conejo3J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo4J1.movimiento.OPempujarArriba),  "button-press-event", G_CALLBACK(FNempujarArribaJ1), conejo4J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo5J1.movimiento.OPempujarArriba),  "button-press-event", G_CALLBACK(FNempujarArribaJ1), conejo5J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo6J1.movimiento.OPempujarArriba),  "button-press-event", G_CALLBACK(FNempujarArribaJ1), conejo6J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo7J1.movimiento.OPempujarArriba),  "button-press-event", G_CALLBACK(FNempujarArribaJ1), conejo7J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo8J1.movimiento.OPempujarArriba),  "button-press-event", G_CALLBACK(FNempujarArribaJ1), conejo8J1.Pieza);
        //Estirar
        //Jugador2
        g_signal_connect_swapped(G_OBJECT(elefanteJ2.movimiento.OPestirarArriba), "button-press-event", G_CALLBACK(FNestirarArribaJ2), elefanteJ2.Pieza);
        g_signal_connect_swapped(G_OBJECT(camelloJ2.movimiento.OPestirarArriba),  "button-press-event", G_CALLBACK(FNestirarArribaJ2), camelloJ2.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo1J2.movimiento.OPestirarArriba), "button-press-event", G_CALLBACK(FNestirarArribaJ2), caballo1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo2J2.movimiento.OPestirarArriba), "button-press-event", G_CALLBACK(FNestirarArribaJ2), caballo2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro1J2.movimiento.OPestirarArriba),   "button-press-event", G_CALLBACK(FNestirarArribaJ2), perro1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro2J2.movimiento.OPestirarArriba),   "button-press-event", G_CALLBACK(FNestirarArribaJ2), perro2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato1J2.movimiento.OPestirarArriba),    "button-press-event", G_CALLBACK(FNestirarArribaJ2), gato1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato2J2.movimiento.OPestirarArriba),    "button-press-event", G_CALLBACK(FNestirarArribaJ2), gato2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo1J2.movimiento.OPestirarArriba),  "button-press-event", G_CALLBACK(FNestirarArribaJ2), conejo1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo2J2.movimiento.OPestirarArriba),  "button-press-event", G_CALLBACK(FNestirarArribaJ2), conejo2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo3J2.movimiento.OPestirarArriba),  "button-press-event", G_CALLBACK(FNestirarArribaJ2), conejo3J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo4J2.movimiento.OPestirarArriba),  "button-press-event", G_CALLBACK(FNestirarArribaJ2), conejo4J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo5J2.movimiento.OPestirarArriba),  "button-press-event", G_CALLBACK(FNestirarArribaJ2), conejo5J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo6J2.movimiento.OPestirarArriba),  "button-press-event", G_CALLBACK(FNestirarArribaJ2), conejo6J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo7J2.movimiento.OPestirarArriba),  "button-press-event", G_CALLBACK(FNestirarArribaJ2), conejo7J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo8J2.movimiento.OPestirarArriba),  "button-press-event", G_CALLBACK(FNestirarArribaJ2), conejo8J2.Pieza);

/// Derecha
    ///Estirar
       // Jugador 1
     //   g_signal_connect_swapped(G_OBJECT(elefanteJ1.movimiento.OPestirarDerecha), "button-press-event", G_CALLBACK(FNestirarDerechaJ1), elefanteJ1.Pieza);
       // g_signal_connect_swapped(G_OBJECT(camelloJ1.movimiento.OPestirarDerecha),  "button-press-event", G_CALLBACK(FNestirarDerechaJ1), camelloJ1.Pieza);
       //  g_signal_connect_swapped(G_OBJECT(caballo1J1.movimiento.OPestirarDerecha), "button-press-event", G_CALLBACK(FNestirarDerechaJ1), caballo1J1.Pieza);
       //  g_signal_connect_swapped(G_OBJECT(caballo2J1.movimiento.OPestirarDerecha), "button-press-event", G_CALLBACK(FNestirarDerechaJ1), caballo2J1.Pieza);
       //  g_signal_connect_swapped(G_OBJECT(perro1J1.movimiento.OPestirarDerecha),   "button-press-event", G_CALLBACK(FNestirarDerechaJ1), perro1J1.Pieza);
       //  g_signal_connect_swapped(G_OBJECT(perro2J1.movimiento.OPestirarDerecha),   "button-press-event", G_CALLBACK(FNestirarDerechaJ1), perro2J1.Pieza);
//         g_signal_connect_swapped(G_OBJECT(gato1J1.movimiento.OPestirarDerecha),    "button-press-event", G_CALLBACK(FNestirarDerechaJ1), gato1J1.Pieza);
   //      g_signal_connect_swapped(G_OBJECT(gato2J1.movimiento.OPestirarDerecha),    "button-press-event", G_CALLBACK(FNestirarDerechaJ1), gato2J1.Pieza);
      //   g_signal_connect_swapped(G_OBJECT(conejo1J1.movimiento.OPestirarDerecha),  "button-press-event", G_CALLBACK(FNestirarDerechaJ1), conejo1J1.Pieza);
        // g_signal_connect_swapped(G_OBJECT(conejo2J1.movimiento.OPestirarDerecha),  "button-press-event", G_CALLBACK(FNestirarDerechaJ1), conejo2J1.Pieza);
        // g_signal_connect_swapped(G_OBJECT(conejo3J1.movimiento.OPestirarDerecha),  "button-press-event", G_CALLBACK(FNestirarDerechaJ1), conejo3J1.Pieza);
       //  g_signal_connect_swapped(G_OBJECT(conejo4J1.movimiento.OPestirarDerecha),  "button-press-event", G_CALLBACK(FNestirarDerechaJ1), conejo4J1.Pieza);
       //  g_signal_connect_swapped(G_OBJECT(conejo5J1.movimiento.OPestirarDerecha),  "button-press-event", G_CALLBACK(FNestirarDerechaJ1), conejo5J1.Pieza);
      //   g_signal_connect_swapped(G_OBJECT(conejo6J1.movimiento.OPestirarDerecha),  "button-press-event", G_CALLBACK(FNestirarDerechaJ1), conejo6J1.Pieza);
      //   g_signal_connect_swapped(G_OBJECT(conejo7J1.movimiento.OPestirarDerecha),  "button-press-event", G_CALLBACK(FNestirarDerechaJ1), conejo7J1.Pieza);
      //   g_signal_connect_swapped(G_OBJECT(conejo8J1.movimiento.OPestirarDerecha),  "button-press-event", G_CALLBACK(FNestirarDerechaJ1), conejo8J1.Pieza);
        ///Empujar
        //Jugador 2
        g_signal_connect_swapped(G_OBJECT(elefanteJ2.movimiento.OPempujarDerecha), "button-press-event", G_CALLBACK(FNempujarDerechaJ2), elefanteJ2.Pieza);
        g_signal_connect_swapped(G_OBJECT(camelloJ2.movimiento.OPempujarDerecha),  "button-press-event", G_CALLBACK(FNempujarDerechaJ2), camelloJ2.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo1J2.movimiento.OPempujarDerecha), "button-press-event", G_CALLBACK(FNempujarDerechaJ2), caballo1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo2J2.movimiento.OPempujarDerecha), "button-press-event", G_CALLBACK(FNempujarDerechaJ2), caballo2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro1J2.movimiento.OPempujarDerecha),   "button-press-event", G_CALLBACK(FNempujarDerechaJ2), perro1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro2J2.movimiento.OPempujarDerecha),   "button-press-event", G_CALLBACK(FNempujarDerechaJ2), perro2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato1J2.movimiento.OPempujarDerecha),    "button-press-event", G_CALLBACK(FNempujarDerechaJ2), gato1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato2J2.movimiento.OPempujarDerecha),    "button-press-event", G_CALLBACK(FNempujarDerechaJ2), gato2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo1J2.movimiento.OPempujarDerecha),  "button-press-event", G_CALLBACK(FNempujarDerechaJ2), conejo1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo2J2.movimiento.OPempujarDerecha),  "button-press-event", G_CALLBACK(FNempujarDerechaJ2), conejo2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo3J2.movimiento.OPempujarDerecha),  "button-press-event", G_CALLBACK(FNempujarDerechaJ2), conejo3J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo4J2.movimiento.OPempujarDerecha),  "button-press-event", G_CALLBACK(FNempujarDerechaJ2), conejo4J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo5J2.movimiento.OPempujarDerecha),  "button-press-event", G_CALLBACK(FNempujarDerechaJ2), conejo5J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo6J2.movimiento.OPempujarDerecha),  "button-press-event", G_CALLBACK(FNempujarDerechaJ2), conejo6J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo7J2.movimiento.OPempujarDerecha),  "button-press-event", G_CALLBACK(FNempujarDerechaJ2), conejo7J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo8J2.movimiento.OPempujarDerecha),  "button-press-event", G_CALLBACK(FNempujarDerechaJ2), conejo8J2.Pieza);



        //Izquierda
       // Jugador 1
        g_signal_connect_swapped(G_OBJECT(elefanteJ1.movimiento.OPempujarIzquierda), "button-press-event", G_CALLBACK(FNempujarIzquierdaJ1), elefanteJ1.Pieza);
        g_signal_connect_swapped(G_OBJECT(camelloJ1.movimiento.OPempujarIzquierda),  "button-press-event", G_CALLBACK(FNempujarIzquierdaJ1), camelloJ1.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo1J1.movimiento.OPempujarIzquierda), "button-press-event", G_CALLBACK(FNempujarIzquierdaJ1), caballo1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo2J1.movimiento.OPempujarIzquierda), "button-press-event", G_CALLBACK(FNempujarIzquierdaJ1), caballo2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro1J1.movimiento.OPempujarIzquierda),   "button-press-event", G_CALLBACK(FNempujarIzquierdaJ1), perro1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro2J1.movimiento.OPempujarIzquierda),   "button-press-event", G_CALLBACK(FNempujarIzquierdaJ1), perro2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato1J1.movimiento.OPempujarIzquierda),    "button-press-event", G_CALLBACK(FNempujarIzquierdaJ1), gato1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato2J1.movimiento.OPempujarIzquierda),    "button-press-event", G_CALLBACK(FNempujarIzquierdaJ1), gato2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo1J1.movimiento.OPempujarIzquierda),  "button-press-event", G_CALLBACK(FNempujarIzquierdaJ1), conejo1J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo2J1.movimiento.OPempujarIzquierda),  "button-press-event", G_CALLBACK(FNempujarIzquierdaJ1), conejo2J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo3J1.movimiento.OPempujarIzquierda),  "button-press-event", G_CALLBACK(FNempujarIzquierdaJ1), conejo3J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo4J1.movimiento.OPempujarIzquierda),  "button-press-event", G_CALLBACK(FNempujarIzquierdaJ1), conejo4J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo5J1.movimiento.OPempujarIzquierda),  "button-press-event", G_CALLBACK(FNempujarIzquierdaJ1), conejo5J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo6J1.movimiento.OPempujarIzquierda),  "button-press-event", G_CALLBACK(FNempujarIzquierdaJ1), conejo6J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo7J1.movimiento.OPempujarIzquierda),  "button-press-event", G_CALLBACK(FNempujarIzquierdaJ1), conejo7J1.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo8J1.movimiento.OPempujarIzquierda),  "button-press-event", G_CALLBACK(FNempujarIzquierdaJ1), conejo8J1.Pieza);
//         g_signal_connect_swapped(G_OBJECT(elefanteJ1.movimiento.OPestirarIzquierda), "button-press-event", G_CALLBACK(FNestirarIzquierdaJ1), elefanteJ1.Pieza);
 //        g_signal_connect_swapped(G_OBJECT(camelloJ1.movimiento.OPestirarIzquierda),  "button-press-event", G_CALLBACK(FNestirarIzquierdaJ1), camelloJ1.Pieza);
 //        g_signal_connect_swapped(G_OBJECT(caballo1J1.movimiento.OPestirarIzquierda), "button-press-event", G_CALLBACK(FNestirarIzquierdaJ1), caballo1J1.Pieza);
//         g_signal_connect_swapped(G_OBJECT(caballo2J1.movimiento.OPestirarIzquierda), "button-press-event", G_CALLBACK(FNestirarIzquierdaJ1), caballo2J1.Pieza);
 //        g_signal_connect_swapped(G_OBJECT(perro1J1.movimiento.OPestirarIzquierda),   "button-press-event", G_CALLBACK(FNestirarIzquierdaJ1), perro1J1.Pieza);
 //        g_signal_connect_swapped(G_OBJECT(perro2J1.movimiento.OPestirarIzquierda),   "button-press-event", G_CALLBACK(FNestirarIzquierdaJ1), perro2J1.Pieza);
 //        g_signal_connect_swapped(G_OBJECT(gato1J1.movimiento.OPestirarIzquierda),    "button-press-event", G_CALLBACK(FNestirarIzquierdaJ1), gato1J1.Pieza);
 //        g_signal_connect_swapped(G_OBJECT(gato2J1.movimiento.OPestirarIzquierda),    "button-press-event", G_CALLBACK(FNestirarIzquierdaJ1), gato2J1.Pieza);
 //        g_signal_connect_swapped(G_OBJECT(conejo1J1.movimiento.OPestirarIzquierda),  "button-press-event", G_CALLBACK(FNestirarIzquierdaJ1), conejo1J1.Pieza);
 //        g_signal_connect_swapped(G_OBJECT(conejo2J1.movimiento.OPestirarIzquierda),  "button-press-event", G_CALLBACK(FNestirarIzquierdaJ1), conejo2J1.Pieza);
 //        g_signal_connect_swapped(G_OBJECT(conejo3J1.movimiento.OPestirarIzquierda),  "button-press-event", G_CALLBACK(FNestirarIzquierdaJ1), conejo3J1.Pieza);
 //        g_signal_connect_swapped(G_OBJECT(conejo4J1.movimiento.OPestirarIzquierda),  "button-press-event", G_CALLBACK(FNestirarIzquierdaJ1), conejo4J1.Pieza);
  //       g_signal_connect_swapped(G_OBJECT(conejo5J1.movimiento.OPestirarIzquierda),  "button-press-event", G_CALLBACK(FNestirarIzquierdaJ1), conejo5J1.Pieza);
  //       g_signal_connect_swapped(G_OBJECT(conejo6J1.movimiento.OPestirarIzquierda),  "button-press-event", G_CALLBACK(FNestirarIzquierdaJ1), conejo6J1.Pieza);
  //       g_signal_connect_swapped(G_OBJECT(conejo7J1.movimiento.OPestirarIzquierda),  "button-press-event", G_CALLBACK(FNestirarIzquierdaJ1), conejo7J1.Pieza);
  //       g_signal_connect_swapped(G_OBJECT(conejo8J1.movimiento.OPestirarIzquierda),  "button-press-event", G_CALLBACK(FNestirarIzquierdaJ1), conejo8J1.Pieza);

        // Jugador 2
        g_signal_connect_swapped(G_OBJECT(elefanteJ2.movimiento.OPempujarIzquierda), "button-press-event", G_CALLBACK(FNempujarIzquierdaJ2), elefanteJ2.Pieza);
        g_signal_connect_swapped(G_OBJECT(camelloJ2.movimiento.OPempujarIzquierda),  "button-press-event", G_CALLBACK(FNempujarIzquierdaJ2), camelloJ2.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo1J2.movimiento.OPempujarIzquierda), "button-press-event", G_CALLBACK(FNempujarIzquierdaJ2), caballo1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(caballo2J2.movimiento.OPempujarIzquierda), "button-press-event", G_CALLBACK(FNempujarIzquierdaJ2), caballo2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro1J2.movimiento.OPempujarIzquierda),   "button-press-event", G_CALLBACK(FNempujarIzquierdaJ2), perro1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(perro2J2.movimiento.OPempujarIzquierda),   "button-press-event", G_CALLBACK(FNempujarIzquierdaJ2), perro2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato1J2.movimiento.OPempujarIzquierda),    "button-press-event", G_CALLBACK(FNempujarIzquierdaJ2), gato1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(gato2J2.movimiento.OPempujarIzquierda),    "button-press-event", G_CALLBACK(FNempujarIzquierdaJ2), gato2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo1J2.movimiento.OPempujarIzquierda),  "button-press-event", G_CALLBACK(FNempujarIzquierdaJ2), conejo1J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo2J2.movimiento.OPempujarIzquierda),  "button-press-event", G_CALLBACK(FNempujarIzquierdaJ2), conejo2J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo3J2.movimiento.OPempujarIzquierda),  "button-press-event", G_CALLBACK(FNempujarIzquierdaJ2), conejo3J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo4J2.movimiento.OPempujarIzquierda),  "button-press-event", G_CALLBACK(FNempujarIzquierdaJ2), conejo4J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo5J2.movimiento.OPempujarIzquierda),  "button-press-event", G_CALLBACK(FNempujarIzquierdaJ2), conejo5J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo6J2.movimiento.OPempujarIzquierda),  "button-press-event", G_CALLBACK(FNempujarIzquierdaJ2), conejo6J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo7J2.movimiento.OPempujarIzquierda),  "button-press-event", G_CALLBACK(FNempujarIzquierdaJ2), conejo7J2.Pieza);
        g_signal_connect_swapped(G_OBJECT(conejo8J2.movimiento.OPempujarIzquierda),  "button-press-event", G_CALLBACK(FNempujarIzquierdaJ2), conejo8J2.Pieza);
//         g_signal_connect_swapped(G_OBJECT(elefanteJ2.movimiento.OPestirarIzquierda), "button-press-event", G_CALLBACK(FNestirarIzquierdaJ2), elefanteJ2.Pieza);
 //        g_signal_connect_swapped(G_OBJECT(camelloJ2.movimiento.OPestirarIzquierda),  "button-press-event", G_CALLBACK(FNestirarIzquierdaJ2), camelloJ2.Pieza);
 //        g_signal_connect_swapped(G_OBJECT(caballo1J2.movimiento.OPestirarIzquierda), "button-press-event", G_CALLBACK(FNestirarIzquierdaJ2), caballo1J2.Pieza);
 //        g_signal_connect_swapped(G_OBJECT(caballo2J2.movimiento.OPestirarIzquierda), "button-press-event", G_CALLBACK(FNestirarIzquierdaJ2), caballo2J2.Pieza);
//         g_signal_connect_swapped(G_OBJECT(perro1J2.movimiento.OPestirarIzquierda),   "button-press-event", G_CALLBACK(FNestirarIzquierdaJ2), perro1J2.Pieza);
 //        g_signal_connect_swapped(G_OBJECT(perro2J2.movimiento.OPestirarIzquierda),   "button-press-event", G_CALLBACK(FNestirarIzquierdaJ2), perro2J2.Pieza);
 //        g_signal_connect_swapped(G_OBJECT(gato1J2.movimiento.OPestirarIzquierda),    "button-press-event", G_CALLBACK(FNestirarIzquierdaJ2), gato1J2.Pieza);
//         g_signal_connect_swapped(G_OBJECT(gato2J2.movimiento.OPestirarIzquierda),    "button-press-event", G_CALLBACK(FNestirarIzquierdaJ2), gato2J2.Pieza);
 //        g_signal_connect_swapped(G_OBJECT(conejo1J2.movimiento.OPestirarIzquierda),  "button-press-event", G_CALLBACK(FNestirarIzquierdaJ2), conejo1J2.Pieza);
 //        g_signal_connect_swapped(G_OBJECT(conejo2J2.movimiento.OPestirarIzquierda),  "button-press-event", G_CALLBACK(FNestirarIzquierdaJ2), conejo2J2.Pieza);
//         g_signal_connect_swapped(G_OBJECT(conejo3J2.movimiento.OPestirarIzquierda),  "button-press-event", G_CALLBACK(FNestirarIzquierdaJ2), conejo3J2.Pieza);
 //        g_signal_connect_swapped(G_OBJECT(conejo4J2.movimiento.OPestirarIzquierda),  "button-press-event", G_CALLBACK(FNestirarIzquierdaJ2), conejo4J2.Pieza);
 //        g_signal_connect_swapped(G_OBJECT(conejo5J2.movimiento.OPestirarIzquierda),  "button-press-event", G_CALLBACK(FNestirarIzquierdaJ2), conejo5J2.Pieza);
//         g_signal_connect_swapped(G_OBJECT(conejo6J2.movimiento.OPestirarIzquierda),  "button-press-event", G_CALLBACK(FNestirarIzquierdaJ2), conejo6J2.Pieza);
 //        g_signal_connect_swapped(G_OBJECT(conejo7J2.movimiento.OPestirarIzquierda),  "button-press-event", G_CALLBACK(FNestirarIzquierdaJ2), conejo7J2.Pieza);
 //        g_signal_connect_swapped(G_OBJECT(conejo8J2.movimiento.OPestirarIzquierda),  "button-press-event", G_CALLBACK(FNestirarIzquierdaJ2), conejo8J2.Pieza);


}

///CONTROL DE LOS MOVIMIENTOS
void FNconfigMovimientoPiezas(){ //Llama de forma ordenada a las funciones encargadas del movimiento de las piezas.

    FNcrearMenusPiezas();
    FNconectarMenusPiezas();
    FNconectarOPMovimientosPiezas();
    FNconectarOPempujarOestirarPiezas();

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
    if(pieza == elefanteJ1.Pieza){
        piezaActual = ELEFANTEJ1;
        pesoActual = elefanteJ1.Peso;
        jugadorActual = J1;
    }
    else{
        if(pieza == camelloJ1.Pieza){
            piezaActual = CAMELLOJ1;
            pesoActual = camelloJ1.Peso;
            jugadorActual = J1;
        }
        else{
            if(pieza == caballo1J1.Pieza){
                piezaActual = CABALLO1J1;
                pesoActual = caballo1J1.Peso;
                jugadorActual = J1;
            }
            else{
                if(pieza == caballo2J1.Pieza){
                    piezaActual = CABALLO2J1;
                    pesoActual = caballo2J1.Peso;
                    jugadorActual = J1;
                }
                else{
                    if(pieza == perro1J1.Pieza){
                        piezaActual = PERRO1J1;
                        pesoActual = perro1J1.Peso;
                        jugadorActual = J1;
                    }
                    else{
                        if(pieza == perro2J1.Pieza){
                            piezaActual = PERRO2J1;
                            pesoActual = perro2J1.Peso;
                            jugadorActual = J1;
                        }
                        else{
                            if(pieza == gato1J1.Pieza){
                                piezaActual = GATO1J1;
                                pesoActual = gato1J1.Peso;
                                jugadorActual = J1;
                            }
                            else{
                                if(pieza == gato2J1.Pieza){
                                    piezaActual = GATO2J1;
                                    pesoActual = gato2J1.Peso;
                                    jugadorActual = J1;
                                }
                                else{
                                    if(pieza == conejo1J1.Pieza){
                                       piezaActual = CONEJO1J1;
                                       pesoActual = conejo1J1.Peso;
                                       jugadorActual = J1;
                                    }
                                    else{
                                        if(pieza == conejo2J1.Pieza){
                                            piezaActual = CONEJO2J1;
                                            pesoActual = conejo2J1.Peso;
                                            jugadorActual = J1;
                                        }
                                        else{
                                            if(pieza == conejo3J1.Pieza){
                                                piezaActual = CONEJO3J1;
                                                pesoActual = conejo3J1.Peso;
                                                jugadorActual = J1;
                                            }
                                            else{
                                                if(pieza == conejo4J1.Pieza){
                                                    piezaActual = CONEJO4J1;
                                                    pesoActual = conejo4J1.Peso;
                                                    jugadorActual = J1;
                                                }
                                                else{
                                                    if(pieza == conejo5J1.Pieza){
                                                        piezaActual = CONEJO5J1;
                                                        pesoActual = conejo5J1.Peso;
                                                        jugadorActual = J1;
                                                    }
                                                    else{
                                                        if(pieza == conejo6J1.Pieza){
                                                            piezaActual = CONEJO6J1;
                                                            pesoActual = conejo6J1.Peso;
                                                            jugadorActual = J1;
                                                        }
                                                        else{
                                                            if(pieza == conejo7J1.Pieza){
                                                                piezaActual = CONEJO7J1;
                                                                pesoActual = conejo7J1.Peso;
                                                                jugadorActual = J1;
                                                            }
                                                            else{
                                                                if(pieza == conejo8J1.Pieza){
                                                                   piezaActual = CONEJO8J1;
                                                                   pesoActual = conejo8J1.Peso;
                                                                   jugadorActual = J1;
                                                                }
                                                                else{
                                                                    if(pieza == elefanteJ2.Pieza){
                                                                        piezaActual = ELEFANTEJ2;
                                                                        pesoActual = elefanteJ2.Peso;
                                                                        jugadorActual = J2;
                                                                    }
                                                                    else{
                                                                        if(pieza == camelloJ2.Pieza){
                                                                            piezaActual = CAMELLOJ2;
                                                                            pesoActual = camelloJ2.Peso;
                                                                            jugadorActual = J2;
                                                                        }
                                                                        else{
                                                                            if(pieza == caballo1J2.Pieza){
                                                                                piezaActual = CABALLO1J2;
                                                                                pesoActual = caballo1J2.Peso;
                                                                                jugadorActual = J2;
                                                                            }
                                                                            else{
                                                                                if(pieza == caballo2J2.Pieza){
                                                                                    piezaActual = CABALLO2J2;
                                                                                    pesoActual = caballo2J2.Peso;
                                                                                    jugadorActual = J2;
                                                                                }
                                                                                else{
                                                                                    if(pieza == perro1J2.Pieza){
                                                                                        piezaActual = PERRO1J2;
                                                                                        pesoActual = perro1J2.Peso;
                                                                                        jugadorActual = J2;
                                                                                    }
                                                                                    else{
                                                                                        if(pieza == perro2J2.Pieza){
                                                                                            piezaActual = PERRO2J2;
                                                                                            pesoActual = perro2J2.Peso;
                                                                                            jugadorActual = J2;
                                                                                        }
                                                                                        else{
                                                                                            if(pieza == gato1J2.Pieza){
                                                                                                piezaActual = GATO1J2;
                                                                                                pesoActual = gato1J2.Peso;
                                                                                                jugadorActual = J2;
                                                                                            }
                                                                                            else{
                                                                                                if(pieza == gato2J2.Pieza){
                                                                                                    piezaActual = GATO2J2;
                                                                                                    pesoActual = gato2J2.Peso;
                                                                                                    jugadorActual = J2;
                                                                                                }
                                                                                                else{
                                                                                                    if(pieza == conejo1J2.Pieza){
                                                                                                       piezaActual = CONEJO1J2;
                                                                                                       pesoActual = conejo1J2.Peso;
                                                                                                       jugadorActual = J2;
                                                                                                    }
                                                                                                    else{
                                                                                                        if(pieza == conejo2J2.Pieza){
                                                                                                            piezaActual = CONEJO2J2;
                                                                                                            pesoActual = conejo2J2.Peso;
                                                                                                            jugadorActual = J2;
                                                                                                        }
                                                                                                        else{
                                                                                                            if(pieza == conejo3J2.Pieza){
                                                                                                                piezaActual = CONEJO3J2;
                                                                                                                pesoActual = conejo3J2.Peso;
                                                                                                                jugadorActual = J2;
                                                                                                            }
                                                                                                            else{
                                                                                                                if(pieza == conejo4J2.Pieza){
                                                                                                                    piezaActual = CONEJO4J2;
                                                                                                                    pesoActual = conejo4J2.Peso;
                                                                                                                    jugadorActual = J2;
                                                                                                                }
                                                                                                                else{
                                                                                                                    if(pieza == conejo5J2.Pieza){
                                                                                                                        piezaActual = CONEJO5J2;
                                                                                                                        pesoActual = conejo5J2.Peso;
                                                                                                                        jugadorActual = J2;
                                                                                                                    }
                                                                                                                    else{
                                                                                                                        if(pieza == conejo6J2.Pieza){
                                                                                                                            piezaActual = CONEJO6J2;
                                                                                                                            pesoActual = conejo6J2.Peso;
                                                                                                                            jugadorActual = J2;
                                                                                                                        }
                                                                                                                        else{
                                                                                                                            if(pieza == conejo7J2.Pieza){
                                                                                                                                piezaActual = CONEJO7J2;
                                                                                                                                pesoActual = conejo7J2.Peso;
                                                                                                                                jugadorActual = J2;
                                                                                                                            }
                                                                                                                            else{
                                                                                                                                if(pieza == conejo8J2.Pieza){
                                                                                                                                   piezaActual = CONEJO8J2;
                                                                                                                                   pesoActual = conejo8J2.Peso;
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
                            }
                        }
                    }
                }
            }
        }
    }
}


/// MOVIMIENTO DE PIEZAS DE TIPO "MOVER"
void FNmoverAbajo(GtkWidget *pieza){ //Mueve la pieza que recibe una posición abajo

    FNpiezaClickeada(pieza); //trae que pieza fue clickeada y la guarda en piezaActual

    for(I = 0; I < 8; I++){
        for(J = 0; J < 8; J++){
            if(piezaActual == posicionPiezas[I][J]){
                for(K = 0; K < 8; K++){
                    for(L = 0; L < 8; L++){
                        if((I == K) && (J == L)){
                            if(siSobrePasaLimites(K+1, ABAJO)){
                                FNmensajeDialogo(formDialogo.Ventana, "\n\n No intentes mover la pieza fuera del trablero!\n");
                                printf("\a");
                            }
                            else{
                                if(siLugarEstaOcupado(K, L, ABAJO)){
                                    FNmensajeDialogo(formDialogo.Ventana, "\n\n Los intercambios entre piezas se deben hacer al inicio!!\n Ahora solo puedes empujar o estirar! \n");
                                    printf("\a");
                                }
                                else{
                                    if(siCongela(I,J)){
                                        FNmensajeDialogo(formDialogo.Ventana, "\n\n LA PIEZA ESTA CONGELADA!!\n");
                                        printf("\a");
                                    }
                                    else{
                                        if(siGana(I, J, ABAJO, jugadorActual, piezaActual)){
                                            if(jugadorActual == J1){
                                                FNmensajeDialogo(formDialogo.Ventana, "\n\n HA GANADO EL JUGADOR 1!!\n");
                                                printf("\a\a\a");
                                            }
                                            else{
                                                FNmensajeDialogo(formDialogo.Ventana, "\n\n HA GANADO EL JUGADOR 2!!\n");
                                                printf("\a\a\a");
                                            }
                                            gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[K+1][L], coordenadasTableroY[K+1][L]);
                                            FNimprimirMatrices();
                                            goto actualizarPosicionPiezas;
                                        }
                                        else{
                                            if(Jugador1.TurnoContador >= 4 || Jugador2.TurnoContador >= 4){
                                                FNmensajeDialogo(formDialogo.Ventana, "\n\n Los turnos por cada jugador, no pueden superar 4 movimientos \n\n");
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
                                                    FNimprimirMatrices();
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
        }
    }

    actualizarPosicionPiezas:
        posicionPiezas[I+1][J] = piezaActual;
        posicionPiezas[I][J] = 0;
        pesoPiezas[I+1][J] = pesoActual;
        pesoPiezas[I][J] = 0;
        queJugador[I+1][J] = jugadorActual;
        queJugador[I][J] = 0;
        FNimprimirMatrices();

    if(siCaeEnTrampa(K+1,L)){
        gtk_widget_destroy(GTK_WIDGET(pieza));
        posicionPiezas[I+1][J] = 0;
        pesoPiezas[I+1][J] = 0;
        queJugador[I+1][J] = 0;
        FNimprimirMatrices();
    }

    salirFNmoverAbajo:
        printf(" ");

}

void FNmoverArriba(GtkWidget *pieza){ //Mueve la pieza que recibe una posición arriba

    FNpiezaClickeada(pieza);

    for(I = 0; I < 8; I++){
        for(J = 0; J < 8; J++){
            if(piezaActual == posicionPiezas[I][J]){
                for(K = 0; K < 8; K++){
                    for(L = 0; L < 8; L++){
                        if((I == K) && (J == L)){
                            if(siSobrePasaLimites(K-1, ARRIBA)){
                                FNmensajeDialogo(formDialogo.Ventana, "\n\n No intentes mover la pieza fuera del trablero!\n"); printf("\a");
                            }
                            else{
                                if(siLugarEstaOcupado(K, L, ARRIBA)){
                                    FNmensajeDialogo(formDialogo.Ventana, "\n\n Los intercambios entre piezas se deben hacer al inicio!!\n Ahora solo puedes empujar o estirar! \n");
                                    printf("\a");
                                }
                                else{
                                    if(siCongela(I,J)){
                                        FNmensajeDialogo(formDialogo.Ventana, "\n\n LA PIEZA ESTA CONGELADA!!\n");
                                        printf("\a");
                                    }
                                    else{
                                        if(siGana(I, J, ARRIBA, jugadorActual, piezaActual)){
                                            if(jugadorActual == J1){
                                                FNmensajeDialogo(formDialogo.Ventana, "\n\n HA GANADO EL JUGADOR 1!!\n");
                                                printf("\a\a\a");
                                            }
                                            else{
                                                FNmensajeDialogo(formDialogo.Ventana, "\n\n HA GANADO EL JUGADOR 2!!\n");
                                                printf("\a\a\a");
                                            }
                                            gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[K-1][L], coordenadasTableroY[K-1][L]);
                                            FNimprimirMatrices();
                                            goto actualizarPosicionPiezas;
                                        }
                                        else{
                                            if(Jugador1.TurnoContador >= 4 || Jugador2.TurnoContador >= 4){
                                                FNmensajeDialogo(formDialogo.Ventana, "\n\n Los turnos por cada jugador, no pueden superar 4 movimientos \n\n");
                                                goto salirFNmoverArriba;
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
                                                FNimprimirMatrices();
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
        }
    }

    actualizarPosicionPiezas:
        posicionPiezas[I-1][J] = piezaActual;
        posicionPiezas[I][J] = 0;
        pesoPiezas[I-1][J] = pesoActual;
        pesoPiezas[I][J] = 0;
        queJugador[I-1][J] = jugadorActual;
        queJugador[I][J] = 0;
        FNimprimirMatrices();

    if(siCaeEnTrampa(K-1, L)){
        gtk_widget_destroy(GTK_WIDGET(pieza));
        posicionPiezas[I-1][J] = 0;
        pesoPiezas[I-1][J] = 0;
        queJugador[I-1][J] = 0;
        FNimprimirMatrices();
    }

    salirFNmoverArriba:
        printf(" ");
}

void FNmoverDerecha(GtkWidget *pieza){ //Mueve la pieza que recibe una posición a la derecha

    FNpiezaClickeada(pieza);

    for(I = 0; I < 8; I++){
        for(J = 0; J < 8; J++){
            if(piezaActual == posicionPiezas[I][J]){
                for(K = 0; K < 8; K++){
                    for(L = 0; L < 8; L++){
                        if((I == K) && (J == L)){
                            if(siSobrePasaLimites(L+1, DERECHA)){
                                FNmensajeDialogo(formDialogo.Ventana, "\n\n No intentes mover la pieza fuera del trablero!\n");
                                printf("\a");
                            }
                            else{
                                if(siLugarEstaOcupado(K, L, DERECHA)){
                                    FNmensajeDialogo(formDialogo.Ventana, "\n\n Los intercambios entre piezas se deben hacer al inicio!!\n Ahora solo puedes empujar o estirar! \n");
                                    printf("\a");
                                }
                                else{
                                    if(siCongela(I,J)){
                                        FNmensajeDialogo(formDialogo.Ventana, "\n\n LA PIEZA ESTA CONGELADA!!\n");
                                        printf("\a");
                                    }
                                    else{
                                        if(Jugador1.TurnoContador >= 4 || Jugador2.TurnoContador >= 4){
                                            FNmensajeDialogo(formDialogo.Ventana, "\n\n Los turnos por cada jugador, no pueden superar 4 movimientos \n\n");
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
                                            FNimprimirMatrices();
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
    }
    actualizarPosicionPiezas:
        posicionPiezas[I][J+1] = piezaActual;
        posicionPiezas[I][J] = 0;
        pesoPiezas[I][J+1] = pesoActual;
        pesoPiezas[I][J] = 0;
        queJugador[I][J+1] = jugadorActual;
        queJugador[I][J] = 0;
        FNimprimirMatrices();

    if(siCaeEnTrampa(K,L+1)){
        gtk_widget_destroy(GTK_WIDGET(pieza));
        posicionPiezas[I][J+1] = 0;
        pesoPiezas[I][J+1] = 0;
        queJugador[I][J+1] = 0;
        FNimprimirMatrices();
    }

    salirFNmoverDerecha:
        printf(" ");

}

void FNmoverIzquierda(GtkWidget *pieza){ //Mueve la pieza que recibe una posición a la izquierda

    FNpiezaClickeada(pieza);

    for(I = 0; I < 8; I++){
        for(J = 0; J < 8; J++){
            if(piezaActual == posicionPiezas[I][J]){
                for(K = 0; K < 8; K++){
                    for(L = 0; L < 8; L++){
                        if((I == K) && (J == L)){
                            if(siSobrePasaLimites(L-1, IZQUIERDA)){
                                FNmensajeDialogo(formDialogo.Ventana, "\n\n No intentes mover la pieza fuera del trablero!\n");
                                printf("\a");
                            }
                            else{
                                if(siLugarEstaOcupado(K, L, IZQUIERDA)){
                                    FNmensajeDialogo(formDialogo.Ventana, "\n\n Los intercambios entre piezas se deben hacer al inicio!!\n Ahora solo puedes empujar o estirar! \n");
                                    printf("\a");
                                }
                                else{
                                    if(siCongela(I,J)){
                                        FNmensajeDialogo(formDialogo.Ventana, "\n\n LA PIEZA ESTA CONGELADA!!\n"); printf("\a");
                                    }
                                    else{
                                        if(Jugador1.TurnoContador >= 4 || Jugador2.TurnoContador >= 4){
                                            FNmensajeDialogo(formDialogo.Ventana, "\n\n Los turnos por cada jugador, no pueden superar 4 movimientos \n\n");
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
                                            FNimprimirMatrices();
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
    }
    actualizarPosicionPiezas:
        posicionPiezas[I][J-1] = piezaActual;
        posicionPiezas[I][J] = 0;
        pesoPiezas[I][J-1] = pesoActual;
        pesoPiezas[I][J] = 0;
        queJugador[I][J-1] = jugadorActual;
        queJugador[I][J] = 0;
        FNimprimirMatrices();
    if(siCaeEnTrampa(K,L-1)){
        gtk_widget_destroy(GTK_WIDGET(pieza));
        posicionPiezas[I][J-1] = 0;
        pesoPiezas[I][J-1] = 0;
        queJugador[I][J-1] = 0;
        FNimprimirMatrices();
    }

    salirFNmoverIzquierda:
        printf(" ");

}

void habilitarOPmovimientosJ1(){ //Habilita las opciones de movimiento del Jugador 1
    //Jugador 1
    gtk_widget_show_all(elefanteJ1.movimiento.OPmoverArriba);
    gtk_widget_show_all(elefanteJ1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(elefanteJ1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(elefanteJ1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(camelloJ1.movimiento.OPmoverArriba);
    gtk_widget_show_all(camelloJ1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(camelloJ1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(camelloJ1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(caballo1J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(caballo1J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(caballo1J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(caballo1J1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(caballo2J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(caballo2J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(caballo2J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(caballo2J1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(perro1J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(perro1J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(perro1J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(perro1J1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(perro2J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(perro2J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(perro2J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(perro2J1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(gato1J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(gato1J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(gato1J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(gato1J1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(gato2J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(gato2J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(gato2J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(gato2J1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo1J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo1J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo1J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo1J1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo2J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo2J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo2J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo2J1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo3J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo3J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo3J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo3J1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo4J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo4J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo4J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo4J1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo5J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo5J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo5J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo5J1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo6J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo6J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo6J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo6J1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo7J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo7J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo7J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo7J1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo8J1.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo8J1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo8J1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo8J1.movimiento.OPmoverIzquierda);

}

void habilitarOPmovimientosJ2(){ //Habilita las opciones de movimiento del Jugador 2
    //Jugador 2
    gtk_widget_show_all(elefanteJ2.movimiento.OPmoverArriba);
    gtk_widget_show_all(elefanteJ2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(elefanteJ2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(elefanteJ2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(camelloJ2.movimiento.OPmoverArriba);
    gtk_widget_show_all(camelloJ2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(camelloJ2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(camelloJ2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(caballo1J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(caballo1J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(caballo1J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(caballo1J2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(caballo2J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(caballo2J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(caballo2J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(caballo2J2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(perro1J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(perro1J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(perro1J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(perro1J2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(perro2J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(perro2J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(perro2J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(perro2J2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(gato1J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(gato1J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(gato1J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(gato1J2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(gato2J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(gato2J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(gato2J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(gato2J2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo1J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo1J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo1J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo1J2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo2J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo2J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo2J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo2J2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo3J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo3J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo3J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo3J2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo4J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo4J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo4J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo4J2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo5J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo5J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo5J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo5J2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo6J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo6J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo6J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo6J2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo7J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo7J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo7J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo7J2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(conejo8J2.movimiento.OPmoverArriba);
    gtk_widget_show_all(conejo8J2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(conejo8J2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(conejo8J2.movimiento.OPmoverIzquierda);

}

void deshabilitarOPmovimientosJ1(){ //Deshabilita las opciones de movimiento del Jugador 1
    gtk_widget_hide(elefanteJ1.movimiento.OPmoverArriba);
    gtk_widget_hide(elefanteJ1.movimiento.OPmoverAbajo);
    gtk_widget_hide(elefanteJ1.movimiento.OPmoverDerecha);
    gtk_widget_hide(elefanteJ1.movimiento.OPmoverIzquierda);

    gtk_widget_hide(camelloJ1.movimiento.OPmoverArriba);
    gtk_widget_hide(camelloJ1.movimiento.OPmoverAbajo);
    gtk_widget_hide(camelloJ1.movimiento.OPmoverDerecha);
    gtk_widget_hide(camelloJ1.movimiento.OPmoverIzquierda);

    gtk_widget_hide(caballo1J1.movimiento.OPmoverArriba);
    gtk_widget_hide(caballo1J1.movimiento.OPmoverAbajo);
    gtk_widget_hide(caballo1J1.movimiento.OPmoverDerecha);
    gtk_widget_hide(caballo1J1.movimiento.OPmoverIzquierda);

    gtk_widget_hide(caballo2J1.movimiento.OPmoverArriba);
    gtk_widget_hide(caballo2J1.movimiento.OPmoverAbajo);
    gtk_widget_hide(caballo2J1.movimiento.OPmoverDerecha);
    gtk_widget_hide(caballo2J1.movimiento.OPmoverIzquierda);

    gtk_widget_hide(perro1J1.movimiento.OPmoverArriba);
    gtk_widget_hide(perro1J1.movimiento.OPmoverAbajo);
    gtk_widget_hide(perro1J1.movimiento.OPmoverDerecha);
    gtk_widget_hide(perro1J1.movimiento.OPmoverIzquierda);

    gtk_widget_hide(perro2J1.movimiento.OPmoverArriba);
    gtk_widget_hide(perro2J1.movimiento.OPmoverAbajo);
    gtk_widget_hide(perro2J1.movimiento.OPmoverDerecha);
    gtk_widget_hide(perro2J1.movimiento.OPmoverIzquierda);

    gtk_widget_hide(gato1J1.movimiento.OPmoverArriba);
    gtk_widget_hide(gato1J1.movimiento.OPmoverAbajo);
    gtk_widget_hide(gato1J1.movimiento.OPmoverDerecha);
    gtk_widget_hide(gato1J1.movimiento.OPmoverIzquierda);

    gtk_widget_hide(gato2J1.movimiento.OPmoverArriba);
    gtk_widget_hide(gato2J1.movimiento.OPmoverAbajo);
    gtk_widget_hide(gato2J1.movimiento.OPmoverDerecha);
    gtk_widget_hide(gato2J1.movimiento.OPmoverIzquierda);

//    gtk_widget_hide(conejo1J1.movimiento.OPmoverArriba);
    gtk_widget_hide(conejo1J1.movimiento.OPmoverAbajo);
    gtk_widget_hide(conejo1J1.movimiento.OPmoverDerecha);
    gtk_widget_hide(conejo1J1.movimiento.OPmoverIzquierda);

//    gtk_widget_hide(conejo2J1.movimiento.OPmoverArriba);
    gtk_widget_hide(conejo2J1.movimiento.OPmoverAbajo);
    gtk_widget_hide(conejo2J1.movimiento.OPmoverDerecha);
    gtk_widget_hide(conejo2J1.movimiento.OPmoverIzquierda);

    gtk_widget_hide(conejo3J1.movimiento.OPmoverArriba);
    gtk_widget_hide(conejo3J1.movimiento.OPmoverAbajo);
    gtk_widget_hide(conejo3J1.movimiento.OPmoverDerecha);
    gtk_widget_hide(conejo3J1.movimiento.OPmoverIzquierda);

    gtk_widget_hide(conejo4J1.movimiento.OPmoverArriba);
    gtk_widget_hide(conejo4J1.movimiento.OPmoverAbajo);
    gtk_widget_hide(conejo4J1.movimiento.OPmoverDerecha);
    gtk_widget_hide(conejo4J1.movimiento.OPmoverIzquierda);

    gtk_widget_hide(conejo5J1.movimiento.OPmoverArriba);
    gtk_widget_hide(conejo5J1.movimiento.OPmoverAbajo);
    gtk_widget_hide(conejo5J1.movimiento.OPmoverDerecha);
    gtk_widget_hide(conejo5J1.movimiento.OPmoverIzquierda);

    gtk_widget_hide(conejo6J1.movimiento.OPmoverArriba);
    gtk_widget_hide(conejo6J1.movimiento.OPmoverAbajo);
    gtk_widget_hide(conejo6J1.movimiento.OPmoverDerecha);
    gtk_widget_hide(conejo6J1.movimiento.OPmoverIzquierda);

    gtk_widget_hide(conejo7J1.movimiento.OPmoverArriba);
    gtk_widget_hide(conejo7J1.movimiento.OPmoverAbajo);
    gtk_widget_hide(conejo7J1.movimiento.OPmoverDerecha);
    gtk_widget_hide(conejo7J1.movimiento.OPmoverIzquierda);

    gtk_widget_hide(conejo8J1.movimiento.OPmoverArriba);
    gtk_widget_hide(conejo8J1.movimiento.OPmoverAbajo);
    gtk_widget_hide(conejo8J1.movimiento.OPmoverDerecha);
    gtk_widget_hide(conejo8J1.movimiento.OPmoverIzquierda);
}

void deshabilitarOPmovimientosJ2(){ //Deshabilita las opciones de movimiento del Jugador 2
    gtk_widget_hide(elefanteJ2.movimiento.OPmoverArriba);
    gtk_widget_hide(elefanteJ2.movimiento.OPmoverAbajo);
    gtk_widget_hide(elefanteJ2.movimiento.OPmoverDerecha);
    gtk_widget_hide(elefanteJ2.movimiento.OPmoverIzquierda);

    gtk_widget_hide(camelloJ2.movimiento.OPmoverArriba);
    gtk_widget_hide(camelloJ2.movimiento.OPmoverAbajo);
    gtk_widget_hide(camelloJ2.movimiento.OPmoverDerecha);
    gtk_widget_hide(camelloJ2.movimiento.OPmoverIzquierda);

    gtk_widget_hide(caballo1J2.movimiento.OPmoverArriba);
    gtk_widget_hide(caballo1J2.movimiento.OPmoverAbajo);
    gtk_widget_hide(caballo1J2.movimiento.OPmoverDerecha);
    gtk_widget_hide(caballo1J2.movimiento.OPmoverIzquierda);

    gtk_widget_hide(caballo2J2.movimiento.OPmoverArriba);
    gtk_widget_hide(caballo2J2.movimiento.OPmoverAbajo);
    gtk_widget_hide(caballo2J2.movimiento.OPmoverDerecha);
    gtk_widget_hide(caballo2J2.movimiento.OPmoverIzquierda);

    gtk_widget_hide(perro1J2.movimiento.OPmoverArriba);
    gtk_widget_hide(perro1J2.movimiento.OPmoverAbajo);
    gtk_widget_hide(perro1J2.movimiento.OPmoverDerecha);
    gtk_widget_hide(perro1J2.movimiento.OPmoverIzquierda);

    gtk_widget_hide(perro2J2.movimiento.OPmoverArriba);
    gtk_widget_hide(perro2J2.movimiento.OPmoverAbajo);
    gtk_widget_hide(perro2J2.movimiento.OPmoverDerecha);
    gtk_widget_hide(perro2J2.movimiento.OPmoverIzquierda);

    gtk_widget_hide(gato1J2.movimiento.OPmoverArriba);
    gtk_widget_hide(gato1J2.movimiento.OPmoverAbajo);
    gtk_widget_hide(gato1J2.movimiento.OPmoverDerecha);
    gtk_widget_hide(gato1J2.movimiento.OPmoverIzquierda);

    gtk_widget_hide(gato2J2.movimiento.OPmoverArriba);
    gtk_widget_hide(gato2J2.movimiento.OPmoverAbajo);
    gtk_widget_hide(gato2J2.movimiento.OPmoverDerecha);
    gtk_widget_hide(gato2J2.movimiento.OPmoverIzquierda);

    gtk_widget_hide(conejo1J2.movimiento.OPmoverArriba);
    gtk_widget_hide(conejo1J2.movimiento.OPmoverAbajo);
    gtk_widget_hide(conejo1J2.movimiento.OPmoverDerecha);
    gtk_widget_hide(conejo1J2.movimiento.OPmoverIzquierda);

    gtk_widget_hide(conejo2J2.movimiento.OPmoverArriba);
    gtk_widget_hide(conejo2J2.movimiento.OPmoverAbajo);
    gtk_widget_hide(conejo2J2.movimiento.OPmoverDerecha);
    gtk_widget_hide(conejo2J2.movimiento.OPmoverIzquierda);

    gtk_widget_hide(conejo3J2.movimiento.OPmoverArriba);
    gtk_widget_hide(conejo3J2.movimiento.OPmoverAbajo);
    gtk_widget_hide(conejo3J2.movimiento.OPmoverDerecha);
    gtk_widget_hide(conejo3J2.movimiento.OPmoverIzquierda);

    gtk_widget_hide(conejo4J2.movimiento.OPmoverArriba);
    gtk_widget_hide(conejo4J2.movimiento.OPmoverAbajo);
    gtk_widget_hide(conejo4J2.movimiento.OPmoverDerecha);
    gtk_widget_hide(conejo4J2.movimiento.OPmoverIzquierda);

    gtk_widget_hide(conejo5J2.movimiento.OPmoverArriba);
    gtk_widget_hide(conejo5J2.movimiento.OPmoverAbajo);
    gtk_widget_hide(conejo5J2.movimiento.OPmoverDerecha);
    gtk_widget_hide(conejo5J2.movimiento.OPmoverIzquierda);

    gtk_widget_hide(conejo6J2.movimiento.OPmoverArriba);
    gtk_widget_hide(conejo6J2.movimiento.OPmoverAbajo);
    gtk_widget_hide(conejo6J2.movimiento.OPmoverDerecha);
    gtk_widget_hide(conejo6J2.movimiento.OPmoverIzquierda);

    gtk_widget_hide(conejo7J2.movimiento.OPmoverArriba);
    gtk_widget_hide(conejo7J2.movimiento.OPmoverAbajo);
    gtk_widget_hide(conejo7J2.movimiento.OPmoverDerecha);
    gtk_widget_hide(conejo7J2.movimiento.OPmoverIzquierda);

    gtk_widget_hide(conejo8J2.movimiento.OPmoverArriba);
    gtk_widget_hide(conejo8J2.movimiento.OPmoverAbajo);
    gtk_widget_hide(conejo8J2.movimiento.OPmoverDerecha);
    gtk_widget_hide(conejo8J2.movimiento.OPmoverIzquierda);
}


/// MOVIMIENTO DE PIEZAS DE TIPO "EMPUJAR" y "ESTIRAR"

/// Funciones de empujada o estirada que el J1 hace sobre el J2
void FNempujarAbajoJ2(GtkWidget *pieza){ //Empuja la pieza que recibe una posición hacia abajo

    FNpiezaClickeada(pieza); //trae que pieza fue clickeada y la guarda en piezaActual

    for(I = 0; I < 8; I++){
        for(J = 0; J < 8; J++){
            if(piezaActual == posicionPiezas[I][J]){
                if(siSobrePasaLimites(I+1, ABAJO)){
                    FNmensajeDialogo(formDialogo.Ventana, "\n\n  No puedes empujar o estirar una pieza fuera del tablero!!\n");
                    printf("\a");
                    goto salirFNempujarAbajoJ2;
                }
                else{
                    if(siLugarEstaOcupado(I, J, ABAJO)){
                        FNmensajeDialogo(formDialogo.Ventana, "\n\n  No puedes empujar o estirar a un lugar donde ya hay una pieza!!\n");
                        printf("\a");
                        goto salirFNempujarAbajoJ2;
                    }
                    else{
                        if(pesoPiezas[I-1][J] <= pesoPiezas[I][J]){
                            FNmensajeDialogo(formDialogo.Ventana, "\n\n   No estas en situacion de empuje o estire \n   o la Pieza no es suficientemente fuerte para empujar o estirar!\n");
                            printf("\a");
                            goto salirFNempujarAbajoJ2;
                        }
                        else{
                            if(Jugador1.TurnoContador >= 4 || Jugador2.TurnoContador >= 4){
                                FNmensajeDialogo(formDialogo.Ventana, "\n\n Los turnos por cada jugador, no pueden superar 4 movimientos \n\n");
                                goto salirFNempujarAbajoJ2;
                            }
                            else{
                                switch(jugadorActual){
                                    case J1:
                                        Jugador2.TurnoContador += 2;
                                        sprintf(Jugador2.TurnoArray, "%d", Jugador2.TurnoContador);
                                        gtk_label_set_text(GTK_LABEL(Jugador2.TurnoCantidadMovimientos), Jugador2.TurnoArray);
                                        break;
                                    case J2:
                                        Jugador1.TurnoContador += 2;
                                        sprintf(Jugador1.TurnoArray, "%d", Jugador1.TurnoContador);
                                        gtk_label_set_text(GTK_LABEL(Jugador1.TurnoCantidadMovimientos), Jugador1.TurnoArray);
                                        break;
                                }
                                pieza_A_EmpujarEstirar = posicionPiezas[I][J]; coorXempEst = I; coorYempEst = J; //COORDENADAS DE LA PIEZA QUE SE QUIERE EMPUJAR O ESTIRAR
                                empujaOestiraJ2(posicionPiezas[I-1][J], pieza, ABAJO);
                                goto actualizarPosicionPiezas;
                            }
                        }
                    }
                }
            }
        }
    }


    actualizarPosicionPiezas:
        posicionPiezas[coorXempEst][coorYempEst] = piezaQueEmpuja;
        posicionPiezas[coorXempEst+1][coorYempEst] = piezaEmpujada;
        posicionPiezas[coorXempEst-1][coorYempEst] = 0;
        pesoPiezas[coorXempEst][coorYempEst] = pesoPiezaQueEmpuja;
        pesoPiezas[coorXempEst+1][coorYempEst] = pesoPiezaEmpujada;
        pesoPiezas[coorXempEst-1][coorYempEst] = 0;
        queJugador[coorXempEst][coorYempEst] = queJugadorPiezaQueEmpuja;
        queJugador[coorXempEst+1][coorYempEst] = queJugadorPiezaEmpujada;
        queJugador[coorXempEst-1][coorYempEst] = 0;
        FNimprimirMatrices();

    if(siCaeEnTrampa(coorXempEst+1, coorYempEst)){
        gtk_widget_destroy(GTK_WIDGET(pieza));
        posicionPiezas[coorXempEst+1][coorYempEst] = 0;
        pesoPiezas[coorXempEst+1][coorYempEst] = 0;
        queJugador[coorXempEst+1][coorYempEst] = 0;
        FNimprimirMatrices();
    }

    salirFNempujarAbajoJ2:
     printf(" ");

}

void FNestirarArribaJ2(GtkWidget *pieza){ //Empuja la pieza que recibe una posición hacia arriba

    FNpiezaClickeada(pieza); //trae que pieza fue clickeada y la guarda en piezaActual

    for(I = 0; I < 8; I++){
        for(J = 0; J < 8; J++){
            if(piezaActual == posicionPiezas[I][J]){
                if(siSobrePasaLimites(I-1, ARRIBA)){
                    FNmensajeDialogo(formDialogo.Ventana, "\n\n  No puedes empujar o estirar una pieza fuera del tablero!!\n");
                    printf("\a");
                    goto salirFNestirarArribaJ2;
                }
                else{
                    if(siLugarEstaOcupado(I-1, J, ARRIBA)){
                        FNmensajeDialogo(formDialogo.Ventana, "\n\n  No puedes empujar o estirar a un lugar donde ya hay una pieza!!\n");
                        printf("\a");
                        goto salirFNestirarArribaJ2;
                    }
                    else{
                        if(pesoPiezas[I-1][J] <= pesoPiezas[I][J]){
                            FNmensajeDialogo(formDialogo.Ventana, "\n\n   No estas en situacion de empuje o estire \n   o la Pieza no es suficientemente fuerte para empujar o estirar!\n"); printf("\a");
                            goto salirFNestirarArribaJ2;
                        }
                        else{
                            if(Jugador1.TurnoContador >= 4 || Jugador2.TurnoContador >= 4){
                                FNmensajeDialogo(formDialogo.Ventana, "\n\n Los turnos por cada jugador, no pueden superar 4 movimientos \n\n");
                                goto salirFNestirarArribaJ2;
                            }
                            else{
                                switch(jugadorActual){
                                    case J1:
                                        Jugador2.TurnoContador += 2;
                                        sprintf(Jugador2.TurnoArray, "%d", Jugador2.TurnoContador);
                                        gtk_label_set_text(GTK_LABEL(Jugador2.TurnoCantidadMovimientos), Jugador2.TurnoArray);
                                        break;
                                    case J2:
                                        Jugador1.TurnoContador += 2;
                                        sprintf(Jugador1.TurnoArray, "%d", Jugador1.TurnoContador);
                                        gtk_label_set_text(GTK_LABEL(Jugador1.TurnoCantidadMovimientos), Jugador1.TurnoArray);
                                        break;
                                }
                                pieza_A_EmpujarEstirar = posicionPiezas[I][J]; coorXempEst = I; coorYempEst = J; //COORDENADAS DE LA PIEZA QUE SE QUIERE EMPUJAR O ESTIRAR
                                empujaOestiraJ2(posicionPiezas[I-1][J], pieza, ARRIBA);
                                goto actualizarPosicionPiezas;
                            }
                        }
                    }
                }
            }
        }
    }



    actualizarPosicionPiezas:
        posicionPiezas[coorXempEst-1][coorYempEst] = piezaEmpujada;
        posicionPiezas[coorXempEst-2][coorYempEst] = piezaQueEmpuja;
        posicionPiezas[coorXempEst][coorYempEst] = 0;
        pesoPiezas[coorXempEst-1][coorYempEst] = pesoPiezaEmpujada;
        pesoPiezas[coorXempEst-2][coorYempEst] = pesoPiezaQueEmpuja;
        pesoPiezas[coorXempEst][coorYempEst] = 0;
        queJugador[coorXempEst-1][coorYempEst] = queJugadorPiezaEmpujada;
        queJugador[coorXempEst-2][coorYempEst] = queJugadorPiezaQueEmpuja;
        queJugador[coorXempEst][coorYempEst] = 0;
        FNimprimirMatrices();

    if(siCaeEnTrampa(coorXempEst+1, coorYempEst)){
        gtk_widget_destroy(GTK_WIDGET(pieza));
        posicionPiezas[coorXempEst+1][coorYempEst] = 0;  /// SIN USAR POR EL SENTIDO DE ESTIRE
        pesoPiezas[coorXempEst+1][coorYempEst] = 0;
        queJugador[coorXempEst+1][coorYempEst] = 0;
//        FNimprimirMatrices();
    }

    salirFNestirarArribaJ2:
        printf(" ");

}

void FNempujarDerechaJ2(GtkWidget *pieza){ //Empuja la pieza que recibe una posición hacia la derecha

    FNpiezaClickeada(pieza); //trae que pieza fue clickeada y la guarda en piezaActual

    for(I = 0; I < 8; I++){
        for(J = 0; J < 8; J++){
            if(piezaActual == posicionPiezas[I][J]){
                if(siSobrePasaLimites(J+1, DERECHA)){
                    FNmensajeDialogo(formDialogo.Ventana, "\n\n  No puedes empujar o estirar una pieza fuera del tablero!!\n"); printf("\a");
                    goto salirFNempujarDerechaJ2;
                }
                else{
                    if(siLugarEstaOcupado(I, J, DERECHA)){
                        FNmensajeDialogo(formDialogo.Ventana, "\n\n  No puedes empujar o estirar a un lugar donde ya hay una pieza!!\n");
                        printf("\a");
                        goto salirFNempujarDerechaJ2;
                    }
                    else{
                        if(pesoPiezas[I-1][J] <= pesoPiezas[I][J]){
                            FNmensajeDialogo(formDialogo.Ventana, "\n\n   No estas en situacion de empuje o estire \n   o la Pieza no es suficientemente fuerte para empujar o estirar!\n");
                            printf("\a");
                            goto salirFNempujarDerechaJ2;
                        }
                        else{
                            if(Jugador1.TurnoContador >= 4 || Jugador2.TurnoContador >= 4){
                                FNmensajeDialogo(formDialogo.Ventana, "\n\n Los turnos por cada jugador, no pueden superar 4 movimientos \n\n");
                                goto salirFNempujarDerechaJ2;
                            }
                            else{
                                switch(jugadorActual){
                                    case J1:
                                        Jugador2.TurnoContador += 2;
                                        sprintf(Jugador2.TurnoArray, "%d", Jugador2.TurnoContador);
                                        gtk_label_set_text(GTK_LABEL(Jugador2.TurnoCantidadMovimientos), Jugador2.TurnoArray);
                                        break;
                                    case J2:
                                        Jugador1.TurnoContador += 2;
                                        sprintf(Jugador1.TurnoArray, "%d", Jugador1.TurnoContador);
                                        gtk_label_set_text(GTK_LABEL(Jugador1.TurnoCantidadMovimientos), Jugador1.TurnoArray);
                                        break;
                                }
                                pieza_A_EmpujarEstirar = posicionPiezas[I][J]; coorXempEst = I; coorYempEst = J; //COORDENADAS DE LA PIEZA QUE SE QUIERE EMPUJAR O ESTIRAR
                                empujaOestiraJ2(posicionPiezas[I-1][J], pieza, DERECHA);
                                goto actualizarPosicionPiezas;
                            }
                        }
                    }
                }
            }
        }
    }

    actualizarPosicionPiezas:
        posicionPiezas[coorXempEst][coorYempEst+1] = piezaEmpujada;
        posicionPiezas[coorXempEst][coorYempEst] = piezaQueEmpuja;
        posicionPiezas[coorXempEst-1][coorYempEst] = 0;
        pesoPiezas[coorXempEst][coorYempEst+1] = pesoPiezaEmpujada;
        pesoPiezas[coorXempEst][coorYempEst] = pesoPiezaQueEmpuja;
        pesoPiezas[coorXempEst-1][coorYempEst] = 0;
        queJugador[coorXempEst][coorYempEst+1] = queJugadorPiezaEmpujada;
        queJugador[coorXempEst][coorYempEst] = queJugadorPiezaQueEmpuja;
        queJugador[coorXempEst-1][coorYempEst] = 0;
        FNimprimirMatrices();

    if(siCaeEnTrampa(K+1,L)){
        gtk_widget_destroy(GTK_WIDGET(pieza));
        posicionPiezas[I+1][J] = 0;                   /// SIN USAR POR EL SENTIDO DE ESTIRE
        pesoPiezas[I+1][J] = 0;
        queJugador[I+1][J] = 0;
//        FNimprimirMatrices();
    }

    salirFNempujarDerechaJ2:
        printf(" ");

}

void FNempujarIzquierdaJ2(GtkWidget *pieza){ //Empuja la pieza que recibe una posición hacia la izquierda

    FNpiezaClickeada(pieza); //trae que pieza fue clickeada y la guarda en piezaActual

    for(I = 0; I < 8; I++){
        for(J = 0; J < 8; J++){
            if(piezaActual == posicionPiezas[I][J]){
                if(siSobrePasaLimites(J-1, IZQUIERDA)){
                    FNmensajeDialogo(formDialogo.Ventana, "\n\n  No puedes empujar o estirar una pieza fuera del tablero!!\n"); printf("\a");
                    goto salirFNempujarIzquierdaJ2;
                }
                else{
                    if(siLugarEstaOcupado(I, J, IZQUIERDA)){
                        FNmensajeDialogo(formDialogo.Ventana, "\n\n  No puedes empujar o estirar a un lugar donde ya hay una pieza!!\n"); printf("\a");
                        goto salirFNempujarIzquierdaJ2;
                    }
                    else{
                        if(pesoPiezas[I-1][J] <= pesoPiezas[I][J]){
                            FNmensajeDialogo(formDialogo.Ventana, "\n\n   No estas en situacion de empuje o estire \n   o la Pieza no es suficientemente fuerte para empujar o estirar!\n");
                            printf("\a");
                            goto salirFNempujarIzquierdaJ2;
                        }
                        else{
                            if(Jugador1.TurnoContador >= 4 || Jugador2.TurnoContador >= 4){
                                FNmensajeDialogo(formDialogo.Ventana, "\n\n Los turnos por cada jugador, no pueden superar 4 movimientos \n\n");
                                goto salirFNempujarIzquierdaJ2;
                            }
                            else{
                                switch(jugadorActual){
                                    case J1:
                                        Jugador2.TurnoContador += 2;
                                        sprintf(Jugador2.TurnoArray, "%d", Jugador2.TurnoContador);
                                        gtk_label_set_text(GTK_LABEL(Jugador2.TurnoCantidadMovimientos), Jugador2.TurnoArray);
                                        break;
                                    case J2:
                                        Jugador1.TurnoContador += 2;
                                        sprintf(Jugador1.TurnoArray, "%d", Jugador1.TurnoContador);
                                        gtk_label_set_text(GTK_LABEL(Jugador1.TurnoCantidadMovimientos), Jugador1.TurnoArray);
                                        break;
                                }
                                pieza_A_EmpujarEstirar = posicionPiezas[I][J]; coorXempEst = I; coorYempEst = J; //COORDENADAS DE LA PIEZA QUE SE QUIERE EMPUJAR O ESTIRAR
                                empujaOestiraJ2(posicionPiezas[I-1][J], pieza, IZQUIERDA);
                                goto actualizarPosicionPiezas;
                            }
                        }
                    }
                }
            }
        }
    }



    actualizarPosicionPiezas:
        posicionPiezas[coorXempEst][coorYempEst-1] = piezaEmpujada;
        posicionPiezas[coorXempEst][coorYempEst] = piezaQueEmpuja;
        posicionPiezas[coorXempEst-1][coorYempEst] = 0;
        pesoPiezas[coorXempEst][coorYempEst-1] = pesoPiezaEmpujada;
        pesoPiezas[coorXempEst][coorYempEst] = pesoPiezaQueEmpuja;
        pesoPiezas[coorXempEst-1][coorYempEst] = 0;
        queJugador[coorXempEst][coorYempEst-1] = queJugadorPiezaEmpujada;
        queJugador[coorXempEst][coorYempEst] = queJugadorPiezaQueEmpuja;
        queJugador[coorXempEst-1][coorYempEst] = 0;
        FNimprimirMatrices();

    if(siCaeEnTrampa(K+1,L)){
        gtk_widget_destroy(GTK_WIDGET(pieza));
        posicionPiezas[I+1][J] = 0;               /// SIN USAR POR EL SENTIDO DE ESTIRE
        pesoPiezas[I+1][J] = 0;
        queJugador[I+1][J] = 0;
//        FNimprimirMatrices();
    }

    salirFNempujarIzquierdaJ2:
        printf(" ");

}

/// Funciones de empujada o estirada que el J2 hace sobre el J1
void FNempujarArribaJ1(GtkWidget *pieza){ //Empuja la pieza que recibe una posición hacia abajo

    FNpiezaClickeada(pieza); //trae que pieza fue clickeada y la guarda en piezaActual

    for(I = 0; I < 8; I++){
        for(J = 0; J < 8; J++){
            if(piezaActual == posicionPiezas[I][J]){
                if(siSobrePasaLimites(I-1, ARRIBA)){
                    FNmensajeDialogo(formDialogo.Ventana, "\n\n  No puedes empujar o estirar una pieza fuera del tablero!!\n");
                    printf("\a");
                    goto salirFNempujarArribaJ1;
                }
                else{
                    if(siLugarEstaOcupado(I, J, ARRIBA)){
                        FNmensajeDialogo(formDialogo.Ventana, "\n\n  No puedes empujar o estirar a un lugar donde ya hay una pieza!!\n");
                        printf("\a");
                        goto salirFNempujarArribaJ1;
                    }
                    else{
                        if(pesoPiezas[I+1][J] <= pesoPiezas[I][J]){
                            FNmensajeDialogo(formDialogo.Ventana, "\n\n   No estas en situacion de empuje o estire \n   o la Pieza no es suficientemente fuerte para empujar o estirar!\n");
                            printf("\a");
                            goto salirFNempujarArribaJ1;
                        }
                        else{
                            if(Jugador1.TurnoContador >= 4 || Jugador2.TurnoContador >= 4){
                                FNmensajeDialogo(formDialogo.Ventana, "\n\n Los turnos por cada jugador, no pueden superar 4 movimientos \n\n");
                                goto salirFNempujarArribaJ1;
                            }
                            else{
                                switch(jugadorActual){
                                    case J1:
                                        Jugador2.TurnoContador += 2;
                                        sprintf(Jugador2.TurnoArray, "%d", Jugador2.TurnoContador);
                                        gtk_label_set_text(GTK_LABEL(Jugador2.TurnoCantidadMovimientos), Jugador2.TurnoArray);
                                        break;
                                    case J2:
                                        Jugador1.TurnoContador += 2;
                                        sprintf(Jugador1.TurnoArray, "%d", Jugador1.TurnoContador);
                                        gtk_label_set_text(GTK_LABEL(Jugador1.TurnoCantidadMovimientos), Jugador1.TurnoArray);
                                        break;
                                }
                                pieza_A_EmpujarEstirar = posicionPiezas[I][J]; coorXempEst = I; coorYempEst = J; //COORDENADAS DE LA PIEZA QUE SE QUIERE EMPUJAR O ESTIRAR
                                empujaOestiraJ1(posicionPiezas[I+1][J], pieza, ARRIBA);
                                goto actualizarPosicionPiezas;
                            }
                        }
                    }
                }
            }
        }
    }


    actualizarPosicionPiezas:
        posicionPiezas[coorXempEst][coorYempEst] = piezaQueEmpuja;
        posicionPiezas[coorXempEst+1][coorYempEst] = 0;
        posicionPiezas[coorXempEst-1][coorYempEst] = piezaEmpujada;
        pesoPiezas[coorXempEst][coorYempEst] = pesoPiezaQueEmpuja;
        pesoPiezas[coorXempEst+1][coorYempEst] = 0;
        pesoPiezas[coorXempEst-1][coorYempEst] = pesoPiezaEmpujada;
        queJugador[coorXempEst][coorYempEst] = queJugadorPiezaQueEmpuja;
        queJugador[coorXempEst+1][coorYempEst] = 0;
        queJugador[coorXempEst-1][coorYempEst] = queJugadorPiezaEmpujada;
        FNimprimirMatrices();

    if(siCaeEnTrampa(coorXempEst-1, coorYempEst)){
        gtk_widget_destroy(GTK_WIDGET(pieza));
        posicionPiezas[coorXempEst-1][coorYempEst] = 0;
        pesoPiezas[coorXempEst-1][coorYempEst] = 0;
        queJugador[coorXempEst-1][coorYempEst] = 0;
        FNimprimirMatrices();
    }

    salirFNempujarArribaJ1:
        printf(" ");

}

void FNestirarAbajoJ1(GtkWidget *pieza){ //Empuja la pieza que recibe una posición hacia arriba

    FNpiezaClickeada(pieza); //trae que pieza fue clickeada y la guarda en piezaActual

    for(I = 0; I < 8; I++){
        for(J = 0; J < 8; J++){
            if(piezaActual == posicionPiezas[I][J]){
                if(siSobrePasaLimites(I+1, ABAJO)){
                    FNmensajeDialogo(formDialogo.Ventana, "\n\n  No puedes empujar o estirar una pieza fuera del tablero!!\n");
                    printf("\a");
                    goto salirFNestirarAbajoJ1;
                }
                else{
                    if(siLugarEstaOcupado(I+1, J, ABAJO)){
                        FNmensajeDialogo(formDialogo.Ventana, "\n\n  No puedes empujar o estirar a un lugar donde ya hay una pieza!!\n");
                        printf("\a");
                        goto salirFNestirarAbajoJ1;
                    }
                    else{
                        if(pesoPiezas[I+1][J] <= pesoPiezas[I][J]){
                            FNmensajeDialogo(formDialogo.Ventana, "\n\n   No estas en situacion de empuje o estire \n   o la Pieza no es suficientemente fuerte para empujar o estirar!\n");
                            printf("\a");
                            goto salirFNestirarAbajoJ1;
                        }
                        else{
                            if(Jugador1.TurnoContador >= 4 || Jugador2.TurnoContador >= 4){
                                FNmensajeDialogo(formDialogo.Ventana, "\n\n Los turnos por cada jugador, no pueden superar 4 movimientos \n\n");
                                goto salirFNestirarAbajoJ1;
                            }
                            else{
                                switch(jugadorActual){
                                    case J1:
                                        Jugador2.TurnoContador += 2;
                                        sprintf(Jugador2.TurnoArray, "%d", Jugador2.TurnoContador);
                                        gtk_label_set_text(GTK_LABEL(Jugador2.TurnoCantidadMovimientos), Jugador2.TurnoArray);
                                        break;
                                    case J2:
                                        Jugador1.TurnoContador += 2;
                                        sprintf(Jugador1.TurnoArray, "%d", Jugador1.TurnoContador);
                                        gtk_label_set_text(GTK_LABEL(Jugador1.TurnoCantidadMovimientos), Jugador1.TurnoArray);
                                        break;
                                }
                                pieza_A_EmpujarEstirar = posicionPiezas[I][J]; coorXempEst = I; coorYempEst = J; //COORDENADAS DE LA PIEZA QUE SE QUIERE EMPUJAR O ESTIRAR
                                empujaOestiraJ1(posicionPiezas[I+1][J], pieza, ABAJO);
                                goto actualizarPosicionPiezas;
                            }
                        }
                    }
                }
            }
        }
    }


    actualizarPosicionPiezas:
    posicionPiezas[coorXempEst+1][coorYempEst] = piezaEmpujada;
    posicionPiezas[coorXempEst+2][coorYempEst] = piezaQueEmpuja;
    posicionPiezas[coorXempEst][coorYempEst] = 0;
    pesoPiezas[coorXempEst+1][coorYempEst] = pesoPiezaEmpujada;
    pesoPiezas[coorXempEst+2][coorYempEst] = pesoPiezaQueEmpuja;
    pesoPiezas[coorXempEst][coorYempEst] = 0;
    queJugador[coorXempEst+1][coorYempEst] = queJugadorPiezaEmpujada;
    queJugador[coorXempEst+2][coorYempEst] = queJugadorPiezaQueEmpuja;
    queJugador[coorXempEst][coorYempEst] = 0;
    FNimprimirMatrices();

    if(siCaeEnTrampa(K+1,L)){
        gtk_widget_destroy(GTK_WIDGET(pieza));
        posicionPiezas[I+1][J] = 0;
        pesoPiezas[I+1][J] = 0;
        queJugador[I+1][J] = 0;
 //       FNimprimirMatrices();
    }

    salirFNestirarAbajoJ1:
        printf(" ");

}

void FNempujarDerechaJ1(GtkWidget *pieza){ //Empuja la pieza que recibe una posición hacia la derecha

    FNpiezaClickeada(pieza); //trae que pieza fue clickeada y la guarda en piezaActual

    for(I = 0; I < 8; I++){
        for(J = 0; J < 8; J++){
            if(piezaActual == posicionPiezas[I][J]){
                if(siSobrePasaLimites(J+1, DERECHA)){
                    FNmensajeDialogo(formDialogo.Ventana, "\n\n  No puedes empujar o estirar una pieza fuera del tablero!!\n");
                    printf("\a");
                    goto salirFNempujarDerechaJ1;
                }
                else{
                    if(siLugarEstaOcupado(I, J, DERECHA)){
                        FNmensajeDialogo(formDialogo.Ventana, "\n\n  No puedes empujar o estirar a un lugar donde ya hay una pieza!!\n"); printf("\a");
                        goto salirFNempujarDerechaJ1;
                    }
                    else{
                        if(pesoPiezas[I+1][J] <= pesoPiezas[I][J]){
                            FNmensajeDialogo(formDialogo.Ventana, "\n\n   No estas en situacion de empuje o estire \n   o la Pieza no es suficientemente fuerte para empujar o estirar!\n");
                            printf("\a");
                            goto salirFNempujarDerechaJ1;
                        }
                        else{
                            if(Jugador1.TurnoContador >= 4 || Jugador2.TurnoContador >= 4){
                                FNmensajeDialogo(formDialogo.Ventana, "\n\n Los turnos por cada jugador, no pueden superar 4 movimientos \n\n");
                                goto salirFNempujarDerechaJ1;
                            }
                            else{
                                switch(jugadorActual){
                                    case J1:
                                        Jugador2.TurnoContador += 2;
                                        sprintf(Jugador2.TurnoArray, "%d", Jugador2.TurnoContador);
                                        gtk_label_set_text(GTK_LABEL(Jugador2.TurnoCantidadMovimientos), Jugador2.TurnoArray);
                                        break;
                                    case J2:
                                        Jugador1.TurnoContador += 2;
                                        sprintf(Jugador1.TurnoArray, "%d", Jugador1.TurnoContador);
                                        gtk_label_set_text(GTK_LABEL(Jugador1.TurnoCantidadMovimientos), Jugador1.TurnoArray);
                                        break;
                                }
                                pieza_A_EmpujarEstirar = posicionPiezas[I][J]; coorXempEst = I; coorYempEst = J; //COORDENADAS DE LA PIEZA QUE SE QUIERE EMPUJAR O ESTIRAR
                                empujaOestiraJ1(posicionPiezas[I+1][J], pieza, DERECHA);
                                goto actualizarPosicionPiezas;
                            }
                        }
                    }
                }
            }
        }
    }


    actualizarPosicionPiezas:
    posicionPiezas[coorXempEst][coorYempEst] = piezaQueEmpuja;
    posicionPiezas[coorXempEst][coorYempEst+1] = piezaEmpujada;
    posicionPiezas[coorXempEst+1][coorYempEst] = 0;
    pesoPiezas[coorXempEst][coorYempEst] = pesoPiezaQueEmpuja;
    pesoPiezas[coorXempEst][coorYempEst+1] = pesoPiezaEmpujada;
    pesoPiezas[coorXempEst+1][coorYempEst] = 0;
    queJugador[coorXempEst][coorYempEst] = queJugadorPiezaQueEmpuja;
    queJugador[coorXempEst][coorYempEst+1] = queJugadorPiezaEmpujada;
    queJugador[coorXempEst+1][coorYempEst] = 0;
    FNimprimirMatrices();

    if(siCaeEnTrampa(K+1,L)){
        gtk_widget_destroy(GTK_WIDGET(pieza));
        posicionPiezas[I+1][J] = 0;
        pesoPiezas[I+1][J] = 0;
        queJugador[I+1][J] = 0;
//        FNimprimirMatrices();
    }

    salirFNempujarDerechaJ1:
        printf(" ");

}

void FNempujarIzquierdaJ1(GtkWidget *pieza){ //Empuja la pieza que recibe una posición hacia la izquierda

    FNpiezaClickeada(pieza); //trae que pieza fue clickeada y la guarda en piezaActual

    for(I = 0; I < 8; I++){
        for(J = 0; J < 8; J++){
            if(piezaActual == posicionPiezas[I][J]){
                if(siSobrePasaLimites(J-1, IZQUIERDA)){
                    FNmensajeDialogo(formDialogo.Ventana, "\n\n  No puedes empujar o estirar una pieza fuera del tablero!!\n");
                    printf("\a");
                    goto salirFNempujarIzquierdaJ1;
                }
                else{
                    if(siLugarEstaOcupado(I, J, IZQUIERDA)){
                        FNmensajeDialogo(formDialogo.Ventana, "\n\n  No puedes empujar o estirar a un lugar donde ya hay una pieza!!\n");
                        printf("\a");
                        goto salirFNempujarIzquierdaJ1;
                    }
                    else{
                        if(pesoPiezas[I+1][J] <= pesoPiezas[I][J]){
                            FNmensajeDialogo(formDialogo.Ventana, "\n\n   No estas en situacion de empuje o estire \n   o la Pieza no es suficientemente fuerte para empujar o estirar!\n");
                            printf("\a");
                            goto salirFNempujarIzquierdaJ1;
                        }
                        else{
                            if(Jugador1.TurnoContador >= 4 || Jugador2.TurnoContador >= 4){
                                FNmensajeDialogo(formDialogo.Ventana, "\n\n Los turnos por cada jugador, no pueden superar 4 movimientos \n\n");
                                goto salirFNempujarIzquierdaJ1;
                            }
                            else{
                                switch(jugadorActual){
                                    case J1:
                                        Jugador2.TurnoContador += 2;
                                        sprintf(Jugador2.TurnoArray, "%d", Jugador2.TurnoContador);
                                        gtk_label_set_text(GTK_LABEL(Jugador2.TurnoCantidadMovimientos), Jugador2.TurnoArray);
                                        break;
                                    case J2:
                                        Jugador1.TurnoContador += 2;
                                        sprintf(Jugador1.TurnoArray, "%d", Jugador1.TurnoContador);
                                        gtk_label_set_text(GTK_LABEL(Jugador1.TurnoCantidadMovimientos), Jugador1.TurnoArray);
                                        break;
                                }
                                pieza_A_EmpujarEstirar = posicionPiezas[I][J]; coorXempEst = I; coorYempEst = J; //COORDENADAS DE LA PIEZA QUE SE QUIERE EMPUJAR O ESTIRAR
                                empujaOestiraJ1(posicionPiezas[I+1][J], pieza, IZQUIERDA);
                                goto actualizarPosicionPiezas;
                            }
                        }
                    }
                }
            }
        }
    }



    actualizarPosicionPiezas:
    posicionPiezas[coorXempEst][coorYempEst] = piezaQueEmpuja;
    posicionPiezas[coorXempEst][coorYempEst-1] = piezaEmpujada;
    posicionPiezas[coorXempEst+1][coorYempEst] = 0;
    pesoPiezas[coorXempEst][coorYempEst] = pesoPiezaQueEmpuja;
    pesoPiezas[coorXempEst][coorYempEst-1] = pesoPiezaEmpujada;
    pesoPiezas[coorXempEst+1][coorYempEst] = 0;
    queJugador[coorXempEst][coorYempEst] = queJugadorPiezaQueEmpuja;
    queJugador[coorXempEst][coorYempEst-1] = queJugadorPiezaEmpujada;
    queJugador[coorXempEst+1][coorYempEst] = 0;
    FNimprimirMatrices();

    if(siCaeEnTrampa(K+1,L)){
        gtk_widget_destroy(GTK_WIDGET(pieza));
        posicionPiezas[I+1][J] = 0;
        pesoPiezas[I+1][J] = 0;
        queJugador[I+1][J] = 0;
//        FNimprimirMatrices();
    }

    salirFNempujarIzquierdaJ1:
        printf(" ");


}

void empujaOestiraJ1(int posicionPieza, GtkWidget *pieza, int sentido){
    if(sentido == ABAJO){
        switch(posicionPieza){
            case ELEFANTEJ1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), elefanteJ1.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ", piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = ELEFANTEJ1;
                printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = elefanteJ1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CAMELLOJ1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), camelloJ1.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ", piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CAMELLOJ1;
                printf("\n piezaQueEmpuja = ", piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = camelloJ1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CABALLO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo1J1.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                printf("\n piezaEmpujada = ", piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO1J1; printf("\n piezaQueEmpuja = ", piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = caballo1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CABALLO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo2J1.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO2J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = caballo2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case PERRO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro1J1.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO1J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = perro1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case PERRO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro2J1.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO2J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = perro2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case GATO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato1J1.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO1J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = gato1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case GATO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato2J1.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ", piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO2J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = gato2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo1J1.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO1J1; printf("\n piezaQueEmpuja = ", piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo2J1.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO2J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO3J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo3J1.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO3J1; printf("\n piezaQueEmpuja = ", piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo3J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO4J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo4J1.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ", piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO4J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo4J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO5J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo5J1.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO5J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo5J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO6J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo6J1.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ", piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO6J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo6J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO7J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo7J1.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO7J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo7J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO8J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo8J1.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO8J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo8J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case ELEFANTEJ2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), elefanteJ2.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = ELEFANTEJ2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = elefanteJ2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CAMELLOJ2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), camelloJ2.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CAMELLOJ2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = camelloJ2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CABALLO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo1J2.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO1J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = caballo1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CABALLO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo2J2.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO2J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = caballo2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case PERRO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro1J2.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO1J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = perro1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case PERRO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro2J2.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO2J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = perro2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case GATO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato1J2.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO1J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = gato1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case GATO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato2J2.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO2J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = gato2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo1J2.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO1J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo2J2.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO2J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO3J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo3J2.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO3J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo3J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO4J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo4J2.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO4J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo4J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO5J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo5J2.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO5J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo5J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO6J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo6J2.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO6J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo6J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO7J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo7J2.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO7J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo7J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO8J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo8J2.Pieza, coordenadasTableroX[coorXempEst+2][coorYempEst], coordenadasTableroY[coorXempEst+2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO8J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo8J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
        }
    }

    if(sentido == ARRIBA){
        switch(posicionPieza){
            case ELEFANTEJ1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), elefanteJ1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = ELEFANTEJ1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = elefanteJ1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CAMELLOJ1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), camelloJ1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CAMELLOJ1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = camelloJ1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CABALLO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo1J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO1J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = caballo1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CABALLO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo2J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO2J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = caballo2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case PERRO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro1J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO1J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = perro1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case PERRO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro2J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO2J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = perro2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case GATO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato1J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO1J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = gato1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case GATO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato2J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO2J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = gato2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo1J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO1J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo2J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO2J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO3J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo3J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO3J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo3J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO4J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo4J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO4J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo4J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO5J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo5J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO5J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo5J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO6J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo6J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO6J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo6J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO7J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo7J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO7J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo7J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO8J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo8J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO8J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo8J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case ELEFANTEJ2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), elefanteJ2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = ELEFANTEJ2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = elefanteJ2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CAMELLOJ2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), camelloJ2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CAMELLOJ2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = camelloJ2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CABALLO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo1J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO1J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = caballo1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CABALLO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo2J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO2J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = caballo2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case PERRO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro1J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO1J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = perro1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case PERRO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro2J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO2J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = perro2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case GATO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato1J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO1J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = gato1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case GATO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato2J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO2J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = gato2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo1J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO1J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo2J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO2J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO3J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo3J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO3J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo3J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO4J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo4J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO4J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo4J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO5J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo5J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO5J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo5J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO6J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo6J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO6J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo6J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO7J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo7J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO7J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo7J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO8J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo8J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO8J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo8J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
        }
    }

    if(sentido == DERECHA){
        switch(posicionPieza){
            case ELEFANTEJ1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), elefanteJ1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = ELEFANTEJ1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = elefanteJ1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CAMELLOJ1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), camelloJ1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CAMELLOJ1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = camelloJ1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CABALLO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo1J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO1J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = caballo1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CABALLO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo2J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO2J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = caballo2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case PERRO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro1J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO1J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = perro1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case PERRO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro2J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO2J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = perro2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case GATO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato1J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO1J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = gato1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case GATO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato2J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO2J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = gato2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo1J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO1J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo2J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO2J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO3J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo3J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO3J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo3J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO4J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo4J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO4J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo4J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO5J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo5J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO5J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo5J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO6J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo6J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO6J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo6J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO7J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo7J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO7J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo7J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO8J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo8J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO8J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo8J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case ELEFANTEJ2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), elefanteJ2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = ELEFANTEJ2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = elefanteJ2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CAMELLOJ2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), camelloJ2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CAMELLOJ2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = camelloJ2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CABALLO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo1J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO1J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = caballo1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CABALLO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo2J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO2J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = caballo2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case PERRO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro1J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO1J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = perro1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case PERRO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro2J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO2J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = perro2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case GATO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato1J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO1J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = gato1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case GATO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato2J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO2J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = gato2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo1J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO1J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo2J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO2J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO3J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo3J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO3J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo3J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO4J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo4J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO4J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo4J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO5J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo5J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO5J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo5J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO6J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo6J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO6J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo6J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO7J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo7J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO7J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo7J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO8J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo8J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO8J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo8J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
        }
    }

    if(sentido == IZQUIERDA){
        switch(posicionPieza){
            case ELEFANTEJ1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), elefanteJ1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = ELEFANTEJ1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = elefanteJ1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CAMELLOJ1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), camelloJ1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CAMELLOJ1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = camelloJ1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CABALLO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo1J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO1J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = caballo1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CABALLO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo2J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO2J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = caballo2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case PERRO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro1J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO1J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = perro1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case PERRO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro2J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO2J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = perro2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case GATO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato1J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO1J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = gato1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case GATO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato2J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO2J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = gato2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo1J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO1J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo2J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO2J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO3J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo3J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO3J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo3J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO4J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo4J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO4J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo4J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO5J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo5J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO5J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo5J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO6J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo6J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO6J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo6J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO7J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo7J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO7J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo7J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO8J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo8J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO8J1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo8J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case ELEFANTEJ2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), elefanteJ2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = ELEFANTEJ2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = elefanteJ2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CAMELLOJ2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), camelloJ2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CAMELLOJ2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = camelloJ2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CABALLO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo1J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO1J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = caballo1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CABALLO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo2J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO2J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = caballo2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case PERRO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro1J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO1J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = perro1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case PERRO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro2J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO2J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = perro2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case GATO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato1J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO1J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = gato1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case GATO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato2J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO2J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = gato2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo1J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO1J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo2J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO2J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO3J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo3J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO3J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo3J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO4J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo4J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO4J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo4J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO5J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo5J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO5J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo5J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO6J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo6J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO6J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo6J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO7J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo7J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO7J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo7J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO8J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo8J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO8J2; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo8J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
        }
    }

}

void empujaOestiraJ2(int posicionPieza, GtkWidget *pieza, int sentido){
    if(sentido == ABAJO){
        switch(posicionPieza){
            case ELEFANTEJ1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), elefanteJ1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = ELEFANTEJ1; printf("\n piezaQueEmpuja = ",piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = elefanteJ1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CAMELLOJ1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), camelloJ1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ", piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CAMELLOJ1; printf("\n piezaQueEmpuja = ", piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = camelloJ1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CABALLO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo1J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ", piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO1J1; printf("\n piezaQueEmpuja = ", piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = caballo1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CABALLO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo2J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ", piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO2J1; printf("\n piezaQueEmpuja = ", piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = caballo2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case PERRO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro1J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ", piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO1J1; printf("\n piezaQueEmpuja = ", piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = perro1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case PERRO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro2J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ", piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO2J1; printf("\n piezaQueEmpuja = ", piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = perro2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case GATO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato1J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ", piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO1J1; printf("\n piezaQueEmpuja = ", piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = gato1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case GATO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato2J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ", piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO2J1; printf("\n piezaQueEmpuja = ", piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = gato2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo1J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ", piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO1J1; printf("\n piezaQueEmpuja = ", piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo2J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ", piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO2J1; printf("\n piezaQueEmpuja = ", piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO3J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo3J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ", piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO3J1; printf("\n piezaQueEmpuja = ", piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo3J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO4J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo4J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ", piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO4J1; printf("\n piezaQueEmpuja = ", piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo4J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO5J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo5J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ", piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO5J1; printf("\n piezaQueEmpuja = ", piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo5J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO6J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo6J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ", piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO6J1; printf("\n piezaQueEmpuja = ", piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo6J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO7J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo7J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ", piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO7J1; printf("\n piezaQueEmpuja = ", piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo7J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO8J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo8J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ", piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO8J1; printf("\n piezaQueEmpuja = ", piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo8J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case ELEFANTEJ2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), elefanteJ2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ", piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = ELEFANTEJ2; printf("\n piezaQueEmpuja = ", piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = elefanteJ2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CAMELLOJ2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), camelloJ2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ", piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CAMELLOJ2; printf("\n piezaQueEmpuja = ", piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = camelloJ2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CABALLO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo1J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ", piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO1J2; printf("\n piezaQueEmpuja = ", piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = caballo1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CABALLO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo2J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO2J2; printf("\n piezaQueEmpuja = ", piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = caballo2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case PERRO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro1J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO1J2;
                pesoPiezaQueEmpuja = perro1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case PERRO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro2J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO2J2;
                pesoPiezaQueEmpuja = perro2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case GATO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato1J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO1J2;
                pesoPiezaQueEmpuja = gato1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case GATO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato2J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO2J2;
                pesoPiezaQueEmpuja = gato2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo1J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO1J2;
                pesoPiezaQueEmpuja = conejo1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo2J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO2J2;
                pesoPiezaQueEmpuja = conejo2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO3J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo3J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO3J2;
                pesoPiezaQueEmpuja = conejo3J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO4J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo4J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO4J2;
                pesoPiezaQueEmpuja = conejo4J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO5J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo5J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO5J2;
                pesoPiezaQueEmpuja = conejo5J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO6J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo6J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO6J2;
                pesoPiezaQueEmpuja = conejo6J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO7J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo7J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO7J2;
                pesoPiezaQueEmpuja = conejo7J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO8J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst+1][coorYempEst], coordenadasTableroY[coorXempEst+1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo8J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO8J2;
                pesoPiezaQueEmpuja = conejo8J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
        }
    }

    if(sentido == ARRIBA){
        switch(posicionPieza){
            case ELEFANTEJ1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), elefanteJ1.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = ELEFANTEJ1;
                pesoPiezaQueEmpuja = elefanteJ1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CAMELLOJ1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), camelloJ1.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CAMELLOJ1;
                pesoPiezaQueEmpuja = camelloJ1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CABALLO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo1J1.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO1J1;
                pesoPiezaQueEmpuja = caballo1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CABALLO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo2J1.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO2J1;
                pesoPiezaQueEmpuja = caballo2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case PERRO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro1J1.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO1J1;
                pesoPiezaQueEmpuja = perro1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case PERRO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro2J1.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO2J1;
                pesoPiezaQueEmpuja = perro2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case GATO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato1J1.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO1J1;
                pesoPiezaQueEmpuja = gato1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case GATO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato2J1.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO2J1;
                pesoPiezaQueEmpuja = gato2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo1J1.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO1J1;
                pesoPiezaQueEmpuja = conejo1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo2J1.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO2J1;
                pesoPiezaQueEmpuja = conejo2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO3J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo3J1.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO3J1;
                pesoPiezaQueEmpuja = conejo3J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO4J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo4J1.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO4J1;
                pesoPiezaQueEmpuja = conejo4J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO5J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo5J1.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO5J1;
                pesoPiezaQueEmpuja = conejo5J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO6J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo6J1.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO6J1;
                pesoPiezaQueEmpuja = conejo6J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO7J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo7J1.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO7J1;
                pesoPiezaQueEmpuja = conejo7J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO8J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo8J1.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO8J1;
                pesoPiezaQueEmpuja = conejo8J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case ELEFANTEJ2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), elefanteJ2.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = ELEFANTEJ2;
                pesoPiezaQueEmpuja = elefanteJ2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CAMELLOJ2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), camelloJ2.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CAMELLOJ2;
                pesoPiezaQueEmpuja = camelloJ2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CABALLO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo1J2.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO1J2;
                pesoPiezaQueEmpuja = caballo1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CABALLO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo2J2.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO2J2;
                pesoPiezaQueEmpuja = caballo2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case PERRO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro1J2.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO1J2;
                pesoPiezaQueEmpuja = perro1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case PERRO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro2J2.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO2J2;
                pesoPiezaQueEmpuja = perro2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case GATO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato1J2.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO1J2;
                pesoPiezaQueEmpuja = gato1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case GATO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato2J2.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO2J2;
                pesoPiezaQueEmpuja = gato2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo1J2.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO1J2;
                pesoPiezaQueEmpuja = conejo1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo2J2.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO2J2;
                pesoPiezaQueEmpuja = conejo2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO3J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo3J2.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO3J2;
                pesoPiezaQueEmpuja = conejo3J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO4J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo4J2.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO4J2;
                pesoPiezaQueEmpuja = conejo4J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO5J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo5J2.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO5J2;
                pesoPiezaQueEmpuja = conejo5J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO6J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo6J2.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO6J2;
                pesoPiezaQueEmpuja = conejo6J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO7J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo7J2.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO7J2;
                pesoPiezaQueEmpuja = conejo7J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO8J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst-1][coorYempEst], coordenadasTableroY[coorXempEst-1][coorYempEst]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo8J2.Pieza, coordenadasTableroX[coorXempEst-2][coorYempEst], coordenadasTableroY[coorXempEst-2][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO8J2;
                pesoPiezaQueEmpuja = conejo8J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
        }
    }

    if(sentido == DERECHA){
        switch(posicionPieza){
            case ELEFANTEJ1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), elefanteJ1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = ELEFANTEJ1;
                pesoPiezaQueEmpuja = elefanteJ1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CAMELLOJ1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), camelloJ1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CAMELLOJ1;
                pesoPiezaQueEmpuja = camelloJ1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CABALLO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo1J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO1J1;
                pesoPiezaQueEmpuja = caballo1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CABALLO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo2J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO2J1;
                pesoPiezaQueEmpuja = caballo2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case PERRO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro1J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO1J1;
                pesoPiezaQueEmpuja = perro1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case PERRO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro2J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO2J1;
                pesoPiezaQueEmpuja = perro2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case GATO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato1J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO1J1;
                pesoPiezaQueEmpuja = gato1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case GATO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato2J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO2J1;
                pesoPiezaQueEmpuja = gato2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo1J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO1J1;
                pesoPiezaQueEmpuja = conejo1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo2J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO2J1;
                pesoPiezaQueEmpuja = conejo2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO3J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo3J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO3J1;
                pesoPiezaQueEmpuja = conejo3J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO4J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo4J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO4J1;
                pesoPiezaQueEmpuja = conejo4J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO5J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo5J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO5J1;
                pesoPiezaQueEmpuja = conejo5J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO6J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo6J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO6J1;
                pesoPiezaQueEmpuja = conejo6J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO7J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo7J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO7J1;
                pesoPiezaQueEmpuja = conejo7J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO8J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo8J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO8J1;
                pesoPiezaQueEmpuja = conejo8J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case ELEFANTEJ2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), elefanteJ2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = ELEFANTEJ2;
                pesoPiezaQueEmpuja = elefanteJ2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CAMELLOJ2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), camelloJ2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CAMELLOJ2;
                pesoPiezaQueEmpuja = camelloJ2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CABALLO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo1J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO1J2;
                pesoPiezaQueEmpuja = caballo1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CABALLO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo2J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO2J2;
                pesoPiezaQueEmpuja = caballo2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case PERRO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro1J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO1J2;
                pesoPiezaQueEmpuja = perro1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case PERRO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro2J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO2J2;
                pesoPiezaQueEmpuja = perro2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case GATO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato1J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO1J2;
                pesoPiezaQueEmpuja = gato1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case GATO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato2J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO2J2;
                pesoPiezaQueEmpuja = gato2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo1J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO1J2;
                pesoPiezaQueEmpuja = conejo1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo2J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO2J2;
                pesoPiezaQueEmpuja = conejo2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO3J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo3J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO3J2;
                pesoPiezaQueEmpuja = conejo3J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO4J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo4J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO4J2;
                pesoPiezaQueEmpuja = conejo4J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO5J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo5J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO5J2;
                pesoPiezaQueEmpuja = conejo5J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO6J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo6J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO6J2;
                pesoPiezaQueEmpuja = conejo6J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO7J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo7J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO7J2;
                pesoPiezaQueEmpuja = conejo7J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO8J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst+1], coordenadasTableroY[coorXempEst][coorYempEst+1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo8J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO8J2;
                pesoPiezaQueEmpuja = conejo8J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
        }
    }

    if(sentido == IZQUIERDA){
        switch(posicionPieza){
            case ELEFANTEJ1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), elefanteJ1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; ;
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = ELEFANTEJ1;
                pesoPiezaQueEmpuja = elefanteJ1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CAMELLOJ1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), camelloJ1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CAMELLOJ1;
                pesoPiezaQueEmpuja = camelloJ1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CABALLO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo1J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO1J1;
                pesoPiezaQueEmpuja = caballo1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CABALLO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo2J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO2J1;
                pesoPiezaQueEmpuja = caballo2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case PERRO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro1J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO1J1;
                pesoPiezaQueEmpuja = perro1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case PERRO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro2J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO2J1;
                pesoPiezaQueEmpuja = perro2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case GATO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato1J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO1J1;
                pesoPiezaQueEmpuja = gato1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case GATO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato2J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO2J1;
                pesoPiezaQueEmpuja = gato2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO1J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo1J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO1J1;
                pesoPiezaQueEmpuja = conejo1J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO2J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo2J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO2J1;
                pesoPiezaQueEmpuja = conejo2J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO3J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo3J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO3J1;
                pesoPiezaQueEmpuja = conejo3J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO4J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo4J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO4J1;
                pesoPiezaQueEmpuja = conejo4J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO5J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo5J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO5J1;
                pesoPiezaQueEmpuja = conejo5J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO6J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo6J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO6J1;
                pesoPiezaQueEmpuja = conejo6J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO7J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo7J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO7J1;
                pesoPiezaQueEmpuja = conejo7J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case CONEJO8J1:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo8J1.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO8J1;
                pesoPiezaQueEmpuja = conejo8J1.Peso;
                queJugadorPiezaQueEmpuja = J1;
                break;
            case ELEFANTEJ2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), elefanteJ2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = ELEFANTEJ2;
                pesoPiezaQueEmpuja = elefanteJ2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CAMELLOJ2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), camelloJ2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CAMELLOJ2;
                pesoPiezaQueEmpuja = camelloJ2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CABALLO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo1J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO1J2;
                pesoPiezaQueEmpuja = caballo1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CABALLO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo2J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CABALLO2J2;
                pesoPiezaQueEmpuja = caballo2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case PERRO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro1J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO1J2;
                pesoPiezaQueEmpuja = perro1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case PERRO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro2J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = PERRO2J2;
                pesoPiezaQueEmpuja = perro2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case GATO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato1J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO1J2;
                pesoPiezaQueEmpuja = gato1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case GATO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato2J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = GATO2J2;
                pesoPiezaQueEmpuja = gato2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO1J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo1J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO1J2;
                pesoPiezaQueEmpuja = conejo1J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO2J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo2J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO2J2;
                pesoPiezaQueEmpuja = conejo2J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO3J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo3J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO3J2;
                pesoPiezaQueEmpuja = conejo3J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO4J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo4J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO4J2;
                pesoPiezaQueEmpuja = conejo4J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO5J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo5J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst];
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO5J2;printf("\n piezaQueEmpuja = ", piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo5J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO6J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo6J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ", piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO6J2; printf("\n piezaQueEmpuja = ", piezaQueEmpuja);
                printf("\n");
                pesoPiezaQueEmpuja = conejo6J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO7J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo7J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ",piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO7J2; printf("\n piezaQueEmpuja = ", piezaQueEmpuja);printf("\n");
                pesoPiezaQueEmpuja = conejo7J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
            case CONEJO8J2:
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), pieza, coordenadasTableroX[coorXempEst][coorYempEst-1], coordenadasTableroY[coorXempEst][coorYempEst-1]);
                gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo8J2.Pieza, coordenadasTableroX[coorXempEst][coorYempEst], coordenadasTableroY[coorXempEst][coorYempEst]);
                piezaEmpujada = posicionPiezas[coorXempEst][coorYempEst]; printf("\n piezaEmpujada = ", piezaEmpujada);
                pesoPiezaEmpujada = pesoPiezas[coorXempEst][coorYempEst];
                queJugadorPiezaEmpujada = queJugador[coorXempEst][coorYempEst];
                piezaQueEmpuja = CONEJO8J2; printf("\n piezaQueEmpuja = ", piezaQueEmpuja);printf("\n");
                pesoPiezaQueEmpuja = conejo8J2.Peso;
                queJugadorPiezaQueEmpuja = J2;
                break;
        }
    }


}


/// Funciones que habilitan y deshabilitan las funciones de empujar y estirar.
void habilitarOPempujarOestirarJ1(){ //Habilita las opciones de empuje del Jugador 1
    //Jugador 1
    gtk_widget_show_all(elefanteJ1.movimiento.OPempujarArriba);
    gtk_widget_show_all(elefanteJ1.movimiento.OPestirarAbajo);
    gtk_widget_show_all(elefanteJ1.movimiento.OPempujarDerecha);
    gtk_widget_show_all(elefanteJ1.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(camelloJ1.movimiento.OPempujarArriba);
    gtk_widget_show_all(camelloJ1.movimiento.OPestirarAbajo);
    gtk_widget_show_all(camelloJ1.movimiento.OPempujarDerecha);
    gtk_widget_show_all(camelloJ1.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(caballo1J1.movimiento.OPempujarArriba);
    gtk_widget_show_all(caballo1J1.movimiento.OPestirarAbajo);
    gtk_widget_show_all(caballo1J1.movimiento.OPempujarDerecha);
    gtk_widget_show_all(caballo1J1.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(caballo2J1.movimiento.OPempujarArriba);
    gtk_widget_show_all(caballo2J1.movimiento.OPestirarAbajo);
    gtk_widget_show_all(caballo2J1.movimiento.OPempujarDerecha);
    gtk_widget_show_all(caballo2J1.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(perro1J1.movimiento.OPempujarArriba);
    gtk_widget_show_all(perro1J1.movimiento.OPestirarAbajo);
    gtk_widget_show_all(perro1J1.movimiento.OPempujarDerecha);
    gtk_widget_show_all(perro1J1.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(perro2J1.movimiento.OPempujarArriba);
    gtk_widget_show_all(perro2J1.movimiento.OPestirarAbajo);
    gtk_widget_show_all(perro2J1.movimiento.OPempujarDerecha);
    gtk_widget_show_all(perro2J1.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(gato1J1.movimiento.OPempujarArriba);
    gtk_widget_show_all(gato1J1.movimiento.OPestirarAbajo);
    gtk_widget_show_all(gato1J1.movimiento.OPempujarDerecha);
    gtk_widget_show_all(gato1J1.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(gato2J1.movimiento.OPempujarArriba);
    gtk_widget_show_all(gato2J1.movimiento.OPestirarAbajo);
    gtk_widget_show_all(gato2J1.movimiento.OPempujarDerecha);
    gtk_widget_show_all(gato2J1.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(conejo1J1.movimiento.OPempujarArriba);
    gtk_widget_show_all(conejo1J1.movimiento.OPestirarAbajo);
    gtk_widget_show_all(conejo1J1.movimiento.OPempujarDerecha);
    gtk_widget_show_all(conejo1J1.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(conejo2J1.movimiento.OPempujarArriba);
    gtk_widget_show_all(conejo2J1.movimiento.OPestirarAbajo);
    gtk_widget_show_all(conejo2J1.movimiento.OPempujarDerecha);
    gtk_widget_show_all(conejo2J1.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(conejo3J1.movimiento.OPempujarArriba);
    gtk_widget_show_all(conejo3J1.movimiento.OPestirarAbajo);
    gtk_widget_show_all(conejo3J1.movimiento.OPempujarDerecha);
    gtk_widget_show_all(conejo3J1.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(conejo4J1.movimiento.OPempujarArriba);
    gtk_widget_show_all(conejo4J1.movimiento.OPestirarAbajo);
    gtk_widget_show_all(conejo4J1.movimiento.OPempujarDerecha);
    gtk_widget_show_all(conejo4J1.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(conejo5J1.movimiento.OPempujarArriba);
    gtk_widget_show_all(conejo5J1.movimiento.OPestirarAbajo);
    gtk_widget_show_all(conejo5J1.movimiento.OPempujarDerecha);
    gtk_widget_show_all(conejo5J1.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(conejo6J1.movimiento.OPempujarArriba);
    gtk_widget_show_all(conejo6J1.movimiento.OPestirarAbajo);
    gtk_widget_show_all(conejo6J1.movimiento.OPempujarDerecha);
    gtk_widget_show_all(conejo6J1.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(conejo7J1.movimiento.OPempujarArriba);
    gtk_widget_show_all(conejo7J1.movimiento.OPestirarAbajo);
    gtk_widget_show_all(conejo7J1.movimiento.OPempujarDerecha);
    gtk_widget_show_all(conejo7J1.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(conejo8J1.movimiento.OPempujarArriba);
    gtk_widget_show_all(conejo8J1.movimiento.OPestirarAbajo);
    gtk_widget_show_all(conejo8J1.movimiento.OPempujarDerecha);
    gtk_widget_show_all(conejo8J1.movimiento.OPempujarIzquierda);

}

void habilitarOPempujarOestirarJ2(){ //Habilita las opciones de empuje del Jugador 2
    //Jugador 2
    gtk_widget_show_all(elefanteJ2.movimiento.OPempujarAbajo);
    gtk_widget_show_all(elefanteJ2.movimiento.OPestirarArriba);
    gtk_widget_show_all(elefanteJ2.movimiento.OPempujarDerecha);
    gtk_widget_show_all(elefanteJ2.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(camelloJ2.movimiento.OPempujarAbajo);
    gtk_widget_show_all(camelloJ2.movimiento.OPestirarArriba);
    gtk_widget_show_all(camelloJ2.movimiento.OPempujarDerecha);
    gtk_widget_show_all(camelloJ2.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(caballo1J2.movimiento.OPempujarAbajo);
    gtk_widget_show_all(caballo1J2.movimiento.OPestirarArriba);
    gtk_widget_show_all(caballo1J2.movimiento.OPempujarDerecha);
    gtk_widget_show_all(caballo1J2.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(caballo2J2.movimiento.OPempujarAbajo);
    gtk_widget_show_all(caballo2J2.movimiento.OPestirarArriba);
    gtk_widget_show_all(caballo2J2.movimiento.OPempujarDerecha);
    gtk_widget_show_all(caballo2J2.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(perro1J2.movimiento.OPempujarAbajo);
    gtk_widget_show_all(perro1J2.movimiento.OPestirarArriba);
    gtk_widget_show_all(perro1J2.movimiento.OPempujarDerecha);
    gtk_widget_show_all(perro1J2.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(perro2J2.movimiento.OPempujarAbajo);
    gtk_widget_show_all(perro2J2.movimiento.OPestirarArriba);
    gtk_widget_show_all(perro2J2.movimiento.OPempujarDerecha);
    gtk_widget_show_all(perro2J2.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(gato1J2.movimiento.OPempujarAbajo);
    gtk_widget_show_all(gato1J2.movimiento.OPestirarArriba);
    gtk_widget_show_all(gato1J2.movimiento.OPempujarDerecha);
    gtk_widget_show_all(gato1J2.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(gato2J2.movimiento.OPempujarAbajo);
    gtk_widget_show_all(gato2J2.movimiento.OPestirarArriba);
    gtk_widget_show_all(gato2J2.movimiento.OPempujarDerecha);
    gtk_widget_show_all(gato2J2.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(conejo1J2.movimiento.OPempujarAbajo);
    gtk_widget_show_all(conejo1J2.movimiento.OPestirarArriba);
    gtk_widget_show_all(conejo1J2.movimiento.OPempujarDerecha);
    gtk_widget_show_all(conejo1J2.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(conejo2J2.movimiento.OPempujarAbajo);
    gtk_widget_show_all(conejo2J2.movimiento.OPestirarArriba);
    gtk_widget_show_all(conejo2J2.movimiento.OPempujarDerecha);
    gtk_widget_show_all(conejo2J2.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(conejo3J2.movimiento.OPempujarAbajo);
    gtk_widget_show_all(conejo3J2.movimiento.OPestirarArriba);
    gtk_widget_show_all(conejo3J2.movimiento.OPempujarDerecha);
    gtk_widget_show_all(conejo3J2.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(conejo4J2.movimiento.OPempujarAbajo);
    gtk_widget_show_all(conejo4J2.movimiento.OPestirarArriba);
    gtk_widget_show_all(conejo4J2.movimiento.OPempujarDerecha);
    gtk_widget_show_all(conejo4J2.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(conejo5J2.movimiento.OPempujarAbajo);
    gtk_widget_show_all(conejo5J2.movimiento.OPestirarArriba);
    gtk_widget_show_all(conejo5J2.movimiento.OPempujarDerecha);
    gtk_widget_show_all(conejo5J2.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(conejo6J2.movimiento.OPempujarAbajo);
    gtk_widget_show_all(conejo6J2.movimiento.OPestirarArriba);
    gtk_widget_show_all(conejo6J2.movimiento.OPempujarDerecha);
    gtk_widget_show_all(conejo6J2.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(conejo7J2.movimiento.OPempujarAbajo);
    gtk_widget_show_all(conejo7J2.movimiento.OPestirarArriba);
    gtk_widget_show_all(conejo7J2.movimiento.OPempujarDerecha);
    gtk_widget_show_all(conejo7J2.movimiento.OPempujarIzquierda);

    gtk_widget_show_all(conejo8J2.movimiento.OPempujarAbajo);
    gtk_widget_show_all(conejo8J2.movimiento.OPestirarArriba);
    gtk_widget_show_all(conejo8J2.movimiento.OPempujarDerecha);
    gtk_widget_show_all(conejo8J2.movimiento.OPempujarIzquierda);
}

void deshabilitarOPempujarOestirarJ1(){ //Deshabilita las opciones de empuje del Jugador 1
    //Jugador 1
    gtk_widget_hide(elefanteJ1.movimiento.OPempujarArriba);
    gtk_widget_hide(elefanteJ1.movimiento.OPestirarAbajo);
    gtk_widget_hide(elefanteJ1.movimiento.OPempujarDerecha);
    gtk_widget_hide(elefanteJ1.movimiento.OPempujarIzquierda);

    gtk_widget_hide(camelloJ1.movimiento.OPempujarArriba);
    gtk_widget_hide(camelloJ1.movimiento.OPestirarAbajo);
    gtk_widget_hide(camelloJ1.movimiento.OPempujarDerecha);
    gtk_widget_hide(camelloJ1.movimiento.OPempujarIzquierda);

    gtk_widget_hide(caballo1J1.movimiento.OPempujarArriba);
    gtk_widget_hide(caballo1J1.movimiento.OPestirarAbajo);
    gtk_widget_hide(caballo1J1.movimiento.OPempujarDerecha);
    gtk_widget_hide(caballo1J1.movimiento.OPempujarIzquierda);

    gtk_widget_hide(caballo2J1.movimiento.OPempujarArriba);
    gtk_widget_hide(caballo2J1.movimiento.OPestirarAbajo);
    gtk_widget_hide(caballo2J1.movimiento.OPempujarDerecha);
    gtk_widget_hide(caballo2J1.movimiento.OPempujarIzquierda);

    gtk_widget_hide(perro1J1.movimiento.OPempujarArriba);
    gtk_widget_hide(perro1J1.movimiento.OPestirarAbajo);
    gtk_widget_hide(perro1J1.movimiento.OPempujarDerecha);
    gtk_widget_hide(perro1J1.movimiento.OPempujarIzquierda);

    gtk_widget_hide(perro2J1.movimiento.OPempujarArriba);
    gtk_widget_hide(perro2J1.movimiento.OPestirarAbajo);
    gtk_widget_hide(perro2J1.movimiento.OPempujarDerecha);
    gtk_widget_hide(perro2J1.movimiento.OPempujarIzquierda);

    gtk_widget_hide(gato1J1.movimiento.OPempujarArriba);
    gtk_widget_hide(gato1J1.movimiento.OPestirarAbajo);
    gtk_widget_hide(gato1J1.movimiento.OPempujarDerecha);
    gtk_widget_hide(gato1J1.movimiento.OPempujarIzquierda);

    gtk_widget_hide(gato2J1.movimiento.OPempujarArriba);
    gtk_widget_hide(gato2J1.movimiento.OPestirarAbajo);
    gtk_widget_hide(gato2J1.movimiento.OPempujarDerecha);
    gtk_widget_hide(gato2J1.movimiento.OPempujarIzquierda);

    gtk_widget_hide(conejo1J1.movimiento.OPempujarArriba);
    gtk_widget_hide(conejo1J1.movimiento.OPestirarAbajo);
    gtk_widget_hide(conejo1J1.movimiento.OPempujarDerecha);
    gtk_widget_hide(conejo1J1.movimiento.OPempujarIzquierda);

    gtk_widget_hide(conejo2J1.movimiento.OPempujarArriba);
    gtk_widget_hide(conejo2J1.movimiento.OPestirarAbajo);
    gtk_widget_hide(conejo2J1.movimiento.OPempujarDerecha);
    gtk_widget_hide(conejo2J1.movimiento.OPempujarIzquierda);

    gtk_widget_hide(conejo3J1.movimiento.OPempujarArriba);
    gtk_widget_hide(conejo3J1.movimiento.OPestirarAbajo);
    gtk_widget_hide(conejo3J1.movimiento.OPempujarDerecha);
    gtk_widget_hide(conejo3J1.movimiento.OPempujarIzquierda);

    gtk_widget_hide(conejo4J1.movimiento.OPempujarArriba);
    gtk_widget_hide(conejo4J1.movimiento.OPestirarAbajo);
    gtk_widget_hide(conejo4J1.movimiento.OPempujarDerecha);
    gtk_widget_hide(conejo4J1.movimiento.OPempujarIzquierda);

    gtk_widget_hide(conejo5J1.movimiento.OPempujarArriba);
    gtk_widget_hide(conejo5J1.movimiento.OPestirarAbajo);
    gtk_widget_hide(conejo5J1.movimiento.OPempujarDerecha);
    gtk_widget_hide(conejo5J1.movimiento.OPempujarIzquierda);

    gtk_widget_hide(conejo6J1.movimiento.OPempujarArriba);
    gtk_widget_hide(conejo6J1.movimiento.OPestirarAbajo);
    gtk_widget_hide(conejo6J1.movimiento.OPempujarDerecha);
    gtk_widget_hide(conejo6J1.movimiento.OPempujarIzquierda);

    gtk_widget_hide(conejo7J1.movimiento.OPempujarArriba);
    gtk_widget_hide(conejo7J1.movimiento.OPestirarAbajo);
    gtk_widget_hide(conejo7J1.movimiento.OPempujarDerecha);
    gtk_widget_hide(conejo7J1.movimiento.OPempujarIzquierda);

    gtk_widget_hide(conejo8J1.movimiento.OPempujarArriba);
    gtk_widget_hide(conejo8J1.movimiento.OPestirarAbajo);
    gtk_widget_hide(conejo8J1.movimiento.OPempujarDerecha);
    gtk_widget_hide(conejo8J1.movimiento.OPempujarIzquierda);
}

void deshabilitarOPempujarOestirarJ2(){ //Deshabilita las opciones de empuje del Jugador 2
    //Jugador 2
    gtk_widget_hide(elefanteJ2.movimiento.OPempujarAbajo);
    gtk_widget_hide(elefanteJ2.movimiento.OPestirarArriba);
    gtk_widget_hide(elefanteJ2.movimiento.OPempujarDerecha);
    gtk_widget_hide(elefanteJ2.movimiento.OPempujarIzquierda);

    gtk_widget_hide(camelloJ2.movimiento.OPempujarAbajo);
    gtk_widget_hide(camelloJ2.movimiento.OPestirarArriba);
    gtk_widget_hide(camelloJ2.movimiento.OPempujarDerecha);
    gtk_widget_hide(camelloJ2.movimiento.OPempujarIzquierda);

    gtk_widget_hide(caballo1J2.movimiento.OPempujarAbajo);
    gtk_widget_hide(caballo1J2.movimiento.OPestirarArriba);
    gtk_widget_hide(caballo1J2.movimiento.OPempujarDerecha);
    gtk_widget_hide(caballo1J2.movimiento.OPempujarIzquierda);

    gtk_widget_hide(caballo2J2.movimiento.OPempujarAbajo);
    gtk_widget_hide(caballo2J2.movimiento.OPestirarArriba);
    gtk_widget_hide(caballo2J2.movimiento.OPempujarDerecha);
    gtk_widget_hide(caballo2J2.movimiento.OPempujarIzquierda);

    gtk_widget_hide(perro1J2.movimiento.OPempujarAbajo);
    gtk_widget_hide(perro1J2.movimiento.OPestirarArriba);
    gtk_widget_hide(perro1J2.movimiento.OPempujarDerecha);
    gtk_widget_hide(perro1J2.movimiento.OPempujarIzquierda);

    gtk_widget_hide(perro2J2.movimiento.OPempujarAbajo);
    gtk_widget_hide(perro2J2.movimiento.OPestirarArriba);
    gtk_widget_hide(perro2J2.movimiento.OPempujarDerecha);
    gtk_widget_hide(perro2J2.movimiento.OPempujarIzquierda);

    gtk_widget_hide(gato1J2.movimiento.OPempujarAbajo);
    gtk_widget_hide(gato1J2.movimiento.OPestirarArriba);
    gtk_widget_hide(gato1J2.movimiento.OPempujarDerecha);
    gtk_widget_hide(gato1J2.movimiento.OPempujarIzquierda);

    gtk_widget_hide(gato2J2.movimiento.OPempujarAbajo);
    gtk_widget_hide(gato2J2.movimiento.OPestirarArriba);
    gtk_widget_hide(gato2J2.movimiento.OPempujarDerecha);
    gtk_widget_hide(gato2J2.movimiento.OPempujarIzquierda);

    gtk_widget_hide(conejo1J2.movimiento.OPempujarAbajo);
    gtk_widget_hide(conejo1J2.movimiento.OPestirarArriba);
    gtk_widget_hide(conejo1J2.movimiento.OPempujarDerecha);
    gtk_widget_hide(conejo1J2.movimiento.OPempujarIzquierda);

    gtk_widget_hide(conejo2J2.movimiento.OPempujarAbajo);
    gtk_widget_hide(conejo2J2.movimiento.OPestirarArriba);
    gtk_widget_hide(conejo2J2.movimiento.OPempujarDerecha);
    gtk_widget_hide(conejo2J2.movimiento.OPempujarIzquierda);

    gtk_widget_hide(conejo3J2.movimiento.OPempujarAbajo);
    gtk_widget_hide(conejo3J2.movimiento.OPestirarArriba);
    gtk_widget_hide(conejo3J2.movimiento.OPempujarDerecha);
    gtk_widget_hide(conejo3J2.movimiento.OPempujarIzquierda);

    gtk_widget_hide(conejo4J2.movimiento.OPempujarAbajo);
    gtk_widget_hide(conejo4J2.movimiento.OPestirarArriba);
    gtk_widget_hide(conejo4J2.movimiento.OPempujarDerecha);
    gtk_widget_hide(conejo4J2.movimiento.OPempujarIzquierda);

    gtk_widget_hide(conejo5J2.movimiento.OPempujarAbajo);
    gtk_widget_hide(conejo5J2.movimiento.OPestirarArriba);
    gtk_widget_hide(conejo5J2.movimiento.OPempujarDerecha);
    gtk_widget_hide(conejo5J2.movimiento.OPempujarIzquierda);

    gtk_widget_hide(conejo6J2.movimiento.OPempujarAbajo);
    gtk_widget_hide(conejo6J2.movimiento.OPestirarArriba);
    gtk_widget_hide(conejo6J2.movimiento.OPempujarDerecha);
    gtk_widget_hide(conejo6J2.movimiento.OPempujarIzquierda);

    gtk_widget_hide(conejo7J2.movimiento.OPempujarAbajo);
    gtk_widget_hide(conejo7J2.movimiento.OPestirarArriba);
    gtk_widget_hide(conejo7J2.movimiento.OPempujarDerecha);
    gtk_widget_hide(conejo7J2.movimiento.OPempujarIzquierda);

    gtk_widget_hide(conejo8J2.movimiento.OPempujarAbajo);
    gtk_widget_hide(conejo8J2.movimiento.OPestirarArriba);
    gtk_widget_hide(conejo8J2.movimiento.OPempujarDerecha);
    gtk_widget_hide(conejo8J2.movimiento.OPempujarIzquierda);
}



/// FUNCIONES DE CONTROL CON RETORNOS LOGICOS DE ACUERDO AL CONTROL DE LA SITUACION QUE SE REQUIERA PARA EL MOVIMIENTO, EMPUJE O ESTIRAMIENTO
int siSobrePasaLimites (int filaOcolumna, int sentido){ //Si retorna true, se intenta mover la pieza fuera del tablero y se envía una advertencia, si retorna false, se mueve la pieza
    if(sentido == ABAJO){//verificando abajo
        if(filaOcolumna > 7){
            return true;
        }
    }

    if(sentido == ARRIBA){//verificando arriba
        if(filaOcolumna < 0){
            return true;
        }
    }

    if(sentido == DERECHA){//verificando derecha
        if(filaOcolumna > 7){
            return true;
        }
    }

    if(sentido == IZQUIERDA){//verificando izquierda
        if(filaOcolumna < 0){
            return true;
        }
    }
    return false;
}

int siCongela(int I, int J){ //Si retorna true, la pieza esta congelada y se envía una advertencia, si retorna false, se mueve la pieza

///  VERIFICANDO ABAJO
    if(queJugador[I+1][J] == queJugador[I][J]){ //Si encuentra un companero
        return false; //no congela
    }
    if(posicionPiezas[I+1][J] != 0){
            if(queJugador[I+1][J] != queJugador[I][J]){//si hay un enemigo
                if(pesoPiezas[I+1][J] > pesoPiezas[I][J]){ //y si el enemigo es mas pesado
                    return true; //congela
                }
            }
    }

///  VERIFICANDO ARRIBA
    if(queJugador[I-1][J] == queJugador[I][J]){ //Si encuentra un companero
        return false; //no congela
    }
    if(posicionPiezas[I-1][J] != 0){
            if(queJugador[I-1][J] != queJugador[I][J]){ //si hay un enemigo
                if(pesoPiezas[I-1][J] > pesoPiezas[I][J]){ //y si el enemigo es mas pesado
                    return true; //congela
                }
            }
    }

///  VERIFICANDO A LA DERECHA
    if(queJugador[I][J+1] == queJugador[I][J]){ //si encuentra un companero
        return false; //no cogela
    }
    if(posicionPiezas[I][J+1] != 0){
            if(queJugador[I][J+1] != queJugador[I][J]){ //si encuentra un enemigo
                if(pesoPiezas[I][J+1] > pesoPiezas[I][J]){ //y si el enemigo es mas pesado
                    return true; //congela
                }
            }
    }

/// VERIFICANDO A LA IZQUIERDA
    if(queJugador[I][J-1] == queJugador[I][J]){ //si encuentra un companero
        return false; //no congela
    }
    if(posicionPiezas[I][J-1] != 0){
        if(queJugador[I][J-1] != queJugador[I][J]){ //si encuentra un enemigo
                if(pesoPiezas[I][J-1] > pesoPiezas[I][J]){ //y si el enemigo es mas pesado
                    return true; //congela
                }
            }
    }
    return false; //si no se cumple ni una, no congela.
}

int siLugarEstaOcupado(int K, int L, int sentido){ //Si retorna true es porque se intenta mover una pieza donde ya esta otra, y este intercambio solo se permite antes de iniciar la partida; también se manda una advertencia.
    if(sentido == ABAJO){
        if(posicionPiezas[K+1][L] != 0){//verificando abajo
            return true;
        }
    }

    if(sentido == ARRIBA){
        if(posicionPiezas[K-1][L] != 0){//verificando arriba
            return true;
        }
    }

    if(sentido == DERECHA){
        if(posicionPiezas[K][L+1] != 0){//verificando derecha
            return true;
        }
    }

    if(sentido == IZQUIERDA){
        if(posicionPiezas[K][L-1] != 0){//verificando izquierda
            return true;
        }
    }
    return false;
}

int siCaeEnTrampa(int fil, int col){ //Si cae en una trampa y no esta ninguna pieza amiga a su alrededor, retorna true y se elimina la pieza, sino se mueve normalmente.
    if((fil == 2 && col == 2) || (fil == 2 && col == 5) || (fil == 5 && col == 2) || (fil == 5 && col == 5)){
        if(queJugador[fil+1][col] == queJugador[fil][col]){
                printf("\n abajo se encuentra un companero");
                return false;
        }
        if(queJugador[fil-1][col] == queJugador[fil][col]){
                printf("\n arriba se encuentra un companero");
                return false;
        }

        if(queJugador[fil][col+1] == queJugador[fil][col]){
                printf("\n a la derecha se encuentra un companero");
                return false;
        }

        if(queJugador[fil][col-1] == queJugador[fil][col]){
                printf("\n a la izquierda se encuentra un companero");
                return false;
        }
        return true;
    }
    return false;
}

int siGana(int I, int J, int sentido, int jugador, int pieza){

    if((pieza == CONEJO1J1) || (pieza == CONEJO2J1)|| (pieza == CONEJO3J1) || (pieza == CONEJO4J1) || (pieza == CONEJO5J1) || (pieza == CONEJO6J1) || (pieza == CONEJO7J1) || (pieza == CONEJO8J1) || (pieza == CONEJO1J2) || (pieza == CONEJO2J2) || (pieza == CONEJO3J2) || (pieza == CONEJO4J2) || (pieza == CONEJO5J2) || (pieza == CONEJO6J2) || (pieza == CONEJO7J2) || (pieza == CONEJO8J2)){
        if(sentido == ABAJO){
            if(jugador == J1){
                if((I+1 == 7 && J == 0) || (I+1 == 7 && J == 1) || (I+1 == 7 && J == 2) || (I+1 == 7 && J == 3) || (I+1 == 7 && J == 4) || (I+1 == 7 && J == 5) || (I+1 == 7 && J == 6) || (I+1 == 7 && J == 7)){
                    return true;
                }
            }
        }

        if(sentido == ARRIBA){
            if(jugador == J2){
                if((I-1 == 0 && J == 0) || (I-1 == 0 && J == 1) || (I-1 == 0 && J == 2) || (I-1 == 0 && J == 3) || (I-1 == 0 && J == 4) || (I-1 == 0 && J == 5) || (I-1 == 0 && J == 6) || (I-1 == 0 && J == 7)){
                    return true;
                }
            }
        }
    }
    return false;
}

///Funciones en prueba..

void FNreiniciarJuego(){

    //Jugador 1
    gtk_widget_destroy(elefanteJ1.Pieza);
    gtk_widget_destroy(camelloJ1.Pieza);
    gtk_widget_destroy(caballo1J1.Pieza);
    gtk_widget_destroy(caballo2J1.Pieza);
    gtk_widget_destroy(perro1J1.Pieza);
    gtk_widget_destroy(perro2J1.Pieza);
    gtk_widget_destroy(gato1J1.Pieza);
    gtk_widget_destroy(gato2J1.Pieza);
    gtk_widget_destroy(conejo1J1.Pieza);
    gtk_widget_destroy(conejo2J1.Pieza);
    gtk_widget_destroy(conejo3J1.Pieza);
    gtk_widget_destroy(conejo4J1.Pieza);
    gtk_widget_destroy(conejo5J1.Pieza);
    gtk_widget_destroy(conejo6J1.Pieza);
    gtk_widget_destroy(conejo7J1.Pieza);
    gtk_widget_destroy(conejo8J1.Pieza);

    //Jugador 2
    gtk_widget_destroy(elefanteJ2.Pieza);
    gtk_widget_destroy(camelloJ2.Pieza);
    gtk_widget_destroy(caballo1J2.Pieza);
    gtk_widget_destroy(caballo2J2.Pieza);
    gtk_widget_destroy(perro1J2.Pieza);
    gtk_widget_destroy(perro2J2.Pieza);
    gtk_widget_destroy(gato1J2.Pieza);
    gtk_widget_destroy(gato2J2.Pieza);
    gtk_widget_destroy(conejo1J2.Pieza);
    gtk_widget_destroy(conejo2J2.Pieza);
    gtk_widget_destroy(conejo3J2.Pieza);
    gtk_widget_destroy(conejo4J2.Pieza);
    gtk_widget_destroy(conejo5J2.Pieza);
    gtk_widget_destroy(conejo6J2.Pieza);
    gtk_widget_destroy(conejo7J2.Pieza);
    gtk_widget_destroy(conejo8J2.Pieza);

    for(int i = 0; i < 8; i ++){
        for(int j = 0; j < 8; j++){
            if(posicionPiezas[i][j] != 0){
                if(pesoPiezas[i][j] != 0){
                    if(queJugador[i][j] != 0){
                        posicionPiezas[i][j] = 0;
                        pesoPiezas[i][j] = 0;
                        queJugador[i][j] = 0;
                    }
                }
            }
        }
    }

    FNimprimirMatrices();

    Sleep(500);

    system("cls");
    printf("\n HoLa");

    FNcrearPiezas();
    FNdimensionarPiezas();
    FNrandomizarPiezas();
    FNconfigMovimientoPiezas();

    gtk_widget_show_all(formJuego.Pantalla);
}

void FNmovimientoAleatorio(){
    printf("\n Entro a FNmovimientoAleatorio");
    FNrecargarPiezas();
    P = 1;

        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(/*piezasJ2[randomPos]*/ CAMELLOJ2  == posicionPiezas[i][j]){ //Si la pieza aleatoria elegida es igual a la pieza en la matriz de piezas
                   if(posicionPiezas[i+1][j] == 0){
                        P = i;
                        printf("\n i+1 = ", P+1," j = ",j);printf("\n");
                        gtk_layout_move(GTK_LAYOUT(formJuego.Layout), camelloJ2.Pieza, coordenadasTableroX[P-1][j], coordenadasTableroY[P-1][j]);
                        gtk_widget_show_all(formJuego.Pantalla);
                   }
                }
            }
        }

        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(/*piezasJ2[randomPos]*/ ELEFANTEJ2  == posicionPiezas[i][j]){ //Si la pieza aleatoria elegida es igual a la pieza en la matriz de piezas
                    if(posicionPiezas[i+1][j] == 0){
                        P = i;
                        printf("\n i+1 = ", P+1," j = ",j);printf("\n");
                        gtk_layout_move(GTK_LAYOUT(formJuego.Layout), elefanteJ2.Pieza, coordenadasTableroX[P-1][j], coordenadasTableroY[P-1][j]);
                        gtk_widget_show_all(formJuego.Pantalla);
                    }
                }
            }
        }

        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(/*piezasJ2[randomPos]*/ GATO1J2  == posicionPiezas[i][j]){ //Si la pieza aleatoria elegida es igual a la pieza en la matriz de piezas
                    if(posicionPiezas[i+1][j] == 0){
                        P = i;
                        printf("\n i+1 = ", P+1," j = ",j);printf("\n");
                        gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato1J2.Pieza, coordenadasTableroX[P-1][j], coordenadasTableroY[P-1][j]);
                        gtk_widget_show_all(formJuego.Pantalla);
                    }
                }
            }
        }

        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(/*piezasJ2[randomPos]*/ CABALLO2J2  == posicionPiezas[i][j]){ //Si la pieza aleatoria elegida es igual a la pieza en la matriz de piezas
                    if(posicionPiezas[i+1][j] == 0){
                        P = i;
                        printf("\n i+1 = ", P+1," j = ",j);printf("\n");
                        gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo2J2.Pieza, coordenadasTableroX[P-1][j], coordenadasTableroY[P-1][j]);
                        gtk_widget_show_all(formJuego.Pantalla);
                    }
                }
            }
        }


}

void FNmoverAleatoriamente(int constPieza){
    switch(constPieza){
        case ELEFANTEJ2:
            gtk_layout_move(GTK_LAYOUT(formJuego.Layout), elefanteJ2.Pieza, coordenadasTableroX[fila-1][columna], coordenadasTableroY[fila-1][columna]);
            break;
        case CAMELLOJ2:
            gtk_layout_move(GTK_LAYOUT(formJuego.Layout), camelloJ2.Pieza, coordenadasTableroX[fila-1][columna], coordenadasTableroY[fila-1][columna]);
            break;
        case CABALLO1J2:
            gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo1J2.Pieza, coordenadasTableroX[fila-1][columna], coordenadasTableroY[fila-1][columna]);
            break;
        case CABALLO2J2:
            gtk_layout_move(GTK_LAYOUT(formJuego.Layout), caballo2J2.Pieza, coordenadasTableroX[fila-1][columna], coordenadasTableroY[fila-1][columna]);
            break;
        case PERRO1J2:
            gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro1J2.Pieza, coordenadasTableroX[fila-1][columna], coordenadasTableroY[fila-1][columna]);
            break;
        case PERRO2J2:
            gtk_layout_move(GTK_LAYOUT(formJuego.Layout), perro2J2.Pieza, coordenadasTableroX[fila-1][columna], coordenadasTableroY[fila-1][columna]);
            break;
        case GATO1J2:
            gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato1J2.Pieza, coordenadasTableroX[fila-1][columna], coordenadasTableroY[fila-1][columna]);
            break;
        case GATO2J2:
            gtk_layout_move(GTK_LAYOUT(formJuego.Layout), gato2J2.Pieza, coordenadasTableroX[fila-1][columna], coordenadasTableroY[fila-1][columna]);
            break;
        case CONEJO1J2:
            gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo1J2.Pieza, coordenadasTableroX[fila-1][columna], coordenadasTableroY[fila-1][columna]);
            break;
        case CONEJO2J2:
            gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo2J2.Pieza, coordenadasTableroX[fila-1][columna], coordenadasTableroY[fila-1][columna]);
            break;
        case CONEJO3J2:
            gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo3J2.Pieza, coordenadasTableroX[fila-1][columna], coordenadasTableroY[fila-1][columna]);
            break;
        case CONEJO4J2:
            gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo4J2.Pieza, coordenadasTableroX[fila-1][columna], coordenadasTableroY[fila-1][columna]);
            break;
        case CONEJO5J2:
            gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo5J2.Pieza, coordenadasTableroX[fila-1][columna], coordenadasTableroY[fila-1][columna]);
            break;
        case CONEJO6J2:
            gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo6J2.Pieza, coordenadasTableroX[fila-1][columna], coordenadasTableroY[fila-1][columna]);
            break;
        case CONEJO7J2:
            gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo7J2.Pieza, coordenadasTableroX[fila-1][columna], coordenadasTableroY[fila-1][columna]);
            break;
        case CONEJO8J2:
            gtk_layout_move(GTK_LAYOUT(formJuego.Layout), conejo8J2.Pieza, coordenadasTableroX[fila-1][columna], coordenadasTableroY[fila-1][columna]);
            break;
    }
    gtk_widget_show_all(formJuego.Pantalla);
}
