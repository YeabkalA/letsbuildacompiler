#include <stdio.h>
#include <stdlib.h>
#include "cradle.h"

/* A global variable to hold the lookahead character */
char lookahead_character;

/* A global variable to use for print buffering */
char _print_buffer[256];
char *print_buffer = _print_buffer;

/* read a single character from the input stream into the
 * lookahead character.
 */
void getChar()
{
  lookahead_character = getchar();
}

/* report an error */
void error(const char *message)
{
  printf("\nError: %s\n", message);
}

/* report an error and halt the compiler */
void abend(const char *message)
{
  error(message);
  exit(-1);
}

/* report what was expected, and exit */
void expected(const char *expectation)
{
    sprintf(print_buffer, "Expected: %s", expectation);
    abend(print_buffer);
}

/* match a single input character. If it matches,
 * load the next character into the lookahead buffer.
 * Otherwise, report on what we expected.
 */
void match(char c)
{
  if (c == lookahead_character) {
    getChar();
  } else {
    sprintf(print_buffer, "Tried to match %c, but got %c.",
        c, lookahead_character);
    expected(print_buffer);
  }
}

/* determine if the provided character is an
 * alphabetical character.
 */
int isAlpha(char c)
{
  if (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')))
    return c;
  return 0;
}

/* determine if the provided character is a digit. */
int isDigit(char c)
{
  if (c >= '0' && c <= '9')
    return c;
  return 0;
}

/* get an identifier from the lookahead buffer. If
 * there's one there, then load up the buffer.
 * otherwise, report that we expected a name
 */
char getIdentifier()
{
  char c = lookahead_character;
  if (isAlpha(lookahead_character)) {
    getChar();
  } else {
    expected("identifier");
  }
  return c;
}

/* get a number from the lookahead buffer. If there's
 * one there, then load up the buffer. Otherwise,
 * report that we expected a number.
 */
char getNumber()
{
  char c = lookahead_character;
  if (isDigit(c)) {
    getChar();
  } else {
    expected("number");
  }
  return c;
}

/* write a string, preceeded by a tab character */
void emit(const char *s)
{
  printf("\t%s", s);
}

/* write a string, preceeded by a tab, followed by a newline */
void emitLine(const char *s)
{
  emit(s);
  printf("\n");
}

/* prepare to run, filling the lookahead character */
void init()
{
  getChar();
}

int main(int argc, char *argv[])
{
  init();
}
