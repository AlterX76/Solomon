#ifndef IBASETYPE_H
#define IBASETYPE_H

#include "Solomon.h"
#include "DataContainerReader.h"
#include "DataContainerWriter.h"
#include "SolomSmallString.h"
#include "SolomLargeString.h"
#include "SolomDatetime.h"
#include "MemorySupport.h"


namespace Solomon {
    //
    // interfaccia per tutti i tipi base:
    namespace Types {
        //
        // common type for all kind of objects:
        template <typename object>
        class DLL_ACTION IBaseType {
            private:
                object          _object;

            public:
                IBaseType() : _object(0) {}
                virtual ~IBaseType() {}

                virtual void    writeIn(DataContainerWriter *stream) {
                    stream->Put(this->_object);
                }

                virtual void    readFrom(DataContainerReader *stream) {
                    stream->Extract(&this->_object);
                }

                virtual size_t  length() const {
                    return (0);
                }
                virtual size_t  size() const {
                    return (sizeof(this->_object));
                }
                virtual object  get() {
                    return (this->_object);
                }
                virtual void    set(object obj) {
                    this->_object = obj;
                }
        };
        //
        // Explicit Specialization of Class Templates:
        template<> class DLL_ACTION IBaseType<SolomSmallString *> {
            private:
                SolomSmallString    *_object;

            public:
                IBaseType() : _object(0) {
                    this->set(EMPTY_STRING);
                }

                virtual ~IBaseType() {
                    MemoryUtil::DeleteMemory(&this->_object, TRUE);
                }

                virtual void writeIn(DataContainerWriter *stream) {
                    if (stream != 0)
                        this->_object->WriteIn(stream);
                }

                virtual void readFrom(DataContainerReader *stream) {
                    if (stream != 0) {
                        MemoryUtil::DeleteMemory(&this->_object, TRUE);
                        this->_object = new SolomSmallString(stream);
                    }
                }

                virtual size_t length() const {
                    return (this->_object->GetLength());
                }

                virtual size_t size() const {
                    return (this->_object->GetSizeOfSolomString());
                }

                virtual u_buffer_pointer get() {
                    return (this->_object->GetText());
                }

                virtual void set(string text) {
                    MemoryUtil::DeleteMemory(&this->_object, TRUE);
                    this->_object = new SolomSmallString((buffer_pointer)text.c_str());
                }
        };
        //
        // Explicit Specialization of Class Templates:
        template<> class DLL_ACTION IBaseType<SolomLargeString *> {
            private:
                SolomLargeString    *_object;

        public:
            IBaseType() : _object(0) {
                this->set(EMPTY_STRING);
            }

            virtual ~IBaseType() {
                MemoryUtil::DeleteMemory(&this->_object, TRUE);
            }

            virtual void writeIn(DataContainerWriter *stream) {
                if (stream != 0)
                    this->_object->WriteIn(stream);
            }

            virtual void readFrom(DataContainerReader *stream) {
                if (stream != 0) {
                    MemoryUtil::DeleteMemory(&this->_object, TRUE);
                    this->_object = new SolomLargeString(stream);
                }
            }

            virtual size_t length() const {
                return (this->_object->GetTextLength());
            }

            virtual size_t size() const {
                return (this->_object->GetSizeOfSolomString());
            }

            virtual u_buffer_pointer get() {
                return (this->_object->GetText());
            }

            virtual void set(string text) {
                MemoryUtil::DeleteMemory(&this->_object, TRUE);
                this->_object = new SolomLargeString((buffer_pointer)text.c_str());
            }
        };

        //
        // Explicit Specialization of Class Templates:
        template<> class DLL_ACTION IBaseType<SolomDateTime *> {
            private:
                SolomDateTime   *_object;
                buffer_pointer  _dateTime;

            public:
                IBaseType() : _object(0), _dateTime(0) {
                    ; // no real inizialitation required
                }

                virtual ~IBaseType() {
                    MemoryUtil::DeleteMemory(&this->_object, TRUE);
                    MemoryUtil::DeleteMemory(&this->_dateTime, TRUE);
                }

                virtual void writeIn(DataContainerWriter *stream) {
                    if (stream != 0 && _object != 0)
                        this->_object->WriteIn(stream);
                }

                virtual void readFrom(DataContainerReader *stream) {
                    if (stream != NULL) {
                        MemoryUtil::DeleteMemory(&this->_object, TRUE);
                        this->_object = new SolomDateTime(stream);
                    }
                }

                virtual size_t length() const {
                    buffer_pointer  dateTime = 0;
                    u_short         length = 0;

                    if (_object != 0)
                        this->_object->GetDateTime(&dateTime);
                    if (dateTime != 0) {
                        length = strlen(dateTime);
                        MemoryUtil::DeleteMemory(&dateTime, TRUE);
                    }
                    return (length);
                }

                virtual size_t size() const {
                    size_t length = 0;

                    if (_object != 0)
                        length = this->_object->GetSizeOfSolomDateTime();
                    return (length);
                }

                virtual u_buffer_pointer get() {
                    if (_object != 0) {
                        MemoryUtil::DeleteMemory(&this->_dateTime, TRUE);
                        this->_object->GetDateTime(&this->_dateTime);
                    }
                    return ((u_buffer_pointer)this->_dateTime);
                }

                virtual void set(string dateTime) {
                    MemoryUtil::DeleteMemory(&this->_object, TRUE);
                    this->_object = new SolomDateTime((buffer_pointer)dateTime.c_str(), FALSE);
                }
        };
        //
        // explicit declarations of instance:
        template class IBaseType<byte>;
        template class IBaseType<geo>;
        template class IBaseType<integer>;
        template class IBaseType<u_integer>;
        template class IBaseType<u_longer>;
        template class IBaseType<shorter>;
        template class IBaseType<u_short>;
    }
}
#endif // IBASETYPE_H
