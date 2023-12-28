/*
 *	Exemple de test bouton poussoir ESP8266  (04-TestPoussoir)
 *
 *		Change l'état de la LED lorsque le bouton est poussé
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

#define PINOCHE_BOUTON D3									// Entrée ESP du bouton
#define PINOCHE_LED D4										// Sortie ESP de la LED
#define BOUTON_MODE INPUT									// Mode de la pinoche du bouton
#define BOUTON_RELACHE HIGH									// Le bouton est relâché
#define BOUTON_POUSSE LOW									// Le bouton est poussé
#define ALLUME_LED LOW										// LED allumée à l'état BAS
#define ETEINS_LED HIGH										// LED éteinte à l'état HAUT

// Variables
int etatBoutonPrecedent = BOUTON_RELACHE;					// État précédent du bouton
int etatLed = ETEINS_LED;									// État initial de la LED
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

	if (etatBouton != etatBoutonPrecedent) {				// Est-ce que l'état du bouton a changé depuis la dernière lecture ?
		if (etatBouton == BOUTON_POUSSE) {					// Oui, est-ce que le bouton est pressé maintenant ?
			etatLed = ! etatLed;							// Oui, inverser l'état de la LED
			digitalWrite(PINOCHE_LED, etatLed);				// Écrire le nouvel état de la LED
		}
		etatBoutonPrecedent = etatBouton;					// Mémoriser le dernier état du bouton
	}
}
