# Tic Tac Toe dengan Minimax
  Minimax merupakan metode yang digunakan dalam pengambilan keputusan dan teori permainan untuk menemukan langkah optimal bagi pemain, dengan asumsi bahwa lawan juga bermain secara optimal. Kedua pemain disebut maximizer dan minimizer. Maximizer mencoba untuk mendapatkan skor setinggi mungkin sementara minimizer mencoba melakukan yang sebaliknya dan mendapatkan skor serendah mungkin. Setiap state pada board memiliki nilai yang terkait dengannya. Dalam keadaan tertentu jika maximizer lebih unggul, skor pada board akan cenderung bernilai positif, disini akan bernilai '0'. Jika minimizer yang unggul pada board maka akan cenderung menjadi nilai negatif, disini akan bernilai '-1'. Sehingga gerak dari computer akan ditentukan hasil minimax tersebut.
  
# Penjelasan
  Pada state awal, board berisi nilai '0' semua.
  ``` 
  int board[9] = {0,0,0,0,0,0,0,0,0}; 
  ```
  Fungsi fill merupakan fungsi untuk mengisi lambang 'X' dan atau 'O' pada board jika player memilih menjadi O. Fungsi fill mengembalikan lambang yang cocok untuk state board saat ini. Player dilambangkan '-1' dan computer '1', jika pada board di sel nomor 1 memiliki nilai '1' maka fungsi fill mengembalikan nilai 'X' untuk di tampilkan sebagai isi board.
  ```
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
```
Sementara fungsi fill2 merupakan fungsi untuk mengisi lambang 'X' dan atau 'O' pada board jika player memilih menjadi 'X'. Fungsi fill2 merupakan kebalikan fungsi fill.
```
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

```
Fungsi boardnow merupakan fungsi untuk menampilkan keadaan board saat ini.
```
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
```
Fungsi wincheck adalah fungsi untuk melakukan check pada board apakah sudah ada pemenang pada state board saat ini. Fungsi mengembalikan nilai dari isi salah satu sel di board yang terdeteksi menang. Misalnya ada 3 sel berurutan secara horizontal, vertikal, ataupun diagonal memiliki nilai sama maka terdeteksi ada pemenang, fungsi mengambil nilai salah satu dari 3 sel tersebut untuk di-return. Jika return value adalah 1 maka computer win atau return value adalah -1 maka player win. Jika tidak terdeteksi kemenangan maka akan mengembalikan nilai 0.
```
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
```
Pada fungsi minimax akan dicari semua kemungkinan yang tersedia untuk kondisi board saat ini. Dalam mencari semua kemungkinan, fungsi akan memutar papan dan berpura-pura menjadi pemain lain pada ``` -minimax(board, player*-1) ```.  Variabel scorenow menyimpan nilai negatif dari return value rekursif minimax, karena nilai terbaik untuk lawan berarti nilai terburuk untuk kita.
```
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
```
Fungsi computer merupakan fungsi untuk menentukan pergerakan computer pada tiap gilirannya. Pada fungsi ini mencoba semua langkah yang mungkin, memanggil minimax untuk setiap langkah yang mungkin, kemudian menggunakan hasil terbaik.

```
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
```
Fungsi player merupakan fungsi untuk giliran player. Fungsi menerima langkah sesuai input dari user dan mengecek apakah sel pada board yang ingin diisi masih kosong atau sudah ditempati serta menghalangi user menginput yang tidak sesuai.
```
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
```
