////////////////////////////////////////////////////////////////////////////////
///				ENTETE
////////////////////////////////////////////////////////////////////////////////

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
 * Lit une dimension des morceaux et s'assure qu'elle est valide
 *
 * \param [in] fichier				Le fichier a lire l'entete
 *
 * \return l'entete DIB du fichier donne
 */
EnteteDib lireEnteteFichier(fstream& fichier);


/**
 * Lit les pixels d’une image à partir d’un fichier
 *
 * \param [in] fichier			Le fichier overt en binaire avec l'image
 * \param [in] image		    L'image deja allouee
 */
void lireDonneesImage(fstream& fichier, Image& image);


/**
 * Ecrit les pixels d'une image dans un fichier
 *
 * \param [in] fichier			Le fichier overt en binaire pour l'ecriture
 * \param [in] image		    L'image a ecrire
 */
void ecrireDonneesImage(fstream& fichier, const Image& image);


/**
 * Ecrire une image dans un fichier
 *
 * \param [in] nomFichier		Le nom du fichier image
 * \param [in] image		    L'image a ecrire
 * \param [in] ok               un bool representant le succes de l'opperation
 */
void ecrireImage(const string& nomFichier, const Image& image, bool& ok);


/**
 * Alloue une image avec la hauteur et largeur
 *
 * \param [in] largeur			Largeur de l'image
 * \param [in] hauteur          Hauteur de l'image
 *
 * \return une image alloue ou vide s'il y a eu un echec
 */
Image allouerImage(unsigned largeur, unsigned hauteur);

/**
 * Retire l'allocation de pointeur d'une image
 *
 * \param [in] image				L'image a desallouer
 */
void desallouerImage(Image& image);


/**
 * Lit une image d'un fichier
 *
 * \param [in] nomFichier		Le nom du fichier image
 * \param [in] ok               un bool representant la reussite de l'ouverture
 *
 * \return L'image extraite du fichier
 */
Image lireImage(const string& nomFichier, bool& ok);


/**
 * Extrait un rectangle dans l'image
 *
 * \param [in] image				L'image a extraire un rectangle
 * \param [in] x            		La position en x du coin haut gauche
 * \param [in] y            		La position en y du coin haut gauche
 * \param [in] hauteur      		La hauteur du rectangle
 * \param [in] largeur      		La largeur du rectangle
 *
 * \return le morceau de l'image
 */
Image extraireMorceau(const Image& image, const int x, const int y, const int hauteur, const int largeur);


/**
 * Decompose une image en plusieurs morceaux
 *
 * \param [in] image				L'image a decomposer
 * \param [in] hauteurMorceaux		La hauteur du morceau
 * \param [in] largeurMorceaux		La largeur du morceau
 *
 * \return l'image decomposee en morceaux
 */
ImageDecomposee decomposerImage(const Image& image, const int hauteurMorceaux, const int largeurMorceaux);


/**
 * Melange le tableau de morceaux
 *
 * \param [in] imageDecomposee		Les morceaux a melanger
 *
 * \return les morceaux melange
 */
ImageDecomposee melangerImage(ImageDecomposee imageDecomposee);


/**
 * Crée une image à partir d'une image décomposée
 *
 * \param [in] imageDecomposee		L'image de départ
 *
 * \return l'image recomposée
 */
Image recomposerImage(const ImageDecomposee imageDecomposee);


#pragma endregion //}

#pragma endregion //}

