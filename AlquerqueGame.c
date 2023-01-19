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
int sentidos[5] = {ARRIBA, ABAJO, DERECHA, IZQUIERDA}; //Se carga en un arreglo los sentidos de los movimientos
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
void FNcrearTurnos();
void FNcolocarPiezas();
void FNreiniciarJuego();
static void FNiniciarPiezasJ1();
static void FNiniciarPiezasJ2();
void manejadorTurnoJ1(GtkToggleButton *turno);
void manejadorTurnoJ2(GtkToggleButton *turno);
void habilitarOPmovimientosJ1();
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
    GtkWidget *OPmoverIzquierda;
    GtkWidget *OPcancelar;

    GtkWidget *LBLmoverArriba;
    GtkWidget *LBLmoverAbajo;
    GtkWidget *LBLmoverDerecha;
    GtkWidget *LBLmoverIzquierda;
    GtkWidget *LBLcancelar;

    GtkWidget *BOXmoverArriba;
    GtkWidget *BOXmoverAbajo;
    GtkWidget *BOXmoverDerecha;
    GtkWidget *BOXmoverIzquierda;
    GtkWidget *BOXcancelar;

    GtkWidget *ICOmoverArriba;
    GtkWidget *ICOmoverAbajo;
    GtkWidget *ICOmoverDerecha;
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

 //   FNconfigMovimientoPiezas(); //Se configura el movimiento de las piezas

  //   FNimprimirMatrices(); //Se imprime en consola las matrices con que se trabajan, para el control de los datos de los movimientos.


    gtk_widget_show_all(formJuego.Pantalla); //Se muestra todo lo que hay en pantalla.
    gtk_main(); //Definición del loop del programa principal main.

    return status;
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
                //pesoPiezas[fila][columna] = elefanteJ1.Peso;
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
    //FNconfigMovimientoPiezas();

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
    gtk_button_set_relief(GTK_BUTTON(FBlanca1.Pieza), GTK_RELIEF_NORMAL);

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
    gtk_button_set_relief(GTK_BUTTON(FBlanca4.Pieza), GTK_RELIEF_NORMAL);

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
        //habilitarOPempujarOestirarJ2(); //Se habilitan las opciones de empuje o estire del J2, las cuales el J1 puede manejar
        gtk_widget_set_sensitive(GTK_WIDGET(Jugador2.TurnoToggle), FALSE); //Se desactiva el boton toggle de turno del J2
    }
    else{ //Sino, cuando el boton toggle se desactiva, todo lo mencionado en las sentencias de arriba, se revierten.
        printf("\n TURNO J1 INACTIVO");
        Jugador1.TurnoContador = 0;
        gtk_label_set_text(GTK_LABEL(Jugador1.TurnoCantidadMovimientos), "0");
        //deshabilitarOPmovimientosJ1();
        //deshabilitarOPempujarOestirarJ2();
        gtk_widget_set_sensitive(GTK_WIDGET(Jugador2.TurnoToggle), TRUE);
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
    return false;
}

int siSobrePasaLimites (int filaOcolumna, int sentido){ //Si retorna true, se intenta mover la pieza fuera del tablero y se env�a una advertencia, si retorna false, se mueve la pieza
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
                                    FNmensajeDialogo(formDialogo.Ventana, "\n\n Los intercambios entre piezas se deben hacer al inicio!!\n Ahora solo puedes empujar o estirar! \n");
                                    printf("\a");
                                }
                                else{
                                    if(Jugador1.TurnoContador >= 4 || Jugador2.TurnoContador >= 4){
                                        FNmensajeDialogo(formDialogo.Ventana, "\n\n Los turnos por cada jugador, no pueden superar 4 movimientos \n\n");
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

void manejadorTurnoJ2(GtkToggleButton *turno){ //Maneja el turno del Jugador 2 cuando se presiona el boton de tipo ToggleButton, dicho botón tiene dos estados (Presionado y No presionado)
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(Jugador2.TurnoToggle))){ //Si el estado del boton esta activo
        printf("\n TURNO J2 ACTIVO");
        habilitarOPmovimientosJ2(); //Se habilitan las opciones de movimiento para el J2
        //habilitarOPempujarOestirarJ1(); //Se habilitan las opciones de empuje o estire del J1, las cuales el J2 puede manejar
        gtk_widget_set_sensitive(GTK_WIDGET(Jugador1.TurnoToggle), FALSE); //Se desactiva el boton toggle de turno del J1
    }
    else{ //Sino, cuando el boton toggle se desactiva, todo lo mencionado en las sentencias de arriba, se revierten.
        printf("\n TURNO J2 INACTIVO");
        Jugador2.TurnoContador = 0;
        gtk_label_set_text(GTK_LABEL(Jugador2.TurnoCantidadMovimientos), "0");
        //deshabilitarOPmovimientosJ2();
        //deshabilitarOPempujarOestirarJ1();
        gtk_widget_set_sensitive(GTK_WIDGET(Jugador1.TurnoToggle), TRUE);
    }
}


void FNmostrarOPmenusPiezas(){ //(DEPRECADO) Muestra las opciones de los menús
    //Observacion: las llamadas a ciertas funciones de los conejos ("Mover arriba" y "Mover abajo") estan comentadas (pero no eliminadas para posibles pruebas) ya que el conejo no puede retroceder.

    //Jugador 1
    gtk_widget_show_all(FBlanca1.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca1.movimiento.OPmoverIzquierda);
}


void habilitarOPmovimientosJ1(){ //Habilita las opciones de movimiento del Jugador 1
    //Jugador 1
    gtk_widget_show_all(FNegra1.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(FNegra2.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(FNegra3.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra3.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra3.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra3.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(FNegra4.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra4.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra4.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra4.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(FNegra5.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra5.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra5.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra5.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(FNegra6.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra6.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra6.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra6.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(FNegra7.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra7.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra7.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra7.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(FNegra8.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra8.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra8.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra8.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(FNegra9.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra9.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra9.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra9.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(FNegra10.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra10.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra10.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra10.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(FNegra11.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra11.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra11.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra11.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(FNegra12.movimiento.OPmoverArriba);
    gtk_widget_show_all(FNegra12.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FNegra12.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FNegra12.movimiento.OPmoverIzquierda);

}

void habilitarOPmovimientosJ2(){ //Habilita las opciones de movimiento del Jugador 1

    //Jugador 2

    gtk_widget_show_all(FBlanca1.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca1.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca1.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca1.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(FBlanca2.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca2.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca2.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca2.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(FBlanca3.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca3.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca3.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca3.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(FBlanca4.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca4.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca4.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca4.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(FBlanca5.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca5.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca5.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca5.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(FBlanca6.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca6.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca6.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca6.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(FBlanca7.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca7.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca7.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca7.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(FBlanca8.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca8.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca8.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca8.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(FBlanca9.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca9.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca9.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca9.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(FBlanca10.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca10.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca10.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca10.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(FBlanca11.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca11.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca11.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca11.movimiento.OPmoverIzquierda);

    gtk_widget_show_all(FBlanca12.movimiento.OPmoverArriba);
    gtk_widget_show_all(FBlanca12.movimiento.OPmoverAbajo);
    gtk_widget_show_all(FBlanca12.movimiento.OPmoverDerecha);
    gtk_widget_show_all(FBlanca12.movimiento.OPmoverIzquierda);

}
