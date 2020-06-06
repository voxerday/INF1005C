////////////////////////////////////////////////////////////////////////////////
////		ENTETE
////////////////////////////////////////////////////////////////////////////////


#pragma region "Inclusions" //{

#include <ciso646>
#include <cstddef>
#include <cstdint>

#include <fstream>
#include <string>

#include "CodeFourni.hpp"


using namespace std;
#include <iostream>
#pragma endregion //}




#pragma region "Globaux" //{

#pragma region "Fonctions" //{


/**
 * Lit une dimension des morceaux et s'assure qu'elle est valide
 *
 * \param [in] fichier				Le fichier a lire l'entete
 *
 * \return l'entete DIB du fichier donne
 */
EnteteDib lireEnteteFichier ( fstream& fichier )
{
    EnteteDib enteteDib = construireDibVide();
    EnteteBmp enteteBmp = construireBmpVide();

    fichier.seekg(sizeof(enteteBmp), ios::beg);
    fichier.read((char*)&enteteDib, sizeof(enteteDib));

    return enteteDib;
}


/**
 * Lit les pixels d’une image à partir d’un fichier
 *
 * \param [in] fichier			Le fichier overt en binaire avec l'image
 * \param [in] image		    L'image deja allouee
 */
void lireDonneesImage ( fstream& fichier, Image& image )
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
 * Ecrit les pixels d'une image dans un fichier
 *
 * \param [in] fichier			Le fichier overt en binaire pour l'ecriture
 * \param [in] image		    L'image a ecrire
 */
void ecrireDonneesImage ( fstream& fichier, const Image& image )
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
 * Ecrire une image dans un fichier
 *
 * \param [in] nomFichier		Le nom du fichier image
 * \param [in] image		    L'image a ecrire
 * \param [in] ok               un bool representant le succes de l'opperation
 */
void ecrireImage ( const string& nomFichier, const Image& image, bool& ok )
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
 * Alloue une image avec la hauteur et largeur
 *
 * \param [in] largeur			Largeur de l'image
 * \param [in] hauteur          Hauteur de l'image
 *
 * \return une image alloue ou vide s'il y a eu un echec
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
 * \param [in] image				L'image a desallouer
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
 * \param [in] nomFichier		Le nom du fichier image
 * \param [in] ok               un bool representant la reussite de l'ouverture  
 *
 * \return L'image extraite du fichier
 */
Image lireImage ( const string& nomFichier, bool& ok )
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
 * \param [in] image				L'image a extraire un rectangle
 * \param [in] x            		La position en x du coin haut gauche
 * \param [in] y            		La position en y du coin haut gauche
 * \param [in] hauteur      		La hauteur du rectangle
 * \param [in] largeur      		La largeur du rectangle
 *
 * \return le morceau de l'image
 */
Image extraireMorceau ( const Image& image, const int x, const int y, const int hauteur, const int largeur)
{
	// TODO: Allouer une image de la taille du morceau à extraire
    Image morceau = allouerImage(largeur, hauteur);
	// TODO: Copier les pixels du morceau dans l'image.
    morceau.pixels = new Pixel *[hauteur];
    for (int i : range(hauteur)) {
        morceau.pixels[i] = new Pixel[largeur];
        for (int j : range(largeur)) {
            morceau.pixels[i][j] = image.pixels[y * hauteur + i][x * largeur + j];
        }
    }
    return morceau;
}


/**
 * Decompose une image en plusieurs morceaux
 *
 * \param [in] image				L'image a decomposer
 * \param [in] hauteurMorceaux		La hauteur du morceau
 * \param [in] largeurMorceaux		La largeur du morceau
 *
 * \return l'image decomposee en morceaux
 */
ImageDecomposee decomposerImage(const Image& image, const int hauteurMorceaux, const int largeurMorceaux)
{
    ImageDecomposee imageDecomposee{};
	// TODO: Spécifier le nombre de morceaux en x et en y contenus dans l'image
    imageDecomposee.nMorceauxX = image.largeur / largeurMorceaux;
    imageDecomposee.nMorceauxY = image.hauteur / hauteurMorceaux;
	// TODO: Allouer morceaux en fonction du nombre de morceaux en y
    imageDecomposee.morceaux = new Image* [imageDecomposee.nMorceauxY];
	for (int i : range(imageDecomposee.nMorceauxY)) {
		// TODO: Allouer la ligne de morceaux courante en fonction du nombre de morceaux en x
        imageDecomposee.morceaux[i] = new Image[imageDecomposee.nMorceauxX];
		for (int j : range(imageDecomposee.nMorceauxX)) {
			// TODO: Utiliser extraireMorceau pour obtenir une image pour chaque morceau de chaque ligne
            imageDecomposee.morceaux[i][j] = extraireMorceau(image, j,
                i, hauteurMorceaux, largeurMorceaux);
		}
	}
	return imageDecomposee;
}


/**
 * Melange le tableau de morceaux
 *
 * \param [in] imageDecomposee		Les morceaux a melanger
 *
 * \return les morceaux melange
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
 * \return l'image recomposée
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