#include "console.h"
#include "scheduler.h"
#include "pcb.h"
#include "api.h"

void prog1() {

	char test[5];

	while (1) {

		og_print_string("Origami1> ");
		while(og_read_line(test, 5)){}
		og_print_string("Fagel 1 viskar: ");
		og_print_string(test);
		og_print_string("\n");
	}

}

void prog2() {

	char test[5];

	while (1) {

		og_print_string("Origami2> ");
		while(og_read_line(test, 5)){}
			og_print_string("Fagel 2 viskar: ");
			og_print_string(test);
			og_print_string("\n");
	}

}


void main_loop() {

console_print_string("................................................................................\n");
console_print_string("................................................................................\n");
console_print_string(".................I..............................................................\n");
console_print_string(".................~=.........................................,~..................\n");
console_print_string("..................7:......................................~:+:..................\n");
console_print_string("...................7:...................................:?I:~:..................\n");
console_print_string("...................77,................................:?:7,:7...................\n");
console_print_string("....................77...............................77:7~,==...................\n");
console_print_string("....................777...........................~77I777I:~=...................\n");
console_print_string(".....................777........................,7777777777~=...................\n");
console_print_string(".....................7777.....................,7777777777777....................\n");
console_print_string("......................777I..................,777777777777777,...................\n");
console_print_string("......................I777~...............,77777777777777777....................\n");
console_print_string(".......................7777,............,777777777777777777,....................\n");
console_print_string(".......................?7777,.........,77777777777777777777,....................\n");
console_print_string("........................77777........I777777777777777777777.....................\n");
console_print_string("........................,77777,.....,777777777777777777777:.....................\n");
console_print_string(".........................777777,...,7777777777777777777777,.....................\n");
console_print_string("..........................77777I.,,,7777777777777777777777......................\n");
console_print_string("..........................:77777=,,7??7777777777777777777?,.....................\n");
console_print_string("...........................777777,,?77777I7777777777777II?=++I..................\n");
console_print_string("...........................,II77I77777777777777777777?IIII:777..................\n");
console_print_string("..........................,,,?777777777777777777777?IIIIII=777..................\n");
console_print_string("..................?IIIIIIII7777777777777777777777?IIIIIII..=77,.................\n");
console_print_string("............?~:~+?IIIIII77777777777777777777777IIIIIIIII....I7,.................\n");
console_print_string("...............:~,:~=?IIIII777777777777777777I7IIIIIIII.....,7+.................\n");
console_print_string(".........................:~~+IIIII7777777777777IIIIII+.......77.................\n");
console_print_string("............................~========?7III77777IIIII..........7.................\n");
console_print_string(".......................................:~++++7II?II...........:,................\n");
console_print_string(".........................................~=++II?II..............................\n");
console_print_string("..........................................:~+I?I:...............................\n");
console_print_string("............................................=7?.................................\n");
console_print_string("................................................................................\n");
console_print_string("................................................................................\n");
console_print_string("                   _____ ______  _____  _____   ___  ___  ___ _____ \n");
console_print_string("                  |  _  || ___ \\|_   _||  __ \\ / _ \\ |  \\/  ||_   _|\n");
console_print_string("                  | | | || |_/ /  | |  | |  \\// /_\\ \\| .  . |  | |  \n");
console_print_string("                  | | | ||    /   | |  | | __ |  _  || |\\/| |  | |  \n");
console_print_string("                  \\ \\_/ /| |\\ \\  _| |_ | |_\\ \\| | | || |  | | _| |_ \n");
console_print_string("                   \\___/ \\_| \\_| \\___/  \\____/\\_| |_/\\_|  |_/ \\___/ \n");
                                                  
console_print_string("Starup\n");

//todo
//pcb_queue_test();


/*if(0xFFFFFFFF == -1){
	console_print_string("jag hade rätt");
}
scheduler_create_process(prog1,3);
scheduler_create_process(prog2,3);
scheduler_create_process(prog3,2);*/


	//console_print_int(scheduler_create_process(prog1, 1));
	//console_print_int(scheduler_create_process(prog2, 1));

scheduler_create_process(prog1, 1);
scheduler_create_process(prog2, 1);

while(1) {}

}


