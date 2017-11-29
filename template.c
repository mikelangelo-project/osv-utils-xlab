#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 2048
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* Expand template string using environment variables.
 *
 * If VAR1 is set to "abc" and VAR2 is not set, template
 * "var1=${VAR1} var2=${VAR2} end" expands to
 * "var1=abc var2= end".
 *
 * If expanded template exceeds the length of 2047 ASCII characters, it is
 * truncated.
 */
static char const *expand_template(char *tmpl)
{
	/* Template is processed in chunks. Anatomy of a template string would
	 * look like this:
	 *
	 *     prefix0=${VARIABLE0} prefix1=${VARIABLE1} some random end text
	 *     |-- chunk ---------||-- chunk ----------||-- trailing text ---|
	 *
	 * Trailing text that is not part of any chunk is appended to the
	 * result verbatim. Pointers in each chunk are named as follows:
	 *
	 *     prefix0=${VARIABLE0}
	 *     |       | |        `- variable_end
	 *     |       | `- variable_start
	 *     |       `- prefix_end
	 *     `- tmpl
	 *
	 * All pointer acrobatics stems from the diagram above. Inserting
	 * NULL at the variable_end pointer makes it possible to pass
	 * variable_start to getenv() function.
	 */

	static char buffer[BUFSIZE];
	size_t pos = 0;
	size_t n, size;

	for (;;) {
		char *prefix_end = strstr(tmpl, "${");
		if (! prefix_end) {
			break;
		}
		char *variable_start = prefix_end + 2;

		char *variable_end = strchr(variable_start, '}');
		if (! variable_end) {
			break;
		}

		*variable_end = '\0';
		char const *envvar = getenv(variable_start);
		if (! envvar) {
			envvar = "";
		}

		size = prefix_end - tmpl;
		n = MIN(BUFSIZE - pos, size);
		memcpy(buffer + pos, tmpl, n);
		pos += n;

		size = strlen(envvar);
		n = MIN(BUFSIZE - pos, size);
		memcpy(buffer + pos, envvar, n);
		pos += n;

		tmpl = variable_end + 1;
	}

	/* Copy template part after the last variable. */
	size = strlen(tmpl);
	n = MIN(BUFSIZE - pos, size);
	memcpy(buffer + pos, tmpl, n);
	pos += n;

	/* NULL-terminate the result */
	buffer[MIN(pos, BUFSIZE - 1)] = '\0';

	return buffer;
}

int main (int argc, char **argv)
{
	char *tmpl = NULL;
	size_t n = 0;

	if (argc != 3) {
		fputs("Usage:\n", stderr);
		fprintf(stderr, "  %s TEMPLATE_PATH OUTPUT_PATH\n", argv[0]);
		return 1;
	}

	FILE *in = fopen(argv[1], "rb");
	if (! in) {
		perror("Cannot open template");
		return 2;
	}

	FILE *out = fopen(argv[2], "wb");
	if (! out) {
		perror("Cannot open output file");
		return 3;
	}

	while (getline(&tmpl, &n, in) >= 0) {
		fputs(expand_template(tmpl), out);
	}
	fclose (out);

	return 0;
}
