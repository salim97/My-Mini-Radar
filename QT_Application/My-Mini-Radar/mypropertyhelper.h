#pragma once
#include <QObject>

#define AUTO_PROPERTY(TYPE, NAME) \
    Q_PROPERTY(TYPE NAME READ NAME WRITE NAME NOTIFY NAME ## Changed ) \
    public: \
       TYPE NAME() const { return m_ ## NAME ; } \
       void NAME(TYPE value) { \
          if (m_ ## NAME == value)  return; \
          m_ ## NAME = value; \
          emit NAME ## Changed(value); \
        } \
       Q_SIGNAL void NAME ## Changed(TYPE value);\
    private: \
       TYPE m_ ## NAME;

#define READONLY_PROPERTY(TYPE, NAME) \
    Q_PROPERTY(TYPE NAME READ NAME CONSTANT ) \
    public: \
       TYPE NAME() const { return m_ ## NAME ; } \
    private: \
       void NAME(TYPE value) {m_ ## NAME = value; } \
       TYPE m_ ## NAME;

#define INIT_CURD(CLASS_NAME) \
    private:\
    Q_OBJECT \
    public:\
        CLASS_NAME() { init(this); }
