/**
 * Lispy main source file.
 *
 * @filename: lispy.c
 *
 * @version: 0.16
 *
 * @date: 2014-11-04
 *
 * @description: Lispy main source code file.
 *
 * @author: Alexander Skjolden
 *
 * @webpage: https://github.com/plastboks/Lispy
 *
 * This file is part of Lispy.
 *
 * Lispy is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Lispy is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Lispy.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "lispy.h"
#include "builtins.h"
#include "version.h"
#include "config.h"

void completion(const char *buf, linenoiseCompletions *lc)
{
    switch (buf[0]) {
        case 't': linenoiseAddCompletion(lc, "true"); break;
        case 'f': linenoiseAddCompletion(lc, "false"); break;
        case 'n': linenoiseAddCompletion(lc, "nil"); break;
        case 'l': linenoiseAddCompletion(lc, "load"); break;
        case 'i': linenoiseAddCompletion(lc, "include"); break;
        case 'd': linenoiseAddCompletion(lc, "def"); break;
        case 'j': linenoiseAddCompletion(lc, "join"); break;
        case 'c': linenoiseAddCompletion(lc, "cons"); break;
        case 'e': linenoiseAddCompletion(lc, "exit()"); break;
    }
}

void prompt(char* cmd)
{
    static unsigned int cmd_count = 1;
    sprintf(cmd, "[%d]> ", cmd_count++);
}

void show_splash()
{
    puts(BOLDMAGENTA);
    puts("     __    _                  ");
    puts("    / /   (_)________  __  __ ");
    puts("   / /   / / ___/ __ \\/ / / /");
    puts("  / /___/ (__  ) /_/ / /_/ /  ");
    puts(" /_____/_/____/ .___/\\__, /  ");
    puts("             /_/    /____/    ");
    puts(RESET);

    puts(BOLDWHITE);
    printf("Version: %s, build: %s (%s)\n", version, VERSION_BUILD, BUILD_DATE);
    puts("Press Ctrl+c , or type 'exit()' to exit");
    puts(RESET);
}

int main(int argc, char** argv)
{
    Range    = mpc_new("range");
    Decimal  = mpc_new("decimal");
    Number   = mpc_new("number");
    String   = mpc_new("string");
    Symbol   = mpc_new("symbol");
    Comment  = mpc_new("comment");
    Sexpr    = mpc_new("sexpr");
    Qexpr    = mpc_new("qexpr");
    Expr     = mpc_new("expr");
    Lispy    = mpc_new("lispy");

    char* input; 
    char stdlib_path[512];
    char settings_path[512];
    char historypath[512];

    char cmd[16];

    /* Define them with the following Language */
    mpca_lang(MPCA_LANG_DEFAULT,
      "                                                           \
        range    : /-?[a-zA-Z0-9]+\\.\\.-?[a-zA-Z0-9]+/;          \
        decimal  : /-?[0-9]+\\.[0-9]+/;                           \
        number   : /-?[0-9]+/ ;                                   \
        string   : /\"(\\\\.|[^\"])*\"/ ;                         \
        symbol   : /[a-zA-Z0-9_+\\-*\\/\\\\=<>!&|%^]+/ ;          \
        comment  : /;[^\\r\\n]*/ ;                                \
        sexpr    : '(' <expr>* ')' ;                              \
        qexpr    : '{' <expr>* '}' ;                              \
        expr     : <range> | <decimal> | <number> | <string> |    \
                   <symbol> | <comment> | <sexpr> | <qexpr> ;     \
        lispy    : /^/ <expr>* /$/ ;                              \
      ",
      Range, Decimal, Number, String, Comment,
      Symbol, Sexpr, Qexpr, Expr, Lispy);

    lenv* e = lenv_new();
    lenv_add_builtins(e);

    /**
     * Load standard library
     */
    sprintf(stdlib_path, "%s/%s", GLIB_PFIX, "std.lspy");
    lval* stdlib_file = lval_add(lval_sexpr(), lval_str(stdlib_path));
    lval* stdlib_load = builtin_load(e, stdlib_file);
    if (stdlib_load->type == LVAL_ERR) {
        lval_println(stdlib_load);
    }
    lval_del(stdlib_load);

    /**
     * Load user settings file
     */
    sprintf(settings_path, "%s/.lispy.lspy", getenv("HOME"));
    lval* settings_file = lval_add(lval_sexpr(), lval_str(settings_path));
    lval* settings_load = builtin_load(e, settings_file);
    if (settings_load->type == LVAL_ERR) {
        lval_println(settings_load);
    }
    lval_del(settings_load);

    if (argc == 1) {
        if (get_splash() > 0) { show_splash(); }

        linenoiseSetMultiLine(1);
        linenoiseSetCompletionCallback(completion);
        sprintf(historypath, "%s/.lispy_history", getenv("HOME"));
        linenoiseHistoryLoad(historypath);

        prompt(cmd);
        while((input = linenoise(cmd)) != NULL) {
            if (input[0] != '\0') {
                linenoiseHistoryAdd(input);
                linenoiseHistorySave(historypath);

                mpc_result_t r;
                if (mpc_parse("<stdin>", input, Lispy, &r)) {

                    lval* x = lval_eval(e, lval_read(r.output));
                    lval_println(x);
                    lval_del(x);
                    mpc_ast_delete(r.output);
                } else {
                    mpc_err_print(r.error);
                    mpc_err_delete(r.error);
                }
                prompt(cmd);

            } else if (!strncmp(input, "/historylen", 11)) {
                int len = atoi(input + 11);
                linenoiseHistorySetMaxLen(len);
            }
            free(input);
        }
    }

    if (argc >= 2) {
        for (int i = 1; i < argc; i++) {
            lval* args = lval_add(lval_sexpr(), lval_str(argv[i]));

            lval* x = builtin_load(e, args);

            if (x->type == LVAL_ERR) {
                lval_println(x);
            }
            lval_del(x);
        }
    }

    lenv_del(e);
    mpc_cleanup(10, Range, Decimal, Number, String, Comment,
            Symbol, Sexpr, Qexpr, Expr, Lispy);
    return 0;
}
