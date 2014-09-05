/* dict.x: Remote dictionary */
program DICTPROG {
   version DICTVERS {
     int INSERT(string) = 1;
     string LOOKUP(string) = 2;
   } = 1;
} = 0x20000001;
