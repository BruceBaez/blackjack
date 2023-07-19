#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//para mostrar la mano normal(segun cantidad de cartas y que cartas posee, si es crupier o bot, no se muestra la primera)
int mostrarCarta(int carta1,int carta2,int carta3,int carta4,int carta5, int cantidadCartas, int esBot){
    switch (cantidadCartas)
    {
    case 1:
        printf(" _______\n");
        printf("|       | \n");
        printf("|       | \n");
        if (!esBot)
        {
            printf("|   %d   | \n",carta1);
        }else
        {
            printf("|   *   | \n");
        }
        printf("|       | \n");
        printf("|_______| \n");    
        break;
    case 2:
        printf(" _______  _______\n");
        printf("|       ||       | \n");
        printf("|       ||       | \n");
        if (!esBot)
        {
            printf("|   %d   ||   %d   | \n",carta1,carta2);
        }else
        {
            printf("|   *   ||   %d   | \n",carta2);
        }
        printf("|       ||       | \n");
        printf("|_______||_______| \n");    
        break;
    case 3:
        printf(" _______  _______  _______\n");
        printf("|       ||       ||       | \n");
        printf("|       ||       ||       | \n");
        if (!esBot)
        {
            printf("|   %d   ||   %d   ||   %d   | \n",carta1,carta2,carta3);
        }else
        {
            printf("|   *   ||   %d   ||   %d   | \n",carta2,carta3);
        }
        printf("|       ||       ||       | \n");
        printf("|_______||_______||_______| \n");    
        break;
    case 4:
        printf(" _______  _______  _______  _______\n");
        printf("|       ||       ||       ||       | \n");
        printf("|       ||       ||       ||       | \n");
        if (!esBot)
        {
            printf("|   %d   ||   %d   ||   %d   ||   %d   | \n",carta1,carta2,carta3,carta4);
        }else
        {
            printf("|   *   ||   %d   ||   %d   ||   %d   | \n",carta2,carta3,carta4);
        }
        printf("|       ||       ||       ||       | \n");
        printf("|_______||_______||_______||_______| \n");    
        break;
    case 5:
        printf(" _______  _______  _______  _______  _______\n");
        printf("|       ||       ||       ||       ||       | \n");
        printf("|       ||       ||       ||       ||       |\n");
        if (!esBot)
        {
            printf("|   %d   ||   %d   ||   %d   ||   %d   ||   %d   | \n",carta1,carta2,carta3,carta4,carta5);
        }else
        {
            printf("|   *   ||   %d   ||   %d   ||   %d   ||   %d   | \n",carta2,carta3,carta4,carta5);
        }
        printf("|       ||       ||       ||       ||       | \n");
        printf("|_______||_______||_______||_______||_______| \n");    
        break;        
    }
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
12 seleccion opcion salir en menu principal
*añadir mas casos si se requiere*
*/
int log(FILE *log,time_t inicioMovimiento, int accion, int numeroCarta, int numero1,int numero2,int numero3,int numero4){
    FILE *log = fopen("log.h","a");//*HACER ESTO AL INICIO DEL PROGRAMA* abrimos el archivo del log para añadir el movimiento hecho al log(modo append)
    //FILE *log  1
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
        fprintf(log,"%s\t%s",salida,mensaje);
        break;
    case 1:
        if (numero1==1)//si se eligio modo basico
        {
            char mensaje[256] = "Se inicia el modo basico\n";    
        }else//modo avanzado
        {
            char mensaje[256] = "Se inicia el modo avanzado\n";
        }
        fprintf(log,"%s\t%s",salida,mensaje);
        break;
    
    case 2:
        if (numero1==1)//si se eligio bot basico
        {
            char mensaje[256] = "V/S bot basico\n";    
        }else//bot avanzado
        {
            char mensaje[256] = "V/S bot avanzado\n";
        }
        fprintf(log,"%s\t%s",salida,mensaje);
        break;
    
    case 3:
        if (numero1==1)//si se eligio modo 1 jugador
        {
            char mensaje[256] = "modo 1 jugador\n";
            
        }else if(numero1==2)//automatico reemplazado por bot basico
        {
            char mensaje[256] = "simulacion con bot basico\n";
        }
        
        else//automatico reemplazado por bot avanzado
        {
            char mensaje[256] = "simulacion con bot avanzado\n";
        }
        fprintf(log,"%s\t%s",salida,mensaje);
        break;
    
    case 4:
        char mensaje[256] = "Inicio ronda\n";
        fprintf(log,"%s\t%s %d",salida,mensaje,numero1);//numero1 = numero de ronda
        break;
    
    case 5:
        char mensaje[256] = "Inicio programa\n";
        fprintf(log,"%s\t%s",salida,mensaje);
        break;

    case 6:
        char mensaje[256] = "Inicio programa\n";
        fprintf(log,"%s\t%s",salida,mensaje);
        break;
    
    case 7:
        char mensaje[256] = "Inicio programa\n";
        fprintf(log,"%s\t%s",salida,mensaje);
        break;
    
    case 8:
        char mensaje[256] = "Inicio programa\n";
        fprintf(log,"%s\t%s",salida,mensaje);
        break;
    case 9:
        char mensaje[256] = "Inicio programa\n";
        fprintf(log,"%s\t%s",salida,mensaje);
        break;
    case 10:
        char mensaje[256] = "Inicio programa\n";
        fprintf(log,"%s\t%s",salida,mensaje);
        break;
    case 11:
        char mensaje[256] = "Inicio programa\n";
        fprintf(log,"%s\t%s",salida,mensaje);
        break;
    case 12:
        char mensaje[256] = "Inicio programa\n";
        fprintf(log,"%s\t%s",salida,mensaje);
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