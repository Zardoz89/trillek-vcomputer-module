// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: device_state.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "device_state.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
// @@protoc_insertion_point(includes)

namespace trillek {
namespace computer {

void protobuf_ShutdownFile_device_5fstate_2eproto() {
  delete DeviceState::default_instance_;
  delete DeviceState_DeviceProperty::default_instance_;
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
void protobuf_AddDesc_device_5fstate_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#else
void protobuf_AddDesc_device_5fstate_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#endif
  DeviceState::default_instance_ = new DeviceState();
  DeviceState_DeviceProperty::default_instance_ = new DeviceState_DeviceProperty();
  DeviceState::default_instance_->InitAsDefaultInstance();
  DeviceState_DeviceProperty::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_device_5fstate_2eproto);
}

#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_device_5fstate_2eproto_once_);
void protobuf_AddDesc_device_5fstate_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_device_5fstate_2eproto_once_,
                 &protobuf_AddDesc_device_5fstate_2eproto_impl);
}
#else
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_device_5fstate_2eproto {
  StaticDescriptorInitializer_device_5fstate_2eproto() {
    protobuf_AddDesc_device_5fstate_2eproto();
  }
} static_descriptor_initializer_device_5fstate_2eproto_;
#endif

// ===================================================================

bool DeviceState_DeviceProperty_Type_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const DeviceState_DeviceProperty_Type DeviceState_DeviceProperty::BOOL;
const DeviceState_DeviceProperty_Type DeviceState_DeviceProperty::STRING;
const DeviceState_DeviceProperty_Type DeviceState_DeviceProperty::INT;
const DeviceState_DeviceProperty_Type DeviceState_DeviceProperty::FLOAT;
const DeviceState_DeviceProperty_Type DeviceState_DeviceProperty::LONG;
const DeviceState_DeviceProperty_Type DeviceState_DeviceProperty::RAW;
const DeviceState_DeviceProperty_Type DeviceState_DeviceProperty::Type_MIN;
const DeviceState_DeviceProperty_Type DeviceState_DeviceProperty::Type_MAX;
const int DeviceState_DeviceProperty::Type_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int DeviceState_DeviceProperty::kTypeFieldNumber;
const int DeviceState_DeviceProperty::kNameFieldNumber;
const int DeviceState_DeviceProperty::kBvalueFieldNumber;
const int DeviceState_DeviceProperty::kSvalueFieldNumber;
const int DeviceState_DeviceProperty::kIvalueFieldNumber;
const int DeviceState_DeviceProperty::kLvalueFieldNumber;
const int DeviceState_DeviceProperty::kFvalueFieldNumber;
const int DeviceState_DeviceProperty::kRvalueFieldNumber;
#endif  // !_MSC_VER

DeviceState_DeviceProperty::DeviceState_DeviceProperty()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:trillek.computer.DeviceState.DeviceProperty)
}

void DeviceState_DeviceProperty::InitAsDefaultInstance() {
}

DeviceState_DeviceProperty::DeviceState_DeviceProperty(const DeviceState_DeviceProperty& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:trillek.computer.DeviceState.DeviceProperty)
}

void DeviceState_DeviceProperty::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  type_ = 0;
  name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  clear_has_value();
}

DeviceState_DeviceProperty::~DeviceState_DeviceProperty() {
  // @@protoc_insertion_point(destructor:trillek.computer.DeviceState.DeviceProperty)
  SharedDtor();
}

void DeviceState_DeviceProperty::SharedDtor() {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete name_;
  }
  if (has_value()) {
    clear_value();
  }
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void DeviceState_DeviceProperty::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const DeviceState_DeviceProperty& DeviceState_DeviceProperty::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_device_5fstate_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_device_5fstate_2eproto();
#endif
  return *default_instance_;
}

DeviceState_DeviceProperty* DeviceState_DeviceProperty::default_instance_ = NULL;

DeviceState_DeviceProperty* DeviceState_DeviceProperty::New() const {
  return new DeviceState_DeviceProperty;
}

void DeviceState_DeviceProperty::clear_value() {
  switch(value_case()) {
    case kBvalue: {
      // No need to clear
      break;
    }
    case kSvalue: {
      delete value_.svalue_;
      break;
    }
    case kIvalue: {
      // No need to clear
      break;
    }
    case kLvalue: {
      // No need to clear
      break;
    }
    case kFvalue: {
      // No need to clear
      break;
    }
    case kRvalue: {
      delete value_.rvalue_;
      break;
    }
    case VALUE_NOT_SET: {
      break;
    }
  }
  _oneof_case_[0] = VALUE_NOT_SET;
}


void DeviceState_DeviceProperty::Clear() {
  if (_has_bits_[0 / 32] & 3) {
    type_ = 0;
    if (has_name()) {
      if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        name_->clear();
      }
    }
  }
  clear_value();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->clear();
}

bool DeviceState_DeviceProperty::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  ::google::protobuf::io::StringOutputStream unknown_fields_string(
      mutable_unknown_fields());
  ::google::protobuf::io::CodedOutputStream unknown_fields_stream(
      &unknown_fields_string);
  // @@protoc_insertion_point(parse_start:trillek.computer.DeviceState.DeviceProperty)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .trillek.computer.DeviceState.DeviceProperty.Type type = 1;
      case 1: {
        if (tag == 8) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::trillek::computer::DeviceState_DeviceProperty_Type_IsValid(value)) {
            set_type(static_cast< ::trillek::computer::DeviceState_DeviceProperty_Type >(value));
          } else {
            unknown_fields_stream.WriteVarint32(tag);
            unknown_fields_stream.WriteVarint32(value);
          }
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_name;
        break;
      }

      // required string name = 2;
      case 2: {
        if (tag == 18) {
         parse_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_bvalue;
        break;
      }

      // optional bool bvalue = 3;
      case 3: {
        if (tag == 24) {
         parse_bvalue:
          clear_value();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &value_.bvalue_)));
          set_has_bvalue();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(34)) goto parse_svalue;
        break;
      }

      // optional string svalue = 4;
      case 4: {
        if (tag == 34) {
         parse_svalue:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_svalue()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(40)) goto parse_ivalue;
        break;
      }

      // optional uint32 ivalue = 5;
      case 5: {
        if (tag == 40) {
         parse_ivalue:
          clear_value();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &value_.ivalue_)));
          set_has_ivalue();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(48)) goto parse_lvalue;
        break;
      }

      // optional uint64 lvalue = 6;
      case 6: {
        if (tag == 48) {
         parse_lvalue:
          clear_value();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &value_.lvalue_)));
          set_has_lvalue();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(61)) goto parse_fvalue;
        break;
      }

      // optional float fvalue = 7;
      case 7: {
        if (tag == 61) {
         parse_fvalue:
          clear_value();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &value_.fvalue_)));
          set_has_fvalue();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(66)) goto parse_rvalue;
        break;
      }

      // optional bytes rvalue = 8;
      case 8: {
        if (tag == 66) {
         parse_rvalue:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_rvalue()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(
            input, tag, &unknown_fields_stream));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:trillek.computer.DeviceState.DeviceProperty)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:trillek.computer.DeviceState.DeviceProperty)
  return false;
#undef DO_
}

void DeviceState_DeviceProperty::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:trillek.computer.DeviceState.DeviceProperty)
  // required .trillek.computer.DeviceState.DeviceProperty.Type type = 1;
  if (has_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->type(), output);
  }

  // required string name = 2;
  if (has_name()) {
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->name(), output);
  }

  // optional bool bvalue = 3;
  if (has_bvalue()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(3, this->bvalue(), output);
  }

  // optional string svalue = 4;
  if (has_svalue()) {
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      4, this->svalue(), output);
  }

  // optional uint32 ivalue = 5;
  if (has_ivalue()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(5, this->ivalue(), output);
  }

  // optional uint64 lvalue = 6;
  if (has_lvalue()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(6, this->lvalue(), output);
  }

  // optional float fvalue = 7;
  if (has_fvalue()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(7, this->fvalue(), output);
  }

  // optional bytes rvalue = 8;
  if (has_rvalue()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      8, this->rvalue(), output);
  }

  output->WriteRaw(unknown_fields().data(),
                   unknown_fields().size());
  // @@protoc_insertion_point(serialize_end:trillek.computer.DeviceState.DeviceProperty)
}

int DeviceState_DeviceProperty::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required .trillek.computer.DeviceState.DeviceProperty.Type type = 1;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->type());
    }

    // required string name = 2;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->name());
    }

  }
  switch (value_case()) {
    // optional bool bvalue = 3;
    case kBvalue: {
      total_size += 1 + 1;
      break;
    }
    // optional string svalue = 4;
    case kSvalue: {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->svalue());
      break;
    }
    // optional uint32 ivalue = 5;
    case kIvalue: {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->ivalue());
      break;
    }
    // optional uint64 lvalue = 6;
    case kLvalue: {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt64Size(
          this->lvalue());
      break;
    }
    // optional float fvalue = 7;
    case kFvalue: {
      total_size += 1 + 4;
      break;
    }
    // optional bytes rvalue = 8;
    case kRvalue: {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->rvalue());
      break;
    }
    case VALUE_NOT_SET: {
      break;
    }
  }
  total_size += unknown_fields().size();

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void DeviceState_DeviceProperty::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const DeviceState_DeviceProperty*>(&from));
}

void DeviceState_DeviceProperty::MergeFrom(const DeviceState_DeviceProperty& from) {
  GOOGLE_CHECK_NE(&from, this);
  switch (from.value_case()) {
    case kBvalue: {
      set_bvalue(from.bvalue());
      break;
    }
    case kSvalue: {
      set_svalue(from.svalue());
      break;
    }
    case kIvalue: {
      set_ivalue(from.ivalue());
      break;
    }
    case kLvalue: {
      set_lvalue(from.lvalue());
      break;
    }
    case kFvalue: {
      set_fvalue(from.fvalue());
      break;
    }
    case kRvalue: {
      set_rvalue(from.rvalue());
      break;
    }
    case VALUE_NOT_SET: {
      break;
    }
  }
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_type()) {
      set_type(from.type());
    }
    if (from.has_name()) {
      set_name(from.name());
    }
  }
  mutable_unknown_fields()->append(from.unknown_fields());
}

void DeviceState_DeviceProperty::CopyFrom(const DeviceState_DeviceProperty& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool DeviceState_DeviceProperty::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void DeviceState_DeviceProperty::Swap(DeviceState_DeviceProperty* other) {
  if (other != this) {
    std::swap(type_, other->type_);
    std::swap(name_, other->name_);
    std::swap(value_, other->value_);
    std::swap(_oneof_case_[0], other->_oneof_case_[0]);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.swap(other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::std::string DeviceState_DeviceProperty::GetTypeName() const {
  return "trillek.computer.DeviceState.DeviceProperty";
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int DeviceState::kDevTypeFieldNumber;
const int DeviceState::kDevSubtypeFieldNumber;
const int DeviceState::kDevIdFieldNumber;
const int DeviceState::kDevVendorIdFieldNumber;
const int DeviceState::kAFieldNumber;
const int DeviceState::kBFieldNumber;
const int DeviceState::kCFieldNumber;
const int DeviceState::kDFieldNumber;
const int DeviceState::kEFieldNumber;
const int DeviceState::kPropertiesFieldNumber;
#endif  // !_MSC_VER

DeviceState::DeviceState()
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:trillek.computer.DeviceState)
}

void DeviceState::InitAsDefaultInstance() {
}

DeviceState::DeviceState(const DeviceState& from)
  : ::google::protobuf::MessageLite() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:trillek.computer.DeviceState)
}

void DeviceState::SharedCtor() {
  _cached_size_ = 0;
  dev_type_ = 0u;
  dev_subtype_ = 0u;
  dev_id_ = 0u;
  dev_vendor_id_ = 0u;
  a_ = 0u;
  b_ = 0u;
  c_ = 0u;
  d_ = 0u;
  e_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

DeviceState::~DeviceState() {
  // @@protoc_insertion_point(destructor:trillek.computer.DeviceState)
  SharedDtor();
}

void DeviceState::SharedDtor() {
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  if (this != &default_instance()) {
  #else
  if (this != default_instance_) {
  #endif
  }
}

void DeviceState::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const DeviceState& DeviceState::default_instance() {
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  protobuf_AddDesc_device_5fstate_2eproto();
#else
  if (default_instance_ == NULL) protobuf_AddDesc_device_5fstate_2eproto();
#endif
  return *default_instance_;
}

DeviceState* DeviceState::default_instance_ = NULL;

DeviceState* DeviceState::New() const {
  return new DeviceState;
}

void DeviceState::Clear() {
  _extensions_.Clear();
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<DeviceState*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 255) {
    ZR_(dev_type_, d_);
  }
  e_ = 0u;

#undef OFFSET_OF_FIELD_
#undef ZR_

  properties_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->clear();
}

bool DeviceState::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  ::google::protobuf::io::StringOutputStream unknown_fields_string(
      mutable_unknown_fields());
  ::google::protobuf::io::CodedOutputStream unknown_fields_stream(
      &unknown_fields_string);
  // @@protoc_insertion_point(parse_start:trillek.computer.DeviceState)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 dev_type = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &dev_type_)));
          set_has_dev_type();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_dev_subtype;
        break;
      }

      // required uint32 dev_subtype = 2;
      case 2: {
        if (tag == 16) {
         parse_dev_subtype:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &dev_subtype_)));
          set_has_dev_subtype();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_dev_id;
        break;
      }

      // required uint32 dev_id = 3;
      case 3: {
        if (tag == 24) {
         parse_dev_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &dev_id_)));
          set_has_dev_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_dev_vendor_id;
        break;
      }

      // required uint32 dev_vendor_id = 4;
      case 4: {
        if (tag == 32) {
         parse_dev_vendor_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &dev_vendor_id_)));
          set_has_dev_vendor_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(40)) goto parse_a;
        break;
      }

      // optional uint32 a = 5;
      case 5: {
        if (tag == 40) {
         parse_a:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &a_)));
          set_has_a();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(48)) goto parse_b;
        break;
      }

      // optional uint32 b = 6;
      case 6: {
        if (tag == 48) {
         parse_b:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &b_)));
          set_has_b();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(56)) goto parse_c;
        break;
      }

      // optional uint32 c = 7;
      case 7: {
        if (tag == 56) {
         parse_c:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &c_)));
          set_has_c();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(64)) goto parse_d;
        break;
      }

      // optional uint32 d = 8;
      case 8: {
        if (tag == 64) {
         parse_d:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &d_)));
          set_has_d();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(72)) goto parse_e;
        break;
      }

      // optional uint32 e = 9;
      case 9: {
        if (tag == 72) {
         parse_e:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &e_)));
          set_has_e();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(82)) goto parse_properties;
        break;
      }

      // repeated .trillek.computer.DeviceState.DeviceProperty properties = 10;
      case 10: {
        if (tag == 82) {
         parse_properties:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_properties()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(82)) goto parse_properties;
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        if ((8000u <= tag)) {
        #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
          DO_(_extensions_.ParseField(tag, input, &default_instance(),
                                      &unknown_fields_stream));
        #else
          DO_(_extensions_.ParseField(tag, input, default_instance_,
                                      &unknown_fields_stream));
        #endif
          continue;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(
            input, tag, &unknown_fields_stream));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:trillek.computer.DeviceState)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:trillek.computer.DeviceState)
  return false;
#undef DO_
}

void DeviceState::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:trillek.computer.DeviceState)
  // required uint32 dev_type = 1;
  if (has_dev_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->dev_type(), output);
  }

  // required uint32 dev_subtype = 2;
  if (has_dev_subtype()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->dev_subtype(), output);
  }

  // required uint32 dev_id = 3;
  if (has_dev_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->dev_id(), output);
  }

  // required uint32 dev_vendor_id = 4;
  if (has_dev_vendor_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->dev_vendor_id(), output);
  }

  // optional uint32 a = 5;
  if (has_a()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(5, this->a(), output);
  }

  // optional uint32 b = 6;
  if (has_b()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(6, this->b(), output);
  }

  // optional uint32 c = 7;
  if (has_c()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(7, this->c(), output);
  }

  // optional uint32 d = 8;
  if (has_d()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(8, this->d(), output);
  }

  // optional uint32 e = 9;
  if (has_e()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(9, this->e(), output);
  }

  // repeated .trillek.computer.DeviceState.DeviceProperty properties = 10;
  for (int i = 0; i < this->properties_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      10, this->properties(i), output);
  }

  // Extension range [1000, 536870912)
  _extensions_.SerializeWithCachedSizes(
      1000, 536870912, output);

  output->WriteRaw(unknown_fields().data(),
                   unknown_fields().size());
  // @@protoc_insertion_point(serialize_end:trillek.computer.DeviceState)
}

int DeviceState::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 dev_type = 1;
    if (has_dev_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->dev_type());
    }

    // required uint32 dev_subtype = 2;
    if (has_dev_subtype()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->dev_subtype());
    }

    // required uint32 dev_id = 3;
    if (has_dev_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->dev_id());
    }

    // required uint32 dev_vendor_id = 4;
    if (has_dev_vendor_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->dev_vendor_id());
    }

    // optional uint32 a = 5;
    if (has_a()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->a());
    }

    // optional uint32 b = 6;
    if (has_b()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->b());
    }

    // optional uint32 c = 7;
    if (has_c()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->c());
    }

    // optional uint32 d = 8;
    if (has_d()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->d());
    }

  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // optional uint32 e = 9;
    if (has_e()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->e());
    }

  }
  // repeated .trillek.computer.DeviceState.DeviceProperty properties = 10;
  total_size += 1 * this->properties_size();
  for (int i = 0; i < this->properties_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->properties(i));
  }

  total_size += _extensions_.ByteSize();

  total_size += unknown_fields().size();

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void DeviceState::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const DeviceState*>(&from));
}

void DeviceState::MergeFrom(const DeviceState& from) {
  GOOGLE_CHECK_NE(&from, this);
  properties_.MergeFrom(from.properties_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_dev_type()) {
      set_dev_type(from.dev_type());
    }
    if (from.has_dev_subtype()) {
      set_dev_subtype(from.dev_subtype());
    }
    if (from.has_dev_id()) {
      set_dev_id(from.dev_id());
    }
    if (from.has_dev_vendor_id()) {
      set_dev_vendor_id(from.dev_vendor_id());
    }
    if (from.has_a()) {
      set_a(from.a());
    }
    if (from.has_b()) {
      set_b(from.b());
    }
    if (from.has_c()) {
      set_c(from.c());
    }
    if (from.has_d()) {
      set_d(from.d());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from.has_e()) {
      set_e(from.e());
    }
  }
  _extensions_.MergeFrom(from._extensions_);
  mutable_unknown_fields()->append(from.unknown_fields());
}

void DeviceState::CopyFrom(const DeviceState& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool DeviceState::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000000f) != 0x0000000f) return false;

  if (!::google::protobuf::internal::AllAreInitialized(this->properties())) return false;

  if (!_extensions_.IsInitialized()) return false;  return true;
}

void DeviceState::Swap(DeviceState* other) {
  if (other != this) {
    std::swap(dev_type_, other->dev_type_);
    std::swap(dev_subtype_, other->dev_subtype_);
    std::swap(dev_id_, other->dev_id_);
    std::swap(dev_vendor_id_, other->dev_vendor_id_);
    std::swap(a_, other->a_);
    std::swap(b_, other->b_);
    std::swap(c_, other->c_);
    std::swap(d_, other->d_);
    std::swap(e_, other->e_);
    properties_.Swap(&other->properties_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.swap(other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
    _extensions_.Swap(&other->_extensions_);
  }
}

::std::string DeviceState::GetTypeName() const {
  return "trillek.computer.DeviceState";
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace computer
}  // namespace trillek

// @@protoc_insertion_point(global_scope)
