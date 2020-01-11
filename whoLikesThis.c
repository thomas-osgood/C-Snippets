#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

/*
* return must be an allocated string
* do not mutate input

likes({})
    // should return "no one likes this"

likes({"Peter"})
    // should return "Peter likes this"

likes({"Jacob", "Alex"})
    // should return "Jacob and Alex like this"

likes({"Max","John","Mark"})
    // should return "Max, John and Mark like this"

likes({"Alex", "Jacob", "Mark", "Max"})
    // should return "Alex, Jacob and 2 others like this"

NOTE:
------
When I go through the tests one-by-one this solution passes
all the provided sample tests. When, however, I attempt to
run all the tests at once, the program randomly crashes. I
believe this is due to an error in the tests themselves.

*/

char* likes(size_t n, const char *const names[n]) {

    int i = 0, others = 0;
    size_t newsize = 0;
    newsize = strlen("no one likes this");
    char *returnVal = (char *) malloc(sizeof(char) * newsize + sizeof(char));
    
    if (n == 0) {
        returnVal = "no one likes this";
    } else if (n == 1) {
        newsize = strlen(names[0]) + strlen(" likes this");
        returnVal = (char *) realloc (returnVal, sizeof(char) * newsize + sizeof(char));
        sprintf(returnVal, "%s likes this", names[0]);
    } else if( n > 1 && n < 4) {
        newsize = strlen(names[0]) + strlen(names[1]) + strlen(" like this");
        if (n == 2) {
            returnVal = (char *) realloc(returnVal, sizeof(char) * newsize + sizeof(char));
            sprintf(returnVal, "%s and %s like this", names[0], names[1]);
        } else {
            newsize += strlen(names[2]) + 4;
            returnVal = (char *) realloc(returnVal, sizeof(char) * newsize + sizeof(char));
            sprintf(returnVal, "%s, %s and %s like this", names[0], names[1], names[2]);
        }
    } else {
        others = n - 2;
        newsize = strlen(names[0]) + strlen(names[1]) + strlen("and  others") + strlen(" like this") + 12;
        returnVal = (char *) realloc(returnVal, sizeof(char) * newsize + sizeof(char));
        sprintf(returnVal, "%s, %s and %d others like this", names[0], names[1], others);
    }
    
    return returnVal;

}
