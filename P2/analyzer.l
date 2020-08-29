
%%
.*\(\).* ;
#.* ;
[{}] ;
[ \t\n] ;
if|else|while|int|float|char|double|for {printf("kwd ");}
[a-zA-Z][a-zA-Z0-9_]* printf(" id");
[0-9] printf(" literal");
[\+] printf(" oper-plus");
[\-] printf(" oper-minus");
[\/] printf(" oper-divide");
[\*] printf(" oper-multiply");
[\=] printf(" oper-equ");
%%

int main(int ac, char **av) {
    FILE    *fd;
    if (ac == 2) {
        if (!(fd = fopen(av[1], "r"))) {
            perror("Error: ");
            return (-1);
        }
        yyset_in(fd);
        yylex();
        fclose(fd);
    }
    else
        printf("Usage: a.out filename\n");
    printf("\n");
    return (0);
}
