// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: route_guide.proto

#ifndef PROTOBUF_INCLUDED_route_5fguide_2eproto
#define PROTOBUF_INCLUDED_route_5fguide_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_route_5fguide_2eproto 

namespace protobuf_route_5fguide_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[5];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_route_5fguide_2eproto
namespace routeguide {
class Feature;
class FeatureDefaultTypeInternal;
extern FeatureDefaultTypeInternal _Feature_default_instance_;
class Point;
class PointDefaultTypeInternal;
extern PointDefaultTypeInternal _Point_default_instance_;
class Rectangle;
class RectangleDefaultTypeInternal;
extern RectangleDefaultTypeInternal _Rectangle_default_instance_;
class RouteNote;
class RouteNoteDefaultTypeInternal;
extern RouteNoteDefaultTypeInternal _RouteNote_default_instance_;
class RouteSummary;
class RouteSummaryDefaultTypeInternal;
extern RouteSummaryDefaultTypeInternal _RouteSummary_default_instance_;
}  // namespace routeguide
namespace google {
namespace protobuf {
template<> ::routeguide::Feature* Arena::CreateMaybeMessage<::routeguide::Feature>(Arena*);
template<> ::routeguide::Point* Arena::CreateMaybeMessage<::routeguide::Point>(Arena*);
template<> ::routeguide::Rectangle* Arena::CreateMaybeMessage<::routeguide::Rectangle>(Arena*);
template<> ::routeguide::RouteNote* Arena::CreateMaybeMessage<::routeguide::RouteNote>(Arena*);
template<> ::routeguide::RouteSummary* Arena::CreateMaybeMessage<::routeguide::RouteSummary>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace routeguide {

// ===================================================================

class Point : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:routeguide.Point) */ {
 public:
  Point();
  virtual ~Point();

  Point(const Point& from);

  inline Point& operator=(const Point& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Point(Point&& from) noexcept
    : Point() {
    *this = ::std::move(from);
  }

  inline Point& operator=(Point&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Point& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Point* internal_default_instance() {
    return reinterpret_cast<const Point*>(
               &_Point_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(Point* other);
  friend void swap(Point& a, Point& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Point* New() const final {
    return CreateMaybeMessage<Point>(NULL);
  }

  Point* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Point>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Point& from);
  void MergeFrom(const Point& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Point* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // int32 latitude = 1;
  void clear_latitude();
  static const int kLatitudeFieldNumber = 1;
  ::google::protobuf::int32 latitude() const;
  void set_latitude(::google::protobuf::int32 value);

  // int32 longitude = 2;
  void clear_longitude();
  static const int kLongitudeFieldNumber = 2;
  ::google::protobuf::int32 longitude() const;
  void set_longitude(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:routeguide.Point)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::int32 latitude_;
  ::google::protobuf::int32 longitude_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_route_5fguide_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class Rectangle : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:routeguide.Rectangle) */ {
 public:
  Rectangle();
  virtual ~Rectangle();

  Rectangle(const Rectangle& from);

  inline Rectangle& operator=(const Rectangle& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Rectangle(Rectangle&& from) noexcept
    : Rectangle() {
    *this = ::std::move(from);
  }

  inline Rectangle& operator=(Rectangle&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Rectangle& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Rectangle* internal_default_instance() {
    return reinterpret_cast<const Rectangle*>(
               &_Rectangle_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(Rectangle* other);
  friend void swap(Rectangle& a, Rectangle& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Rectangle* New() const final {
    return CreateMaybeMessage<Rectangle>(NULL);
  }

  Rectangle* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Rectangle>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Rectangle& from);
  void MergeFrom(const Rectangle& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Rectangle* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // .routeguide.Point lo = 1;
  bool has_lo() const;
  void clear_lo();
  static const int kLoFieldNumber = 1;
  private:
  const ::routeguide::Point& _internal_lo() const;
  public:
  const ::routeguide::Point& lo() const;
  ::routeguide::Point* release_lo();
  ::routeguide::Point* mutable_lo();
  void set_allocated_lo(::routeguide::Point* lo);

  // .routeguide.Point hi = 2;
  bool has_hi() const;
  void clear_hi();
  static const int kHiFieldNumber = 2;
  private:
  const ::routeguide::Point& _internal_hi() const;
  public:
  const ::routeguide::Point& hi() const;
  ::routeguide::Point* release_hi();
  ::routeguide::Point* mutable_hi();
  void set_allocated_hi(::routeguide::Point* hi);

  // @@protoc_insertion_point(class_scope:routeguide.Rectangle)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::routeguide::Point* lo_;
  ::routeguide::Point* hi_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_route_5fguide_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class Feature : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:routeguide.Feature) */ {
 public:
  Feature();
  virtual ~Feature();

  Feature(const Feature& from);

  inline Feature& operator=(const Feature& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Feature(Feature&& from) noexcept
    : Feature() {
    *this = ::std::move(from);
  }

  inline Feature& operator=(Feature&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Feature& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Feature* internal_default_instance() {
    return reinterpret_cast<const Feature*>(
               &_Feature_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  void Swap(Feature* other);
  friend void swap(Feature& a, Feature& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Feature* New() const final {
    return CreateMaybeMessage<Feature>(NULL);
  }

  Feature* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Feature>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Feature& from);
  void MergeFrom(const Feature& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Feature* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string name = 1;
  void clear_name();
  static const int kNameFieldNumber = 1;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  #if LANG_CXX11
  void set_name(::std::string&& value);
  #endif
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // .routeguide.Point location = 2;
  bool has_location() const;
  void clear_location();
  static const int kLocationFieldNumber = 2;
  private:
  const ::routeguide::Point& _internal_location() const;
  public:
  const ::routeguide::Point& location() const;
  ::routeguide::Point* release_location();
  ::routeguide::Point* mutable_location();
  void set_allocated_location(::routeguide::Point* location);

  // @@protoc_insertion_point(class_scope:routeguide.Feature)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::routeguide::Point* location_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_route_5fguide_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class RouteNote : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:routeguide.RouteNote) */ {
 public:
  RouteNote();
  virtual ~RouteNote();

  RouteNote(const RouteNote& from);

  inline RouteNote& operator=(const RouteNote& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  RouteNote(RouteNote&& from) noexcept
    : RouteNote() {
    *this = ::std::move(from);
  }

  inline RouteNote& operator=(RouteNote&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const RouteNote& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const RouteNote* internal_default_instance() {
    return reinterpret_cast<const RouteNote*>(
               &_RouteNote_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    3;

  void Swap(RouteNote* other);
  friend void swap(RouteNote& a, RouteNote& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline RouteNote* New() const final {
    return CreateMaybeMessage<RouteNote>(NULL);
  }

  RouteNote* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<RouteNote>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const RouteNote& from);
  void MergeFrom(const RouteNote& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(RouteNote* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // bytes datasend = 1;
  void clear_datasend();
  static const int kDatasendFieldNumber = 1;
  const ::std::string& datasend() const;
  void set_datasend(const ::std::string& value);
  #if LANG_CXX11
  void set_datasend(::std::string&& value);
  #endif
  void set_datasend(const char* value);
  void set_datasend(const void* value, size_t size);
  ::std::string* mutable_datasend();
  ::std::string* release_datasend();
  void set_allocated_datasend(::std::string* datasend);

  // int32 size = 2;
  void clear_size();
  static const int kSizeFieldNumber = 2;
  ::google::protobuf::int32 size() const;
  void set_size(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:routeguide.RouteNote)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr datasend_;
  ::google::protobuf::int32 size_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_route_5fguide_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class RouteSummary : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:routeguide.RouteSummary) */ {
 public:
  RouteSummary();
  virtual ~RouteSummary();

  RouteSummary(const RouteSummary& from);

  inline RouteSummary& operator=(const RouteSummary& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  RouteSummary(RouteSummary&& from) noexcept
    : RouteSummary() {
    *this = ::std::move(from);
  }

  inline RouteSummary& operator=(RouteSummary&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const RouteSummary& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const RouteSummary* internal_default_instance() {
    return reinterpret_cast<const RouteSummary*>(
               &_RouteSummary_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    4;

  void Swap(RouteSummary* other);
  friend void swap(RouteSummary& a, RouteSummary& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline RouteSummary* New() const final {
    return CreateMaybeMessage<RouteSummary>(NULL);
  }

  RouteSummary* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<RouteSummary>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const RouteSummary& from);
  void MergeFrom(const RouteSummary& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(RouteSummary* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // int32 point_count = 1;
  void clear_point_count();
  static const int kPointCountFieldNumber = 1;
  ::google::protobuf::int32 point_count() const;
  void set_point_count(::google::protobuf::int32 value);

  // int32 feature_count = 2;
  void clear_feature_count();
  static const int kFeatureCountFieldNumber = 2;
  ::google::protobuf::int32 feature_count() const;
  void set_feature_count(::google::protobuf::int32 value);

  // int32 distance = 3;
  void clear_distance();
  static const int kDistanceFieldNumber = 3;
  ::google::protobuf::int32 distance() const;
  void set_distance(::google::protobuf::int32 value);

  // int32 elapsed_time = 4;
  void clear_elapsed_time();
  static const int kElapsedTimeFieldNumber = 4;
  ::google::protobuf::int32 elapsed_time() const;
  void set_elapsed_time(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:routeguide.RouteSummary)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::int32 point_count_;
  ::google::protobuf::int32 feature_count_;
  ::google::protobuf::int32 distance_;
  ::google::protobuf::int32 elapsed_time_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_route_5fguide_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Point

// int32 latitude = 1;
inline void Point::clear_latitude() {
  latitude_ = 0;
}
inline ::google::protobuf::int32 Point::latitude() const {
  // @@protoc_insertion_point(field_get:routeguide.Point.latitude)
  return latitude_;
}
inline void Point::set_latitude(::google::protobuf::int32 value) {
  
  latitude_ = value;
  // @@protoc_insertion_point(field_set:routeguide.Point.latitude)
}

// int32 longitude = 2;
inline void Point::clear_longitude() {
  longitude_ = 0;
}
inline ::google::protobuf::int32 Point::longitude() const {
  // @@protoc_insertion_point(field_get:routeguide.Point.longitude)
  return longitude_;
}
inline void Point::set_longitude(::google::protobuf::int32 value) {
  
  longitude_ = value;
  // @@protoc_insertion_point(field_set:routeguide.Point.longitude)
}

// -------------------------------------------------------------------

// Rectangle

// .routeguide.Point lo = 1;
inline bool Rectangle::has_lo() const {
  return this != internal_default_instance() && lo_ != NULL;
}
inline void Rectangle::clear_lo() {
  if (GetArenaNoVirtual() == NULL && lo_ != NULL) {
    delete lo_;
  }
  lo_ = NULL;
}
inline const ::routeguide::Point& Rectangle::_internal_lo() const {
  return *lo_;
}
inline const ::routeguide::Point& Rectangle::lo() const {
  const ::routeguide::Point* p = lo_;
  // @@protoc_insertion_point(field_get:routeguide.Rectangle.lo)
  return p != NULL ? *p : *reinterpret_cast<const ::routeguide::Point*>(
      &::routeguide::_Point_default_instance_);
}
inline ::routeguide::Point* Rectangle::release_lo() {
  // @@protoc_insertion_point(field_release:routeguide.Rectangle.lo)
  
  ::routeguide::Point* temp = lo_;
  lo_ = NULL;
  return temp;
}
inline ::routeguide::Point* Rectangle::mutable_lo() {
  
  if (lo_ == NULL) {
    auto* p = CreateMaybeMessage<::routeguide::Point>(GetArenaNoVirtual());
    lo_ = p;
  }
  // @@protoc_insertion_point(field_mutable:routeguide.Rectangle.lo)
  return lo_;
}
inline void Rectangle::set_allocated_lo(::routeguide::Point* lo) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete lo_;
  }
  if (lo) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      lo = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, lo, submessage_arena);
    }
    
  } else {
    
  }
  lo_ = lo;
  // @@protoc_insertion_point(field_set_allocated:routeguide.Rectangle.lo)
}

// .routeguide.Point hi = 2;
inline bool Rectangle::has_hi() const {
  return this != internal_default_instance() && hi_ != NULL;
}
inline void Rectangle::clear_hi() {
  if (GetArenaNoVirtual() == NULL && hi_ != NULL) {
    delete hi_;
  }
  hi_ = NULL;
}
inline const ::routeguide::Point& Rectangle::_internal_hi() const {
  return *hi_;
}
inline const ::routeguide::Point& Rectangle::hi() const {
  const ::routeguide::Point* p = hi_;
  // @@protoc_insertion_point(field_get:routeguide.Rectangle.hi)
  return p != NULL ? *p : *reinterpret_cast<const ::routeguide::Point*>(
      &::routeguide::_Point_default_instance_);
}
inline ::routeguide::Point* Rectangle::release_hi() {
  // @@protoc_insertion_point(field_release:routeguide.Rectangle.hi)
  
  ::routeguide::Point* temp = hi_;
  hi_ = NULL;
  return temp;
}
inline ::routeguide::Point* Rectangle::mutable_hi() {
  
  if (hi_ == NULL) {
    auto* p = CreateMaybeMessage<::routeguide::Point>(GetArenaNoVirtual());
    hi_ = p;
  }
  // @@protoc_insertion_point(field_mutable:routeguide.Rectangle.hi)
  return hi_;
}
inline void Rectangle::set_allocated_hi(::routeguide::Point* hi) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete hi_;
  }
  if (hi) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      hi = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, hi, submessage_arena);
    }
    
  } else {
    
  }
  hi_ = hi;
  // @@protoc_insertion_point(field_set_allocated:routeguide.Rectangle.hi)
}

// -------------------------------------------------------------------

// Feature

// string name = 1;
inline void Feature::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Feature::name() const {
  // @@protoc_insertion_point(field_get:routeguide.Feature.name)
  return name_.GetNoArena();
}
inline void Feature::set_name(const ::std::string& value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:routeguide.Feature.name)
}
#if LANG_CXX11
inline void Feature::set_name(::std::string&& value) {
  
  name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:routeguide.Feature.name)
}
#endif
inline void Feature::set_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:routeguide.Feature.name)
}
inline void Feature::set_name(const char* value, size_t size) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:routeguide.Feature.name)
}
inline ::std::string* Feature::mutable_name() {
  
  // @@protoc_insertion_point(field_mutable:routeguide.Feature.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Feature::release_name() {
  // @@protoc_insertion_point(field_release:routeguide.Feature.name)
  
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Feature::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    
  } else {
    
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:routeguide.Feature.name)
}

// .routeguide.Point location = 2;
inline bool Feature::has_location() const {
  return this != internal_default_instance() && location_ != NULL;
}
inline void Feature::clear_location() {
  if (GetArenaNoVirtual() == NULL && location_ != NULL) {
    delete location_;
  }
  location_ = NULL;
}
inline const ::routeguide::Point& Feature::_internal_location() const {
  return *location_;
}
inline const ::routeguide::Point& Feature::location() const {
  const ::routeguide::Point* p = location_;
  // @@protoc_insertion_point(field_get:routeguide.Feature.location)
  return p != NULL ? *p : *reinterpret_cast<const ::routeguide::Point*>(
      &::routeguide::_Point_default_instance_);
}
inline ::routeguide::Point* Feature::release_location() {
  // @@protoc_insertion_point(field_release:routeguide.Feature.location)
  
  ::routeguide::Point* temp = location_;
  location_ = NULL;
  return temp;
}
inline ::routeguide::Point* Feature::mutable_location() {
  
  if (location_ == NULL) {
    auto* p = CreateMaybeMessage<::routeguide::Point>(GetArenaNoVirtual());
    location_ = p;
  }
  // @@protoc_insertion_point(field_mutable:routeguide.Feature.location)
  return location_;
}
inline void Feature::set_allocated_location(::routeguide::Point* location) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete location_;
  }
  if (location) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      location = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, location, submessage_arena);
    }
    
  } else {
    
  }
  location_ = location;
  // @@protoc_insertion_point(field_set_allocated:routeguide.Feature.location)
}

// -------------------------------------------------------------------

// RouteNote

// bytes datasend = 1;
inline void RouteNote::clear_datasend() {
  datasend_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& RouteNote::datasend() const {
  // @@protoc_insertion_point(field_get:routeguide.RouteNote.datasend)
  return datasend_.GetNoArena();
}
inline void RouteNote::set_datasend(const ::std::string& value) {
  
  datasend_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:routeguide.RouteNote.datasend)
}
#if LANG_CXX11
inline void RouteNote::set_datasend(::std::string&& value) {
  
  datasend_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:routeguide.RouteNote.datasend)
}
#endif
inline void RouteNote::set_datasend(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  datasend_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:routeguide.RouteNote.datasend)
}
inline void RouteNote::set_datasend(const void* value, size_t size) {
  
  datasend_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:routeguide.RouteNote.datasend)
}
inline ::std::string* RouteNote::mutable_datasend() {
  
  // @@protoc_insertion_point(field_mutable:routeguide.RouteNote.datasend)
  return datasend_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* RouteNote::release_datasend() {
  // @@protoc_insertion_point(field_release:routeguide.RouteNote.datasend)
  
  return datasend_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void RouteNote::set_allocated_datasend(::std::string* datasend) {
  if (datasend != NULL) {
    
  } else {
    
  }
  datasend_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), datasend);
  // @@protoc_insertion_point(field_set_allocated:routeguide.RouteNote.datasend)
}

// int32 size = 2;
inline void RouteNote::clear_size() {
  size_ = 0;
}
inline ::google::protobuf::int32 RouteNote::size() const {
  // @@protoc_insertion_point(field_get:routeguide.RouteNote.size)
  return size_;
}
inline void RouteNote::set_size(::google::protobuf::int32 value) {
  
  size_ = value;
  // @@protoc_insertion_point(field_set:routeguide.RouteNote.size)
}

// -------------------------------------------------------------------

// RouteSummary

// int32 point_count = 1;
inline void RouteSummary::clear_point_count() {
  point_count_ = 0;
}
inline ::google::protobuf::int32 RouteSummary::point_count() const {
  // @@protoc_insertion_point(field_get:routeguide.RouteSummary.point_count)
  return point_count_;
}
inline void RouteSummary::set_point_count(::google::protobuf::int32 value) {
  
  point_count_ = value;
  // @@protoc_insertion_point(field_set:routeguide.RouteSummary.point_count)
}

// int32 feature_count = 2;
inline void RouteSummary::clear_feature_count() {
  feature_count_ = 0;
}
inline ::google::protobuf::int32 RouteSummary::feature_count() const {
  // @@protoc_insertion_point(field_get:routeguide.RouteSummary.feature_count)
  return feature_count_;
}
inline void RouteSummary::set_feature_count(::google::protobuf::int32 value) {
  
  feature_count_ = value;
  // @@protoc_insertion_point(field_set:routeguide.RouteSummary.feature_count)
}

// int32 distance = 3;
inline void RouteSummary::clear_distance() {
  distance_ = 0;
}
inline ::google::protobuf::int32 RouteSummary::distance() const {
  // @@protoc_insertion_point(field_get:routeguide.RouteSummary.distance)
  return distance_;
}
inline void RouteSummary::set_distance(::google::protobuf::int32 value) {
  
  distance_ = value;
  // @@protoc_insertion_point(field_set:routeguide.RouteSummary.distance)
}

// int32 elapsed_time = 4;
inline void RouteSummary::clear_elapsed_time() {
  elapsed_time_ = 0;
}
inline ::google::protobuf::int32 RouteSummary::elapsed_time() const {
  // @@protoc_insertion_point(field_get:routeguide.RouteSummary.elapsed_time)
  return elapsed_time_;
}
inline void RouteSummary::set_elapsed_time(::google::protobuf::int32 value) {
  
  elapsed_time_ = value;
  // @@protoc_insertion_point(field_set:routeguide.RouteSummary.elapsed_time)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace routeguide

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_route_5fguide_2eproto
