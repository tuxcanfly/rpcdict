/*
 * dict.x: Remote dictionary
 * 1. INSERT(string, string):
 * @param string - word
 * @param string - meaning
 * inserts the word and the meaning to the datastore
 * return zero or one based on success
 *
 * 2. LOOKUP(string):
 * @param string - word
 * lookup the word and return the meaning
 */
program DICTPROG {
   version DICTVERS {
     int INSERT(string, string) = 1;
     string LOOKUP(string) = 2;
   } = 1;
} = 0x20000001;
