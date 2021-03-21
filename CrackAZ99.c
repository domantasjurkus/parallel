#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <unistd.h>
#include <pthread.h>

/******************************************************************************
  Demonstrates how to crack an encrypted password using a simple
  "brute force" algorithm. Works on passwords that consist only of 2 uppercase
  letters and a 2 digit integer.

  Compile with:
    cc -o CrackAZ99 CrackAZ99.c -lcrypt

  If you want to analyse the output then use the redirection operator to send
  output to a file that you can view using an editor or the less utility:
    ./CrackAZ99 > output.txt

  Dr Kevan Buckley, University of Wolverhampton, 2018 Modified by Dr. Ali Safaa 2019
******************************************************************************/

int count=0;     // A counter used to track the number of combinations explored so far

/**
 Required by lack of standard function in C.   
*/

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

char *salt_and_encrypted = "$6$AS$kCadGR45uq3cFGdm9aBLOsRG7xv6jhL13JAQ222aTq.Y9lkakq6Ld4Wlgy2ch66CwM.fLD/ius/qK3dkrPtzY/";

/**
 This function can crack the kind of password explained above. All combinations
 that are tried are displayed and when the password is found, #, is put at the 
 start of the line. Note that one of the most time consuming operations that 
 it performs is the output of intermediate results, so performance experiments 
 for this kind of program should not include this. i.e. comment out the printfs.
*/

void *threadfunction(void *ptr){
  int x = (int *)ptr;
  int y, z;
  
  char salt[7];
  char *enc;
  char plain[7];
  
  substr(salt, salt_and_encrypted, 0, 6);
  
  //printf("trying %c\n", x);
  
  for(y='A'; y<='Z'; y++){
      //printf("trying %c%c\n", x, y);
      for(z=0; z<=99; z++){
        sprintf(plain, "%c%c%02d", x, y, z);
        //printf("%s\n", plain);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
	    printf("#%-8d%s %s\n", count, plain, enc);
	    return;
        } 
      }
    }
}

void crack(){
  int x;
  
  pthread_t threads[26];
  int i=0;
  
  for(x='A'; x<='Z'; x++){
    pthread_create(&threads[i], NULL, threadfunction, (void *) x);
    i++;
  }
  
  for (int j=0; j<26; j++) {
    pthread_join(threads[j], NULL);
  }
  
}

int main(int argc, char *argv[]){
  //crack("$6$AS$kCadGR45uq3cFGdm9aBLOsRG7xv6jhL13JAQ222aTq.Y9lkakq6Ld4Wlgy2ch66CwM.fLD/ius/qK3dkrPtzY/");
  crack();
  printf("%d solutions explored\n", count);

  return 0;
}

