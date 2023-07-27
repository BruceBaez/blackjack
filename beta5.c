#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


typedef struct {                //Struct que contiene el nombre y el puntaje del jugador
    char nombre[50];            
    int puntaje;
} EntradaRanking;
EntradaRanking rankingJugador;
// Declaración del prototipo de la funcion buscarMejorJugada
int buscarMejorJugada(int puntuacionCrupier, int *cartasDisponibles, int numCartasDisponibles, int puntuacionJugador);

int generarAleatorio(int min, int max) {            //Funcion para numero aleatorio de la bibloteca stdlib.h     
    return min + rand() % (max - min + 1);
}

int valorCarta(int carta) {                         //Esta función recibe el numero de una carta y devuelve su valor en el juego
    if (carta >= 2 && carta <= 10)
        return carta;
    else if (carta >= 11 && carta <= 13)
        return 10;
    else
        return 1;
}
int obtenerCartaDelCrupier(int numCartasCrupier,int cartasCrupier[5]) {
    int indiceCartaCrupier = generarAleatorio(0, numCartasCrupier - 1);
    int nuevaCartaCrupier = cartasCrupier[indiceCartaCrupier];
    for (int i = indiceCartaCrupier; i < numCartasCrupier - 1; i++) {
        cartasCrupier[i] = cartasCrupier[i + 1];
    }
    numCartasCrupier--;

    return nuevaCartaCrupier;
}
// Función que realiza la busqueda en espacio de soluciones para que el crupier encuentre la mejor jugada
int buscarMejorJugadaCrupier(int puntuacionCrupier, int *cartasDisponibles, int numCartasDisponibles, int puntuacionJugador) {
    if (puntuacionCrupier > 21) {
        // Si la puntuacion del crupier supera 21, devuelve una puntuacion inválida
        return -1;
    }

    if (numCartasDisponibles == 0) {
        // Si no quedan cartas disponibles, devuelve la puntuacion actual del crupier
        return puntuacionCrupier;
    }

    int mejorPuntuacion = puntuacionCrupier;

    for (int i = 0; i < numCartasDisponibles; i++) {
        int nuevaPuntuacion = puntuacionCrupier + valorCarta(cartasDisponibles[i]);

        // Actualiza el mazo después de repartir la carta al crupier
        int cartasDisponiblesNueva[10];
        memcpy(cartasDisponiblesNueva, cartasDisponibles, sizeof(int) * numCartasDisponibles);
        for (int j = i; j < numCartasDisponibles - 1; j++) {
            cartasDisponiblesNueva[j] = cartasDisponiblesNueva[j + 1];
        }

        int nuevaNumCartasDisponibles = numCartasDisponibles - 1;

        // Realiza recursión para seguir buscando la mejor jugada
        int nuevaMejorPuntuacion = buscarMejorJugadaCrupier(nuevaPuntuacion, cartasDisponiblesNueva, nuevaNumCartasDisponibles, puntuacionJugador);

        // Si la nueva puntuación del crupier es inválida (superó 21) o es mayor que la mejor encontrada hasta ahora, actualiza la mejor puntuación
        if (nuevaMejorPuntuacion == -1 || nuevaMejorPuntuacion > mejorPuntuacion) {
            mejorPuntuacion = nuevaMejorPuntuacion;
        }
    }

    return mejorPuntuacion;
}

// Función para que el crupier juegue su mano utilizando la Búsqueda en Espacio de Soluciones
void jugarManoCrupier(int *puntuacionCrupier, int *cartasDisponibles, int *numCartasDisponibles, int puntuacionJugador) {
    // Realiza la búsqueda en espacio de soluciones para encontrar la mejor puntuación
    int mejorPuntuacion = buscarMejorJugadaCrupier(*puntuacionCrupier, cartasDisponibles, *numCartasDisponibles, puntuacionJugador);

    // El crupier toma cartas hasta alcanzar o superar la mejor puntuación encontrada
    while (*puntuacionCrupier < mejorPuntuacion && *puntuacionCrupier <= 21) {
        if (*numCartasDisponibles == 0) {
            printf("No quedan cartas disponibles para el crupier.\n");
            break;
        }

        int indiceCartaSeleccionada = generarAleatorio(0, *numCartasDisponibles - 1); // Carta para el crupier y actualiza el mazo
        int nuevaCartaCrupier = cartasDisponibles[indiceCartaSeleccionada];

        *puntuacionCrupier += valorCarta(nuevaCartaCrupier);
        printf("Crupier recibe carta: %d\n", nuevaCartaCrupier);

        // Actualiza el mazo después de repartir la carta al crupier
        for (int i = indiceCartaSeleccionada; i < *numCartasDisponibles - 1; i++) {
            cartasDisponibles[i] = cartasDisponibles[i + 1];
        }
        (*numCartasDisponibles)--;
    }
}
int jugarBlackjack(char* nombre) {      //Funcion que recibe el nombre del jugador y simula el modo basico
    int vidasJugador = 1;
    int vidasCrupier = 1;
    int ronda = 1;

    while (vidasJugador > 0 && vidasCrupier > 0) {  //imprime informacion de la ronda y estadisticas
        printf("Ronda: %d\n", ronda);
        printf("Vidas Jugador: %d\n", vidasJugador);
        printf("Vidas Crupier: %d\n", vidasCrupier);

        int cartasDisponibles[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};        //Crea arreglo de cartas disponibles y el numero disponible
        int numCartasDisponibles = 10;

        int cartaJugador;
        int puntuacionJugador = 0;
        int puntuacionCrupier = 0;

        int indiceCartaSeleccionada = generarAleatorio(0, numCartasDisponibles - 1); //Entrega carta aleatoriamente, usando la funcion generar aleatorio, a la vez actualiza las cartas disponibles en el mazo
        cartaJugador = cartasDisponibles[indiceCartaSeleccionada];
        for (int i = indiceCartaSeleccionada; i < numCartasDisponibles - 1; i++) {
            cartasDisponibles[i] = cartasDisponibles[i + 1];
        }
        numCartasDisponibles--;

        indiceCartaSeleccionada = generarAleatorio(0, numCartasDisponibles - 1); //Entrega carta al crupier aleatoriamente y vuelve a actualiazar el mazo
        int nuevaCartaCrupier = cartasDisponibles[indiceCartaSeleccionada];
        for (int i = indiceCartaSeleccionada; i < numCartasDisponibles - 1; i++) {
            cartasDisponibles[i] = cartasDisponibles[i + 1];
        }
        numCartasDisponibles--;

        puntuacionJugador = valorCarta(cartaJugador);                   //Puntaciones
        puntuacionCrupier = valorCarta(nuevaCartaCrupier);

        printf("Jugador: %d\n", puntuacionJugador);                     //Imprime las puntaciones
        printf("Crupier: %d\n", puntuacionCrupier);

        char opcion;
        printf("Deseas pedir una nueva carta? (s/n): ");                //pregunta si desea pedir carta o no
        scanf(" %c", &opcion);

        int numCartasJugador = 1;
        int salirRonda = 0;

        for (; opcion == 's' && puntuacionJugador < 21 && numCartasJugador < 5; numCartasJugador++) {   //Itera mientras el jugador quiera pedir una carta, no haya alcanzado 21
            if (numCartasDisponibles == 0) {
                printf("No quedan cartas disponibles.\n");
                break;
            }

            indiceCartaSeleccionada = generarAleatorio(0, numCartasDisponibles - 1);        //Selecciona una nueva carta y actualiza mazo
            int nuevaCarta = cartasDisponibles[indiceCartaSeleccionada];
            for (int i = indiceCartaSeleccionada; i < numCartasDisponibles - 1; i++) {
                cartasDisponibles[i] = cartasDisponibles[i + 1];
            }
            numCartasDisponibles--;

            puntuacionJugador += valorCarta(nuevaCarta);        //Actualiza puntajes
            printf("Carta recibida: %d\n", nuevaCarta);
            printf("Puntuacion actual: %d\n", puntuacionJugador);

            if (puntuacionJugador >= 21) {
                salirRonda = 1;
                break;
            }

            if (numCartasJugador < 4) {
                printf("Deseas pedir otra carta? (s/n): "); //pregunta si desea seguir pidiendo cartas
                scanf(" %c", &opcion);
            }
        }

        if (!salirRonda) { 
            for (; puntuacionCrupier < 16 && puntuacionJugador <= 21; puntuacionCrupier += valorCarta(nuevaCartaCrupier)) { //El crupier pide hasta que su puntacion sea mayor o igual a 16 o hasta que el jugador supere los 21
                if (numCartasDisponibles == 0) {
                    printf("No quedan cartas disponibles.\n");
                    break;
                }

                indiceCartaSeleccionada = generarAleatorio(0, numCartasDisponibles - 1); //Carta para el crupier y actualiza mazo
                nuevaCartaCrupier = cartasDisponibles[indiceCartaSeleccionada];
                for (int i = indiceCartaSeleccionada; i < numCartasDisponibles - 1; i++) {
                    cartasDisponibles[i] = cartasDisponibles[i + 1];
                }
                numCartasDisponibles--;
            }
        }

        printf("Puntuacion final:\n");      //imprime puntuaciones finales del jugador y el crupier
        printf("Jugador: %d\n", puntuacionJugador);
        printf("Crupier: %d\n", puntuacionCrupier);

        if (puntuacionJugador > 21) {       //determina el resultado de la ronda y actualiza las vidas del jugador y el crupier
            vidasJugador--;
            printf("Te has pasado de 21. Vidas restantes Jugador: %d\n", vidasJugador);
        } else if (puntuacionCrupier > 21) {
            vidasCrupier--;
            printf("Jugador gana! El crupier se ha pasado de 21. Vidas restantes Crupier: %d\n", vidasCrupier);
        } else if (puntuacionJugador == puntuacionCrupier) {
            printf("Empate!\n");
        } else if (puntuacionJugador > puntuacionCrupier) {
            printf("Jugador gana!\n");
            vidasCrupier--;
        } else {
            printf("Crupier gana!\n");
            vidasJugador--;
            printf("Vidas restantes Jugador: %d\n", vidasJugador);
        }

        ronda++;
        //espera a que el jugador presione enter para continuar
        printf("Presiona enter para continuar...\n");
        while (getchar() != '\n');
        getchar();
    }

    if (vidasJugador == 0) { //Verifica el resultado final y actualiza los puntajes
        printf("Te has quedado sin vidas. Fin del juego.\n");
        return 0;
    } else {
        printf("El crupier se ha quedado sin vidas. ¡Felicidades! Has ganado.\n");
        rankingJugador.puntaje++;
        return 1;
    }
}   
int jugarSimulacionBlackjack() {   //esta funcion es similar a jugarblackjack, solo que aqui las decisiones del jugador se hacen de forma automatica.
    int vidasJugador = 7;
    int vidasCrupier = 7;
    int ronda = 1;

    while (vidasJugador > 0 && vidasCrupier > 0) {
        printf("Ronda: %d\n", ronda);
        printf("Vidas Jugador: %d\n", vidasJugador);
        printf("Vidas Crupier: %d\n", vidasCrupier);

        int cartasDisponibles[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int numCartasDisponibles = 10;

        int cartaJugador;
        int puntuacionJugador = 0;
        int puntuacionCrupier = 0;

        int indiceCartaSeleccionada = generarAleatorio(0, numCartasDisponibles - 1);
        cartaJugador = cartasDisponibles[indiceCartaSeleccionada];
        for (int i = indiceCartaSeleccionada; i < numCartasDisponibles - 1; i++) {
            cartasDisponibles[i] = cartasDisponibles[i + 1];
        }
        numCartasDisponibles--;

        int nuevaCartaCrupier;
        int indiceCartaCrupier = generarAleatorio(0, numCartasDisponibles - 1);
        nuevaCartaCrupier = cartasDisponibles[indiceCartaCrupier];
        for (int i = indiceCartaCrupier; i < numCartasDisponibles - 1; i++) {
            cartasDisponibles[i] = cartasDisponibles[i + 1];
        }
        numCartasDisponibles--;

        puntuacionJugador = valorCarta(cartaJugador);
        puntuacionCrupier = valorCarta(nuevaCartaCrupier);

        printf("Jugador: %d\n", puntuacionJugador);
        printf("Crupier: %d\n", puntuacionCrupier);

        char opcion;                                                           //aqui es donde se modifica el codigo, donde simplemente el bot saca carta dependiendo si su puntacion es menor o no a 16
        if (puntuacionJugador < 16) {
            opcion = 's';
        } else {
            opcion = 'n';
        }

        int numCartasJugador = 1;
        int salirRonda = 0;

        for (; opcion == 's' && puntuacionJugador < 21 && numCartasJugador < 5; numCartasJugador++) {
            if (numCartasDisponibles == 0) {
                printf("No quedan cartas disponibles.\n");
                break;
            }

            indiceCartaSeleccionada = generarAleatorio(0, numCartasDisponibles - 1);
            int nuevaCarta = cartasDisponibles[indiceCartaSeleccionada];
            for (int i = indiceCartaSeleccionada; i < numCartasDisponibles - 1; i++) {
                cartasDisponibles[i] = cartasDisponibles[i + 1];
            }
            numCartasDisponibles--;

            puntuacionJugador += valorCarta(nuevaCarta);
            printf("Carta recibida: %d\n", nuevaCarta);
            printf("Puntuacion actual: %d\n", puntuacionJugador);

            if (puntuacionJugador >= 21) {
                salirRonda = 1;
                break;
            }

            if (numCartasJugador < 4) {
                if (puntuacionJugador < 16) {  // El bot decide si pedir otra carta o no
                    opcion = 's';
                } else {
                    opcion = 'n';
                }
            }
        }

        if (!salirRonda) { 
                // El crupier juega su mano utilizando la Búsqueda en Espacio de Soluciones
                printf("Turno del Crupier:\n");
                int mejorPuntuacionCrupier = buscarMejorJugadaCrupier(puntuacionCrupier, cartasDisponibles, numCartasDisponibles, puntuacionJugador);
                while (puntuacionCrupier < mejorPuntuacionCrupier && puntuacionCrupier <= 21) {
                    if (numCartasDisponibles == 0) {
                        printf("No quedan cartas disponibles para el crupier.\n");
                        break;
                    }

                    int indiceCartaSeleccionada = generarAleatorio(0, numCartasDisponibles - 1); // Carta para el crupier y actualiza el mazo
                    int nuevaCartaCrupier = cartasDisponibles[indiceCartaSeleccionada];

                    puntuacionCrupier += valorCarta(nuevaCartaCrupier);
                    printf("Crupier recibe carta: %d\n", nuevaCartaCrupier);

                    // Actualiza el mazo después de repartir la carta al crupier
                    for (int i = indiceCartaSeleccionada; i < numCartasDisponibles - 1; i++) {
                        cartasDisponibles[i] = cartasDisponibles[i + 1];
                    }
                    numCartasDisponibles--;
                }
            }

        printf("Puntuacion final:\n");
        printf("Jugador: %d\n", puntuacionJugador);
        printf("Crupier: %d\n", puntuacionCrupier);

        if (puntuacionJugador > 21) {
            vidasJugador--;
            printf("Te has pasado de 21. Vidas restantes Jugador: %d\n", vidasJugador);
        } else if (puntuacionCrupier > 21) {
            vidasCrupier--;
            printf("Jugador gana! El crupier se ha pasado de 21. Vidas restantes Crupier: %d\n", vidasCrupier);
        } else if (puntuacionJugador == puntuacionCrupier) {
            printf("Empate!\n");
        } else if (puntuacionJugador > puntuacionCrupier) {
            printf("Jugador gana!\n");
            vidasCrupier--;
        } else {
            printf("Crupier gana!\n");
            vidasJugador--;
            printf("Vidas restantes Jugador: %d\n", vidasJugador);
        }

        ronda++;
        printf("Presiona enter para continuar...\n");
        while (getchar() != '\n');
        getchar();
    }

    if (vidasJugador == 0) {
        printf("Te has quedado sin vidas. Fin del juego.\n");
        return 0;
    } else {
        printf("El crupier se ha quedado sin vidas. ¡Felicidades! Has ganado.\n");
  
        return 1;
    }
}

int jugarBlackjackAvanzado(char* nombre) {      //Funcion que recibe el nombre del jugador y simula el modo avanzado
    int vidasJugador = 1;
    int vidasCrupier = 1;
    int ronda = 1;
    int contadorRondas=0;
    int objetivoJuego=21;
    int cartaDevueltaMazo=0;
    int ultimaCartaCrupier=0;
    int activarCartaEspecial21=0;
    int proteccionJugador =0;
    int proteccionCrupier=0;
    int apuesta=0;
    int cartasJugador[5];
    int cartasCrupier[5];
    int numCartasJugador = 0;
    int numCartasCrupier=0;

    while (vidasJugador > 0 && vidasCrupier > 0) {  //imprime informacion de la ronda y estadisticas
        printf("Ronda: %d\n", ronda);
        printf("Vidas Jugador: %d\n", vidasJugador);
        printf("Vidas Crupier: %d\n", vidasCrupier);
        int nuevaCartaEspecial = 0;
        int valorCartaEspecial;
        int cartaEspecialDisponible;
        int indiceCartaEspecial; 


        int cartasDisponibles[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};        //Crea arreglo de cartas disponibles y el numero disponible
        int numCartasDisponibles = 10;
        int cartasEspeciales[25]={11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35};
        int numCartasEspeciales=25;
        
        int cartaJugador;
        int puntuacionJugador = 0;
        int puntuacionCrupier = 0;

        int indiceCartaSeleccionada = generarAleatorio(0, numCartasDisponibles - 1); //Entrega carta aleatoriamente, usando la funcion generar aleatorio, a la vez actualiza las cartas disponibles en el mazo
        cartaJugador = cartasDisponibles[indiceCartaSeleccionada];
        for (int i = indiceCartaSeleccionada; i < numCartasDisponibles - 1; i++) {
            cartasDisponibles[i] = cartasDisponibles[i + 1];
        }
        numCartasDisponibles--;
        cartasJugador[numCartasJugador] = cartaJugador;
        numCartasJugador++;
        indiceCartaSeleccionada = generarAleatorio(0, numCartasDisponibles - 1); //Entrega carta al crupier aleatoriamente y vuelve a actualiazar el mazo
        int nuevaCartaCrupier = cartasDisponibles[indiceCartaSeleccionada];
        for (int i = indiceCartaSeleccionada; i < numCartasDisponibles - 1; i++) {
            cartasDisponibles[i] = cartasDisponibles[i + 1];
        }
        numCartasDisponibles--;
        cartasCrupier[numCartasCrupier]=nuevaCartaCrupier;
        numCartasCrupier++;
        puntuacionJugador = valorCarta(cartaJugador);                   //Puntaciones
        puntuacionCrupier = valorCarta(nuevaCartaCrupier);

        printf("Jugador: %d\n", puntuacionJugador);                     //Imprime las puntaciones
        printf("Crupier: %d\n", puntuacionCrupier);

        char opcion;
        printf("Deseas pedir una nueva carta? (s/n): ");                //pregunta si desea pedir carta o no
        scanf(" %c", &opcion);

        int numCartasJugador = 1;
        int salirRonda = 0;
        for (; opcion == 's' && puntuacionJugador < objetivoJuego && numCartasJugador < 5; numCartasJugador++) {   //Itera mientras el jugador quiera pedir una carta, no haya alcanzado 21
            if (numCartasDisponibles == 0) {
                printf("No quedan cartas disponibles.\n");
                break;
            }

            indiceCartaSeleccionada = generarAleatorio(0, numCartasDisponibles - 1);        //Selecciona una nueva carta y actualiza mazo
            int nuevaCarta = cartasDisponibles[indiceCartaSeleccionada];
            for (int i = indiceCartaSeleccionada; i < numCartasDisponibles - 1; i++) {
                cartasDisponibles[i] = cartasDisponibles[i + 1];
            }
            numCartasDisponibles--;
            cartasJugador[numCartasJugador]=nuevaCarta;
            numCartasJugador++;

            puntuacionJugador += valorCarta(nuevaCarta);        //Actualiza puntajes
            printf("Carta recibida: %d\n", nuevaCarta);
            printf("Puntuacion actual: %d\n", puntuacionJugador);

            if (puntuacionJugador >= objetivoJuego) {
                salirRonda = 1;
                break;
            }
            if (numCartasJugador == 3 && numCartasEspeciales > 0) {
                printf("¡Carta especial entregada!\n");
                int indiceCartaEspecial = generarAleatorio(0, numCartasEspeciales - 1);
                nuevaCartaEspecial = cartasEspeciales[indiceCartaEspecial];
                for (int i = indiceCartaEspecial; i < numCartasEspeciales - 1; i++) {
                    cartasEspeciales[i] = cartasEspeciales[i + 1];
                }
            
                numCartasEspeciales--;
                printf("Carta especial recibida: %d\n", nuevaCartaEspecial);
            }
        }
        
        printf("Deseas usar esta carta especial? %d (s/n): ",nuevaCartaEspecial);
        scanf(" %c", &opcion);
        
        if (opcion == 's') {
            if (nuevaCartaEspecial >= 1 && nuevaCartaEspecial <= 10) {
                valorCartaEspecial = nuevaCartaEspecial;
                cartaEspecialDisponible = 0;
                indiceCartaEspecial = -1;
            
                for (int i = 0; i < numCartasDisponibles; i++) {
                    if (cartasDisponibles[i] == valorCartaEspecial) {
                        cartaEspecialDisponible = valorCartaEspecial;
                        indiceCartaEspecial = i;
                        break;
                    }
                }
            }    
            if (cartaEspecialDisponible == valorCartaEspecial) {
                puntuacionJugador += valorCartaEspecial;
                printf("¡Has obtenido la carta de valor %d del mazo original!\n", valorCartaEspecial);
            
                // Remover la carta especial obtenida del mazo original
                for (int i = indiceCartaEspecial; i < numCartasDisponibles - 1; i++) {
                    cartasDisponibles[i] = cartasDisponibles[i + 1];
                }
                numCartasDisponibles--;
            } else {
                printf("La carta de valor %d no está disponible en el mazo original.\n", valorCartaEspecial);
            }

        }else if (nuevaCartaEspecial==11){
            printf("¡La carta especial cambia el objetivo del juego a 17 para esta ronda!\n");
            objetivoJuego = 17;
        }else if (nuevaCartaEspecial==12){
            printf("¡La carta especial cambia el objetivo del juego a 24 para esta ronda!\n");
            objetivoJuego=24;
        }else if (nuevaCartaEspecial==13){
            printf("¡La carta especial te otorga 1 vida adicional!\n");
            vidasJugador++;
        }else if (nuevaCartaEspecial==14){
            printf("¡La carta especial le quita 1 al crupier!\n");
            vidasCrupier--;
        }else if (nuevaCartaEspecial==15){
            printf("¡La carta especial te permite obtener una de las cartas del crupier!\n");
            int nuevaCartaCrupier = obtenerCartaDelCrupier(numCartasCrupier,cartasCrupier);         
            puntuacionJugador += valorCarta(nuevaCartaCrupier);                            
            printf("Has obtenido una carta del crupier: %d\n", nuevaCartaCrupier);
            printf("Tu puntuación actual: %d\n", puntuacionJugador);
        }else if (nuevaCartaEspecial==16){
            printf("¡La carta especial te quita 1 vida adicional!\n");
            vidasJugador--;
        }else if (nuevaCartaEspecial==17){
            printf("¡La carta especial devuelve la última carta obtenida al mazo original!\n");
            if (numCartasDisponibles < 10) {
                cartaDevueltaMazo = cartaJugador; 
                cartasDisponibles[numCartasDisponibles] = cartaDevueltaMazo; 
                numCartasDisponibles++; 
                printf("La carta %d ha sido devuelta al mazo original.\n", cartaDevueltaMazo);
            } else {
                printf("No es posible devolver una carta al mazo original en este momento.\n");
            }
        }else if (nuevaCartaEspecial==18){
            printf("¡La carta especial obliga al crupier a mostrar su última carta!\n");
            printf("La última carta obtenida por el crupier fue: %d\n", ultimaCartaCrupier);
        }else if(nuevaCartaEspecial==19){
            printf("¡La carta especial revela la última carta del crupier y del jugador!\n");
            printf("Última carta del crupier: %d\n", ultimaCartaCrupier);
            printf("Última carta del jugador: %d\n", cartaJugador);
        }else if (nuevaCartaEspecial==20){
            printf("¡La carta especial revela todas las cartas obtenidas!\n");
            printf("Cartas obtenidas del jugador:\n");
            for (int i = 0; i < numCartasJugador; i++) {
                printf("%d ", cartasJugador[i]);
            }
            printf("\n");
            printf("Cartas obtenidas del crupier:\n");
            for (int i = 0; i < numCartasCrupier; i++) {
                printf("%d ", cartasCrupier[i]);
            }
            printf("\n");
            printf("Carta especial obtenida: %d\n", nuevaCartaEspecial);
        }else if (nuevaCartaEspecial==21){
            printf("¡Se ha activado la carta especial 21 se ha reiniciado la ronda!\n");
            activarCartaEspecial21 = 1;
        }else if (nuevaCartaEspecial==22){
            printf("¡Has obtenido la carta especial 22! Estás protegido de perder una vida en caso de perder la ronda.\n");
            proteccionJugador =1;
        }else if (nuevaCartaEspecial==23){
            printf("¡Has obtenido la carta especial 23! En esta ronda, el crupier y el jugador apuestan una vida extra.\n");
            apuesta=1;
        }else if (nuevaCartaEspecial==24){
            printf("Esta carta especial no hace nada");
        }else if (nuevaCartaEspecial==25){
            printf("¡Has obtenido la carta especial 25 FalsoTortazo! Los HP del Pokemon enemigo se redujeron a 1.\n");
            vidasCrupier = 1;
        }else{
            printf("la carta especial no existe");
        }

        printf("Puntuacion actual: %d\n", puntuacionJugador);
        if (numCartasJugador < 4) {
            printf("Deseas pedir otra carta? (s/n): "); //pregunta si desea seguir pidiendo cartas
            scanf(" %c", &opcion);
        }
        if (!salirRonda) { 
            for (; puntuacionCrupier < 16 && puntuacionJugador <= objetivoJuego; puntuacionCrupier += valorCarta(nuevaCartaCrupier)) { //El crupier pide hasta que su puntacion sea mayor o igual a 16 o hasta que el jugador supere los 21
                if (numCartasDisponibles == 0) {
                    printf("No quedan cartas disponibles.\n");
                    break;
                }

                indiceCartaSeleccionada = generarAleatorio(0, numCartasDisponibles - 1); //Carta para el crupier y actualiza mazo
                nuevaCartaCrupier = cartasDisponibles[indiceCartaSeleccionada];
                ultimaCartaCrupier=nuevaCartaCrupier;
                for (int i = indiceCartaSeleccionada; i < numCartasDisponibles - 1; i++) {
                    cartasDisponibles[i] = cartasDisponibles[i + 1];
                }
                numCartasDisponibles--;
            }
        }

        printf("Puntuacion final:\n");      //imprime puntuaciones finales del jugador y el crupier
        printf("Jugador: %d\n", puntuacionJugador);
        printf("Crupier: %d\n", puntuacionCrupier);

        if (puntuacionJugador > objetivoJuego) {       //determina el resultado de la ronda y actualiza las vidas del jugador y el crupier
            if(!proteccionJugador){
                vidasJugador--;
            }
            printf("Te has pasado de 21. Vidas restantes Jugador: %d\n", vidasJugador);
        }
        if (puntuacionCrupier > objetivoJuego) {
            if (!proteccionCrupier){
                vidasCrupier--;
            }
            printf("Jugador gana! El crupier se ha pasado de 21. Vidas restantes Crupier: %d\n", vidasCrupier);
        } else if (puntuacionJugador == puntuacionCrupier) {
            printf("Empate!\n");
        } else if (puntuacionJugador > puntuacionCrupier) {
            if (!proteccionCrupier){
                printf("Jugador gana!\n");
            }
            vidasCrupier--;
        } else {
            if(!proteccionJugador){
                printf("Crupier gana!\n");
            }
            vidasJugador-=apuesta;
            printf("Vidas restantes Jugador: %d\n", vidasJugador);
        }
        ronda++;
        contadorRondas++;
        //espera a que el jugador presione enter para continuar
        printf("Presiona enter para continuar...\n");
        while (getchar() != '\n');
        getchar();
    }
        if (activarCartaEspecial21) {
            printf("Se ha reiniciado la ronda.\n");
            ronda = 1;
            contadorRondas = 0;
            objetivoJuego = 21;
            activarCartaEspecial21 = 0;  // Reiniciar la activación de la carta especial 21
        }

        if (vidasJugador == 0) { //Verifica el resultado final y actualiza los puntajes
            printf("Te has quedado sin vidas. Fin del juego.\n");
            return 0;
        } else {
            printf("El crupier se ha quedado sin vidas. ¡Felicidades! Has ganado.\n");
            rankingJugador.puntaje++;
            return 1;
        }

    
}


int main() {                //Main y menu del programa, se usa un switch-case anidados para crearlo
    int a = 0;
    //int resultado = 0;

    printf(" _____ __    _____ _____ _____       __ _____ _____ _____    _____ _____ _____ _____ _____ _____ _____\n");
    printf("| __  |  |  |  _  |     |  |  |   __|  |  _  |     |  |  |  |     |  _  |   __|_   _|   __| __  |   __|\n");
    printf("| __ -|  |__|     |   --|    -|  |  |  |     |   --|    -|  | | | |     |__   | | | |   __|    -|__   |\n");
    printf("|_____|_____|__|__|_____|__|__|  |_____|__|__|_____|__|__|  |_|_|_|__|__|_____| |_| |_____|__|__|_____|\n\n");

    while (a != 3) {
        int b,opcion,modo,resultado;
        printf("1-Jugar\n");
        printf("2-Ranking\n");
        printf("3-Salir\n");
        printf("Eliga una opcion valida (ingrese 1, 2 o 3): ");
        scanf("%d", &a);

        switch (a) {
            case 1:
                printf("1-0 Jugadores\n");
                printf("2-1 Jugador\n");
                printf("3-Salir\n");
                printf("Eliga una opcion valida (ingrese 1, 2 o 3): ");
                scanf("%d", &opcion);

                switch (opcion) {
                    case 1:
                        jugarSimulacionBlackjack();
                        break;
                    case 2:
                        printf("1-Modo Basico\n");
                        printf("2-Modo Avanzado\n");
                        printf("3-Salir\n");
                        printf("Eliga una opcion valida (ingrese 1, 2 o 3): ");
                        scanf("%d", &modo);

                        switch (modo) {
                            case 1:
                                printf("Ingrese su nombre: ");
                                scanf("%s", rankingJugador.nombre);
                                resultado = jugarBlackjack(rankingJugador.nombre);
                                break;
                            case 2:
                                // Código para el modo avanzado
                                printf("Ingrese su nombre: ");
                                scanf("%s", rankingJugador.nombre);
                                jugarBlackjackAvanzado(rankingJugador.nombre);
                                break;
                            case 3:
                                printf("///////Gracias por jugar/////\n");
                                break;
                                //return 0;
                            default:
                                printf("Opcion no valida, ingrese una correcta:\n");
                                break;
                        }
                        break;
                    case 3:
                        printf("///////Gracias por jugar/////\n");
                        break;
                        
                    default:
                        printf("Opcion no valida, ingrese una correcta:\n");
                        break;
                }
                break;
                
            case 2:
                // Código para la opción 2-Ranking
                printf("////////Ranking//////\n");
                printf("La puntuacion del jugador %s es:%d\n",rankingJugador.nombre, rankingJugador.puntaje);
                //return 0;
                break;
            case 3:
                printf("///////Gracias por jugar/////\n");
                
                break;
            default:
                printf("Opcion no valida, ingrese una correcta:\n");
                break;
        }
    }
    
    printf("Programa finalizado\n");
    return 0;
}
