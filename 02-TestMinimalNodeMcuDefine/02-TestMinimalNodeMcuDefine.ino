/*
 *	Exemple de test minimal ESP8266 avec #define  (02-TestMinimalNodeMcuDefine)
 *
 *		Allume la LED quand le bouton est poussé
 *
 *	Matériel
 *		ESP8266 version NodeMCU
 *			LED connectée en D4, allumé=bas
 *			Bouton connecté en D3, poussé=bas
 *
 *	V1.0.0 FF - Juillet 2023 - Pour le FabLab
 *
 *	GNU GENERAL PUBLIC LICENSE - Version 3, 29 June 2007
 */

#define PINOCHE_BOUTON D3									// Entrée ESP du bouton
#define BOUTON_RELACHE HIGH									// Le bouton est relâché
#define BOUTON_POUSSE LOW									// Le bouton est poussé
#define BOUTON_MODE INPUT									// Mode de la pinoche du bouton
#define PINOCHE_LED D4										// Sortie ESP de la LED
#define ALLUME_LED LOW										// LED allumée à l'état BAS
#define ETEINS_LED HIGH										// LED éteinte à l'état HAUT

// Variables
int etatBouton = 0;											// État actuel du bouton

// Initialisation au lancement du programme
void setup() {
	digitalWrite(PINOCHE_LED, ETEINS_LED);					// Éteins la LED
	pinMode(PINOCHE_LED, OUTPUT);							// Définit la pinoche de la LED en sortie
	pinMode(PINOCHE_BOUTON, BOUTON_MODE);					// Définit la pinoche du bouton en entrée
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
