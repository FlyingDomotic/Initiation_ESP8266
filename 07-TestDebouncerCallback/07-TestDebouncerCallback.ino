/*
 *	Exemple de test bouton poussoir ESP8266  (07-TestDebouncerCallback)
 *
 *		Change l'état de la LED lorsque le bouton est poussé.
 *		Version avec anti-rebonds (debouncer) et rétro appel (callback)
 *
 *	Matériel
 *		ESP8266 version NodeMCU
 *			LED connectée en D4, allumé=bas
 *			Bouton connecté en D3, poussé=bas
 *
 *	V1.0.0 FF - Juillet 2023 - Pour le FabLab
 *
 *	GNU GENERAL PUBLIC LICENSE - Version 3, 29 June 2007
 *
 */

#define DEBUG												// Trace des états et actions

#define PINOCHE_BOUTON D3									// Entrée ESP du bouton
#define PINOCHE_LED D4										// Sortie ESP de la LED
#define BOUTON_PULL_UP false								// Bouton sans tirage au niveau haut
#define BOUTON_ANTI_REBOND (50)								// Anti-rebond à 50 ms
#define BOUTON_BAS true										// Bouton actif au niveau bas
#define ALLUME_LED LOW										// LED allumée à l'état BAS
#define ETEINS_LED HIGH										// LED éteinte à l'état HAUT

#include <EasyButton.h>										// Librairie Easy Button

// Variables
int etatLed = ETEINS_LED;									// État initial de la LED

// Classe Easy Button
EasyButton bouton(PINOCHE_BOUTON, BOUTON_ANTI_REBOND, BOUTON_BAS, BOUTON_PULL_UP);

// Routine activée lors de l'appui sur le bouton
void appuiBouton() {
	#ifdef DEBUG
		Serial.println("Le bouton est poussé");				// Tracer l'état du bouton
	#endif
	etatLed = ! etatLed;									// Oui, inverser l'état de la LED
	digitalWrite(PINOCHE_LED, etatLed);						// Écrire le nouvel état de la LED
	#ifdef DEBUG
		if (etatLed == ALLUME_LED) {						// Est-ce que la LED est allumée ?
			Serial.println("La LED est allumée");
		} else {
			Serial.println("La LED est éteinte");
		}
	#endif
}

// Initialisation au lancement du programme
void setup() {
	#ifdef DEBUG
		Serial.begin(74880);								// Initialise le port série à 74880 bds (~ 7.500 caractères par seconde)
		Serial.println("Le programme s'initialise ...");
	#endif
	digitalWrite(PINOCHE_LED, ETEINS_LED);					// Éteins la LED
	pinMode(PINOCHE_LED, OUTPUT);							// Définit la pinoche de la LED en sortie
	bouton.begin();											// Lance la gestion du bouton
	bouton.onPressed(appuiBouton);							// Routine à appeler lors de l'appui sur le bouton
}

// Boucle permanente
void loop() {
	bouton.read();											// Passer la main à la classe EasyButton
}
