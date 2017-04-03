#ifndef MEMORYSLOTFILTER
#define MEMORYSLOTFILTER


class BaseInfoClient;


/*
 * How to use the specialized filter:
 *
 class MemorySlotSessionTokenFilter : public BaseMemorySlotFilter<std::string> {
    public:
        bool operator()(BaseMemorySlot& slot, const std::string& key) {
            if (key == slot.token)
                return (true);
            return (false);
        }
 };

 class MemorySlotUserIdFilter : public BaseMemorySlotFilter<int> {
    public:
        bool operator ()(BaseMemorySlot &slot, const int &key) {
            if (key == slot.userId)
                return (true);
            return (false);
        }
 };

 ...
 MemorySlotSessionTokenFilter    mySessionTokenFilter;
 BaseMemorySlot                  *slot = 0;

 slot = tcpServer.findMemorySlot(mySessionTokenFilter, myStringKey);
*/

template<typename T>
class BaseMemorySlotFilter {
    private:
        BaseMemorySlotFilter(const BaseMemorySlotFilter&);
        BaseMemorySlotFilter& operator=(const BaseMemorySlotFilter&);

    public:
        BaseMemorySlotFilter() {}
        //
        // where customized filter will take place:
        virtual bool operator()(BaseInfoClient& slot, const T& key) = 0;
};

#endif // MEMORYSLOTFILTER

