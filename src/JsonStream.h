// ----------------------------------------------------------------------------
// JsonStream.h
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#ifndef _JSON_STREAM_H_
#define _JSON_STREAM_H_
#ifdef ARDUINO
#include <Arduino.h>
#else
#include <cstddef>
#include <cstring>
#endif
#include <Streaming.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <ArduinoJson.h>


class JsonDepthTracker
{
public:
  JsonDepthTracker();
  JsonDepthTracker(bool first_item,
    bool inside_object);
  bool first_item_;
  bool inside_object_;
};

class JsonStream
{
public:
  enum JsonTypes
  {
    LONG_TYPE,
    DOUBLE_TYPE,
    BOOL_TYPE,
    NULL_TYPE,
    STRING_TYPE,
    OBJECT_TYPE,
    ARRAY_TYPE,
    ANY_TYPE
  };
  static const uint8_t STRING_LENGTH_DOUBLE=36;
  static const uint8_t DOUBLE_DIGITS_DEFAULT=6;
  static const char EOL='\n';
  static const uint16_t BUFFER_LENGTH_MAX=256;

  JsonStream();
  JsonStream(Stream & stream);
  void setStream(Stream & stream);
  void removeStream();
  bool streamIsSet();
  Stream & getStream();

  // encoder methods
  void beginObject();
  void endObject();
  void beginArray();
  void endArray();
  void setCompactPrint();
  void setPrettyPrint();
  template<typename K>
  void writeKey(K key);
  template<typename T>
  void write(T value);
  template<typename T>
  void writeDouble(T value,
    unsigned char prec=DOUBLE_DIGITS_DEFAULT);
  template<typename K,
    typename T>
  void write(K key,
    T value);
  template<typename K,
    typename T>
  void writeDouble(K key,
    T value,
    unsigned char prec=DOUBLE_DIGITS_DEFAULT);
  void writeNull();
  template<typename K>
  void writeNull(K key);
  template<typename T>
  void writeJson(T value);
  template<typename K,
    typename T>
  void writeJson(K key,
    T value);
  void writeNewline();
  void writeChar(char c);
  void writeByte(byte b);
  template <typename T,
    size_t N>
  void write(T (& values)[N]);
  template <size_t N>
  void write(const char (& values)[N]);
  template <size_t N>
  void write(char (& values)[N]);
  template <typename K,
    typename T,
    size_t N>
  void write(K key,
    T (& values)[N]);
  template <typename T>
  void writeArray(T * values,
    size_t N);
  template <typename K,
    typename T>
  void writeArray(K key,
    T * values,
    size_t N);
  template <typename T,
    size_t N>
  void write(Array<T,N> values);
  template <typename T>
  void write(Vector<T> values);
  template <typename T,
    size_t N>
  void write(Array<T,N> * values_ptr);
  template <typename T>
  void write(Vector<T> * values_ptr);

  // decoder methods
  int available();
  template <size_t N>
  long readJsonIntoBuffer(char (&buffer)[N]);
  template<typename T>
  bool readJsonAndFind(T target);
  char readChar();
  void clear();
private:
  static const uint8_t RESPONSE_DEPTH_MAX=8;
  static const uint8_t RESPONSE_INDENT=2;
  Stream * stream_ptr_;
  bool pretty_print_;
  byte indent_level_;
  bool writing_;
  Array<JsonDepthTracker,RESPONSE_DEPTH_MAX> depth_tracker_;
  void indent();
  void endItem();
  void endArrayItem();
  template<size_t N>
  void prettyPrintBuffer(const char (&buffer)[N]);
};

#include "JsonStream/JsonStreamDefinitions.h"

#endif
