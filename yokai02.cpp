// yokai02 for g++
// 2021.12.21 kei.

//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char ytoa[256];
void make_ytoa(){
	memset(ytoa,0x00,sizeof(ytoa));
	ytoa['A']=0x00; ytoa['B']=0x08; ytoa['C']=0x10; ytoa['D']=0x18; ytoa['E']=0x20; ytoa['F']=0x28;
	ytoa['G']=0x30; ytoa['H']=0x01; ytoa['I']=0x09; ytoa['J']=0x11; ytoa['K']=0x19; ytoa['L']=0x21;
	ytoa['M']=0x29; ytoa['N']=0x31; ytoa['O']=0x02; ytoa['P']=0x0A; ytoa['Q']=0x12; ytoa['R']=0x1A;
	ytoa['S']=0x22; ytoa['T']=0x2A; ytoa['U']=0x32; ytoa['V']=0x03; ytoa['W']=0x0B; ytoa['X']=0x13;
	ytoa['Y']=0x1B; ytoa['Z']=0x23; ytoa['-']=0x2B; ytoa['.']=0x33; ytoa['1']=0x04; ytoa['2']=0x0C;
	ytoa['3']=0x14; ytoa['4']=0x1C; ytoa['5']=0x24; ytoa['6']=0x05; ytoa['7']=0x0D; ytoa['8']=0x15;
	ytoa['9']=0x1D; ytoa['0']=0x25; ytoa['!']=0x2D; ytoa['n']=0x2C; ytoa['m']=0x34; ytoa['c']=0x35;
	//ytoa['ﾅ']=0x2C; ytoa['ﾑ']=0x34; ytoa['ｺ']=0x35; // 念のためﾅﾑｺも処理
}


int main(int argc, char* argv[])
{
	char a31DC[256];
	char temp=0;
	int i=0;
	int stackApos=0,stackXpos=0,stackYpos=0;
	static int stackA[256];

	int A=0,X=0,Y=0,C=0,Z=0;
	int a31F6=0; // 文字列長さ
	int a31F4=0,a31F5=0,a31F7=0,a31F8=0,a31F9=0,a31FA=0,a31FB=0;
	int ror=0;
	int loopmode=0;

	if(argc==1){
		printf("yokai-test02 check digit $31F4 $31F5 simulator\n");
		loopmode=1;
	}else{
		strcpy(a31DC,argv[1]);
	}
	// 文字テーブル作成
	make_ytoa();

LOOP:
	if(loopmode==1){
		// printf("INPUT PASSWORD:");
		// gets(a31DC);
	}
	a31F6=strlen(a31DC);

	// ここで文字コードをコンバートしておく
	for(i=0;i<a31F6;i++){
		temp=ytoa[a31DC[i]];
		a31DC[i]=temp;
	}

// スタート
	X=0;
	C=0;
	a31F4=0;
	a31F5=0;
	a31F7=0;
	a31F8=0;
	a31F9=0;
	a31FB=0;
	A=1;
	a31FA=A;

D86B:
	A=a31DC[X];

D8BD:
	stackA[stackApos++]=A;
	Y=8;
D8C0:
	A = A << 1;

	if(A>0xFF){
		C=1;
		A=A&0xFF;
	}else{
		C=0;
	}
	stackA[stackApos++]=A;
// 31F4と31F5を右1ビットローテート
	ror = a31F4 &0x01;
	a31F4 = a31F4 >> 1;
	a31F4 = a31F4 | (C << 7); // C0000000
	C=ror;

	ror = a31F5 &0x01;
	a31F5 = a31F5 >> 1;
	a31F5 = a31F5 | (C << 7); // C0000000
	C=ror;

	//printf("ror %02X %02X\n",a31F4,a31F5);

	A = 0;
	A = 0xFF + C;
	if(A>0xFF){ A=0; C=1; }else C=0;
	A = A ^ 0xFF;
	stackA[stackApos++]=A;
	A = A & 0x84;
	A = A ^ a31F4;
	a31F4 = A;
	A = stackA[--stackApos];
	A = A & 0x08;
	A = A ^ a31F5;
	a31F5 = A;
	A = stackA[--stackApos];
	Y--;
	if(Y>0) goto D8C0;
	A = stackA[--stackApos]; // ここまでで31F4と31F5算出完了

D8A4: // 31F7と31F8を生成(Complete)
	stackA[stackApos++]=A;
	stackA[stackApos++]=A;
	A = a31F4;
	if(A>=0xE5){  C=1; }else C=0; //C5の値でキャリーを生成
	A = stackA[--stackApos];
	A = A + a31F7 + C;
	if(A>0xFF){ // ADCのキャリー処理
		A = A & 0xFF;
		C = 1;
	}else C=0;
	a31F7 = A;
	A = a31F8;
	A = A + a31F5 + C;
	if(A>0xFF){ // ADCのキャリー処理
		A = A & 0xFF;
		C = 1;
	}else C=0;
	a31F8 = A;
	A = stackA[--stackApos];

D89B: // 31F9を生成(Complete)
	stackA[stackApos++]=A;
	A = A ^ a31F9;
	a31F9 = A;
	A = stackA[--stackApos];

// ここから下にまだバグがある

D88F: // 31FAを生成
	stackA[stackApos++]=A;
	// 31FAをローテート
	ror = a31FA & 0x01;
	a31FA = a31FA >> 1;
	a31FA = a31FA | (C << 7); // $31F8のCがここで入る
	C = ror;
	A = A + a31FA + C;
	if(A>0xFF){ // ADCのキャリー処理
		A = A & 0xFF;
		C = 1;
	}else C=0;
	a31FA = A;

	A = stackA[--stackApos];

D87F:
	stackA[stackApos++]=A;
D880: // 31FBを生成
	// Aを左ローテート
	A = A << 1;
	if(A>0xFF){ // ADCのキャリー処理
		A = A & 0xFF;
		C = 1;
	}
	if(A==0) Z=1; else Z=0; // 演算結果がゼロの時Z=1;

	stackA[stackApos++]=A; // スタックに値を保存
	A = a31FB;
	A = A + C;
	if(A>0xFF){ // ADCのキャリー処理
		A = A & 0xFF;
		C = 1;
	}else C=0;
	a31FB = A;

	A = stackA[--stackApos];
	if(!Z) goto D880; // ローテ終わるまでループ
	//printf("a31FB=%x ",a31FB);

	A = stackA[--stackApos];

// 文字数分だけ演算をカウント
	X++;
	if(a31F6!=X) goto D86B;


	//printf("31F4 31F5 31F6 31F7 31F8 31F9 31FA 31FB\n");
	printf("%02X %02X %02X %02X %02X %02X %02X %02X\n"
		,a31F4,a31F5,a31F6,a31F7,a31F8,a31F9,a31FA,a31FB);
/*
	printf("31F4 31F5 31F6 31F7 31F8 31F9\n");
	printf("  %02X   %02X   %02X   %02X   %02X   %02X\n"
		,a31F4,a31F5,a31F6,a31F7,a31F8,a31F9);
*/
	// if(loopmode) goto LOOP;

	return 0;
}
