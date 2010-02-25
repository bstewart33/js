#ifndef DMZ_JS_MODULE_V8_DOT_H
#define DMZ_JS_MODULE_V8_DOT_H

#include <dmzRuntimePlugin.h>
#include <dmzRuntimeRTTI.h>
#include <dmzTypesBase.h>
#include <dmzTypesString.h>

#include <v8.h>

namespace dmz {

   class JsModuleV8 {

      public:
         static JsModuleV8 *cast (
            const Plugin *PluginPtr,
            const String &PluginName = "");

         String get_js_module_v8_name () const;
         Handle get_js_module_v8_handle () const;

         // JsModuleV8 Interface
         

      protected:
         JsModuleV8 (const PluginInfo &Info);
         ~JsModuleV8 ();

      private:
         JsModuleV8 ();
         JsModuleV8 (const JsModuleV8 &);
         JsModuleV8 &operator= (const JsModuleV8 &);

         const PluginInfo &__Info;
   };

   //! \cond
   const char JsModuleV8InterfaceName[] = "JsModuleV8Interface";
   //! \endcond
};


inline dmz::JsModuleV8 *
dmz::JsModuleV8::cast (const Plugin *PluginPtr, const String &PluginName) {

   return (JsModuleV8 *)lookup_rtti_interface (
      JsModuleV8InterfaceName,
      PluginName,
      PluginPtr);
}


inline
dmz::JsModuleV8::JsModuleV8 (const PluginInfo &Info) :
      __Info (Info) {

   store_rtti_interface (JsModuleV8InterfaceName, __Info, (void *)this);
}


inline
dmz::JsModuleV8::~JsModuleV8 () {

   remove_rtti_interface (JsModuleV8InterfaceName, __Info);
}


inline dmz::String
dmz::JsModuleV8::get_js_module_v8_name () const { return __Info.get_name (); }


inline dmz::Handle
dmz::JsModuleV8::get_js_module_v8_handle () const { return __Info.get_handle (); }

#endif // DMZ_JS_MODULE_V8_DOT_H