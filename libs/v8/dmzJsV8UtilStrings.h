#ifndef DMZ_JS_V8_UTIL_STRINGS_DOT_H
#define DMZ_JS_V8_UTIL_STRINGS_DOT_H

#include <dmzJsV8UtilExport.h>
#include <dmzTypesBase.h>
#include <dmzTypesString.h>

#include <v8.h>

namespace dmz {

class DMZ_JS_V8_UTIL_LINK_SYMBOL V8FileString :
      public v8::String::ExternalAsciiStringResource {

   public:
      V8FileString (const String &FileName);

      V8FileString (
         const String &FileName,
         const String &Header,
         const String &Footer);

      virtual ~V8FileString ();

      String get_file_name () const;
      // ExternalAsciiStringResource Interface.
      virtual const char *data () const;
      virtual size_t length () const;

   protected:
      struct State;
      State &_state;

   private:
      V8FileString ();
      V8FileString (const V8FileString &);
      V8FileString &operator= (const V8FileString &);
};

class DMZ_JS_V8_UTIL_LINK_SYMBOL V8EmbeddedBuffer :
      public v8::String::ExternalAsciiStringResource {

   public:
      V8EmbeddedBuffer (char *buffer, const size_t Length);
      virtual ~V8EmbeddedBuffer ();

      // ExternalAsciiStringResource Interface.
      virtual const char *data () const;
      virtual size_t length () const;

   protected:
      struct State;
      State &_state;

   private:
      V8EmbeddedBuffer ();
      V8EmbeddedBuffer (const V8EmbeddedBuffer &);
      V8EmbeddedBuffer &operator= (const V8EmbeddedBuffer &);
};

class DMZ_JS_V8_UTIL_LINK_SYMBOL V8EmbeddedString :
      public v8::String::ExternalAsciiStringResource {

   public:
      V8EmbeddedString (String *ptr);
      V8EmbeddedString (const char *Buffer, const size_t Length);
      virtual ~V8EmbeddedString ();

      // ExternalAsciiStringResource Interface.
      virtual const char *data () const;
      virtual size_t length () const;

   protected:
      struct State;
      State &_state;

   private:
      V8EmbeddedString ();
      V8EmbeddedString (const V8EmbeddedString &);
      V8EmbeddedString &operator= (const V8EmbeddedString &);
};

class DMZ_JS_V8_UTIL_LINK_SYMBOL V8ExternalString :
      public v8::String::ExternalAsciiStringResource {

   public:
      V8ExternalString (
         const char *Buffer,
         const size_t Length);

      V8ExternalString (
         const char *Buffer,
         const size_t Length,
         const String &Header,
         const String &Footer);

      virtual ~V8ExternalString ();

      void ref ();

      // ExternalAsciiStringResource Interface.
      virtual void Dispose ();
      virtual const char *data () const;
      virtual size_t length () const;

   protected:
      struct State;
      State &_state;

   private:
      V8ExternalString ();
      V8ExternalString (const V8ExternalString &);
      V8ExternalString &operator= (const V8ExternalString &);
};

};

#endif // DMZ_JS_V8_UTIL_STRINGS_DOT_H
