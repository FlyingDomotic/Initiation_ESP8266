# FabLab - Introduction à l'ESP8266

## A quoi ça sert ?
Ces fichiers sont une introduction pratique à l'ESP8266. Les exemples fournis utilisent un NodeMCU.
Il est également possible d'utiliser un D1 mini avec un bouton poussoir, une LED et une résistance.
Le premiers exemples allument la lampe lorsqu'on appuie sur le bouton.
Viennent ensuite quelques exemples de serveur Web sur un point d'accès WiFi local.
Les versions finales couplent les deux, en ajoutant une mise à jour par le réseau.

## Prérequis

Vous devez avoir une machine Windows, Linux ou Mac avec l'IDE Arduino installé (disponible à https://www.arduino.cc/en/software).
De plus, vous devez avoir ajouté le support matériel Arduino pour l'ESP8266 (inclure la ligne "http://arduino.esp8266.com/stable/package_esp8266com_index.json" dans la liste du gestionnaire de cartes supplémentaires des préférences de l'IDE Arduino).
Vous devez enfin installer le support ESP8266 dans le gestionnaire de carte de l'IDE.
Vous trouverez des explications détaillées (par exemple) à http://blog.idleman.fr/programmer-un-esp8266-avec-arduino-ide-editor/. Chargez les dernières versions de l'IDE et du support ESP8266.

## Installation

Clonez le dépôt GitHub dans le répertoire de votre choix
```
cd ~
git clone https://github.com/FlyingDomotic/Introduction_ESP8266.git Introduction_ESP8266
```

## Mise à jour

Allez dans le répertoire d'installation et charger la nouvelle version
```
cd ~/Introduction_ESP8266
git pull
```
Note: si vous avez fait des modifs dans les fichiers du plugin et que la commande `git pull` ne fonctionne pas, vous pouvez écraser les modifications locales avec la commande
```
git stash
```
ou
```
git checkout <fichier modifié>
```

## Configuration

Utilisez le menu "Outils" pour sélectionner le type ce carte dont vous disposez (probablement un nodeMCU 1.0 ou un D1 mini). Sélectionnez également le port où le module est connecté (attention à le brancher sur votre machine avant de sélectionner le port).

## Exemples fournis

Voici la liste des fichiers d'exemple fournis avec leurs principales caractérisques :
1. TestMinimalNodeMcu : allume la LED lorsqu'on appuie sur le bouton d'un nodeMCU
2. TestMinimalNodeMcuDefine : ajoute des #define pour isoler les paramètres
3. TestMinimalMulti : ajoute le support du D1 mini
4. TestPoussoir : chaque appui change l'état de la lampe
5. TestTrace : ajoute une trace sur le port série
6. TestTraceConditionnelle : rend la trace conditionnelle
7. TestDebouncerCallback : ajoute un module anti-rebond (debouncer) avec rétro-appel (callback)
8. WebMinimal : version minimale d'un serveur Web
9. WebRequete : ajoute l'affichage de la requête envoyée au serveur
10. WebLedBouton : intègre bouton et LED de l'exemple 8 et affiche létatu de la LED sur la page Web
11. WebLedBouton2 : ajoute 3 boutons sur la page Web pour changer l'état de la LED
12. WebAsynchrone : version asynchrone du serveur Web
13. WebWifiExistant : ajout de la connexion à un WiFi existant
14. WebOta : ajout de la mise à jour du micro-code par le réseau (OTA - Over The Air)
