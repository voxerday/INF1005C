//////////////////////////////////////////////////////////////////////////////////////////////////////
// \title       Travail dirig� no 5
// \description Programme qui accomplit plusieurs fonctions sur une image BMP telles que lire 
//              les ent�tes BMP et DIB d'un fichier, lire les donn�es de l'image, les �crire, 
//              allouer l'image, la d�sallouer, extraire des morceaux de l'image, d�composer l'image,
//              la m�langer et la recomposer.
// \file        CodeDemande.cpp
// \author      Marc-Andr� Gosselin (2020217)
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
 * Lit les ent�tes BMP et DIB d'un fichier donn�.
 *
 * \param [in] fichier				Le fichier � lire l'ent�te
 *
 * \return l'ent�te DIB du fichier donn�
 */
EnteteDib lireEnteteFichier(fstream& fichier)
{
	// TODO: Lire l'ent�te DIB du fichier donn�.
	EnteteDib enteteDib = construireDibVide();
	EnteteBmp enteteBmp = construireBmpVide();

	fichier.seekg(sizeof(enteteBmp), ios::beg);
	fichier.read((char*)&enteteDib, sizeof(enteteDib));

	return enteteDib;
}


/**
 * Lit les pixels d�une image � partir d�un fichier binaire
 *
 * \param [in] fichier			Le fichier ouvert en binaire qui contient l'image
 * \param [in] image		    L'image deja allou�e
 *
 * \return Rien
 */
void lireDonneesImage(fstream& fichier, Image& image)
{
	// TODO: Se positionner au d�but du tableau de pixels dans le fichier.
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
 * �crit les pixels d'une image dans un fichier binaire
 *
 * \param [in] fichier			Le fichier ouvert en binaire pour l'�criture
 * \param [in] image		    L'image � �crire
 *
 * \return Rien
 */
void ecrireDonneesImage(fstream& fichier, const Image& image)
{
	// TODO: Se positionner au d�but du tableau de pixels dans le fichier (apr�s
	//       les ent�tes).
	EnteteDib enteteDib = construireDibVide();
	EnteteBmp enteteBmp = construireBmpVide();
	fichier.seekg(sizeof(enteteBmp) + sizeof(enteteDib), ios::beg);
	// TODO: Pour chaque ligne de l'image, �crire la ligne puis �crire des bytes
	//       � z�ro pour le padding.
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
 * �crire une image dans un fichier binaire
 *
 * \param [in] nomFichier		Le nom du fichier image � ouvrir en �criture binaire
 * \param [in] image		    L'image � �crire
 * \param [in] ok               Un bool repr�sentant le succ�s de l'op�ration
 *
 * \return Rien
 */
void ecrireImage(const string& nomFichier, const Image& image, bool& ok)
{
	// TODO: Ouvrir un fichier en �criture binaire.
	fstream fichier(nomFichier, ios::out | ios::binary);
	// Si l'ouverture n'a pas �chou�e :
	ok = !fichier.fail();
	if (ok == true) {
		fichier.seekp(0, ios::beg);
		// TODO: Construire les ent�tes � partir de l'image.
		EnteteBmp enteteBmp = construireEnteteBmp(image);
		EnteteDib enteteDib = construireEnteteDib(image);
		// TODO: �crire les ent�tes dans le fichier.
		fichier.write((char*)&enteteBmp, sizeof(enteteBmp));
		fichier.write((char*)&enteteDib, sizeof(enteteDib));
		// TODO: �crire les donn�es (pixels) de l'image dans le fichier.
		ecrireDonneesImage(fichier, image);
	}
}


/**
 * Alloue avec un pointeur une image selon la hauteur et la largeur
 *
 * \param [in] largeur			Largeur de l'image
 * \param [in] hauteur          Hauteur de l'image
 *
 * \return Une image allou�e ou vide (s'il y a eu un �chec)
 */
Image allouerImage(unsigned largeur, unsigned hauteur)
{
	Image image{};
	// Si la largeur ET la hauteur ne sont pas nulles :
	if (largeur != 0 && hauteur != 0) {
		// TODO: Affecter les dimensions � l'image.
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
 * \param [in] image				L'image � d�sallouer
 *
 * \return Rien
 */
void desallouerImage(Image& image)
{
	// Si le tableau dynamique de l'image n'est pas nul :
	if (image.pixels != nullptr) {
		// TODO: D�sallouer le tableau 2D.
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
 * \param [in] nomFichier		Le nom du fichier image � ouvrir en lecture binaire
 * \param [in] ok               Un bool repr�sentant la r�ussite (ou non) de l'ouverture
 *
 * \return L'image extraite du fichier
 */
Image lireImage(const string& nomFichier, bool& ok)
{
	// TODO: Ouvrir le fichier en lecture binaire.
	fstream fichier(nomFichier, ios::in | ios::binary);
	Image image{};
	ok = !fichier.fail();
	// Si l'ouverture n'a pas �chou�e :
	if (ok == true) {
		// TODO: Lire l'ent�te DIB.
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
 * \param [in] image				L'image � extraire un rectangle
 * \param [in] x            		La position en x du coin haut gauche de l'image
 * \param [in] y            		La position en y du coin haut gauche de l'image
 * \param [in] hauteur      		La hauteur du rectangle
 * \param [in] largeur      		La largeur du rectangle
 *
 * \return Le morceau de l'image
 */
Image extraireMorceau(const Image& image, const int x, const int y, const int hauteur, const int largeur)
{
	// TODO: Allouer une image de la taille du morceau � extraire
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
 * D�compose une image en plusieurs morceaux
 *
 * \param [in] image				L'image � d�composer
 * \param [in] hauteurMorceaux		La hauteur du morceau
 * \param [in] largeurMorceaux		La largeur du morceau
 *
 * \return L'image d�compos�e en morceaux
 */
ImageDecomposee decomposerImage(const Image& image, const int hauteurMorceaux, const int largeurMorceaux)
{
	ImageDecomposee imageDecomposee{};
	// TODO: Sp�cifier le nombre de morceaux en x et en y contenus dans l'image
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
 * M�lange le tableau de morceaux
 *
 * \param [in] imageDecomposee		Les morceaux � m�langer
 *
 * \return Les morceaux m�lang�s
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
 * Cr�e une image � partir d'une image d�compos�e
 *
 * \param [in] imageDecomposee		L'image de d�part
 *
 * \return L'image recompos�e
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