/*
    INT32 To IP Address
    
    Take a long int32 number and convert it into an IP address.
*/

#include <inttypes.h>

void uint32_to_ip(uint32_t ip, char *output)
{
  /* you dont need to allocate memory, use 'output' */
  if (ip == 0) {
    sprintf(output, "0.0.0.0");
    return output;
  }
  
  int i = 0, x = 0;
  long numVal[4];
  
  for (i = 0; i < 32; i += 8) {
    numVal[x] = (ip >> i) & 0xFF;
    x++;
  }
  sprintf(output, "%d.%d.%d.%d", numVal[3], numVal[2], numVal[1], numVal[0]);
  
  return output;
  
}
