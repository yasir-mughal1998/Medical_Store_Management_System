#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<conio.h>
#include<Windows.h>
#include<time.h>

using namespace std;

int i;
//function for auto increment customer & supplier Id.
int getsupp_id();
//function for main menu
void main_menu();
//function for all box
void main_box();
void box1();
void lbox();
void box();
//function for bill slip
void bill();
//function for about menu
void about();
//function for medicine menu
void medicine();
void medi_sale();
void stock();
void update_stock();
void medi_entry();
void medi_search();
void remainder();
//function for supplier menu
void supplier();
void supp_entry();
void supp_list();
void sup_update();
void search();
void search_id();
void search_name();
//function for report menu
void report_menu();
void sale_rpt();
void sale_rpt_daily();
void profit_rpt();
void pur_rpt();
void pur_rpt_daily();
//functin to update password and user name
void update_pass();


//===================================structures =========================
struct medical
{
	string id, medi_name, type;
	int quantity;
	double sale, total, unit, cost, profit, duepr;
	int qty;
	string  exp_date_d, exp_date_m, exp_date_y, manu_date_d, manu_date_m, manu_date_y;
	int bill_no;
	string comp_name;
	string supp_name;
};

struct medical temp;
struct medical tmp;


struct supplier
{
	string supp_id, supp_name, city, mob_no, email;
};
struct supplier temp1, tmp1;

struct bill
{
	string billno, cname, mediname;
	int medi_qty;
	double medi_rate;
	double total;
	int day, month, year;
};
struct bill bil;

struct sales_report
{
	int medi_id;
	string medir_name;
	string cust_name;
	int sDay, sMonth, sYear;
	int qty;
	double rate;
	double total;
};
struct sales_report s_r;

struct purchase_report
{
	int medi_id;
	string medir_name;
	string supp_name;
	string medi_type;
	int sday, smonth, syear;
	int qty;
	double rate;
	double total;
	double total_s;
};
struct purchase_report p_r;

struct profit_report
{
	unsigned int medi_id;
	string medir_name;
	int sDay, sMonth, sYear;
	int qty;
	double rate;
	double unit;
	double profit;
};
struct profit_report pr_r;

void login()
{
	int a = 0;
	string  uname, user;
	string pword, pass, temp;
	fstream login, login1;
	login.open("login.dat", ios::in);
	if (!login)
	{
		login1.open("login.dat", ios::out);
		login1 << "admin  admin";
		login1.close();
	}
	while (a<3)
	{
		system("cls");
		cout << "\n\n\n\n\n\n\n\t\t\t\t\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2  LOGIN  \xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\n" << endl;
		cout << "\t\t\t\tUSERNAME:  "; cin >> uname;
		cout << endl << endl << "\t\t\t\tPASSWORD:  "; cin >> pword;

		login >> user >> pass;
		if (uname == user && pword == pass)
		{
			cout << "\n\n\n\t\t LOGIN IS SUCCESSFUL !!!!! WELCOME TO MEDICAL STORE MANAGEMENT SYSTEM" << endl;
			cout << "\t\t\t\t\tPress any key to continue...." << endl;
			_getch();
			login.close();
			main_menu();
		}
		else
		{
			a++;
			cout << "\n\n\t\t SORRY !!!! LOGIN UNSUCCESSFUL" << endl;
			cout << "\n\t\t\tpress any key to try again..";
			_getch();
		}

	}

	if (a > 2)
	{
		cout << "\n\n\t\t SORRY you have entered the wrong password 3 times" << endl;
		exit(0);
	}
}


void gotoxy(int x, int y)
{
	COORD  coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void update_pass()
{
	string user, pass, user1, pass1;
	string ch;
	system("cls");
	fstream update, update1;
	update.open("login.dat", ios::in | ios::out);
	gotoxy(10, 7);
	cout << "Enter current username: "; cin >> user1;
	gotoxy(10, 8);
	cout << "Enter current password: "; cin >> pass1;

	update >> user >> pass;

	if (user == user1 && pass == pass1)
	{
		update1.open("login.dat", ios::out);
		gotoxy(10, 9);
		cout << "Enter new username: "; cin >> user;
		gotoxy(10, 10);
		cout << "Enter new password: "; cin >> pass;
		update1 << user << " " << pass;
		gotoxy(11, 20);
		cout << "updation successful  !!!....";
		gotoxy(12, 22);
		cout << "press any key to go to main menu....";
		_getch();

	}
	else
	{
		gotoxy(13, 11);
		cout << "incorrec passord or username...";
		gotoxy(13, 12);
		cout << "Enter 'A' to try again or 'C' to cancel  ";
		cin >> ch;
		if (ch == "a" || ch == "A")
			update_pass();
	}
	update.close();
	update1.close();

	main_menu();
}


//=========================Time & Date ====================
void td(int x1, int y1, int x2, int y2)
{
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);
	gotoxy(x1, y1);
	cout << "DATE : " << now->tm_mday << "-" << 1 + now->tm_mon << "-" << (1900 + now->tm_year);
	gotoxy(x2, y2);
	cout << "TIME : " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec;
}

//=========================== validation =========================
int validate(string str, int code)
{
	if (code == 0)
	{
		for (int i = 0; i<str.length(); i++)
		{
			if (!((str.at(i) >= 97 && str.at(i) <= 122) || (str.at(i) >= 65 && str.at(i) <= 90) || str.at(i) == 32))
				return 0;
		}
	}
	else if (code == 1)
	{
		for (int i = 0; i<str.length(); i++)
			if (!((str.at(i) >= 48 && str.at(i) <= 57) || str.at(i) == 46 || str.at(i) == '-'))
				return 0;
	}
	else if (code == 2)
	{
		for (int i = 0; i<str.length(); i++)
			if (!((str.at(i) >= 97 && str.at(i) <= 122) || (str.at(i) >= 65 && str.at(i) <= 90) || (str.at(i) >= 48 && str.at(i) <= 57) || str.at(i) == 32 || str.at(i) == '@' || str.at(i) == '.'))
				return 0;
	}

	return 1;
}


//============================all boxes ===============

void box()
{
	for (i = 3; i <= 79; i++)
	{
		gotoxy(i, 3);
		cout << char(219);
		gotoxy(78, 45);
		cout << char(219);
		gotoxy(i, 45);
		cout << char(219);
	}

	for (i = 3; i <= 45; i++)
	{
		gotoxy(3, i);
		cout << char(219);
		gotoxy(79, i);
		cout << char(219);
	}
}

void lbox()
{
	gotoxy(25, 6);
	cout << char(201);
	for (i = 26; i<55; i++)
	{
		gotoxy(i, 6);
		cout << char(205);
	}
	gotoxy(55, 6);
	cout << char(187);
	gotoxy(25, 6);
	for (i = 6; i<8; i++)
	{
		gotoxy(25, i + 1);
		cout << char(186);
	}
	gotoxy(25, 9);
	cout << char(200);
	for (i = 26; i<55; i++)
	{
		gotoxy(i, 9);
		cout << char(205);
	}
	gotoxy(55, 9);
	cout << char(188);
	gotoxy(55, 6);
	for (i = 6; i<8; i++)
	{
		gotoxy(55, i + 1);
		cout << char(186);
	}

}

void box1()
{
	gotoxy(1, 3);
	cout << char(201);
	for (i = 1; i<79; i++)
	{
		gotoxy(1 + i, 3);
		cout << char(205);
	}

	gotoxy(80, 3);
	cout << char(187);
	gotoxy(1, 3);
	for (i = 4; i<10; i++)
	{
		gotoxy(1, i);
		cout << char(186);
	}
	gotoxy(1, 9);
	for (i = 4; i<8; i++)
	{
		gotoxy(80, i);
		cout << char(186);
	}
}

void main_box()
{
	gotoxy(1, 6);
	cout << char(201);
	for (i = 1; i<79; i++)
	{
		gotoxy(1 + i, 6);
		cout << char(205);
	}

	gotoxy(80, 6);
	cout << char(187);
	gotoxy(1, 6);
	for (i = 5; i<35; i++)
	{
		gotoxy(1, 2 + i);
		cout << char(186);
	}
	gotoxy(1, 37);
	cout << char(200);
	for (i = 1; i<79; i++)
	{
		gotoxy(1 + i, 37);
		cout << char(205);
	}
	gotoxy(80, 37);
	cout << char(188);
	gotoxy(80, 6);
	for (i = 5; i<35; i++)
	{
		gotoxy(80, 2 + i);
		cout << char(186);
	}
}

//main function
int main()
{
	login();
	main_menu();
}

void main_menu()

{
	string ch;

	system("cls");
	gotoxy(3, 5);
	cout << "Supplier Info";

	gotoxy(23, 5);
	cout << "Medicine";
	gotoxy(38, 5);
	cout << "Report";
	gotoxy(50, 5);
	cout << "Bill";
	gotoxy(60, 5);
	cout << "About";
	gotoxy(71, 5);
	cout << "Exit";
	gotoxy(51, 36);
	cout << "to update password enter U";

	td(65, 38, 65, 40);   //this function display date & time
	box1();
	main_box();
	gotoxy(30, 10);
	cout << "Medical Store Management System ";
	gotoxy(2, 28);
	remainder();        //this function is active only when medicine qty is less then 10.
	gotoxy(10, 38);
	cout << "Press First Character for further Menu  ";

	cin >> ch;
	if (ch == "S" || ch == "s") { supplier(); }
	else if (ch == "M" || ch == "m") { medicine(); }
	else if (ch == "R" || ch == "r") { report_menu(); }
	else if (ch == "B" || ch == "b") { bill(); }
	else if (ch == "A" || ch == "a") { about(); }
	else if (ch == "U" || ch == "u") { update_pass(); }
	else if (ch == "E" || ch == "e") {
		gotoxy(23, 20);
		cout << "Do you want to exit now? Y/N :";
		ch = _getch();
		if (ch == "Y" || ch == "y")
		{
			system("cls");
			gotoxy(35, 20);
			cout << " Please wait.....";
			gotoxy(35, 22);
			Sleep(1000);
			exit(0);
		}
		else
			main_menu();
	}

	else
	{
		gotoxy(11, 34);
		cout << "Plese Enter right character ONLY (S,U,M,R,B,A).";
		gotoxy(11, 35);
		cout << "press any key to enter again.";
		_getch();
	}
	main_menu();
}




//=========================For supplier ===========================
void supplier()
{
	string ch;
	do
	{
		system("cls");
		main_box();
		gotoxy(34, 3);
		cout << "----------------";
		gotoxy(35, 4);
		cout << "Supplier MENU";
		gotoxy(34, 5);
		cout << "----------------";
		gotoxy(25, 11);
		cout << "Add New Supplier";

		gotoxy(25, 15);
		cout << "Update Supplier";

		gotoxy(25, 19);
		cout << "Search Supplier";

		gotoxy(25, 23);
		cout << "List of Existing Supplier";

		gotoxy(25, 27);
		cout << "Main Menu";

		gotoxy(10, 40);
		cout << "Press First Character for further Operation ";


		cin >> ch;
		if (ch == "A" || ch == "a") { supp_entry(); }
		else if (ch == "U" || ch == "u") { sup_update(); }
		else if (ch == "L" || ch == "l") { supp_list(); }
		else if (ch == "S" || ch == "s") { search(); }
		else if (ch == "M" || ch == "m") { main_menu(); }
		else
		{
			gotoxy(11, 34);
			cout << "Plese Enter right character ONLY (A,L,U,S,M).";
			gotoxy(11, 35);
			cout << "press any key to enter again. ";
			_getch();
		}
	} while (ch != "M" || ch != "m");
}

//=========================For Medicine ===========================
void medicine()
{
	string ch;
	do
	{
		system("cls");

		gotoxy(34, 3);
		cout << "---------------";
		gotoxy(35, 4);
		cout << "Medicine Menu.";
		gotoxy(34, 5);
		cout << "---------------";
		gotoxy(25, 13);
		cout << "Purchase New Medicine";
		gotoxy(25, 17);
		cout << "Sale Medicine";
		gotoxy(25, 21);
		cout << "Search Medicine";
		gotoxy(25, 25);
		cout << "Stock of Medicine";
		gotoxy(25, 29);
		cout << "Update stock";
		gotoxy(25, 33);
		cout << "Main Menu";
		main_box();
		gotoxy(10, 38);
		cout << "Press First Character for further Operations.";
		gotoxy(10, 39);
		cout << "NOTE:In case of letter duplication use second letter ";
		cin >> ch;
		if (ch == "P" || ch == "p") { medi_entry(); }
		else if (ch == "S" || ch == "s") { medi_sale(); }
		else if (ch == "T" || ch == "t") { stock(); }
		else if (ch == "E" || ch == "e") { medi_search(); }
		else if (ch == "M" || ch == "m") { main_menu(); }
		else if (ch == "U" || ch == "u") { update_stock(); }
		else
		{
			gotoxy(11, 34);
			cout << "Plese Enter right character ONLY (P,S,E,T,U,M).";
			gotoxy(11, 35);
			cout << "press any key to enter again";
			_getch();
		}

	} while (ch != "M" || ch != "m");

}
//=========================For Report ===========================
void report_menu()
{
	string ch;
	do
	{
		system("cls");
		gotoxy(34, 3);
		cout << "---------------";
		gotoxy(35, 4);
		cout << "Report Menu.";
		gotoxy(34, 5);
		cout << "---------------";
		gotoxy(25, 12);
		cout << "Purchase Report";
		gotoxy(25, 16);
		cout << "Sale Report";
		gotoxy(25, 20);
		cout << "Profit Report";
		gotoxy(25, 24);
		cout << "Daily Sale Report";
		gotoxy(25, 28);
		cout << "Daily Purchase Report";
		gotoxy(25, 32);
		cout << "Main Menu";
		main_box();
		gotoxy(10, 38);
		cout << "Press First Character for further Operations....";
		gotoxy(10, 39);
		cout << "In case of duplication enter second character   ";


		cin >> ch;
		if (ch == "P" || ch == "p") { pur_rpt(); }
		else if (ch == "S" || ch == "s") { sale_rpt(); }
		else if (ch == "D" || ch == "d") { sale_rpt_daily(); }
		else if (ch == "R" || ch == "r") { profit_rpt(); }
		else if (ch == "A" || ch == "a") { pur_rpt_daily(); }
		else if (ch == "M" || ch == "m") { main_menu(); }
		else
		{
			gotoxy(11, 34);
			cout << "Plese Enter right character ONLY (P,S,R,D,A,M).";
			gotoxy(11, 35);
			cout << "press any key to enter again.";
			_getch();
		}
	} while (ch != "M" || ch != "m");

}

void about()
{
	system("cls");
	gotoxy(28, 4);
	cout << "***** MEDICAL STORE *****";
	gotoxy(10, 8);
	cout << "=> Project Is About Medical Store ";
	gotoxy(10, 10);
	cout << "=> User Can Add Medicine and Supplier Details";
	gotoxy(10, 12);
	cout << "=> User Can Modify  Existing Records";
	gotoxy(10, 14);
	cout << "=> User Can Search Medicine and Supplier Details";
	gotoxy(10, 16);
	cout << "=> Also Used For Displaying Stock Of Medicine ";

	cout << "\n\n\n\t\t<<<<-Press any key for main menu->>>>";
	_getch();
	main_menu();


}
//======================Remainder for medicine stock ===============
void remainder()
{
	fstream rem;
	rem.open("medical.dat", ios::in);
	if (!rem)
		return;
	while (rem >> temp.id >> temp.medi_name >> temp.supp_name >> temp.quantity >> temp.unit >> temp.sale >> temp.cost >> temp.total >> temp.type >> temp.manu_date_d >> temp.manu_date_m >> temp.manu_date_y >> temp.exp_date_d >> temp.exp_date_m >> temp.exp_date_y)
	{
		if (temp.quantity<10)
		{
			gotoxy(10, 45);
			cout << temp.medi_name << endl;
			cout << ":  Quantity of this medicine is less then 10" << endl;
		}
	}


}

//========================for bill =============================
void bill()
{
	fstream billdat, billdat1;
	string id, ch;
	int j = 1;
	double netamt = 0.0;
	system("cls");
	billdat.open("dbbill.dat", ios::in);
	gotoxy(13, 4);
	cout << "Enter bill no : ";
	cin >> id;
	i = validate(id, 1);
	if (i == 0) {
		system("cls"); gotoxy(25, 15);  cout << "you entered wrong data....press any key to enter again or 'R' to return to menu.";
		ch = _getch();
		if (ch == "r" || ch == "R") { main_menu(); }
		else { bill(); }
	}
	system("cls");
	gotoxy(25, 3);
	box();
	gotoxy(7, 7);
	cout << "Bill No: ";
	cout << id;
	gotoxy(7, 9);
	cout << "Customer Name: ";
	td(50, 9, 50, 7);
	gotoxy(7, 12);
	cout << "Sr.No   Medicine Name       Qty          Rate         Total ";
	gotoxy(6, 14);
	cout << "---------------------------------------------------------------------";

	i = 15;
	if (!billdat)
	{
		billdat1.open("dbbill.dat", ios::out);
		billdat1.close();
		gotoxy(20, 25);
		cout << "\n\tError opening file!!!";
		_getch();
		return;
	}
	while (billdat >> bil.billno >> bil.cname >> bil.mediname >> bil.medi_qty >> bil.medi_rate >> bil.total >> bil.day >> bil.month >> bil.year)
	{



		if (id == bil.billno)
		{
			gotoxy(7, i);

			cout << j;
			gotoxy(14, i);
			cout << bil.mediname;
			gotoxy(22, 9);
			cout << bil.cname;
			gotoxy(35, i);
			cout << bil.medi_qty;
			gotoxy(47, i);
			cout << bil.medi_rate;
			gotoxy(60, i);
			cout << fixed << setprecision(2) << bil.total;
			netamt = netamt + bil.total;
			i++;
			j++;
			gotoxy(35, 32);
			cout << "                                ";
			gotoxy(20, 40);
			cout << "Press Any key to go to  MENU ...........";
			break;
		}
	}



	gotoxy(6, 35);
	cout << "---------------------------------------------------------------------";
	gotoxy(50, 37);
	cout << "Net Amount : ";
	cout << fixed << setprecision(2) << netamt;

	billdat.close();
	_getch();
	main_menu();
}

//========FOR SUPPLIERS ENTRY=================
void supp_entry()
{

	string ch;
	int i;
	fstream suppdat, suppdat1;
	system("cls");
	i = getsupp_id();
	temp1.supp_id = to_string(i);
	suppdat.open("supplier.dat", ios::app);
	if (!suppdat)
	{
		gotoxy(20, 25);
		cout << "\n Error opening file!!";
		return;
	}

	system("cls");
	td(55, 46, 55, 48);
	box();
	lbox();
	gotoxy(30, 8);
	cout << " SUPPLIER ENTRY ";
	gotoxy(8, 13);
	cout << "SUPPLIER ID : " << temp1.supp_id;
	gotoxy(39, 13);
	cout << "FIRST NAME : ";
	gotoxy(8, 18);
	cout << "CITY        : ";
	gotoxy(39, 18);
	cout << "CONTACT NO.   : ";
	gotoxy(8, 23);
	cout << "EMAIL ID    : ";

	gotoxy(55, 13);
	cin >> temp1.supp_name;
	i = validate(temp1.supp_name, 0);
	if (i == 0) {
		system("cls"); gotoxy(25, 15);  cout << "you entered wrong data....press any key to enter again or 'R' to return to menu.";
		ch = _getch();
		if (ch == "r" || ch == "R") { supplier(); }
		else { supp_entry(); }
	}
	gotoxy(22, 18);
	cin >> temp1.city;
	i = validate(temp1.city, 0);
	if (i == 0) {
		system("cls"); gotoxy(25, 15);  cout << "you entered wrong data....press any key to enter again  or 'R' to return to menu.";
		ch = _getch();
		if (ch == "r" || ch == "R") { supplier(); }
		else { supp_entry(); }
	}
	gotoxy(55, 18);
	cin >> temp1.mob_no;
	i = validate(temp1.mob_no, 1);
	if (i == 0) {
		system("cls"); gotoxy(25, 15);  cout << "you entered wrong data....press any key to enter again  or 'R' to return to menu.";
		ch = _getch();
		if (ch == "r" || ch == "R") { supplier(); }
		else { supp_entry(); }
	}
	gotoxy(22, 23);
	cin >> temp1.email;
	i = validate(temp1.email, 2);
	if (i == 0) {
		system("cls"); gotoxy(25, 15);  cout << "you entered wrong data....press any key to enter again  or 'R' to return to menu.";
		ch = _getch();
		if (ch == "r" || ch == "R") { supplier(); }
		else { supp_entry(); }
	}
	gotoxy(20, 30);
	cout << "Save";
	gotoxy(28, 30);
	cout << "Cancel";
	gotoxy(18, 34);
	cout << "Press First charecter for the operation : ";
	cin >> ch;
	if (ch == "s" || ch == "S")
	{
		suppdat << temp1.supp_id << " " << temp1.supp_name << " " << temp1.mob_no << " " << temp1.city << " " << temp1.email << endl;
		gotoxy(20, 40);
		cout << "Supplier Added successfully!!!!!";
		_getch();


	}
	else if (ch == "c" || ch == "C") { suppdat.close(); supplier(); }
	else
	{
		system("cls");
		gotoxy(20, 25);
		cout << "you entered wrong choice....press any key to try again.";
		_getch();
		supp_entry();
	}

	suppdat.close();

}
//=========FOR SUPPLIER DISPLAY LIST ==========
void supp_list()
{
	system("cls");

	fstream suppdat, suppdat1;
	suppdat.open("supplier.dat", ios::in);
	if (!suppdat)
	{
		suppdat1.open("supplier.dat", ios::out);
		suppdat1.close();
		gotoxy(35, 20);
		cout << "\n\t Error opening File! ";
		_getch();
		return;
	}
	system("cls");
	box();
	td(55, 46, 55, 48);
	gotoxy(8, 48);
	cout << "Press Anykey to go to SUPPLIER MENU !!!";
	lbox();
	gotoxy(30, 8);
	cout << " SUPPLIER LIST ";
	gotoxy(5, 10);
	cout << "ID.  SUPPLIER NAME.      PH.NO.     CITY.         EMAIL";
	gotoxy(4, 12);
	i = 14;
	cout << "=================================================================";
	while (suppdat >> temp1.supp_id >> temp1.supp_name >> temp1.mob_no >> temp1.city >> temp1.email)
	{

		gotoxy(4, i);
		cout << temp1.supp_id;
		gotoxy(9, i);
		cout << temp1.supp_name;
		gotoxy(27, i);
		cout << temp1.mob_no;
		gotoxy(41, i);
		cout << temp1.city;
		gotoxy(54, i);
		cout << temp1.email;
		i = i + 2;
	}
	suppdat.close();
	_getch();
}
//======================search supplier==================
void search()
{
	string ch;

	do
	{
		system("cls");
		gotoxy(17, 10);
		cout << " Two options Available for searching : Search by ";
		gotoxy(25, 15);
		cout << "ID number";
		gotoxy(25, 17);
		cout << "Name";
		gotoxy(25, 21);
		cout << "Return";
		main_box();
		gotoxy(17, 24);
		cout << "Press First charecter for the operation : ";
		cin >> ch;
		if (ch == "I" || ch == "i")  search_id();
		else if (ch == "N" || ch == "n") search_name();
		else if (ch == "R" || ch == "r") supplier();
		else
		{
			system("cls");
			gotoxy(22, 18);
			cout << "You entered wrong choice!!!!!";
			gotoxy(22, 20);
			cout << "press any key to try again...";
			_getch();
		}
	} while (ch != "R" || ch != "r");

}
//=============================== Search by id =============================
void search_id()
{
	string id, ch;
	fstream suppdat, suppdat1;

	suppdat.open("supplier.dat", ios::in);
	if (!suppdat)
	{
		suppdat1.open("supplier.dat", ios::out);
		suppdat1.close();
		gotoxy(20, 32);
		cout << "Error opening file!!!!";
		_getch();
		return;
	}
	system("cls");
	main_box();
	gotoxy(13, 8);
	cout << "Enter id to be searched:";
	cin >> id;
	i = validate(id, 1);
	if (i == 0)
	{
		system("cls");  gotoxy(20, 20); cout << "id you entered is not valid...press any key to try again.";
		ch = _getch();
		search_id();
	}
	gotoxy(20, 35);
	cout << "Press Any key to Return Back Menu ....";
	gotoxy(8, 14);
	cout << "ID.   SUPPLIER NAME      CITY       PH.NO         EMAIL";
	gotoxy(8, 16);
	i = 18;
	cout << "===================================================================";
	while (suppdat >> temp1.supp_id >> temp1.supp_name >> temp1.mob_no >> temp1.city >> temp1.email)
	{
		if (temp1.supp_id == id)
		{
			gotoxy(8, i);
			cout << temp1.supp_id;
			gotoxy(14, i);
			cout << temp1.supp_name;
			gotoxy(30, i);
			cout << temp1.city;
			gotoxy(42, i);
			cout << "0" << temp1.mob_no;
			gotoxy(55, i);
			cout << temp1.email;
			i++;
			break;
		}
	}
	if (temp1.supp_id != id)
	{
		gotoxy(20, 30);
		cout << "Record not found!";
	}
	suppdat.close();
	_getch();
}
//============================ Search by name =============================
void search_name()
{
	fstream suppdat, suppdat1;
	string name;

	suppdat.open("supplier.dat", ios::in);
	if (!suppdat)
	{
		suppdat1.open("supplier.dat", ios::out);
		suppdat1.close();
		gotoxy(20, 32);
		cout << "file can't open!!!!";
		_getch();
		return;
	}
	system("cls");
	main_box();
	gotoxy(13, 8);
	cout << " Enter Supplier Name to be searched : ";
	cin >> name;
	gotoxy(20, 35);
	cout << "Press Any key to Return Back Menu ....";
	gotoxy(8, 14);
	cout << "ID.   SUPPLIER NAME      CITY       PH.NO         EMAIL";
	gotoxy(8, 16);
	i = 18;
	cout << "===================================================================";

	while (suppdat >> temp1.supp_id >> temp1.supp_name >> temp1.mob_no >> temp1.city >> temp1.email)
	{
		if (temp1.supp_name.compare(name) == 0)
		{
			gotoxy(8, i);
			cout << temp1.supp_id;
			gotoxy(14, i);
			cout << temp1.supp_name;
			gotoxy(30, i);
			cout << temp1.city;
			gotoxy(42, i);
			cout << "0" << temp1.mob_no;
			gotoxy(55, i);
			cout << temp1.email;
			i++;
			break;
		}
	}
	if (temp1.supp_name.compare(name) != 0)
	{
		gotoxy(20, 30);
		cout << "Record not found!!!";
	}
	suppdat.close();
	_getch();
}
//============supp update=================
void sup_update()
{
	int j = 0, i;
	string ch, id;
	fstream suppdat, tmpdat;
	system("cls");
	box();
	suppdat.open("supplier.dat", ios::in | ios::out);
	tmpdat.open("temp.dat", ios::out);
	if (!suppdat || !tmpdat)
	{
		gotoxy(20, 25);
		cout << "\n\t Error opening file!! ";
		_getch();
		return;
	}
	lbox();
	gotoxy(30, 8);
	cout << " Modifying Supplier ";
	gotoxy(12, 13);
	cout << "Enter supplier ID :  ";
	cin >> id;
	i = validate(id, 1);
	if (i == 0)
	{
		system("cls"); gotoxy(20, 20);   cout << "id you entered is invalid....press any key to try again.";
		_getch();
		sup_update();
	}
	gotoxy(12, 15);
	while (suppdat >> temp1.supp_id >> temp1.supp_name >> temp1.mob_no >> temp1.city >> temp1.email)
	{
		if (temp1.supp_id == id)
		{
			j++;
			gotoxy(18, 17);
			cout << " Existing Record  ";
			gotoxy(10, 19);
			cout << temp1.supp_id << "\t" << temp1.supp_name << "\t" << temp1.mob_no << "\t" << temp1.city << "\t" << temp1.email;
			gotoxy(12, 22);
			cout << "Enter New Name       : ";  cin >> tmp1.supp_name;
			i = validate(tmp1.supp_name, 0);
			if (i == 0)
			{
				system("cls"); gotoxy(20, 15); cout << "you entered wrong data....press any key to enter again  or 'R' to return to menu.";
				ch = _getch();
				if (ch == "r" || ch == "R") { supplier(); }
				else { sup_update(); }
			}
			gotoxy(12, 24);
			cout << "Enter New mobile no  : ";  cin >> tmp1.mob_no;
			i = validate(tmp1.mob_no, 1);
			if (i == 0)
			{
				system("cls"); gotoxy(20, 15); cout << "you entered wrong data....press any key to enter again  or 'R' to return to menu.";
				ch = _getch();
				if (ch == "r" || ch == "R") { supplier(); }
				else { sup_update(); }
			}

			gotoxy(12, 26);
			cout << "Enter New City       : ";  cin >> tmp1.city;
			i = validate(tmp1.city, 0);
			if (i == 0)
			{
				system("cls"); gotoxy(20, 15);  cout << "you entered wrong data....press any key to enter again  or 'R' to return to menu.";
				ch = _getch();
				if (ch == "r" || ch == "R") { supplier(); }
				else { sup_update(); }
			}
			gotoxy(12, 28);
			cout << "Enter New email      : ";  cin >> tmp1.email;
			i = validate(tmp1.email, 2);
			if (i == 0)
			{
				system("cls");  gotoxy(20, 15);  cout << "you entered wrong data....press any key to enter again  or 'R' to return to menu.";
				ch = _getch();
				if (ch == "r" || ch == "R") { supplier(); }
				else { sup_update(); }
			}
			gotoxy(20, 32);
			cout << "Update";
			gotoxy(30, 32);
			cout << "Cancel";
			gotoxy(18, 36);
			cout << "Press First charecter for the operation : ";
			cin >> ch;
			if (ch == "u" || ch == "U")
			{
				tmpdat << temp1.supp_id << " " << tmp1.supp_name << " " << tmp1.mob_no << " " << tmp1.city << " " << tmp1.email << endl;
				gotoxy(20, 38);
				cout << "Supplier updated successfully...";
				_getch();


			}

		}
		else
		{
			tmpdat << temp1.supp_id << " " << temp1.supp_name << " " << temp1.mob_no << " " << temp1.city << " " << temp1.email << endl;
		}

	}
	if (j == 0)
	{
		gotoxy(20, 30);
		cout << "Record not find!!!";
		_getch();
	}
	suppdat.close();
	tmpdat.close();
	remove("supplier.dat");
	rename("temp.dat", "supplier.dat");
	_getch();


}
//===============================END OF SUPPLIER FUNCTION===================


//============================ FOR MEDICINE PURCHASE    ===================
void medi_entry()
{
	string ch, a;
	string id;
	double unit_p;

	bool flag = false;
	system("cls");
	fstream medirep, medidat, medidat1;

	medirep.open("purreport.dat", ios::app);
	medidat.open("medical.dat", ios::in);

	time_t t = time(0);
	struct tm * now = localtime(&t);
	p_r.sday = now->tm_mday;
	p_r.smonth = 1 + now->tm_mon;
	p_r.syear = 1900 + now->tm_year;

	system("cls");
	box();
	td(87, 20, 87, 18);
	lbox();
	gotoxy(30, 8);
	cout << " MEDICINE PURSHASE  ";
	{
		gotoxy(7, 11);
		cout << "MEDICINE ID    : ";

		gotoxy(40, 11);
		cout << "MEDICINE NAME  : ";

		gotoxy(7, 14);
		cout << "MEDICINE TYPE  : ";

		gotoxy(7, 18);
		cout << "COMPANY NAME   : ";

		gotoxy(40, 18);
		cout << "SUPPLIER NAME  : ";

		gotoxy(7, 21);
		cout << "UNIT COST   Rs.:  ";

		gotoxy(40, 21);
		cout << "SALE COST   Rs.: ";

		gotoxy(7, 24);
		cout << "QUANTITY       :  ";

		gotoxy(7, 27); cout << "MFG.DATE: ";                                    gotoxy(35, 27); cout << "EXP.DATE ";
		gotoxy(7, 29); cout << "DATE(dd): ";                                    gotoxy(35, 29); cout << "DATE(dd): ";
		gotoxy(7, 30); cout << "MONTH(mm): ";								    gotoxy(35, 30); cout << "MONTH(mm): ";
		gotoxy(7, 31); cout << "YEAR(yyyy): ";                                 gotoxy(35, 31); cout << "YEAR(yyyy): ";


		gotoxy(25, 11);
		cin >> id;
		i = validate(id, 1);
		if (i == 0)
		{
			system("cls");  gotoxy(20, 20); cout << "id you entered is invalid.....press any key to try again or 'R' to return back.";
			ch = _getch();
			if (ch == "R" || ch == "r") medicine();
			else
				medi_entry();
		}
		while (medidat >> temp.id >> temp.medi_name >> temp.supp_name >> temp.quantity >> temp.unit >> temp.sale >> temp.cost >> temp.total >> temp.type >> temp.manu_date_d >> temp.manu_date_m >> temp.manu_date_y >> temp.exp_date_d >> temp.exp_date_m >> temp.exp_date_y)
		{

			if (id == temp.id)
			{
				flag = true;
				break;
			}
		}
		if (flag == true)
		{
			gotoxy(20, 31);
			cout << "ID Allready Exists";
			medidat.close();
			_getch();
			system("cls");
			medi_entry();
		}
		else
		{
			medidat1.open("medical.dat", ios::app);
			temp.id = id;
			p_r.medi_id = stoi(temp.id);
		}
		gotoxy(58, 11);
		cin >> temp.medi_name;
		i = validate(temp.medi_name, 0);
		if (i == 0)
		{
			system("cls"); gotoxy(20, 15);  cout << "you entered wrong data......press any key to try again or 'R' to return to previous menu.";
			ch = _getch();
			if (ch == "r" || ch == "R") { medicine(); }
			else { medi_entry(); }
		}
		p_r.medir_name = temp.medi_name;
		gotoxy(25, 14);
		cin >> temp.type;
		i = validate(temp.type, 0);
		if (i == 0)
		{
			system("cls");  gotoxy(20, 15);  cout << "you entered wrong data......press any key to try again or 'R' to return to previous menu.";
			ch = _getch();
			if (ch == "r" || ch == "R") { medicine(); }
			else { medi_entry(); }
		}
		p_r.medi_type = temp.type;
		gotoxy(25, 18);
		cin >> temp.comp_name;
		i = validate(temp.comp_name, 2);
		if (i == 0)
		{
			system("cls");  gotoxy(20, 15);  cout << "you entered wrong data......press any key to try again or 'R' to return to previous menu.";
			ch = _getch();
			if (ch == "r" || ch == "R") { medicine(); }
			else { medi_entry(); }
		}
		gotoxy(58, 18);
		cin >> temp.supp_name;
		i = validate(temp.supp_name, 0);
		if (i == 0)
		{
			system("cls"); gotoxy(20, 15);   cout << "you entered wrong data......press any key to try again or 'R' to return to previous menu.";
			ch = _getch();
			if (ch == "r" || ch == "R") { medicine(); }
			else { medi_entry(); }
		}
		p_r.supp_name = temp.supp_name;
		gotoxy(25, 21);
		cin >> a;
		if (i == 0)
		{
			system("cls");  gotoxy(20, 15);  cout << "you entered wrong data......press any key to try again or 'R' to return to previous menu.";
			ch = _getch();
			if (ch == "r" || ch == "R") { medicine(); }
			else { medi_entry(); }
		}
		temp.unit = stod(a);
		p_r.rate = temp.unit;
		gotoxy(58, 21);
		cin >> a;
		i = validate(a, 1);
		if (i == 0)
		{
			system("cls"); gotoxy(20, 15); cout << "you entered wrong data......press any key to try again or 'R' to return to previous menu.";
			ch = _getch();
			if (ch == "r" || ch == "R") { medicine(); }
			else { medi_entry(); }
		}
		temp.sale = stoi(a);
		gotoxy(25, 24);
		cin >> a;
		i = validate(a, 1);
		if (i == 0)
		{
			system("cls");  gotoxy(20, 15);  cout << "you entered wrong data......press any key to try again or 'R' to return to previous menu.";
			ch = _getch();
			if (ch == "r" || ch == "R") { medicine(); }
			else { medi_entry(); }
		}
		temp.quantity = stoi(a);
		p_r.qty = temp.quantity;
		gotoxy(17, 29);
		cin >> temp.manu_date_d;
		i = validate(temp.manu_date_d, 1);
		if (i == 0)
		{
			system("cls");  gotoxy(20, 15);  cout << "you entered wrong data......press any key to try again or 'R' to return to previous menu.";
			ch = _getch();
			if (ch == "r" || ch == "R") { medicine(); }
			else { medi_entry(); }
		}
		gotoxy(18, 30);
		cin >> temp.manu_date_m;
		i = validate(temp.manu_date_m, 1);
		if (i == 0)
		{
			system("cls");  gotoxy(20, 15);  cout << "you entered wrong data......press any key to try again or 'R' to return to previous menu.";
			ch = _getch();
			if (ch == "r" || ch == "R") { medicine(); }
			else { medi_entry(); }
		}
		gotoxy(19, 31);
		cin >> temp.manu_date_y;
		i = validate(temp.manu_date_y, 1);
		if (i == 0)
		{
			system("cls");  gotoxy(20, 15);  cout << "you entered wrong data......press any key to try again or 'R' to return to previous menu.";
			ch = _getch();
			if (ch == "r" || ch == "R") { medicine(); }
			else { medi_entry(); }
		}
		gotoxy(45, 29);
		cin >> temp.exp_date_d;
		i = validate(temp.exp_date_d, 1);
		if (i == 0)
		{
			system("cls"); gotoxy(20, 15); cout << "you entered wrong data......press any key to try again or 'R' to return to previous menu.";
			ch = _getch();
			if (ch == "r" || ch == "R") { medicine; }
			else { medi_entry(); }
		}
		gotoxy(46, 30);
		cin >> temp.exp_date_m;
		i = validate(temp.exp_date_m, 1);
		if (i == 0)
		{
			system("cls"); gotoxy(20, 15); cout << "you entered wrong data......press any key to try again or 'R' to return to previous menu.";
			ch = _getch();
			if (ch == "r" || ch == "R") { medicine; }
			else { medi_entry(); }
		}
		gotoxy(47, 31);
		cin >> temp.exp_date_y;
		i = validate(temp.exp_date_y, 1);
		if (i == 0)
		{
			system("cls"); gotoxy(20, 15); cout << "you entered wrong data......press any key to try again or 'R' to return to previous menu.";
			ch = _getch();
			if (ch == "r" || ch == "R") { medicine; }
			else { medi_entry(); }
		}
		gotoxy(7, 34);
		cout << "==========================================================";
		temp.total = temp.quantity*temp.sale;
		temp.cost = (temp.unit*temp.quantity);
		gotoxy(10, 36);
		cout << "TOTAL UNIT COST = Rs. " << fixed << setprecision(2) << temp.cost;
		gotoxy(44, 36);
		cout << "TOTAL SALE COST = Rs. " << fixed << setprecision(2) << temp.total;
		p_r.total = temp.cost;
		p_r.total_s = temp.total;

	}
	gotoxy(20, 38);
	cout << "Save";
	gotoxy(28, 38);
	cout << "Cancel";
	gotoxy(18, 39);
	cout << "Press First charecter for the operation : ";


	cin >> ch;

	if (ch == "S" || ch == "s")
	{
		medidat1 << fixed << setprecision(2) << temp.id << " " << temp.medi_name << " " << temp.supp_name << " " << temp.quantity << " " << temp.unit << " " << temp.sale << " " << temp.cost << " " << temp.total << " " << temp.type << " " << temp.manu_date_d << " " << temp.manu_date_m << " " << temp.manu_date_y << " " << temp.exp_date_d << " " << temp.exp_date_m << " " << temp.exp_date_y << endl;

		medirep << fixed << setprecision(2) << p_r.medi_id << " " << p_r.medir_name << " " << p_r.medi_type << " " << p_r.supp_name << " " << p_r.qty << " " << p_r.rate << " " << p_r.total << " " << p_r.total_s << " " << p_r.sday << " " << p_r.smonth << " " << p_r.syear << endl;

		gotoxy(18, 41);
		cout << "Medicine Added sucessfully!!!!!!";
		_getch();

	}

	medidat.close();
	medidat1.close();
	medirep.close();
	medicine();


}
//===========FOR MEDICINE SALE=========================
void medi_sale()
{
	time_t t = time(0);
	struct tm * now = localtime(&t);
	int j, i, a;
	int d1, m, y;
	double b;
	string  mediname, c_name, cname, meditype;
	string  ch;
	fstream billdat, medidat, saldat, proftdat, tmpdat;
	int count = 0;
	d1 = now->tm_mday;
	m = 1 + now->tm_mon;
	y = 1900 + (now->tm_year);
	ch = 'Y';
	billdat.open("dbbill.dat", ios::app);
	medidat.open("medical.dat", ios::in);
	saldat.open("saleRpt.dat", ios::app);
	proftdat.open("profitRpt.dat", ios::app);
	tmpdat.open("temp.dat", ios::out);
	system("cls");
	main_box();
	i = 9;
	gotoxy(10, 7);
	cout << " Customer Name :"; cin >> c_name;
	i = validate(c_name, 0);
	if (i == 0)
	{
		system("cls");  gotoxy(20, 15);  cout << "you entered wrong data........press any key to try again or 'R' to return to previous menu.";
		ch = _getch();
		if (ch == "r" || ch == "R") { medicine(); }
		else { medi_sale(); }
	}

	gotoxy(9, 9);
	cout << "ENTER MEDICINE NAME TO BE SOLD  : "; cin >> mediname;
	i = validate(mediname, 0);
	if (i == 0)
	{
		system("cls");  gotoxy(20, 15);  cout << "you entered wrong data.s.......press any key to try again or 'R' to return to previous menu.";
		ch = _getch();
		if (ch == "r" || ch == "R") { medicine(); }
		else { medi_sale(); }
	}
	gotoxy(9, 11);
	cout << "ENTER MEDICINE TYPE TO BE SOLD  : "; cin >> meditype;
	i = validate(meditype, 0);
	if (i == 0)
	{
		system("cls");  gotoxy(20, 15);  cout << "you entered wrong data........press any key to try again or 'R' to return to previous menu.";
		ch = _getch();
		if (ch == "r" || ch == "R") { medicine(); }
		else { medi_sale(); }
	}

	j = 0;
	while (medidat >> temp.id >> temp.medi_name >> temp.supp_name >> temp.quantity >> temp.unit >> temp.sale >> temp.cost >> temp.total >> temp.type >> temp.manu_date_d >> temp.manu_date_m >> temp.manu_date_y >> temp.exp_date_d >> temp.exp_date_m >> temp.exp_date_y)
	{
		if (temp.medi_name == mediname && temp.type == meditype)
		{
			count += 1;
			gotoxy(8, 14);
			cout << " Medicine Name        : " << temp.medi_name;
			gotoxy(8, 15);
			cout << " Quantity in stock    : " << temp.quantity;
			gotoxy(8, 16);
			cout << " Sales price          : " << temp.sale;
			gotoxy(8, 17);
			cout << " Enter bill number    : "; cin >> bil.billno;
			i = validate(bil.billno, 1);
			if (i == 0)
			{
				system("cls");  gotoxy(20, 15);  cout << "you entered wrong data........press any key to try again or 'R' to return to previous menu.";
				ch = _getch();
				if (ch == "r" || ch == "R") { medicine(); }
				else { medi_sale(); }
			}
			gotoxy(8, 20);
			cout << "Quantity want to sale : ";
			cin >> a;
			string stra = to_string(a);
			i = validate(stra, 1);
			if (i == 0)
			{
				system("cls");  gotoxy(20, 15);  cout << "you entered wrong data........press any key to try again or 'R' to return to previous menu.";
				ch = _getch();
				if (ch == "r" || ch == "R") { medicine(); }
				else { medi_sale(); }
			}
			pr_r.profit = (temp.sale - temp.unit)*a;
			tmp = temp;
			tmp.quantity = (temp.quantity - a);
			tmp.total = (tmp.quantity*temp.sale);
			tmp.cost = (tmp.quantity*temp.unit);
			tmp.duepr = (tmp.sale*a);
			b = tmp.duepr;
			tmp.qty = a;

			tmpdat << fixed << setprecision(2) << temp.id << " " << temp.medi_name << " " << temp.supp_name << " " << tmp.quantity << " " << temp.unit << " " << temp.sale << " " << tmp.cost << " " << tmp.total << " " << temp.type << " " << temp.manu_date_d << " " << temp.manu_date_m << " " << temp.manu_date_y << " " << temp.exp_date_d << " " << temp.exp_date_m << " " << temp.exp_date_y << endl;
			bil.cname = c_name;
			s_r.cust_name = c_name;
			bil.mediname = temp.medi_name;
			bil.medi_qty = a;
			bil.medi_rate = temp.sale;
			bil.total = temp.sale*a;

			bil.day = d1;
			bil.month = m;
			bil.year = y;

			billdat << bil.billno << " " << bil.cname << " " << bil.mediname << " " << bil.medi_qty << " " << bil.medi_rate << " " << bil.total << " " << bil.day << " " << bil.month << " " << bil.year << endl;

			billdat.close();

			//sale report
			s_r.sDay = d1;
			s_r.sMonth = m;
			s_r.sYear = y;
			s_r.medir_name = temp.medi_name;
			s_r.qty = a;
			s_r.rate = temp.sale;
			s_r.total = temp.sale*a;

			saldat << s_r.medir_name << " " << s_r.cust_name << " " << s_r.qty << " " << s_r.rate << " " << s_r.total << " " << s_r.sDay << " " << s_r.sMonth << " " << s_r.sYear << endl;
			saldat.close();

			//profit report
			pr_r.sDay = d1;
			pr_r.sMonth = m;
			pr_r.sYear = y;
			pr_r.medir_name = temp.medi_name;
			pr_r.qty = a;
			pr_r.rate = temp.sale;
			pr_r.unit = temp.unit;
			proftdat << fixed << setprecision(2) << pr_r.medir_name << " " << pr_r.sDay << " " << pr_r.sMonth << " " << pr_r.sYear << " " << pr_r.qty << " " << pr_r.unit << " " << pr_r.rate << " " << pr_r.profit << endl;
			proftdat.close();

		}
		else
			tmpdat << fixed << setprecision(2) << temp.id << " " << temp.medi_name << " " << temp.supp_name << " " << temp.quantity << " " << temp.unit << " " << temp.sale << " " << temp.cost << " " << temp.total << " " << temp.type << " " << temp.manu_date_d << " " << temp.manu_date_m << " " << temp.manu_date_y << " " << temp.exp_date_d << " " << temp.exp_date_m << " " << temp.exp_date_y << endl;
	}
	if (count == 0)
	{
		system("cls");
		gotoxy(33, 10);
		cout << "Not in stock!!!!!";
		_getch();
		return;
	}
	gotoxy(8, 22);
	cout << "* Price paid by customer = " << b;
	gotoxy(8, 24);
	cout << "* Quantity sold          = " << a;
	_getch();
	tmpdat.close();
	medidat.close();
	remove("medical.dat");
	rename("temp.dat", "medical.dat");

}
//===========================MEDICINE STOCK=====================================
void stock()
{
	string ch;
	int i;
	fstream medidat;

	{
		system("cls");
		medidat.open("medical.dat", ios::in);
		if (!medidat)
		{
			gotoxy(30, 15);
			cout << "\n\t Error opening File!!! ";
			_getch();
			medicine();
		}
		system("cls");
		main_box();
		lbox();
		gotoxy(30, 8);
		cout << " STOCK OF MEDICINE ";
		i = 14;
		gotoxy(9, 10);
		cout << "ID.   MEDICINE NAME(Type).    QTY     Supplier Name     Exp.Date";
		gotoxy(9, 12);
		cout << "==================================================================\n";

		while (medidat >> temp.id >> temp.medi_name >> temp.supp_name >> temp.quantity >> temp.unit >> temp.sale >> temp.cost >> temp.total >> temp.type >> temp.manu_date_d >> temp.manu_date_m >> temp.manu_date_y >> temp.exp_date_d >> temp.exp_date_m >> temp.exp_date_y)
		{
			gotoxy(9, i);
			cout << temp.id;
			gotoxy(15, i);
			cout << temp.medi_name << "(" << temp.type << ")";
			gotoxy(40, i);
			cout << temp.quantity;
			gotoxy(47, i);
			cout << temp.supp_name;
			gotoxy(65, i);
			cout << temp.exp_date_d << "-" << temp.exp_date_m << "-" << temp.exp_date_y;
			i++;
		}
		gotoxy(10, 38);
		cout << "Press any key  to Go Back.... ";
		_getch();

	}

}
//=============================== FOR MEDICINE SEARCH ====================
void medi_search()
{
	string mediname, meditype;
	int i;
	string ch;
	system("cls");
	fstream medidat;
	medidat.open("medical.dat", ios::in);
	if (!medidat)
	{
		gotoxy(35, 15);
		cout << "\n\t Error opening File!!! ";
		_getch();
		medicine();
	}
	system("cls");
	main_box();
	lbox();
	gotoxy(34, 8);
	cout << " MEDICINE ";
	gotoxy(9, 10);
	cout << "ID.   MEDICINE NAME.    QTY     Supplier Name     Exp.Date";
	gotoxy(9, 12);
	cout << "==================================================================\n";
	gotoxy(4, 5);
	cout << "Nmae to be searched : ";
	gotoxy(55, 5);
	cout << "Type :";
	gotoxy(25, 5);
	cin >> mediname;
	i = validate(mediname, 0);
	if (i == 0)
	{
		system("cls");  gotoxy(20, 15);  cout << "you entered wrong data........press any key to try again or 'R' to return to previous menu.";
		ch = _getch();
		if (ch == "r" || ch == "R") { medicine(); }
		else { medi_search(); }
	}
	gotoxy(62, 5);
	cin >> meditype;
	i = validate(meditype, 0);
	if (i == 0)
	{
		system("cls");  gotoxy(20, 15);  cout << "you entered wrong data........press any key to try again or 'R' to return to previous menu.";
		ch = _getch();
		if (ch == "r" || ch == "R") { medicine(); }
		else { medi_search(); }
	}
	i = 14;

	while (medidat >> temp.id >> temp.medi_name >> temp.supp_name >> temp.quantity >> temp.unit >> temp.sale >> temp.cost >> temp.total >> temp.type >> temp.manu_date_d >> temp.manu_date_m >> temp.manu_date_y >> temp.exp_date_d >> temp.exp_date_m >> temp.exp_date_y)
	{
		if (mediname == temp.medi_name && meditype == temp.type)
		{
			gotoxy(9, i);
			cout << temp.id;
			gotoxy(15, i);
			cout << temp.medi_name;
			gotoxy(32, i);
			cout << temp.quantity;
			gotoxy(43, i);
			cout << temp.supp_name;
			gotoxy(60, i);
			cout << temp.exp_date_d << "-" << temp.exp_date_m << "-" << temp.exp_date_y;;
			i++;
			break;
		}

	}
	if (mediname != temp.medi_name || meditype != temp.type)
	{
		gotoxy(20, 20);
		cout << "Not in Stock.....";
	}
	_getch();

}
//============================ FOR MEDICINE UPDATE =====================
void update_stock()
{
	string name, type;
	int  a, count = 0, i;
	string ch;
	fstream medidat, tmpdat;
	system("cls");
	medidat.open("medical.dat", ios::in);
	tmpdat.open("temp.dat", ios::out);
	if (!medidat)
	{
		gotoxy(35, 15);
		cout << "\n\t Error opening File!!! ";
		_getch();
		medicine();
	}
	system("cls");
	box();
	gotoxy(27, 8);
	cout << " UPDATE MEDICINE QUANTITY ";
	gotoxy(9, 10);
	cout << "Enter medicine name to update qty: ";
	cin >> name;
	i = validate(name, 0);
	if (i == 0)
	{
		system("cls");  gotoxy(25, 10); cout << "you entered wrong data....press any key to try again or press 'R' to return to previous menu.";
		ch = _getch();
		if (ch == "r" || ch == "R") { medicine(); }
		else { update_stock(); }

	}
	gotoxy(9, 12);
	cout << "Enter medicine type: "; cin >> type;
	i = validate(type, 0);
	if (i == 0)
	{
		system("cls");  gotoxy(25, 10); cout << "you entered wrong data....press any key to try again or press 'R' to return to previous menu.";
		ch = _getch();
		if (ch == "r" || ch == "R") { medicine(); }
		else { update_stock(); }

	}

	while (medidat >> temp.id >> temp.medi_name >> temp.supp_name >> temp.quantity >> temp.unit >> temp.sale >> temp.cost >> temp.total >> temp.type >> temp.manu_date_d >> temp.manu_date_m >> temp.manu_date_y >> temp.exp_date_d >> temp.exp_date_m >> temp.exp_date_y)
	{
		if (name == temp.medi_name && type == temp.type)
		{
			gotoxy(8, 15);
			cout << temp.medi_name;
			gotoxy(8, 17);
			cout << temp.quantity;
			gotoxy(8, 19);
			cout << "Quantity want to update : ";
			cin >> a;
			tmp = temp;
			tmp.quantity = (tmp.quantity + a);
			tmp.total = (tmp.quantity*temp.sale);
			tmp.cost = (tmp.quantity*temp.unit);
			tmp.qty = a;
			count++;
			tmpdat << fixed << setprecision(2) << temp.id << " " << temp.medi_name << " " << temp.supp_name << " " << tmp.quantity << " " << temp.unit << " " << temp.sale << " " << tmp.cost << " " << tmp.total << " " << temp.type << " " << temp.manu_date_d << " " << temp.manu_date_m << " " << temp.manu_date_y << " " << temp.exp_date_d << " " << temp.exp_date_m << " " << temp.exp_date_y << endl;
		}
		else
			tmpdat << fixed << setprecision(2) << temp.id << " " << temp.medi_name << " " << temp.supp_name << " " << temp.quantity << " " << temp.unit << " " << temp.sale << " " << temp.cost << " " << temp.total << " " << temp.type << " " << temp.manu_date_d << " " << temp.manu_date_m << " " << temp.manu_date_y << " " << temp.exp_date_d << " " << temp.exp_date_m << " " << temp.exp_date_y << endl;
	}

	if (count == 0)
	{
		system("cls");
		gotoxy(33, 10);
		cout << "Not in stock!!!!!!";
		_getch();
		tmpdat.close();
		remove("temp.dat");
		return;
	}
	else
	{
		gotoxy(8, 20);
		cout << "update successful....";
		_getch();
	}
	tmpdat.close();
	medidat.close();
	remove("medical.dat");
	rename("temp.dat", "medical.dat");
}
//===================== view report =============================/
void sale_rpt()
{
	int j;
	system("cls");
	fstream srdat;
	srdat.open("saleRpt.dat", ios::in);
	if (!srdat)
	{
		cout << "\n\t error opening File! ";
		_getch();
		report_menu();
	}
	system("cls");
	box();
	gotoxy(20, 50);
	cout << "Press any key to go to REPORT MENU ...........";
	lbox();
	gotoxy(34, 8);
	cout << "Sales Report";
	gotoxy(7, 10);
	cout << " Medicine Name    Customer Name       Qty    Rate   Total    Date";
	gotoxy(7, 12);
	cout << "===================================================================";
	j = 14;
	while (srdat >> s_r.medir_name >> s_r.cust_name >> s_r.qty >> s_r.rate >> s_r.total >> s_r.sDay >> s_r.sMonth >> s_r.sYear)
	{
		gotoxy(9, j);
		cout << s_r.medir_name;
		gotoxy(26, j);
		cout << s_r.cust_name;
		gotoxy(44, j);
		cout << s_r.qty;
		gotoxy(51, j);
		cout << s_r.rate;
		gotoxy(58, j);
		cout << s_r.total;
		gotoxy(65, j);
		cout << s_r.sDay << "-" << s_r.sMonth << "-" << s_r.sYear;
		j = j + 2;
	}
	_getch();
}
//======================= VIEW PURCHASE REPORT ===========================
void pur_rpt()
{
	int j;
	system("cls");
	main_box();
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);
	p_r.sday = now->tm_mday;
	p_r.smonth = 1 + now->tm_mon;
	p_r.syear = (1900 + now->tm_year);
	fstream prdat;
	prdat.open("purreport.dat", ios::in);
	if (!prdat)
	{
		gotoxy(35, 15);
		cout << "\n\t Error opening File! ";
		_getch();
		report_menu();
	}
	gotoxy(20, 40);
	cout << "Press Enter to go to REPORT MENU ...........";
	lbox();
	gotoxy(34, 8);
	cout << "Purchase Report";
	gotoxy(6, 10);
	cout << "ID. Medi Name(Type)  Supplier Name    Qty   Rate   Total     Date";
	gotoxy(6, 12);
	cout << "====================================================================";
	j = 14;
	while (prdat >> p_r.medi_id >> p_r.medir_name >> p_r.medi_type >> p_r.supp_name >> p_r.qty >> p_r.rate >> p_r.total >> p_r.total_s >> p_r.sday >> p_r.smonth >> p_r.syear)
	{
		gotoxy(6, j);
		cout << p_r.medi_id;
		gotoxy(11, j);
		cout << p_r.medir_name << "(" << p_r.medi_type << ")";
		gotoxy(30, j);
		cout << p_r.supp_name;
		gotoxy(44, j);
		cout << p_r.qty;
		gotoxy(50, j);
		cout << p_r.rate;
		gotoxy(58, j);
		cout << p_r.total;
		gotoxy(65, j);
		cout << p_r.sday << "-" << p_r.smonth << "-" << p_r.syear;
		j += 2;
	}
	prdat.close();
	_getch();
}
//========================= report of profit ===========================
void profit_rpt()
{
	int j;
	system("cls");
	box();
	fstream prdat;
	prdat.open("profitRpt.dat", ios::in);
	if (!prdat)
	{
		gotoxy(35, 15);
		cout << "\n\t Error opening File! ";
		_getch();
		report_menu();
	}
	gotoxy(20, 40);
	cout << "Press Enter to go to REPORT MENU ...........";
	lbox();
	gotoxy(34, 8);
	cout << "Profit Report";
	gotoxy(7, 10);
	cout << "Medicine Name      Date     Qty     Unit Price  Sale Price   Profit ";
	gotoxy(7, 12);
	cout << "===================================================================";
	j = 14;
	while (prdat >> pr_r.medir_name >> pr_r.sDay >> pr_r.sMonth >> pr_r.sYear >> pr_r.qty >> pr_r.unit >> pr_r.rate >> pr_r.profit)
	{
		gotoxy(7, j);
		cout << pr_r.medir_name;
		gotoxy(23, j);
		cout << pr_r.sDay << "-" << pr_r.sMonth << "-" << pr_r.sYear;
		gotoxy(36, j);
		cout << pr_r.qty;
		gotoxy(48, j);
		cout << pr_r.unit;
		gotoxy(60, j);
		cout << pr_r.rate;
		gotoxy(70, j);
		cout << pr_r.profit;
		j += 2;

	}
	prdat.close();
	_getch();
}

//daily sale report

void sale_rpt_daily()
{
	int j;
	char ch;
	string d, m, y;
	double total = 0.00;
	system("cls");
	fstream dsrdat; //daily sale report data
	dsrdat.open("saleRpt.dat", ios::in);
	if (!dsrdat)
	{
		gotoxy(35, 15);
		cout << "\n\t Error opening File! ";
		_getch();
		report_menu();
	}
	gotoxy(15, 10);
	cout << "Enter Date(dd):  ";
	gotoxy(15, 12);
	cout << "Enter Month(mm): ";
	gotoxy(15, 14);
	cout << "Enter year(yyyy):";
	gotoxy(33, 10);
	cin >> d;
	i = validate(d, 1);
	if (i == 0)
	{
		system("cls");  gotoxy(20, 20);  cout << "you entered wrong data.....press any key to enter again or 'R' to return back";
		ch = _getch();
		if (ch == 'r' || ch == 'R') { report_menu(); }
		else { sale_rpt_daily(); }
	}
	gotoxy(33, 12);
	cin >> m;
	i = validate(m, 1);
	if (i == 0)
	{
		system("cls");  gotoxy(20, 20);  cout << "you entered wrong data.....press any key to enter again or 'R' to return back";
		ch = _getch();
		if (ch == 'r' || ch == 'R') { report_menu(); }
		else { sale_rpt_daily(); }
	}
	gotoxy(33, 14);
	cin >> y;
	i = validate(y, 1);
	if (i == 0)
	{
		system("cls");  gotoxy(20, 20);  cout << "you entered wrong data.....press any key to enter again or 'R' to return back";
		ch = _getch();
		if (ch == 'r' || ch == 'R') { report_menu(); }
		else { sale_rpt_daily(); }
	}
	system("cls");
	box();
	lbox();
	gotoxy(34, 8);
	cout << "Sales Report";
	gotoxy(82, 25);
	cout << "Press any key to go to REPORT MENU ....";
	gotoxy(7, 10);
	cout << " Medicine Name   Customer Name.   Qty.  Rate.  Total.   Date";
	gotoxy(7, 12);
	cout << "===================================================================";
	j = 14;
	while (dsrdat >> s_r.medir_name >> s_r.cust_name >> s_r.qty >> s_r.rate >> s_r.total >> s_r.sDay >> s_r.sMonth >> s_r.sYear)
	{
		if (stoi(d) == s_r.sDay && stoi(m) == s_r.sMonth && stoi(y) == s_r.sYear)
		{
			gotoxy(9, j);
			cout << s_r.medir_name;
			gotoxy(24, j);
			cout << s_r.cust_name;
			gotoxy(42, j);
			cout << s_r.qty;
			gotoxy(47, j);
			cout << s_r.rate;
			gotoxy(54, j);
			cout << s_r.total;
			gotoxy(62, j);
			cout << s_r.sDay << "-" << s_r.sMonth << "-" << s_r.sYear;
			j = j + 2;
			total = total + s_r.total;
		}
	}
	gotoxy(7, 42);
	cout << "-------------------------------------------------------------------";
	gotoxy(45, 43);
	cout << fixed << setprecision(2) << "Total:       " << total;
	dsrdat.close();
	_getch();
}

//daily purchase report

void pur_rpt_daily()
{
	int j;
	string d, m, y;
	char ch;
	double total = 0.00;
	fstream dprdat;   //daily purchase report data

	system("cls");
	dprdat.open("purreport.dat", ios::in);
	if (!dprdat)
	{
		gotoxy(35, 15);
		cout << "\n\t Error opening File! ";
		_getch();
		report_menu();
	}
	gotoxy(15, 10);
	cout << "Enter Date(dd):  ";
	gotoxy(15, 12);
	cout << "Enter Month(mm): ";
	gotoxy(15, 14);
	cout << "Enter year(yyyy):";
	gotoxy(33, 10);
	cin >> d;
	i = validate(d, 1);
	if (i == 0)
	{
		system("cls");  gotoxy(20, 20);  cout << "you entered wrong data.....press any key to enter again or 'R' to return back";
		ch = _getch();
		if (ch == 'r' || ch == 'R') { report_menu(); }
		else { sale_rpt_daily(); }
	}
	gotoxy(33, 12);
	cin >> m;
	i = validate(m, 1);
	if (i == 0)
	{
		system("cls");  gotoxy(20, 20);  cout << "you entered wrong data.....press any key to enter again or 'R' to return back";
		ch = _getch();
		if (ch == 'r' || ch == 'R') { report_menu(); }
		else { sale_rpt_daily(); }
	}
	gotoxy(33, 14);
	cin >> y;
	i = validate(y, 1);
	if (i == 0)
	{
		system("cls");  gotoxy(20, 20);  cout << "you entered wrong data.....press any key to enter again or 'R' to return back";
		ch = _getch();
		if (ch == 'r' || ch == 'R') { report_menu(); }
		else { sale_rpt_daily(); }
	}
	system("cls");
	box();
	lbox();
	gotoxy(34, 8);
	cout << "Purchase Report";
	gotoxy(82, 25);
	cout << "Press Enter to go to REPORT MENU ...........";
	td(82, 22, 82, 23);
	gotoxy(7, 10);
	cout << "ID. Medicine Name.  Supplier Name.   Qty.  Rate.  Total.   Date";
	gotoxy(7, 12);
	cout << "===================================================================";
	j = 14;
	while (dprdat >> p_r.medi_id >> p_r.medir_name >> p_r.medi_type >> p_r.supp_name >> p_r.qty >> p_r.rate >> p_r.total >> p_r.total_s >> p_r.sday >> p_r.smonth >> p_r.syear)
	{
		if (stoi(d) == p_r.sday && stoi(m) == p_r.smonth && stoi(y) == p_r.syear)
		{
			gotoxy(7, j);
			cout << p_r.medi_id;
			gotoxy(13, j);
			cout << p_r.medir_name;
			gotoxy(28, j);
			cout << p_r.supp_name;
			gotoxy(44, j);
			cout << p_r.qty;
			gotoxy(50, j);
			cout << p_r.rate;
			gotoxy(57, j);
			cout << p_r.total;
			gotoxy(65, j);
			cout << p_r.sday << "-" << p_r.smonth << "-" << p_r.syear;
			j += 2;
			total = total + p_r.total;
		}
	}
	gotoxy(7, 42);
	cout << "-------------------------------------------------------------------";
	gotoxy(45, 43);
	cout << fixed << setprecision(2) << "Total:        " << total;
	dprdat.close();
	_getch();

}

int getsupp_id()
{

	int id = 100;
	ifstream suppdat;
	suppdat.open("supplier.dat");
	if (suppdat.is_open()) {
		while (!suppdat.eof())
		{
			if (suppdat.peek() >= 0) { suppdat >> id; }
			else { suppdat >> temp1.supp_name; }
			suppdat >> temp1.supp_name >> temp1.mob_no >> temp1.city >> temp1.email;
		}

		suppdat.close();
		return id + 1;
	}
	else {
		return 101;
	}
}


//=============================================:) THE END :) =================================