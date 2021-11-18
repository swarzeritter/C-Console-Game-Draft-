﻿#include <iostream>
#include <string>
#include <fstream>

/*
Will do
-Inv system(60%)
-item buffs
-and a lot more
-do normal parry
*/

#define logotype			\
"||============\n\
|| DUELIST alpha 0.4\n\
||\n\
|=> "
using namespace std;

bool auth = false;
int bot_try;
char bot_do;
ofstream save;

string cmd;
int inventory[3][4];
enum invType {
	weapon,
	wear,
	belt
};

enum choice {
	duel,
	inv,
	stats
};

void Dialog(string text) {
	cout << text << endl;
	cout << "\n\nENTER - щоб продовжити" << endl;
	getchar();
	system("cls");
}

void tutorial() {
	Dialog("Привiт гравцю!");
	Dialog("Як ти з назви зрозумiв, ти будешь грати за вiдчайдушного дуелянта, котрий намагатиметься одолати всiх своїх опонентiв!");
	Dialog("Ти напевно спитаєш:\n- А навiщо менi це?");
	Dialog("А я вiдповiм:\n- А хто його знае, бо ця мiнi-гра є бонусним завданням для вступу до спецiальностi :)");
}
enum hands {
	leftArm,
	rightArm
};
enum itemsinfo {
	iid,
	slot,
	secondSlot,
	iHP,
	iDamage,
	iHit,
	iProtect,
	iParry
};
string ItemName[][2] = {
	{"0",		"Пусто"},
	{"1",		"Меч бога"},
	{"2",		"Тестовий квантовий щит"}
};
int Items[][8] = {
	//id		slot		sSlot		iHP			iDMG		iHit		iProt		iParry
	{0,			0,			0,			0,			0,			0,			0,			0},
	{1,			weapon,		rightArm,	10,			11,			20,			13,			25},
	{2,			weapon,		leftArm,	-99,		9999,		7,			-99999,	-99999}

};
class Inv {
public:
	void InventoryUpdate() {
		restorePoints();
		for (int i = 0; i < 3; i++) {
			for (int k = 0; k < 4; k++) {
				int numitem = inventory[i][k];
				calcPoints(Items[numitem][3], Items[numitem][4], Items[numitem][5], Items[numitem][6], Items[numitem][7]);
				if (i == weapon && k == 2) { break; }
			}
		}
	}
	int totalHP(int i) {
		return addHP + i;
	}
	int totalDamage(int i) {
		return addDamage + i;
	}
	int totalHit(int i) {
		return addHit + i;
	}
	int totalProtect(int i) {
		return addProtect + i;
	}
	int totalParry(int i) {
		return addParry	+ i;
	}
	int dropItem() {

	}
private:
	int addHP;
	int addDamage;
	int addHit;
	int addProtect;
	int addParry;
	void restorePoints() {
		addHP = addDamage = addHit = addProtect = addParry = 0;
	}
	void calcPoints(int hp, int dmg, int hit, int protect, int parry) {
		addHP += hp;
		addDamage += dmg;
		addHit += hit;
		addProtect += protect;
		addParry += parry;
	}
};
class Player {
public:
	string name="defaultname";
	int health = 100;
	bool do_chance = false;
	int exp=0;
	int lvl=1;
	int damage = 10;
	int hit=50;
	int protection=50;
	int parry=15;
	int duel_num = 0;

	int newLVL() {
		cout << "======================================\n\
Вiтаємо ви отримали " << lvl << " рiвень персонажа!!\n\
Ви можете покращити одне з умiнь вашого персонажу!\nДля цього введiть\n\
1 - шанс попадання\n\
2 - шанс захисту\n\
3 - шанс парирування\n\n";
		cin >> cmd;
		if (cmd == "1") {
			hit += 2;
			cout << "Ви успiшно прокачали шанс попадання на 2 одиницi" << endl;
		}
		else if (cmd == "2") {
			protection += 2;
			cout << "Ви успiшно прокачали шанс захисту на 2 одиницi" << endl;
		}
		else if (cmd == "3") {
			parry += 2;
			cout << "Ви успiшно прокачали шанс парирування на 2 одиницi" << endl;
		}
		else {
			return newLVL();
		}
		return 0;
	}
	int toNextLVL() {
		if (lvl >= 20) { return 0; }
		int tempExp = 8;
		for (int i = lvl; i > 1; i--) {
			tempExp += 2;
		}
		return tempExp;
	}
	int calcLVL() {
		if (lvl >= 20) { return 0; }
		int tempExp = 8;
		for (int i = lvl; i > 1;i--) {
			tempExp += 2;
		}
		while (exp > tempExp) {
			exp -= tempExp;
			lvl++;
			newLVL();
		}
		return 0;
	}
	int giveRandExp(int i) {
		srand(time(NULL));
		int tempExp=rand()%i+1;
		cout << "[EXP] За цей бiй ви отримали " << tempExp << " досвiду" << endl;
		exp += tempExp;
		return 0;
	}
};


void OnGameInit(int command) {
	Player player, bot;
	ifstream check("save.txt");
	if (!check.is_open()) {
		check.close();
		//
		tutorial();
		cout << "[Creating new profile...]\n";
		cout << "Привiт юний лицарю, назови своє iм'я: " << endl;
		cin >> player.name;
		system("cls");
		save.open("save.txt", ios_base::out);
		save << player.name << endl \
			<< player.exp << endl\
			<< player.lvl << endl\
			<< player.damage << endl\
			<< player.hit << endl\
			<< player.protection << endl\
			<< player.parry << endl\
			<< player.duel_num << endl\
			<< inventory[weapon][0] << endl\
			<< inventory[weapon][1] << endl\
			<< inventory[wear][0] << endl\
			<< inventory[wear][1] << endl\
			<< inventory[wear][2] << endl\
			<< inventory[wear][3] << endl\
			<< inventory[belt][0] << endl\
			<< inventory[belt][1] << endl\
			<< inventory[belt][2] << endl\
			<< inventory[belt][3] << endl;
		save.close();
	}
	check >> player.name \
		>> player.exp \
		>> player.lvl \
		>> player.damage \
		>> player.hit \
		>> player.protection \
		>> player.parry \
		>> player.duel_num\
		>> inventory[weapon][0]\
		>> inventory[weapon][1]\
		>> inventory[wear][0]\
		>> inventory[wear][1]\
		>> inventory[wear][2]\
		>> inventory[wear][3]\
		>> inventory[belt][0]\
		>> inventory[belt][1]\
		>> inventory[belt][2]\
		>> inventory[belt][3];
	check.close();
	Inv owner;
	owner.InventoryUpdate();
	srand(time(NULL));
	switch (command) {
	case duel:
		char duel_cmd;
		player.health = owner.totalHP(player.health);
		system("cls");
		cout << "Бачу ти вже готовий! Твiй супротивник: Бот#" << rand()%100 << endl;
		cout << "Його данi:" << endl\
			<< "LVL: " << bot.lvl << endl\
			<< "DMG: " << bot.damage << endl\
			<< "Шанс попадання: " << bot.hit << endl\
			<< "Шанс захисту: " << bot.protection << endl\
			<< "Шанс парування: " << bot.parry << endl;
		cout << "\nДля того, щоб атакувати введiть a\nДля захисту d\n" << endl;
		while (player.health > 0 and bot.health > 0) {
			cout << "---------------" << endl\
				<< "| Ви: " << player.health << endl\
				<< "| Бот: " << bot.health << endl\
				<< "---------------" << endl;
			cout << "Ваш хiд: " << endl;
			cin >> duel_cmd;
			bot_try = rand() % 2;
			switch (bot_try) {
			case 0:
				bot_do = 'a';
				if (rand() % 101 <= bot.hit) {
					bot.do_chance = true;
				}
				else { bot.do_chance = false; }
				break;
			case 1:
				bot_do = 'd';
				if (rand() % 101 <= bot.protection) {
					bot.do_chance = true;
				}
				else { bot.do_chance = false; }
				break;
			}
			switch (duel_cmd) {
			case 'a':
				if (rand() % 101 <= owner.totalHit(player.hit)) {
					player.do_chance = true;
				}
				else { player.do_chance = false; }
				if (rand() % 101 <= owner.totalParry(player.parry) && bot_do == 'a' && duel_cmd == 'a' && bot.do_chance == true && player.do_chance == true) {
					cout << "Ви парирували атаку супротивника -0 HP у обох гравцiв!" << endl;
				}
				else if (bot_do == 'a' && duel_cmd == 'a' && bot.do_chance == true && player.do_chance == true) {
					cout << "Ви поранили один одного" << endl\
						<< "[HP] Ви -"<< bot.damage << endl\
						<< "[HP] Бот -"<< owner.totalDamage(player.damage) << endl;
					player.health -= bot.damage;
					bot.health -= owner.totalDamage(player.damage);
				}
				if (duel_cmd == 'a' && player.do_chance == true && bot.do_chance == false) {
					cout << "Бот не змiг передбачити ваш маневр, тому ви змогли атакувати його!\n[HP] Супротивник -" << owner.totalDamage(player.damage) << "HP" << endl;
					bot.health -= owner.totalDamage(player.damage);
				}
				if (rand() % 101 <= bot.parry && duel_cmd == 'a' && player.do_chance == true && bot_do == 'd' && bot.do_chance == true) {
					cout << "Ви бездумно замахнулись iз усiєii сили в супротивника, але бот зумiв передбачити це, але меч вiдрiкошетило по вам самим." << endl;
					player.health -= bot.damage;
				}
				else if (duel_cmd == 'a' && player.do_chance == true && bot_do == 'd' && bot.do_chance == true) {
					cout << "Бот змiг ухилитися вiд вашого удару\n[HP] -0 HP у обох гравцiв!" << endl;
				}
				if (bot_do == 'a' && duel_cmd == 'a' && bot.do_chance == false && player.do_chance == false) {
					cout << "Два дуелятна вирiшили помахати мечами одне одному\n[HP] -0 HP у обох гравцiв!" << endl;
				}
				if (duel_cmd == 'a' && player.do_chance == false && bot_do=='a' && bot.do_chance==true) {
					cout << "Нажаль однiєю тактикою цей бiй не виграєш, промах, бот влучив по вам!" << endl\
						<< "[HP] Ви -" << bot.damage << endl;
					player.health -= bot.damage;
				}
				if (duel_cmd == 'a' && bot_do == 'd' && player.do_chance == false && bot.do_chance == false) {
					cout << "Знову два гравцi вирiшили помахати своiми мечами\n[HP] -0 HP у обох гравцiв!" << endl;
				}
				if (duel_cmd == 'a' && bot_do == 'd' && player.do_chance == false && bot.do_chance == true) {
					cout << "Може вже досить махати мечем по повітрю?\nВи та ваш опонент промахнулись!\n[HP] -0 HP у обох гравцiв!" << endl;
				}
				//cout << "debug: " << duel_cmd << " " << bot_do << " " << player.do_chance << " " << bot.do_chance << endl;
				
				break;
			case 'd':
				if (rand() % 101 <= owner.totalProtect(player.protection)) {
					player.do_chance = true;
				}
				else { player.do_chance = false; }
				if (bot_do == 'd' && duel_cmd == 'd') {
					cout << "О_о, два гравцi вирiшили покрутитися навколо повiтря\n[HP] -0 HP у обох гравцiв!" << endl;
				}
				if (rand() % 101 <= owner.totalParry(player.parry) && duel_cmd == 'd' && player.do_chance == true && bot_do == 'a' && bot.do_chance == true) {
					cout << "Бот накинувсь на вас з усiх сил, але не помiтив вашой пiднiжки, тому вiн впав\n[HP] Бот -" << owner.totalDamage(player.damage) << endl;
					player.health -= owner.totalDamage(player.damage);
				}
				else if (duel_cmd == 'd' && player.do_chance == true && bot_do == 'a' && bot.do_chance == true) {
					cout << "Бот намагавсь пробити вашу оборону, але у нього нiчого не вийшло.\n[HP] -0 HP у обох гравцiв!" << endl;
				}
				if (duel_cmd == 'd' && player.do_chance == false && bot_do == 'a' && bot.do_chance == true) {
					cout << "Суперник вашого танцю не зрозумiв, тому з легкiстю пробив вашу оборону\n[HP] Ви -" << bot.damage << endl;
					player.health -= bot.damage;
				}
				if (duel_cmd == 'd' && player.do_chance == true && bot_do == 'a' && bot.do_chance == false) {
					cout << "Ви були готовi вiдбити атаку, але ваш супротивник забув вимкнути праску\n[HP] -0 HP у обох гравцiв!" << endl;
				}
				if (duel_cmd == 'd' && player.do_chance == false && bot_do == 'a' && bot.do_chance == false) {
					cout << "При нападi супротивника, ви раптово втратили рiвновагу, але боту щойно позвонили по телфону, \nтому вiн змушений був вiдповiсти на дзвінок\n[HP] -0 HP у обох гравцiв!" << endl;
				}
				//cout << "debug: " << duel_cmd << " " << bot_do << " " << player.do_chance << " " << bot.do_chance << endl;
				break;
			}
		}
		if (bot.health <= 0 && player.health > 0) {
			cout << "[!!!] Вiтаю ви перемогли бота!" << endl;
			player.giveRandExp(8);
			owner.dropItem();
		}
		else if (player.health <= 0 && bot.health > 0) {
			cout << "[!!!] Як сумно, вас перемiг випадковий набiр чисел!" << endl;
			player.giveRandExp(4);
		}
		else {
			cout << "[!!!] Перемогти бота це круто, але потрiбно було залишитись в живих :/ " << endl;
			player.giveRandExp(6);
		}
		player.calcLVL();
		player.duel_num++;
		break;
		
	case stats:
		system("cls");
		cout << "=======[Ваш iгровий персонаж]========" << endl\
			<< "Iм'я: " << player.name << endl \
			<< "Досвiд: " << player.exp << " / " << player.toNextLVL() << endl\
			<< "Рiвень: " << player.lvl << endl\
			<< "Макс. здоров'я: " << player.health << "	+(" << owner.totalHP(0) << ")" << endl\
			<< "Урон: " << player.damage << "		+(" << owner.totalDamage(0) << ")" <<  endl\
			<< "Шанс попадання: " << player.hit << "	+(" << owner.totalHit(0) << ")" << endl\
			<< "Шанс захисту: " << player.protection << "	+(" << owner.totalProtect(0) << ")" << endl\
			<< "Шанс парування: " << player.parry << "	+(" << owner.totalParry(0) << ")" << endl\
			<< "Кi-сть дуелей: " << player.duel_num << endl;
		cout << "\n\nback - щоб повернутися\n" << endl;
		player.calcLVL();
		cin >> cmd;
		system("cls");
		break;
	case inv:
		system("cls");
		cout << "  Голова:	      [" << ItemName[inventory[wear][0]][1] << "] " << endl\
			<< "                    ▄▄██████▄▄ " << endl\
			<< "                   ████████████" << endl\
			<< "                  ██████████████" << endl\
			<< "                  ███▀      ▀███" << endl\
			<< "                  ▀█▀ *    * ▀█▀" << endl\
			<< "                   ▀▄   --   ▄▀" << endl\
			<< "                     ▀▀▄▄▄▄▀▀" << endl\
			<< "   Тiло:	      [" << ItemName[inventory[wear][1]][1] << "] " << endl\
			<< "                   ▄███████████▄" << endl\
			<< "                  ▄█████████████▄" << endl\
			<< "                 ▄▀ ▄▀█████████ ▀▄" << endl\
			<< "               ▄▀ ▄▀  ████████ ▀▄ ▀▄" << endl\
			<< "               ▀▀▀    ▄▀████▀▄   ▀▄█" << endl\
			<< "   Права рука: [" << ItemName[inventory[weapon][rightArm]][1] << "]   Лiва рука: [" << ItemName[inventory[weapon][leftArm]][1] << "] " << endl\
			<< "                      ██▄▄▄▄██" << endl\
			<< "	Пояс:      [" << ItemName[inventory[belt][0]][1] << "]    [" << ItemName[inventory[belt][1]][1] << "]" << endl
			<< "	           [" << ItemName[inventory[belt][2]][1] << "]    [" << ItemName[inventory[belt][3]][1] << "]" << endl
			<< "                      ████████" << endl\
			<< "                      ███▀▀███" << endl\
			<< "                      ███  ███" << endl\
			<< "                      ███  ███" << endl\
			<< "  Ноги:    	     [ " << ItemName[inventory[wear][2]][1] << " ] " << endl\
			<< "                      ███  ███" << endl\
			<< "                     ████  ████" << endl\
			<< "                    █████  █████ " << endl\
			<< "  Взуття:            [ " << ItemName[inventory[wear][3]][1] << " ] " << endl;
		cout << "Повернутись (back): ";
		cin >> cmd;
		if (cmd == "back") {
			system("cls");
		}
		break;
	default:;
	}
	//autosave
	save.open("save.txt", ios_base::out);
	save << player.name << endl \
		<< player.exp << endl\
		<< player.lvl << endl\
		<< player.damage << endl\
		<< player.hit << endl\
		<< player.protection << endl\
		<< player.parry << endl\
		<< player.duel_num << endl\
		<< inventory[weapon][0] << endl\
		<< inventory[weapon][1] << endl\
		<< inventory[wear][0] << endl\
		<< inventory[wear][1] << endl\
		<< inventory[wear][2] << endl\
		<< inventory[wear][3] << endl\
		<< inventory[belt][0] << endl\
		<< inventory[belt][1] << endl\
		<< inventory[belt][2] << endl\
		<< inventory[belt][3] << endl;
	save.close();
}

void OnGameLoad() {
	system("cls");
	cout << "|+-/|==>Save System\n\
|Введiть:\n\
|1 - для створення нового профiлю" << endl;
	ifstream check("save.txt");
	cout << ((!check.is_open()) ? "" : "|2 - для завантаження вже iснуючого профiля") << endl;
	cin >> cmd;
	if (cmd == "1") {
		if (check.is_open()) {
			cout << "|Система знайшла данi про iснуючий профiль, знищити i створити новий(y/n)?" << endl;
			cin >> cmd;
			if (cmd == "y") {
				check.close();
				remove("save.txt");
				OnGameInit(666);
			}
			else {
				return OnGameLoad();
			}
		}
		else {
			OnGameInit(666);
		}
	}
	else if (cmd == "2" && (check.is_open())) {
		OnGameInit(666);
	}
	else { OnGameLoad(); }
	check.close();
	auth = true;
	system("cls");
}

void cmds(string cmd) {
	if (cmd == "help"){
		cout << "\
|КОМАНДИ:\n\
|duel - розпочати дуель\n\
|stats - iгрова статистика\n\
|inv - iнвентар\n\
|cls - очистити вiкно\n\
|logout - вийти з iгрового профiлю\n\
|q - вийти з гри\n\n";
	}
	else if (cmd == "duel") {
		OnGameInit(duel);
	}
	else if (cmd == "inv") {
		OnGameInit(inv);
	}
	else if (cmd == "stats") {
		OnGameInit(stats);
	}
	else if (cmd == "cls") {
		system("cls");
	}
	else if (cmd == "logout") {
		auth = false;
		system("cls");
	}
	else if (cmd == "q" or cmd == "quit") {
		exit(0);
	}
	else {
		cout << "|Помилка, invalid command! Try to write help\n" << endl;
	}
}

int main() {
	setlocale(LC_ALL, "rus");
	//OnGameInit(666);
	if (!auth) { OnGameLoad(); }
	cout << logotype;
	cin >> cmd;
	cmds(cmd);
	return main();
}