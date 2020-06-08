//////////////////////////////////////////////////////////////////////////////////////////////////////
// \title       Travail dirigé no 5
// \description Programme qui accomplit plusieurs fonctions sur une image BMP telles que lire 
//              les entêtes BMP et DIB d'un fichier, lire les données de l'image, les écrire, 
//              allouer l'image, la désallouer, extraire des morceaux de l'image, décomposer l'image,
//              la mélanger et la recomposer.
// \file        CodeDemande.cpp
// \author      Marc-André Gosselin (2020217)
// \author      Martin Careau (1978446)
// \date        09/06/2020
//////////////////////////////////////////////////////////////////////////////////////////////////////


#pragma region "Inclusions" //{

#include <ciso646>
#include <cstddef>
#include <cstdint>

#include <fstream>
#include <string>

#include "CodeFourni.hpp"


using namespace std;

#pragma endregion //}




#pragma region "Globaux" //{

#pragma region "Fonctions" //{


/**
 * Lit les entêtes BMP et DIB d'un fichier donné.
 *
 * \param [in] fichier				Le fichier à lire l'entête
 *
 * \return l'entête DIB du fichier donné
 */
EnteteDib lireEnteteFichier(fstream& fichier)
{
	// TODO: Lire l'entête DIB du fichier donné.
	EnteteDib enteteDib = construireDibVide();
	EnteteBmp enteteBmp = construireBmpVide();

	fichier.seekg(sizeof(enteteBmp), ios::beg);
	fichier.read((char*)&enteteDib, sizeof(enteteDib));

	return enteteDib;
}


/**
 * Lit les pixels d’une image à partir d’un fichier binaire
 *
 * \param [in] fichier			Le fichier ouvert en binaire qui contient l'image
 * \param [in] image		    L'image deja allouée
 *
 * \return Rien
 */
void lireDonneesImage(fstream& fichier, Image& image)
{
	// TODO: Se positionner au début du tableau de pixels dans le fichier.
	EnteteDib enteteDib = construireDibVide();
	EnteteBmp enteteBmp = construireBmpVide();
	fichier.seekg(sizeof(enteteBmp) + sizeof(enteteDib), ios::beg);
	// TODO: Pour chaque ligne de l'image, lire la ligne et sauter le padding.
	unsigned padding = calculerTaillePadding(image);
	for (int hauteur : range(image.hauteur)) {
		for (int largeur : range(image.largeur)) {
			Pixel pixel{};
			fichier.read((char*)&pixel, sizeof(pixel));
			image.pixels[hauteur][largeur] = pixel;
		}
		fichier.seekg(padding, ios::cur);
	}
}


/**
 * Écrit les pixels d'une image dans un fichier binaire
 *
 * \param [in] fichier			Le fichier ouvert en binaire pour l'écriture
 * \param [in] image		    L'image à écrire
 *
 * \return Rien
 */
void ecrireDonneesImage(fstream& fichier, const Image& image)
{
	// TODO: Se positionner au début du tableau de pixels dans le fichier (après
	//       les entêtes).
	EnteteDib enteteDib = construireDibVide();
	EnteteBmp enteteBmp = construireBmpVide();
	fichier.seekg(sizeof(enteteBmp) + sizeof(enteteDib), ios::beg);
	// TODO: Pour chaque ligne de l'image, écrire la ligne puis écrire des bytes
	//       à zéro pour le padding.
	int zero = 0;
	unsigned padding = calculerTaillePadding(image);
	for (int hauteur : range(image.hauteur)) {
		for (int largeur : range(image.largeur)) {
			Pixel pixel = image.pixels[hauteur][largeur];
			fichier.write((char*)&pixel, sizeof(pixel));
		}
		fichier.write((char*)&zero, padding);
	}
}


/**
 * Écrire une image dans un fichier binaire
 *
 * \param [in] nomFichier		Le nom du fichier image à ouvrir en écriture binaire
 * \param [in] image		    L'image à écrire
 * \param [in] ok               Un bool représentant le succès de l'opération
 *
 * \return Rien
 */
void ecrireImage(const string& nomFichier, const Image& image, bool& ok)
{
	// TODO: Ouvrir un fichier en écriture binaire.
	fstream fichier(nomFichier, ios::out | ios::binary);
	// Si l'ouverture n'a pas échouée :
	ok = !fichier.fail();
	if (ok == true) {
		fichier.seekp(0, ios::beg);
		// TODO: Construire les entêtes à partir de l'image.
		EnteteBmp enteteBmp = construireEnteteBmp(image);
		EnteteDib enteteDib = construireEnteteDib(image);
		// TODO: Écrire les entêtes dans le fichier.
		fichier.write((char*)&enteteBmp, sizeof(enteteBmp));
		fichier.write((char*)&enteteDib, sizeof(enteteDib));
		// TODO: Écrire les données (pixels) de l'image dans le fichier.
		ecrireDonneesImage(fichier, image);
	}
}


/**
 * Alloue avec un pointeur une image selon la hauteur et la largeur
 *
 * \param [in] largeur			Largeur de l'image
 * \param [in] hauteur          Hauteur de l'image
 *
 * \return Une image allouée ou vide (s'il y a eu un échec)
 */
Image allouerImage(unsigned largeur, unsigned hauteur)
{
	Image image{};
	// Si la largeur ET la hauteur ne sont pas nulles :
	if (largeur != 0 && hauteur != 0) {
		// TODO: Affecter les dimensions à l'image.
		image.hauteur = hauteur;
		image.largeur = largeur;
		// TODO: Allouer un tableau dynamique de pixels pour l'image.
		//       On veut Image::hauteur de lignes qui ont chacune
		//       Image::largeur de pixels.
		image.pixels = new Pixel * [hauteur];
		for (int i : range(hauteur)) {
			image.pixels[i] = new Pixel[largeur];
		}
	}
	return image;
}


/**
 * Retire l'allocation de pointeur d'une image
 *
 * \param [in] image				L'image à désallouer
 *
 * \return Rien
 */
void desallouerImage(Image& image)
{
	// Si le tableau dynamique de l'image n'est pas nul :
	if (image.pixels != nullptr) {
		// TODO: Désallouer le tableau 2D.
		for (int i : range(image.hauteur)) {
			delete image.pixels[i];
		}
		delete image.pixels;
		image.pixels = 0;
	}
}


/**
 * Lit une image d'un fichier
 *
 * \param [in] nomFichier		Le nom du fichier image à ouvrir en lecture binaire
 * \param [in] ok               Un bool représentant la réussite (ou non) de l'ouverture
 *
 * \return L'image extraite du fichier
 */
Image lireImage(const string& nomFichier, bool& ok)
{
	// TODO: Ouvrir le fichier en lecture binaire.
	fstream fichier(nomFichier, ios::in | ios::binary);
	Image image{};
	ok = !fichier.fail();
	// Si l'ouverture n'a pas échouée :
	if (ok == true) {
		// TODO: Lire l'entête DIB.
		EnteteDib enteteDib = lireEnteteFichier(fichier);
		// TODO: Allouer une image selon le contenu du DIB.
		image = allouerImage(enteteDib.largeurImage, enteteDib.hauteurImage);
		// TODO: Lire les pixels du fichier.
		lireDonneesImage(fichier, image);
	}
	return image;
}


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
Image extraireMorceau(const Image& image, const int x, const int y, const int hauteur, const int largeur)
{
	// TODO: Allouer une image de la taille du morceau à extraire
	Image morceau = allouerImage(largeur, hauteur);
	// TODO: Copier les pixels du morceau dans l'image.
	for (int i : range(hauteur)) {
		for (int j : range(largeur)) {
			morceau.pixels[i][j] = image.pixels[y + i][x + j];
		}
	}
	return morceau;
}


/**
 * Décompose une image en plusieurs morceaux
 *
 * \param [in] image				L'image à décomposer
 * \param [in] hauteurMorceaux		La hauteur du morceau
 * \param [in] largeurMorceaux		La largeur du morceau
 *
 * \return L'image décomposée en morceaux
 */
ImageDecomposee decomposerImage(const Image& image, const int hauteurMorceaux, const int largeurMorceaux)
{
	ImageDecomposee imageDecomposee{};
	// TODO: Spécifier le nombre de morceaux en x et en y contenus dans l'image
	imageDecomposee.nMorceauxX = image.largeur / largeurMorceaux;
	imageDecomposee.nMorceauxY = image.hauteur / hauteurMorceaux;
	// TODO: Allouer morceaux en fonction du nombre de morceaux en y
	imageDecomposee.morceaux = new Image * [imageDecomposee.nMorceauxY];
	for (int i : range(imageDecomposee.nMorceauxY)) {
		// TODO: Allouer la ligne de morceaux courante en fonction du nombre de morceaux en x
		imageDecomposee.morceaux[i] = new Image[imageDecomposee.nMorceauxX];
		for (int j : range(imageDecomposee.nMorceauxX)) {
			// TODO: Utiliser extraireMorceau pour obtenir une image pour chaque morceau de chaque ligne
			imageDecomposee.morceaux[i][j] = extraireMorceau(image, j * largeurMorceaux,
				i * hauteurMorceaux, hauteurMorceaux, largeurMorceaux);
		}
	}
	return imageDecomposee;
}


/**
 * Mélange le tableau de morceaux
 *
 * \param [in] imageDecomposee		Les morceaux à mélanger
 *
 * \return Les morceaux mélangés
 */
ImageDecomposee melangerImage(ImageDecomposee imageDecomposee)
{
	Image morceauTemp{};
	int x, y;
	for (int i : range(imageDecomposee.nMorceauxY)) {
		for (int j : range(imageDecomposee.nMorceauxX)) {
			// Inverser le morceau courant avec un morceau choisi au hasard
			morceauTemp = imageDecomposee.morceaux[i][j];
			x = rand() % imageDecomposee.nMorceauxX;
			y = rand() % imageDecomposee.nMorceauxY;
			imageDecomposee.morceaux[i][j] = imageDecomposee.morceaux[y][x];
			imageDecomposee.morceaux[y][x] = morceauTemp;
		}
	}
	return imageDecomposee;
}


/**
 * Crée une image à partir d'une image décomposée
 *
 * \param [in] imageDecomposee		L'image de départ
 *
 * \return L'image recomposée
 */
Image recomposerImage(const ImageDecomposee imageDecomposee)
{
	Image image;
	int largeurMorceau = imageDecomposee.morceaux[0][0].largeur;
	int hauteurMorceau = imageDecomposee.morceaux[0][0].hauteur;
	int blocX, blocY, y, x;
	// TODO: Allouer l'image
	image = allouerImage(largeurMorceau * imageDecomposee.nMorceauxX,
		hauteurMorceau * imageDecomposee.nMorceauxY);
	for (int i : range(image.hauteur)) {
		blocY = i / hauteurMorceau;
		y = i - blocY * hauteurMorceau;
		for (int j : range(image.largeur)) {
			// TODO: Copier le pixel correspondant du morceau dans l'image
			blocX = j / largeurMorceau;
			x = j - blocX * largeurMorceau;
			image.pixels[i][j] = imageDecomposee.morceaux[blocY][blocX].pixels[y][x];
		}
	}
	return image;
}

#pragma endregion //}

#pragma endregion //}