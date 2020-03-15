//
//      ENERGÍA Y EFICIENCIA: AHORRO EN EL PASO A BOMBILLAS LED
//

// Librerías
#include <stdio.h>
#include <string.h>

// Variables globales
int hours;			  // hours diarias de uso
int bombillasT[9][2]; // Bombillas a cambiar

const int inc[9] = {10, 15, 25, 40, 60, 75, 100, 150, 200};					// Consumo bombillas incandescentes
const int hal[9] = { 0, 10, 20, 35, 50, 70, 100, 150, 200};					// Consumo bombillas halógenas
const float led[9] = {1.3, 3.5, 5.0, 9.0, 11.0, 15.0, 18.0, 25.0, 30.0};	// Consumo bombillas LED

float energyCost = 0.18f;
float bulbCost = 0.00f;

// Funciones
void list(){

    printf(" \n\t;-------------------------------------------------;\n");
    printf("   \t|     CONSUMPTION COMPARISON PER BULB (WATTS)     |\n");
    printf("   \t|-------------------------------------------------|\n");
    printf("   \t|   INCANDESCENTS  |     LEDS     |    HALOGENS   |\n");
    printf("01:\t|        10        |      1,3     |      ---      |\n");
    printf("02:\t|        15        |      3,5     |       10      |\n");
    printf("03:\t|        25        |      5,0     |       20      |\n");
    printf("04:\t|        40        |      9,0     |       35      |\n");
    printf("05:\t|        60        |     11,0     |       50      |\n");
    printf("06:\t|        75        |     15,0     |       70      |\n");
    printf("07:\t|       100        |     18,0     |      100      |\n");
    printf("08:\t|       150        |     25,0     |      150      |\n");
    printf("09:\t|       200        |     30,0     |      200      |\n");
    printf("   \t'-------------------------------------------------'\n");
    printf("(Bulbs in the same row have aprox. the same brightness)\n\n");
}

float initPower(){

    float iP = 0;
    for(int i=0; i<9; i++){
    	iP += bombillasT[i][0]*inc[i];
    	iP += bombillasT[i][1]*hal[i];
    }
    return iP;
}

float actualPower(){
	float aP = 0;
    for(int i=0; i<9; i++){
    	aP += bombillasT[i][0]*led[i];
    	aP += bombillasT[i][1]*led[i];
    }
    return aP;
}

void status(){

	// Resumen de bombillas a cambiar
    printf("\n  INCANDESCENT TO LED    \t|      HALOGEN TO LED\n");
    printf("        10w ---> %d        \t|           ---      \t\n", bombillasT[0][0]);
    printf("        15w ---> %d        \t|        10w ---> %d \t\n", bombillasT[1][0], bombillasT[1][1]);
    printf("        25w ---> %d        \t|        20w ---> %d \t\n", bombillasT[2][0], bombillasT[2][1]);
    printf("        40w ---> %d        \t|        35w ---> %d \t\n", bombillasT[3][0], bombillasT[3][1]);
    printf("        60w ---> %d        \t|        50w ---> %d \t\n", bombillasT[4][0], bombillasT[4][1]);
    printf("        75w ---> %d        \t|        70w ---> %d \t\n", bombillasT[5][0], bombillasT[5][1]);
    printf("       100w ---> %d        \t|       100w ---> %d \t\n", bombillasT[6][0], bombillasT[6][1]);
    printf("       150w ---> %d        \t|       150w ---> %d \t\n", bombillasT[7][0], bombillasT[7][1]);
    printf("       200w ---> %d        \t|       200w ---> %d \t\n", bombillasT[8][0], bombillasT[8][1]);

    // Potencia eléctrica ahorrada y porcentaje de eficiencia aumentado
    float iP = initPower();
    float aP = actualPower();
    printf("\nPower saved: %.2fw", iP-aP);
    if (iP-aP > 0) printf("\nEnergy consumption has been reduced to %.2f%%", 100*(aP/iP));
    else 		   printf("\nEnergy consumption has not changed");

    // hours totales de uso al ano, el precio por Kwh
    printf("\n\nHours used whithin a year: %d\t\tKwh price: %.2f\n", hours*365, energyCost);

    // Comparativa de costes con el sistema anterior, con el actual y su diferencia
    printf("\nCOSTS\n\t    Before\t  After\t\tDifference");
    printf("\n   Week:    %.2f \t  %.2f  \t%.2f", (energyCost*iP*hours*7/1000),   (energyCost*aP*hours*7/1000),   (energyCost*(iP-aP)*hours*7/1000));
    printf("\n   Month:   %.2f \t  %.2f  \t%.2f", (energyCost*iP*hours*30/1000),  (energyCost*aP*hours*30/1000),  (energyCost*(iP-aP)*hours*30/1000));
    printf("\n   Year:    %.2f \t  %.2f  \t%.2f", (energyCost*iP*hours*365/1000), (energyCost*aP*hours*365/1000), (energyCost*(iP-aP)*hours*365/1000));

    // Cálculo del tiempo de amortización del cambio de bombillas
    long amortS = (bulbCost/(energyCost*(iP-aP)*hours*7/1000));
    if (amortS <= 0){
    	printf("\n\nPayback time: - weeks or ");
    }
    else {
    	printf("\n\nPayback time: %li weeks o ", amortS);
    }

    long amortM = (bulbCost/(energyCost*(iP-aP)*hours*30/1000));
    if (amortM <= 0) printf("- months.\n\n");
    else			 printf("%li months.\n\n", amortM);
}

void add(){

	// Tomar datos
	char type[1];
	int num, npot;
    printf ("\nHow many bulbs would you like to add?\t");
	scanf("%i", &num);
	printf("What type are they? (i/h)\t\t");
	scanf("%s", type);
	printf("How much power do they? (1-9)\t\t");
    scanf("%i", &npot);

    // Chequeo de datos y operaciones
    if (num <= 0){
    	printf("INVALID BULB AMOUNT\n");
    }
    else {
        if (npot<1 || npot>9){
        	printf("INCORRECT BULB POWER. It must be an integer from 1 to 9.\n");
        }
        else {

        	// Bombillas incandescentes
            if (type[0] == 'i'){
                float addition = num * (inc[npot-1] - led[npot-1]);
                printf("\nDone. The saving achieved with this change is: %.2fw\n\n", addition);
                bombillasT[npot-1][0] = num;
            }

        	// Bombillas halógenas
            else if ((type[0] == 'h') && (npot !=1)){
                float addition = num * (hal[npot-1] - led[npot-1]);
                printf("\nDone. The saving achieved with this change is: %.2fw\n\n", addition);
                bombillasT[npot-1][1] = num;
            }

            else {
            	printf("INCORRECT BULB TYPE OR POWER. Bulb type should be 'i' or 'h'.\n");
            }
        }
    }
}


void remove(){

	// Tomar datos
	char type[1];
	int num, npot;
    printf ("\nHow many bulbs do you want to remove?\t");
	scanf("%d", &num);
	num = -num;
	printf("What type are they? (i/h)\t\t\t");
	scanf("%s", type);
	printf("How much power do they? (1-9)\t\t\t");
    scanf("%d", &npot);

    // Chequeo de datos y operaciones
    if (num >= 0) printf("INVALID BULB AMOUNT\n");
    else {
        if (npot < 1) printf("INCORRECT BULB POWER -.-\n");
        else if (npot > 9) printf("INCORRECT BULB POWER. It must be an integer from 1 to 9.\n");
        else {

        	// Bombillas incandescentes
            if (type[0] == 'i'){
                num = -num;
                float addition = num * (inc[npot-1] - led[npot-1]);
                printf("\nDone. The saving lost with this change is: %.2fw\n\n", addition);
                num = -num;
                bombillasT[npot-1][0] += num;
            }

            // Bombillas halógenas
            else if ((type[0] == 'h') && (npot !=1)){
                num = -num;
                float addition = num * (hal[npot-1] - led[npot-1]);
                printf("\nDone. The saving lost with this change is: %.2fw\n\n", addition);
                num = -num;
                bombillasT[npot-1][1] += num;
            }

            else {
            	printf("INCORRECT BULB TYPE OR POWER. Bulb type should be 'i' or 'h'.\n");
            }
        }
    }
}


void reset(){

	for(int i=0; i<10; i++){
		for(int j=0; j<2; j++){
			bombillasT[i][j] = 0;
		}
	}

    hours  = 0;
}


void energyCostUpdate(){
    printf("\nHow much do the bulbs cost?\t\t\t");
    scanf("%f", &bulbCost);
    if (bulbCost < 0){
    	printf("Are you paid for taking them? Let's say they're free...");
    	bulbCost = 0;
    }
    printf("Whats the price of a Kwh? (default 0.18)\t");
    scanf("%f", &energyCost);
    if (energyCost > 0.5){
    	printf("I believe that's too much... let's leave it as it was\n");
    	energyCost=0.18;
    }
    else if (energyCost < 0){
    	printf("I don't think you are paid for wasting energy...\n");
    	energyCost=0.18;
    }
    else {
    	printf("The price has been modified.\n\n");
    }
}


int main(){

    // Presentación
    printf("\n |                                                                            |\n");
    printf(" | LED-Bulbs: Light eficiency                                                 |\n");
    printf(" | Por Pablo Davila                                                           |\n\n");

    reset();

    // Cuerpo del programa
    while(true){

        // Selección de comando
		char comando[6];
        printf("\n>>");
		scanf("%s", comando);

		// Traducción numérica del comando escrito
		int funcion;
        if      (strcmp(comando, "help")   == 0) funcion = 0;
        else if (strcmp(comando, "list")   == 0) funcion = 1;
        else if (strcmp(comando, "status") == 0) funcion = 2;
        else if (strcmp(comando, "add")    == 0) funcion = 3;
        else if (strcmp(comando, "remove") == 0) funcion = 4;
        else if (strcmp(comando, "reset")  == 0) funcion = 5;
        else if (strcmp(comando, "time")   == 0) funcion = 6;
        else if (strcmp(comando, "price")  == 0) funcion = 7;
        else if (strcmp(comando, "exit")   == 0) funcion = 8;
        else if (strcmp(comando, "stop")   == 0) funcion = 8;
        else {
            printf("(ERROR: Uknown command)\n");
            funcion = 0;
        }

        // Ejecución del comando introducido
		switch(funcion){

		case 0: // Comando HELP
			printf("\nCommands:\n1. list:\tShows the available light bulbs.\n2. status:\tShows the selected bulbs and more data.\n3. add: \tAdd bulbs you will change for LED ones.\n4. remove:\tRemove selected bulbs from the list.\n5. reset:\tWipes the selected bulbs list.\n6. time:\tAllows you to set up the average daily usage of the bulbs.\n7. price:\tAllows you to enter the bulbs and the electricity's price.\n8. exit:\tLeave this program.\n\n");
			funcion = -1;
			break;

		case 1: // Comando LIST
			list();
			funcion = -1;
			break;

		case 2: // Comando STATUS
			status();
			funcion = -1;
			break;

		case 3: // Comando ADD
			add();
			funcion = -1;
			break;

		case 4: // Comando REMOVE
			remove();
			funcion = -1;
			break;

		case 5: // Comando RESET
			char answ[3];
			printf("\nAre you sure you want to delete all the selected light bulbs?\t");
			scanf("%s", answ);
			if      (strcmp(answ, "si")  == 0) reset();
			else if (strcmp(answ, "sep") == 0) reset();
			else if (strcmp(answ, "seh") == 0) reset();
			else if (strcmp(answ, "yes") == 0) reset();
			printf("\nAll the selected light bulbs have been deleted.\n\n");
			funcion = -1;
			break;

		case 6: // Comando TIME
			printf("\nHow many hours a day do you use these bulbs?\t");
			scanf("%d", &hours);
			if ((hours > 24)||(hours < 0)){
				printf("You must enter an integer between 0 and 24\n");}
			else {
				printf("Bulbs usage submited.\n\n");
			}
			funcion = -1;
			break;

		case 7: // Comando PRICE
			energyCostUpdate();
			funcion = -1;
			break;

		case 8: // Comando EXIT
			printf("\nI hope you finded it useful! ;-)\n\n");
			return 0;
		}
	}
}

