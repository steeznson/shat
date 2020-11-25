#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#ifdef MACOS
#define PATH_MAX 4096
#endif

void check_num_args(int argc){
    if (argc != 2){
        printf("This util only takes one argument\n");
        exit(1);
    }
}

char *detect_path(char *argv[]){
    char cwd[PATH_MAX];
    char first_char = argv[1][0];
    /* accept absolute path; spurn relative path */
    if (first_char == '/'){
        return argv[1];
    } else if (first_char == '.'){
        int length = strlen(argv[1]);
        if (length == 1 || length == 2){
            printf("This util can only read text files\n");
            exit(1);
        }
        if (argv[1][1] == '/' || argv[1][1] == '.'){
            printf("`shat` is too shit to handle relative paths\n");
            exit(1);
        }
    }
    /* if we got here, target file is in current directory */
    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/");
    return strcat(cwd, argv[1]);
}

int main(int argc, char *argv[]){
    char parse_char;
    FILE *to_read;
    /* ascertain file path */
    check_num_args(argc);
    char *path = (char *)malloc(PATH_MAX);
    strcpy(path, detect_path(argv));
    /* open file */
    to_read = fopen(path, "r");
    if (to_read == NULL){
        printf("Cannot open file\n");
        exit(1);
    }
    /* read it! */
    parse_char = fgetc(to_read);
    while (parse_char != EOF){
        printf("%c", parse_char);
        parse_char = fgetc(to_read);
    }
    /* tidy up */
    free(path);
    fclose(to_read);
    return 0;
}
