/*
 *	Exemple de serveur Web (09-WebRequete)
 *
 *		Affiche la requête envoyée au serveur
 *
 *	Matériel
 *		ESP8266
 *
 *	V1.0.0 FF - Juillet 2023 - Pour le FabLab
 *
 *	GNU GENERAL PUBLIC LICENSE - Version 3, 29 June 2007
 *
 */

#define DEBUG												// Trace des états et actions

// Include la librairie Wifi
#include <ESP8266WiFi.h>
 
// Définition du nom du point d'accès à créer
const char* ssid = "WIFI_SERVEUR_WEB";
const char* password = "PASSWORD";
 
// Classe serveur Web
WiFiServer serveurWeb(80);									// Utiliser le port 80
 
// Classe client Web
WiFiClient clientWeb;

// Initialisation au lancement du programme
void setup() {
	#ifdef DEBUG
		Serial.begin(74880);								// Initialise le port série à 74880 bds (~ 7.500 caractères par seconde)
		Serial.println("Le programme s'initialise ...");
	#endif

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
		clientWeb.print("Vous avez envoyé : ");
		clientWeb.println(requete);
		clientWeb.println("</html>");						// Fin du HTML
	}
}
