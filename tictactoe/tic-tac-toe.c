#include <stdio.h>

//function prototype
char fill(int i); //fill the board if computer is X
char fill2(int i); //fill the board if computer is O
void boardnow(int board[9], int c); //board state
int wincheck(const int board[9]); //winner check
int minimax(int board[9], int player); //minimax
void computer(int board[9]); //computer turn
void player(int board[9]); //player turn

int main() {
    int board[9] = {0,0,0,0,0,0,0,0,0};
    char p;
    char c;
    int turn, ch;
    
    printf("TIC TAC TOE\n");
    printf("You VS Computer\n");
    printf("Choose:\n");
    start:
    printf("Play (1) O or (2) X? ");
    scanf("%c", &c);
    getchar();
    if(c == '1' || c == 'O'){
    	ch = 1;
	}
	else if(c == '2' || c == 'X'){
		ch = 2;
	}
	else{
		printf("Choose (1) O or (2) X only\n");
		goto start;
	}
	printf("Choose:\n");
	    first:
	    printf("Play (1)st or (2)nd? ");
	    scanf("%c", &p);
	    printf("\n");
	
	    if(p == '1'){
	    	for(turn = 1; turn <= 9 && wincheck(board) == 0; turn++) {
		        if(turn % 2 == 0)
		            computer(board);
		        else {
		            boardnow(board, ch);
		            player(board);
		        }
	    	}
	    }
	    else if(p == '2'){
	    	for(turn = 1; turn <= 9 && wincheck(board) == 0; turn++) {
		        if(turn % 2 != 0){
		            computer(board);
				}
		        else {
		        	boardnow(board, ch);
		            player(board);
		        }
	    	}
		}
		else{
			printf("Choose (1) or (2) only\n");
			goto first;
		}
	    
	    switch(wincheck(board)) {
	        case 0:
	        	boardnow(board, ch);
	            printf("\nDraw\n");
	            break;
	        case 1:
	            boardnow(board, ch);
	            printf("\nComputer win\n");
	            break;
	        case -1:
	        	boardnow(board, ch);
	            printf("\nYou win\n");
	            break;
	    }
}
char fill(int i) {
    switch(i) {
        case -1:
            return 'O';
        case 0:
            return ' ';
        case 1:
            return 'X';
    }
}

char fill2(int i) {
    switch(i) {
        case -1:
            return 'X';
        case 0:
            return ' ';
        case 1:
            return 'O';
    }
}

void boardnow(int board[9], int c) {
	if(c == 1){
		printf(" %c | %c | %c\n",fill(board[0]),fill(board[1]),fill(board[2]));
	    printf("---|---|---\n");
	    printf(" %c | %c | %c\n",fill(board[3]),fill(board[4]),fill(board[5]));
	    printf("---|---|---\n");
	    printf(" %c | %c | %c\n",fill(board[6]),fill(board[7]),fill(board[8]));
	}
	else{
		printf(" %c | %c | %c\n",fill2(board[0]),fill2(board[1]),fill2(board[2]));
	    printf("---|---|---\n");
	    printf(" %c | %c | %c\n",fill2(board[3]),fill2(board[4]),fill2(board[5]));
	    printf("---|---|---\n");
	    printf(" %c | %c | %c\n",fill2(board[6]),fill2(board[7]),fill2(board[8]));
	}
    
}

int wincheck(const int board[9]) {
    int winstate[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i) {
        if(board[winstate[i][0]] != 0 && board[winstate[i][0]] == board[winstate[i][1]] &&
           board[winstate[i][1]] == board[winstate[i][2]]){
           	return board[winstate[i][2]];
		   }
            
    }
    return 0;
}

int minimax(int board[9], int player) {
    int winner = wincheck(board);
    if(winner != 0){
    	return winner*player;
	}
    int move = -1;
    int score = -2;
    int scorenow;
    int i;
    for(i = 0; i < 9; ++i) {
        if(board[i] == 0) {
            board[i] = player;
            scorenow = -minimax(board, player*-1);
            if(scorenow > score) {
                score = scorenow;
                move = i;
            }
            board[i] = 0;
        }
    }
    if(move == -1){
    	return 0;
	}
    return score;
}

void computer(int board[9]) {
    int move = -1;
    int score = -2;
    int temp;
    int i;
    for(i = 0; i < 9; ++i) {
        if(board[i] == 0) {
            board[i] = 1;
            temp = -minimax(board, -1);
            //printf("%d\n", temp);
            board[i] = 0;
            if(temp > score) {
                score = temp;
                move = i;
            }
        }
    }
    board[move] = 1;
}

void player(int board[9]) {
    int move = 1;
    while(1){
        printf("\nInput move: ");
        scanf("%d", &move);
        if(move > 9 || move < 1){
			printf("Invalid number. Input 1 - 9\n");
			continue;
		}
        else if(board[move-1] != 0){
        	printf("It's occupied\n");
        	continue;
		}
        else{
        	break;
		}
    }
    board[move-1] = -1;
}
