/*
 *	Exemple de test minimal ESP8266 avec #define et #ifdef  (03-TestMinimalMulti)
 *
 *		Allume la LED quand le bouton est poussé
 *
 *	Matériel
 *		ESP8266 version NodeMCU
 *			LED connectée en D4, allumé=bas
 *			Bouton connecté en D3, poussé=bas
 *
 *		ESP8266 version D1 Mini
 *			LED connecté avec une résistance de 100 Ohm entre D8 et +3.3V, allumé=bas
 *			Bouton connecté entre D1 et la masse, entrée paramétrée en pull-up, poussé=bas
 *
 *	V1.0.0 FF - Juillet 2023 - Pour le FabLab
 *
 *	GNU GENERAL PUBLIC LICENSE - Version 3, 29 June 2007
 *
 */

#define NODE_MCU											// ESP8266 version NODE MCU (sinon, version D1 Mini)
#ifdef NODE_MCU
	#define PINOCHE_BOUTON D3								// Entrée ESP du bouton
	#define PINOCHE_LED D4									// Sortie ESP de la LED
	#define BOUTON_MODE INPUT								// Mode de la pinoche du bouton
#else
	#define PINOCHE_BOUTON D1								// Entrée ESP du bouton
	#define PINOCHE_LED D8									// Sortie ESP de la LED
	#define BOUTON_MODE INPUT_PULLUP						// Mode de la pinoche du bouton
#endif
#define BOUTON_RELACHE HIGH									// Le bouton est relâché
#define BOUTON_POUSSE LOW									// Le bouton est poussé
#define ALLUME_LED LOW										// LED allumée à l'état BAS
#define ETEINS_LED HIGH										// LED éteinte à l'état HAUT

// Variables
int etatBouton = 0;											// État actuel du bouton

// Initialisation au lancement du programme
void setup() {
	digitalWrite(PINOCHE_LED, ETEINS_LED);					// Éteins la LED
	pinMode(PINOCHE_LED, OUTPUT);							// Définit la pinoche de la LED en sortie
	pinMode(PINOCHE_BOUTON, BOUTON_MODE);					// Définit la pinoche du bouton en entrée, avec tirage à l'état haut
}

// Boucle permanente
void loop() {
	etatBouton = digitalRead(PINOCHE_BOUTON);				// Lecture de l'état du bouton

	// Aligne l'état de la LED avec celui du bouton
	if (etatBouton == BOUTON_POUSSE) {						// Si le bouton est pressé
		digitalWrite(PINOCHE_LED, ALLUME_LED);				// Allume la LED
	} else {												// Sinon, le bouton est relâché
		digitalWrite(PINOCHE_LED, ETEINS_LED);				// Éteins la LED
	}
}

