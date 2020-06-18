//////////////////////////////////////////////////////////////////////////////////////////////////////
// \title       Travail dirigé no 6
// \description Programme qui permet de créer une sonnerie, la modifier, l’afficher ou la recommencer.
// \file        main.cpp
// \author      Marc-André Gosselin (2020217)
// \author      Martin Careau (1978446)
// \date        18/06/2020
//////////////////////////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include "cppitertools//range.hpp"
#include "gsl/span"


#include <bitset>
using namespace std;
using namespace iter;
using namespace gsl;

const uint64_t nBitsDuree = 4;
const uint64_t nBitsNote = 4;
const uint64_t nNotes = 9;
const uint64_t dureeMax = 15;
const uint64_t taillePortee = 9;
const uint64_t nBitsParOctet = 8;

struct Portee {
    uint64_t nColonnes;
    char** portee;
};

/**
 * Affiche un texte et lit une valuer située dans l'intervalle défini
 *
 * \param [in] texte		Le texte à afficher
 * \param [in] max			La valeur maximale acceptée
 *
 * \return La valeur lue
 */
uint64_t lireValeurValide(string texte, uint64_t max) {
    uint64_t valeur;
    do {
        cout << texte << endl;
        cin >> valeur;
    } while (valeur < 0 || valeur > max);
    return valeur;
}

/**
 * Retourne la valeur du décalage à effectuer
 *
 * \param [in] position		La position
 * \param [in] nBits		Nombre de bits de la note ou durée
 *
 * \return La valeur du décalage
 */
uint64_t calculerDecalage(uint64_t position, uint64_t nBits) {
    // TODO: Calculer le décalage nécessaire pour que le premier bit de la séquence se retrouve à la position demandée du uint64_t
    return ((64 - nBits) - (position * nBits));
}

/**
 * Effectue le décalage à gauche
 *
 * \param [in] valeurADecaler	La valeur à décaler
 * \param [in] decalage		    Nombre de bits à décaler
 *
 * \return La valeur décalée
 */
uint64_t effectuerDecalageAGauche(uint64_t valeurADecaler, uint64_t decalage) {
    // TODO: Décaler valeurADecaler à gauche de decalage bits
    return valeurADecaler << decalage;
}

/**
 * Ajoute des bits dans une sonnerie
 *
 * \param [in] sonnerie	    La sonnerie à modifier
 * \param [in] position		La position où ajouter les bits
 * \param [in] bits	        Les bits à ajouter
 * \param [in] nBits		Nombre de bits de la note ou durée
 *
 * \return La valeur du décalage
 */
void ajouterBitsDansSonnerie(uint64_t& sonnerie, uint64_t position, uint64_t bits, uint64_t nBits) {
    // TODO: Créer un masque contenant uniquement des bits à 0 sauf pour les nBits à écrire (en tenant compte aussi de leur position)
    uint64_t masque = pow(2, nBits) - 1;
    masque = effectuerDecalageAGauche(masque, calculerDecalage(position, nBits));
    // TODO: Inverser le masque pour avoir uniquement des bits à 1 sauf pour les nBits à écrire
    masque = masque ^ 0xffffffffffffffff;
    // TODO: Appliquer le masque pour que la sonnerie garde le même contenu sauf pour les nBits à écrire qui sont maintenant à 0
    sonnerie = sonnerie & masque;
    // TODO: Décaler les bits à écrire pour qu'ils soient à la bonne position dans la sonnerie
    bits = effectuerDecalageAGauche(bits, calculerDecalage(position, nBits));
    // TODO: Combiner les bits à la sonnerie pour les ajouter
    sonnerie += bits;
}

/**
 * Retourne les bits de la sonnerie à une position donnée
 *
 * \param [in] sonnerie	    La sonnerie à extraire des bits
 * \param [in] position		La position où extraire les bits
 * \param [in] nBits		Nombre de bits de la note ou durée
 *
 * \return Les bits extrait de la sonnerie
 */
uint64_t obtenirBitsDeSonnerie(uint64_t sonnerie, uint64_t position, uint64_t nBits) {
    // TODO: Créer un masque contenant uniquement des bits à 0 sauf pour les nBits à extraire (en tenant compte aussi de leur position)
    uint64_t masque = 0xfffffffffffffff << (64 - nBits); masque = masque >> (position * nBits);
    // TODO: Appliquer un masque pour extraire les bits
    sonnerie = sonnerie & masque;
    // TODO: Décaler les bits obtenus pour les ramener à droite (en fonction de leur position initiale)
    sonnerie = sonnerie >> (64-((position+1) * nBits));
    return sonnerie;
}

/**
 * Retourne une sonnerie sous la forme uint64_t
 *
 * \param [in] duree	    La duree de la sonnerie
 * \param [in] notes		Un tableau de notes
 *
 * \return La sonnerie sous 64 bits
 */
uint64_t convertirSonnerieEnInt(uint64_t duree, uint64_t* notes) {
    uint64_t sonnerie = 0;
    // TODO: Ajouter la durée au début de la sonnerie
    sonnerie += effectuerDecalageAGauche(duree, calculerDecalage(0, nBitsDuree));
    // TODO: Ajouter chaque note dans la sonnerie
    for (uint64_t i : range(duree)) {
        sonnerie += effectuerDecalageAGauche(notes[i], calculerDecalage(i+1, nBitsNote));
    }
    return sonnerie;
}

/**
 * Crée une sonnerie par l'utilisateur
 *
 * \return La sonnerie nouvellement créée
 */
uint64_t creerNouvelleSonnerie() {
    // TODO: Lire la durée de la sonnerie
    uint64_t duree = lireValeurValide("Veuillez entrer la duree de la sonnerie", dureeMax);
    // TODO: Allouer le tableau dynamique de notes
    uint64_t notes[dureeMax];
    // TODO: Lire et stocker chaque note dans le tableau
    for (uint64_t i : range(duree)) {
        notes[i] = lireValeurValide("Veuillez entrer la note", nNotes);
    }
    // TODO: Convertir la sonnerie en int
    return convertirSonnerieEnInt(duree, notes);
}

/**
 * Ajoute une note donnée par l'utilisateur à la sonnerie
 *
 * \param [in] sonnerie	    La sonnerie à laquelle ajouter une note
 */
void ajouterNote(uint64_t& sonnerie) {
    // TODO: Si le nombre maximal de notes n'est pas atteint:
    if (sonnerie < 0xf00000000000000) {
        uint64_t duree = sonnerie >> nNotes * nBitsNote;
        // TODO: Modifier la durée de la sonnerie
        sonnerie += 0x100000000000000;
        // TODO: Lire et ajouter une note à la fin de la sonnerie
        uint64_t note = lireValeurValide("Veuillez entrer la note", nNotes);
        ajouterBitsDansSonnerie(sonnerie, duree, note, nBitsNote);
    }
    // TODO: Sinon, afficher un message d'erreur
    else {
        cerr << "La sonnerie a atteint la duree maximale." << endl;
    }
}

/**
 * Retirer la dernière note d'une sonnerie
 *
 * \param [in] sonnerie	    La sonnerie à retirer la dernière note
 */
void enleverNote(uint64_t& sonnerie) {
    // TODO: Si la sonnerie n'est pas vide:
    if (sonnerie >= 0x1000000000000000) {
        uint64_t duree = obtenirBitsDeSonnerie(sonnerie, 0, nBitsDuree);
        // TODO: Modifier la durée de la sonnerie
        sonnerie -= 0x1000000000000000;
        // TODO: Enlever une note à la fin de la sonnerie
        uint64_t masque = pow(2, nBitsNote) - 1;
        masque = effectuerDecalageAGauche(masque, calculerDecalage(duree, nBitsNote));
        // Inverser le masque pour avoir uniquement des bits à 1 sauf pour les nBits à écrire
        masque = masque ^ 0xffffffffffffffff;
        // Appliquer le masque pour que la sonnerie garde le même contenu sauf pour les nBits à écrire qui sont maintenant à 0
        sonnerie = sonnerie & masque;
    }
    // TODO: Sinon, afficher un message d'erreur
    else {
        cerr << "La sonnerie ne possede pas de note a retirer." << endl;
    }
}

/**
 * Modifie une note à une position choisie par l'utilisateur
 *
 * \param [in] sonnerie	    La sonnerie à modifier
 */
void modifierNote(uint64_t& sonnerie) {
    // TODO: Si la sonnerie n'est pas vide:
    if (sonnerie >= 0x100000000000000) {
        uint64_t duree = obtenirBitsDeSonnerie(sonnerie, 0, nBitsDuree);
        // TODO: Lire la position et la nouvelle valeur de la note à modifier
        uint64_t position = lireValeurValide("Veuillez entrez la position a modifier", duree);
        cout << "duree" << duree;
        uint64_t note = lireValeurValide("Veuillez entrer la note", nNotes);
        // TODO: Modifier la note dans la sonnerie
        ajouterBitsDansSonnerie(sonnerie, position, note, nBitsNote);
    }
    // TODO: Sinon, afficher un message d'erreur
    else {
        cerr << "La sonnerie ne possede pas de note a modifier." << endl;
    }
}

/**
 * Initialise une portée
 *
 * \param [in] nColonnes    La durée de la sonnerie 
 *
 * \return La portée initialisé
 */
Portee initialiserPortee(uint64_t nColonnes) {
    // TODO: Créer une nouvelle portée ayant nColonnes. Le nombre de lignes de la portée est de taillePortee
    Portee portee{};
    portee.nColonnes = nColonnes;
    portee.portee = new char*[nColonnes];
    // TODO: Allouer le tableau dynamique de la portée
    // TODO: Initialiser une ligne sur deux à des - et les autres lignes à des ' '. La portée doit contenir 5 lignes de - et 4 lignes de ' '.
    for (uint64_t i : range(nColonnes)) {
        portee.portee[i] = new char[taillePortee];
        for (uint64_t j : range(taillePortee)) {
            if (j % 2)
                portee.portee[i][j] = ' ';
            else 
                portee.portee[i][j] = '-';
        }
    }
    return portee;
}

/**
 * Retourne la portée d'une sonnerie
 *
 * \param [in] sonnerie	    La sonnerie à transcrire sur une portée
 *
 * \return La portée de la sonnerie
 */
Portee construirePortee(uint64_t sonnerie) {
    // TODO: Initialiser la portée en fonction de la durée de la sonnerie
    uint64_t duree = obtenirBitsDeSonnerie(sonnerie, 0, nBitsDuree);

    Portee portee = initialiserPortee(duree);
    // TODO: Extraire chaque note de la sonnerie
    uint64_t note = 0;
    for (uint64_t i : range(duree)) {
        note = obtenirBitsDeSonnerie(sonnerie, i + 1, nBitsNote);
        //note = sonnerie << (nBitsDuree + (nBitsDuree * i)) >> (64 - nBitsNote);
        // TODO: Si la note n'est pas 0 (silence), ajouter le caractère 'o' dans la portée à la ligne correspondant à la note  et à la colonne correspondant à la position de la note dans la sonnerie
        //		La note 1 va sur la ligne du bas de la portée et 9 sur la ligne du haut
        if (note != 0) {
            portee.portee[i][nNotes-(note)] = 'o';
        }
    }
    return portee;
}

/**
 * Affiche la portée à l'écran
 *
 * \param [in] portee	    La portée à afficher
 */
void afficherPortee(Portee portee) {
    // TODO: Afficher toutes les cases de la portée
    for (uint64_t i : range(taillePortee)) {
        for (uint64_t j : range(portee.nColonnes)) {
            cout << portee.portee[j][i];
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    // TODO: Créer une nouvelle sonnerie
    // TODO: Afficher le menu à l'infini et appeler la (les) bonne(s) fonction(s) pour chaque option
    uint64_t sonnerie = creerNouvelleSonnerie();
    int option = 0;
    do {
        cout << "Veuillez choisir une option" << endl
            << "1. Ajouter une note a la fin" << endl
            << "2. Enlever une note a la fin" << endl
            << "3. Modifier note" << endl
            << "4. Creer nouvelle sonnerie" << endl
            << "5. Afficher la portee" << endl;
        cin >> option;
        if (option == 1)
            ajouterNote(sonnerie);
        else if (option == 2)
            enleverNote(sonnerie);
        else if (option == 3)
            modifierNote(sonnerie);
        else if (option == 4)
            creerNouvelleSonnerie();
        else if (option == 5)
            afficherPortee(construirePortee(sonnerie));
    } while (option != -1);
}