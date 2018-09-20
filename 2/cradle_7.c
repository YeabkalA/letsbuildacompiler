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

/* write a string, preceded by a tab character */
void emit(const char *s)
{
  printf("\t%s", s);
}

/* write a string, preceded by a tab, followed by a newline */
void emitLine(const char *s)
{
  emit(s);
  printf("\n");
}

/*---------------------------------------------------------------
  Parse and Translate a Math Factor */

void expression();

void factor()
{
  if (lookahead_character == '(') {
    match('(');
    expression();
    match(')');
  } else {
    sprintf(print_buffer, "mov rax, %c", getNumber());
    emitLine(print_buffer);
  }
}

/*--------------------------------------------------------------
  Recognize and Translate a Multiply */

void multiply()
{
   match('*');
   factor();
   emitLine("pop rbx");
   emitLine("imul rax, rbx");
}


/*-------------------------------------------------------------
 Recognize and Translate a Divide */

void divide()
{
   match('/');
   factor();
   emitLine("pop rbx");
   emitLine("xor rdx, rdx");
   emitLine("xor rax, rbx");
   emitLine("xor rbx, rax");
   emitLine("xor rax, rbx");
   emitLine("idiv rbx");
   emitLine("mov rbx, rax");
}
/*---------------------------------------------------------------
  Parse and Translate a Math Term */

void term()
{
   factor();
   while (lookahead_character == '*' || lookahead_character == '/')
   {
     emitLine("push rax");
     switch (lookahead_character)
     {
       case '*': multiply(); break;
       case '/': divide(); break;
       default: expected("Mulop");
     }
   }
}

/*--------------------------------------------------------------
  Recognize and Translate an Add */

void add()
{
   match('+');
   term();
   emitLine("pop rbx");
   emitLine("add rax, rbx");
}

/*-------------------------------------------------------------
  Recognize and Translate a Subtract */

void subtract()
{
   match('-');
   term();
   emitLine("pop rbx");
   emitLine("sub rax, rbx");
   emitLine("neg rax");
}

int isAddop(char c)
{
  return (c == '+' || c == '-');
}


/*---------------------------------------------------------------
  Parse and Translate an Expression */

void expression()
{
  if (isAddop(lookahead_character))
  {
    emitLine("xor rax, rax");
  } else {
      term();
  }
  while (isAddop(lookahead_character))
  {
    emitLine("push rax");
    switch (lookahead_character)
    {
      case '+': add(); break;
      case '-': subtract(); break;
      default: expected("Addop");
    }
  }
}

/* prepare to run, filling the lookahead character */
void init()
{
  getChar();
}

int main(int argc, char *argv[])
{
  init();
  expression();
}
