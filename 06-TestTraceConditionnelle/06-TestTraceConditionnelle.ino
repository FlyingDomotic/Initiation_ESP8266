/*
 *	Exemple de test bouton poussoir ESP8266  (06-TestTraceConditionnelle)
 *
 *		Change l'état de la LED lorsque le bouton est poussé.
 *		Version avec trace conditionnelle des états et actions
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
	#ifdef DEBUG
		Serial.begin(74880);								// Initialise le port série à 74880 bds (~ 7.500 caractères par seconde)
		Serial.println("Le programme s'initialise ...");
	#endif
	digitalWrite(PINOCHE_LED, ETEINS_LED);					// Éteins la LED
	pinMode(PINOCHE_LED, OUTPUT);							// Définit la pinoche de la LED en sortie
	pinMode(PINOCHE_BOUTON, BOUTON_MODE);					// Définit la pinoche du bouton en entrée, avec tirage à l'état haut
}

// Boucle permanente
void loop() {
	etatBouton = digitalRead(PINOCHE_BOUTON);				// Lecture de l'état du bouton

	if (etatBouton != etatBoutonPrecedent) {				// Est-ce que l'état du bouton a changé depuis la dernière lecture ?
		if (etatBouton == BOUTON_POUSSE) {					// Oui, est-ce que le bouton est pressé maintenant ?
			#ifdef DEBUG
				Serial.println("Le bouton est poussé");		// Tracer l'état du bouton
			#endif
			etatLed = ! etatLed;							// Oui, inverser l'état de la LED
			digitalWrite(PINOCHE_LED, etatLed);				// Écrire le nouvel état de la LED
			#ifdef DEBUG
				if (etatLed == ALLUME_LED) {				// Est-ce que la LED est allumée ?
					Serial.println("La LED est allumée");
				} else {
					Serial.println("La LED est éteinte");
				}
			#endif
		} else {
			#ifdef DEBUG
				Serial.println("Le bouton est relâché");	// Tracer l'état du bouton
			#endif
		}
		etatBoutonPrecedent = etatBouton;					// Mémoriser le dernier état du bouton
	}
}
