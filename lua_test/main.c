//
//  main.c
//  Nano Lua Dict Example
//
//  Created by Nicolas Goles on 7/19/12.
//

#include <stdio.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "nanoluadict.h"

void aFunction() {
   printf("C function is being called!! :D\n");
}

int main(int argc, const char * argv[])
{
    /* Declare a Lua State, open the Lua State and load the libraries (see above). */
    lua_State *L;
    L = luaL_newstate();
    luaL_openlibs(L);

    luaDict(L
            , "sample_dictionary"
            , 8
            , kvPairWithNumber("key1", 1)
            , kvPairWithNumber("key2", 2)
            , kvPairWithString("key3", "string 3")
            , kvPairWithNumber("key4", 4)
            , kvPairWithNumber("key5", 5)
            , kvPairWithNumber("key6", 6)
            , kvPairWithNumber("key7", 7)
            , kvPairWithCFunction("c_function", &aFunction));

   /* Load Table Print Script */
   int status = luaL_dofile(L, "tableprint.lua");
   if (status) {
      /* If something went wrong, error message is at the top of */
      /* the stack */
      fprintf(stderr, "Couldn't load file: %s\n", lua_tostring(L, -1));
      return 1;
   }

   /* Print the sample_dictionary table */
   lua_pushglobaltable(L);
   lua_getfield(L, -1, "do_print");
   lua_remove(L, -2);

    if (lua_pcall(L, 0, 0, 0)) {
        fprintf(stderr, "Error on pcall: %s\n", lua_tostring(L, -1));
    }

    return 0;
}

