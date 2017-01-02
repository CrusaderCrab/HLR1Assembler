
namespace HLR1{

enum class CondCode{
    EQ,
    NE,
    LT,
    LE,
    GT,
    GE,
    BL,
    BE,
    AB,
    AE,
    END,
    FIRST=EQ
};

inline CondCode operator++( CondCode& x ) { return x = (CondCode)((uint32_t)(x) + 1); }

}
