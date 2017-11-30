/**
 * Project06.c
 *
 * Main class to run the project.
 */

#include <stdlib.h>
#include <stdio.h>

#include "ports.h"
#include "ADC.h"

int main(int argc, char *argv[]) {

	initIOCtrl() ;
	initPorts() ;

	initADC() ;

	return EXIT_SUCCESS;
}
