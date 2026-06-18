/**
 * @file gpio_info.c
 * @brief Used to print information about GPIO.  If no input will print all lines.  Can take in single line number.
 * @author Jared Hagemann
 * @date 7/17/2026
 * */
#include <stdio.h>
#include <gpiod.h>

int main(int argc, char*argv[]) {
    int pinnumber = -1;
    if(argc > 2){
        perror("Must have either no arguments are one argument that equals pin number\n");
		return 1;
    }
    if(argc == 2){
        pinnumber = atoi(argv[1]);
    }
    struct gpiod_chip *chip = gpiod_chip_open_by_name("gpiochip0");
    if (!chip) return 1;

    printf("Name: %s\n", gpiod_chip_name(chip));
    printf("Label: %s\n", gpiod_chip_label(chip));
    unsigned int numLines = gpiod_chip_num_lines(chip);
    printf("Number of Lines: %u\n", numLines);
    
    struct gpiod_line *line;
    if(pinnumber >= 0){
        printf("HERE!\n");
        line = gpiod_chip_get_line(chip, pinnumber);
        printf("Offset: %u, Name: %s, Consumer: %s, Direction: %d, Active State: %d, Bias: %d\n", 
                gpiod_line_offset(line), 
                gpiod_line_name(line),
                gpiod_line_consumer(line),
                gpiod_line_direction(line),
                gpiod_line_active_state(line),
                gpiod_line_bias(line));
    }
    else{
        for (int i = 0; i < numLines; i++) {
            line = gpiod_chip_get_line(chip, i);
            printf("Offset: %u, Name: %s, Consumer: %s, Direction: %d, Active State: %d, Bias: %d\n", 
                gpiod_line_offset(line), 
                gpiod_line_name(line),
                gpiod_line_consumer(line),
                gpiod_line_direction(line),
                gpiod_line_active_state(line),
                gpiod_line_bias(line));
        }
    }
    
    gpiod_chip_close(chip);
    return 0;
}
