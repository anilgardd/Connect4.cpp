#include <iostream>
#include <fstream>

using namespace std; 
int board[10][10];
int turn_player=1;

void game_menu();
void print_board();
int check_game();
void add_token();
void play_loop();
void save_board();
void load_board();
void log_file();

int main(){
    int i,j,m,n;
    game_menu();
    return 0;
}
// hamle kayıtları
void log_file(int column){
    ofstream log;
    log.open("log.txt", ios::app);
    log << turn_player << ". Oyuncu " << column << " sütununa yerleştirdi."<<endl; 
    log.close();
}
// terminale yazdırma
void print_board(){
    int i,j;
    for(i=9;i>=1;i--){
        for(j=1;j<=9;j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}
//kazanma durum kontrolleri
int check_game() {
    int i, j;
    for (i = 1; i <= 9; i++) {
        for (j = 1; j <= 9; j++) {
            if (i + 3 <= 9 && j + 3 <= 9) {
                if (board[i][j] != 0 && board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2] && board[i][j] == board[i + 3][j + 3]) {
                    return board[i][j];
                }
                if (board[i][j] != 0 && board[i][j] == board[i + 1][j - 1] && board[i][j] == board[i + 2][j - 2] && board[i][j] == board[i + 3][j - 3]) {
                    return board[i][j];
                }
            }
            if (j + 3 <= 9) {
                if (board[i][j] != 0 && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2] && board[i][j] == board[i][j + 3]) {
                    return board[i][j];
                }
            }
            if (i + 3 <= 9) {
                if (board[i][j] != 0 && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j] && board[i][j] == board[i + 3][j]) {
                    return board[i][j];
                }
            }
        }
    }
    return 0;
}
//hamle yaptırma
void add_token(){
    int input;
    do{
        cout << "0 ile 9 arasında bir değer girin: ";
        cin >> input;
    } while (input < 0 || input > 9);
    
    if(input == 0){
        game_menu();
        return;
    }
    
    board[board[0][input]+1][input] = turn_player;
    board[0][input] += 1;
    log_file(input);
    print_board();
    int game_status = check_game();
    if (game_status != 0){
        cout << "Oyunu kazanan: " << game_status << endl;
        return; 
    }
    
    if (turn_player == 1){
        turn_player = 2;
    }
    else{
        turn_player = 1;
    }
    
    play_loop();
}

// genel loop
void play_loop(){
    if(turn_player==1){
        cout << "Ana menü için 0 yazabilirsin." << endl;
        cout << "1. Oyuncu: Hangi sütuna yerleştirmek istiyorsun?" << endl;
        add_token();
    }
    else if(turn_player==2){
        cout << "Ana menü için 0 yazabilirsin." << endl;
        cout << "2. Oyuncu: Hangi sütuna yerleştirmek istiyorsun?" << endl;
        add_token();
    }
}
// tahta durumunu kaydetme
void save_board() {
    ofstream file;
    file.open("game_data.txt");
    int i,j;
    for (i=0;i<10;i++) {
        for (j=0;j<10;j++) {
            file<<board[i][j]<<" ";
        }
        file << "\n";
    }
    file << turn_player << "\n";
    file.close();
    cout << "Oyun kaydedildi." << endl;
}
//kayıtlı tahtayı yükleme
void load_board() {
    ifstream file;
    file.open("game_data.txt");
    if (!file) {
        cout << "Dosya bulunamadı!" << endl;
        return;
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            file >> board[i][j];
        }
    }
    file >> turn_player;
    file.close();
    cout << "Oyun yüklendi." << endl;
}
//oyun menüsü
void game_menu(){
    int game_choice;
    cout<< "1-Oyuna Başla" <<endl;
    cout<< "2-Oyunu Kaydet" <<endl;
    cout<< "3-Oyunu Yükle" <<endl;
    cout<< "4-Oyundan Çık" <<endl;

    cin >> game_choice ;

    if(game_choice==1){
        print_board();
        play_loop();
    }
    if(game_choice==2){
        save_board();
    }
    else if(game_choice==3){
        load_board();
    }
    else if(game_choice==4){
        ofstream file("log.txt");
        return;
    }
    else{
        game_menu();
    }
}