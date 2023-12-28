/*
 *	Exemple de serveur Web avec gestion d'un bouton et d'une LED (11-WebLedBouton2)
 *
 *		Change l'état de la LED lorsque le bouton est poussé.
 *		Le serveur Web embarque indique l'état de la LED.
 *		Il permet aussi de forcer son allumage, son extinction ou sa bascule.
 *		Le serveur Web propose 3 boutons pour changer l'état de la LED.
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
#include <ESP8266WiFi.h>									// Librairie Wifi
 
// Définition du nom du point d'accès à créer
const char* ssid = "WIFI_SERVEUR_WEB";
const char* password = "PASSWORD";
 
// Classe serveur Web
WiFiServer serveurWeb(80);									// Utiliser le port 80
 
// Classe client Web
WiFiClient clientWeb;

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
	WiFi.softAP(ssid, password);							// Démarrer un point d'accès Wifi

	#ifdef DEBUG
		Serial.print("URL de connexion: http://");
		Serial.print(WiFi.softAPIP());						// Afficher l'adresse IP de ce serveur
		Serial.println("/");
	#endif
	serveurWeb.begin();										// Lancer le serveur Web
}

// Boucle permanente
void loop() {
	bouton.read();											// Passer la main à la classe EasyButton
	clientWeb = serveurWeb.available();						// Est-ce qu'on a un client?
	if (clientWeb) {										// Oui, on a un client
		#ifdef DEBUG
			Serial.println("Nouveau client connecté");
		#endif
		String requete = clientWeb.readStringUntil('\r');	// Lire la requête
		#ifdef DEBUG
			Serial.print("Requête : ");
			Serial.println(requete);						// Afficher la requête
		#endif
		clientWeb.flush();									// Vide le buffer des infos restantes
		clientWeb.println("HTTP/1.1 200 OK");				// Envoyer le statut de la demande
		clientWeb.println("Content-Type: text/html");		// Type de message
		clientWeb.println(""); 								// Fin de l'entête
		clientWeb.println("<!DOCTYPE HTML>");				// Document de type HTML
		clientWeb.println("<meta charset=\"UTF-8\">");      // Indiquer qu'on utilise des caractères accentués
		clientWeb.println("<html>");						// Début du HTML
		clientWeb.println("Bienvenue sur le serveur Web de test du FabLab !<br>");	// Message

		if (requete.indexOf("/LED=ON") >= 0 ) {				// "/LED=ON" dans la requête ?
			#ifdef DEBUG
				Serial.println("Force la LED on");
			#endif
			etatLed = ALLUME_LED;							// Allumer la LED
			digitalWrite(PINOCHE_LED, etatLed);				// Écrire le nouvel état de la LED
		} else if (requete.indexOf("/LED=OFF") >= 0 ) {		// "/LED=OFF" dans la requête ?
			#ifdef DEBUG
				Serial.println("Force la LED off");
			#endif
			etatLed = ETEINS_LED;							// Éteindre la LED
			digitalWrite(PINOCHE_LED, etatLed);				// Écrire le nouvel état de la LED
		} else if (requete.indexOf("/LED=INVERSE") >= 0 ) {	// "/LED=INVERSE" dans la requête ?
			#ifdef DEBUG
				Serial.println("Bascule l'état de la LED");
			#endif
			etatLed = ! etatLed;							// Inverser l'état de la LED
			digitalWrite(PINOCHE_LED, etatLed);				// Écrire le nouvel état de la LED
		}
		clientWeb.println("<br><br>");
		clientWeb.print("La LED est ");
		clientWeb.print(etatLed == ALLUME_LED ? "allumée":"éteinte");
		clientWeb.println("<br><br>");
		clientWeb.println("<a href=\"/LED=ON\"\"><button>Allumer</button></a>");
		clientWeb.println("<a href=\"/LED=OFF\"\"><button>Éteindre</button></a>");  
		clientWeb.println("<a href=\"/LED=INVERSE\"\"><button>Inverser</button></a>");  
		clientWeb.println("</html>");						// Fin du HTML
	}
}
