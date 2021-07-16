#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>

#ifndef	CONSUMER
#define	CONSUMER	"Consumer"
#endif
bool state=false;
void beeper_callback(const std_msgs::Bool& msg)
{
	state=msg.data;
}

int main(int argc,char **argv) 
{
	ros::init(argc,argv,"beeper");
	ros::NodeHandle node_obj;
	ros::Rate loop_rate(5);
    ros::Subscriber beeper_subscriber= node_obj.subscribe("/drone/beeper",10,beeper_callback);
		char *chipname = "gpiochip0";
	unsigned int line_num = 23;	// GPIO Pin #23
	struct gpiod_chip *chip;
	struct gpiod_line *line;
	int i, ret;

	chip = gpiod_chip_open_by_name(chipname);
	if (!chip) {
		perror("Open chip failed\n");
		goto end;
	}

	line = gpiod_chip_get_line(chip, line_num);
	if (!line) {
		perror("Get line failed\n");
		goto close_chip;
	}

	ret = gpiod_line_request_output(line, CONSUMER, 0);
	if (ret < 0) {
		perror("Request line as output failed\n");
		goto release_line;
	}

	while (ros::ok())
	{
		ros::spinOnce();
		ret = gpiod_line_set_value(line, state);
		if (ret < 0) {
			perror("Set line output failed\n");
			goto release_line;
		}
		loop_rate.sleep();
	}
release_line:
	gpiod_line_release(line);
close_chip:
	gpiod_chip_close(chip);
end:
	return 0;
}

