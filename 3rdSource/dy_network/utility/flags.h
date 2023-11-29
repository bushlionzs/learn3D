#ifndef _FLAGS_H_INCLUDED
#define _FLAGS_H_INCLUDED

#include <assert.h>

union FlagValue 
{
    static FlagValue new_BOOL(int b)
    {
        FlagValue v;
        v.b = (b != 0);
        return v;
    }

    static FlagValue new_INT(int i)
    {
        FlagValue v;
        v.i = i;
        return v;
    }

    static FlagValue new_FLOAT(float f)
    {
        FlagValue v;
        v.f = f;
        return v;
    }

    static FlagValue new_STRING(const char* s)
    {
        FlagValue v;
        v.s = s;
        return v;
    }

    bool b;
    int i;
    double f;
    const char* s;
};

class Flag
{
public:
    enum Type { BOOL, INT, FLOAT, STRING };

    Flag(const char* file, const char* name, const char* comment,
        Type type, void* variable, FlagValue default_);

    const char* file() const { return _file; }
    const char* name() const { return _name; }
    const char* comment() const { return _comment; }

    Type type() const { return _type; }

    bool* bool_variable() const
    {
        assert(_type == BOOL);
        return &_variable->b;
    }

    int* int_variable() const
    {
        assert(_type == INT);
        return &_variable->i;
    }

    double* float_variable() const
    {
        assert(_type == FLOAT);
        return &_variable->f;
    }

    const char** string_variable() const
    {
        assert(_type == STRING);
        return &_variable->s;
    }

    // Default values
    bool bool_default() const
    {
        assert(_type == BOOL);
        return _default.b;
    }

    int int_default() const
    {
        assert(_type == INT);
        return _default.i;
    }

    double float_default() const
    {
        assert(_type == FLOAT);
        return _default.f;
    }

    const char* string_default() const
    {
        assert(_type == STRING);
        return _default.s;
    }

    void set_to_default();

    Flag* next() const { return _next; }

    void print(bool print_current_value);

private:
    const char* _file;
    const char* _name;
    const char* _comment;

    Type _type;
    FlagValue* _variable;
    FlagValue _default;

    Flag* _next;

    friend class FlagList;
};

#define DEFINE_FLAG(type, c_type, name, default, comment)   \
  c_type FLAG_##name = (default);                           \
  static Flag Flag_##name(__FILE__, #name, (comment),       \
                          Flag::type, &FLAG_##name,         \
                          FlagValue::new_##type(default))

#define DECLARE_FLAG(c_type, name)                          \
  extern c_type FLAG_##name

#define DEFINE_bool(name, default, comment)                 \
  DEFINE_FLAG(BOOL, bool, name, default, comment)
#define DEFINE_int(name, default, comment)                  \
  DEFINE_FLAG(INT, int, name, default, comment)
#define DEFINE_float(name, default, comment)                \
  DEFINE_FLAG(FLOAT, double, name, default, comment)
#define DEFINE_string(name, default, comment)               \
  DEFINE_FLAG(STRING, const char*, name, default, comment)


#define DECLARE_bool(name) DECLARE_FLAG(bool, name)
#define DECLARE_int(name) DECLARE_FLAG(int, name)
#define DECLARE_float(name) DECLARE_FLAG(double, name)
#define DECLARE_string(name) DECLARE_FLAG(const char*, name)

class FlagList
{
public:
    FlagList();

    static Flag* list() { return _list; }

    static void print(const char* file, bool print_current_value);

    static Flag* lookup(const char* name);

    static void split_argument(const char* arg,
                               char* buffer, 
                               int buffer_size,
                               const char** name, 
                               const char** value,
                               bool* is_bool);

    static int set_flags_from_command_line(int* argc, const char** argv, bool remove_flags);
    static inline int set_flags_from_command_line(int* argc, char** argv, bool remove_flags)
    {
        return set_flags_from_command_line(argc, const_cast<const char**>(argv), remove_flags);
    }

    static void register_flag(Flag* flag);
private:
    static Flag* _list;
};

#endif //_FLAGS_H_INCLUDED