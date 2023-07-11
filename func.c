#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//para mostrar la carta(una a la vez)
int mostrarCarta(int numeroCarta){
    printf(" _______\n");
    printf("|       | \n");
    printf("|       | \n");
    printf("|   %d   | \n",numeroCarta);
    printf("|       | \n");
    printf("|_______| \n");
    return 0;
    
}



/*para meter acciones al log formato AAAAMMDD_HHMM\t acción realizada
identificamos la accion con el numero accion
0 inicio general programa, 1 seleccion modo juego, 2 seleccion dificultad,
3 seleccion modo 1 jugador o 0 jugadores, 4 Inicio ronda X,
5 reparticion cartas a J1 total x y jugador 2 total y,
6 jugador pide carta y sale X sumando Y en total,
7 jugador se planta con Y puntos, 8 jugador se paso, 9 jugador gana ronda,
10 recuento vidas jugadores, 11 indico fin de ronda y ganador
*añadir mas casos si se requiere*
*/
int log(FILE *log,time_t inicioMovimiento, int accion, int numeroCarta, int numero1,int numero2){
    FILE *log = fopen("log.h","a");//*HACER ESTO AL INICIO DEL PROGRAMA* abrimos el archivo del log para añadir el movimiento hecho al log(modo append)
    //FILE *log
    //log = fopen("log.h","a"); dejar esta linea en esta funcion
    time_t hora = time(NULL);
    //tiempo total del movimiento
    double tiempoAccion = difftime(inicioMovimiento,hora);//tiempo que tarda el movimiento, (PARA CADA LLAMADA,ANTEPONER A ESTA FUNCION UN time_t inicioMovimiento = time(NULL))
    struct tm *horaLocal = localtime(&hora);
    char salida[64];
    strftime(salida,64,"%Y%m%d_%H:%M",horaLocal);//info guardada en el string salida
    //con un switch case caigo en todos los casos, 
    //dependiendo del caso solicito la informacion necesaria y guardo en el archivo
    //usando fprintf
    switch (accion)
    {
    case 0:
        char mensaje[256] = "Inicio programa\n";
        fprintf(log,"%s\t%s",salida,mensaje);//REVISAR, no estoy seguro de que así se guarde bien la linea.
        break;
    
    default:
        break;
    }
    fclose(log);//cerrar el archivo
    return 0;
}


int main(){
    return 0;

}