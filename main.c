#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define ROOTDIR "/sys/class/backlight/gmux_backlight" 

int
get_max_brightness(){
    int max_b = 0;

    FILE *fp = fopen(ROOTDIR"/max_brightness", "r");
    fscanf(fp, "%d", &max_b);
    fclose(fp);

    return max_b;
}

int
get_current_brightness(){
    int brightness = 0;
    FILE *fp = fopen(ROOTDIR"/brightness", "r");
    fscanf(fp, "%d", &brightness);
    fclose(fp);
    return brightness;
}


void
change_brightness(int percentage){
    float max_brightness = (float)get_max_brightness();
    float current_perc = ((float)get_current_brightness() / max_brightness) * 100.;
    int new_percentage = current_perc + percentage;
    float set_value = max_brightness / 2.;  // default should be mid light

    if ( new_percentage > 100 )
        set_value = max_brightness;
    else if ( new_percentage < 0 )
        set_value = 0;
    else
        set_value = (new_percentage / 100.) * max_brightness;

    FILE *fp = fopen(ROOTDIR"/brightness", "w");
    fprintf(fp, "%d", (int)set_value);
    fclose(fp);
}


void usage() {
    printf( "Usage: backlight [[--inc|--dec] percentage change]|[--get]\n" );
    exit(1);
}


int
main( int argc, char *argv[] ) {

    char *p;
    int amount;

    if ( argc == 2 ) {
        if ( strcmp(argv[1], "--get") == 0 )
            printf("%.2f\n", ((float)get_current_brightness() / get_max_brightness()) * 100.);
        else 
            usage();
    }
    else if ( argc == 3 ) {
        errno = 0;
        long conv = strtol(argv[2], &p, 10);    
        
        if (errno != 0 || *p != '\0' || conv > INT_MAX) {
            printf("Bad number supplied\n");
            usage();
        }
        else {
            amount = conv;
        }

        if ( strcmp(argv[1], "--inc") == 0) {
            change_brightness(amount);
        }
        else if ( strcmp(argv[1], "--dec") == 0 ) {
            change_brightness(-amount);
        }
        else {
            usage();
        }
    }
    else 
        usage();

}
