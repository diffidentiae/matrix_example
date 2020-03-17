

#include "unit_class.hpp"

unit_t::unit_t() 
{
	name = "<empty>";
	mail = "<empty>";
	pass = "<empty>";
	desc = "<empty>";
	link = "<empty>";
	oldPass = false;
}

unit_t::unit_t(string nameT, string mailT, string passT, string descT, string linkT)
	{
		name = nameT;
		mail = mailT;
		pass = passT;
		desc = descT;
		link = linkT;
		oldPass = false;
	}

unit_t::unit_t(unit_t const& unitTemp)
	{
		this->name = unitTemp.name_();
		this->mail = unitTemp.mail_();
		this->pass = unitTemp.pass_();
		this->desc = unitTemp.desc_();
		this->link = unitTemp.link_();
		this->oldPass = unitTemp.oldPass_();
	}

unit_t::~unit_t()
	{

	}

unit_t& unit_t::operator =(unit_t const& unitTemp)
	{
		this->name = unitTemp.name_();
		this->mail = unitTemp.mail_();
		this->pass = unitTemp.pass_() ;
		this->desc = unitTemp.desc_();
		this->link = unitTemp.link_();
		this->oldPass = unitTemp.oldPass_();

		return *this;
	}

	string unit_t::name_() const
	{
		return name;
	}

	string unit_t::mail_() const
	{
		return mail;
	}

	string unit_t::pass_()
	{
		return pass;
	}

	string unit_t::pass_() const
	{
		return pass;
	}

	string unit_t::desc_() const
	{
		return desc;
	}

	string unit_t::link_() const
	{
		return link;
	}

	bool unit_t::oldPass_() const
	{
		return oldPass;
	}


	void unit_t::generatePassword(int passLength, string addSymbols, bool onlyNums)
	{
		srand(time(NULL));
		string numbers = "0123456789";
		string letters;
		string lettersUp;
		
		int N = 3;
		int addSymbolsLength = addSymbols.length() - 1;

		if (addSymbols.length() > 0)
			N = 4;

		string passwordTemp;

		bool numbersUsed = false, lettersUsed = false, lettersUpUsed = false, addSymbolsUsed = false;

		if (onlyNums == false)
		{
			letters = "abcdefghijklmnopqrstuvwxyz";
			lettersUp = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		}

		int randPos;

		if (onlyNums == true)
		{
			for (int i = 0; i < passLength; i++)
			{
				randPos = 0 + rand() % 10;
				passwordTemp = passwordTemp + numbers[randPos];
			}
			pass = passwordTemp;
		}
		else
		{
		Leap1:
			for (int i = 0; i < passLength; i++)
			{
				int j = 1 + rand() % N;
				switch (j)
				{
				case 1:
					randPos = 0 + rand() % 10;
					passwordTemp = passwordTemp + numbers[randPos];
					numbersUsed = true;
					break;
				case 2:
					randPos = 0 + rand() % 26;
					passwordTemp = passwordTemp + letters[randPos];
					lettersUsed = true;
					break;
				case 3:
					randPos = 0 + rand() % 26;
					passwordTemp = passwordTemp + lettersUp[randPos];
					lettersUpUsed = true;
					break;
				case 4:
					randPos = 0 + rand() % addSymbolsLength;
					passwordTemp = passwordTemp + addSymbols[randPos];
					addSymbolsUsed = true;
					break;
				default:
					cout << "error while generating pass";
					break;
				}
			}
		
			if (!(numbersUsed == true && lettersUsed == true && lettersUpUsed == true && (addSymbolsUsed == true || N ==3)))
			{
				numbersUsed = false;
				lettersUsed = false;
				lettersUpUsed = false;
				addSymbolsUsed = false;
				passwordTemp.erase();
				goto Leap1;
			}

			pass = passwordTemp;
		
		}
	}

	ostream& unit_t::unitOutput(ostream& stream) const
	{
		stream << endl << "name: " << name << endl;
		if (mail.length() != 0)
			stream << "login: " << mail << endl;
		if (pass.length() != 0)
			stream << "password: " << pass << endl;
		if (desc.length() != 0)
			stream << "description: " << desc << endl;
		if (link.length() != 0)
			stream << "link: " << link << endl;
		if (oldPass == true)
			stream << "time to change password";
		return stream;

	}
