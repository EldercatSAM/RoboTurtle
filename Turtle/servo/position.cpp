#include<iostream>
#include<algorithm>
#include<math.h>
#include<stdlib.h>
using namespace std;

#define ServoNum 12
#define LegNum 4
#define JointNum 3//ÿ���ȵĹؽ���

struct turtle_position{
	//ȡÿ������������������е�Ϊ�����
	double toe_position [LegNum][3];
	double foot_position[LegNum][3];
	double knee_position[LegNum][3];
	const double hip_position[LegNum][3] = {//�����õ����Źؽ�����
		-6.25,6.25,-2.195,
		6.25,6.25,-2.195,
		-6.25,-6.25,-2.195,
		6.25,-6.25,-2.195
	};
	const int initial_theta[LegNum][JointNum] = { //��ʼ��̬ʱ����ĽǶ�
		135,0,0,
		45,0,0,
		-135,0,0,
		-45,0,0 };
	const int revise[ServoNum] = { 1,1,1,1,1,1,1,1,1,1,1,1 }; //���������͹涨��������ͬΪ1���෴Ϊ-1����δ������//Ϊʲô���ܳ�ʼ�� {1}
	const double foot = 5.90; //�����õ��ĳ���
	const double leg = 7.40;
	const double hip = 4.54;
	//const double deviation[3] = { 6.25,6.25,-2.195 };
};

turtle_position calculate(int *Move) {	
	turtle_position sam;
	double theta[ServoNum];
	for (int i = 0; i < ServoNum; i++) {
		theta[i] = (1500 - Move[i]) / 2 * 0.18; //���Ƶ��ת��Ϊtheta�ǣ�����theta��[-90,90]
		//cout << theta[i] << " ";
	}

	for (int i = 0; i < LegNum; i++) {
		sam.knee_position[i][0] = sam.hip_position[i][0] + cos(sam.initial_theta[i][0] + theta[3 * i + 2] * sam.revise[3 * i + 2])*sam.hip;
		sam.knee_position[i][1] = sam.hip_position[i][1] + sin(sam.initial_theta[i][0] + theta[3 * i + 2] * sam.revise[3 * i + 2])*sam.hip;
		sam.knee_position[i][2] = sam.hip_position[i][2];
	}
	//ͶӰ
	/*
	sam.knee_position[0][0] = sam.hip_position[0][0] + cos(135 + theta[2])*sam.hip;
	sam.knee_position[0][1] = sam.hip_position[0][1] + sin(135 + theta[2])*sam.hip;
	sam.knee_position[0][2] = sam.hip_position[0][2];
	sam.knee_position[1][0] = sam.hip_position[1][0] + cos(45 + theta[5])*sam.hip;
	sam.knee_position[1][1] = sam.hip_position[1][1] + sin(45 + theta[5])*sam.hip;
	sam.knee_position[1][2] = sam.hip_position[1][2];
	sam.knee_position[2][0] = sam.hip_position[2][0] + cos(-135 + theta[8])*sam.hip;
	sam.knee_position[2][1] = sam.hip_position[2][1] + sin(-135 + theta[8])*sam.hip;
	sam.knee_position[2][2] = sam.hip_position[2][2];
	sam.knee_position[3][0] = sam.hip_position[3][0] + cos(-45 + theta[11])*sam.hip;
	sam.knee_position[3][1] = sam.hip_position[3][1] + sin(-45 + theta[11])*sam.hip;
	sam.knee_position[3][2] = sam.hip_position[3][2];*/
	//for (int i = 0; i < ServoNum; i++)cout << sam.revise[i] << " ";
	for (int i = 0; i < LegNum; i++) {//�Ƚ�����xoyƽ����ͶӰ���ٸ��ݼ���ϥ�ؽڵķ�������ŵ�����
		//cout <<theta[3 * i + 1] * sam.revise[3 * i + 1] << endl;
		sam.foot_position[i][0] = sam.knee_position[i][0] + cos(sam.initial_theta[i][0] + theta[3 * i + 2] * sam.revise[3 * i + 2])*(sam.leg*cos(sam.initial_theta[i][1] + theta[3 * i + 1]));
		sam.foot_position[i][1] = sam.knee_position[i][1] + sin(sam.initial_theta[i][0] + theta[3 * i + 2] * sam.revise[3 * i + 2])*(sam.leg*cos(sam.initial_theta[i][1] + theta[3 * i + 1]));
		sam.foot_position[i][2] = sam.knee_position[i][2] + sam.leg*sin(sam.initial_theta[i][1] + theta[3 * i + 1] * sam.revise[3 * i + 1]);
	}
	for (int i = 0; i < LegNum; i++) {//��ȫ����
		sam.toe_position[i][0] = sam.foot_position[i][0] + cos(sam.initial_theta[i][0] + theta[3 * i + 2] * sam.revise[3 * i + 2])*(sam.foot*cos(sam.initial_theta[i][2] + theta[3 * i]));
		sam.toe_position[i][1] = sam.foot_position[i][1] + sin(sam.initial_theta[i][0] + theta[3 * i + 2] * sam.revise[3 * i + 2])*(sam.foot*cos(sam.initial_theta[i][2] + theta[3 * i]));
		sam.toe_position[i][2] = sam.foot_position[i][2] + sam.foot*sin(sam.initial_theta[i][2] + theta[3 * i] * sam.revise[3 * i]);
	}
	return sam;
}

void test() {
	int x[12] = { 1500,2500,1500, 1500,2500,1500, 1500,2500,1500, 1500,2500,1500 };
	turtle_position sam = calculate(x);
	cout << "toe:" << endl;
	for (int i = 0; i < LegNum; i++) {
		for (int j = 0; j < 3; j++)
			cout << sam.toe_position[i][j] << " ";
		cout << endl;
	}
	cout << "foot:" << endl;
	for (int i = 0; i < LegNum; i++) {
		for (int j = 0; j < 3; j++)
			cout << sam.foot_position[i][j] << " ";
		cout << endl;
	}
	cout << "knee:" << endl;
	for (int i = 0; i < LegNum; i++) {
		for (int j = 0; j < 3; j++)
			cout << sam.knee_position[i][j] << " ";
		cout << endl;
	}
}
int main() {
	test();
	system("pause");
	return 0;
}