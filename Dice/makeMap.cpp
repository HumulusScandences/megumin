#include "makeMap.h"
#include<iostream>
#include <set>
#include <cmath>
#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <functional>
using namespace std;
char arr[80][80];

void makeMap::init(string &mapResult)             //初始化
{
    for(int i=0;i<=80;i++)
    {
        for(int j=0;j<=80;j++)
        {
            if (i%2==1){
                int tmp=j+2;
                if (tmp%4==0){
                    arr[i][j]='|';
                }else{
                    arr[i][j]=' ';
                }
            }else{
                if (j%4==0){
                    arr[i][j]='|';
                }else{
                    arr[i][j]='-';
                }
            }
        }
    }
      string tag="";
    for (int h=0;h<20;h++){
        if (h<10){
            tag+="  0"+std::to_string(h);
        }else{
        tag+="  "+std::to_string(h);
        }
    }
    cout<<tag<<endl;
//    垂直数字标识
    int i,j;
    for (i = 0;i<40;++i)
    {
        string vNum;
        if (i<20){
            vNum="0"+std::to_string(i/2);
        }else{
            vNum=std::to_string(i/2);
        }
         if ( i%2==0){
			 mapResult+=vNum;
         }
        
        for (j = 0;j<80;++j)
			mapResult+=arr[i][j];
		mapResult+="\n";
        }
}

void  makeMap::set(string &mapResult,char flag,int i,int j)          //玩家行动
{
    char key=flag;
    for (int a=0;a<=80;a++){
        for (int b=0;b<=80;b++){
            if (arr[a][b]==key){
                arr[a][b]='|';
            }
        }
    }
    arr[i*2][j*4]=key;
      string tag="";
    for (int h=0;h<20;h++){
        if (h<10){
            tag+="  0"+std::to_string(h);
        }else{
        tag+="  "+std::to_string(h);
        }
    }
    cout<<tag<<endl;
//    垂直数字标识
    for (i = 0;i<40;++i)
    {
       
        string vNum;
        if (i<20){
            vNum="0"+std::to_string(i/2);
        }else{
            vNum=std::to_string(i/2);
        }
         if ( i%2==0){
             cout<<vNum;
         }
        
        for (j = 0;j<80;++j)
            cout<<arr[i][j];
        cout<<endl;
        }
}

makeMap::makeMap(){

}

makeMap::~makeMap(){

}