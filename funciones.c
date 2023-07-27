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
        if (esBot==0)
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
        if (esBot==0)
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
        if (esBot==0)
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
        if (esBot==0)
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
        if (esBot==0)
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
int log_partida(FILE *log,time_t inicioMovimiento, int accion, int numeroCarta, int numero1,int numero2,int numero3){
    log = fopen("log.h","a");
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
        //inicio general programa
        fprintf(log,"%s\tInicio programa\n",salida);
        break;
    case 1:
        //seleccion modo juego
        if (numero1==1)//si se eligio modo basico
        {
            fprintf(log,"%s\tSe inicia el modo basico\n",salida);   
        }else//modo avanzado
        {
            fprintf(log,"%s\tSe inicia el modo avanzado\n",salida);
        }
        break;
    
    case 2:
        //seleccion dificultad
        if (numero1==1)//si se eligio bot basico
        {
            fprintf(log,"%s\tV/S bot basico\n",salida);   
        }else//bot avanzado
        {
            fprintf(log,"%s\tV/S bot avanzado\n",salida);
        }
        
        break;
    
    case 3:
        //seleccion modo 1 jugador o 0 jugadores
        if (numero1==1)//si se eligio modo 1 jugador
        {
            fprintf(log,"%s\tmodo 1 jugador\n",salida);
            
        }else if(numero1==2)//automatico reemplazado por bot basico
        {
            fprintf(log,"%s\tsimulacion con bot basico\n",salida);

        }
        
        else//automatico reemplazado por bot avanzado
        {
            fprintf(log,"%s\tsimulacion con bot avanzado\n",salida);

        }

        break;
    
    case 4:
        //Inicio ronda X
        fprintf(log,"%s\tInicio ronda %d\n",salida,numero1);//numero1 = numero de ronda
        break;
    
    case 5:
        //reparte cartas jugador 1 total num1 y jugador 2 total num2

        fprintf(log,"%s\trepartimos cartas: J1 = %d\tJ2 = %d\n",salida,numero1,numero2);//num1=total cartas j1, num2=total cartas j2
        break;

    case 6:
        // jugador pide carta y sale num2 sumando num3 en total,
        switch (numero1)//numero 1 determina si es jugador(0)Bot basico(1)o avanzado(2)
        {
        case 0:
            fprintf(log,"%s\tJugador pide carta,saca %d, total%d\n",salida,numero2,numero3);
            break;
        case 1:
            fprintf(log,"%s\tBot basico pide carta,saca %d, total%d\n",salida,numero2,numero3);
            break;
        default:
            fprintf(log,"%s\tBot avanzado pide carta,saca %d, total%d\n",salida,numero2,numero3);
            break;
        }
        
        break;
    
    case 7:
        // jugador se planta con Y puntos
        fprintf(log,"%s\tse planta con %d\n",salida,numero1);
        break;
    
    case 8:
        //jugador se paso
        fprintf(log,"%s\tsumó mas de %d, se pasó\n",salida,numero1);//num1=limite de ronda
        break;
    
    case 9:
        //jugador gana ronda
        if (numero1)//num1 si es 1, el jugador(no crupier) ganó, caso contrario, perdió
        {
            fprintf(log,"%s\tJugador gana!\n",salida);
        }else
        {
            fprintf(log,"%s\tJugador pierde!\n",salida);
        }

        break;
    
    case 10:
        //recuento vidas jugadores
        fprintf(log,"%s\tvidas crupier = %d\tvidas jugador = %d\n",salida,numero1,numero2);//num1=vidas rival(bot basico o avanzado)num2= pj(jugador, bot basico o bot avanzado)
        break;
    
    case 11:
        //indico fin de partida y ganador
        if (numero1==1)//num1: 1 si gano el jugador,0 si gano el crupier
        {
            fprintf(log,"%s\tFin del juego. jugador gana",salida);
        }else
        {
            fprintf(log,"%s\tFin del juego. crupier gana",salida);
        }
        
        
        break;
    
    case 12:
        //seleccion opcion salir en menu principal
        fprintf(log,"%s\tFin del programa",salida);
        break;
    
    
    default:
        break;
    }
    fclose(log);//cerrar el archivo
    return 0;
}


int main(){
    FILE *log = fopen("log.h","a");
    return 0;

}