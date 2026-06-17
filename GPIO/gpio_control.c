#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <gpiod.h>

#ifndef	CONSUMER
#define	CONSUMER	"Consumer"
#endif

int main(int argc, char*argv[]){
	unsigned int status = 0;
	if(argc != 2){
		perror("Must have only one argument.  Options are: On Off\n");
		return 1;
	}
	else{
		if(strcmp(argv[1], "On") == 0){
			status = 1;
		}
		else if(strcmp(argv[1], "Off") == 0){
			status = 0;
		}
		else{
			perror("Invalid argument.  Must be either On or Off.\n");
			return 1;
		}
	}
	
	char *chipname = "gpiochip0";
	unsigned int line_num = 4;	// GPIO Pin #4
	struct gpiod_chip *chip;
	struct gpiod_line *line;
	int ret;
	
	
	chip = gpiod_chip_open_by_name(chipname);
	if (!chip) {
		perror("Open chip failed\n");
		return 1;
	}
	line = gpiod_chip_get_line(chip, line_num);
	if (!line) {
		perror("Get line failed\n");
		return 1;
	}
	
	ret = gpiod_line_request_output(line, CONSUMER, status);
	if (ret < 0) {
		perror("Request line as output failed\n");
		return 1;
	}
	
	//Do Something
	ret = gpiod_line_set_value(line, status);
	
	
	release_line:
		gpiod_line_release(line);
	close_chip:
		gpiod_chip_close(chip);
	end:
	return 0;
}
