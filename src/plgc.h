

/*
typedef unsigned char  uint8;
typedef unsigned short  uint16;
typedef unsigned long  uint32;
typedef unsigned long long  uint32;
*/

namespace pl{
  const char* pl_type[]={
    "boolean",
    "number",
    "string",
    "function",
    "userdata",
    "table"
  };

  class gc_common{
  public:
    int mark;
    static const int m_color=1;
    unsigned int refcount;
    gc_common* next;
    
    gc_common(){
      mark=0;
      refcount=0;
      next=0;
    }
    
    void setbit(int b){
      mark=mark|b;
    }
    void cleanbit(int b){
      mark=mark&~b;
    }
  };
  
  class pl_bool:gc_common{
  public:
    bool val;
    operator bool&(){return val;}
  };
  class pl_number:gc_common{
  public:
    enum Ttype{
      _int,
      _float,
      _bigint,
      _bignum
    } type;
    union{
      int _int;float _float;
    } val;
    void convert(){}
    operator int&(){return val._int;}
    operator float&(){return val._float;}
  };
}