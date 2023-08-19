#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "hangman.h"


#define MAX_WORD_LEN 50


int file_length(FILE* file_ptr, char ch){
    int c = 0;

    //Get number of words in the file
    while((ch = fgetc(file_ptr)) != EOF){
        if(ch == ' ' || ch == '\n'){c++;}
    }

    return c-1;
}

int gen_rand_num(int file_length){
    srand(time(NULL)); //rand init seed
    
    int lower = 0, upper = file_length, count = 10; //generate 10 times (take last number)

    srand(time(0));
    
    int num = 0;

    for (int i = 0; i < count; i++) {
        num = (rand() % (upper - lower + 1)) + lower;
    }

    return num;
}

char* rand_word(FILE* file_ptr, char ch, int file_length){
    char* word = malloc(MAX_WORD_LEN * sizeof(char));
    int rand_num = gen_rand_num(file_length);
    int counter = 0;

    while(fgets(word, MAX_WORD_LEN, file_ptr)){
        counter++;
        if(counter == rand_num){
            break;
        }
    }
    
    return word;
}

char* arrayatize(char* word){
    char* arr_ptr;
    int w_len = strlen(word);

    arr_ptr = (char*)malloc(w_len * sizeof(char)); //alloc space for chars

    if(arr_ptr == NULL){ //check if alloc is successful
        printf("memory not allocated.\n");
    }
    else{ //assign word chars to char array
        for(int i=0; i < w_len; i++){
            arr_ptr[i] = word[i];
        }
    }

    return arr_ptr; //return ptr to char array
}

void displayboard(int pic_num){
    char* pics[] = {
        "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n========="
    };
    
    printf("%s\n", pics[pic_num]); //print hangman picture

}

void intro_banner(){
    char* message[] = {"------------------------------------------------------------------------\n",
                       "{}    {}    {}{}    {}    {}    {}}}}}    {}      {}    {}{}    {}    {}\n",
                       "{}    {}   {}  {}   {}}}  {}   {}    {}   {}}}  {{{}   {}  {}   {}}}  {}\n",
                       "{}{{}}{}  {}{{}}{}  {} {} {}   {}         {} {{}} {}  {}{{}}{}  {} {} {}\n",
                       "{}    {}  {}    {}  {}  {{{}   {}  {{{{   {}  {}  {}  {}    {}  {}  {{{}\n",
                       "{}    {}  {}    {}  {}    {}    {}}}}}    {}      {}  {}    {}  {}    {}\n",
                       "------------------------------------------------------------------------\n",
                       "\n"};
    for(int i=0; i<8; i++){
        printf("%s", message[i]);
    }
}

void win_message(){
    char* win_msg[] = {"oooooo   oooo   .oooooo.   ooooo     ooo      oooooo   oooooo     oooo ooooo ooooo      ooo\n",
                       " `888.   .8'   d8P'  `Y8b  `888'     `8'       `888.    `888.     .8'  `888' `888b.     `8'\n",
                       "  `888. .8'   888      888  888       8         `888.   .8888.   .8'    888   8 `88b.    8 \n", 
                       "   `888.8'    888      888  888       8          `888  .8'`888. .8'     888   8   `88b.  8 \n", 
                       "    `888'     888      888  888       8           `888.8'  `888.8'      888   8     `88b.8 \n", 
                       "     888      `88b    d88'  `88.    .8'            `888'    `888'       888   8       `888 \n", 
                       "    o888o      `Y8bood8P'     `YbodP'               `8'      `8'       o888o o8o        `8 \n",
                      "\n"};

    int count = 0;
    while(count < 3){
        for(int i=0; i<8;i++){
            printf("%s", win_msg[i]);
        }
        sleep(1);
        system("cls");
        sleep(1);
        count++;
    }
}

char menu(){
    char* menu[] = {"1: Play Game\n", 
                    "2: Add New Word\n",
                    "3: Help/How to Play\n",
                    "4: Quit\n"};

    printf("Menu:\n");
    for(int i=0; i<4; i++){
        printf("%s", menu[i]);
    }
    char choice; //user choice

    printf("\nYou pick: ");
    scanf("%c", &choice);
    

    return choice;
}

char* update_guess(char* word, char* char_array, char guess, int size){

    for(int i=0; i<size-1; i++){
        if(word[i] == guess){
            char_array[i] = guess;
        }
    }

    return char_array;
}

void print_blanks(char* char_array, int size){ //print blanks
    
    printf("\n");
    for(int j=0; j<size-1; j++){
        printf("%c ", char_array[j]);
    }
    printf("\n\n");
}

int check_guess(char* word, int size, char guess){
    int count = 0;
    for(int i=0; i<size; i++){
        if(word[i] == guess){
            return 1;
        }
    }
    return 0;
}

int complete(char* char_array, int size){
    int count = 0;
    for(int i=0; i<size; i++){
        if(char_array[i] == '_'){
            count++;
        }
    }
    if(count > 0){
        return 0;
    }
    else{
        return 1;
    }
}

void choice_one(char* word){
    int size = strlen(word);
    word[size-1] = '\0';

    //allocate space for new array & load with characters
    char* char_array = (char*)malloc((size - 1) * sizeof(char));
    for(int i=0; i<size-1; i++){
        char_array[i] = '_';
    }
    
    char guess;
    int count = 0;

    while(1){
        system("cls");                  //clear screen 
        displayboard(count);            //display hangman iteration
        print_blanks(char_array, size); //display blank slots
        fflush(stdin);
        
        //check if full word is achieved
        if(complete(char_array, size) == 1){
            sleep(1);
            system("cls");
            win_message();
            break;
        }

        if(count + 1 == 7){
                printf("Too many tries! You lose!");
                sleep(2.5);
                break;
        }

        printf("Guess: ");  
        scanf("%c", &guess); //receive input
        //----------------------------------------------
        
        //check guess
        if(check_guess(word, size, guess) == 1){ //if guess is in word, update array
            
            //update array
            char_array = update_guess(word, char_array, guess, size);
            //char_array[size-1] = '\0';
            
            
            
        }

        else{ //if not, increment counter
            printf("Not in word!\n");
            count++;
            sleep(1.5); //display msg for 1.5 sec, then update screen
        }

    }

}



int game(char* word){
    char* array = arrayatize(word); //char array
    int w_len = strlen(word);
    int checker = 0;

    while(1){
        system("cls");
        intro_banner();             //print HANGMAN banner
        char user_choice = menu();  //display menu, receive user choice

        if(user_choice == '1'){
            choice_one(word);
            fflush(stdin);
            checker = 1;
            break;
        }
        else if(user_choice == '2'){
            printf("Add new word!");
            fflush(stdin);
            sleep(2);
            checker = 1;
            break;
            //call function to add word to text file. return to menu
        }
        else if(user_choice == '3'){
            printf("How to play!");
            checker = 1;
            break;
            //call function to display help page. return to menu
        }
        else if(user_choice == '4'){
            printf("Quitting game now.");
            checker = 0;
            break;
        }
        else{
            printf("\nInvalid choice. Try again");
            fflush(stdin);
            sleep(2);
            system("cls");
        }
        
    }

    return checker; //exit game
}





int main(){
    while(1){
        system("cls");
        FILE* ptr; //file ptr
        char ch;   //file character
        
        ptr = fopen("wordlist.txt", "r");

        //Check if file exists & can be opened
        if(NULL == ptr){
            printf("file can't be opened\n");
            return 0;
        }
        else{
            int count = file_length(ptr, ch); //number of words in file

            rewind(ptr); //set pointer back to top of file
            char* word = rand_word(ptr, ch, count); //generate random word from file
            
            if(game(word) == 0){ //start game
                break;
            } 
        }
    }
    
    return 0;
}