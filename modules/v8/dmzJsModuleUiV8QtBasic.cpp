#include "dmzJsModuleUiV8QtBasic.h"
#include "dmzJsModuleUiV8QtBasicWidgets.h"
#include <dmzJsModuleV8.h>
#include <dmzJsV8UtilConvert.h>
#include <dmzRuntimePluginFactoryLinkSymbol.h>
#include <dmzRuntimePluginInfo.h>
#include <dmzTypesStringTokenizer.h>
#include <QtGui/QtGui>
#include <QtUiTools/QUiLoader>

#include <QtCore/QDebug>

namespace {

static void
local_v8_qt_object_delete (dmz::V8ValuePersist object, void *param) {

   if (param) {

      dmz::V8QtObject *obj = (dmz::V8QtObject *)param;
      delete obj;
      obj = 0;
   }

   object.Dispose ();
   object.Clear ();
}

};


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_uiloader_load (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);
   const String Name = v8_to_string (Args[0]);

   if (self && Name) {

      QUiLoader loader;
      QFile file (Name.get_buffer ());
      file.open (QFile::ReadOnly);
      QWidget *widget = loader.load (&file, 0);
      file.close ();

      result = self->create_v8_widget (widget);
      
      self->_log.info << "Loaded UI: " << Name << endl;
   }

   return scope.Close (result);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_widget_close (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);
   if (self) {

      QWidget *widget = self->_to_qt_widget (Args.This ());
      if (widget) { widget->close (); }
   }

   return scope.Close (result);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_widget_hide (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);
   if (self) {

      QWidget *widget = self->_to_qt_widget (Args.This ());
      if (widget) { widget->hide (); }
   }

   return scope.Close (result);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_widget_lookup (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);

   if (self) {

      QWidget *widget = self->_to_qt_widget (Args.This ());
      String param = v8_to_string (Args[0]);

      if (widget && param) {

         QWidget *child = widget->findChild<QWidget *>(param.get_buffer ());

         if (child) {

            result = self->create_v8_widget (child);
         }
      }
   }

   return scope.Close (result);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_widget_observe (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);

   if (self && Args[0]->IsObject () && Args[2]->IsFunction ()) {

      V8QtObject *jsObject = self->_to_js_qt_object (Args.This ());
      if (jsObject) {
         
         QWidget *qtWidget = jsObject->get_qt_widget ();

         V8Object src = V8Object::Cast (Args[0]);
         const String Signal = v8_to_string (Args[1]).to_lower ();
         V8Function func = v8_to_function (Args[2]);

         if (qtWidget) {

            if (jsObject->bind (qtWidget, Signal)) {
               
               jsObject->add_callback (src, func);
            }
         }
         
         result = func;
      }
   }

   return scope.Close (result);
}


#if 0
dmz::V8Value
dmz::JsModuleUiV8QtBasic::_widget_property (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);
   if (self) {

      QWidget *widget = self->_to_qt_widget (Args.This ());
      if (widget) {

         // if (Args.Lengt () > 2) {
         //    
         //    const String Value = v8_to_string (Args[1]);
         // }
         // else {
         //    
         //    String Value;
         // }
      }
   }

   return scope.Close (result);
}
#endif


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_widget_show (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);
   if (self) {

      QWidget *widget = self->_to_qt_widget (Args.This ());
      if (widget) { widget->show (); }
   }

   return scope.Close (result);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_button_text (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);

   if (self) {

      QWidget *widget = self->_to_qt_widget (Args.This ());
      String param = v8_to_string (Args[0]);

      if (widget && param) {

         QAbstractButton *button = qobject_cast<QAbstractButton *>(widget);
         
         if (button) {

            button->setText (param.get_buffer ());
         }
      }
   }

   return scope.Close (result);
}


dmz::JsModuleUiV8QtBasic::JsModuleUiV8QtBasic (const PluginInfo &Info, Config &local) :
      Plugin (Info),
      JsModuleUiV8Qt (Info),
      JsExtV8 (Info),
      _log (Info),
      _core (0),
      _root (0),
      _qtApi () {

   _root = new QObject (0);
   _root->setObjectName (get_plugin_name ().get_buffer ());
   
   _init (local);
}


dmz::JsModuleUiV8QtBasic::~JsModuleUiV8QtBasic () {

   delete _root;
   _root = 0;
}


// Plugin Interface
void
dmz::JsModuleUiV8QtBasic::update_plugin_state (
      const PluginStateEnum State,
      const UInt32 Level) {

   if (State == PluginStateInit) {

   }
   else if (State == PluginStateStart) {

   }
   else if (State == PluginStateStop) {

   }
   else if (State == PluginStateShutdown) {

      _self.Dispose (); _self.Clear ();
   }
}


void
dmz::JsModuleUiV8QtBasic::discover_plugin (
      const PluginDiscoverEnum Mode,
      const Plugin *PluginPtr) {

   if (Mode == PluginDiscoverAdd) {

   }
   else if (Mode == PluginDiscoverRemove) {

   }
}


// JsModuleUiV8Qt Interface
dmz::V8Value
dmz::JsModuleUiV8QtBasic::create_v8_widget (QWidget *value) {

   v8::Context::Scope cscope (_v8Context);
   v8::HandleScope scope;

   V8Value result = v8::Undefined ();

   if (value) {
      
      V8Object vobj;
      V8QtObject *qobj;

      if (value->inherits ("QAbstractButton")) {
      
         if (!_buttonCtor.IsEmpty ()) {
            
            vobj = _buttonCtor->NewInstance ();
            qobj = new V8QtButton (value);
         }
      }
      else if (value->inherits ("QWidget")) {

         if (!_widgetCtor.IsEmpty ()) {
            
            vobj = _widgetCtor->NewInstance ();
            qobj = new V8QtWidget (value);
         }
      }
      
      if (!vobj.IsEmpty () && qobj) {
         
         vobj->SetInternalField (0, v8::External::Wrap ((void *)qobj));
         
         V8ObjectPersist persist = V8ObjectPersist::New (vobj);
         persist.MakeWeak ((void *)qobj, local_v8_qt_object_delete);
         
         result = vobj;
      }
   }

   return scope.Close (result);
}


// JsExtV8 Interface
void
dmz::JsModuleUiV8QtBasic::update_js_module_v8 (const ModeEnum Mode, JsModuleV8 &module) {

   if (Mode == JsExtV8::Store) {
      
      if (!_core) { _core = &module; }
   }
   else if (Mode == JsExtV8::Remove) {
      
      if (_core == &module) { _core = 0; }
   }
}


void
dmz::JsModuleUiV8QtBasic::update_js_context_v8 (v8::Handle<v8::Context> context) {

   _v8Context = context;
}


void
dmz::JsModuleUiV8QtBasic::update_js_ext_v8_state (const StateEnum State) {

   v8::HandleScope scope;

   if (State == JsExtV8::Register) {
      
      if (_core) {

         _core->register_interface ("dmz/components/ui", _qtApi.get_new_instance ());
      }
   }
   else if (State == JsExtV8::Init) {

      _widgetCtor = V8FunctionPersist::New (_widgetTemp->GetFunction ());
      _buttonCtor = V8FunctionPersist::New (_buttonTemp->GetFunction ());
   }
   else if (State == JsExtV8::Shutdown) {

      _widgetCtor.Dispose (); _widgetCtor.Clear ();
      _buttonCtor.Dispose (); _buttonCtor.Clear ();

      _qtApi.clear ();
      _v8Context.Clear ();
   }
}


QWidget  *
dmz::JsModuleUiV8QtBasic::_to_qt_widget (V8Value value) {
   
   QWidget *result (0);
   V8QtObject *object = _to_js_qt_object (value);
   if (object) { result = object->get_qt_widget (); }
   return result;
}


dmz::V8QtObject *
dmz::JsModuleUiV8QtBasic::_to_js_qt_object (V8Value value) {

   v8::HandleScope scope;
   V8QtObject *result (0);
   
   V8Object obj = v8_to_object (value);
   if (!obj.IsEmpty ()) {

      if (_widgetTemp->HasInstance (obj) ||
            _buttonTemp->HasInstance (obj)) {

         result = (V8QtObject *)v8::External::Unwrap (obj->GetInternalField (0));
      }
   }

   return result;
}


// JsModuleUiV8QtBasic Interface
void
dmz::JsModuleUiV8QtBasic::_init (Config &local) {

   v8::HandleScope scope;

   _self = V8ValuePersist::New (v8::External::Wrap (this));

   // API
   _qtApi.add_function ("load", _uiloader_load, _self);
   // _qtApi.add_function ("observer"< _global_observer, _self);

   _widgetTemp = V8FunctionTemplatePersist::New (v8::FunctionTemplate::New ());
   V8ObjectTemplate widgetProto = _widgetTemp->PrototypeTemplate ();
   widgetProto->Set ("close", v8::FunctionTemplate::New (_widget_close, _self));
   widgetProto->Set ("lookup", v8::FunctionTemplate::New (_widget_lookup, _self));
   widgetProto->Set ("show", v8::FunctionTemplate::New (_widget_show, _self));
   widgetProto->Set ("hide", v8::FunctionTemplate::New (_widget_hide, _self));
   widgetProto->Set ("observe", v8::FunctionTemplate::New (_widget_observe, _self));
   // widgetProto->Set ("property", v8::FunctionTemplate::New (_widget_property, _self));
   V8ObjectTemplate widgetInstance = _widgetTemp->InstanceTemplate ();
   widgetInstance->SetInternalFieldCount (1);

   _buttonTemp = V8FunctionTemplatePersist::New (v8::FunctionTemplate::New ());
   _buttonTemp->Inherit (_widgetTemp);
   V8ObjectTemplate buttonProto = _buttonTemp->PrototypeTemplate ();
   buttonProto->Set ("text", v8::FunctionTemplate::New (_button_text, _self));
   V8ObjectTemplate buttonInstance = _buttonTemp->InstanceTemplate ();
   buttonInstance->SetInternalFieldCount (1);
}


extern "C" {

DMZ_PLUGIN_FACTORY_LINK_SYMBOL dmz::Plugin *
create_dmzJsModuleUiV8QtBasic (
      const dmz::PluginInfo &Info,
      dmz::Config &local,
      dmz::Config &global) {

   return new dmz::JsModuleUiV8QtBasic (Info, local);
}

};
