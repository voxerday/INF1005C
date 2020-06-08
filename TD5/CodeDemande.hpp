//////////////////////////////////////////////////////////////////////////////////////////////////////
// \title       Travail dirigé no 5
// \description Déclaration de toutes les fonctions écrites dans CodeDemande.cpp
// \file        CodeDemande.hpp
// \author      Marc-André Gosselin (2020217)
// \author      Martin Careau (1978446)
// \date        09/06/2020
//////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once


#pragma region "Inclusions" //{

#include <ciso646>
#include <cstddef>
#include <cstdint>

#include <fstream>
#include <string>

#include "CodeFourni.hpp"


using namespace std;

#pragma endregion //}




#pragma region "Déclarations" //{

#pragma region "Globaux" //{

//TODO Les déclarations de vos fonctions vont ici

/**
 * Lit les entêtes BMP et DIB d'un fichier donné.
 *
 * \param [in] fichier				Le fichier à lire l'entête
 *
 * \return l'entête DIB du fichier donné
 */
EnteteDib lireEnteteFichier(fstream& fichier);


/**
 * Lit les pixels d’une image à partir d’un fichier binaire
 *
 * \param [in] fichier			Le fichier ouvert en binaire qui contient l'image
 * \param [in] image		    L'image deja allouée
 *
 * \return Rien
 */
void lireDonneesImage(fstream& fichier, Image& image);


/**
 * Écrit les pixels d'une image dans un fichier binaire
 *
 * \param [in] fichier			Le fichier ouvert en binaire pour l'écriture
 * \param [in] image		    L'image à écrire
 *
 * \return Rien
 */
void ecrireDonneesImage(fstream& fichier, const Image& image);


/**
 * Écrire une image dans un fichier binaire
 *
 * \param [in] nomFichier		Le nom du fichier image à ouvrir en écriture binaire
 * \param [in] image		    L'image à écrire
 * \param [in] ok               Un bool représentant le succès de l'opération
 *
 * \return Rien
 */
void ecrireImage(const string& nomFichier, const Image& image, bool& ok);


/**
 * Alloue avec un pointeur une image selon la hauteur et la largeur
 *
 * \param [in] largeur			Largeur de l'image
 * \param [in] hauteur          Hauteur de l'image
 *
 * \return Une image allouée ou vide (s'il y a eu un échec)
 */
Image allouerImage(unsigned largeur, unsigned hauteur);

/**
 * Retire l'allocation de pointeur d'une image
 *
 * \param [in] image				L'image à désallouer
 *
 * \return Rien
 */
void desallouerImage(Image& image);


/**
 * Lit une image d'un fichier
 *
 * \param [in] nomFichier		Le nom du fichier image à ouvrir en lecture binaire
 * \param [in] ok               Un bool représentant la réussite (ou non) de l'ouverture
 *
 * \return L'image extraite du fichier
 */
Image lireImage(const string& nomFichier, bool& ok);


/**
 * Extrait un rectangle dans l'image
 *
 * \param [in] image				L'image à extraire un rectangle
 * \param [in] x            		La position en x du coin haut gauche de l'image
 * \param [in] y            		La position en y du coin haut gauche de l'image
 * \param [in] hauteur      		La hauteur du rectangle
 * \param [in] largeur      		La largeur du rectangle
 *
 * \return Le morceau de l'image
 */
Image extraireMorceau(const Image& image, const int x, const int y, const int hauteur, const int largeur);


/**
 * Décompose une image en plusieurs morceaux
 *
 * \param [in] image				L'image à décomposer
 * \param [in] hauteurMorceaux		La hauteur du morceau
 * \param [in] largeurMorceaux		La largeur du morceau
 *
 * \return L'image décomposée en morceaux
 */
ImageDecomposee decomposerImage(const Image& image, const int hauteurMorceaux, const int largeurMorceaux);


/**
 * Mélange le tableau de morceaux
 *
 * \param [in] imageDecomposee		Les morceaux à mélanger
 *
 * \return Les morceaux mélangés
 */
ImageDecomposee melangerImage(ImageDecomposee imageDecomposee);


/**
 * Crée une image à partir d'une image décomposée
 *
 * \param [in] imageDecomposee		L'image de départ
 *
 * \return L'image recomposée
 */
Image recomposerImage(const ImageDecomposee imageDecomposee);

#pragma endregion //}

#pragma endregion //}

