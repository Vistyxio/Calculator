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

struct ncc { //定义结构体 
	long double num; //转换后的数 
	long long l; //让循环跳过的长度（数的位数） 
};

char optor[9999] = {0}; //存储四则运算符 
long double num[9999] = {0}; //存储计算中的数 
char kh[9999] = {0}; //存储括号 
int a = 1; //存储算式长度，第一位是一个括号所以初始为1 

bool check(string s) { //检查括号匹配函数 
	stack<char> st; //新建栈st 
    long long len = s.length(); //存储长度 
	bool flag = 1; //存储布尔标识 
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

ncc string2num(string str, int n) { //string转long double函数 
	ncc a; //新建一个结构体 
	a.l = 0, a.num = 0; //初始化 
	int len1 = 0, len2 = 0; //小数点前len1和小数点后len2的初始化 
	int f = 0; //是否有小数点的标识 
	while(str[n + len1] >= '0' && str[n + len1] <= '9') { //如果在0~9之间（此处处理小数点前） 
		len1++; //len1自加一 
	}
	if(str[n + len1] == '.') { //如果下一位是小数点 
		f = 1; //有小数点令f为1 
		while(str[n + len1 + 1 + len2] >= '0' && str[n + len1 + 1 + len2] <= '9') { //如果在0~9之间（此处处理小数点后） 
			len2++; //len2自加一 
		}
	}
	for(register int i = n; i < n + len1; i++) { //计算long double数值 
		a.num += (int(str[i])- '0') * pow(10, (len1 + n - i - 1)); //循环自加 
	}
	if(f) { //如果有小数点 
		for(register int i = n + len1 + 1; i < n + len1 + 1 + len2; i++) { //继续计算long double数值的小数部分 
			a.num += (int(str[i])- '0') * pow(0.1, (i - (n + len1))); //循环自加 
		}
	}
	a.l = len1 + len2 + f; //位数等于小数点前位数加上小数点后位数加上小数点（不是小数时len2和f都是零） 
	return a; //返回a 
}

void loop(long long n1) { //递归计算函数，n1为左括号位置 
	long long n2 = 0; // 
	long long l = 0, r = 0; //初始化第i位的左右坐标 
	for(register int i = n1 + 1; i < a; i++) { //循环找括号 
		if(kh[i] == '(' || kh[i] == '[' || kh[i] == '{') {
			loop(i); //如果是左括号进入递归 
		}
		if(kh[i] == ')' || kh[i] == ']' || kh[i] == '}') {
			n2 = i; //如果是右括号将n2赋值为右括号坐标 
			break; 
		}
	}
	for(register int i = n1 + 1; i < n2; i++) { //在左括号和右括号之间循环，此循环处理乘除 
		if(optor[i] == '*') { //如果运算符是乘 
			l = i, r = i; //将左右赋值到运算符坐标 
			while(num[l] == 0 && l > n1) l--; //向左寻找括号内的最近数值 
			while(num[r] == 0 && r < n2) r++; //向右寻找括号内的最近数值 
			num[i] = num[l] * num[r]; //相乘 
			optor[i] = 0, num[l] = 0, num[r] = 0; //清空运算符和两个原始数据 
		}
		if(optor[i] == '/') { //如果运算符是除 
			l = i, r = i; //将左右赋值到运算符坐标 
			while(num[l] == 0 && l > n1) l--; //向左寻找括号内的最近数值 
			while(num[r] == 0 && r < n2) r++; //向右寻找括号内的最近数值 
			num[i] = num[l] / num[r]; //相除 
			optor[i] = 0, num[l] = 0, num[r] = 0; //清空运算符和两个原始数据 
		}
	}
	for(register int i = n1 + 1; i < n2; i++) { //在左括号和右括号之间循环，此循环处理加减 
		if(optor[i] == '+') { //如果运算符是加 
			l = i, r = i; //将左右赋值到运算符坐标 
			while(num[l] == 0 && l > n1) l--; //向左寻找括号内的最近数值
			while(num[r] == 0 && r < n2) r++; //向右寻找括号内的最近数值 
			num[i] = num[l] + num[r]; //相加 
			optor[i] = 0, num[l] = 0, num[r] = 0; //清空运算符和两个原始数据 
		}
		if(optor[i] == '-') { //如果运算符是减 
			l = i, r = i; //将左右赋值到运算符坐标 
			while(num[l] == 0 && l > n1) l--; //向左寻找括号内的最近数值
			while(num[r] == 0 && r < n2) r++; //向右寻找括号内的最近数值 
			num[i] = num[l] - num[r]; //相减 
			optor[i] = 0, num[l] = 0, num[r] = 0; //清空运算符和两个原始数据 
		}
	}
	kh[n1] = 0, kh[n2] = 0; //此次计算完成，清空两侧括号 
	return;
} 

void yunsuan() { //四则运算主要函数 
	string str, kuohao, standard = "0123456789.+-*/()[]{}"; //定义str存放算式，kuohao存放算式中的括号，standard存放合法字符 
	bool f = 0, t = 0; //初始化布尔标识f和t为零 
	cout << "输入算式(英文符号，无空格)" << endl;
	cin >> str;
	for(register int i = 0; i < str.length(); i++) { //循环检验 
		if(str[i] == '.') {
			if((i == 0 || i == str.length() - 1) || ((str[i - 1] < '0' || str[i - 1] > '9') || (str[i + 1] < '0' || str[i + 1] > '9'))) {
				cout << "小数点错误" << endl;
				yunsuan();
				return; 
			}
			for(register int j = i + 1; j < str.length(); j++) {
				if(str[j] == '+' || str[j] == '-' || str[j] == '*' || str[j] == '/') break;
				if((str[j] >= '0' && str[j] <= '9') && str[j + 1] == '.') {
					cout << "多个小数点" << endl;
					yunsuan();
					return; 
				}
			}
		}
		if(str[i] == '(' || str[i] == ')' || str[i] == '{' || str[i] == '}' || str[i] == '[' || str[i] == ']') { //循环将算式中的括号提取出来 
			kuohao += str[i];
		}
		if(str[i] == '/' && str[i + 1] == '0' && str[i + 2] != '.') {
			cout << "被除数不能为零" << endl;
			yunsuan();
			return; 
		}
		if((str[i] == '(' && str[i + 1] == ')') || (str[i] == '[' && str[i + 1] == ']') || (str[i] == '{' && str[i + 1] == '}')) {
			cout << "括号内不能为空" << endl;
			yunsuan();
			return; 
		}
		f = 0;
		for(register int j = 0; j < standard.length(); j++) { //如果有非法字符则算式错误 
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
			cout << "存在非法输入(非法字符或符号不匹配)" << endl;
			yunsuan();
			return; 
		}
	}
	if(!check(kuohao)) {
		cout << "括号匹配错误" << endl;
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
