#include "flags.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

namespace
{
const char* to_cstring(Flag::Type type)
{
    switch (type)
    {
    case Flag::BOOL:
        return "bool";
    case Flag::INT:
        return "int";
    case Flag::FLOAT:
        return "float";
    case Flag::STRING:
        return "string";
    }

    assert(false);
    return nullptr;
}

void print_flag_value(Flag::Type type, FlagValue* p)
{
    switch (type)
    {
    case Flag::BOOL:
        printf("%s", (p->b ? "true" : "false"));
        return;
    case Flag::INT:
        printf("%d", p->i);
        return;
    case Flag::FLOAT:
        printf("%f", p->f);
        return;
    case Flag::STRING:
        printf("%s", p->s);
        return;
    }

    assert(false);
}
}

Flag::Flag(const char* file, const char* name, const char* comment,
    Type type, void* variable, FlagValue default__)
    : _file(file)
    , _name(name)
    , _comment(comment)
    , _type(type)
    , _variable(reinterpret_cast<FlagValue*>(variable))
    , _default(default__)
{
    FlagList::register_flag(this);
}

void Flag::set_to_default()
{
    switch (_type)
    {
    case Flag::BOOL:
        _variable->b = _default.b;
        return;
    case Flag::INT:
        _variable->i = _default.i;
        return;
    case Flag::FLOAT:
        _variable->f = _default.f;
        return;
    case Flag::STRING:
        _variable->s = _default.s;
        return;
    }

    assert(false);
}

void Flag::print(bool print_current_value) {
    printf("  --%s (%s)  type: %s  default: ", _name, _comment, to_cstring(_type));
    print_flag_value(_type, &_default);
    if (print_current_value) {
        printf("  current value: ");
        print_flag_value(_type, _variable);
    }
    printf("\n");
}

Flag* FlagList::_list = nullptr;

FlagList::FlagList()
{
    _list = nullptr;
}

void FlagList::print(const char* file, bool print_current_value)
{
    const char* current = nullptr;
    for (Flag* f = _list; f != NULL; f = f->next())
    {
        if (!file || file == f->file())
        {
            if (current != f->file())
            {
                printf("Flags from %s:\n", f->file());
                current = f->file();
            }
            f->print(print_current_value);
        }
    }
}

Flag* FlagList::lookup(const char* name)
{
    Flag* f = _list;
    while (f && strcmp(name, f->name()) != 0)
    {
        f = f->next();
    }
    return f;
}

void FlagList::split_argument(const char* arg,
                              char* buffer, 
                              int buffer_size,
                              const char** name, 
                              const char** value,
                              bool* is_bool)
{
    *name = nullptr;
    *value = nullptr;
    *is_bool = false;

    if (*arg == '-')
    {
        // find the begin of the flag name
        arg++;  // remove 1st '-'
        if (*arg == '-')
        {
            arg++;  // remove 2nd '-'
        }

        if (arg[0] == 'n' && arg[1] == 'o')
        {
            arg += 2;  // remove "no"
            *is_bool = true;
        }
        *name = arg;

        // find the end of the flag name
        while (*arg != '\0' && *arg != '=')
        {
            arg++;
        }

        // get the value if any
        if (*arg == '=')
        {
            // make a copy so we can NUL-terminate flag name
            int n = static_cast<int>(arg - *name);
            memcpy(buffer, *name, n * sizeof(char));
            buffer[n] = '\0';
            *name = buffer;
            // get the value
            *value = arg + 1;
        }
    }
}

int FlagList::set_flags_from_command_line(int* argc, const char** argv, bool remove_flags)
{
    for (int i = 1; i < *argc; /* see below */)
    {
        int j = i;  // j > 0
        const char* arg = argv[i++];

        // split arg into flag components
        char buffer[1024];
        const char* name;
        const char* value;
        bool is_bool;
        split_argument(arg, buffer, sizeof buffer, &name, &value, &is_bool);

        if (name)
        {
            // lookup the flag
            Flag* flag = lookup(name);
            if (!flag)
            {
                fprintf(stderr, "Error: unrecognized flag %s\n", arg);
                return j;
            }

            // if we still need a flag value, use the next argument if available
            if (flag->type() != Flag::BOOL && !value)
            {
                if (i < *argc) 
                {
                    value = argv[i++];
                }
                else
                {
                    fprintf(stderr, "Error: missing value for flag %s of type %s\n",
                        arg, to_cstring(flag->type()));
                    return j;
                }
            }

            // set the flag
            char empty[] = { '\0' };
            char* endp = empty;
            switch (flag->type())
            {
            case Flag::BOOL:
                *flag->bool_variable() = !is_bool;
                break;
            case Flag::INT:
                *flag->int_variable() = strtol(value, &endp, 10);
                break;
            case Flag::FLOAT:
                *flag->float_variable() = strtod(value, &endp);
                break;
            case Flag::STRING:
                *flag->string_variable() = value;
                break;
            }

            // handle errors
            if ((flag->type() == Flag::BOOL && value) ||
                (flag->type() != Flag::BOOL && is_bool) ||
                *endp != '\0') 
            {
                fprintf(stderr, "Error: illegal value for flag %s of type %s\n",
                    arg, to_cstring(flag->type()));
                return j;
            }

            // remove the flag & value from the command
            if (remove_flags)
            {
                while (j < i)
                {
                    argv[j++] = nullptr;
                }
            }
        }
    }

    // shrink the argument list
    if (remove_flags)
    {
        int j = 1;
        for (int i = 1; i < *argc; i++)
        {
            if (argv[i] != NULL)
            {
                argv[j++] = argv[i];
            }
        }
        *argc = j;
    }

    // parsed all flags successfully
    return 0;
}

void FlagList::register_flag(Flag* flag)
{
    assert(flag && flag->name() && '\0' != flag->name()[0]);
    flag->_next = _list;
    _list = flag;
}