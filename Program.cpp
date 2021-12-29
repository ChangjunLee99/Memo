#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
using namespace std;

bool turnOff = false;

#define Subject_length 41 // 제목 길이
#define Content_length 301 // 내용 길이

int all_Index = 0;
int all_Index_dev = 0;
enum Status {
	_Main = 0,
	_Browse,
	_Create,
	_Delete,
	_Fix
};

Status stats = _Main;

void cinclear() {
	cin.clear();
	cin.ignore(256, '\n');
}

struct Writing {
public:
	int index;
	char subject[Subject_length] = { 0 };
	char content[Content_length] = { 0 };
};

class Writings {
public:
	vector<Writing> written;

	Writing createfirstWriting() {
		Writing a;
		a.index = 0;
		char subject = { 0 };
		char content = { 0 };
		written.push_back(a);
		return a;
	}

	Writings() {
		createfirstWriting();
	}

	void Browse() {
		int cnt = 1;
		vector<Writing>::iterator it;
		for (it = written.begin() + 1; cnt <= all_Index; it++) {
			cout << it->index << "번째 " << "\n" << "제목 : " << it->subject << '\n' << "내용 : " << it->content << '\n' << endl;
			cnt++;
		}
	}

	void Delete(int* a) {
		int d = *a;
		written.erase(written.begin() + d);
	}

	void Fix(int* a) {
		int z = *a;
		Writing d;
		vector<Writing>::iterator it;
		int cnt = 1;
		for (it = written.begin() + 1; it != written.end(); it++) {
			if (*a = cnt) {
				d.index = it->index;
				break;
			}
			else cnt++;
		}
		cout << "제목을 입력하십시오 (.으로 종료) : ";
		for (int i = 0; i < Subject_length; i++) {
			char a;
			cin >> a;
			if (a == '.') {
				break;
			}
			else {
				d.subject[i] = a;
			}
		}
		cout << "내용을 입력하십시오 (%으로 종료) : ";
		for (int i = 0; i < Content_length; i++) {
			char a;
			cin >> a;
			if (a == '%') {
				break;
			}
			else {
				d.content[i] = a;
			}
		}
		written[*a] = d;
	}

	void addWriting() {
		Writing b;
		all_Index++;
		b.index = all_Index;
		cout << "제목을 입력하십시오 (.으로 종료) : ";
		for (int i = 0; i < Subject_length; i++) {
			char a;
			cin >> a;
			if (a == '.') {
				break;
			}
			else {
				b.subject[i] = a;
			}
		}
		cout << "내용을 입력하십시오  (%으로 종료) : ";
		for (int i = 0; i < Content_length; i++) {
			char a;
			cin >> a;
			if (a == '%') {
				break;
			}
			else {
				b.content[i] = a;
			}
		}
		written.push_back(b);
	}
};

class Main {
public:
	Writings main;
	void View_() {
		//system("cls");
		if (stats == _Main) {
			system("cls");
			cout << "Browse : 1, " << "Create : 2, " << "Delete : 3, " << "Fix : 4, " << "exit 입력 시 종료" << endl;
		}

		else if (stats == _Browse) {
			cout << "Browse" << endl;
			main.Browse();
			cout << "Main으로 : 0, Fix : 1, Delete : 2" << endl;
		}
		else if (stats == _Create) {
			cout << "Create" << endl;
			//main.addWriting();
		}
		else if (stats == _Delete) {
			if (all_Index == 0) {
				cout << "현재 메모 없음.";
				Sleep(1000);
				stats = _Main;
				View_();
			}
			else {
				cout << "Delete" << endl;
				main.Browse();
			}
		}
		else if (stats == _Fix) {
			if (all_Index == 0) {
				cout << "현재 메모 없음.";
				Sleep(1000);
				stats = _Main;
				View_();
			}
			else {
				main.Browse();
				cout << "전체 " << all_Index << "개 중 변경 할 텍스트 선택(0입력 시 뒤로) : ";
			}
		}
	}
	void Input_() {
		if (stats == _Main) {
			string* a = new string;
			cin >> *a;
			if (*a == "exit") {
				cout << "종료";
				turnOff = true;
			}
			else if (*a < "1" || *a > "4") {
				cout << "잘 못 입력하셨습니다." << endl;
				cinclear();
				delete a;
				Sleep(1000);
				system("cls");
				void Input();
			}
			else if (*a == "1") {
				delete a;
				cinclear();
				system("cls");
				stats = _Browse;
			}
			else if (*a == "2") {
				delete a;
				cinclear();
				system("cls");
				stats = _Create;
			}
			else if (*a == "3") {
				delete a;
				cinclear();
				system("cls");
				stats = _Delete;
			}
			else if (*a == "4") {
				delete a;
				cinclear();
				system("cls");
				stats = _Fix;
			}

		}
		else if (stats == _Browse) {
			int* a = new int;
			cin >> *a;
			if (*a == 0) {
				stats = _Main;
				cinclear();
				delete a;
				system("cls");
			}
			else if (*a == 1) {
				stats = _Fix;
				cinclear();
				delete a;
				system("cls");
			}
			else if (*a == 2) {
				stats = _Delete;
				cinclear();
				delete a;
				system("cls");
			}
		}
		else if (stats == _Create) {
			main.addWriting();
			stats = _Main;
			system("cls");
		}
		else if (stats == _Delete) {
			cout << "삭제할 글(0 입력 시 뒤로) : ";
			string* a = new string;
			cin >> *a;
			if (*a == "0") {
				stats = _Main;
			}
			else {
				int* b = (int*)a;
				if (*b > all_Index || 0 > *b) {
					cout << "잘 못 입력하셨습니다.";
					Sleep(1000);
					cinclear();
					delete a;
					system("cls");
				}
				else {
					main.Delete(b);
					cout << *b << "삭제 완료." << endl;
					Sleep(1000);
					cinclear();
					delete a;
					system("cls");
					stats = _Main;
				}
			}
		}
		else if (stats == _Fix) {

			int* a = new int;
			cin >> *a;
			if (*a > all_Index || 0 > *a || cin.fail()) {
				cout << "잘 못 입력하셨습니다.";
				Sleep(1000);
				cinclear();
				delete a;
				system("cls");
			}
			else if (*a <= all_Index && *a != 0) {
				main.Fix(a);
				cout << "변경 완료." << endl;
				cinclear();
				delete a;
				Sleep(1000);
				stats = _Main;
			}
			else if (*a == 0) {
				cinclear();
				delete a;
				stats = _Main;
			}
		}
	}
};

int main() {
	Main b;
	while (!turnOff) {
		b.View_();
		b.Input_();
	}
}