#include "flite/utils/args.hpp"
#include "flite/utils/tokenstream.hpp"

static void parse_description(const char* description, cst_features* f);
static void parse_usage(const char* progname, const char* s1, const char* s2, const char* description);

cst_val* cst_args(char** argv, int argc, const char* description, cst_features* args)
{
    /* parses the given arguments wrt the description */
    cst_features* op_types = new_features();
    cst_val* files = NULL;
    int i;
    const char* type;

    parse_description(description, op_types);

    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if ((!feat_present(op_types, argv[i])) ||
                (cst_streq("-h", argv[i])) ||
                (cst_streq("-?", argv[i])) ||
                (cst_streq("--help", argv[i])) ||
                (cst_streq("-help", argv[i])))
                parse_usage(argv[0], "", "", description);
            else {
                type = feat_string(op_types, argv[i]);
                if (cst_streq("<binary>", type))
                    feat_set_string(args, argv[i], "true");
                else {
                    if (i + 1 == argc)
                        parse_usage(argv[0], "missing argument for ", argv[i], description);
                    if (cst_streq("<int>", type))
                        feat_set_int(args, argv[i], atoi(argv[i + 1]));
                    else if (cst_streq("<float>", type))
                        feat_set_float(args, argv[i], atof(argv[i + 1]));
                    else if (cst_streq("<string>", type))
                        feat_set_string(args, argv[i], argv[i + 1]);
                    else
                        parse_usage(argv[0], "unknown arg type ", type, description);
                    i++;
                }
            }
        }
        else
            files = cons_val(string_val(argv[i]), files);
    }
    delete_features(op_types);

    return val_reverse(files);
}

static void parse_usage(const char* progname, const char* s1, const char* s2, const char* description)
{
    cst_errmsg("%s: %s %s\n", progname, s1, s2);
    cst_errmsg("%s\n", description);
    exit(0);
}

static void parse_description(const char* description, cst_features* f)
{
    /* parse the description into something more usable */
    cst_tokenstream* ts;
    const char* arg;
    char* op;
    const char* xop;

    ts = ts_open_string(description, " \t\r\n", /* whitespace */
                        "{}[]|",                /* singlecharsymbols */
                        "",                     /* prepunctuation */
                        "");                    /* postpunctuation */
    while (!ts_eof(ts)) {
        op = cst_strdup(ts_get(ts));
        if ((op[0] == '-') && (cst_strchr(ts->whitespace, '\n') != 0)) { /* got an option */
            xop = feat_own_string(f, op);
            arg = ts_get(ts);
            if (arg[0] == '<')
                feat_set_string(f, xop, arg);
            else
                feat_set_string(f, xop, "<binary>");
        }
        cst_free(op);
    }

    ts_close(ts);
}
