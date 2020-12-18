#include <stdio.h>   /* pour les entrées-sorties */
#include <string.h>  /* pour les manipulations de chaînes de caractères */
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include "rep.h"

#define VERSION 3.0
#define SQUELET
/**************************************************************************/
/* Compléter votre nom ici                                                */
/*   Nom : NIVEL                   Prénom : Maël                          */
/**************************************************************************/

extern bool modif;


/**********************************************************************/
/*  Ajout d'un contact dans le répertoire stocké en mémoire           */
/**********************************************************************/

int ajouter_un_contact_dans_rep(Repertoire *rep, Enregistrement enr)
{
#ifdef IMPL_TAB
	// compléter code ici pour tableau

	int idx;
	idx = rep->nb_elts;

	if (rep->nb_elts < MAX_ENREG)
	{
		*(rep->tab + idx) = enr;
		rep->nb_elts++;
		modif = true; //Quand on ajoute un contact, on passe modif = true pour pouvoir enregistrer (ou non) les contacts dans le txt

	}
	else {
		return(ERROR);
	}

	
#else
#ifdef IMPL_LIST

	bool inserted = false;
	if (rep->nb_elts == 0) {
		if (InsertElementAt(rep->liste, rep->liste->size, enr) != 0) {
			rep->nb_elts += 1;
			modif = true;
			rep->est_trie = true;
			return(OK);
		}

	}
	else {
		if (InsertElementAt(rep->liste, rep->liste->size, enr) != 0) {
			rep->nb_elts += 1;
			modif = true;
			rep->est_trie = false;
			return(OK);
		}

	}


#endif
	
#endif


	return(OK);

} /* fin ajout */
  /**********************************************************************/
  /* supprime du répertoire l'enregistrement dont l'indice est donné en */
  /*   paramètre       et place modif = true                            */
  /**********************************************************************/
#ifdef IMPL_TAB
void supprimer_un_contact_dans_rep(Repertoire *rep, int indice) {

	// compléter code ici pour tableau
	if (rep->nb_elts >= 1)		/* s'il y a au moins un element ds le tableau */
	{						/* et que l'indice pointe a l'interieur */
		for (int i = indice; i < rep->nb_elts; i++)
		{
			*(rep->tab + i) = *(rep->tab + i + 1);
		}

		rep->nb_elts -= 1;		/* ds ts les cas, il y a un element en moins */
		modif = true;
	}

	return;
} /* fin supprimer */

#else
#ifdef IMPL_LIST
  /************************************************************************/
  /* supprime du répertoire l'enregistrement contenu dans le maillon elem */
  /*                   et fixe modif à vrai                              */
  /************************************************************************/
  // complet

	int supprimer_un_contact_dans_rep_liste(Repertoire *rep, SingleLinkedListElem *elem) {
	
	int ret=DeleteLinkedListElem(rep->liste, elem);
	if (ret == 1) {
		rep->nb_elts--;
		modif = true;
	}

	return (0); 
	}
#endif
#endif


  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement sur une ligne à l'écran  */
  /* ex Dupont, Jean                 0320304050                         */
  /**********************************************************************/
void affichage_enreg(Enregistrement enr)
{
	// code à compléter ici
	printf(" %s, %s                 %s", enr.nom, enr.prenom, enr.tel);

} /* fin affichage_enreg */
  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement avec alignement des mots */
  /* pour les listes                                                    */
  /* ex | Dupont                |Jean                  |0320304050      */
  /**********************************************************************/
void affichage_enreg_frmt(Enregistrement enr)
{
	// code à compléter ici
	// comme fonction affichage_enreg, mais avec présentation alignées des infos

	printf("|%-20s      |%-20s      |%-30s\n", enr.nom, enr.prenom, enr.tel); //On réserve un nombre de caractères pour print le contact (ici 20 ou 30) et on
																			  //l'aligne à gauche du champ (avec le -)
} /* fin affichage_enreg */


  /**********************************************************************/
  /* test si dans l'ordre alphabetique, un enregistrement est apres     */
  /* un autre                                                           */
  /**********************************************************************/
bool est_sup(Enregistrement enr1, Enregistrement enr2)
{
	// code à compléter ici
	// même mot => 0 ; enr1 > enr2 => 1 ; enr2 > enr1 => -1
	if (_strcmpi(enr1.nom, enr2.nom) < 0) { return false; }					//utilisation de la fonction _strcmpi pour comparer les deux noms, puis les prenom si
	else if (_strcmpi(enr1.nom, enr2.nom) > 0) { return true; }				//les noms sont identiques
	else {
		if (_strcmpi(enr1.prenom, enr2.prenom) < 0) { return false; }
		else if (_strcmpi(enr1.prenom, enr2.prenom) > 0) { return true; }
		else { return false; }
	}
}
 
/*********************************************************************/
/*   Tri Alphabetique du tableau d'enregistrements                   */
/*********************************************************************/

void trier(Repertoire *rep)
{

#ifdef IMPL_TAB
	// ajouter code ici pour tableau
	Enregistrement temp;
	int tour = 0;
	if (!rep->nb_elts) { return; }
	do
	{
		tour = 0; //Compteur qui va nous permettre de savoir quand sortir de la boucle. Si tour est toujours à 0 a la fin de la boucle for : le repertoire est trié
		for (int i = 0; i < rep->nb_elts - 1; i++) // Pour chaque element du repertoire,
		{
			if (est_sup(*(rep->tab + i), *(rep->tab + i + 1))) //on test si il y'a besoin d'inverser, si oui
			{
				temp = *(rep->tab + i); //on inverse
				*(rep->tab + i) = *(rep->tab + (i + 1));
				*(rep->tab + (i + 1)) = temp;
				tour++; //et a chaque modification : +1
			}
		}
	} while (tour != 0); //Si tour = 0 -> Liste trié -> On sort de la boucle


	
#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
	// rien à faire !
	// la liste est toujours triée
#endif
#endif


	rep->est_trie = true;

} /* fin trier */

  /**********************************************************************/
  /* recherche dans le répertoire d'un enregistrement correspondant au  */
  /*   nom à partir de l'indice ind                                     */
  /*   retourne l'indice de l'enregistrement correspondant au critère ou*/
  /*   un entier négatif si la recherche est négative				    */
  /**********************************************************************/

int rechercher_nom(Repertoire *rep, char nom[], int ind)
{
	int i = ind;		    /* position (indice) de début de recherche dans tableau/liste rep */
	int ind_fin;			/* position (indice) de fin de tableau/liste rep */

	char tmp_nom[MAX_NOM];	/* 2 variables temporaires dans lesquelles */
	char tmp_nom2[MAX_NOM];	/* on place la chaine recherchee et la chaine lue dans le */
							/* tableau, afin de les convertir en majuscules et les comparer */
	bool trouve = false;		


#ifdef IMPL_TAB
							// ajouter code ici pour tableau
	ind_fin = rep->nb_elts;
	strcpy_s(tmp_nom, _countof(tmp_nom), nom); //Copie du nom a rechercher dans tmp_nom
	_strupr_s(tmp_nom, _countof(tmp_nom)); //Passage en maj de tmp_nom pour ne pas les prendre en compte dans la recherche
	while (trouve == false)
	{
		for (int i = 0; i < ind_fin; i++)
		{
			strcpy_s(tmp_nom2, _countof(tmp_nom2), rep->tab[i].nom); //Copie de l'element i dans tmp_nom2
			_strupr_s(tmp_nom2, _countof(tmp_nom2)); //Passage en maj de tmp_nom2

			if (strcmp(tmp_nom,tmp_nom2) == 0) //Si les deux char sont égaux, on return true
			{
				trouve = true;
				return i;
			}
		}
		return -1;
	}

	
#else
#ifdef IMPL_LIST
							// ajouter code ici pour Liste
	ind_fin = rep->nb_elts;
	strcpy_s(tmp_nom, _countof(tmp_nom), nom); //Copie du nom a rechercher dans tmp_nom
	_strupr_s(tmp_nom, _countof(tmp_nom)); //Passage en maj de tmp_nom pour ne pas les prendre en compte dans la recherche
	while (trouve == false)
	{
		for (int i = 0; i < ind_fin; i++)
		{
			strcpy_s(tmp_nom2, _countof(tmp_nom2), GetElementAt(rep->liste, i)->pers.nom); //Copie de l'element i dans tmp_nom2
			_strupr_s(tmp_nom2, _countof(tmp_nom2)); //Passage en maj de tmp_nom2

			if (strcmp(tmp_nom, tmp_nom2) == 0) //Si les deux char sont égaux, on return true
			{
				trouve = true;
				return i;
			}
		}
		return -1;
	}
	
#endif
#endif

	return((trouve) ? i : -1);
} /* fin rechercher_nom */

  /*********************************************************************/
  /* Supprimer tous les caracteres non numériques de la chaines        */
  /*********************************************************************/
void compact(char *s)
{
	// compléter code ici
	int size = strlen(s); //Taille du num
	int i = 0;
		while(s[i]!= '\0') { //Tant que nous ne sommes pas arrivés a la fin de la liste on test si le digit est un nombre
			if (isdigit(s[i]) == 0) { //S'il n'en est pas un
				for (int j = i; s[j + 1] != '\0'; j++) {//On décale les elements vers la gauche
					s[j] = s[j + 1];
				}
				s[size - 1] = '\0'; //On diminue la taille de la liste
				size--;
			}
			else ++i;
		}
	return;
}

/**********************************************************************/
/* sauvegarde le répertoire dans le fichier dont le nom est passé en  */
/* argument                                                           */
/* retourne OK si la sauvegarde a fonctionné ou ERROR sinon           */

/**********************************************************************/
int sauvegarder(Repertoire *rep, char nom_fichier[])
{
	FILE *Fic_rep;					/* le fichier */
	errno_t err;
	char buffer[sizeof(Enregistrement) + 1]; //Création du buffer qui va contenir les informations
#ifdef IMPL_TAB
	err = fopen_s(&Fic_rep, nom_fichier, "w"); 
	if (err != 0 || Fic_rep == NULL) { return ERROR; } //Verification de l'existance et de la bonne ouverture du fichier
	for (int i = 0; i < rep->nb_elts; i++) 
	{
		sprintf_s(buffer, sizeof(buffer),"%s%c%s%c%s\n",rep->tab[i].nom, SEPARATEUR, rep->tab[i].prenom, SEPARATEUR, rep->tab[i].tel); //Stock la serie de caractères dans le buffer
		fputs(buffer, Fic_rep); //On print le buffer dans le txt
	}
	if (feof(Fic_rep)) { 
		fclose(Fic_rep); //on ferme le fichier
	}

	// ajouter code ici pour tableau

	
#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
	err = fopen_s(&Fic_rep, nom_fichier, "w");
	if (err != 0 || Fic_rep == NULL) { return ERROR; } //Verification de l'existance et de la bonne ouverture du fichier
	for (int i = 0; i < rep->nb_elts; i++)
	{
		sprintf_s(buffer, sizeof(buffer), "%s%c%s%c%s\n", GetElementAt(rep->liste, i)->pers.nom, SEPARATEUR, GetElementAt(rep->liste, i)->pers.prenom, SEPARATEUR, GetElementAt(rep->liste, i)->pers.tel); //Stock la serie de caractères dans le buffer
		fputs(buffer, Fic_rep); //On print le buffer dans le txt
	}
	if (feof(Fic_rep)) {
		fclose(Fic_rep); //on ferme le fichier
	}
#endif
#endif

	return(OK);
} /* fin sauvegarder */


  /**********************************************************************/
  /*   charge dans le répertoire le contenu du fichier dont le nom est  */
  /*   passé en argument                                                */
  /*   retourne OK si le chargement a fonctionné et ERROR sinon         */
  /**********************************************************************/

int charger(Repertoire *rep, char nom_fichier[])
{
	FILE *fic_rep;					/* le fichier */
	errno_t err;
	int num_rec = 0;						/* index sur enregistrements */
	int long_max_rec = sizeof(Enregistrement);
	char buffer[sizeof(Enregistrement) + 1];
	int idx = 0;

	char *char_nw_line;
	
	_set_errno(0);
	if ( ((err = fopen_s(&fic_rep, nom_fichier, "r")) != 0) || (fic_rep == NULL) )
	{
		return(err);
	}
	else
	{
		while (!feof(fic_rep) && (rep->nb_elts < MAX_ENREG))
		{
			if (fgets(buffer, long_max_rec, fic_rep) != NULL)
			{
				/* memorisation de l'enregistrement lu dans le tableau */
				buffer[long_max_rec] = 0;			/* en principe il y a deja un fin_de_chaine, cf fgets */

				if ((char_nw_line = strchr(buffer, '\n')) != NULL)
					*char_nw_line = '\0';			/* suppression du fin_de_ligne eventuel */

				idx = 0;								/* analyse depuis le debut de la ligne */
#ifdef IMPL_TAB
				if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							/* on saute le separateur */
					if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].tel, MAX_TEL, SEPARATEUR) == OK)
							num_rec++;		/* element à priori correct, on le comptabilise */
					}
				}
#else
#ifdef IMPL_LIST
				Enregistrement enr;
				if (lire_champ_suivant(buffer, &idx, enr.nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							/* on saute le separateur */
					if (lire_champ_suivant(buffer, &idx, enr.prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, enr.tel, MAX_TEL, SEPARATEUR) == OK)
							//ajouter_un_contact_dans_rep(rep, enr);
							InsertElementAt(rep->liste, rep->liste->size, enr);

							num_rec++;		/* element à priori correct, on le comptabilise */

					}
				}									// ajouter code implemention liste

#endif
#endif




			}

		}
		rep->nb_elts = num_rec;
		fclose(fic_rep);
		return(OK);
	}


} /* fin charger */
