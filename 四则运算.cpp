#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<stack>
#include<ctime>
#include<algorithm>

using namespace std;

struct ncc { //����ṹ�� 
	long double num; //ת������� 
	long long l; //��ѭ�������ĳ��ȣ�����λ���� 
};

char optor[9999] = {0}; //�洢��������� 
long double num[9999] = {0}; //�洢�����е��� 
char kh[9999] = {0}; //�洢���� 
int a = 1; //�洢��ʽ���ȣ���һλ��һ���������Գ�ʼΪ1 

bool check(string s) { //�������ƥ�亯�� 
	stack<char> st; //�½�ջst 
    long long len = s.length(); //�洢���� 
	bool flag = 1; //�洢������ʶ 
    for(register int i = 0; i < len; i++) {
    	if(s[i] == '(' || s[i] == '{' || s[i] == '[') {
    		st.push(s[i]);
		} else {
			if(st.empty()) {
				flag = 0;
				break;
			}
			char t = st.top();
			st.pop();
			if(s[i] == ')' && (t == '[' || t == '{')) {
			    flag = 0;
			    break;
			} else if(s[i] == '}' && (t == '(' || t == '[')) {
			    flag = 0;
			    break;
			} else if(s[i] == ']' && (t == '{' || t == '(')) {
			    flag = 0;
			    break;
			}
		}
	}
	if(!st.empty()) flag = 0;
	if(flag == 1) {
		return 1;
	} else {
		return 0;
	}
}

ncc string2num(string str, int n) { //stringתlong double���� 
	ncc a; //�½�һ���ṹ�� 
	a.l = 0, a.num = 0; //��ʼ�� 
	int len1 = 0, len2 = 0; //С����ǰlen1��С�����len2�ĳ�ʼ�� 
	int f = 0; //�Ƿ���С����ı�ʶ 
	while(str[n + len1] >= '0' && str[n + len1] <= '9') { //�����0~9֮�䣨�˴�����С����ǰ�� 
		len1++; //len1�Լ�һ 
	}
	if(str[n + len1] == '.') { //�����һλ��С���� 
		f = 1; //��С������fΪ1 
		while(str[n + len1 + 1 + len2] >= '0' && str[n + len1 + 1 + len2] <= '9') { //�����0~9֮�䣨�˴�����С����� 
			len2++; //len2�Լ�һ 
		}
	}
	for(register int i = n; i < n + len1; i++) { //����long double��ֵ 
		a.num += (int(str[i])- '0') * pow(10, (len1 + n - i - 1)); //ѭ���Լ� 
	}
	if(f) { //�����С���� 
		for(register int i = n + len1 + 1; i < n + len1 + 1 + len2; i++) { //��������long double��ֵ��С������ 
			a.num += (int(str[i])- '0') * pow(0.1, (i - (n + len1))); //ѭ���Լ� 
		}
	}
	a.l = len1 + len2 + f; //λ������С����ǰλ������С�����λ������С���㣨����С��ʱlen2��f�����㣩 
	return a; //����a 
}

void loop(long long n1) { //�ݹ���㺯����n1Ϊ������λ�� 
	long long n2 = 0; // 
	long long l = 0, r = 0; //��ʼ����iλ���������� 
	for(register int i = n1 + 1; i < a; i++) { //ѭ�������� 
		if(kh[i] == '(' || kh[i] == '[' || kh[i] == '{') {
			loop(i); //����������Ž���ݹ� 
		}
		if(kh[i] == ')' || kh[i] == ']' || kh[i] == '}') {
			n2 = i; //����������Ž�n2��ֵΪ���������� 
			break; 
		}
	}
	for(register int i = n1 + 1; i < n2; i++) { //�������ź�������֮��ѭ������ѭ������˳� 
		if(optor[i] == '*') { //���������ǳ� 
			l = i, r = i; //�����Ҹ�ֵ����������� 
			while(num[l] == 0 && l > n1) l--; //����Ѱ�������ڵ������ֵ 
			while(num[r] == 0 && r < n2) r++; //����Ѱ�������ڵ������ֵ 
			num[i] = num[l] * num[r]; //��� 
			optor[i] = 0, num[l] = 0, num[r] = 0; //��������������ԭʼ���� 
		}
		if(optor[i] == '/') { //���������ǳ� 
			l = i, r = i; //�����Ҹ�ֵ����������� 
			while(num[l] == 0 && l > n1) l--; //����Ѱ�������ڵ������ֵ 
			while(num[r] == 0 && r < n2) r++; //����Ѱ�������ڵ������ֵ 
			num[i] = num[l] / num[r]; //��� 
			optor[i] = 0, num[l] = 0, num[r] = 0; //��������������ԭʼ���� 
		}
	}
	for(register int i = n1 + 1; i < n2; i++) { //�������ź�������֮��ѭ������ѭ������Ӽ� 
		if(optor[i] == '+') { //���������Ǽ� 
			l = i, r = i; //�����Ҹ�ֵ����������� 
			while(num[l] == 0 && l > n1) l--; //����Ѱ�������ڵ������ֵ
			while(num[r] == 0 && r < n2) r++; //����Ѱ�������ڵ������ֵ 
			num[i] = num[l] + num[r]; //��� 
			optor[i] = 0, num[l] = 0, num[r] = 0; //��������������ԭʼ���� 
		}
		if(optor[i] == '-') { //���������Ǽ� 
			l = i, r = i; //�����Ҹ�ֵ����������� 
			while(num[l] == 0 && l > n1) l--; //����Ѱ�������ڵ������ֵ
			while(num[r] == 0 && r < n2) r++; //����Ѱ�������ڵ������ֵ 
			num[i] = num[l] - num[r]; //��� 
			optor[i] = 0, num[l] = 0, num[r] = 0; //��������������ԭʼ���� 
		}
	}
	kh[n1] = 0, kh[n2] = 0; //�˴μ�����ɣ������������ 
	return;
} 

void yunsuan() { //����������Ҫ���� 
	string str, kuohao, standard = "0123456789.+-*/()[]{}"; //����str�����ʽ��kuohao�����ʽ�е����ţ�standard��źϷ��ַ� 
	bool f = 0, t = 0; //��ʼ��������ʶf��tΪ�� 
	cout << "������ʽ(Ӣ�ķ��ţ��޿ո�)" << endl;
	cin >> str;
	for(register int i = 0; i < str.length(); i++) { //ѭ������ 
		if(str[i] == '.') {
			if((i == 0 || i == str.length() - 1) || ((str[i - 1] < '0' || str[i - 1] > '9') || (str[i + 1] < '0' || str[i + 1] > '9'))) {
				cout << "С�������" << endl;
				yunsuan();
				return; 
			}
			for(register int j = i + 1; j < str.length(); j++) {
				if(str[j] == '+' || str[j] == '-' || str[j] == '*' || str[j] == '/') break;
				if((str[j] >= '0' && str[j] <= '9') && str[j + 1] == '.') {
					cout << "���С����" << endl;
					yunsuan();
					return; 
				}
			}
		}
		if(str[i] == '(' || str[i] == ')' || str[i] == '{' || str[i] == '}' || str[i] == '[' || str[i] == ']') { //ѭ������ʽ�е�������ȡ���� 
			kuohao += str[i];
		}
		if(str[i] == '/' && str[i + 1] == '0' && str[i + 2] != '.') {
			cout << "����������Ϊ��" << endl;
			yunsuan();
			return; 
		}
		if((str[i] == '(' && str[i + 1] == ')') || (str[i] == '[' && str[i + 1] == ']') || (str[i] == '{' && str[i + 1] == '}')) {
			cout << "�����ڲ���Ϊ��" << endl;
			yunsuan();
			return; 
		}
		f = 0;
		for(register int j = 0; j < standard.length(); j++) { //����зǷ��ַ�����ʽ���� 
			if(str[i] == standard[j]) {
				f = 1;
				break;
			}
		}
		if(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
			if(i == 0 || i == str.length() - 1) {
				f = 0;
			} else if(!(((str[i - 1] >= '0' && str[i - 1] <= '9') || str[i - 1] == ')' || str[i - 1] == ']' || str[i - 1] == '}') && ((str[i + 1] >= '0' && str[i + 1] <= '9') || str[i + 1] == '(' || str[i + 1] == '[' || str[i + 1] == '{'))) {
				f = 0;
			}
			if((str[i] == '-' && i == 0 && (str[i + 1] >= '0' && str[i + 1] <= '9')) || (str[i] == '-' && i == 0 && (str[i + 1] == '(' || str[i + 1] == '[' || str[i + 1] == '{')) || (str[i] == '-' && (str[i - 1] == '(' || str[i - 1] == '[' || str[i - 1] == '{'))) {
				f = 1;
			}
			if(str[i] == '-' && (str[i - 1] == '(' || str[i - 1] == '[' || str[i - 1] == '{') && (str[i + 1] == '(' || str[i + 1] == '[' || str[i + 1] == '{')) {
				f = 1;
			}
		}
		if(!f) {
			cout << "���ڷǷ�����(�Ƿ��ַ�����Ų�ƥ��)" << endl;
			yunsuan();
			return; 
		}
	}
	if(!check(kuohao)) {
		cout << "����ƥ�����" << endl;
		yunsuan();
		return; 
	}
	for(register int i = 0; i < str.length(); i++) {
		if(str[i] >= '0' && str[i] <= '9') {
			ncc temp = string2num(str, i);
			num[a] = temp.num;
			a++;
			i += temp.l;
		}
		if(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
			optor[a] = str[i];
			a++;
		}
		if(str[i] == '(' || str[i] == ')' || str[i] == '[' || str[i] == ']' || str[i] == '{' || str[i] == '}') {
			kh[a] = str[i];
			a++;
		}
	}
	a++;
	kh[0] = '(';
	kh[a- 1] = ')';
	loop(0);
	for(register int i = 0; i < a; i++) {
		if(num[i] != 0) {
			cout << str << " = " << num[i] << endl;
			t = 1;
			break;
		}
	}
	if(!t) cout << str << " = 0" << endl;
	system("pause>nul");
	memset(optor, 0, sizeof(optor));
	memset(num, 0, sizeof(num));
	memset(kh, 0, sizeof(kh));
	a = 1;
	yunsuan();
	return;
}

int main(int argc, char** argv) {
	yunsuan();
	return 0;
}
