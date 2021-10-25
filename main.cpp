#include <iostream>
#include <string>
#include <fstream>

/*
Will do
-Inv system
-item buffs
-and a lot more
*/

#define logotype			\
"||============\n\
|| DUELIST alpha 0.3\n\
||\n\
|=> "
using namespace std;

bool auth = false;
int bot_try;
char bot_do;
ofstream save;

string cmd;

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

class Player {
public:
	string name="defaultname";
	double health = 100;
	bool do_chance = false;
	int exp=0;
	int lvl=1;
	double damage = 10;
	int hit=50;
	int protection=50;
	int parry=15;
	int duel_num = 0;
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
			<< player.duel_num << endl;
		save.close();
	}
	check >> player.name \
		>> player.exp \
		>> player.lvl \
		>> player.damage \
		>> player.hit \
		>> player.protection \
		>> player.parry \
		>> player.duel_num;
	check.close();
	switch (command) {
	case duel:
		char duel_cmd;
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
			//buf's
			switch (duel_cmd) {
			case 'a':
				if (rand() % 101 <= player.hit) {
					player.do_chance = true;
				}
				else { player.do_chance = false; }
				if (rand() % 101 <= player.parry && bot_do == 'a' && duel_cmd == 'a' && bot.do_chance == true && player.do_chance == true) {
					cout << "Ви парирували атаку супротивника -0 HP у обох гравцiв!" << endl;
				}
				else if (bot_do == 'a' && duel_cmd == 'a' && bot.do_chance == true && player.do_chance == true) {
					cout << "Ви поранили один одного" << endl\
						<< "[HP] Ви -"<<bot.damage << endl\
						<< "[HP] Бот -"<< player.damage << endl;
					player.health -= bot.damage;
					bot.health -= player.damage;
				}
				if (duel_cmd == 'a' && player.do_chance == true && bot.do_chance == false) {
					cout << "Бот не змiг передбачити ваш маневр, тому ви змогли атакувати його!\n[HP] Супротивник -" << player.damage << "HP" << endl;
					bot.health -= player.damage;
				}
				if (duel_cmd == 'a' && player.do_chance == true && bot_do == 'd' && bot.do_chance == true) {
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
					cout << "Може вже досить махати мечем по повітрю?\nВи промахнулись!\n[HP] -0 HP у обох гравцiв!" << endl;
				}
				//cout << "debug: " << duel_cmd << " " << bot_do << " " << player.do_chance << " " << bot.do_chance << endl;
				
				break;
			case 'd':
				if (rand() % 101 <= player.protection) {
					player.do_chance = true;
				}
				else { player.do_chance = false; }
				if (bot_do == 'd' && duel_cmd == 'd') {
					cout << "О_о, два гравцi вирiшили покрутитися навколо повiтря\n[HP] -0 HP у обох гравцiв!" << endl;
				}
				if (duel_cmd == 'd' && player.do_chance == true && bot_do == 'a' && bot.do_chance == true) {
					cout << "Бот намагавсь пробити вашу оборону, але у нього нiчого не вийшло.\n[HP] -0 HP у обох гравцiв!" << endl;
				}
				if (duel_cmd == 'd' && player.do_chance == false && bot_do == 'a' && bot.do_chance == true) {
					cout << "Суперник вашого танцю не зрозумiв, тому з легкiстю пробив вашу оборону\n[HP] Ви -" << player.damage << endl;
					player.health -= bot.damage;
				}
				if (duel_cmd == 'd' && player.do_chance == true && bot_do == 'a' && bot.do_chance == false) {
					cout << "Ви були готовi вiдбити атаку, але ваш супротивник забув вимкнути праску\n[HP] -0 HP у обох гравцiв!" << endl;
				}
				if (duel_cmd == 'd' && player.do_chance == false && bot_do == 'a' && bot.do_chance == false) {
					cout << "При нападi супротивника, ви раптово втратили рiвновагу, але боту щойно позвонили по телфону, \nтому вiн змушений був вiдповiсти на нього\n[HP] -0 HP у обох гравцiв!" << endl;
				}
				//cout << "debug: " << duel_cmd << " " << bot_do << " " << player.do_chance << " " << bot.do_chance << endl;
				break;
			}
		}
		if (bot.health <= 0 && player.health > 0) {
			cout << "[!!!] Вiтаю ви перемогли бота!" << endl;
		}
		else if (player.health <= 0 && bot.health > 0) {
			cout << "[!!!] Як сумно, вас перемiг випадковий набiр чисел!" << endl;
		}
		else {
			cout << "[!!!] Перемогти бота це круто, але потрiбно було залишитись в живих :/ " << endl;
		}
		player.duel_num++;
		break;
		
	case stats:
		system("cls");
		cout << "=======[Ваш iгровий персонаж]========" << endl\
			<< "Iм'я: " << player.name << endl \
			<< "Досвiд: " << player.exp << endl\
			<< "Рiвень: " << player.lvl << endl\
			<< "Урон: " << player.damage << endl\
			<< "Шанс попадання: " << player.hit << endl\
			<< "Шанс захисту: " << player.protection << endl\
			<< "Шанс парування" << player.parry << endl\
			<< "Кi-сть дуелей: " << player.duel_num << endl;
		cout << "\n\nback - щоб повернутися\n" << endl;
		cin >> cmd;
		break;
	case inv:
		cout << "work in progress" << endl;
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
		<< player.duel_num << endl;
	save.close();
}

void OnGameLoad() {
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
				system("cls");
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
	check.close();
	auth = true;
}

void cmds(string cmd) {
	if (cmd == "help"){
		cout << "\
|КОМАНДИ:\n\
|duel - розпочати дуель\n\
|inv - iнвентар\n\
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