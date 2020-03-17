#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <list>
#include <iterator>
#include <stdio.h>
#include "unit_class.hpp"
#include "mycrypto.hpp"
#include "Kuznyechik.hpp"
#include "converterofmystupidity.hpp"

using namespace std;

//Gets encryption method and string
//encrypts string and return back encrypted version of string
string encryptString(CFB_Mode<Kuznyechik>& samp, string temp)
{
	ByteBlock mesage;
	ByteBlock result;
	mesage = hex_to_bytes(temp);
	samp.encrypt(mesage, result);
	return hex_representation(result);
		
}

//Gets encryption method and string
//decrypt string and return back decrypted version of string
string decryptString(CFB_Mode<Kuznyechik> & samp, string temp)
{
	ByteBlock mesage;
	ByteBlock result;
	mesage = hex_to_bytes(temp);
	samp.decrypt(mesage, result);
	return hex_representation(result);
}

int main()
{	
	setlocale(LC_ALL, "Russian");
	string input, keyFileLocation, dataFileLocation;
	ByteBlock key;
	ByteBlock iv;
	ByteBlock msg;
	ByteBlock result;
	list <unit_t> unitList;
	list <unit_t> ::iterator iterUnit;
	bool keyIn = false;
	L2:
	cout << endl << "Введите место расположения файла ключа:" << endl;
	getline(cin, keyFileLocation);
	ifstream keyInput(keyFileLocation);
	if (!keyInput)
	{
		cerr << "Файл ключа не открывается!" << endl;
		goto L2;
	}
	string inputT1, inputT2;
	getline(keyInput,  inputT1);
	key = hex_to_bytes(inputT1);
	inputT2 = inputT1;
	getline(keyInput, inputT1);
	iv = hex_to_bytes(inputT1);
	if (inputT1.length() == 0 || inputT2.length() == 0)
	{
		cerr << "Ключ отсутствует!" << endl;
		goto L2;
	}
	cout << endl << "Введите место расположения файла данных:" << endl;
	getline(cin, dataFileLocation);
	keyIn = true;
	bool newFileInCheck = false;
	CFB_Mode<Kuznyechik> encryptor(Kuznyechik(key), iv);
	cout << "Программа готова к работе, вводите команды:" << endl;
	getline(cin, input);
	while ((input != "quit") && (input != "q"))
	{
		
		if (input == "open data file")
		{
			string dataFileLocationTemp = dataFileLocation;
			if (newFileInCheck == true)
			{
				cout << "Введите путь нового файла: " << endl;
				getline(cin, dataFileLocationTemp);
			}
			ifstream dataInput(dataFileLocationTemp);
			if (keyIn == false)
			{
				cerr << "Файл ключа не введен!" << endl;
				break;
			}
			if (!dataInput)
			{
				cerr << "Файл данных не открывается!" << endl;
				break;
			}

			string tempN = "<empty>",tempM = "<empty>",tempP = "<empty>",
				tempD = "<empty>",tempL = "<empty>",tempMY = "<empty>";
			while (dataInput)
			{
				getline(dataInput, tempN);
				getline(dataInput, tempM);
				getline(dataInput, tempP);
				getline(dataInput, tempD);
				getline(dataInput, tempL);
				if ((tempM == "" || tempP == "") && (unitList.begin() == unitList.end()))
				{
					cerr << "Ошибка ввода данных, отсутствуют ключевые элементы";
					break;
				}
					
				if (tempN == "" || tempM == "" || tempP == "" || tempD == "" || tempL == "")
					break;

				tempN = decryptString(encryptor, tempN);
				ConverterOtT tN(tempN,1);
				tempN = tN.convertBack();
				tempM = decryptString(encryptor, tempM);
				ConverterOtT tM(tempM, 1);
				tempM = tM.convertBack();
				tempP = decryptString(encryptor, tempP);
				ConverterOtT tP(tempP, 1);
				tempP = tP.convertBack();
				tempD = decryptString(encryptor, tempD);
				ConverterOtT tD(tempD, 1);
				tempD = tD.convertBack();
				tempL = decryptString(encryptor, tempL);
				ConverterOtT tL(tempL, 1);
				tempL = tL.convertBack();

				unit_t temp1(tempN, tempM, tempP, tempD, tempL);
				unitList.push_back(temp1);
			}
			newFileInCheck = true;
			
		}

		if (input == "add new mail")
		{
			string tempN, tempM, tempP, tempD, tempL;
			cout << endl << "Введите название почты: " << endl;
			getline(cin, tempN);
			cout << endl << "Введите адресс почты: " << endl;
			getline(cin, tempM);
			cout << endl << "Введите пароль почты: " << endl;
			getline(cin, tempP);
			cout << endl << "Введите описание почты: " << endl;
			getline(cin, tempD);
			cout << endl << "Введите ссылку на почту: " << endl;
			getline(cin, tempL);



			unit_t temp1(tempN, tempM, tempP, tempD, tempL);
			unitList.push_back(temp1);

		}

		if (input == "remove mail")
		{
			string searchM;
			cout << endl << "Введите адрес почты для которого будет произведено удаление:" << endl;
			getline(cin, searchM);
			bool greatSuccess = false;
			for (iterUnit = unitList.begin(); iterUnit != unitList.end(); iterUnit++)
			{
				if (iterUnit->mail_() == searchM)
				{
					greatSuccess = true;
					break;
				}
			}
			if (greatSuccess == false)
				cerr << "Такой почты не найдено";
			else
			{
				unitList.erase(iterUnit);
			}
		}

		if (input == "output by mail")
		{
			string searchM;
			cout << endl << "Введите адрес почты для которого будет произведен вывод:" << endl;
			getline(cin, searchM);
			bool greatSuccess = false;
			for (iterUnit = unitList.begin(); iterUnit != unitList.end(); iterUnit++)
			{
				if (iterUnit->mail_() == searchM)
				{
					greatSuccess = true;
					break;
				}
			}
			if (greatSuccess == false)
				cerr << "Такой почты не найдено";
			else
			{
				iterUnit->unitOutput(cout);
			}
		}

		if (input == "output by name")
		{
			string searchN;
			cout << endl << "Введите название почты для которогой будет произведен вывод:" << endl;
			getline(cin, searchN);
			bool greatSuccess = false;
			for (iterUnit = unitList.begin(); iterUnit != unitList.end(); iterUnit++)
			{
				if (iterUnit->name_() == searchN)
				{
					greatSuccess = true;
					break;
				}
			}
			if (greatSuccess == false)
				cerr << "Такого названия не найдено";
			else
			{
				iterUnit->unitOutput(cout);
			}
		}


		if (input == "generate new password")
		{
			string searchM;
			cout << endl << "Введите адрес почты для которого будет произведена замена:" << endl;
			getline(cin, searchM);
			bool greatSuccess = false;
			for (iterUnit = unitList.begin(); iterUnit != unitList.end(); iterUnit++)
			{
				if (iterUnit->mail_() == searchM)
				{
					greatSuccess = true;
					break;
				}
			}
			if (greatSuccess == false)
				cerr << "Такой почты не найдено";
			else
			{
				cout << endl << "Желаете ввести пароль самостоятельно? Y/n" << endl;
				string c;
				getline(cin, c);
				if (c == "Y" || c == "y")
				{
					string passInput;
					cout << endl << "Вводите пароль:" << endl;
					getline(cin, passInput);
					iterUnit->pass_() = passInput;
				}
				else
				{
					string addSym;
					bool onlyNumbers = false;
					cout << endl << "Введите доп символы для пароля:" << endl;
					getline(cin, addSym);
					cout << endl << "Убрать буквы из пароля? Y/n" << endl;
					getline(cin, c);
					int a;
					cout << endl << "Введите длину пароля:" << endl;
					cin >> a;

					if (c == "Y" || c == "y")
					{
						onlyNumbers = true;
					}
					iterUnit->generatePassword(a, addSym, onlyNumbers);
				}

			}
			
		}

		if (input == "output")
		{
			for (iterUnit = unitList.begin(); iterUnit != unitList.end(); iterUnit++)
			{
				iterUnit->unitOutput(cout);
			}
		}
		getline(cin, input);
	}

	ofstream kek1(dataFileLocation);
	ofstream kek2(keyFileLocation);
	if (!kek1)
	{
		cerr << "Файл данных не открывается!" << endl;
		goto L2;
	}
	string tempN, tempM, tempP, tempD, tempL, tempMY;
	for (iterUnit = unitList.begin(); iterUnit != unitList.end(); iterUnit++)
	{
		tempN = iterUnit->name_();
		tempM = iterUnit->mail_();
		tempP = iterUnit->pass_();
		tempD = iterUnit->desc_();
		tempL = iterUnit->link_();

		ConverterOtT teN(tempN, 0);
		tempN = teN.convertTo();
		tempN = encryptString(encryptor, tempN);
		ConverterOtT teM(tempM, 0);
		tempM = teM.convertTo();
		tempM = encryptString(encryptor, tempM);
		ConverterOtT teP(tempP, 0);
		tempP = teP.convertTo();
		tempP = encryptString(encryptor, tempP);
		ConverterOtT teD(tempD, 0);
		tempD = teD.convertTo();
		tempD = encryptString(encryptor, tempD);
		ConverterOtT teL(tempL, 0);
		tempL = teL.convertTo();
		tempL = encryptString(encryptor, tempL);


		kek1 << tempN << endl << tempM << endl << tempP << endl << tempD << endl << tempL << endl;
	}
	kek2 << hex_representation(key) << endl << hex_representation(iv) << endl;
	

return 0;


}

