//
//  main.cpp
//  box
//
//  Created by chen jeremy on 5/23/16.
//  Copyright © 2016 chen jeremy. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;


char map[1000][1000];//column start with 1,row start with 1
int i=1;
int size[1000];
int player_row,player_column,box_row,box_column,dest_row,dest_column,win=0;
int way[1000][1000]={0};
int b=0;
string filename;


void control(int playercurrent_row,int playercurrent_column,int boxcurrent_row,int boxcurrent_column);//玩家控制
void swap(int row1,int column1,int row2,int column2);//位子交換
void printMap(int totalrow);//畫面輸出
void determinelocation();//判斷走到，玩家，箱子，終點的位子


int main(int argc, const char * argv[]) {
    // insert code here...
    fstream file_size,file_map;
    
    cout << "Insert filename(xxx.txt):";
    cin >> filename;
    
    file_size.open(filename, ios::in);
    file_map.open(filename, ios::in);
    
    while (file_size >> size[i] ) {i++;};//放入size array
    while(file_map.getline(map[b]+1,sizeof(map),'\n')){b++;};//放入map array
    
    printMap(size[1]);
    
    determinelocation();

    while (1) {
        control(player_row,player_column,box_row,box_column);
        determinelocation();
        system("clear");
        printMap(size[1]);
        if (win==1) {
            cout << "You Win!!!\n";
            break;
        }
    }
    
    return 0;
}


void swap(int row1,int column1,int row2,int column2) {
    
    char temp;
    temp = map[row1][column1];
    map[row1][column1] = map[row2][column2];
    map[row2][column2] = temp;
}

void control(int playercurrent_row,int playercurrent_column,int boxcurrent_row,int boxcurrent_column){
    
    char control;
    while(1){
        cout << "'a':left, 'd':right, 's':down, 'w':up\n";
        cin >> control;;
        if(control=='a'|| control=='s'|| control=='d'|| control=='w')
            break;
        else cout << "Wrong input\n";
    }
    //走左，左方沒箱子
    if (control== 'a' && way[playercurrent_row][playercurrent_column-1] ==1) {
        
        swap(playercurrent_row,playercurrent_column,playercurrent_row,playercurrent_column-1);
        
    }
    //走左，左方有箱子
    else if(control== 'a' && boxcurrent_row == playercurrent_row && boxcurrent_column == playercurrent_column-1 && (way[boxcurrent_row][boxcurrent_column-1] ==1 || way[boxcurrent_row][boxcurrent_column-1] ==2)){
        
        if (way[boxcurrent_row][boxcurrent_column-1] ==1) {
            swap(boxcurrent_row,boxcurrent_column,boxcurrent_row,boxcurrent_column-1);
            swap(playercurrent_row,playercurrent_column,playercurrent_row,playercurrent_column-1);

        }else{
            cout << "You Win!!!\n";
            map[dest_row][dest_column] = '-';
            swap(boxcurrent_row,boxcurrent_column,boxcurrent_row,boxcurrent_column-1);
            swap(playercurrent_row,playercurrent_column,playercurrent_row,playercurrent_column-1);
            win=1;
        }
    }
    //走下，下方沒箱子
    else if (control== 's' && way[playercurrent_row+1][playercurrent_column] ==1) {
        
        swap(playercurrent_row,playercurrent_column,playercurrent_row+1,playercurrent_column);
        
    }
    //走下，下方有箱子
    else if(control== 's' && boxcurrent_row == playercurrent_row+1 && boxcurrent_column == playercurrent_column && (way[boxcurrent_row+1][boxcurrent_column] ==1 || way[boxcurrent_row+1][boxcurrent_column] ==2)){
        
        if (way[boxcurrent_row+1][boxcurrent_column] ==1) {
            swap(boxcurrent_row,boxcurrent_column,boxcurrent_row+1,boxcurrent_column);
            swap(playercurrent_row,playercurrent_column,playercurrent_row+1,playercurrent_column);
        }else{
            cout << "You Win!!!\n";
            map[dest_row][dest_column] = '-';
            swap(boxcurrent_row,boxcurrent_column,boxcurrent_row+1,boxcurrent_column);
            swap(playercurrent_row,playercurrent_column,playercurrent_row+1,playercurrent_column);
            win=1;
        }
    }
    //走右，下方沒箱子
    else if (control== 'd' && way[playercurrent_row][playercurrent_column+1] ==1) {
        
        swap(playercurrent_row,playercurrent_column,playercurrent_row,playercurrent_column+1);
      
    }
    //走右，下方有箱子
    else if (control== 'd' && boxcurrent_row == playercurrent_row && boxcurrent_column == playercurrent_column+1 && (way[boxcurrent_row][boxcurrent_column+1] ==1 || way[boxcurrent_row][boxcurrent_column+1] ==2)){
        
        if (way[boxcurrent_row][boxcurrent_column+1] ==1) {
            swap(boxcurrent_row,boxcurrent_column,boxcurrent_row,boxcurrent_column+1);
            swap(playercurrent_row,playercurrent_column,playercurrent_row,playercurrent_column+1);

        }else{
            cout << "You Win!!!\n";
            map[dest_row][dest_column] = '-';
            swap(boxcurrent_row,boxcurrent_column,boxcurrent_row,boxcurrent_column+1);
            swap(playercurrent_row,playercurrent_column,playercurrent_row,playercurrent_column+1);
            win=1;
        }
    }
    //走上，下方沒箱子
    else if (control== 'w' && way[playercurrent_row-1][playercurrent_column] ==1) {
        swap(playercurrent_row,playercurrent_column,playercurrent_row-1,playercurrent_column);
        
    }
    //走上，下方有箱子
    else if  (control== 'w' && boxcurrent_row == playercurrent_row-1 && boxcurrent_column == playercurrent_column && (way[boxcurrent_row-1][boxcurrent_column] ==1 || way[boxcurrent_row-1][boxcurrent_column] ==2)){
    
        if (way[boxcurrent_row-1][boxcurrent_column] ==1) {
            swap(boxcurrent_row,boxcurrent_column,boxcurrent_row-1,boxcurrent_column);
            swap(playercurrent_row,playercurrent_column,playercurrent_row-1,playercurrent_column);
        }else{
            cout << "You Win!!!\n";
            map[dest_row][dest_column] = '-';
            swap(boxcurrent_row,boxcurrent_column,boxcurrent_row-1,boxcurrent_column);
            swap(playercurrent_row,playercurrent_column,playercurrent_row-1,playercurrent_column);
            win=1;
        }
    }
    else{cout << "You can't go that way\n";}

}
//畫面輸出
void printMap(int totalrow){
    
    for (int i=1; i<=totalrow; i++) {
        cout << map[i]+1 << endl;
    }
    
}
//判斷走到，玩家，箱子，終點的位子
void determinelocation(){

    for (int i = 1; i<=size[1]; i++) {
        for (int j = 1; j<=size[2]; j++) {
            if (map[i][j] =='0') {
                player_row = i;
                player_column = j;
            }
            if (map[i][j] =='1') {
                box_row = i;
                box_column = j;
            }
            if (map[i][j] =='-') {
                way[i][j] = 1;
                
            }else if(map[i][j] =='2'){
                way[i][j] = 2;
                dest_row = i;
                dest_column = j;
            }
             else{
                 way[i][j] = 0;
             }
        }
    }
}




