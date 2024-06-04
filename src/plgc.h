

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
    "table",
    "thread"
  };

  class gc_common{
  public:
    int mark;
    static const int m_color=1;
    unsigned int refcount;
    gc_common* next;
    int flags;
    
    gc_common(){
      mark=0;
      refcount=0;
      next=0;
    }
    virtual ~gc_common(){}
    
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
    } num_type;
    union{
      int _int;float _float;
    } val;
    void convert(Ttype t){
      if(t==num_type) return;
      switch(num_type){
	case _int:
	  switch(t){
	    case _float:
	      float tmp= val._int;
	      val._float= tmp;
	      num_type= _float;
	      break;
	  }
	  break;
	case _float:
	  switch(t){
	    case _int:
	      int tmp= val._float;
	      val._int= tmp;
	      num_type= _int;
	      break;
	  }
	  break;
      }
    }
    operator int&(){return val._int;}
    operator float&(){return val._float;}
  };
  
  class pl_table:gc_common{
  public:
    map<gc_common*,gc_common*> table;
    gc_common* operator [](gc_common*n){return table[n];}
  };
  
  class pl_thread:gc_common{
  public:
    //vector<pl_table*>
  };
  
  
}
