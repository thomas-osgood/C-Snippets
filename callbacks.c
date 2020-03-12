/*
 * Created By: Thomas Osgood
 * Purpose:
 * 	Practice 'function callbacks' using function
 * 	pointers.
 */

/*** Required Includes ***/
#include <stdio.h>

/*** Function Prototypes ***/
void sayHello(char *name);
void useCallback(int num1, int num2, void (*cb)(char*));

/*** Main Function Definition ***/

/*
 * Function Name: main
 * Description:
 * 	Main function that gets called when the program
 * 	is compiled and run.
 * Input(s):
 * 	None
 * Return(s):
 * 	Exit Code - integer number representing how the program exits.
 */
int main(void) {
	void (*callback)(char*) = sayHello;
	useCallback(5,3,callback);
	return 0;
}

/*** Sub-Function Definitions ***/

/*
 * Function Name: sayHello
 * Description:
 * 	Function to print 'Hello' and a name.
 * Input(s):
 * 	name - char* to print out.
 * Return(s):
 * 	None
 */
void sayHello(char *name) {
	printf("Hello %s!\n", name);
	return;
}

/*
 * Function Name: useCallback
 * Description:
 * 	Use callback function, add two numbers and print the
 * 	result to STDOUT.
 * Input(s):
 * 	num1 - integer number to add
 * 	num2 - integer number to add
 * 	cb - void function pointer with char* input.
 * Return(s):
 * 	None
 */
void useCallback(int num1, int num2, void (*cb)(char*)) {
	cb("Thomas");
	printf("The sum of %d and %d is %d\n", num1, num2, num1 + num2);
	return;
}
