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
	if(argc != 2){
		perror("Incorrect number of arguments!\n");
		return 1;
	}
	
	char *chipname = "gpiochip0";
	unsigned int line_num = 4;	// GPIO Pin #4
	char *pstatus = argv[1];
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
	
	ret = gpiod_line_request_output(line, CONSUMER, 0);
	if (ret < 0) {
		perror("Request line as output failed\n");
		return 1;
	}
	
	//Do Something
	if(strcmp(pstatus, "On") == 0){
		ret = gpiod_line_set_value(line, 1);
	}
	else{
		ret = gpiod_line_set_value(line, 0);
	}
	
	
	release_line:
		gpiod_line_release(line);
	close_chip:
		gpiod_chip_close(chip);
	end:
	return 0;
}
