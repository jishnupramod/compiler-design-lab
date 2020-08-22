#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int check_operator(char ch) {
    switch(ch) {
        case '+':
            printf(" oper-plus ");
            break;
        case '-':
            printf(" oper-minus ");
            break;
        case '*':
            printf(" oper-mul ");
            break;
        case '/':
            printf(" oper-div ");
            break;
        case '%':
            printf(" oper-mod ");
            break;
        case '=':
            printf(" oper-equ ");
            break;
        default:
            return 0;
    }
    return 1;
}

int check_keyword(char word[]) {
    char keyword_buffer[][10] =  {"auto","break","case","char","const","continue","default",
							"do","double","else","enum","extern","float","for","goto",
							"if","int","long","register","return","short","signed",
							"sizeof","static","struct","switch","typedef","union",
							"unsigned","void","volatile","while"};
     for (int i=0; i<32; ++i) {
        if (strcmp(keyword_buffer[i], word) == 0) {
            printf("kwd ");
            return 1;
        }
    }
    return 0;
}

void check_id(char word[]) {
    int flag = 0;
    if (isalpha(word[0]) || word[0] == '_') {
        for (int i=1; i<strlen(word); ++i) { 
            if (!isalnum((char)word[i]) && word[i] != '_') {
                flag = 1;
                break;
             }                   
        }
    } else
        flag = 1;
    if (!flag)
        printf("id");
    else {
        printf("Error: expected identifier or '('\n");
        exit(0);
    }
}


// Use <space>, <comma>, or <semicolon> as delimiters. 
// Operators cannot act as delimiters.
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: %s <filename>\n", argv[0]);
        return 0;
    }
    FILE *fp, *temp;
    fp = fopen(argv[1], "r");
    if (!fp) {
        printf("\nThe given file cannot be parsed! :( \n");
        exit(0);
    }
    int ch, x = 0;
    char word[20];
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '/') {
            temp = fp;
            int tmp = fgetc(temp);
            if (tmp == '/') {
                while ((ch = fgetc(fp)) != '\n');
            } else if (tmp == '*') {
                while ((ch = fgetc(fp)) != '/');
                ch = fgetc(fp);
            }
        }
        if (ch == '#') {
            while ((ch = fgetc(fp)) != '\n');
        }
        if (check_operator(ch)) {
            if (x != 0) {
                word[x] = '\0';
                x = 0;
                if (!check_keyword(word))
                    check_id(word);
            }
            continue;
        }
        else if (isalnum(ch))
            word[x++] = ch;
        else if ((ch == ' ' || ch == '\n')  && (x != 0)) {
            word[x] = '\0';
            x = 0;
            if (check_keyword(word))
                continue;
            else 
                check_id(word);
        }
        else if (ch == ',' || ch == ';') {
            word[x] = '\0';
            x = 0;
            if (!check_keyword(word))
                check_id(word);
            printf("%c ", ch);    
        }
    }
    printf("\n");
    fclose(fp);
    fclose(temp);
    return 0;
}
