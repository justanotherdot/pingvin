/*
 * splash, a toy shell
 *
 * author: Ryan James Spencer <spencer.ryanjames@gmail.com>
 * file: splash.c
 *
 * Inspired by this blog post: https://brennan.io/2015/01/16/write-a-shell-in-c/
 * but with our own improvements (annotations where applicable).
 *
 */

#include <stdio.h>
#include <stdlib.h>


typedef struct config {
  void* empty;
} Config;

// TODO This could take a configuration object.
void run(Config* cfg) {
  // Get the input line.
  // Parse the input line.
  // Execute the program specified.
}

Config* setup(int argc, char** argv) {
  Config* cfg = malloc(sizeof(Config));
  return cfg;
}

void teardown(Config* cfg) {
  free(cfg);
}

// main :: Int -> Ptr String -> IO ()
int main(int argc, char** argv) {
  Config* cfg = setup(argc, argv);
  run(cfg);
  /* teardown(cfg); */
  return EXIT_SUCCESS;
}
