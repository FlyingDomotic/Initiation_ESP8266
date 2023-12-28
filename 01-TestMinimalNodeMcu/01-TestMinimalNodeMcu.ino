/*
 *	Exemple de test minimal ESP8266 (01-TestMinimalNodeMcu)
 *
 *		Allume la LED quand le bouton est poussé (version NodeMCU)
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

// Variables
int etatBouton = 0;											// État actuel du bouton

// Initialisation au lancement du programme
void setup() {
	digitalWrite(D4, HIGH);									// Éteins la LED
	pinMode(D4, OUTPUT);									// Définit la pinoche de la LED en sortie
	pinMode(D3, INPUT);										// Définit la pinoche du bouton en entrée
}

// Boucle permanente
void loop() {
	etatBouton = digitalRead(D3);							// Lecture de l'état du bouton

	// Aligne l'état de la LED avec celui du bouton
	if (etatBouton == LOW) {								// Si le bouton est pressé
		digitalWrite(D4, LOW);								// Allume la LED
	} else {												// Sinon, le bouton est relâché
		digitalWrite(D4, HIGH);								// Éteins la LED
	}
}
