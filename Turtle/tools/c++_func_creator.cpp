#include<bits/stdc++.h>
//#include<conio.h>
using namespace std;

int main() {
	//	freopen("C:\\in.txt","r",stdin);
	//	freopen("C:\\out.txt","w",stdout);
	freopen("in.txt", "r", stdin);
	freopen("out.c", "w", stdout);

	/*printf("#!/usr/bin/python\n# -*- coding:utf-8 -*-\n\nimport os\nimport serial\nimport time\nfrom PCA9685 import PCA9685\nimport subprocess\nimport threading\n\ns=(0,35,-20,100,100,80,100,60,25,80,90,115,40)\n\nn=[0,1500,1500,1500,1500,1500,1500,1500,1500,1500,1500,1500,1500]\n\npwm = PCA9685(0x40)\npwm.setPWMFreq(50)\n\n");
	printf("def action(ti,*a):\n	timer=0\n	while 1:\n		for i in range (1,13):\n			pwm.setServoPulse(i,(n[i]+s[i]+((a[i]-n[i])/ti)*timer))\n			#print(n[i]+s[i]+((a[i]-n[i])/ti)*timer)\n		time.sleep(0.001)\n");
	printf("		timer=timer+5\n		if(timer>=ti):\n			for j in range (1,13):\n				n[j]=a[j]\n			break\n\ndef action0():\n	for i in range (1,13):\n		pwm.setServoPulse(i,1500+s[i])\n\n\n");
	*/

	int tot; cin >> tot; getchar();
	for (int i = 1; i <= tot; i++) {
		char name[50];
		gets(name);//
		//cout << "def " << name << "():" << endl;
		int n; cin >> n;
		int b[500];
		int data[500][15];
		for (int p = 1; p <= n; p++) {
			int a;
			cin >> a >> b[p];
			char s[5000];
			gets(s);
			int i = 0;
			int j = 1;
			while (s[i++] != '\n'&&s[i] != EOF) {
				if (s[i] == 'P') {
					int q = 0;
					while (s[++i] != ' ') {
						q = q * 10 + s[i] - '0';
					}
					data[p][j++] = q;
				}
			}
		}
			/*cout << "    ti=" << b << endl;
			cout << "    b=[0,";
			for (int i = 1; i <= 12; i++) {
				cout << data[i];
				if (i != 12)cout << ",";
			}
			cout << "]" << endl;
			cout << "    action(ti,*b)" << endl;
			cout << endl;*/
			cout << "void " << name << "(){" << endl;
			cout << "    #ifndef steps" << endl;
			cout << "    #define steps " <<  n << endl;
			cout << "    int ti[steps] = {";
			for (int i = 1; i <= n; i++){
				cout << b[i];
				if(i!=n)cout << ",";
			}
			cout << "};" << endl;
			cout << "	int b[steps][ServoNum] = {" << endl;
			for (int i = 1; i <= n; i++) {
				cout<<"		";
				for (int j = 1; j <= 12; j++) {
					cout << data[i][j];
					if(j!=12 || i!=n) cout<< ",";
				}
				if(i!=n)cout << endl;
			}
			cout << "};" << endl;
			cout << "	for (int i=0;i<steps;i++)" << endl;
			cout << "		action(ti[i],b[i]);" << endl;
			cout << "	#endif" << endl << "}";
			
		}
	}
