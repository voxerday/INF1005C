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
	EnteteDib enteteDib = construireDibVide();
	EnteteBmp enteteBmp = construireBmpVide();
	fichier.seekg(sizeof(enteteBmp) + sizeof(enteteDib), ios::beg);

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
	EnteteDib enteteDib = construireDibVide();
	EnteteBmp enteteBmp = construireBmpVide();
	fichier.seekg(sizeof(enteteBmp) + sizeof(enteteDib), ios::beg);

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
	fstream fichier(nomFichier, ios::out | ios::binary);

	ok = !fichier.fail();
	if (ok == true) {
		fichier.seekp(0, ios::beg);

		EnteteBmp enteteBmp = construireEnteteBmp(image);
		EnteteDib enteteDib = construireEnteteDib(image);

		fichier.write((char*)&enteteBmp, sizeof(enteteBmp));
		fichier.write((char*)&enteteDib, sizeof(enteteDib));

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

	if (largeur != 0 && hauteur != 0) {

		image.hauteur = hauteur;
		image.largeur = largeur;

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
	if (image.pixels != nullptr) {

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
	fstream fichier(nomFichier, ios::in | ios::binary);
	Image image{};
	ok = !fichier.fail();

	if (ok == true) {

		EnteteDib enteteDib = lireEnteteFichier(fichier);

		image = allouerImage(enteteDib.largeurImage, enteteDib.hauteurImage);

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
	Image morceau = allouerImage(largeur, hauteur);

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

	imageDecomposee.nMorceauxX = image.largeur / largeurMorceaux;
	imageDecomposee.nMorceauxY = image.hauteur / hauteurMorceaux;

	imageDecomposee.morceaux = new Image * [imageDecomposee.nMorceauxY];
	for (int i : range(imageDecomposee.nMorceauxY)) {

		imageDecomposee.morceaux[i] = new Image[imageDecomposee.nMorceauxX];
		for (int j : range(imageDecomposee.nMorceauxX)) {

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

	image = allouerImage(largeurMorceau * imageDecomposee.nMorceauxX,
		hauteurMorceau * imageDecomposee.nMorceauxY);
	for (int i : range(image.hauteur)) {
		blocY = i / hauteurMorceau;
		y = i - blocY * hauteurMorceau;
		for (int j : range(image.largeur)) {

			blocX = j / largeurMorceau;
			x = j - blocX * largeurMorceau;
			image.pixels[i][j] = imageDecomposee.morceaux[blocY][blocX].pixels[y][x];
		}
	}
	return image;
}

#pragma endregion //}

#pragma endregion //}