//////////////////////////////////////////////////////////////////////////////////////////////////////////
// \title       Jouer au prof #2
// \description Programme qui présente un menu permettant de choisir plusieurs fonctions à effectuer
//              telles que l'ajout d'une question à un examen, l'écriture d'un examen et la vérification
//              de si un élève a passé l'examen ou non.
// \file        exo2.cpp
// \author      Marc-André Gosselin (2020217)
// \author      Martin Careau (1978446)
// \date        31/05/2020
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "CodeFourni.hpp"
#include "cppitertools/enumerate.hpp"


//! Methode qui s'assure que réponse choisie est parmi les choix de réponses.
//! \param question             La question qu'il faut ajouter une reponse.
//! \return                     Une string de la reponse.
std::string verificationChoix(Question question)
{
	bool isOk = false;
	std::string reponse;
	gsl::span<std::string> spanChoix(question.choixDeReponses, nbChoixReponses);
	do {
		std::cin >> reponse;
		for (std::string choix : spanChoix) {
			if (choix.rfind(reponse, 0) == 0) {
				isOk = true;
				break;
			}
		}
		if (isOk == false) std::cout << "Entrez une lettre valide parmis les choix de reponse." << std::endl;
	} while (isOk == false);
	return reponse;
}

//! Methode qui cree une nouvelle question par l'utilisateur.
//! \return                     La question cree de l'utilisateur.
Question creerNouvelleQuestion()
{
	Question question{};
	std::cout << "Veuillez entrer la question" << std::endl;
	getline(std::cin.ignore(), question.question);
	gsl::span<std::string> spanChoix(question.choixDeReponses, nbChoixReponses);

	for (auto&& [index, choix] : iter::enumerate(spanChoix)) {
		std::cout << "Veuillez entrer le choix de réponse numero " << index + 1 << std::endl;
		getline(std::cin, choix);
	}
	std::cout << "Veuillez entrer la lettre de la reponse" << std::endl;
	question.reponse = verificationChoix(question);
	return question;
}

//! Methode qui ajoute une question a l'examen.
//! \param examen               L'examen a ajouter la question.
//! \param question             La question a ajouter, si non fourni, appel la fonction pour en creer une.
void ajouterQuestion(Examen& examen, Question question = creerNouvelleQuestion())
{
	if (examen.nQuestions < nbQuestionsMax) {
		examen.questions[examen.nQuestions] = question;
		examen.nQuestions++;
	}
	else {
		std::cerr << "La limite de question est atteinte." << std::endl;
	}
}

//! Methode qui charge un examen a partir d'un fichier.
//! \param nomFichier           Le nom du fichier a lire.
//! \param examen               L'examen a charger.
void lireExamen(const std::string& nomFichier, Examen& examen)
{
	std::ifstream fichier(nomFichier);
	if (fichier) {
		while (!ws(fichier).eof()) {
			Question question{};
			getline(fichier, question.question);
			gsl::span<std::string> spanChoix(question.choixDeReponses, nbChoixReponses);

			for (auto&& [index, choix] : iter::enumerate(spanChoix)) {
				getline(fichier, choix);
			}
			fichier >> question.reponse;
			ajouterQuestion(examen, question);
		}
	}
	else {
		std::cerr << "Le chargement du fichier a echoue." << std::endl;
	}
}

//! Methode qui charge une s'matrice à partir d'un fichier.
//! \param nomFichier           Le nom du fichier a ecrire.
//! \param examen               L'examen a sauvegarder.
void ecrireExamen(const std::string& nomFichier, Examen& examen)
{
	std::ofstream fichier(nomFichier);
	gsl::span<Question> spanQuestion(examen.questions, examen.nQuestions);

	for (auto&& question : spanQuestion) {
		gsl::span<std::string> spanChoix(question.choixDeReponses, nbChoixReponses);
		fichier << question.question << std::endl;
		for (auto&& choix : spanChoix) {
			fichier << choix << std::endl;
		}
		fichier << question.reponse << std::endl;
	}
}

//! Methode qui fait passer l'examen a l'utilisateur.
//! \param examen               L'examen a faire passer.
void passerExamen(Examen& examen)
{
	int note = 0;
	std::string reponses[nbQuestionsMax];
	gsl::span<Question> spanQuestion(examen.questions, examen.nQuestions);
	for (auto&& [index, question] : iter::enumerate(spanQuestion)) {
		gsl::span<std::string> spanChoix(question.choixDeReponses, nbChoixReponses);
		std::cout << std::endl << index + 1 << ". " << question.question << std::endl;
		for (auto&& choix : spanChoix) {
			std::cout << choix << std::endl;
		}
		std::cout << "Entrez votre reponse : ";
		std::cin >> reponses[index];
		if (reponses[index] == question.reponse) {
			note++;
		}
	}
	std::cout << std::endl << "RESULTATS" << std::endl;
	for (auto&& [index, question] : iter::enumerate(spanQuestion)) {
		gsl::span<std::string> spanChoix(question.choixDeReponses, nbChoixReponses);
		std::cout << std::endl << index + 1 << ". " << question.question << std::endl;
		std::cout << "Votre reponse : " << reponses[index] << std::endl
			<< "La reponse : " << question.reponse << std::endl;
	}
	std::cout << std::endl << "Total : "
		<< note << "/" << examen.nQuestions << std::endl;

}

int main() 
{
	std::string nomFichier;
	int option;
	Examen examen{};
	std::cout << "Veuillez entrer le nom de l'examen a modifier : " << std::endl;
	std::cin >> nomFichier;
	lireExamen(nomFichier, examen);
	do {
		std::cout << "Faites votre choix parmi les options suivantes;" << std::endl
			<< "1 - Ajouter une question" << std::endl
			<< "2 - Sauvegarder l'examen" << std::endl
			<< "3 - Passer l'examen" << std::endl
			<< "Entrez une option : ";
		std::cin >> option;
		switch (option)
		{
		case 1: 
			ajouterQuestion(examen);
			break; 
		case 2:
			ecrireExamen(nomFichier, examen);
			break;
		case 3:
			passerExamen(examen);
			break;
		}
	} while (option != -1);
}
