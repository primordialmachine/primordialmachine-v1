/// @file Collections/Queue.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_COLLECTIONS_QUEUE_H_INCLUDED)
#define MACHINE_COLLECTIONS_QUEUE_H_INCLUDED



#if !defined(MACHINE_COLLECTIONS_PRIVATE)
#error("Do not include this file directly, include `_Collections.h` instead.")
#endif

#include "./Collections/Collection.h"



/// @brief A queue.
/// We have a write position WRITE and rea position READ.
/// Both are initially 0.
/// 
/// We have a size SIZE and a capacity CAPACITY which is initially 0.
/// 
/// pushBack
/// First we check if the queue is full i.e. SIZE == CAPACITY.
/// If the queue is full, we increase the capacity such that SIZE < CAPACITY.
/// We store the element at e[(TAIL + 1) % CAPACITY] and then let TAIL' = (TAIL + 1) % CAPACITY and SIZE' = SIZE + 1.
/// 
/// pushFront
/// First we check if the queue is full i.e. SIZE == CAPACITY.
/// If the queue is full, we increase the capacity such that SIZE < CAPACITY.
/// We store the element at e[(HEAD - 1) % CAPACITY] and then let HEAD' = (HEAD - 1) % CAPACITY and SIZE' = SIZE + 1.
/// 
/// 
/// See https://opendatastructures.org/ods-cpp/2_3_Array_Based_Queue.html
MACHINE_DECLARE_CLASSTYPE(Machine_Queue)

struct Machine_Queue_Class {
  Machine_Collection_Class parent;
  void(*pushFront)(Machine_Queue* self, Machine_Value value);
  Machine_Value(*popFront)(Machine_Queue* self);
  void(*pushBack)(Machine_Queue* self, Machine_Value value);
  Machine_Value(*popBack)(Machine_Queue* self);
};

/// @brief As @a sie
struct Machine_Queue {
  Machine_Collection parent;
  /// @brief The size of the queue.
  size_t size;
  /// @brief The capacity of the queue.
  /// @initial @a 0.
  size_t capacity;
  /// @brief The head of the queue.
  /// @initial @a 0.
  size_t head;
  /// @brief The tail of the queue.
  /// @initial @a 0.
  size_t tail;
  /// @brief A pointer to an array of @a capacity Machine_Value elements.
  Machine_Value* elements;
};

/// @brief Construct this queue.
/// @param self A pointer to this queue.
/// @param numberOfArguments The number of arguments.
/// @param arguments The arguments.
void Machine_Queue_construct(Machine_Queue* self, size_t numberOfArguments, Machine_Value const* arguments);

/// @brief Create an empty queue.
/// @return The queue.
Machine_Queue* Machine_Queue_create();

/// @brief Dequeue a value from this queue.
/// @param self This queue.
/// @return The value.
Machine_Value Machine_Queue_popFront(Machine_Queue* self);

/// @brief Enqueue a value to this queue.
/// @param self This queue.
/// @param value The value.
void Machine_Queue_pushFront(Machine_Queue* self, Machine_Value value);

/// @brief Dequeue a value from this queue.
/// @param self This queue.
/// @return The value.
Machine_Value Machine_Queue_popBack(Machine_Queue* self);

/// @brief Enqueue a value to this queue.
/// @param self This queue.
/// @param value The value.
void Machine_Queue_pushBack(Machine_Queue* self, Machine_Value value);



#endif // MACHINE_COLLECTIONS_FIFOQUEUE_H_INCLUDED
