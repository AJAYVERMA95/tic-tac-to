#include <stdio.h>
int showingPosition_onGrid ();
int ConvertPositionIntoGridFormat(int,char ch[3][3]);
int Save_Empty_Grid(char ch[3][3]);
int showingGridAfterIndividualInput(char ch[3][3]);
int calculatePositionOfPlayerAndStoreSymbol(int,int *prow,int *pcol,char ch[3][3] ,char);
int chk_whether_position_is_preoccupied(int,int,char ch[3][3],int,char);
int Game_Refree(int,int,char ch[3][3],char p1[50],char p2[50]);
int GameWiningCondition(char Player_symbol,int count,char ch[3][3],char p1[50],char p2[50]);
int checkingForWinner(char Player_symbol,char ch[3][3]);
int main(){
	int posPlayer,count = 1;
	char ch[3][3],p1[50],p2[50];
	printf("Enter 1st player name :");
	gets(p1);
	printf("Enter 2nd player name :");
	gets(p2);
	Save_Empty_Grid(ch);
	Game_Refree(posPlayer,count,ch,p1,p2);
	return 2;
}
int showingPosition_onGrid (){
	int flag = 1,i,j;
	for(i=1;i<=3;i++){
		for(j=1;j<=3;j++){
			printf(" %d |",flag);
			flag++;
		}
		printf("\n");
	}
	return 1;
}
int Save_Empty_Grid(char ch[3][3]){
	int i,j;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			ch[i][j] = ' ' ;
		}
	}
	return 1;
}
int calculatePositionOfPlayerAndStoreSymbol(int posPlayer,int *prow,int *pcol,char ch[3][3],char Player_symbol){
	scanf("%d",&posPlayer);
	posPlayer = ConvertPositionIntoGridFormat(posPlayer,ch);
	*prow = (posPlayer / 10) -1 ;
	*pcol = (posPlayer % 10)  -1;
	chk_whether_position_is_preoccupied(*prow,*pcol,ch,posPlayer,Player_symbol);
	return 1;
}
int ConvertPositionIntoGridFormat(int posPlayer,char ch[3][3]){
	int CorrectPosPlayer,i,j;
	switch(posPlayer){
		case 1 : posPlayer = 11 ;break;
		case 2 : posPlayer = 12 ;break;
		case 3 : posPlayer = 13 ;break;
		case 4 : posPlayer = 21 ;break;
		case 5 : posPlayer = 22 ;break;
		case 6 : posPlayer = 23 ;break;
		case 7 : posPlayer = 31 ;break;
		case 8 : posPlayer = 32 ;break;
		case 9 : posPlayer = 33 ;break;
		default : showingGridAfterIndividualInput(ch);
		printf("INVALID POSITION.\n\n");
		showingPosition_onGrid ();
		printf("\nEnter correct position as above : \a");
		posPlayer = 0;
		break;
	}
	if(posPlayer == 0){
		scanf("%d",&CorrectPosPlayer);
		posPlayer =	ConvertPositionIntoGridFormat(CorrectPosPlayer,ch);
	}	
	return posPlayer;
}
int chk_whether_position_is_preoccupied(int row,int col,char ch[3][3],int posPlayer,char Player_symbol){
	int i,j;
	if(ch[row][col] == 'X' || ch[row][col] == 'O'){
		printf("\nPosition is PREOCCUPIED.\a\n");
		showingGridAfterIndividualInput(ch);
		printf("\n");		
		showingPosition_onGrid ();
		printf("\nEnter empty position : ");
		calculatePositionOfPlayerAndStoreSymbol(posPlayer,&row,&col,ch,Player_symbol);	
	}
	else ch[row][col] = Player_symbol;
	return 	1;
}
int showingGridAfterIndividualInput(char ch[3][3]){
	int i,j;
	printf("\n\n");
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			printf(" %c |",ch[i][j] );
		}
		printf("\n");
	}
	printf("\n\n");
	return 1;
}
int Game_Refree(int posPlayer,int count,char ch[3][3],char p1[50],char p2[50]){
	int i,j,row,col,end;
	char Player_symbol = 'O';
	if(count % 2 != 0){
		printf("************************************ %s's TURN ********************************\n\n",p1);
		Player_symbol = 'X' ;
	}
	else printf("************************************ %s's TURN *******************************\n\n",p2);
	showingPosition_onGrid ();
	printf("\nEnter position number as given above to place your symbol :  ");
	calculatePositionOfPlayerAndStoreSymbol(posPlayer,&row,&col,ch,Player_symbol);
	showingGridAfterIndividualInput(ch);
	end = GameWiningCondition(Player_symbol,count,ch,p1,p2);
	count++;
	if(count <= 9 && (end != 1))Game_Refree(posPlayer,count,ch,p1,p2);
	return 1;
}
int GameWiningCondition(char Player_symbol,int count,char ch[3][3],char p1[50],char p2[50]){
	int winner;
	winner = checkingForWinner(Player_symbol,ch);
	if(winner == 3){
		(((Player_symbol == 'X') > 0 ) && printf(" %s WIN",p1)) || printf(" %s WIN",p2);
		return 1;
	}
	if(count == 9)printf("MATCH DRAW.");
	return 2;
}
int checkingForWinner(char Player_symbol,char ch[3][3]){
	int i,j,counter = 0;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(ch[i][j] == Player_symbol)counter++;               //for row
		}
		if(counter == 3)break;
		else counter = 0 ;
	}
	if(counter != 3){
		counter = 0 ;
		for(i=0;i<3;i++){                                         //for column
			for(j=0;j<3;j++){
				if(ch[j][i] == Player_symbol)counter++;
			}
			if(counter == 3)break;
			else counter = 0 ;
		}	
	}
	if(counter != 3){
		counter = 0 ;
		for(i=0;i<3;i++){                                         //for diagonal
			if(ch[i][i] == Player_symbol)counter++;
		}	
		if(counter != 3){
			counter = 0 ;
			for(i=0;i<3;i++){                                         //for diagonal
				if(ch[i][2 - i] == Player_symbol)counter++;
			}	
		}
	}
	return counter;
}