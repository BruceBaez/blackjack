#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {                //Struct en el codigo original
    char nombre[50];            
    int puntaje;
} EntradaRanking;
EntradaRanking rankingJugador;

//muestra carta especial estando en modo avanzado, las muestra como numero
int mostrarCartaEspecial(int carta1,int carta2,int carta3, int cantidadCartas, int oculta){
    switch (cantidadCartas)
    {
    case 1:
        printf(" _______\n");
        printf("|       | \n");
        printf("|  S P  | \n");
        if (oculta==0)
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
        printf("|  S P  ||  S P  | \n");
        if (oculta==0)
        {
            printf("|   %d   ||   %d   | \n",carta1,carta2);
        }else
        {
            printf("|   *   ||   *   | \n");
        }
        printf("|       ||       | \n");
        printf("|_______||_______| \n");    
        break;
    case 3:
        printf(" _______  _______  _______\n");
        printf("|       ||       ||       | \n");
        printf("|  S P  ||  S P  ||  S P  | \n");
        if (oculta==0)
        {
            printf("|   %d   ||   %d   ||   %d   | \n",carta1,carta2,carta3);
        }else
        {
            printf("|   *   ||   *   ||   *   | \n",carta2,carta3);
        }
        printf("|       ||       ||       | \n");
        printf("|_______||_______||_______| \n");    
        break;       
    }
    return 0;

}
//mostrar puntajes
int leaderboard(FILE *puntajes){
    char top10[10];
    puntajes = fopen("leaderboards.in","a+");

    for (int i = 0; i < 10; i++)
    {
        top10[i]=fscanf(puntajes,"%s\t%d");//nombre partidas_ganadas
    }
    printf("#TOP PUNTUACIONES#\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",top10[0],top10[1],top10[2],top10[3],top10[4],top10[5],top10[6],top10[7],top10[8],top10[9]);
    fclose(puntajes);
    return 0;
}
//añadir puntaje al leaderboard y reordenarlo si es necesario
int addToLeaderboards(FILE *puntajes,char player){
    puntajes = fopen("leaderboards.in","r");
    char nombres[1000];
    int puntos[1000];
    char nombre1,nombre2;
    int punto1,punto2;
    do
    {
        
        if (fscanf(puntajes,"%s")==player)
        {
            for (int i = 0; i < 999; i++)
            {
                if (!feof(puntajes))
                {
                    /* code */
                }
                
                nombre1=fscanf(puntajes,"%s");
                punto1=(int*)fscanf(puntajes,"%d\n");
                nombre2=fscanf(puntajes,"%s");
                punto2=(int*)fscanf(puntajes,"%d\n");
                /*mientras se copian los datos, se revisa 
                si esta el nombre del jugador para actualizarlo, 
                ademas de subirlo de posicion si con la partida ganada 
                tiene mejor puntuacion que el jugador por encima en la tabla*/
                if (nombre1==player)
                {
                    punto1++;
                    nombres[i]=nombre1;
                    puntos[i]=punto1;                    
                                   
                }else if (nombre2==player)
                {
                    punto2++;
                    if (punto1>punto2)
                    {
                        nombres[i]=nombre1;
                        puntos[i]=punto1;
                    }else
                    {
                        nombres[i]=nombre2;
                        puntos[i]=punto2;
                        nombres[i+1]=nombre1;
                        puntos[i+1]=punto1;
                    }                    

                }else{
                    nombres[i]=nombre1;
                    puntos[i]=punto1;                    
                }
                
                
                
            }
        }
        for (int i = 0; i < 1000; i++)
        {
            if(!feof(puntajes)){
                nombres[i]=fscanf(puntajes,"%s");
                puntos[i]=fscanf(puntajes,"%d\n");
            }
            nombres[i]=player;
            puntos[i]=1;
        }

        
    } while (!feof(puntajes));
    fclose(puntajes);
    puntajes = fopen("leaderboards.in","w");
        for (int i = 0; i < 1000; i++)
        {
            fprintf(puntajes,"%s\t%d\n",nombres[i],puntos[i]);
        }
    fclose(puntajes);
    return 0;

}