// CarShop.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "console.h"
#include<iostream>
#include<fstream>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include <iomanip>
#include<windows.h>
#include <string>

using namespace std;
namespace con = JadedHoboConsole;

enum varianta {
	da = 1, nu = 0
};

char comerciantNumeIntrodus[255];
char comerciantParolaIntrodusa[255];
char adminNumeIntrodus[255];
char adminParolaIntrodusa[255];
int tipCont;
int m, n;
int counter;
int costTotal = 0;
bool cumparaturiTerminate = false;

struct masini
{
	char marca[255];
	char tip[255];
	unsigned int kilometriiTotali, anFabricatie, pret, id;


};
ofstream trimiteMasinaCatreDB("db_order_list.txt");
int produseCumparate=0;
string ** matrix;
int locatiaProdusului=-1;
string **matriceProduseCumparate;
void intoarcereLaMeniulPrincipal();
void coeficientCalitate()
{
	
	float minCalitate = 0;
	float maxCalitate = 0;
	float raportCalitate1;
	float raportCalitate2;
	
	float pret1, pret2, an1, an2, km1, km2;
	for (m = 0; m < 10; m++)
	{
		
		if (matrix[m][2] == matrix[counter][2]) {
			km1 = stoi(matrix[m][3]);
			km2 = stoi(matrix[counter][3]);
			an1 = stoi(matrix[m][4]);
			an2 = stoi(matrix[counter][4]);
			pret1 = stoi(matrix[m][5]);
			pret2 = stoi(matrix[counter][5]);

			raportCalitate1 = 2.0f / (km1 + pret1) + 1.0 / an1;
			raportCalitate2 = 2.0f / (km2 + pret2) + 1.0 / an2;
			if (raportCalitate1 > raportCalitate2) {
				if (raportCalitate1 > minCalitate) {
					minCalitate = raportCalitate1;
					locatiaProdusului = m;
				}

			}
			else
				if (raportCalitate2 > minCalitate) {
					minCalitate = raportCalitate2;
					locatiaProdusului = m;
				}

				
			
				

		}
	
		
		
	}
}
void initial()
{
	system("color 82");
	ofstream clearer("db_order_list.txt");
	clearer.clear();
	clearer.close();
	
	
}
bool verificareCompercializant()
{
	struct comerciant
	{
		char nume[255];
		char parola[255];
	}comerciantDB;
	ifstream citireComerciant("db_comercianti.txt");
	citireComerciant >> comerciantDB.nume >> comerciantDB.parola;

	
	if (comerciantNumeIntrodus == comerciantDB.nume&&comerciantParolaIntrodusa == comerciantDB.parola)
	{
		return true;
	}
	else
	{
		return false;
	}


}
bool verificareAdministrator()
{
	struct administrator
	{
		char nume[255];
		char parola[255];
	}adminDB;
	ifstream citireAdmin("db_admins.txt");
	citireAdmin >> adminDB.nume >> adminDB.parola;
	
	
	if (adminNumeIntrodus == adminDB.nume&&adminParolaIntrodusa == adminDB.parola)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void selectareTipCont()
{
	
	
	 //Implicit se acorda cont de cumparator
	system("cls");
	cout << "                                   |     Car Deals SRL    |                 " << endl;
	cout << "________________________________________________________________________________________________________________________" << endl;
	cout << "Selectati tipul de cont dorit";
	cout << "________________________________________________________________________________________________________________________" << endl;
	cout << "1. Cumparator"<<endl;
	cout << "2. Vanzator"<<endl;
	cout << "3. Administrator"<<endl;
	cin >> tipCont;
	
	switch (tipCont)
	{
	case 1:
	{ofstream scriereCont("db_tip_cont_selectat.txt");
	scriereCont.clear();
	scriereCont << tipCont;
	scriereCont.close();
	intoarcereLaMeniulPrincipal();
	break;
	}
	case 2:
	{ system("cls");
	cout << "Logati-va"<<endl;
	cout << "Nume :" << endl;
	cin.get(comerciantNumeIntrodus, 255);
	cout << "Parola:" << endl;
	cin.get(comerciantParolaIntrodusa, 255);

		if (verificareCompercializant() == true) {
		ofstream scriereCont("db_tip_cont_selectat.txt");
		scriereCont.clear();
		scriereCont << tipCont;
		scriereCont.close();
		intoarcereLaMeniulPrincipal();
	}
		break;
	}
	case 3:
	{  system("cls");
	cout << "Logati-va"<<endl;
	cout << "Nume:" << endl;
	cin >> adminNumeIntrodus;
		cout << "Parola :" << endl;
		cin >> adminParolaIntrodusa;	
		if (verificareAdministrator() == true) {
		ofstream scriereCont("db_tip_cont_selectat.txt");
		scriereCont.clear();
		scriereCont << tipCont;
		scriereCont.close();
		intoarcereLaMeniulPrincipal();
	}
		break;
	}


	}
	
}
void afisareProduseCumparate()
{
	int i, j;
	for (i = 0; i < produseCumparate; i++)
	{
		for (j = 0; j < 5; j++)
			cout << con::fg_green << setw(15) << matrix[i][j] << " ";
		cout << endl;
	}
}
void afisareMatrice()
{
	int i, j;
	for (i = 0; i < 10; i++)
	{
		if (i == locatiaProdusului) {
		
			for (j = 0; j < 6; j++)
				cout <<con::fg_red<< setw(15) << matrix[i][j] << " ";
			cout << endl;
		}
		
		else
		{
			for (j=0; j < 6; j++)
			cout <<con::fg_green<< setw(15) << matrix[i][j] << " ";
			cout << endl;
     	}
	}
		cout << "\n\n";
	

}
void magazin()
{
	int l, g;
	int meniuMagazin,idSelectat;
	char modelDorit[255];
	
	system("cls");
	ifstream citireProduse("db_shop_list.txt");
	ifstream citireNrTotalProduse("db_items_in_shop.txt");
	int nrTotalProduse;
	citireNrTotalProduse >> nrTotalProduse;
	
	ifstream dbProduse("db_shop_list.txt");
	masini masina[100];
	
	for (int i = 0; i < nrTotalProduse; i++)
	{
		
		dbProduse >>masina[i].id>> masina[i].marca >> masina[i].tip >> masina[i].kilometriiTotali >> masina[i].anFabricatie >> masina[i].pret;
	}
	
	
	cout << "                                        Lista produse                                          " << endl;
	cout << "________________________________________________________________________________________________________________________" << endl;
	cout << "              ID    MARCA    TIP    Kilometraj    Anul de Fabricatie    Pret    "<<endl;
	for (l = 0; l < 10; l++)
	{
		for (g = 0; g < 6; g++)
		{
			citireProduse >> matrix[l][g];
		}
	}
	/*
	for (int i = 0; i < nrTotalProduse; i++)
	{
		cout << masina[i].id <<setw(2)<< " " << masina[i].marca << setw(2) << " " << masina[i].tip << setw(2) << " " << masina[i].kilometriiTotali << setw(2) << " " << masina[i].anFabricatie << setw(2) << " " << masina[i].pret << setw(2) <<"\n";
		
	}
	*/
	afisareMatrice();
	cout << "________________________________________________________________________________________________________________________" << endl;
	cout << "Meniu: "<<endl;
	cout << "1-Achizitie" << endl;
	cout << "2-Cea mai buna oferta" << endl;
	cout << "3-Intoarce-te la meniul principal"<<endl;
	cout << "Alegeti o optiune :";
	cin >> meniuMagazin;
	switch (meniuMagazin)
	{
	case 1: {
		cout << "Introduceti ID-ul produsului: ";
		cin >> idSelectat;
		
		for (int i = 0; i < nrTotalProduse; i++)
		{
			if (masina[i].id == idSelectat)
			{
				
				trimiteMasinaCatreDB << masina[i].marca << " " << masina[i].tip << " " << masina[i].kilometriiTotali << " " << masina[i].anFabricatie << " " << masina[i].pret << endl;
				produseCumparate++;
				system("cls");
				magazin();
			}
		}
		
		break; }

	case 2:
	{
		cout << "introduceti modelul dorit" << endl;
		cin >> modelDorit;
		for(m=0;m<10;m++)
			if (matrix[m][2] == modelDorit)
			{
				counter = m;
				break;
			}
		coeficientCalitate();
		intoarcereLaMeniulPrincipal();
		break;
	}

	case 3: {
		cumparaturiTerminate = true;
		intoarcereLaMeniulPrincipal();
		break;


	}
	}
	
	
}
void cosProduse()
{
	system("cls");
	int a, b;
	
	ifstream getProduseFromDB("db_order_list.txt");
	masini masiniCumparate[100];
	for (int i = 0; i < produseCumparate; i++)
	{
		getProduseFromDB  >> masiniCumparate[i].marca >> masiniCumparate[i].tip >> masiniCumparate[i].kilometriiTotali >> masiniCumparate[i].anFabricatie >> masiniCumparate[i].pret;
	}
	cout << "________________________________________________________________________________________________________________________" << endl;
	for (int i = 0; i < produseCumparate; i++)
		costTotal += masiniCumparate[i].pret;
	afisareProduseCumparate();
	cout << "________________________________________________________________________________________________________________________" << endl;
	cout << "Cost Total ="<<costTotal<<endl;
	cout << "Confirmati comanda?";
	cout << "0/1:\n";
	int var;
	cin >> var;
	switch (var)
	{
	case 1:
		system("cls");
		cout << "Comanda facuta cu succes";
		getch();
		intoarcereLaMeniulPrincipal();
		break;
		case 0:
		system("cls");
		cout << "Comanda anulata cu succes";
		getch();
		intoarcereLaMeniulPrincipal();
	default:
		cout << "ati introdus o valoare gresita";
		break;
	}


	


}
void meniuPornire()
{
	int optiuneMeniu;
	cout << "                                   |     Car Deals SRL    |                 " << endl;
	cout << "________________________________________________________________________________________________________________________" << endl;
	cout << "                                         Bine ati venit la magazinul nostru                                             " << endl;
	cout << "                                         Selectati o optiune din meniul principal                                       " << endl;
	cout << "________________________________________________________________________________________________________________________" << endl;
	cout << " 1. Deschideti Magazinul" << endl;
	cout << " 2. Selectati tipul contului" << endl;
	cout << " 3. Vezi produsele cumparate" << endl;
	cin >> optiuneMeniu;
	switch (optiuneMeniu)
	{
	case 1:magazin();
		break;
	case 2:
		selectareTipCont();
		break;
	case 3:cosProduse();
	
		break;

		

		
	}
	if (cumparaturiTerminate)
	{
		matriceProduseCumparate = new string *[produseCumparate];
		for (int i = 0; i < produseCumparate; i++)
		{
			matriceProduseCumparate[i] = new string[6];
		}
	}
	
}
void intoarcereLaMeniulPrincipal()
{
	system("cls");
	meniuPornire();
}




int main()
{
	matrix = new string*[10];
	for (int i = 0; i < 10; i++)
	{
		matrix[i] = new string[6];
	}
	matriceProduseCumparate = new string *[produseCumparate];
	for (int i = 0; i < produseCumparate; i++)
	{
		matriceProduseCumparate[i] = new string[5];
	}

	initial();
	meniuPornire();
	
	
	getch();
	system("pause");
	
	trimiteMasinaCatreDB.close();
    return 0;
}

