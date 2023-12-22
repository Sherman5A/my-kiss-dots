#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


void help(void) {
    printf("Le help menu.\n");
    printf("There are no options.\n");

}

void change_bri(int mod_bri) {

    FILE *fptr;
    fptr = fopen("/sys/class/backlight/amdgpu_bl0/brightness", "r+");

    if (fptr == NULL) {
        perror("fopen");
        printf("Can not get sys backlight.\n");
        return;
    }

    char backlight_content[4];

    fgets(backlight_content, 4, fptr);

    int current_bri = atoi(backlight_content);

    int new_bri = current_bri + mod_bri;

    if ( new_bri > 255 ) {
        new_bri = 255;
    } else if ( new_bri < 2 ) {
        new_bri = 2;
    }

    printf("%d\n", new_bri);

    fptr = freopen("/sys/class/backlight/amdgpu_bl0/brightness", "w", stdout);

    fprintf(fptr, "%d", new_bri);
    fclose(fptr);

    return;
}

int main(int argc, char* argv[]) {


    if (argc != 2) {
        printf("Incorrect number of arguments.\n");
        return 0;
    }

    int i;

    for (i=1; i < argc; i++) {
        if ( (strcmp(argv[1], "-h")) == 0 ) {
            help();
    	    return 0;
        }

        for ( char* pos = argv[1]; *pos != '\0'; pos++ )
            if ( isalpha(*pos) ) {
                printf("Alpha found. Only integers accepted.\n");
                return 0;
    	    }
            int bri_mod = atoi(argv[1]);
            printf("Success.\n");
            change_bri(bri_mod);
    }
    return 0;
}

