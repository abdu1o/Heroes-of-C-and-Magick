#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <cmath>
#pragma comment(lib, "winmm.lib")
using namespace std;


//MUSIC========================================================
DWORD WINAPI Music_Menu(void* param)
{
	PlaySoundA("menu_music.WAV", NULL, SND_NODEFAULT | SND_ASYNC);
	return 0;
}
DWORD WINAPI Music_Game(void* param)
{
	PlaySoundA("bg_music.WAV", NULL, SND_ASYNC | SND_LOOP);
	return 0;
}
DWORD WINAPI Print(void* param)
{
	PlaySoundA("print.WAV", NULL, SND_ASYNC | SND_NODEFAULT);
	return 0;
}
DWORD WINAPI Music_Dragon(void* param)
{
	PlaySoundA("dragon.WAV", NULL, SND_ASYNC | SND_LOOP);
	return 0;
}
DWORD WINAPI Button(void* param)
{
	PlaySoundA("button.WAV", NULL, SND_NODEFAULT | SND_ASYNC);
	return 0;
}
DWORD WINAPI Adios(void* param)
{
	PlaySoundA("adios.WAV", NULL, SND_NODEFAULT | SND_ASYNC);
	return 0;
}
DWORD WINAPI Dragon_Death(void* param)
{
	PlaySoundA("dragon_death.WAV", NULL, SND_NODEFAULT | SND_ASYNC);
	return 0;
}
DWORD WINAPI YOU_DIED(void* param)
{
	PlaySoundA("YOU DIED.WAV", NULL, SND_NODEFAULT | SND_ASYNC);
	return 0;
}
//=============================================================


//RANDOM NUMBER================================================
int RandomNumber(int min, int max)
{
	srand(time(NULL));

	int num = min + rand() % (max - min + 1);
	return num;
}
//=============================================================


//PLAYER STATS=================================================
int max_hp = 120;
int hp = max_hp;

int max_mana = 100;
int mana = max_mana;

int lvl = 1;
int xp = 0;
int max_xp = 100;

int dmg = 25;

int magick_dmg = 30;

int armor = 4;
//=============================================================


//DRAGON STATS=================================================
int drag_hp = 500;
int drag_dmg = 100;
int drag_magick_dmg = 200;
//=============================================================


//FUNCTIONS====================================================
void LvlUP();
void Menu();
void Stats();
void Fight();
void DragonFight();
void Choice();
void Intro();
void Thx();
void Dragon();
//=============================================================

int day = 1;

void Choice()
{
	CreateThread(0, 0, Music_Game, 0, 0, 0);
	int choice;

	while (true)
	{
		if (day % 15 == 0)
		{
			system("cls");
			cout << "Every day the dragon becomes stronger! \nHis health is increased: " << drag_hp << "-->" << drag_hp + 50 << "\n";
			drag_hp += 50;
			system("pause");
		}

		system("cls");
		cout << "Day " << day;
		cout << "\nWhere are you going to go? \n\n";
		cout << " Arena=- [1] \n Dragon=- [2] \n Stats=- [3] \n Exit menu=- [4] \n";
		cout << "\n-=====--=====--=====-\n";
		cin >> choice;

		if (choice == 1)
		{
			string arena = "In arena, you can fight, thereby increasing your level, \nin order to defeat the dragon in the future...\n";

			for (int i = 0; i < arena.length(); i++)
			{
				Sleep(30);
				cout << arena[i];
			}
			day += 1;
			system("pause\n");
			Fight();
		}
		else if (choice == 2)
		{
			string drag1 = "So.....\n";

			for (int i = 0; i < drag1.length(); i++)
			{
				Sleep(50);
				cout << drag1[i];
			}
			Sleep(1500);
			string drag2 = "The fight begins!\n";

			for (int i = 0; i < drag2.length(); i++)
			{
				Sleep(50);
				cout << drag2[i];
			}
			system("pause");
			DragonFight();
		}
		else if (choice == 3)
		{
			Stats();
			system("pause");
			system("cls");
		}
		else if (choice == 4)
		{
			Menu();
		}
		else
		{
			system("cls");
			Choice();
		}
	}
}

void Stats()
{
	system("cls");

	cout << "-==-Stats-==-\n";
	cout << "-== LvL " << lvl << " ==-\n";
	cout << "-== Hp " << max_hp << " ==-\n";
	cout << "-== Mana " << max_mana << " ==-\n";
	cout << "-== Dmg " << dmg << " ==-\n";
	cout << "-== Magick dmg " << magick_dmg << " ==-\n";
	cout << "-== Armor " << armor << " ==-\n";

	system("pause");
	system("cls");
	Choice();
}

void DragonFight()
{
	CreateThread(0, 0, Music_Dragon, 0, 0, 0);
	system("cls");
	Dragon();

BeginFight:
	while (drag_hp >= 0 && hp >= 0)
	{
		int fight;
		
		cout << "\n\n-=====--=====--=====-\n";
		cout << "\n[1] - Attack \n[2] - Charge attack \n[3] - Magick attack \n";
		cout << "\n-=====--=====--=====-\n";
		cin >> fight;

		if (fight == 1)
		{
			drag_hp -= dmg;
		}
		else if (fight == 2)
		{
			drag_hp -= dmg * 2;
			hp -= (dmg / 2) - armor;
		}
		else if (fight == 3)
		{
			if (mana > 30)
			{
				drag_hp -= magick_dmg;
				mana -= 30;
			}
			else if (mana < 30)
			{
				cout << "You can not cast magick!\n";
				goto BeginFight;
			}
		}
		else
		{
			goto BeginFight;
		}

		cout << "Dragon attacking!\n";
		int drag_attack = RandomNumber(1, 10);

		if (drag_attack == 4)
		{
			cout << "Dragon deal " << drag_magick_dmg << " sacred damage to you\n";
			hp -= drag_magick_dmg;

			cout << "Enemy hp " << drag_hp << "\n";
			cout << "Your hp " << hp << "\n";
			cout << "Your mana " << mana << "\n";
		}
		else
		{
			cout << "Dragon deal " << drag_dmg << " damage to you\n";
			hp -= drag_dmg - armor;

			cout << "Enemy hp " << drag_hp << "\n";
			cout << "Your hp " << hp << "\n";
			cout << "Your mana " << mana << "\n";
		}
	}
	if (drag_hp <= 0)
	{
		CreateThread(0, 0, Dragon_Death, 0, 0, 0);
		Sleep(7000);

		system("cls");
		string fin_txt = "And yes, it did. \nThe universal dragon has been defeated and now not only New Londo, \nbut the whole world can sleep peacefully... \n";
		for (int i = 0; i < fin_txt.length(); i++)
		{
			Sleep(50);
			cout << fin_txt[i];

		}
		drag_hp = 500;
		hp += max_hp - hp;
		mana += max_mana - mana;
		day = 1;
		system("pause");
		Thx();
	}
	else
	{
		CreateThread(0, 0, YOU_DIED, 0, 0, 0);
		Sleep(8000);

		system("cls");
		string fin_txt = "Good job, Ashen one, but it's not enough, \nbecause the dragon has become even closer to the destruction of the kingdom...\nSo rise up and fight again!\n\n";
		for (int i = 0; i < fin_txt.length(); i++)
		{
			Sleep(50);
			cout << fin_txt[i];
		}
		cout << "-" << xp << " xp\n";
		drag_hp = 500;
		hp += max_hp - hp;
		mana += max_mana - mana;
		xp -= xp;
		day++;
		system("pause");
		CreateThread(0, 0, Music_Game, 0, 0, 0);
	}
}

void Thx()
{
	system("cls");
	string thx = "\nThanks for playing this game!\n";
	for (int i = 0; i < thx.length(); i++)
	{
		Sleep(50);
		cout << thx[i];
	}
	system("pause");
	Menu();
}

void Fight()
{
	system("cls");

	//ENEMY STATS==================================================
	int hp_enemy_max = RandomNumber(70, 210);
	int hp_enemy = hp_enemy_max;
	int dmg_enemy = RandomNumber(15, 30);
	//=============================================================

	cout << "Time to fight!\n";
BeginFight:
	while (hp_enemy >= 0 && hp >= 0)
	{
		int fight;
		cout << "-=====--=====--=====-\n";
		cout << "\n[1] - Attack \n[2] - Charge attack \n[3] - Magick attack \n";
		cout << "\n-=====--=====--=====-\n";
		cin >> fight;

		if (fight == 1)
		{
			hp_enemy -= dmg;
		}
		else if (fight == 2)
		{
			hp_enemy -= dmg * 2;
			hp -= (dmg / 2) - armor;
		}
		else if (fight == 3)
		{
			if (mana > 30)
			{
				hp_enemy -= magick_dmg;
				mana -= 30;
			}
			else if (mana < 30)
			{
				cout << "You can not cast magick!\n";
				goto BeginFight;
			}
		}
		else
		{
			goto BeginFight;
		}

		cout << "Enemy deal " << dmg_enemy << " damage to you\n";
		hp -= dmg_enemy - armor;

		cout << "Enemy hp " << hp_enemy << "\n";
		cout << "Your hp " << hp << "\n";
		cout << "Your mana " << mana << "\n";
	}

	if (hp_enemy <= 0)
	{
		system("cls");
		cout << "YOU WIN!\n";
		cout << "+" << hp_enemy_max / 2 << " xp \n";
		xp += hp_enemy_max / 2 + 10;
		hp += max_hp - hp;
		mana += max_mana - mana;

		if (xp >= max_xp)
		{
			cout << "Level UP! \n";
			system("pause");
			LvlUP();
		}
		system("pause");
	}

	else if (hp <= 0)
	{
		system("cls");
		cout << "YOU DIED\n";
		if (xp < 25)
		{
			cout << "-" << 0 << " xp \n";
			hp += max_hp - hp;
			mana += max_mana - mana;
			system("pause");
		}
		else
		{
			cout << "-" << 25 << " xp \n";
			xp -= 25;
			hp += max_hp - hp;
			mana += max_mana - mana;
			system("pause");
		}

	}

}

void LvlUP()
{
	system("cls");
	lvl += 1;
	xp -= max_xp;
	max_xp += 20;

	int choice;
	cout << "-=====--=====--=====-\n";
	cout << "You have one upgrade point \n Choose what to improve \n\n [1] - Health points (+25) \n [2] - Melee damage (+15) \n [3] - Mana points (+15) \n [4] - Magick damage (+10) \n [5] - Armor points (+7)\n";
	cout << "\n-=====--=====--=====-\n";
	cin >> choice;

	if (choice == 1)
	{
		int old_max_hp = max_hp;
		max_hp += 25;
		hp = max_hp;
		cout << "Congratulations! \n" << old_max_hp << " --> " << max_hp << " hp\n";
	}
	else if (choice == 2)
	{
		int old_dmg = dmg;
		dmg += 15;
		cout << "Congratulations! \n" << old_dmg << " --> " << dmg << " damage\n";;
	}
	else if (choice == 3)
	{
		int old_max_mana = max_mana;
		max_mana += 15;
		mana = max_mana;
		cout << "Congratulations! \n" << old_max_mana << " --> " << max_mana << " mana\n";;
	}
	else if (choice == 4)
	{
		int old_magick_dmg = magick_dmg;
		magick_dmg += 10;
		cout << "Congratulations! \n" << old_magick_dmg << " --> " << magick_dmg << " magick damage\n";;
	}
	else if (choice == 5)
	{
		int old_armor = armor;
		armor += 7;
		cout << "Congratulations! \n" << old_armor << " --> " << armor << " armor\n";;
	}
}

void Intro()
{
	CreateThread(0, 0, Print, 0, 0, 0);

	string intro = "An old horror has settled in the New Londor. \nThe silver dragon Ilat is once again terrorizing the capital, and only you, \nchosen undead, can stop him...\n";

	for (int i = 0; i < intro.length(); i++)
	{
		Sleep(91);
		cout << intro[i];
	}

	system("pause\n");

	system("cls");
	Choice();
}

void Menu()
{
	system("cls");
	CreateThread(0, 0, Music_Menu, 0, 0, 0);

	int choice;
	cout << "-=====--=====--=====-\n";
	cout << "\nStart=- [1] \nAuthor=- [2] \nExit=- [3] \n";
	cout << "\n-=====--=====--=====-\n";
	cin >> choice;

	switch (choice)
	{
	case(1):
		system("cls");
		CreateThread(0, 0, Button, 0, 0, 0);
		Sleep(4000);
		Intro();
		break;

	case(2):
		system("cls");
		system("start https://github.com/abdu1o");
		Menu();
		break;

	case(3):
		system("cls");
		cout << "Support my patreon ~ abdu1o\n";
		CreateThread(0, 0, Adios, 0, 0, 0);
		Sleep(2000);
		exit(1);
		break;

	default:
		system("cls");
		Menu();
		break;
	}

}

int main()
{
	system("title Heroes of C++ and Magic");
	Menu();
}

void Dragon()
{
		cout << "\n_______________________________________________________.d888*`___\n";
		cout << "_________________________________________________, d888* `_______\n";
		cout << "_______________________________________________, d888`__________ \n";
		cout << "_____________________________________________, d888`____________ \n";
		cout << "____________________________________________, d88`______________ \n";
		cout << "__________________________________________, d88`________________ \n";
		cout << "_________________________________________, d8`__________________ \n";
		cout << "_______________________________________, d8* ____________________\n";
		cout << "_____________________________________, d88* _____________..d** `_\n";
		cout << "___________________________________, d88`_________..d8* `________\n";
		cout << "_________________________________, d888`____..d8P* ` ____________\n";
		cout << "_________________________._____, d8888 * 8888 * `________________\n";
		cout << "_______________________, * _____, 88888 * 8P * __________________\n";
		cout << "_____________________, * ______d888888 * 8b._____________________\n";
		cout << "___________________, P_______dP__ * 888. * 888b._________________\n";
		cout << "_________________, 8 * ________8____ * 888__`* * 88888b._________\n";
		cout << "_______________, dP________________ * 88___________ * 8 8b.______\n";
		cout << "______________d8`__________________*8b_______________ * 8b.______\n";
		cout << "____________, d8`____________________*8.__________________ * 88b.\n";
		cout << "___________d8P_______________________88._______________________  \n";
		cout << "_________, 88P________________________888_______________________ \n";
		cout << "________d888 * _______.d88P____________888_______________________\n";
		cout << "_______d8888b..d888888 * ______________888_______________________\n";
		cout << "_____, 888888888888888b.______________888_______________________ \n";
		cout << "____, 8 *; 88888P * ****788888888ba.______888____________________\n";
		cout << "___, 8; , 8888 * ________`88888*_________d88 * __________________\n";
		cout << "___)8e888 * __________, 88888be._______888_______________________\n";
		cout << "__, d888`___________,8888888 * **_____d888_______________________\n";
		cout << "_, d88P`___________,8888888Pb._____d888`________________________ \n";
		cout << "_888 * ____________, 88888888 * *___.d8888 * ____________________\n";
		cout << "_`88____________,888888888____.d88888b_________________________  \n";
		cout << "__`P___________,8888888888bd888888 * ____________________________\n";
		cout << "_______________d888888888888d888 * ______________________________\n";
		cout << "_______________8888888888888888b.______________________________  \n";
		cout << "_______________88 * ._ * 88888888888b.________.db________________\n";
		cout << "_______________`888b.`8888888888888b._.d8888P__________________  \n";
		cout << "________________ * *88b.`*8888888888888888888888b... ____________\n";
		cout << "_________________ * 888b.`*8888888888P * **78888888888 88e.______\n";
		cout << "__________________88888b.`* * ******.d8888b * *`88888P * ________\n";
		cout << "__________________`888888b_____.d88888888888 * *`888 8.__________\n";
		cout << "___________________)888888.___d888888888888P___`88 88888b.______ \n";
		cout << "__________________, 88888 * ____d88888888888 * *`____`8 888b_____\n";
		cout << "_________________, 8888 * ____.8888888888P`_________` 888b.______\n";
		cout << "________________, 888 * ______888888888b...__________`888P88b.___\n";
		cout << "_______.db.___, d88* ________88888888888888b_________`8888_______\n";
		cout << "___, d888888b.8888`_________`*888888888888888888P`___`888b._____ \n";
		cout << "__/*****8888b**`______________`***8888P*``8888`_______`8888b.__  \n";
		cout << "_______/**88`_________________.ed8b..__.d888P`__________`8 8888_ \n";
		cout << "____________________________d8**888888888P*_______________`88b_  \n";
		cout << "___________________________(*``,d8888***`________________________\n";
}


