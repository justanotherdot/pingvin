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

// TODO check all mallocs and follow check and re-assign pattern
// as opposed to realloc.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_TOKENS 256

typedef struct config {
  void* empty;
} Config;

typedef struct line_buf {
  char* line;
  size_t size;
} LineBuf;

typedef struct parse_result {
  char** tokens;
  size_t qty;
} ParseResult;

LineBuf* read_line(FILE* handle) {
  char* line = NULL;
  size_t bufsize = 0;

  getline(&line, &bufsize, handle);

  LineBuf* lb = malloc(sizeof(LineBuf));
  lb->line = line;
  lb->size = bufsize;

  return lb;
}

// TODO this will need to become a more sophisticated parser in order to do
// standard shell stuff.
ParseResult*  parse_line(LineBuf* lb, char* delim) {
  char* token;
  char* rest;
  char** tokens = malloc(sizeof(char*) * MAX_TOKENS);
  int qty = 0;

  token = strtok_r(lb->line, delim, &rest);
  while (token != NULL) {
    tokens[qty] = token, ++qty;
    token = strtok_r(NULL, delim, &rest);
  }
  tokens[qty] = NULL;

  ParseResult* pr = malloc(sizeof(ParseResult));
  pr->tokens = tokens;
  pr->qty = qty;

  return pr;
}

int spawn_process(Config* cfg, ParseResult* pr) {
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // TODO swap this out with execve to pass environment.
    if (execvp(pr->tokens[0], pr->tokens) == -1) {
      perror("splash");
    }
    exit(EXIT_FAILURE);
    /* perror("splash"); */

  } else if (pid < 0) {
    perror("splash");
  } else {
    // TODO, see https://www.cons.org/cracauer/sigint.html
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WTERMSIG(status) && !WIFSIGNALED(status));
  }

  return 1;
}

void run(Config* cfg) {
  LineBuf* lb = read_line(stdin);
  ParseResult* pr = parse_line(lb, " \t\r\n\a");
  // TODO provide builtins.
  spawn_process(cfg, pr);

  free(lb);
  free(pr);
}

Config* setup(int argc, char** argv) {
  Config* cfg = malloc(sizeof(Config));
  return cfg;
}

void teardown(Config* cfg) {
  free(cfg);
}

int main(int argc, char** argv, char** envp) {
  // TODO check that all memory is freed properly.
  // TODO make parser type better named. Actually parse to a proper data type.
  // TODO Handle configuration options
  // TODO do simple expansions.
  // TODO Make tokens a resizable array.
  Config* cfg = setup(argc, argv);
  run(cfg);
  teardown(cfg);
  return EXIT_SUCCESS;
}
