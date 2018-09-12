#ifndef __CRADLE_H__
#define __CRADLE_H__

/* A global variable for a single lookahead character */
extern char lookahead_character;

/* A global variable to use for print buffering */
extern char *print_buffer;

/* read a single character from the input stream into the
 * lookahead character.
 */
extern void getChar();

/* report an error */
extern void error(const char *message);

/* report an error and halt the compiler */
extern void abend(const char *message);

/* report what was expected, and exit */
extern void expected(const char *expectation);

/* match a single input character. If it matches,
 * load the next character into the lookahead buffer.
 * Otherwise, report on what we expected.
 */
extern void match(char c);

/* determine if the provided character is an
 * alphabetical character.
 */
extern int isAlpha(char c);

/* determine if the provided character is a digit. */
extern int isDigit(char c);

/* get an identifier from the lookahead buffer. If
 * there's one there, then load up the buffer.
 * otherwise, report that we expected a name
 */
extern char getIdentifier();

/* get a number from the lookahead buffer. If there's
 * one there, then load up the buffer. Otherwise,
 * report that we expected a number.
 */
extern char getNumber();

/* write a string, preceeded by a tab character */
extern void emit(const char *s);

/* write a string, preceeded by a tab, followed by a newline */
extern void emitLine(const char *s);

/* prepare to run, filling the lookahead character */
extern void init();

#endif /* __CRADLE_H__ */
