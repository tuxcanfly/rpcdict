/* dict.x: Remote dictionary */
program DICTPROG {
   version INSERTVERS {
     int INSERT(string) = 1;
   } = 1;
   version LOOKUPVERS {
     string LOOKUP(string) = 1;
   } = 1;
} = 0x20000001;
