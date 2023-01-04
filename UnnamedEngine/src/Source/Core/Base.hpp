#include <memory>

namespace UE
{
    // A Scope is a unique pointer that cannot have more than one owner
    template<typename T>
    using Scope = std::unique_ptr<T>;

    // Creates a Scope using the input args
    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
    
    // A Ref is a shared pointer that can have more than one owner, but free()
    // is called on the data if the owner count gets to 0
    template<typename T>
    using Ref = std::shared_ptr<T>;

    // Creates a Ref using the input args
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    using UEInt8 = signed char;
    using UEBool = bool;
    #define UE_INT8_MAX 127

    // UEResult is a abstraction used to return both data and result code
    template<typename T = void>
    class UEResult
    {
    public:
        using _UEResult = UEInt8;
        enum : _UEResult
        {
            Error     = -1,
            Success   = 0,
            Warn      = 1,
            Undefined = UE_INT8_MAX
        };

    public:
        UEResult()                 : Result(UEResult::Undefined) {}
        UEResult(_UEResult result) : Result(result) {}
        UEResult(T value)          : Result(UEResult::Success), Value(value) {}

        // Implicit operator
        operator UEBool() const
        {
            return (Result != UEResult::Error && Result != UEResult::Undefined);
        }

        UEResult& operator = (_UEResult result)
        {
            Result = result;
            return *this;
        }

    public:
        _UEResult Result;
        T Value;
    };

    template<>
    class UEResult<void>
    {
    public:
        using _UEResult = UEInt8;
        enum : _UEResult
        {
            Error     = -1,
            Success   = 0,
            Warn      = 1,
            Undefined = UE_INT8_MAX
        };

    public:
        UEResult()                 : Result(UEResult::Undefined) {}
        UEResult(_UEResult result) : Result(result) {}

        // Implicit operator
        operator UEBool() const
        {
            return (Result != UEResult::Error && Result != UEResult::Undefined);
        }
        
        UEResult& operator = (_UEResult result)
        {
            Result = result;
            return *this;
        }

    public:
        _UEResult Result;
    };
}