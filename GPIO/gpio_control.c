/**
 * @file gpio_control.c
 * @brief Used to turn GPIO4 on and off
 * @author Jared Hagemann
 * @date 7/17/2026
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gpiod.h>


#define	CONSUMER	"Consumer"


int main(int argc, char*argv[]){	
	if(argc != 2){
		fprintf(stderr,"Must have only one argument.  Options are: On Off\n");
		return 1;
	}
	
	unsigned int status = 0;
	if(strcmp(argv[1], "On") == 0){
		status = 1;
	}
	else if(strcmp(argv[1], "Off") == 0){
		status = 0;
	}
	else{
		fprintf(stderr, "Invalid argument.  Must be either On or Off.\n");
		return 1;
	}
	
	char *chipname = "gpiochip0";
	unsigned int line_num = 4;	// GPIO Pin #4
	struct gpiod_chip *chip;
	struct gpiod_line *line;
	int ret;
	
	
	chip = gpiod_chip_open_by_name(chipname);
	if (!chip) {
		fprintf(stderr, "Open chip failed\n");
		return 1;
	}
	line = gpiod_chip_get_line(chip, line_num);
	if (!line) {
		fprintf(stderr, "Get line failed\n");
		gpiod_chip_close(chip);
		return 1;
	}
	
	ret = gpiod_line_request_output(line, CONSUMER, status);
	if (ret < 0) {
		fprintf(stderr, "Request line as output failed\n");
		gpiod_line_release(line);
		gpiod_chip_close(chip);
		return 1;
	}
	
	//Do Something
	gpiod_line_set_value(line, status);	
	
	gpiod_line_release(line);
	gpiod_chip_close(chip);
	return 0;
}
