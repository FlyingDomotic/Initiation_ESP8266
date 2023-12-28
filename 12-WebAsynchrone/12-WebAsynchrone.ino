/*
 *	Exemple de serveur Web avec gestion d'un bouton et d'une LED (12-WebAsynchrone)
 *
 *		Change l'état de la LED lorsque le bouton est poussé.
 *		Le serveur Web embarque indique l'état de la LED.
 *		Il permet aussi de forcer son allumage, son extinction ou sa bascule.
 *		Le serveur Web propose 3 boutons pour changer l'état de la LED.
 *		Version du serveur Web Asynchrone
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
#define ALLUME_LED LOW										// LED allumée à l'état BAS
#define ETEINS_LED HIGH										// LED éteinte à l'état HAUT
#define BOUTON_ANTI_REBOND (50)								// Anti-rebond à 50 ms
#define BOUTON_BAS true										// Bouton actif au niveau bas

#include <EasyButton.h>										// Librairie Easy Button
#include <ESP8266WiFi.h>									// Librairie Wifi
#include <ESPAsyncWebServer.h>								// Librairie serveur Web asynchrone
 
// Définition du nom du point d'accès à créer
const char* ssid = "WIFI_SERVEUR_WEB";
const char* password = "PASSWORD";
 
// Classe serveur Web asynchrone
AsyncWebServer serveurWeb(80);								// Utiliser le port 80
 
// Variables
int etatLed = ETEINS_LED;									// État initial de la LED

// Classe Easy Button
EasyButton bouton(PINOCHE_BOUTON, BOUTON_ANTI_REBOND, BOUTON_BAS, BOUTON_PULL_UP);

// Aligne l'étt de la LED avec le contenu de la variable etatLed
void modifieLed() {
	digitalWrite(PINOCHE_LED, etatLed);						// Écrire le nouvel état de la LED
	#ifdef DEBUG
		if (etatLed == ALLUME_LED) {						// Est-ce que la LED est allumée ?
			Serial.println("La LED est allumée");
		} else {
			Serial.println("La LED est éteinte");
		}
	#endif
}

// Renvoie l'état de la LED
void afficheEtat(AsyncWebServerRequest *requete) {
	String message = "";									// Contenu de la réponse
	message += "<!DOCTYPE HTML>\n";							// Document de type HTML
	message += "<meta charset=\"UTF-8\">\n";				// Indiquer qu'on utilise des caractères accentués
	message += "<html>\n";									// Début du HTML
	message += "Bienvenue sur le serveur Web de test du FabLab !<br>\n";	// Message
	message += "<br><br>\n";
	message += "La LED est ";
	message += etatLed == ALLUME_LED ? "allumée":"éteinte";
	message += "\n<br><br>";
	message += "<a href=\"/LED=ON\"\"><button>Allumer</button></a>\n";
	message += "<a href=\"/LED=OFF\"\"><button>Éteindre</button></a>\n";  
	message += "<a href=\"/LED=INVERSE\"\"><button>Inverser</button></a>\n";  
	message += "</html>\n";									// Fin du HTML
	requete->send_P(200, "text/html", message.c_str());
}

// Routine activée lors de la réception de la commande /LED=ON
void setLedOn(AsyncWebServerRequest *requete) {
	#ifdef DEBUG
		Serial.println("Force la LED on");
	#endif
	etatLed = ALLUME_LED;
	modifieLed();
	afficheEtat(requete);
}

// Routine activée lors de la réception de la commande /LED=OFF
void setLedOff(AsyncWebServerRequest *requete) {
	#ifdef DEBUG
		Serial.println("Force la LED off");
	#endif
	etatLed = ETEINS_LED;
	modifieLed();
	afficheEtat(requete);
}
// Routine activée lors de la réception de la commande /LED=INVERSE
void setLedInverse(AsyncWebServerRequest *requete) {
	#ifdef DEBUG
		Serial.println("Bascule l'état de la LED");
	#endif
	etatLed = !etatLed;
	modifieLed();
	afficheEtat(requete);
}

// Routine activée lors de l'appui sur le bouton
void appuiBouton() {
	#ifdef DEBUG
		Serial.println("Le bouton est poussé");				// Tracer l'état du bouton
	#endif
	etatLed = ! etatLed;									// Oui, inverser l'état de la LED
	modifieLed();
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

	serveurWeb.on("/", HTTP_GET, afficheEtat);				// Routines réalisant les différente actions
	serveurWeb.on("/LED=ON", HTTP_GET, setLedOn);
	serveurWeb.on("/LED=OFF", HTTP_GET, setLedOff);
	serveurWeb.on("/LED=INVERSE", HTTP_GET, setLedInverse);

	serveurWeb.begin();										// Lancer le serveur Web
}

// Boucle permanente
void loop() {
	bouton.read();											// Passer la main à la classe EasyButton
}
