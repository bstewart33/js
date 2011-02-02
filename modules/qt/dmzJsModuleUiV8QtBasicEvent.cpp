#include "dmzJsModuleUiV8QtBasic.h"
#include <dmzJsV8UtilConvert.h>
#include <QtCore/QEvent>
#include <QtGui/QMouseEvent>


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_event_type (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);
   if (self) {

      QEvent *event = self->_to_qevent(Args.This ());
      if (event) { result = v8::Number::New (event->type ()); }
   }

   return scope.Close (result);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_mouse_event_button (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);
   if (self) {

      QMouseEvent *event = (QMouseEvent *)self->_to_qevent(Args.This ());
      if (event) { result = v8::Number::New (event->button ()); }
   }

   return scope.Close (result);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_mouse_event_buttons (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);
   if (self) {

      QMouseEvent *event = (QMouseEvent *)self->_to_qevent(Args.This ());
      if (event) { result = v8::Integer::New (event->buttons ()); }
   }

   return scope.Close (result);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_mouse_event_global_pos (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Object result;

   JsModuleUiV8QtBasic *self = _to_self (Args);
   if (self) {

      QMouseEvent *event = (QMouseEvent *)self->_to_qevent(Args.This ());
      if (event) {

         QPoint pos = event->globalPos ();
         result = v8::Object::New ();
         result->Set(v8::String::NewSymbol ("x"), v8::Number::New (pos.x ()));
         result->Set(v8::String::NewSymbol ("y"), v8::Number::New (pos.y ()));
      }
   }

   return scope.Close (result);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_mouse_event_global_x (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);
   if (self) {

      QMouseEvent *event = (QMouseEvent *)self->_to_qevent(Args.This ());
      if (event) { result = v8::Number::New (event->globalX ()); }
   }

   return scope.Close (result);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_mouse_event_global_y (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);
   if (self) {

      QMouseEvent *event = (QMouseEvent *)self->_to_qevent(Args.This ());
      if (event) { result = v8::Number::New (event->globalY ()); }
   }

   return scope.Close (result);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_mouse_event_pos (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Object result;

   JsModuleUiV8QtBasic *self = _to_self (Args);
   if (self) {

      QMouseEvent *event = (QMouseEvent *)self->_to_qevent(Args.This ());
      if (event) {

         QPoint pos = event->pos ();
         result = v8::Object::New ();
         result->Set(v8::String::NewSymbol ("x"), v8::Number::New (pos.x ()));
         result->Set(v8::String::NewSymbol ("y"), v8::Number::New (pos.y ()));
      }
   }

   return scope.Close (result);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_mouse_event_posf (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Object result;

   JsModuleUiV8QtBasic *self = _to_self (Args);
   if (self) {

      QMouseEvent *event = (QMouseEvent *)self->_to_qevent(Args.This ());
      if (event) {

         QPointF pos = event->posF ();
         result = v8::Object::New ();
         result->Set(v8::String::NewSymbol ("x"), v8::Number::New (pos.x ()));
         result->Set(v8::String::NewSymbol ("y"), v8::Number::New (pos.y ()));
      }
   }

   return scope.Close (result);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_mouse_event_x (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);
   if (self) {

      QMouseEvent *event = (QMouseEvent *)self->_to_qevent(Args.This ());
      if (event) { result = v8::Number::New (event->x ()); }
   }

   return scope.Close (result);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::_mouse_event_y (const v8::Arguments &Args) {

   v8::HandleScope scope;
   V8Value result = v8::Undefined ();

   JsModuleUiV8QtBasic *self = _to_self (Args);
   if (self) {

      QMouseEvent *event = (QMouseEvent *)self->_to_qevent(Args.This ());
      if (event) { result = v8::Number::New (event->y ()); }
   }

   return scope.Close (result);
}


dmz::V8Value
dmz::JsModuleUiV8QtBasic::create_v8_qevent (QEvent *value) {

   v8::Context::Scope cscope (_state.context);
   v8::HandleScope scope;

   V8Value result = v8::Undefined ();

   if (value) {

      V8Object obj;

      // NOTE: Adding a default will cause a DMZ crash for some events when the "type"
      // function is called. Until the specific reason is found, add and test events
      // on a case-by-case basis.
      switch (value->type ()) {

      case QEvent::MouseButtonDblClick:
      case QEvent::MouseButtonPress:
      case QEvent::MouseButtonRelease:
      case QEvent::MouseMove:
         if (!_mouseEventCtor.IsEmpty ()) { obj = _mouseEventCtor->NewInstance (); }
         break;
//      default: if (!_eventCtor.IsEmpty ()) { obj = _eventCtor->NewInstance (); } break;
      }

      if (!obj.IsEmpty ()) {

         obj->SetInternalField (0, v8::External::Wrap ((void *)value));
         result = obj;
      }
   }

   return scope.Close (result);
}


QEvent *
dmz::JsModuleUiV8QtBasic::_to_qevent (V8Value value) {

   v8::HandleScope scope;
   QEvent *result (0);

   V8Object obj = v8_to_object (value);
   if (!obj.IsEmpty ()) {

      if (_eventTemp->HasInstance (obj) || _mouseEventTemp->HasInstance (obj)) {

         result = (QEvent *)v8::External::Unwrap (obj->GetInternalField (0));
      }
   }

   return result;
}


void
dmz::JsModuleUiV8QtBasic::_init_mouse_event () {

   v8::HandleScope scope;

   _mouseEventTemp = V8FunctionTemplatePersist::New (v8::FunctionTemplate::New ());
   _mouseEventTemp->Inherit (_eventTemp);

   V8ObjectTemplate instance = _mouseEventTemp->InstanceTemplate ();
   instance->SetInternalFieldCount (1);

   V8ObjectTemplate proto = _mouseEventTemp->PrototypeTemplate ();
   proto->Set ("button", v8::FunctionTemplate::New (_mouse_event_button, _self));
   proto->Set ("buttons", v8::FunctionTemplate::New (_mouse_event_buttons, _self));
   proto->Set ("globalX", v8::FunctionTemplate::New (_mouse_event_global_x, _self));
   proto->Set ("globalY", v8::FunctionTemplate::New (_mouse_event_global_y, _self));
   proto->Set ("globalPos", v8::FunctionTemplate::New (_mouse_event_global_pos, _self));
   proto->Set ("pos", v8::FunctionTemplate::New (_mouse_event_pos, _self));
   proto->Set ("posF", v8::FunctionTemplate::New (_mouse_event_posf, _self));
   proto->Set ("x", v8::FunctionTemplate::New (_mouse_event_x, _self));
   proto->Set ("y", v8::FunctionTemplate::New (_mouse_event_y, _self));
}


void
dmz::JsModuleUiV8QtBasic::_init_event () {

   v8::HandleScope scope;

   _eventTemp = V8FunctionTemplatePersist::New (v8::FunctionTemplate::New ());

   V8ObjectTemplate instance = _eventTemp->InstanceTemplate ();
   instance->SetInternalFieldCount (1);

   V8ObjectTemplate proto = _eventTemp->PrototypeTemplate ();
   proto->Set ("type", v8::FunctionTemplate::New (_event_type, _self));

   // enum QEvent::Type
   _eventApi.add_constant ("MouseButtonDblClick", (UInt32)QEvent::MouseButtonDblClick);
   _eventApi.add_constant ("MouseButtonPress", (UInt32)QEvent::MouseButtonPress);
   _eventApi.add_constant ("MouseButtonRelease", (UInt32)QEvent::MouseButtonRelease);
   _eventApi.add_constant ("MouseMove", (UInt32)QEvent::MouseMove);
}