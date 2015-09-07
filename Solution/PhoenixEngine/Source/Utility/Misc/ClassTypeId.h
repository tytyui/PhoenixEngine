#ifndef PHOENIX_CLASS_TYPE_ID_H
#define PHOENIX_CLASS_TYPE_ID_H

namespace Phoenix
{
    template <typename TBase>
    class ClassTypeId
    {
    public:
        typedef std::size_t TypeId;
        
        template <typename T>
        static TypeId GetType()
        {
            static const TypeId ID = NextTypeId++;
            return ID;
        }
        
    private:
        static TypeId NextTypeId;
    };
    
    template <typename TBase>
    typename ClassTypeId<TBase>::TypeId ClassTypeId<TBase>::NextTypeId = 0;
}

#endif
